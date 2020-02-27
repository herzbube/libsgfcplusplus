// Project includes
#include "SgfcDoublePropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcDoublePropertyValue::SgfcDoublePropertyValue(const std::string& rawValue, SgfcDouble doubleValue)
    : SgfcSinglePropertyValue(true, rawValue)
    , doubleValue(doubleValue)
  {
  }

  SgfcDoublePropertyValue::SgfcDoublePropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(false, rawValue)
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
