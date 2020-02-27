// Project includes
#include "SgfcStonePropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcStonePropertyValue::SgfcStonePropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(false, rawValue)
  {
  }

  SgfcStonePropertyValue::~SgfcStonePropertyValue()
  {
  }

  SgfcPropertyValueType SgfcStonePropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Stone;
  }

  std::string SgfcStonePropertyValue::GetRawStoneValue() const
  {
    return SgfcSinglePropertyValue::GetRawValue();
  }

  const ISgfcStonePropertyValue* SgfcStonePropertyValue::ToStoneValue() const
  {
    return this;
  }
}
