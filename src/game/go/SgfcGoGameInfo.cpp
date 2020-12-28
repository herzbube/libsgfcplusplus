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
#include "../../../include/ISgfcNumberPropertyValue.h"
#include "../../../include/ISgfcPropertyFactory.h"
#include "../../../include/ISgfcPropertyValueFactory.h"
#include "../../../include/ISgfcRealPropertyValue.h"
#include "../../../include/SgfcConstants.h"
#include "../../../include/SgfcPlusPlusFactory.h"
#include "SgfcGoGameInfo.h"

namespace LibSgfcPlusPlus
{
  SgfcGoGameInfo::SgfcGoGameInfo()
    : numberOfHandicapStones(SgfcConstants::HandicapStonesNone)
    , komi(SgfcConstants::KomiNone)
  {
  }

  SgfcGoGameInfo::SgfcGoGameInfo(std::shared_ptr<ISgfcNode> rootNode)
    : SgfcGameInfo(rootNode)
    , numberOfHandicapStones(SgfcConstants::HandicapStonesNone)
    , komi(SgfcConstants::KomiNone)
  {
  }

  SgfcGoGameInfo::SgfcGoGameInfo(std::shared_ptr<ISgfcNode> rootNode, std::shared_ptr<ISgfcNode> gameInfoNode)
    : SgfcGameInfo(rootNode, gameInfoNode)
    , numberOfHandicapStones(SgfcConstants::HandicapStonesNone)
    , komi(SgfcConstants::KomiNone)
  {
    ReadFromGameInfoNode(gameInfoNode);
  }

  SgfcGoGameInfo::~SgfcGoGameInfo()
  {
  }

  SgfcNumber SgfcGoGameInfo::GetNumberOfHandicapStones() const
  {
    return this->numberOfHandicapStones;
  }

  void SgfcGoGameInfo::SetNumberOfHandicapStones(SgfcNumber numberOfHandicapStones)
  {
    this->numberOfHandicapStones = numberOfHandicapStones;
  }

  SgfcReal SgfcGoGameInfo::GetKomi() const
  {
    return this->komi;
  }

  void SgfcGoGameInfo::SetKomi(SgfcReal komi)
  {
    this->komi = komi;
  }

  SgfcGoRuleset SgfcGoGameInfo::GetGoRuleset() const
  {
    return this->goRuleset;
  }

  void SgfcGoGameInfo::SetGoRuleset(SgfcGoRuleset goRuleset)
  {
    this->goRuleset = goRuleset;
    SgfcGameInfo::SetRulesName(SgfcGoRuleset::ToPropertyValue(goRuleset));
  }

  void SgfcGoGameInfo::SetRulesName(const SgfcSimpleText& rulesName)
  {
    SgfcGameInfo::SetRulesName(rulesName);
    this->goRuleset = SgfcGoRuleset::FromPropertyValue(GetRulesName());
  }

  SgfcGoPlayerRank SgfcGoGameInfo::GetGoBlackPlayerRank() const
  {
    return this->goBlackPlayerRank;
  }

  void SgfcGoGameInfo::SetGoBlackPlayerRank(SgfcGoPlayerRank goBlackPlayerRank)
  {
    this->goBlackPlayerRank = goBlackPlayerRank;
    SgfcGameInfo::SetBlackPlayerRank(SgfcGoPlayerRank::ToPropertyValue(goBlackPlayerRank));
  }

  void SgfcGoGameInfo::SetBlackPlayerRank(const SgfcSimpleText& blackPlayerRank)
  {
    SgfcGameInfo::SetBlackPlayerRank(blackPlayerRank);
    this->goBlackPlayerRank = SgfcGoPlayerRank::FromPropertyValue(GetBlackPlayerRank());
  }

  SgfcGoPlayerRank SgfcGoGameInfo::GetGoWhitePlayerRank() const
  {
    return this->goWhitePlayerRank;
  }

  void SgfcGoGameInfo::SetGoWhitePlayerRank(SgfcGoPlayerRank goWhitePlayerRank)
  {
    this->goWhitePlayerRank = goWhitePlayerRank;
    SgfcGameInfo::SetWhitePlayerRank(SgfcGoPlayerRank::ToPropertyValue(goWhitePlayerRank));
  }

  void SgfcGoGameInfo::SetWhitePlayerRank(const SgfcSimpleText& whitePlayerRank)
  {
    SgfcGameInfo::SetWhitePlayerRank(whitePlayerRank);
    this->goBlackPlayerRank = SgfcGoPlayerRank::FromPropertyValue(GetWhitePlayerRank());
  }

  const ISgfcGoGameInfo* SgfcGoGameInfo::ToGoGameInfo() const
  {
    return this;
  }

  void SgfcGoGameInfo::WriteToGameInfoNode(std::shared_ptr<ISgfcNode> gameInfoNode)
  {
    SgfcGameInfo::WriteToGameInfoNode(gameInfoNode);

    auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
    auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();

    if (this->numberOfHandicapStones == SgfcConstants::HandicapStonesNone)
      RemovePropertyFromNodeIfExists(SgfcPropertyType::HA, gameInfoNode);
      else
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::HA, propertyValueFactory->CreateNumberPropertyValue(this->numberOfHandicapStones)));
    if (this->komi == SgfcConstants::KomiNone)
      RemovePropertyFromNodeIfExists(SgfcPropertyType::KM, gameInfoNode);
    else
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::KM, propertyValueFactory->CreateRealPropertyValue(this->komi)));
  }

  void SgfcGoGameInfo::ReadFromGameInfoNode(std::shared_ptr<ISgfcNode> gameInfoNode)
  {
    auto gameInfoProperties = gameInfoNode->GetProperties();

    for (auto gameInfoProperty : gameInfoProperties)
    {
      switch (gameInfoProperty->GetPropertyType())
      {
        case SgfcPropertyType::HA:
          this->numberOfHandicapStones = GetNumberPropertyValue(gameInfoProperty);
          if (this->numberOfHandicapStones == 0)
            this->numberOfHandicapStones = SgfcConstants::HandicapStonesNone;
          break;
        case SgfcPropertyType::KM:
          this->komi = GetRealPropertyValue(gameInfoProperty);
          if (this->komi == 0.0)
            this->komi = SgfcConstants::KomiNone;
          break;
        default:
          break;
      }
    }

    this->goRuleset = SgfcGoRuleset::FromPropertyValue(GetRulesName());
    this->goBlackPlayerRank = SgfcGoPlayerRank::FromPropertyValue(GetBlackPlayerRank());
    this->goWhitePlayerRank = SgfcGoPlayerRank::FromPropertyValue(GetWhitePlayerRank());
  }
}
