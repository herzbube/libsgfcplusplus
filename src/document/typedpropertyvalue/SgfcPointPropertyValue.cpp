// Project includes
#include "SgfcPointPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcPointPropertyValue::SgfcPointPropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(rawValue, true)
  {
  }

  SgfcPointPropertyValue::~SgfcPointPropertyValue()
  {
  }

  SgfcPropertyValueType SgfcPointPropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Point;
  }

  std::string SgfcPointPropertyValue::GetRawPointValue() const
  {
    return SgfcSinglePropertyValue::GetRawValue();
  }

  const ISgfcPointPropertyValue* SgfcPointPropertyValue::ToPointValue() const
  {
    return this;
  }

  const ISgfcGoPointPropertyValue* SgfcPointPropertyValue::ToGoPointValue() const
  {
    return nullptr;
  }
}
