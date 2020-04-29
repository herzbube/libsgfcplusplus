#pragma once

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief SgfcGameType enumerates all game types defined by the SGF standard.
  /// The enum value SgfcGameType::Unknown is used for all non-standard game
  /// game types.
  ///
  /// @important Do not rely on the numeric value underlying each enumeration
  /// member. Specifically, do not attempt to map the numeric value to the game
  /// type's representation in the SGF content.
  enum class SGFCPLUSPLUS_EXPORT SgfcGameType
  {
    Go,
    Othello,
    Chess,
    GomokuAndRenju,
    NineMensMorris,
    Backgammon,
    ChineseChess,
    Shogi,
    LinesOfAction,
    Ataxx,
    Hex,
    Jungle,
    Neutron,
    PhilosophersFootball,
    Quadrature,
    Trax,
    Tantrix,
    Amazons,
    Octi,
    Gess,
    Twixt,
    Zertz,
    Plateau,
    Yinsh,
    Punct,
    Gobblet,
    Hive,
    Exxit,
    Hnefatal,
    Kuba,
    Tripples,
    Chase,
    TumblingDown,
    Sahara,
    Byte,
    Focus,
    Dvonn,
    Tamsk,
    Gipf,
    Kropki,
    Unknown,
  };
}
