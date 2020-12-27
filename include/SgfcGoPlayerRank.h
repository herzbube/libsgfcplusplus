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
#include "SgfcGoPlayerRankType.h"
#include "SgfcGoPlayerRatingType.h"
#include "SgfcTypedefs.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoPlayerRank struct is a simple type that can hold the
  /// decomposed values of an SgfcPropertyType::BR or SgfcPropertyType::WR
  /// property value.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  /// @ingroup game
  /// @ingroup go
  struct SGFCPLUSPLUS_EXPORT SgfcGoPlayerRank
  {
  public:
    /// @brief The rank. The default is 30.
    SgfcNumber Rank = 30;

    /// @brief The rank type. The default is SgfcGoPlayerRankType::Kyu.
    SgfcGoPlayerRankType RankType = SgfcGoPlayerRankType::Kyu;

    /// @brief The optional rating type that applies to the rank (e.g. the rank
    /// is established). The default is SgfcGoPlayerRatingType::Unspecified.
    SgfcGoPlayerRatingType RatingType = SgfcGoPlayerRatingType::Unspecified;

    /// @brief True if the SgfcGoPlayerRank object holds a valid Go player rank.
    /// False if the SgfcGoPlayerRank object holds an invalid Go player rank.
    /// The default is false.
    ///
    /// This is mainly used to indicate whether
    /// SgfcGoPlayerRank::FromPropertyValue() was successful in decomposing
    /// the SgfcPropertyType::BR or SgfcPropertyType::WR property value. A
    /// library client that manually creates an SgfcGoPlayerRank object can
    /// simply set this to true to assert a valid Go player rank.
    bool IsValid = false;

    /// @brief Decomposes the content of @a propertyValue into distinct rank,
    /// rank type and rating type values.
    ///
    /// See the SGF standard specification for the recommended structure of an
    /// SgfcPropertyType::BR or SgfcPropertyType::WR property value.
    ///
    /// In addition to what the SGF standard recommends, this also recognizes
    /// the notation "1p", "2p", etc. to express professional Dan ranks.
    ///
    /// @return SgfcGoPlayerRank An object with the decomposed rank, rank type
    /// and rating type values. The object's SgfcGoPlayerRank::IsValid member
    /// is true if decomposition was successful, otherwise it is false.
    static SgfcGoPlayerRank FromPropertyValue(const SgfcSimpleText& propertyValue);

    /// @brief Composes a property value for SgfcPropertyType::BR or
    /// SgfcPropertyType::WR from the rank, rank type and rating type values in
    /// @a goPlayerRank.
    ///
    /// See the SGF standard specification for the recommended structure of an
    /// SgfcPropertyType::BR or SgfcPropertyType::WR property value.
    ///
    /// In addition to what the SGF standard recommends, this also produces
    /// the notation "1p", "2p", etc. to express professional Dan ranks.
    ///
    /// @return SgfcSimpleText A property value for SgfcPropertyType::BR or
    /// SgfcPropertyType::WR that conforms to the SGF standard's recommended
    /// formatting, or SgfcConstants::NoneValueString if the
    /// SgfcGoPlayerRank::IsValid member of @a goPlayerRank is false.
    static SgfcSimpleText ToPropertyValue(SgfcGoPlayerRank goPlayerRank);

    /// @brief Returns true if the properties @e Rank, @e RankType and
    /// @e RatingType are the same for the current SgfcGoPlayerRank object and
    /// for @a other. Returns false if any of these properties are different.
    bool operator==(const SgfcGoPlayerRank& other) const;

    /// @brief Returns true if any of the properties @e Rank, @e RankType or
    /// @e RatingType are different for the current SgfcGoPlayerRank
    /// object and for @a other. Returns false if all properties are the same.
    bool operator!=(const SgfcGoPlayerRank& other) const;
  };
}
