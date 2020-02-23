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

  SgfcPropertyValueType SgfcSinglePropertyValue::GetValueType() const
  {
    return this->valueType;
  }

  std::string SgfcSinglePropertyValue::GetRawValue() const
  {
    return this->rawValue;
  }
}
