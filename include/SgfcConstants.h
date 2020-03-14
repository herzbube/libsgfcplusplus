#pragma once

// Project includes
#include "SgfcBoardSize.h"
#include "SgfcGameType.h"
#include "SgfcPropertyType.h"
#include "SgfcTypedefs.h"

// C++ Standard Library includes
#include <map>
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcConstants class is a container class for constants.
  class SgfcConstants
  {
  public:
    /// @name libsgfc++ constants
    //@{
    static const std::string LibraryName;
    //@}

    /// @name String constants defined by the SGF standard
    //@{
    static const std::string NoneString;
    static const std::string DoubleNormalString;
    static const std::string DoubleEmphasizedString;
    static const std::string ColorBlackString;
    static const std::string ColorWhiteString;
    static const std::map<std::string, SgfcPropertyType> PropertyNameToPropertyTypeMap;
    static const std::map<SgfcPropertyType, std::string> PropertyTypeToPropertyNameMap;
    static const std::map<SgfcNumber, SgfcGameType> GameTypeAsNumberToGameTypeMap;
    static const std::map<SgfcGameType, SgfcNumber> GameTypeToGameTypeAsNumberMap;
    //@}

    /// @name Other constants for values defined by the SGF standard
    //@{
    /// @brief The default game type if the SgfcPropertyType::GM property exists
    /// but has no value.
    ///
    /// The SGF standard defines this to be SgfcGameType::Go.
    static const SgfcGameType DefaultGameType;

    /// @brief The minimum board size that is allowed for SgfcPropertyType::SZ.
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
    /// @brief A number value denoting "no game type".
    ///
    /// ISgfcGame::GetGameTypeAsNumber() returns this value, for instance, if
    /// the SgfcPropertyType::GM property is not present in a game's root ndoe,
    /// or if the game has no root node.
    static const SgfcNumber GameTypeNone;

    /// @brief A board size value denoting "no board size".
    ///
    /// ISgfcGame::GetBoardSize() returns this value, for instance, if the
    /// SgfcPropertyType::SZ property is not present in a game's root ndoe,
    /// or if the game has no root node.
    static const SgfcBoardSize BoardSizeNone;
    //@}
  };
}
