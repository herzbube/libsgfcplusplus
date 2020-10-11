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
#include "../../include/SgfcColor.h"
#include "../../include/SgfcDouble.h"
#include "../../include/SgfcTypedefs.h"

// C++ Standard Library includes
#include <string>
#include <utility>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcValueConverter class converts raw string values into value
  /// types defined by the SGF standard, and vice versa.
  ///
  /// @ingroup internals
  /// @ingroup parsing
  class SgfcValueConverter
  {
  public:
    /// @brief Initializes a newly constructed SgfcValueConverter object.
    SgfcValueConverter();
    
    /// @brief Destroys and cleans up the SgfcValueConverter object.
    virtual ~SgfcValueConverter();

    /// @brief Attempts to convert the specified string value @a stringValue
    /// into an SgfcNumber value. The number is formed by the first sequence of
    /// digit characters encountered in @a stringValue. Whitespace at the
    /// beginning is ignored. Plus and minus characters indicate the number's
    /// sign. The first non-digit, non-sign, non-whitespace character and
    /// all characters beyond are ignored.
    ///
    /// Conversion succeeds if at least one usable digit character is found.
    /// Conversion fails if no usable digit characters are found.
    ///
    /// Example: A floating point number is read up to the decimal point.
    ///
    /// @retval true if conversion succeeds. @a outNumberValue in this case
    ///         holds the converted value. The value of
    ///         @a outTypeConversionErrorMessage is undefined.
    /// @retval false if conversion fails. @a outTypeConversionErrorMessage
    ///         in this case holds an error message with a human readable
    ///         description why the conversion failed. The value of
    ///         @a outNumberValue is undefined.
    bool TryConvertStringToNumberValue(
      const std::string& stringValue,
      SgfcNumber& outNumberValue,
      std::string& outTypeConversionErrorMessage) const;

    /// @brief Converts the specified SgfcNumber @a numberValue into a string
    /// value and returns that string value.
    std::string ConvertNumberValueToString(SgfcNumber numberValue) const;

    /// @brief Attempts to convert the specified string value @a stringValue
    /// into an SgfcReal value. The number is formed by the first sequence of
    /// digit and decimal point (".") characters encountered in @a stringValue.
    /// Whitespace at the beginning is ignored. Plus and minus characters
    /// indicate the number's sign. The first non-digit, non-decimal point,
    /// non-sign, non-whitespace character and all characters beyond are
    /// ignored. The only exception is the scientific notation which is also
    /// recognized.
    ///
    /// Conversion succeeds if at least one usable digit character is found.
    /// Conversion fails if no usable digit characters are found.
    ///
    /// @retval true if conversion succeeds. @a outRealValue in this case
    ///         holds the converted value. The value of
    ///         @a outTypeConversionErrorMessage is undefined.
    /// @retval false if conversion fails. @a outTypeConversionErrorMessage
    ///         in this case holds an error message with a human readable
    ///         description why the conversion failed. The value of
    ///         @a outRealValue is undefined.
    bool TryConvertStringToRealValue(
      const std::string& stringValue,
      SgfcReal& outRealValue,
      std::string& outTypeConversionErrorMessage) const;

    /// @brief Converts the specified SgfcReal @a realValue into a string
    /// value and returns that string value.
    std::string ConvertRealValueToString(SgfcReal realValue) const;

    /// @brief Attempts to convert the specified string value @a stringValue
    /// into an SgfcDouble value.
    ///
    /// @retval true if conversion succeeds. @a outDoubleValue in this case
    ///         holds the converted value. The value of
    ///         @a outTypeConversionErrorMessage is undefined.
    /// @retval false if conversion fails. @a outTypeConversionErrorMessage
    ///         in this case holds an error message with a human readable
    ///         description why the conversion failed. The value of
    ///         @a outDoubleValue is undefined.
    bool TryConvertStringToDoubleValue(
      const std::string& stringValue,
      SgfcDouble& outDoubleValue,
      std::string& outTypeConversionErrorMessage) const;

    /// @brief Converts the specified SgfcDouble @a doubleValue into a string
    /// value and returns that string value.
    std::string ConvertDoubleValueToString(SgfcDouble doubleValue) const;

    /// @brief Attempts to convert the specified string value @a stringValue
    /// into an SgfcColor value.
    ///
    /// @retval true if conversion succeeds. @a outColorValue in this case
    ///         holds the converted value. The value of
    ///         @a outTypeConversionErrorMessage is undefined.
    /// @retval false if conversion fails. @a outTypeConversionErrorMessage
    ///         in this case holds an error message with a human readable
    ///         description why the conversion failed. The value of
    ///         @a outColorValue is undefined.
    bool TryConvertStringToColorValue(
      const std::string& stringValue,
      SgfcColor& outColorValue,
      std::string& outTypeConversionErrorMessage) const;

    /// @brief Converts the specified SgfcColor @a colorValue into a string
    /// value and returns that string value.
    std::string ConvertColorValueToString(SgfcColor colorValue) const;
  };
}
