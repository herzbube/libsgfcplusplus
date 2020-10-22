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

namespace LibSgfcPlusPlus
{
  /// @brief SgfcGameType enumerates all game types defined by the SGF standard.
  /// The enum value SgfcGameType::Unknown is used for all non-standard game
  /// game types.
  ///
  /// @ingroup public-api
  ///
  /// @attention Do not rely on the numeric value underlying each enumeration
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
