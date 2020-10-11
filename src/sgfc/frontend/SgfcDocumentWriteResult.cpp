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
#include "SgfcDocumentWriteResult.h"

// C++ Standard Library includes
#include <iostream>

namespace LibSgfcPlusPlus
{
  SgfcDocumentWriteResult::SgfcDocumentWriteResult()
  {
    this->exitCode = SgfcUtility::GetSgfcExitCodeFromMessageCollection(this->parseResult);
  }

  SgfcDocumentWriteResult::SgfcDocumentWriteResult(
    std::shared_ptr<ISgfcMessage> invalidCommandLineReason)
    : parseResult( { invalidCommandLineReason } )
  {
    this->exitCode = SgfcUtility::GetSgfcExitCodeFromMessageCollection(this->parseResult);
  }

  SgfcDocumentWriteResult::SgfcDocumentWriteResult(
    std::vector<std::shared_ptr<ISgfcMessage>> parseResult)
    : parseResult(parseResult)
  {
    this->exitCode = SgfcUtility::GetSgfcExitCodeFromMessageCollection(this->parseResult);
  }

  SgfcDocumentWriteResult::~SgfcDocumentWriteResult()
  {
  }

  SgfcExitCode SgfcDocumentWriteResult::GetExitCode() const
  {
    return this->exitCode;
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcDocumentWriteResult::GetParseResult() const
  {
    return this->parseResult;
  }

  void SgfcDocumentWriteResult::DebugPrintToConsole() const
  {
    std::cout << "Exit code = " << (int)GetExitCode() << std::endl;

    for (auto parseResultMessage : GetParseResult())
    {
      std::cout
        << "Message ID = "
        << parseResultMessage->GetMessageID()
        << ", type = "
        << (int)parseResultMessage->GetMessageType()
        << ", line = "
        << parseResultMessage->GetLineNumber()
        << ", column = "
        << parseResultMessage->GetColumnNumber()
        << ", is critical = "
        << parseResultMessage->IsCriticalMessage()
        << ", text = "
        << parseResultMessage->GetMessageText()
        << std::endl;
    }
  }
}
