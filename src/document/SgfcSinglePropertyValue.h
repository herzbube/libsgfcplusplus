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

#pragma once

// Project includes
#include "../../include/ISgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcSinglePropertyValue class provides an implementation of the
  /// ISgfcSinglePropertyValue interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcSinglePropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcSinglePropertyValue object
    /// that has the raw property string value @a rawValue. The value type is
    /// SgfcPropertyValueType::Unknown, HasTypedValue() returns false and
    /// GetTypeConversionErrorMessage() returns an empty string.
    SgfcSinglePropertyValue(const std::string& rawValue);

    /// @brief Initializes a newly constructed SgfcSinglePropertyValue object
    /// that has the raw property string value @a rawValue and the value type
    /// @a valueType. HasTypedValue() returns true and
    /// GetTypeConversionErrorMessage() returns an empty string.
    ///
    /// Subclasses are expected to use this constructor.
    SgfcSinglePropertyValue(const std::string& rawValue, SgfcPropertyValueType valueType);

    /// @brief Initializes a newly constructed SgfcSinglePropertyValue object
    /// that has the raw property string value @a rawValue and the value type
    /// @a valueType. HasTypedValue() returns false and
    /// GetTypeConversionErrorMessage() returns @a typeConversionErrorMessage.
    SgfcSinglePropertyValue(const std::string& rawValue, SgfcPropertyValueType valueType, const std::string& typeConversionErrorMessage);

    /// @brief Destroys and cleans up the SgfcSinglePropertyValue object.
    virtual ~SgfcSinglePropertyValue();

    virtual bool IsComposedValue() const override;
    virtual const ISgfcSinglePropertyValue* ToSingleValue() const override;

    virtual SgfcPropertyValueType GetValueType() const override;
    virtual bool HasTypedValue() const override;
    virtual std::string GetTypeConversionErrorMessage() const override;

    virtual std::string GetRawValue() const override;

    virtual const ISgfcNumberPropertyValue* ToNumberValue() const override;
    virtual const ISgfcRealPropertyValue* ToRealValue() const override;
    virtual const ISgfcDoublePropertyValue* ToDoubleValue() const override;
    virtual const ISgfcColorPropertyValue* ToColorValue() const override;
    virtual const ISgfcSimpleTextPropertyValue* ToSimpleTextValue() const override;
    virtual const ISgfcTextPropertyValue* ToTextValue() const override;
    virtual const ISgfcPointPropertyValue* ToPointValue() const override;
    virtual const ISgfcMovePropertyValue* ToMoveValue() const override;
    virtual const ISgfcStonePropertyValue* ToStoneValue() const override;

  private:
    SgfcPropertyValueType valueType;
    bool hasTypedValue;
    std::string typeConversionErrorMessage;
    std::string rawValue;
  };
}
