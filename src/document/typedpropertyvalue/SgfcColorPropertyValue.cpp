// Project includes
#include "SgfcColorPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcColorPropertyValue::SgfcColorPropertyValue(const std::string& rawValue, SgfcColor colorValue)
    : SgfcSinglePropertyValue(true, rawValue)
    , colorValue(colorValue)
  {
  }

  SgfcColorPropertyValue::SgfcColorPropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(false, rawValue)
    , colorValue(SgfcColor::Black)
  {
  }

  SgfcColorPropertyValue::~SgfcColorPropertyValue()
  {
  }

  SgfcPropertyValueType SgfcColorPropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Color;
  }

  SgfcColor SgfcColorPropertyValue::GetColorValue() const
  {
    ThrowIfHasNotTypedValue();
    return this->colorValue;
  }

  const ISgfcColorPropertyValue* SgfcColorPropertyValue::ToColorValue() const
  {
    return this;
  }
}
