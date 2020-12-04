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
#include "SgfcTypedefs.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcRoundInformation struct is a simple type that can hold the
  /// decomposed values of an SgfcPropertyType::RO property value.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  /// @ingroup game
  ///
  /// The SGF standard specifies that the SgfcPropertyType::RO property value
  /// should be written as "xx (tt)", where "xx" is the number of the round and
  /// "(tt)" the type of the round. SgfcRoundInformation::FromPropertyValue()
  /// can be used to convert from such a composite property value to an
  /// SgfcRoundInformation object, which holds the decomposed values, while
  /// SgfcRoundInformation::ToPropertyValue() stitches the decomposed values in
  /// an SgfcRoundInformation object back together to a composite property
  /// value.
  struct SGFCPLUSPLUS_EXPORT SgfcRoundInformation
  {
  public:
    /// @brief The round number. The default is an empty string.
    ///
    /// Although the term "round number" implies a numeric value, the
    /// SgfcRoundInformation struct defines this to be a string, because the
    /// SGF standard also does not define a specific value type.
    SgfcSimpleText RoundNumber;

    /// @brief The round type. The default is an empty string.
    SgfcSimpleText RoundType;

    /// @brief True if the SgfcRoundInformation object holds valid round
    /// number and round type values. False if the round number and round type
    /// values are not valid. The default is false.
    ///
    /// This is mainly used to indicate whether
    /// SgfcRoundInformation::FromPropertyValue() was successful in decomposing
    /// the SgfcPropertyType::RO property value. A library client that manually
    /// creates an SgfcRoundInformation object can simply set this to true to
    /// assert valid values.
    bool IsValid = false;

    /// @brief Decomposes the content of @a propertyValue into distinct round
    /// number and round type values.
    ///
    /// The SGF standard specifies that @a propertyValue for
    /// SgfcPropertyType::RO should be written as "xx (tt)", where "xx" is the
    /// number of the round and "(tt)" the type of the round. This method
    /// attempts to parse @a propertyValue according to the SGF standard's
    /// suggested formatting.
    ///
    /// @return SgfcRoundInformation An object with the decomposed round number
    /// and round type values. The object's SgfcRoundInformation::IsValid member
    /// is true if decomposition was successful, otherwise it is false.
    static SgfcRoundInformation FromPropertyValue(const SgfcSimpleText& propertyValue);

    /// @brief Composes a property value for SgfcPropertyType::RO from the
    /// round number and round type values in @a roundInformation.
    ///
    /// The SGF standard specifies that a property value for
    /// SgfcPropertyType::RO should be written as "xx (tt)", where "xx" is the
    /// number of the round and "(tt)" the type of the round. This method
    /// composes a return value that conforms to the SGF standard's suggested
    /// formatting.
    ///
    /// @return SgfcSimpleText A property value for SgfcPropertyType::RO that
    /// conforms to the SGF standard's suggested formatting, or
    /// SgfcConstants::NoneValueString if the SgfcRoundInformation::IsValid
    /// member of @a roundInformation is false.
    static SgfcSimpleText ToPropertyValue(const SgfcRoundInformation& roundInformation);
  };
}
