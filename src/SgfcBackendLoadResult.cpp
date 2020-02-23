// Project includes
#include "SgfcBackendLoadResult.h"

namespace LibSgfcPlusPlus
{
  SgfcBackendLoadResult::SgfcBackendLoadResult(
    std::vector<std::shared_ptr<ISgfcMessage>> parseResult,
    std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper)
    : parseResult(parseResult)
    , sgfDataWrapper(sgfDataWrapper)
  {
  }

  SgfcBackendLoadResult::~SgfcBackendLoadResult()
  {
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcBackendLoadResult::GetParseResult() const
  {
    return this->parseResult;
  }

  std::shared_ptr<SgfcBackendDataWrapper> SgfcBackendLoadResult::GetSgfDataWrapper() const
  {
    return this->sgfDataWrapper;
  }
}
