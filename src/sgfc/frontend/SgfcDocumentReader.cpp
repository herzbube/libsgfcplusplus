// Project includes
#include "../../../include/SgfcConstants.h"
#include "../../document/SgfcDocument.h"
#include "../../SgfcUtility.h"
#include "../argument/SgfcArguments.h"
#include "../backend/SgfcBackendController.h"
#include "../message/SgfcMessage.h"
#include "SgfcDocumentReader.h"
#include "SgfcDocumentReadResult.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcDocumentReader::SgfcDocumentReader()
    : arguments(new SgfcArguments())
  {
  }

  SgfcDocumentReader::~SgfcDocumentReader()
  {
  }

  std::shared_ptr<ISgfcArguments> SgfcDocumentReader::GetArguments() const
  {
    return this->arguments;
  }

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::ReadSgfFile(const std::string& sgfFilePath)
  {
    SgfcBackendController backendController(this->arguments->GetArguments());

    std::shared_ptr<SgfcBackendLoadResult> backendLoadResult = backendController.LoadSgfFile(sgfFilePath);

    SgfcExitCode sgfcExitCode = SgfcUtility::GetSgfcExitCodeFromMessageCollection(
      backendLoadResult->GetParseResult());

    std::shared_ptr<ISgfcDocument> document;
    if (sgfcExitCode != SgfcExitCode::FatalError)
      document = std::shared_ptr<ISgfcDocument>(new SgfcDocument(backendLoadResult->GetSgfDataWrapper()->GetSgfData()));
    else
      document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());

    std::shared_ptr<ISgfcDocumentReadResult> result = std::shared_ptr<ISgfcDocumentReadResult>(new SgfcDocumentReadResult(
      backendLoadResult->GetParseResult(),
      document));
    return result;
  }

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::ReadSgfContent(const std::string& sgfContent)
  {
    std::string tempFilePath = SgfcUtility::GetUniqueTempFilePath();

    try
    {
      SgfcUtility::AppendTextToFile(tempFilePath, sgfContent);
    }
    catch (std::runtime_error&)
    {
      std::string messageText = "Writing SGF content to temporary file failed: " + tempFilePath;
      auto result = CreateReadResultWithErrorMessage(
        SgfcConstants::SaveSgfContentToFilesystemErrorMessageID,
        messageText);
      return result;
    }

    auto result = ReadSgfFile(tempFilePath);

    try
    {
      SgfcUtility::DeleteFileIfExists(tempFilePath);
    }
    catch (std::runtime_error&)
    {
      std::string messageText = "Deleting temporary file failed: " + tempFilePath;
      auto result = CreateReadResultWithErrorMessage(
        SgfcConstants::DeleteFileErrorMessageID,
        messageText);
      return result;
    }

    return result;
  }

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::CreateReadResultWithErrorMessage(
    int messageID,
    const std::string& messageText) const
  {
    auto message = std::shared_ptr<ISgfcMessage>(new SgfcMessage(
      messageID,
      messageText));

    std::vector<std::shared_ptr<ISgfcMessage>> parseResult = { message };
    auto document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());

    return std::shared_ptr<ISgfcDocumentReadResult>(new SgfcDocumentReadResult(
      parseResult,
      document));
  }
}
