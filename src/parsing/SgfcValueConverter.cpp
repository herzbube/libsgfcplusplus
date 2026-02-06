// -----------------------------------------------------------------------------
// Copyright 2020-2026 Patrick Näf (herzbube@herzbube.ch)
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
#include "../../include/SgfcConstants.h"
#include "SgfcValueConverter.h"
#include "../SgfcUtility.h"

// C++ Standard Library includes
#include <cctype> // for std::isspace
#include <charconv> // for std::from_chars
#include <limits>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <system_error> // for std::errc, std::make_error_code, std::error_code

namespace LibSgfcPlusPlus
{
  SgfcValueConverter::SgfcValueConverter()
  {
  }

  SgfcValueConverter::~SgfcValueConverter()
  {
  }

  bool SgfcValueConverter::TryConvertStringToNumberValue(
    const std::string& stringValue,
    SgfcNumber& outNumberValue,
    std::string& outTypeConversionErrorMessage) const
  {
    return TryConvertStringToNumericValue(stringValue,
                                          "an integer value",
                                          outNumberValue,
                                          outTypeConversionErrorMessage);
  }

  std::string SgfcValueConverter::ConvertNumberValueToString(SgfcNumber numberValue) const
  {
    std::stringstream numberValueAsString;
    // Make sure that decimal point is always a period (".") character and that
    // there are no thousands separators
    numberValueAsString.imbue(std::locale::classic());
    numberValueAsString << numberValue;
    return numberValueAsString.str();
  }

  bool SgfcValueConverter::TryConvertStringToRealValue(
    const std::string& stringValue,
    SgfcReal& outRealValue,
    std::string& outTypeConversionErrorMessage) const
  {
    // -------------------- Implementation note --------------------
    // We would like to use std::from_chars, just like we do in
    // TryConvertStringToNumberValue(). Unfortunately at the
    // time of writing clang's floating-type support for std::from_chars is
    // still limited to very new macOS and iOS deployment targets. When
    // considering to switch in the future, check out the values of macro
    // _LIBCPP_AVAILABILITY_FROM_CHARS_FLOATING_POINT when compiling on macOS.
    //
    // At the time of writing, the GitHub Actions Runner Image "macos-latest"
    // [1] uses a macOS version in which std::from_chars does not yet support
    // floating-type conversions. The difficult to understand error message is
    // "error: call to deleted function 'from_chars'". Even if this error
    // message goes away in the future because of an updated Runner Image,
    // the macro mentioned above still needs to be checked, to avoid forcing
    // clients to increase their iOS deployment target.
    // [1] https://github.com/actions/runner-images
    //
    // Once std::from_chars can be adopted for floating-type conversions, this
    // code snippet can be used to replace the current implementation:
    //
    //   return TryConvertStringToNumericValue(stringValue,
    //                                         "a floating point value",
    //                                         outRealValue,
    //                                         outTypeConversionErrorMessage);
    // -------------------- Implementation note --------------------

    try
    {
      outRealValue = stod(stringValue);
      return true;
    }
    catch (std::invalid_argument&)
    {
      outTypeConversionErrorMessage = "String value is not a floating point value";
      return false;
    }
    catch (std::out_of_range&)
    {
      outTypeConversionErrorMessage = "String value is a floating point value that is out of range";
      return false;
    }
  }

  std::string SgfcValueConverter::ConvertRealValueToString(SgfcReal realValue) const
  {
    std::stringstream realValueAsString;
    // Make sure that decimal point is always a period (".") character and that
    // there are no thousands separators
    realValueAsString.imbue(std::locale::classic());
    // Make sure the floating point value of the Score member is converted with
    // usefully high (although not maximum) precision, and that the conversion
    // does not use scientific notation
    realValueAsString << std::setprecision(std::numeric_limits<SgfcReal>::max_digits10 - 1);
    realValueAsString << realValue;
    return realValueAsString.str();
  }

