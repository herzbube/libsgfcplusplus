// Project includes
#include "SgfcPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcPropertyValue::SgfcPropertyValue()
    : isCompositeValue(false)
    , valueType1(SgfcPropertyValueType::Unknown)
    , valueType2(SgfcPropertyValueType::None)
  {
  }

  SgfcPropertyValue::SgfcPropertyValue(const std::string& rawValue)
    : isCompositeValue(false)
    , valueType1(SgfcPropertyValueType::Unknown)
    , rawValue1(rawValue)
    , valueType2(SgfcPropertyValueType::None)
  {
  }

  SgfcPropertyValue::SgfcPropertyValue(const std::string& rawValue1, const std::string& rawValue2)
    : isCompositeValue(true)
    , valueType1(SgfcPropertyValueType::Unknown)
    , rawValue1(rawValue1)
    , valueType2(SgfcPropertyValueType::Unknown)
    , rawValue2(rawValue2)
  {
  }

  SgfcPropertyValue::~SgfcPropertyValue()
  {
  }

  bool SgfcPropertyValue::IsCompositeValue() const
  {
    return this->isCompositeValue;
  }

  SgfcPropertyValueType SgfcPropertyValue::GetValueType1() const
  {
    return this->valueType1;
  }

  std::string SgfcPropertyValue::GetRawValue1() const
  {
    return this->rawValue1;
  }

  SgfcPropertyValueType SgfcPropertyValue::GetValueType2() const
  {
    return this->valueType2;
  }

  std::string SgfcPropertyValue::GetRawValue2() const
  {
    return this->rawValue2;
  }
}
