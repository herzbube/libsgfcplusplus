// Project includes
#include "SgfcTextPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcTextPropertyValue::SgfcTextPropertyValue(const std::string& rawValue, const std::string& textValue)
    : SgfcSinglePropertyValue(rawValue, true)
    , textValue(textValue)
  {
  }

  SgfcTextPropertyValue::~SgfcTextPropertyValue()
  {
  }

  SgfcPropertyValueType SgfcTextPropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Text;
  }

  std::string SgfcTextPropertyValue::GetTextValue() const
  {
    ThrowIfHasNotTypedValue();
    return this->textValue;
  }

  const ISgfcTextPropertyValue* SgfcTextPropertyValue::ToTextValue() const
  {
    return this;
  }
}
