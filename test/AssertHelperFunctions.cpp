// -----------------------------------------------------------------------------
// Copyright 2024 Patrick Näf (herzbube@herzbube.ch)
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
#include "AssertHelperFunctions.h"

// Library includes
#include <ISgfcComposedPropertyValue.h>
#include <ISgfcGoGameInfo.h>
#include <ISgfcNumberPropertyValue.h>
#include <ISgfcProperty.h>
#include <ISgfcPropertyFactory.h>
#include <ISgfcPropertyValueFactory.h>
#include <ISgfcSimpleTextPropertyValue.h>
#include <SgfcConstants.h>
#include <SgfcPlusPlusFactory.h>
#include <SgfcUtility.h>

// Unit test library includes
#include <catch2/catch_test_macros.hpp>

namespace LibSgfcPlusPlus
{
  void AssertGameInfoHasDefaultValues(std::shared_ptr<ISgfcGameInfo> gameInfo)
  {
    REQUIRE( gameInfo->GetGameType() == SgfcConstants::DefaultGameType );
    REQUIRE( gameInfo->GetGameTypeAsNumber() == SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType) );
    REQUIRE( gameInfo->GetBoardSize() == SgfcBoardSize::GetDefaultBoardSize(SgfcConstants::DefaultGameType) );

    REQUIRE( gameInfo->GetRecorderName() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetSourceName() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetAnnotationAuthor() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetCopyrightInformation() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetGameName() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetGameInformation() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetGameDates().size() == 0 );
    REQUIRE( gameInfo->GetRawGameDates() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetRulesName() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetGameResult() == SgfcGameResult() );
    REQUIRE( gameInfo->GetRawGameResult() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetTimeLimitInSeconds() == 0.0 );
    REQUIRE( gameInfo->GetOvertimeInformation() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetOpeningInformation() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetBlackPlayerName() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetBlackPlayerRank() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetBlackPlayerTeamName() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetWhitePlayerName() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetWhitePlayerRank() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetWhitePlayerTeamName() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetGameLocation() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetEventName() == SgfcConstants::NoneValueString );
    REQUIRE( gameInfo->GetRoundInformation() == SgfcRoundInformation() );
    REQUIRE( gameInfo->GetRawRoundInformation() == SgfcConstants::NoneValueString );
  }

  void AssertGoGameInfoHasDefaultValues(std::shared_ptr<ISgfcGameInfo> gameInfo)
  {
    AssertGameInfoHasDefaultValues(gameInfo);

    auto goGameInfo = gameInfo->ToGoGameInfo();
    REQUIRE( goGameInfo != nullptr );
    REQUIRE( goGameInfo->GetNumberOfHandicapStones() == SgfcConstants::HandicapStonesNone );
    REQUIRE( goGameInfo->GetKomi() == SgfcConstants::KomiNone );
    REQUIRE( goGameInfo->GetGoRuleset() == SgfcGoRuleset() );
    REQUIRE( goGameInfo->GetGoBlackPlayerRank() == SgfcGoPlayerRank() );
    REQUIRE( goGameInfo->GetGoWhitePlayerRank() == SgfcGoPlayerRank() );
  }

  void AssertGameInfoHasRootPropertyValues(std::shared_ptr<ISgfcGameInfo> gameInfo, SgfcGameType gameType, SgfcNumber gameTypeAsNumber, SgfcBoardSize boardSize)
  {
    REQUIRE( gameInfo->GetGameType() == gameType );
    REQUIRE( gameInfo->GetGameTypeAsNumber() == gameTypeAsNumber );
    REQUIRE( gameInfo->GetBoardSize() == boardSize );

    auto goGameInfo = gameInfo->ToGoGameInfo();
    if (gameType == SgfcGameType::Go)
      REQUIRE( goGameInfo != nullptr );
    else
      REQUIRE( goGameInfo == nullptr );
  }

  void AssertPropertiesContainRootPropertyValues(std::vector<std::shared_ptr<ISgfcProperty>>& properties, SgfcNumber gameTypeAsNumber, SgfcBoardSize boardSize)
  {
    bool didFindGameTypeProperty = false;
    bool didFindBoardSizeProperty = false;

    for (auto property : properties)
    {
      switch (property->GetPropertyType())
      {
        case SgfcPropertyType::GM:
        {
          didFindGameTypeProperty = true;
          auto propertyValues = property->GetPropertyValues();
          REQUIRE( propertyValues.size() == 1 );
          auto propertyValue = propertyValues.front()->ToSingleValue();
          REQUIRE( propertyValue != nullptr );
          auto numberPropertyValue = propertyValue->ToNumberValue();
          REQUIRE( numberPropertyValue != nullptr );
          REQUIRE( numberPropertyValue->GetNumberValue() == gameTypeAsNumber );
          break;
        }
        case SgfcPropertyType::SZ:
        {
          didFindBoardSizeProperty = true;
          auto propertyValues = property->GetPropertyValues();
          REQUIRE( propertyValues.size() == 1 );
          if (boardSize.IsSquare())
          {
            auto propertyValue = propertyValues.front()->ToSingleValue();
            REQUIRE( propertyValue != nullptr );
            auto numberPropertyValue = propertyValue->ToNumberValue();
            REQUIRE( numberPropertyValue != nullptr );
            REQUIRE( numberPropertyValue->GetNumberValue() == boardSize.Columns );
          }
          else
          {
            auto propertyValue = propertyValues.front()->ToComposedValue();
            REQUIRE( propertyValue != nullptr );
            auto numberPropertyValue1 = propertyValue->GetValue1()->ToNumberValue();
            REQUIRE( numberPropertyValue1 != nullptr );
            REQUIRE( numberPropertyValue1->GetNumberValue() == boardSize.Columns );
            auto numberPropertyValue2 = propertyValue->GetValue2()->ToNumberValue();
            REQUIRE( numberPropertyValue2 != nullptr );
            REQUIRE( numberPropertyValue2->GetNumberValue() == boardSize.Rows );
          }
          break;
        }
        default:
        {
          break;
        }
      }
    }

    REQUIRE( didFindGameTypeProperty == true );
    REQUIRE( didFindBoardSizeProperty == true );
  }

  void AssertPropertiesContainsGameInfoPropertyValue(std::vector<std::shared_ptr<ISgfcProperty>>& properties, SgfcPropertyType propertyType, const SgfcSimpleText& simpleTextValue)
  {
    bool didFindGameInfoProperty = false;

    for (auto property : properties)
    {
      if (property->GetPropertyType() != propertyType)
        continue;

      didFindGameInfoProperty = true;

      auto propertyValues = property->GetPropertyValues();
      REQUIRE( propertyValues.size() == 1 );
      auto propertyValue = propertyValues.front()->ToSingleValue();
      REQUIRE( propertyValue != nullptr );
      auto simpleTextPropertyValue = propertyValue->ToSimpleTextValue();
      REQUIRE( simpleTextPropertyValue != nullptr );
      REQUIRE( simpleTextPropertyValue->GetSimpleTextValue() == simpleTextValue );

      break;
    }

    REQUIRE( didFindGameInfoProperty == true );
  }
}
