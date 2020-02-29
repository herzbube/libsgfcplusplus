// Project includes
#include "SgfcMovePropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcMovePropertyValue::SgfcMovePropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(rawValue)
  {
  }

  SgfcMovePropertyValue::~SgfcMovePropertyValue()
  {
  }

  SgfcPropertyValueType SgfcMovePropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Move;
  }

  std::string SgfcMovePropertyValue::GetRawMoveValue() const
  {
    return SgfcSinglePropertyValue::GetRawValue();
  }

  const ISgfcMovePropertyValue* SgfcMovePropertyValue::ToMoveValue() const
  {
    return this;
  }
}
