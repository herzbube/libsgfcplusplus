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
#include "ISgfcPropertyValue.h"
#include "SgfcPropertyValueType.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcNumberPropertyValue;
  class ISgfcRealPropertyValue;
  class ISgfcDoublePropertyValue;
  class ISgfcColorPropertyValue;
  class ISgfcSimpleTextPropertyValue;
  class ISgfcTextPropertyValue;
  class ISgfcPointPropertyValue;
  class ISgfcMovePropertyValue;
  class ISgfcStonePropertyValue;

  /// @brief The ISgfcSinglePropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value is a single value of a
  /// basic value type. Some properties allow composed values - see
  /// ISgfcComposedPropertyValue for details.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  ///
  /// ISgfcSinglePropertyValue contains a number of convenience methods that
  /// help casting an ISgfcSinglePropertyValue object to a concrete type (e.g.
  /// ToNumberValue()). The return value of GetValueType() provides the
  /// information which casting method to use.
  ///
  /// ISgfcSinglePropertyValue is immutable, i.e. once the
  /// ISgfcSinglePropertyValue object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcSinglePropertyValue : public ISgfcPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcSinglePropertyValue object.
    ISgfcSinglePropertyValue();

    /// @brief Destroys and cleans up the ISgfcSinglePropertyValue object.
    virtual ~ISgfcSinglePropertyValue();

    /// @brief Returns the concrete type of the property value object. Depending
    /// on the value returned, a caller then knows which one of the convenience
    /// casting methods to use.
    ///
    /// GetValueType() returns the value type that is defined in the SGF
    /// standard. If the actual SGF content does not conform to the SGF
    /// standard, then libsgfc++ will be unable to parse the raw property string
    /// value. HasTypedValue() returns false to indicate such cases. See the
    /// documentation of HasTypedValue() for more details.
    ///
    /// GetValueType() returns SgfcPropertyValueType::Unknown for values of
    /// properties that are not defined in the SGF standard. In that case the
    /// ISgfcSinglePropertyValue object cannot be cast to any concrete type,
    /// i.e. all of the convenience casting methods will return @e nullptr.
    /// The interpretation of the raw property string value returned by
    /// GetRawValue() is left to the caller.
    ///
    /// @note GetValueType() never returns SgfcPropertyValueType::None.
    virtual SgfcPropertyValueType GetValueType() const = 0;

    /// @brief Returns true if the raw string value returned by GetRawValue()
    /// is available as a typed value. Otherwise returns false.
    ///
    /// "Available as a typed value" means that ISgfcSinglePropertyValue can be
    /// cast to a concrete type and that type can then be used to retrieve the
    /// typed value. Example: GetValueType() returns
    /// SgfcPropertyValueType::Number. ToNumberValue() can therefore be invoked
    /// to obtain an ISgfcSinglePropertyValue object, and
    /// ISgfcNumberPropertyValue::GetNumberValue() can then be invoked to
    /// retrieve the signed integer number that corresponds to the raw string
    /// value that GetRawValue() returns.
    ///
    /// When libsgfc++ parses SGF content it attempts to interpret the raw
    /// property string value according to the value type defined for the
    /// property in the SGF standard. If that interpretation fails
    /// GetValueType() will return the value type according to the SGF standard
    /// definition, but HasTypedValue() will return false.
    virtual bool HasTypedValue() const = 0;

    /// @brief Returns an error message that describes why the raw string value
    /// returned by GetRawValue() could not be converted to the typed value
    /// returned by GetValueType().
    ///
    /// Invoking this method makes sense only if GetValueType() returns a value
    /// other than SgfcPropertyValueType::Unknown, because only in this case
    /// does libsgfc++ attempt a conversion. In addition, HasTypedValue()
    /// obviously must return false to indicate that a type conversion error
    /// occurred.
    ///
    /// Returns an empty string if GetValueType() returns
    /// SgfcPropertyValueType::Unknown or if HasTypedValue() returns false.
    virtual std::string GetTypeConversionErrorMessage() const = 0;

    /// @brief Returns the property value as a raw string, i.e. as close as
    /// possible as it appears in the original SGF content.
    ///
    /// The following processing is applied to the original SGF content before
    /// it is made available from this getter as raw string:
    /// - The escape character ("\") is stripped from SimpleText and Text
    ///   values (unless it was escaped itself).
    /// - Values that are not SimpleText or Text are trimmed of leading and
    ///   trailing whitespace.
    /// - In SimpleText values, whitespace characters other than space are
    ///   converted to space. Exception: Escaped line breaks are removed
    ///   entirely.
    /// - In Text values, whitespace characters other than line breaks are
    ///   converted to space. In addition, escaped line breaks are removed
    ///   entirely.
    /// - In SimpleText and Text values, all unnecessary escape characters
    ///   are removed. E.g. escaping the "a" character is not necessary, so
    ///   "\a" appears as simply "a" in the raw string. Necessary escape
    ///   characters are preserved, though, and appear in the raw string
    ///   (e.g. "\\" or "\]").
    /// - In Move values, if the game type is Go and the board size is <= 19x19,
    ///   the value "tt" is converted to an empty string. This is in accord with
    ///   the SGF standard that defines an empty string and value "tt" both
    ///   to express a pass move, but in FF4 the "tt" representation is kept
    ///   only for compatibility with FF3.
    virtual std::string GetRawValue() const = 0;

    /// @brief Returns an ISgfcNumberPropertyValue object if GetValueType()
    /// returns SgfcPropertyValueType::Number. Returns @e nullptr otherwise.
    /// The caller is not the owner of the returned object.
    virtual const ISgfcNumberPropertyValue* ToNumberValue() const = 0;

    /// @brief Returns an ISgfcRealPropertyValue object if GetValueType()
    /// returns SgfcPropertyValueType::Real. Returns @e nullptr otherwise.
    /// The caller is not the owner of the returned object.
    virtual const ISgfcRealPropertyValue* ToRealValue() const = 0;

    /// @brief Returns an ISgfcDoublePropertyValue object if GetValueType()
    /// returns SgfcPropertyValueType::Double. Returns @e nullptr otherwise.
    /// The caller is not the owner of the returned object.
    virtual const ISgfcDoublePropertyValue* ToDoubleValue() const = 0;

    /// @brief Returns an ISgfcColorPropertyValue object if GetValueType()
    /// returns SgfcPropertyValueType::Color. Returns @e nullptr otherwise.
    /// The caller is not the owner of the returned object.
    virtual const ISgfcColorPropertyValue* ToColorValue() const = 0;

    /// @brief Returns an ISgfcSimpleTextPropertyValue object if GetValueType()
    /// returns SgfcPropertyValueType::SimpleText. Returns @e nullptr otherwise.
    /// The caller is not the owner of the returned object.
    virtual const ISgfcSimpleTextPropertyValue* ToSimpleTextValue() const = 0;

    /// @brief Returns an ISgfcTextPropertyValue object if GetValueType()
    /// returns SgfcPropertyValueType::Text. Returns @e nullptr otherwise.
    /// The caller is not the owner of the returned object.
    virtual const ISgfcTextPropertyValue* ToTextValue() const = 0;

    /// @brief Returns an ISgfcPointPropertyValue object if GetValueType()
    /// returns SgfcPropertyValueType::Point. Returns @e nullptr otherwise.
    /// The caller is not the owner of the returned object.
    virtual const ISgfcPointPropertyValue* ToPointValue() const = 0;

    /// @brief Returns an ISgfcMovePropertyValue object if GetValueType()
    /// returns SgfcPropertyValueType::Move. Returns @e nullptr otherwise.
    /// The caller is not the owner of the returned object.
    virtual const ISgfcMovePropertyValue* ToMoveValue() const = 0;

    /// @brief Returns an ISgfcStonePropertyValue object if GetValueType()
    /// returns SgfcPropertyValueType::Stone. Returns @e nullptr otherwise.
    /// The caller is not the owner of the returned object.
    virtual const ISgfcStonePropertyValue* ToStoneValue() const = 0;
  };
}
