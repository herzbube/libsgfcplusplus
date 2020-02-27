// Project includes
#include "SgfcNumberPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcNumberPropertyValue::SgfcNumberPropertyValue(const std::string& rawValue, long numberValue)
    : SgfcSinglePropertyValue(true, rawValue)
    , numberValue(numberValue)
  {
  }

  SgfcNumberPropertyValue::SgfcNumberPropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(false, rawValue)
    , numberValue(0)
  {
  }

  SgfcNumberPropertyValue::~SgfcNumberPropertyValue()
  {
  }

  SgfcPropertyValueType SgfcNumberPropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Number;
  }

  long SgfcNumberPropertyValue::GetNumberValue() const
  {
    ThrowIfHasNotTypedValue();
    return this->numberValue;
  }

  const ISgfcNumberPropertyValue* SgfcNumberPropertyValue::ToNumberValue() const
  {
    return this;
  }
}
