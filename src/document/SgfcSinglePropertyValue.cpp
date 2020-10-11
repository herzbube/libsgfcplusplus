// -----------------------------------------------------------------------------
// Copyright 2020 Patrick Näf (herzbube@herzbube.ch)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -----------------------------------------------------------------------------

// Project includes
#include "SgfcSinglePropertyValue.h"

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcSinglePropertyValue::SgfcSinglePropertyValue(const std::string& rawValue, bool hasTypedValue)
    : hasTypedValue(hasTypedValue)
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
