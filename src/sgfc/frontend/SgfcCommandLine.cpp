// Project includes
#include "../../../include/SgfcConstants.h"
#include "../../SgfcUtility.h"
#include "../message/SgfcMessage.h"
#include "SgfcCommandLine.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcCommandLine::SgfcCommandLine(const std::vector<std::shared_ptr<ISgfcArgument>>& arguments)
    : backendController(new SgfcBackendController(arguments))
  {
  }

  SgfcCommandLine::~SgfcCommandLine()
  {
  }

  std::vector<std::shared_ptr<ISgfcArgument>> SgfcCommandLine::GetArguments() const
  {
    return this->backendController->GetArguments();
  }

  bool SgfcCommandLine::IsCommandLineValid() const
  {
    return this->backendController->IsCommandLineValid();
  }

  std::shared_ptr<ISgfcMessage> SgfcCommandLine::GetInvalidCommandLineReason() const
  {
    return this->backendController->GetInvalidCommandLineReason();
  }


  SgfcExitCode SgfcCommandLine::LoadSgfFile(const std::string& sgfFilePath)
  {
    this->backendLoadResult = this->backendController->LoadSgfFile(sgfFilePath);

    SgfcExitCode sgfcExitCode = SgfcUtility::GetSgfcExitCodeFromMessageCollection(
      this->backendLoadResult->GetParseResult());

    return sgfcExitCode;
  }

  SgfcExitCode SgfcCommandLine::LoadSgfContent(const std::string& sgfContent)
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    std::string tempFilePath = SgfcUtility::GetUniqueTempFilePath();

    try
    {
      SgfcUtility::AppendTextToFile(tempFilePath, sgfContent);
    }
    catch (std::runtime_error&)
    {
      std::string messageText = "Writing SGF content to temporary file failed: " + tempFilePath;
      SgfcExitCode sgfcExitCode = CreateAndSetBackendLoadResultWithErrorMessage(
        SgfcConstants::SaveSgfContentToFilesystemErrorMessageID,
        messageText);
      return sgfcExitCode;
    }

    auto sgfcExitCode = LoadSgfFile(tempFilePath);

    try
    {
      SgfcUtility::DeleteFileIfExists(tempFilePath);
    }
    catch (std::runtime_error&)
    {
      std::string messageText = "Deleting temporary file failed: " + tempFilePath;
      SgfcExitCode sgfcExitCode = CreateAndSetBackendLoadResultWithErrorMessage(
        SgfcConstants::DeleteFileErrorMessageID,
        messageText);
      return sgfcExitCode;
    }

    return sgfcExitCode;
  }

  bool SgfcCommandLine::IsSgfContentValid() const
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    if (this->backendLoadResult == nullptr)
      return false;

    return SgfcUtility::GetIsSgfDataValidFromMessageCollection(this->backendLoadResult->GetParseResult());
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcCommandLine::GetParseResult() const
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    if (this->backendLoadResult == nullptr)
      return std::vector<std::shared_ptr<ISgfcMessage>>();

    return this->backendLoadResult->GetParseResult();
  }

  SgfcExitCode SgfcCommandLine::SaveSgfFile(const std::string& sgfFilePath)
  {
    ThrowIfIsSgfContentValidReturnsFalse();

    this->backendSaveResult = this->backendController->SaveSgfFile(
      sgfFilePath,
      this->backendLoadResult->GetSgfDataWrapper());

    SgfcExitCode sgfcExitCode = SgfcUtility::GetSgfcExitCodeFromMessageCollection(
      this->backendSaveResult->GetSaveResult());

    return sgfcExitCode;
  }

  SgfcExitCode SgfcCommandLine::SaveSgfContent(std::string& sgfContent)
  {
    ThrowIfIsSgfContentValidReturnsFalse();

    std::string tempFilePath = SgfcUtility::GetUniqueTempFilePath();

    auto sgfcExitCode = SaveSgfFile(tempFilePath);

    if (sgfcExitCode == SgfcExitCode::FatalError)
    {
      DeleteTempFileOrCreateAndSetBackendSaveResultWithErrorMessage(tempFilePath);
      return SgfcExitCode::FatalError;
    }

    try
    {
      sgfContent = SgfcUtility::ReadFileContent(tempFilePath);
    }
    catch (std::runtime_error&)
    {
      bool deleteTempFileSuccess = DeleteTempFileOrCreateAndSetBackendSaveResultWithErrorMessage(tempFilePath);
      if (! deleteTempFileSuccess)
        return SgfcExitCode::FatalError;

      std::string messageText = "Reading SGF content from temporary file failed: " + tempFilePath;
      SgfcExitCode sgfcExitCode = CreateAndSetBackendSaveResultWithErrorMessage(
        SgfcConstants::ReadSgfContentFromFilesystemErrorMessageID,
        messageText);
      return sgfcExitCode;
    }

    bool deleteTempFileSuccess = DeleteTempFileOrCreateAndSetBackendSaveResultWithErrorMessage(tempFilePath);
    if (! deleteTempFileSuccess)
      return SgfcExitCode::FatalError;

    return sgfcExitCode;
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcCommandLine::GetSaveResult() const
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    if (this->backendSaveResult == nullptr)
      return std::vector<std::shared_ptr<ISgfcMessage>>();

    return this->backendSaveResult->GetSaveResult();
  }

  void SgfcCommandLine::ThrowIfIsCommandLineValidReturnsFalse() const
  {
    if (! this->IsCommandLineValid())
      throw std::logic_error("Interface protocol violation: IsCommandLineValid() returns false");
  }

  void SgfcCommandLine::ThrowIfIsSgfContentValidReturnsFalse() const
  {
    if (! this->IsSgfContentValid())
      throw std::logic_error("Interface protocol violation: IsSgfContentValid() returns false");
  }

  bool SgfcCommandLine::DeleteTempFileOrCreateAndSetBackendSaveResultWithErrorMessage(
    const std::string& tempFilePath)
  {
    try
    {
      SgfcUtility::DeleteFileIfExists(tempFilePath);
      return true;
    }
    catch (std::runtime_error&)
    {
      std::string messageText = "Deleting temporary file failed: " + tempFilePath;
      SgfcExitCode sgfcExitCode = CreateAndSetBackendSaveResultWithErrorMessage(
        SgfcConstants::DeleteFileErrorMessageID,
        messageText);
      return false;
    }
  }

  SgfcExitCode SgfcCommandLine::CreateAndSetBackendLoadResultWithErrorMessage(
    int messageID,
    const std::string& messageText)
  {
    auto message = std::shared_ptr<ISgfcMessage>(new SgfcMessage(
      messageID,
      messageText));

    std::vector<std::shared_ptr<ISgfcMessage>> parseResult = { message };
    std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper =
      std::shared_ptr<SgfcBackendDataWrapper>(new SgfcBackendDataWrapper());

    std::shared_ptr<SgfcBackendLoadResult> backendLoadResult =
      std::shared_ptr<SgfcBackendLoadResult>(new SgfcBackendLoadResult(parseResult, sgfDataWrapper));

    return SgfcUtility::GetSgfcExitCodeFromMessageCollection(parseResult);
  }

  SgfcExitCode SgfcCommandLine::CreateAndSetBackendSaveResultWithErrorMessage(
    int messageID,
    const std::string& messageText)
  {
    auto message = std::shared_ptr<ISgfcMessage>(new SgfcMessage(
      messageID,
      messageText));

    std::vector<std::shared_ptr<ISgfcMessage>> saveSgfResult = { message };

    std::shared_ptr<SgfcBackendSaveResult> backendSaveResult =
      std::shared_ptr<SgfcBackendSaveResult>(new SgfcBackendSaveResult(saveSgfResult));

    return SgfcUtility::GetSgfcExitCodeFromMessageCollection(saveSgfResult);
  }
}
