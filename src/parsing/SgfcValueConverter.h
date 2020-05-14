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
  class SgfcValueConverter
  {
  public:
    /// @brief Initializes a newly constructed SgfcValueConverter object.
    SgfcValueConverter();
    
    /// @brief Destroys and cleans up the SgfcValueConverter object.
    virtual ~SgfcValueConverter();

    /// @brief Attempts to convert the specified string value @a stringValue
    /// into an SgfcNumber value.
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
    /// into an SgfcReal value.
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
