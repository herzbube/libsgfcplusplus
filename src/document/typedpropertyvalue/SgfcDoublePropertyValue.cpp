// Project includes
#include "SgfcDoublePropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcDoublePropertyValue::SgfcDoublePropertyValue(const std::string& rawValue, SgfcDouble doubleValue)
    : SgfcSinglePropertyValue(rawValue)
    , doubleValue(doubleValue)
  {
  }

  SgfcDoublePropertyValue::SgfcDoublePropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage)
    : SgfcSinglePropertyValue(rawValue, typeConversionErrorMessage)
    , doubleValue(SgfcDouble::Normal)
  {
  }

  SgfcDoublePropertyValue::~SgfcDoublePropertyValue()
  {
  }

  SgfcPropertyValueType SgfcDoublePropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Double;
  }

  SgfcDouble SgfcDoublePropertyValue::GetDoubleValue() const
  {
    ThrowIfHasNotTypedValue();
    return this->doubleValue;
  }

  const ISgfcDoublePropertyValue* SgfcDoublePropertyValue::ToDoubleValue() const
  {
    return this;
  }
}
