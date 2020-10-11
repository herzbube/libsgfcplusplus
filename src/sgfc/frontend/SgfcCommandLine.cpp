// -----------------------------------------------------------------------------
// Copyright 2020 Patrick Näf (herzbube@herzbube.ch)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -----------------------------------------------------------------------------

// Project includes
#include "../../SgfcUtility.h"
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
    this->backendLoadResult = this->backendController->LoadSgfContent(sgfContent);

    SgfcExitCode sgfcExitCode = SgfcUtility::GetSgfcExitCodeFromMessageCollection(
      this->backendLoadResult->GetParseResult());

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

    this->backendSaveResult = this->backendController->SaveSgfContent(
      sgfContent,
      this->backendLoadResult->GetSgfDataWrapper());

    SgfcExitCode sgfcExitCode = SgfcUtility::GetSgfcExitCodeFromMessageCollection(
      this->backendSaveResult->GetSaveResult());

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
}
