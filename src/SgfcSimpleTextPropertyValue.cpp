// Project includes
#include "SgfcSimpleTextPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcSimpleTextPropertyValue::SgfcSimpleTextPropertyValue(const std::string& rawValue, const std::string& simpleTextValue)
    : SgfcSinglePropertyValue(true, rawValue)
    , simpleTextValue(simpleTextValue)
  {
  }

  SgfcSimpleTextPropertyValue::SgfcSimpleTextPropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(false, rawValue)
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
