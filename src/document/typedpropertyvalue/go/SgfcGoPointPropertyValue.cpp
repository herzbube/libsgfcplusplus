// Project includes
#include "SgfcGoPointPropertyValue.h"
#include "../../../game/go/SgfcGoPoint.h"

namespace LibSgfcPlusPlus
{
  SgfcGoPointPropertyValue::SgfcGoPointPropertyValue(const std::string& rawValue)
    : SgfcPointPropertyValue(rawValue)
    , goPoint(new SgfcGoPoint(rawValue))
  {
  }

  SgfcGoPointPropertyValue::~SgfcGoPointPropertyValue()
  {
  }

  const ISgfcGoPointPropertyValue* SgfcGoPointPropertyValue::ToGoPointValue() const
  {
    return this;
  }

  std::shared_ptr<ISgfcGoPoint> SgfcGoPointPropertyValue::GetGoPoint() const
  {
    return this->goPoint;
  }
}
