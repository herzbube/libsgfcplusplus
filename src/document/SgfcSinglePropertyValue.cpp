// Project includes
#include "SgfcSinglePropertyValue.h"

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcSinglePropertyValue::SgfcSinglePropertyValue(const std::string& rawValue)
    : hasTypedValue(true)
    , rawValue(rawValue)
  {
  }

  SgfcSinglePropertyValue::SgfcSinglePropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage)
    : hasTypedValue(false)
    , typeConversionErrorMessage(typeConversionErrorMessage)
    , rawValue(rawValue)
  {
  }

  SgfcSinglePropertyValue::~SgfcSinglePropertyValue()
  {
  }

  bool SgfcSinglePropertyValue::IsComposedValue() const
  {
    return false;
  }

  const ISgfcSinglePropertyValue* SgfcSinglePropertyValue::ToSingleValue() const
  {
    return this;
  }

  const ISgfcComposedPropertyValue* SgfcSinglePropertyValue::ToComposedValue() const
  {
    return nullptr;
  }

  bool SgfcSinglePropertyValue::HasTypedValue() const
  {
    return this->hasTypedValue;
  }

  std::string SgfcSinglePropertyValue::GetTypeConversionErrorMessage() const
  {
    return this->typeConversionErrorMessage;
  }

  std::string SgfcSinglePropertyValue::GetRawValue() const
  {
    return this->rawValue;
  }

  const ISgfcNumberPropertyValue* SgfcSinglePropertyValue::ToNumberValue() const
  {
    return nullptr;
  }

  const ISgfcRealPropertyValue* SgfcSinglePropertyValue::ToRealValue() const
  {
    return nullptr;
  }

  const ISgfcDoublePropertyValue* SgfcSinglePropertyValue::ToDoubleValue() const
  {
    return nullptr;
  }

  const ISgfcColorPropertyValue* SgfcSinglePropertyValue::ToColorValue() const
  {
    return nullptr;
  }

  const ISgfcSimpleTextPropertyValue* SgfcSinglePropertyValue::ToSimpleTextValue() const
  {
    return nullptr;
  }

  const ISgfcTextPropertyValue* SgfcSinglePropertyValue::ToTextValue() const
  {
    return nullptr;
  }

  const ISgfcPointPropertyValue* SgfcSinglePropertyValue::ToPointValue() const
  {
    return nullptr;
  }

  const ISgfcMovePropertyValue* SgfcSinglePropertyValue::ToMoveValue() const
  {
    return nullptr;
  }

  const ISgfcStonePropertyValue* SgfcSinglePropertyValue::ToStoneValue() const
  {
    return nullptr;
  }

  void SgfcSinglePropertyValue::ThrowIfHasNotTypedValue() const
  {
    if (! HasTypedValue())
    {
      std::stringstream message;
      message << "Property value object has no typed property value. Value type: " << static_cast<int>(GetValueType());
      throw std::logic_error(message.str());
    }
  }
}
