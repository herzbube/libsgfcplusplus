// Project includes
#include "SgfcCommandLine.h"
#include "SgfcUtility.h"

// SGFC includes
extern "C"
{
  #include "../sgfc/all.h"
  #include "../sgfc/protos.h"
}

// C++ Standard Library includes
#include <algorithm>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcCommandLine::SgfcCommandLine(const std::vector<std::string>& arguments)
    : backendController(new SgfcBackendController(arguments))
  {
  }

  SgfcCommandLine::~SgfcCommandLine()
  {
  }

  std::vector<std::string> SgfcCommandLine::GetArguments() const
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

    throw std::runtime_error("not yet implemented");
  }

  bool SgfcCommandLine::IsSgfContentValid() const
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    return SgfcUtility::GetIsSgfDataValidFromMessageCollection(this->backendLoadResult->GetParseResult());
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcCommandLine::GetParseResult() const
  {
    ThrowIfIsCommandLineValidReturnsFalse();

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

    throw std::runtime_error("not yet implemented");
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcCommandLine::GetSaveResult() const
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    return this->backendSaveResult->GetSaveResult();
  }

  void SgfcCommandLine::ThrowIfIsCommandLineValidReturnsFalse() const
  {
    if (! this->IsCommandLineValid())
      throw std::runtime_error("Interface protocol violation: IsCommandLineValid() returns false");
  }

  void SgfcCommandLine::ThrowIfIsSgfContentValidReturnsFalse() const
  {
    if (! this->IsSgfContentValid())
      throw std::runtime_error("Interface protocol violation: IsSgfContentValid() returns false");
  }
}
