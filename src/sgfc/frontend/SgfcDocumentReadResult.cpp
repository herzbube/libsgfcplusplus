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
    std::cout << "Exit code = " << (int)GetExitCode() << std::endl;
    std::cout << "IsSgfDataValid = " << IsSgfDataValid() << std::endl;

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

    GetDocument()->DebugPrintToConsole();
  }
}
