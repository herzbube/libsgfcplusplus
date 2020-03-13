// Project includes
#include "SgfcSimpleTextPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcSimpleTextPropertyValue::SgfcSimpleTextPropertyValue(const std::string& rawValue, const std::string& simpleTextValue)
    : SgfcSinglePropertyValue(rawValue, true)
    , simpleTextValue(simpleTextValue)
  {
  }

  SgfcSimpleTextPropertyValue::~SgfcSimpleTextPropertyValue()
  {
  }

  SgfcPropertyValueType SgfcSimpleTextPropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::SimpleText;
  }

  std::string SgfcSimpleTextPropertyValue::GetSimpleTextValue() const
  {
    ThrowIfHasNotTypedValue();
    return this->simpleTextValue;
  }

  const ISgfcSimpleTextPropertyValue* SgfcSimpleTextPropertyValue::ToSimpleTextValue() const
  {
    return this;
  }
}