  bool SgfcValueConverter::TryConvertStringToDoubleValue(
    const std::string& stringValue,
    SgfcDouble& outDoubleValue,
    std::string& outTypeConversionErrorMessage) const
  {
    if (stringValue == SgfcConstants::DoubleNormalString)
    {
      outDoubleValue = SgfcDouble::Normal;
      return true;
    }
    else if (stringValue == SgfcConstants::DoubleEmphasizedString)
    {
      outDoubleValue = SgfcDouble::Emphasized;
      return true;
    }
    else
    {
      std::stringstream message;
      message
        << "Raw property string value is not a Double value. The SGF standard allows these values: "
        << SgfcConstants::DoubleNormalString << " or " << SgfcConstants::DoubleEmphasizedString;

      outTypeConversionErrorMessage = message.str();
      return false;
    }
  }

  std::string SgfcValueConverter::ConvertDoubleValueToString(SgfcDouble doubleValue) const
  {
    if (doubleValue == SgfcDouble::Normal)
      return SgfcConstants::DoubleNormalString;
    else
      return SgfcConstants::DoubleEmphasizedString;
  }

  bool SgfcValueConverter::TryConvertStringToColorValue(
    const std::string& stringValue,
    SgfcColor& outColorValue,
    std::string& outTypeConversionErrorMessage) const
  {
    if (stringValue == SgfcConstants::ColorBlackString)
    {
      outColorValue = SgfcColor::Black;
      return true;
    }
    else if (stringValue == SgfcConstants::ColorWhiteString)
    {
      outColorValue = SgfcColor::White;
      return true;
    }
    else
    {
      std::stringstream message;
      message
        << "Raw property string value is not a Color value. The SGF standard allows these values: "
        << SgfcConstants::ColorBlackString << " or " << SgfcConstants::ColorWhiteString;

      outTypeConversionErrorMessage = message.str();
      return false;
    }
  }

  std::string SgfcValueConverter::ConvertColorValueToString(SgfcColor colorValue) const
  {
    if (colorValue == SgfcColor::Black)
      return SgfcConstants::ColorBlackString;
    else
      return SgfcConstants::ColorWhiteString;
  }

  template<SgfcNumberOrSgfcReal TNumeric>
  bool SgfcValueConverter::TryConvertStringToNumericValue(
    const std::string& stringValue,
    const std::string& numericTypeDescriptionForErrorMessage,
    TNumeric& outNumericValue,
    std::string& outTypeConversionErrorMessage) const
  {
    // Originally we used stol() and stod() for the conversion. Unlike those
    // functions, std::from_chars() does not ignore leading whitespace, so to
    // remain compatible we perform left-trimming first, in the same way that
    // the other functions do (i.e. using std::isspace).
    const char* stringValueBuffer = stringValue.c_str();
    const char* endOfBuffer = stringValueBuffer + stringValue.length();
    while (stringValueBuffer < endOfBuffer)
    {
      // std::isspace uses the current C locale. According to the documentation,
      // std::isspace requres an unsigned char as input even though the function
      // prototype uses the type "int" for its argument.
      // https://en.cppreference.com/w/cpp/string/byte/isspace.html
      auto characterToExamine = static_cast<unsigned char>(*stringValueBuffer);
      if (! std::isspace(characterToExamine))
        break;
      stringValueBuffer++;
    }

    // std::from_chars() only recognizes the minus sign, not the plus sign,
    // so we have to make sure that the plus sign is eliminated
    if (*stringValueBuffer == '+')
      stringValueBuffer++;

    // If it fails, std::from_chars does not modify outNumberValue
    auto from_chars_result = std::from_chars(stringValueBuffer, endOfBuffer, outNumericValue);
    if (from_chars_result.ec == std::errc{})
      return true;

    switch (from_chars_result.ec)
    {
      case std::errc::invalid_argument:
      {
        outTypeConversionErrorMessage = "String value is not " + numericTypeDescriptionForErrorMessage + ": " + stringValue;
        return false;
      }
      case std::errc::result_out_of_range:
      {
        outTypeConversionErrorMessage = "String value is " + numericTypeDescriptionForErrorMessage + " that is out of range";
        return false;
      }
      default:
      {
        auto error_code = std::make_error_code(from_chars_result.ec);
        std::stringstream message;
        message
          << "An unexpected error occurred converting the string value into " + numericTypeDescriptionForErrorMessage + ". Error code: "
          << error_code.value()
          << ", error message: "
          << error_code.message();
        outTypeConversionErrorMessage = message.str();
        return false;
      }
    }
  }
}
