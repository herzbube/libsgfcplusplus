// Project includes
#include "SgfcGoStonePropertyValue.h"
#include "../../../game/go/SgfcGoPoint.h"
#include "../../../game/go/SgfcGoStone.h"

namespace LibSgfcPlusPlus
{
  SgfcGoStonePropertyValue::SgfcGoStonePropertyValue(const std::string& rawValue, SgfcColor color)
    : SgfcStonePropertyValue(rawValue)
    , goStone(new SgfcGoStone(color, std::shared_ptr<ISgfcGoPoint>(new SgfcGoPoint(rawValue))))
  {
  }

  SgfcGoStonePropertyValue::~SgfcGoStonePropertyValue()
  {
  }

  const ISgfcGoStonePropertyValue* SgfcGoStonePropertyValue::ToGoStoneValue() const
  {
    return this;
  }

  std::shared_ptr<ISgfcGoStone> SgfcGoStonePropertyValue::GetGoStone() const
  {
    return this->goStone;
  }
}
