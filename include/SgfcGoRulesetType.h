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
  /// @brief SgfcGoRulesetType enumerates the ruleset types that are
  /// recognized by libsgfc++.
  ///
  /// @ingroup public-api
  /// @ingroup game
  /// @ingroup go
  ///
  /// @see ISgfcGameInfo
  enum class SGFCPLUSPLUS_EXPORT SgfcGoRulesetType
  {
    /// @brief The rules of the American Go Association (AGA).
    AGA,

    /// @brief The Ing rules.
    ///
    /// The SGF standard uses the description "The Ing rules of Goe". The word
    /// "Goe" is an alternative spelling of Go proposed by Ing Chang-Ki, the
    /// author of the ruleset, to differentiate it from the English verb
    /// "to go".
    Ing,

    /// @brief The Nihon-Kiin rule set.
    Japanese,

    /// @brief The New Zealand rules.
    NZ,
  };
}
