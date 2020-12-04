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
  /// @brief SgfcGoPlayerRatingType enumerates the rating types that can apply
  /// to a Go player's rank.
  ///
  /// @ingroup public-api
  /// @ingroup game
  /// @ingroup go
  ///
  /// @see ISgfcGameInfo
  enum class SGFCPLUSPLUS_EXPORT SgfcGoPlayerRatingType
  {
    /// @brief The rank of the Go player is uncertain.
    Uncertain,

    /// @brief The rank of the Go player is established.
    Established,

    /// @brief The rating type that applies to the Go player's rank is
    /// not specified, i.e. it is not known whether the rank is uncertain
    /// or established.
    Unspecified,
  };
}
