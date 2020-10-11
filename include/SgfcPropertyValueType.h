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

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief SgfcPropertyValueType enumerates the basic SGF property value
  /// types.
  ///
  /// @ingroup public-api
  enum class SGFCPLUSPLUS_EXPORT SgfcPropertyValueType
  {
    /// @brief The property has no value.
    None,
    /// @brief The property value is a positive or negative integer.
    Number,
    /// @brief The property value is a positive or negative decimal value.
    Real,
    /// @brief The property value is a Double value. A Double value can have
    /// one of two integer values: Either 1 (which means "normal") or 2 (which
    /// means "emphasized").
    ///
    /// Example: GB[1] means "good for black" (normal). GB[2] means "very good
    /// for black" (emphasized).
    Double,
    /// @brief The property value is a Color value. A Color value can have one
    /// of two string values: Either "B" (which means "black") or "W" (which
    /// means "white").
    Color,
    /// @brief The property value is a simple string of arbitrary length. The
    /// only whitespace allowed for this string type are space characters.
    /// Specifically, a SimpleText property value does not contain line breaks.
    SimpleText,
    /// @brief The property value is a formatted string of arbitrary length.
    /// The only whitespace allowed for this string type are space characters
    /// and line break characters.
    ///
    /// SGF uses the description "formatted string" to refer to the fact that
    /// an SGF processing application should retain line breaks when it displays
    /// the property value.
    Text,
    /// @brief The property value describes a location on the game board. The
    /// value's string representation is game specific.
    Point,
    /// @brief The property value describes a move according to the game rules.
    /// The value's string representation is game specific.
    Move,
    /// @brief The property value describes a game piece and its location on the
    /// game board. The value's string representation is game specific.
    Stone,
    /// @brief The property value has an unknown type. This is used for
    /// non-empty values of any property not defined in the SGF standard.
    Unknown,
  };
}
