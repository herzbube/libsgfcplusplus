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

// Project includes
#include "../../../include/SgfcConstants.h"
#include "../../../include/SgfcGoRuleset.h"

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcGoRuleset SgfcGoRuleset::FromPropertyValue(const SgfcSimpleText& propertyValue)
  {
    SgfcGoRuleset goRuleset;
    goRuleset.IsValid = true;

    if (propertyValue == SgfcConstants::GoRulesetAGA)
      goRuleset.GoRulesetType = SgfcGoRulesetType::AGA;
    else if (propertyValue == SgfcConstants::GoRulesetIng)
      goRuleset.GoRulesetType = SgfcGoRulesetType::Ing;
    else if (propertyValue == SgfcConstants::GoRulesetJapanese)
      goRuleset.GoRulesetType = SgfcGoRulesetType::Japanese;
    else if (propertyValue == SgfcConstants::GoRulesetNZ)
      goRuleset.GoRulesetType = SgfcGoRulesetType::NZ;
    else
      goRuleset.IsValid = false;

    return goRuleset;
  }

  SgfcSimpleText SgfcGoRuleset::ToPropertyValue(SgfcGoRuleset goRuleset)
  {
    if (! goRuleset.IsValid)
      return SgfcConstants::NoneValueString;

    switch (goRuleset.GoRulesetType)
    {
      case SgfcGoRulesetType::AGA:
        return SgfcConstants::GoRulesetAGA;
      case SgfcGoRulesetType::Ing:
        return SgfcConstants::GoRulesetIng;
      case SgfcGoRulesetType::Japanese:
        return SgfcConstants::GoRulesetJapanese;
      case SgfcGoRulesetType::NZ:
        return SgfcConstants::GoRulesetNZ;
      default:
      {
        std::stringstream message;
        message << "SgfcGoRuleset::ToPropertyValue: Unexpected go ruleset type " << static_cast<int>(goRuleset.GoRulesetType);
        throw std::logic_error(message.str());
      }
    }
  }
}
