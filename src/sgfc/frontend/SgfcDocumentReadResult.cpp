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
#include "../../document/SgfcDocument.h"
#include "../../SgfcUtility.h"
#include "SgfcDocumentReadResult.h"

// C++ Standard Library includes
#include <iostream>

namespace LibSgfcPlusPlus
{
  SgfcDocumentReadResult::SgfcDocumentReadResult(
    std::shared_ptr<ISgfcMessage> invalidCommandLineReason)
    : parseResult( { invalidCommandLineReason } )
    , document(new SgfcDocument())
  {
    this->exitCode = SgfcUtility::GetSgfcExitCodeFromMessageCollection(this->parseResult);
    this->isSgfDataValid = SgfcUtility::GetIsSgfDataValidFromMessageCollection(this->parseResult);
  }

  SgfcDocumentReadResult::SgfcDocumentReadResult(
    std::vector<std::shared_ptr<ISgfcMessage>> parseResult,
    std::shared_ptr<ISgfcDocument> document)
    : parseResult(parseResult)
    , document(document)
  {
    this->exitCode = SgfcUtility::GetSgfcExitCodeFromMessageCollection(this->parseResult);
    this->isSgfDataValid = SgfcUtility::GetIsSgfDataValidFromMessageCollection(this->parseResult);
  }

  SgfcDocumentReadResult::~SgfcDocumentReadResult()
  {
  }

  SgfcExitCode SgfcDocumentReadResult::GetExitCode() const
  {
    return this->exitCode;
  }

  bool SgfcDocumentReadResult::IsSgfDataValid() const
  {
    return this->isSgfDataValid;
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcDocumentReadResult::GetParseResult() const
  {
    return this->parseResult;
  }

  std::shared_ptr<ISgfcDocument> SgfcDocumentReadResult::GetDocument() const
  {
    return this->document;
  }

  void SgfcDocumentReadResult::DebugPrintToConsole() const
  {
    std::cout << "Exit code = " << static_cast<int>(GetExitCode()) << std::endl;
    std::cout << "IsSgfDataValid = " << IsSgfDataValid() << std::endl;

    for (auto parseResultMessage : GetParseResult())
    {
      std::cout
        << "Message ID = "
        << static_cast<int>(parseResultMessage->GetMessageID())
        << ", type = "
        << static_cast<int>(parseResultMessage->GetMessageType())
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

    GetDocument()->DebugPrintToConsole();
  }
}
