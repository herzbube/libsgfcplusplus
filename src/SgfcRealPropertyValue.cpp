// Project includes
#include "SgfcRealPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcRealPropertyValue::SgfcRealPropertyValue(const std::string& rawValue, double realValue)
    : SgfcSinglePropertyValue(true, rawValue)
    , realValue(realValue)
  {
  }

  SgfcRealPropertyValue::SgfcRealPropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(false, rawValue)
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

  double SgfcRealPropertyValue::GetRealValue() const
  {
    ThrowIfHasNotTypedValue();
    return this->realValue;
  }

  const ISgfcRealPropertyValue* SgfcRealPropertyValue::ToRealValue() const
  {
    return this;
  }
}
