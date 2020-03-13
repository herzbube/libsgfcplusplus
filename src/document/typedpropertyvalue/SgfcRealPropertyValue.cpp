// Project includes
#include "SgfcRealPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcRealPropertyValue::SgfcRealPropertyValue(const std::string& rawValue, SgfcReal realValue)
    : SgfcSinglePropertyValue(rawValue, true)
    , realValue(realValue)
  {
  }

  SgfcRealPropertyValue::SgfcRealPropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage)
    : SgfcSinglePropertyValue(rawValue, typeConversionErrorMessage)
    , realValue(0.0)
  {
  }

  SgfcRealPropertyValue::~SgfcRealPropertyValue()
  {
  }

  SgfcPropertyValueType SgfcRealPropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Real;
  }

  SgfcReal SgfcRealPropertyValue::GetRealValue() const
  {
    ThrowIfHasNotTypedValue();
    return this->realValue;
  }

  const ISgfcRealPropertyValue* SgfcRealPropertyValue::ToRealValue() const
  {
    return this;
  }
}
