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
#include "SgfcPlusPlusExport.h"

/// @file

namespace LibSgfcPlusPlus
{
  /// @brief An SgfcPropertyTraits value describes the traits of an
  /// ISgfcProperty object. The value is a combination of individual flags
  /// defined in the SgfcPropertyTrait enumeration.
  ///
  /// @ingroup public-api
  ///
  /// All bitwise operators have been overloaded to make the SgfcPropertyTraits
  /// typedef interoperate with the SgfcPropertyTrait enumeration as
  /// conveniently as possible. There are some limitations, though, because
  /// SgfcPropertyTraits is a typedef and not a true type (i.e. it's not a
  /// class or struct). For instance, the assignment operator cannot be
  /// overloaded so it's not possible to assign an SgfcPropertyTrait enumeration
  /// member directly to an SgfcPropertyTraits variable. Consequently, whenever
  /// SgfcPropertyTrait (the enum type) needs to be treated interchangeably with
  /// SgfcPropertyTraits (the typdef) a static_cast must be done. This works
  /// because SgfcPropertyTraits (the typedef) is used as the underlying type
  /// of SgfcPropertyTrait (the enum type).
  ///
  /// @verbatim
  /// SgfcPropertyTraits traits = static_cast<SgfcPropertyTraits>(SgfcPropertyTrait::Inheritable);
  /// @endverbatim
  ///
  /// @see SgfcConstants::PropertyTraitsNone
  /// @see SgfcConstants::PropertyTraitsAll
  ///
  /// @note Using an unsigned numerical type as the underlying type of this
  /// typedef is important to make the bitwise operators, specifically the
  /// shift left and shift right operators, unambiguous and safe to use.
  typedef unsigned long long SgfcPropertyTraits;

  /// @brief SgfcPropertyTrait enumerates the individual traits that an
  /// ISgfcProperty object can have. An ISgfcProperty object can have several
  /// traits, which is why the enumeration values are defined as flags that can
  /// be combined into a single SgfcPropertyTraits value.
  ///
  /// @ingroup public-api
  ///
  /// The SGF standard uses the term "property attribute" instead of
  /// "property trait".
  ///
  /// @see SgfcConstants::PropertyTraitsNone
  /// @see SgfcConstants::PropertyTraitsAll
  enum class SGFCPLUSPLUS_EXPORT SgfcPropertyTrait : SgfcPropertyTraits
  {
    /// @brief The property is an inheritable property. Inheritable properties
    /// are properties that affect not only the node contining these properties
    /// but also ALL subsequent child nodes, until a new setting is encountered
    /// or the setting is cleared.
    Inheritable = 1ULL,
  };

  /// @name Bitwise AND operators
  //@{
  /// @brief Bitwise AND operator, applying the right-hand-side trait operand
  /// @a rhs to the left-hand-side traits operand @a lhs.
  SgfcPropertyTraits operator&(SgfcPropertyTraits lhs, SgfcPropertyTrait rhs);
  /// @brief Bitwise AND operator, combining the left-hand-side trait operand
  /// @a lhs with the right-hand-side trait operand @ rhs.
  ///
  /// This operator does not make much sense - the result will always be
  /// SgfcConstants::PropertyTraitsNone
  SgfcPropertyTraits operator&(SgfcPropertyTrait lhs, SgfcPropertyTrait rhs);
  /// @brief Bitwise AND compound assignment operator, applying the
  /// right-hand-side trait operand @a rhs to the left-hand-side traits
  /// operand @a lhs.
  SgfcPropertyTraits& operator&=(SgfcPropertyTraits& lhs, SgfcPropertyTrait rhs);
  //@}

  /// @name Bitwise OR operators
  //@{
  /// @brief Bitwise OR operator, applying the right-hand-side trait operand
  /// @a rhs to the left-hand-side traits operand @a lhs.
  SgfcPropertyTraits operator|(SgfcPropertyTraits lhs, SgfcPropertyTrait rhs);
  /// @brief Bitwise OR operator, combining the left-hand-side trait operand
  /// @a lhs with the right-hand-side trait operand @ rhs.
  SgfcPropertyTraits operator|(SgfcPropertyTrait lhs, SgfcPropertyTrait rhs);
  /// @brief Bitwise OR compound assignment operator, applying the
  /// right-hand-side trait operand @a rhs to the left-hand-side traits
  /// operand @a lhs.
  SgfcPropertyTraits& operator|=(SgfcPropertyTraits& lhs, SgfcPropertyTrait rhs);
  //@}

  /// @name Bitwise XOR operators
  //@{
  /// @brief Bitwise XOR operator, applying the right-hand-side trait operand
  /// @a rhs to the left-hand-side traits operand @a lhs.
  SgfcPropertyTraits operator^(SgfcPropertyTraits lhs, SgfcPropertyTrait rhs);
  /// @brief Bitwise XOR operator, combining the left-hand-side trait operand
  /// @a lhs with the right-hand-side trait operand @ rhs.
  ///
  /// This operator does not make much sense - the result will always be
  /// SgfcConstants::PropertyTraitsNone
  SgfcPropertyTraits operator^(SgfcPropertyTrait lhs, SgfcPropertyTrait rhs);
  /// @brief Bitwise XOR compound assignment operator, applying the
  /// right-hand-side trait operand @a rhs to the left-hand-side traits
  /// operand @a lhs.
  SgfcPropertyTraits& operator^=(SgfcPropertyTraits& lhs, SgfcPropertyTrait rhs);
  //@}

  /// @name Bitwise shift operators
  //@{
  /// @brief Bitwise left shift operator, shifting the left-hand-side traits
  /// operand @a lhs by the number of bits in the right-hand-side operand
  /// @a numberOfBitsToShift.
  SgfcPropertyTraits operator<<(SgfcPropertyTrait lhs, unsigned short numberOfBitsToShift);

  /// @brief Bitwise right shift operator, shifting the left-hand-side traits
  /// operand @a lhs by the number of bits in the right-hand-side operand
  /// @a numberOfBitsToShift.
  SgfcPropertyTraits operator>>(SgfcPropertyTrait lhs, unsigned short numberOfBitsToShift);
  //@}

  /// @name Other bitwise operators
  //@{
  /// @brief Bitwise NOT operator, flipping all bits of the right-hand-side
  /// trait operand @a rhs.
  SgfcPropertyTraits operator~(SgfcPropertyTrait rhs);
  //@}
}
