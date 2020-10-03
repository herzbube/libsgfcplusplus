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
