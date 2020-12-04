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
#include "ISgfcGameInfo.h"
#include "SgfcGoPlayerRank.h"
#include "SgfcGoRuleset.h"
#include "SgfcTypedefs.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcGoGameInfo interface is a specialization of ISgfcGameInfo
  /// that contains additional game information that is specific for the game
  /// of Go (e.g. komi).
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  /// @ingroup go
  class SGFCPLUSPLUS_EXPORT ISgfcGoGameInfo : virtual public ISgfcGameInfo
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGoGameInfo object.
    ISgfcGoGameInfo();

    /// @brief Destroys and cleans up the ISgfcGoGameInfo object.
    virtual ~ISgfcGoGameInfo();

    /// @brief Returns the number of handicap stones.
    ///
    /// @see SgfcPropertyType::HA
    virtual SgfcNumber GetNumberOfHandicapStones() const = 0;
    /// @brief Sets the number of handicap stones.
    ///
    /// @see SgfcPropertyType::HA
    virtual void SetNumberOfHandicapStones(SgfcNumber numberOfHandicapStones) = 0;

    /// @brief Returns the komi.
    ///
    /// @see SgfcPropertyType::KM
    virtual SgfcReal GetKomi() const = 0;
    /// @brief Sets the komi.
    ///
    /// @see SgfcPropertyType::KM
    virtual void SetKomi(SgfcReal komi) = 0;

    /// @brief Returns the Go ruleset used for the game.
    ///
    /// @see SgfcPropertyType::RU
    virtual SgfcGoRuleset GetGoRuleset() const = 0;
    /// @brief Sets the Go ruleset used for the game.
    ///
    /// @see SgfcPropertyType::RU
    virtual void SetRuleset(SgfcGoRuleset goRuleset) = 0;

    /// @brief Returns the rank of the black player.
    ///
    /// @see SgfcPropertyType::BR
    virtual SgfcGoPlayerRank GetGoBlackPlayerRank() const = 0;
    /// @brief Sets the rank of the black player.
    ///
    /// @see SgfcPropertyType::BR
    virtual void SetBlackPlayerRank(SgfcGoPlayerRank goBlackPlayerRank) = 0;

    /// @brief Returns the rank of the white player.
    ///
    /// @see SgfcPropertyType::WR
    virtual SgfcGoPlayerRank GetGoWhitePlayerRank() const = 0;
    /// @brief Sets the rank of the white player.
    ///
    /// @see SgfcPropertyType::WR
    virtual void SetWhitePlayerRank(SgfcGoPlayerRank goWhitePlayerRank) = 0;
  };
}
