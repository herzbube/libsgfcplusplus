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
#include "SgfcGoRulesetType.h"
#include "SgfcTypedefs.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoRuleset struct is a simple type that can hold the
  /// decomposed values of an SgfcPropertyType::RU property value.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  /// @ingroup game
  /// @ingroup go
  struct SGFCPLUSPLUS_EXPORT SgfcGoRuleset
  {
  public:
    /// @brief The ruleset type. The default is SgfcGoRulesetType::AGA.
    SgfcGoRulesetType GoRulesetType = SgfcGoRulesetType::AGA;

    /// @brief True if the SgfcGoRuleset object holds a valid Go ruleset.
    /// False if the SgfcGoRuleset object holds an invalid Go ruleset.
    /// The default is false.
    ///
    /// This is mainly used to indicate whether
    /// SgfcGoRuleset::FromPropertyValue() was successful in decomposing
    /// the SgfcPropertyType::RU property value. A library client that manually
    /// creates an SgfcGoRuleset object can simply set this to true to assert
    /// a valid Go ruleset.
    bool IsValid = false;

    /// @brief Decomposes the content of @a propertyValue into a distinct
    /// ruleset type value.
    ///
    /// See the SGF standard specification for the recommended structure of an
    /// SgfcPropertyType::RU property value.
    ///
    /// @return SgfcGoRuleset An object with the decomposed ruleset type value.
    /// The object's SgfcGoRuleset::IsValid member is true if decomposition was
    /// successful, otherwise it is false.
    static SgfcGoRuleset FromPropertyValue(const SgfcSimpleText& propertyValue);

    /// @brief Composes a property value for SgfcPropertyType::RU from the
    /// ruleset type value in @a goRuleset.
    ///
    /// See the SGF standard specification for the recommended structure of an
    /// SgfcPropertyType::RU property value.
    ///
    /// @return SgfcSimpleText A property value for SgfcPropertyType::RU that
    /// conforms to the SGF standard's mandatory formatting, or
    /// SgfcConstants::NoneValueString if the SgfcGoRuleset::IsValid member of
    /// @a goRuleset is false.
    static SgfcSimpleText ToPropertyValue(SgfcGoRuleset goRuleset);

    /// @brief Returns true if the properties @e GoRulesetType and @e IsValid
    /// are the same for the current SgfcGoRuleset object and for @a other.
    /// Returns false if any of these properties are different.
    bool operator==(const SgfcGoRuleset& other) const;

    /// @brief Returns true if any of the properties @e GoRulesetType or
    /// @e IsValid are different for the current SgfcGoRuleset object and for
    /// @a other. Returns false if all properties are the same.
    bool operator!=(const SgfcGoRuleset& other) const;
  };
}
