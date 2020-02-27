// Project includes
#include "../../SgfcUtility.h"
#include "SgfcDocumentReadResult.h"

namespace LibSgfcPlusPlus
{
  SgfcDocumentReadResult::SgfcDocumentReadResult()
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
}
