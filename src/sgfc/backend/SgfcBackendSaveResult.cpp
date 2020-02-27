// Project includes
#include "SgfcBackendSaveResult.h"

namespace LibSgfcPlusPlus
{
  SgfcBackendSaveResult::SgfcBackendSaveResult(
    std::vector<std::shared_ptr<ISgfcMessage>> saveResult)
    : saveResult(saveResult)
  {
  }

  SgfcBackendSaveResult::~SgfcBackendSaveResult()
  {
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcBackendSaveResult::GetSaveResult() const
  {
    return this->saveResult;
  }

}
