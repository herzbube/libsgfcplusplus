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
  /// @brief SgfcGoPlayerRankType enumerates the rank types in the traditional
  /// Go ranking system.
  ///
  /// @ingroup public-api
  /// @ingroup game
  /// @ingroup go
  ///
  /// @see ISgfcGameInfo
  enum class SGFCPLUSPLUS_EXPORT SgfcGoPlayerRankType
  {
    /// @brief The rank type is Kyu. A Kyu rank is a student rank. The generally
    /// accepted Kyu ranks range from 30 (lowest) to 1 (highest). The notation
    /// is "30k", "29k", etc..
    Kyu,

    /// @brief The rank type is amateur Dan. An amateur Dan rank is a master
    /// rank. The generally accepted amateur Dan ranks range from 1 (lowest) to
    /// 7 (highest). The notation is "1d", "2d", etc..
    AmateurDan,

    /// @brief The rank type is professional Dan. A professional Dan rank is a
    /// master rank. The generally accepted professional Dan ranks range from
    /// 1 (lowest) to 9 (highest). The notation is "1p", "2p", etc..
    ProfessionalDan,
  };
}
