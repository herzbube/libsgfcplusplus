// Project includes
#include "SgfcTextPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcTextPropertyValue::SgfcTextPropertyValue(const std::string& rawValue, const std::string& textValue)
    : SgfcSinglePropertyValue(true, rawValue)
    , textValue(textValue)
  {
  }

  SgfcTextPropertyValue::SgfcTextPropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(false, rawValue)
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
