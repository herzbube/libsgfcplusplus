// Project includes
#include "../../SgfcUtility.h"
#include "SgfcDocumentWriteResult.h"

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
}
