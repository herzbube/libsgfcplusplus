// Project includes
#include "SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcSinglePropertyValue::SgfcSinglePropertyValue()
    : valueType(SgfcPropertyValueType::Unknown)
  {
  }

  SgfcSinglePropertyValue::SgfcSinglePropertyValue(const std::string& rawValue)
    : valueType(SgfcPropertyValueType::Unknown)
    , rawValue(rawValue)
  {
  }

  SgfcSinglePropertyValue::~SgfcSinglePropertyValue()
  {
  }

  bool SgfcSinglePropertyValue::IsComposedValue() const
  {
    return false;
  }

  const ISgfcSinglePropertyValue* SgfcSinglePropertyValue::ToSingleValue() const
  {
    return this;
  }

  const ISgfcComposedPropertyValue* SgfcSinglePropertyValue::ToComposedValue() const
  {
    return nullptr;
  }

  SgfcPropertyValueType SgfcSinglePropertyValue::GetValueType() const
  {
    return this->valueType;
  }

  std::string SgfcSinglePropertyValue::GetRawValue() const
  {
    return this->rawValue;
  }
}
