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

    /// @brief Returns the number of handicap stones. The default value is
    /// SgfcConstants::HandicapStonesNone.
    ///
    /// @see SgfcPropertyType::HA
    virtual SgfcNumber GetNumberOfHandicapStones() const = 0;
    /// @brief Sets the number of handicap stones.
    ///
    /// @see SgfcPropertyType::HA
    virtual void SetNumberOfHandicapStones(SgfcNumber numberOfHandicapStones) = 0;

    /// @brief Returns the komi. The default value is SgfcConstants::KomiNone.
    ///
    /// @see SgfcPropertyType::KM
    virtual SgfcReal GetKomi() const = 0;
    /// @brief Sets the komi.
    ///
    /// @see SgfcPropertyType::KM
    virtual void SetKomi(SgfcReal komi) = 0;

    /// @brief Returns the Go ruleset used for the game. The default value is
    /// an SgfcGoRuleset object which has the @e IsValid property set to false.
    ///
    /// The returned SgfcGoRuleset also has the @e IsValid property set to
    /// false if there is a problem with decomposing the raw property value.
    /// See SgfcGoRuleset::FromPropertyValue() for details. An indicator that
    /// this happened is if GetRulesName() returns a value that is not equal to
    /// SgfcConstants::NoneValueString.
    ///
    /// Invoking the base class method SetRulesName() also changes the
    /// information returned by this method.
    ///
    /// @see SgfcPropertyType::RU
    virtual SgfcGoRuleset GetGoRuleset() const = 0;
    /// @brief Sets the Go ruleset used for the game.
    ///
    /// Invoking this setter also changes the information returned by
    /// GetRulesName().
    ///
    /// @see SgfcPropertyType::RU
    virtual void SetGoRuleset(SgfcGoRuleset goRuleset) = 0;

    /// @brief Returns the rank of the black player. The default value is
    /// an SgfcGoPlayerRank object which has the @e IsValid property set to
    /// false.
    ///
    /// The returned SgfcGoPlayerRank also has the @e IsValid property set to
    /// false if there is a problem with decomposing the raw property value.
    /// See SgfcGoPlayerRank::FromPropertyValue() for details. An indicator that
    /// this happened is if GetBlackPlayerRank() returns a value that is not
    /// equal to SgfcConstants::NoneValueString.
    ///
    /// Invoking the base class method SetBlackPlayerRank() also changes the
    /// information returned by this method.
    ///
    /// @see SgfcPropertyType::BR
    virtual SgfcGoPlayerRank GetGoBlackPlayerRank() const = 0;
    /// @brief Sets the rank of the black player.
    ///
    /// Invoking this setter also changes the information returned by
    /// GetBlackPlayerRank().
    ///
    /// @see SgfcPropertyType::BR
    virtual void SetGoBlackPlayerRank(SgfcGoPlayerRank goBlackPlayerRank) = 0;

    /// @brief Returns the rank of the white player. The default value is
    /// an SgfcGoPlayerRank object which has the @e IsValid property set to
    /// false.
    ///
    /// The returned SgfcGoPlayerRank also has the @e IsValid property set to
    /// false if there is a problem with decomposing the raw property value.
    /// See SgfcGoPlayerRank::FromPropertyValue() for details. An indicator that
    /// this happened is if GetWhitePlayerRank() returns a value that is not
    /// equal to SgfcConstants::NoneValueString.
    ///
    /// Invoking the base class method SetWhitePlayerRank() also changes the
    /// information returned by this method.
    ///
    /// @see SgfcPropertyType::WR
    virtual SgfcGoPlayerRank GetGoWhitePlayerRank() const = 0;
    /// @brief Sets the rank of the white player.
    ///
    /// Invoking this setter also changes the information returned by
    /// GetWhitePlayerRank().
    ///
    /// @see SgfcPropertyType::WR
    virtual void SetGoWhitePlayerRank(SgfcGoPlayerRank goWhitePlayerRank) = 0;
  };
}
