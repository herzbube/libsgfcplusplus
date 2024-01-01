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
#include "SgfcBoardSize.h"
#include "SgfcGameType.h"
#include "SgfcNodeTraits.h"
#include "SgfcPropertyCategory.h"
#include "SgfcPropertyTraits.h"
#include "SgfcPropertyType.h"
#include "SgfcTypedefs.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <map>
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcConstants class is a container class for constants.
  ///
  /// @ingroup public-api
  /// @ingroup library-support
  class SGFCPLUSPLUS_EXPORT SgfcConstants
  {
  public:
    SgfcConstants() = delete;
    ~SgfcConstants() = delete;

    /// @name libsgfc++ constants
    //@{
    /// @brief The library name.
    static const std::string LibraryName;
    /// @brief The library version.
    static const std::string LibraryVersion;
    /// @brief The SGFC version used by the library.
    static const std::string SgfcVersion;
    //@}

    /// @name ISgfcMessage related constants
    //@{
    /// @brief Indicates an invalid line number. This is used for messages
    /// that do not refer to a specific line number in a piece of SGF content.
    static const unsigned long InvalidLineNumber;
    /// @brief Indicates an invalid column number. This is used for messages
    /// that do not refer to a specific column number in a piece of SGF content.
    static const unsigned long InvalidColumnNumber;
    /// @brief A library error number (= errno value) indicating "no error".
    /// This is defined to be the value 0 (zero).
    static const int LibraryErrorNumberNoError;
    //@}

    /// @name String constants defined by the SGF standard
    //@{
    /// @brief The raw string value that corresponds to the None value as
    /// defined by the SGF standard.
    ///
    /// The SGF standard defines this to be an empty string.
    static const std::string NoneValueString;
    /// @brief The raw string value that corresponds to the Double value
    /// #SgfcDouble::Normal, as defined by the SGF standard.
    ///
    /// The SGF standard defines this to be the string "1".
    static const std::string DoubleNormalString;
    /// @brief The raw string value that corresponds to the Double value
    /// #SgfcDouble::Emphasized, as defined by the SGF standard.
    ///
    /// The SGF standard defines this to be the string "2".
    static const std::string DoubleEmphasizedString;
    /// @brief The raw string value that corresponds to the Color value
    /// #SgfcColor::Black, as defined by the SGF standard.
    ///
    /// The SGF standard defines this to be the string "B".
    static const std::string ColorBlackString;
    /// @brief The raw string value that corresponds to the Color value
    /// #SgfcColor::White, as defined by the SGF standard.
    ///
    /// The SGF standard defines this to be the string "W".
    static const std::string ColorWhiteString;
    /// @brief The raw string value that corresponds to a pass Move value for
    /// #SgfcGameType::Go, as defined by the SGF standard.
    ///
    /// The SGF standard defines this to be an empty string.
    static const std::string GoMovePassString;
    //@}

    /// @name String constants defined by the SGF standard for SgfcPropertyType::RU
    //@{
    /// @brief The SgfcPropertyType::RU property value defined by the SGF
    /// standard to denote SgfcGoRulesetType::AGA.
    static const SgfcSimpleText GoRulesetAGA;
    /// @brief The SgfcPropertyType::RU property value defined by the SGF
    /// standard to denote SgfcGoRulesetType::Ing.
    static const SgfcSimpleText GoRulesetIng;
    /// @brief The SgfcPropertyType::RU property value defined by the SGF
    /// standard to denote SgfcGoRulesetType::Japanese.
    static const SgfcSimpleText GoRulesetJapanese;
    /// @brief The SgfcPropertyType::RU property value defined by the SGF
    /// standard to denote SgfcGoRulesetType::NZ.
    static const SgfcSimpleText GoRulesetNZ;
    //@}

    /// @name Mappings between libsgfc++ values and SGF standard values, and vice versa
    //@{
    /// @brief Maps property names as defined by the SGF standard to values from
    /// the enumeration SgfcPropertyType.
    static const std::map<std::string, SgfcPropertyType> PropertyNameToPropertyTypeMap;
    /// @brief Maps values from the enumeration SgfcPropertyType to property
    /// names as defined by the SGF standard. SgfcPropertyType::Unknown does
    /// not appear in the map.
    static const std::map<SgfcPropertyType, std::string> PropertyTypeToPropertyNameMap;
    /// @brief Maps values from the enumeration SgfcPropertyType to values from
    /// the enumeration SgfcPropertyCategory.
    static const std::map<SgfcPropertyType, SgfcPropertyCategory> PropertyTypeToPropertyCategoryMap;
    /// @brief Maps values from the enumeration SgfcPropertyType to
    /// SgfcPropertyTraits values.
    static const std::map<SgfcPropertyType, SgfcPropertyTraits> PropertyTypeToPropertyTraitsMap;
    /// @brief Maps game type Number values as defined by the SGF standard to
    /// values from the enumeration SgfcGameType.
    static const std::map<SgfcNumber, SgfcGameType> GameTypeAsNumberToGameTypeMap;
    /// @brief Maps values from the enumeration SgfcGameType to Number values
    /// as defined by the SGF standard. SgfcGameType::Unknown does not appear
    /// in the map.
    static const std::map<SgfcGameType, SgfcNumber> GameTypeToGameTypeAsNumberMap;
    //@}

    /// @name Other constants for values defined by the SGF standard
    //@{
    /// @brief The default game type if the SgfcPropertyType::GM property does
    /// not exist.
    ///
    /// The SGF standard defines this to be SgfcGameType::Go.
    static const SgfcGameType DefaultGameType;

    /// @brief An SgfcNumber value that denotes a game type that is
    /// "not a number".
    ///
    /// ISgfcGame and ISgfcGameTypeProperty both provide a GetGameTypeAsNumber()
    /// method to obtain the raw SgfcNumber value of an SgfcPropertyType::GM
    /// property. If the raw SgfcNumber value cannot be determined because it
    /// has multiple property values, or a single property value that cannot be
    /// converted to an SgfcNumber value, then the GetGameTypeAsNumber() methods
    /// return this constant.
    ///
    /// The constant has an underlying numeric value, but one that is extremely
    /// unlikely to occur in real SGF content. Do not rely on the actual
    /// constant's numeric value.
    static const SgfcNumber GameTypeNaN;

    /// @brief The minimum board size that is required for SgfcPropertyType::SZ.
    ///
    /// The SGF standard defines this to be 1x1.
    static const SgfcBoardSize BoardSizeMinimum;

    /// @brief The maximum board size that is allowed for SgfcPropertyType::SZ
    /// if the game type is SgfcGameType::Go.
    ///
    /// The SGF standard defines this to be 52x52.
    static const SgfcBoardSize BoardSizeMaximumGo;

    /// @brief The default board size if the game type is SgfcGameType::Go.
    ///
    /// The SGF standard defines this to be 19x19.
    static const SgfcBoardSize BoardSizeDefaultGo;

    /// @brief The default board size if the game type is SgfcGameType::Chess.
    ///
    /// The SGF standard defines this to be 8x8.
    static const SgfcBoardSize BoardSizeDefaultChess;
    //@}

    /// @name Other constants
    //@{
    /// @brief A board size value denoting "no board size".
    ///
    /// ISgfcGame::GetBoardSize() returns this value, for instance, if the
    /// SgfcPropertyType::SZ property is not present in a game's root node,
    /// or if the game has no root node, and the game type is not one of the
    /// few game types with a known default board size.
    static const SgfcBoardSize BoardSizeNone;

    /// @brief A board size value denoting "invalid board size".
    ///
    /// A board size is invalid if it violates the constraints defined by the
    /// SGF standard:
    /// - All game types: If the board size is below the minimum size
    ///   #BoardSizeMinimum.
    /// - For SgfcGameType::Go: If the board size is above the maximum size
    ///   #BoardSizeMaximumGo.
    ///
    /// ISgfcGame::GetBoardSize() returns this value, for instance, if the
    /// SgfcPropertyType::SZ property is present in a game's root node but has
    /// an invalid size.
    static const SgfcBoardSize BoardSizeInvalid;

    /// @brief A Number value that denotes "no handicap stones" value for
    /// SgfcPropertyType::HA (a Go specific property).
    static const SgfcNumber HandicapStonesNone;

    /// @brief A Real value that denotes "no komi" value for
    /// SgfcPropertyType::KM (a Go specific property).
    static const SgfcReal KomiNone;

    /// @brief An SgfcNodeTraits value that denotes a node that has no traits.
    static const SgfcNodeTraits NodeTraitsNone;

    /// @brief An SgfcNodeTraits value that denotes a node that has all traits.
    /// It makes no sense for a node to actually have all traits, this is merely
    /// a convenience constant for working with flags.
    ///
    /// This constant is set up to have all bits set in the underlying primitive
    /// numeric type, so you should not rely on any particular numeric value.
    static const SgfcNodeTraits NodeTraitsAll;

    /// @brief An SgfcPropertyTraits value that denotes a property that has no
    /// traits.
    static const SgfcPropertyTraits PropertyTraitsNone;

    /// @brief An SgfcPropertyTraits value that denotes a property that has all
    /// traits. It makes no sense for a property to actually have all traits,
    /// this is merely a convenience constant for working with flags.
    ///
    /// This constant is set up to have all bits set in the underlying primitive
    /// numeric type, so you should not rely on any particular numeric value.
    static const SgfcPropertyTraits PropertyTraitsAll;
    //@}
  };
}
