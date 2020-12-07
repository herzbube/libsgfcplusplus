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
#include "../../include/ISgfcComposedPropertyValue.h"
#include "../../include/ISgfcProperty.h"
#include "../../include/ISgfcNumberPropertyValue.h"
#include "../../include/ISgfcPropertyFactory.h"
#include "../../include/ISgfcPropertyValueFactory.h"
#include "../../include/ISgfcRealPropertyValue.h"
#include "../../include/ISgfcSimpleTextPropertyValue.h"
#include "../../include/ISgfcTextPropertyValue.h"
#include "../../include/SgfcConstants.h"
#include "../../include/SgfcPlusPlusFactory.h"
#include "../SgfcUtility.h"
#include "SgfcGameInfo.h"
#include "SgfcGameUtility.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcGameInfo::SgfcGameInfo()
    : gameType(SgfcGameType::Unknown)
    , gameTypeAsNumber(0)
    , timeLimitInSeconds(0)
  {
  }

  SgfcGameInfo::SgfcGameInfo(std::shared_ptr<ISgfcNode> rootNode, std::shared_ptr<ISgfcNode> gameInfoNode)
    : SgfcGameInfo()
  {
    if (rootNode == nullptr)
      throw std::invalid_argument("SgfcGameInfo constructor failed: Root node is nullptr");
    if (gameInfoNode == nullptr)
      throw std::invalid_argument("SgfcGameInfo constructor failed: Game info node is nullptr");

    ReadFromRootNode(rootNode);
    ReadFromGameInfoNode(gameInfoNode);
  }

  SgfcGameInfo::~SgfcGameInfo()
  {
  }

  SgfcGameType SgfcGameInfo::GetGameType() const
  {
    return this->gameType;
  }

  SgfcNumber SgfcGameInfo::GetGameTypeAsNumber()
  {
    return this->gameTypeAsNumber;
  }

  SgfcBoardSize SgfcGameInfo::GetBoardSize() const
  {
    return this->boardSize;
  }

  SgfcSimpleText SgfcGameInfo::GetRecorderName() const
  {
    return this->recorderName;
  }

  void SgfcGameInfo::SetRecorderName(const SgfcSimpleText& recorderName)
  {
    this->recorderName = recorderName;
  }

  SgfcSimpleText SgfcGameInfo::GetSourceName() const
  {
    return this->sourceName;
  }

  void SgfcGameInfo::SetSourceName(const SgfcSimpleText& sourceName)
  {
    this->sourceName = sourceName;
  }

  SgfcSimpleText SgfcGameInfo::GetAnnotationAuthor() const
  {
    return this->annotationAuthor;
  }

  void SgfcGameInfo::SetAnnotationAuthor(const SgfcSimpleText& annotationAuthor)
  {
    this->annotationAuthor = annotationAuthor;
  }

  SgfcSimpleText SgfcGameInfo::GetCopyrightInformation() const
  {
    return this->copyrightInformation;
  }

  void SgfcGameInfo::SetCopyrightInformation(const SgfcSimpleText& copyrightInformation)
  {
    this->copyrightInformation = copyrightInformation;
  }

  SgfcSimpleText SgfcGameInfo::GetGameName() const
  {
    return this->gameName;
  }

  void SgfcGameInfo::SetGameName(const SgfcSimpleText& gameName)
  {
    this->gameName = gameName;
  }

  SgfcText SgfcGameInfo::GetGameInformation() const
  {
    return this->gameInformation;
  }

  void SgfcGameInfo::SetGameInformation(const SgfcText& gameInformation)
  {
    this->gameInformation = gameInformation;
  }

  std::vector<SgfcDate> SgfcGameInfo::GetGameDates() const
  {
    return this->gameDates;
  }

  void SgfcGameInfo::SetGameDates(const std::vector<SgfcDate>& gameDates)
  {
    this->gameDates = gameDates;
    this->rawGameDates = SgfcDate::ToPropertyValue(gameDates);
  }

  SgfcSimpleText SgfcGameInfo::GetRawGameDates() const
  {
    return this->rawGameDates;
  }

  SgfcSimpleText SgfcGameInfo::GetRulesName() const
  {
    return this->rulesName;
  }

  void SgfcGameInfo::SetRulesName(const SgfcSimpleText& rulesName)
  {
    this->rulesName = rulesName;
  }

  SgfcGameResult SgfcGameInfo::GetGameResult() const
  {
    return this->gameResult;
  }

  void SgfcGameInfo::SetGameResult(SgfcGameResult gameResult)
  {
    this->gameResult = gameResult;
    this->rawGameResult = SgfcGameResult::ToPropertyValue(gameResult);
  }

  SgfcSimpleText SgfcGameInfo::GetRawGameResult() const
  {
    return this->rawGameResult;
  }

  SgfcReal SgfcGameInfo::GetTimeLimitInSeconds() const
  {
    return this->timeLimitInSeconds;
  }

  void SgfcGameInfo::SetTimeLimitInSeconds(SgfcReal timeLimitInSeconds)
  {
    this->timeLimitInSeconds = timeLimitInSeconds;
  }

  SgfcSimpleText SgfcGameInfo::GetOvertimeInformation() const
  {
    return this->overtimeInformation;
  }

  void SgfcGameInfo::SetOvertimeInformation(const SgfcSimpleText& overtimeInformation)
  {
    this->overtimeInformation = overtimeInformation;
  }

  SgfcSimpleText SgfcGameInfo::GetOpeningInformation() const
  {
    return this->openingInformation;
  }

  void SgfcGameInfo::SetOpeningInformation(const SgfcSimpleText& openingInformation)
  {
    this->openingInformation = openingInformation;
  }

  SgfcSimpleText SgfcGameInfo::GetBlackPlayerName() const
  {
    return this->blackPlayerName;
  }

  void SgfcGameInfo::SetBlackPlayerName(const SgfcSimpleText& blackPlayerName)
  {
    this->blackPlayerName = blackPlayerName;
  }

  SgfcSimpleText SgfcGameInfo::GetBlackPlayerRank() const
  {
    return this->blackPlayerRank;
  }

  void SgfcGameInfo::SetBlackPlayerRank(const SgfcSimpleText& blackPlayerRank)
  {
    this->blackPlayerRank = blackPlayerRank;
  }

  SgfcSimpleText SgfcGameInfo::GetBlackPlayerTeamName() const
  {
    return this->blackPlayerTeamName;
  }

  void SgfcGameInfo::SetBlackPlayerTeamName(const SgfcSimpleText& blackPlayerTeamName)
  {
    this->blackPlayerTeamName = blackPlayerTeamName;
  }

  SgfcSimpleText SgfcGameInfo::GetWhitePlayerName() const
  {
    return this->whitePlayerName;
  }

  void SgfcGameInfo::SetWhitePlayerName(const SgfcSimpleText& whitePlayerName)
  {
    this->whitePlayerName = whitePlayerName;
  }

  SgfcSimpleText SgfcGameInfo::GetWhitePlayerRank() const
  {
    return this->whitePlayerRank;
  }

  void SgfcGameInfo::SetWhitePlayerRank(const SgfcSimpleText& whitePlayerRank)
  {
    this->whitePlayerRank = whitePlayerRank;
  }

  SgfcSimpleText SgfcGameInfo::GetWhitePlayerTeamName() const
  {
    return this->whitePlayerTeamName;
  }

  void SgfcGameInfo::SetWhitePlayerTeamName(const SgfcSimpleText& whitePlayerTeamName)
  {
    this->whitePlayerTeamName = whitePlayerTeamName;
  }

  SgfcSimpleText SgfcGameInfo::GetGameLocation() const
  {
    return this->gameLocation;
  }

  void SgfcGameInfo::SetGameLocation(const SgfcSimpleText& gameLocation)
  {
    this->gameLocation = gameLocation;
  }

  SgfcSimpleText SgfcGameInfo::GetEventName() const
  {
    return this->eventName;
  }

  void SgfcGameInfo::SetEventName(const SgfcSimpleText& eventName)
  {
    this->eventName = eventName;
  }

  SgfcRoundInformation SgfcGameInfo::GetRoundInformation() const
  {
    return this->roundInformation;
  }

  void SgfcGameInfo::SetRoundInformation(const SgfcRoundInformation& roundInformation)
  {
    this->roundInformation = roundInformation;
    this->rawRoundInformation = SgfcRoundInformation::ToPropertyValue(roundInformation);
  }

  SgfcSimpleText SgfcGameInfo::GetRawRoundInformation() const
  {
    return this->rawRoundInformation;
  }

  const ISgfcGoGameInfo* SgfcGameInfo::ToGoGameInfo() const
  {
    return nullptr;
  }

  void SgfcGameInfo::WriteToRootNode(std::shared_ptr<ISgfcNode> rootNode)
  {
    if (rootNode == nullptr)
      throw std::invalid_argument("SgfcGameInfo::WriteToRootNode failed: Game info node is nullptr");

    auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
    auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();

    rootNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::GM, propertyValueFactory->CreateNumberPropertyValue(this->gameTypeAsNumber)));

    std::shared_ptr<ISgfcPropertyValue> propertyValueSZ;
    if (this->boardSize.IsSquare())
      propertyValueSZ = propertyValueFactory->CreateNumberPropertyValue(this->boardSize.Columns);
    else
      propertyValueSZ = propertyValueFactory->CreateComposedNumberAndNumberPropertyValue(this->boardSize.Columns, this->boardSize.Rows);
    rootNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::SZ, propertyValueSZ));
  }

  void SgfcGameInfo::WriteToGameInfoNode(std::shared_ptr<ISgfcNode> gameInfoNode)
  {    
    if (gameInfoNode == nullptr)
      throw std::invalid_argument("SgfcGameInfo::WriteToGameInfoNode failed: Game info node is nullptr");

    auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
    auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();

    if (this->recorderName != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::US, propertyValueFactory->CreateSimpleTextPropertyValue(this->recorderName)));
    if (this->sourceName != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::SO, propertyValueFactory->CreateSimpleTextPropertyValue(this->sourceName)));
    if (this->annotationAuthor != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::AN, propertyValueFactory->CreateSimpleTextPropertyValue(this->annotationAuthor)));
    if (this->copyrightInformation != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::CP, propertyValueFactory->CreateSimpleTextPropertyValue(this->copyrightInformation)));
    
    if (this->gameName != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::GN, propertyValueFactory->CreateSimpleTextPropertyValue(this->gameName)));
    if (this->gameInformation != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::GC, propertyValueFactory->CreateTextPropertyValue(this->gameInformation)));
    if (this->rawGameDates != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::DT, propertyValueFactory->CreateSimpleTextPropertyValue(this->rawGameDates)));
    if (this->rulesName != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::RU, propertyValueFactory->CreateSimpleTextPropertyValue(this->rulesName)));
    if (this->rawGameResult != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::RE, propertyValueFactory->CreateSimpleTextPropertyValue(this->rawGameResult)));

    if (this->timeLimitInSeconds != 0.0)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::TM, propertyValueFactory->CreateRealPropertyValue(this->timeLimitInSeconds)));
    if (this->overtimeInformation != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::OT, propertyValueFactory->CreateSimpleTextPropertyValue(this->overtimeInformation)));
    if (this->openingInformation != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::ON, propertyValueFactory->CreateSimpleTextPropertyValue(this->openingInformation)));
    
    if (this->blackPlayerName != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::PB, propertyValueFactory->CreateSimpleTextPropertyValue(this->blackPlayerName)));
    if (this->blackPlayerRank != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::BR, propertyValueFactory->CreateSimpleTextPropertyValue(this->blackPlayerRank)));
    if (this->blackPlayerTeamName != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::BT, propertyValueFactory->CreateSimpleTextPropertyValue(this->blackPlayerTeamName)));
    if (this->whitePlayerName != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::PW, propertyValueFactory->CreateSimpleTextPropertyValue(this->whitePlayerName)));
    if (this->whitePlayerRank != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::WR, propertyValueFactory->CreateSimpleTextPropertyValue(this->whitePlayerRank)));
    if (this->whitePlayerTeamName != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::WT, propertyValueFactory->CreateSimpleTextPropertyValue(this->whitePlayerTeamName)));

    if (this->gameLocation != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::PC, propertyValueFactory->CreateSimpleTextPropertyValue(this->gameLocation)));
    if (this->eventName != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::EV, propertyValueFactory->CreateSimpleTextPropertyValue(this->eventName)));
    if (this->rawRoundInformation != SgfcConstants::NoneValueString)
      gameInfoNode->SetProperty(propertyFactory->CreateProperty(SgfcPropertyType::RO, propertyValueFactory->CreateSimpleTextPropertyValue(this->rawRoundInformation)));
  }

  void SgfcGameInfo::ReadFromRootNode(std::shared_ptr<ISgfcNode> rootNode)
  {
    auto propertyGM = rootNode->GetProperty(SgfcPropertyType::GM);
    if (propertyGM == nullptr)
      this->gameTypeAsNumber = SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType);
    else
      this->gameTypeAsNumber = SgfcGameUtility::GetGameTypeAsNumber(propertyGM->GetPropertyValues());
    this->gameType = SgfcUtility::MapNumberValueToGameType(this->gameTypeAsNumber);

    auto propertySZ = rootNode->GetProperty(SgfcPropertyType::SZ);
    if (propertySZ == nullptr)
      this->boardSize = SgfcUtility::GetDefaultBoardSize(this->gameType);
    else
      this->boardSize = SgfcGameUtility::GetBoardSize(propertySZ->GetPropertyValues(), this->gameType);
  }

  void SgfcGameInfo::ReadFromGameInfoNode(std::shared_ptr<ISgfcNode> gameInfoNode)
  {
    auto gameInfoProperties = gameInfoNode->GetProperties();

    for (auto gameInfoProperty : gameInfoProperties)
    {
      switch (gameInfoProperty->GetPropertyType())
      {
        case SgfcPropertyType::US:
          this->recorderName = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::SO:
          this->sourceName = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::AN:
          this->annotationAuthor = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::CP:
          this->copyrightInformation = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::GN:
          this->gameName = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::GC:
          this->gameInformation = GetTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::DT:
          this->rawGameDates = GetSimpleTextPropertyValue(gameInfoProperty);
          this->gameDates = SgfcDate::FromPropertyValue(this->rawGameDates);
          break;
        case SgfcPropertyType::RU:
          this->rulesName = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::RE:
          this->rawGameResult = GetSimpleTextPropertyValue(gameInfoProperty);
          this->gameResult = SgfcGameResult::FromPropertyValue(this->rawGameResult);
          break;
        case SgfcPropertyType::TM:
          this->timeLimitInSeconds = GetRealPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::OT:
          this->overtimeInformation = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::ON:
          this->openingInformation = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::PB:
          this->blackPlayerName = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::BR:
          this->blackPlayerRank = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::BT:
          this->blackPlayerTeamName = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::PW:
          this->whitePlayerName = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::WR:
          this->whitePlayerRank = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::WT:
          this->whitePlayerTeamName = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::PC:
          this->gameLocation = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::EV:
          this->eventName = GetSimpleTextPropertyValue(gameInfoProperty);
          break;
        case SgfcPropertyType::RO:
          this->rawRoundInformation = GetSimpleTextPropertyValue(gameInfoProperty);
          this->roundInformation = SgfcRoundInformation::FromPropertyValue(this->rawRoundInformation);
          break;
        default:
          break;
      }
    }
  }

  SgfcNumber SgfcGameInfo::GetNumberPropertyValue(std::shared_ptr<ISgfcProperty> property)
  {
    auto propertyValue = property->GetPropertyValue();
    if (propertyValue == nullptr)
      return 0;
    auto singlePropertyValue = propertyValue->ToSingleValue();
    if (singlePropertyValue == nullptr)
      return 0;
    if (singlePropertyValue->GetValueType() != SgfcPropertyValueType::Number)
      return 0;
    if (! singlePropertyValue->HasTypedValue())
      return 0;
    return singlePropertyValue->ToNumberValue()->GetNumberValue();
  }

  SgfcReal SgfcGameInfo::GetRealPropertyValue(std::shared_ptr<ISgfcProperty> property)
  {
    auto propertyValue = property->GetPropertyValue();
    if (propertyValue == nullptr)
      return 0.0;
    auto singlePropertyValue = propertyValue->ToSingleValue();
    if (singlePropertyValue == nullptr)
      return 0.0;
    if (singlePropertyValue->GetValueType() != SgfcPropertyValueType::Real)
      return 0.0;
    if (! singlePropertyValue->HasTypedValue())
      return 0.0;
    return singlePropertyValue->ToRealValue()->GetRealValue();
  }

  SgfcSimpleText SgfcGameInfo::GetSimpleTextPropertyValue(std::shared_ptr<ISgfcProperty> property)
  {
    auto propertyValue = property->GetPropertyValue();
    if (propertyValue == nullptr)
      return SgfcConstants::NoneValueString;
    auto singlePropertyValue = propertyValue->ToSingleValue();
    if (singlePropertyValue == nullptr)
      return SgfcConstants::NoneValueString;
    if (singlePropertyValue->GetValueType() != SgfcPropertyValueType::SimpleText)
      return SgfcConstants::NoneValueString;
    if (! singlePropertyValue->HasTypedValue())
      return singlePropertyValue->GetRawValue();
    return singlePropertyValue->ToSimpleTextValue()->GetSimpleTextValue();
  }

  SgfcText SgfcGameInfo::GetTextPropertyValue(std::shared_ptr<ISgfcProperty> property)
  {
    auto propertyValue = property->GetPropertyValue();
    if (propertyValue == nullptr)
      return SgfcConstants::NoneValueString;
    auto singlePropertyValue = propertyValue->ToSingleValue();
    if (singlePropertyValue == nullptr)
      return SgfcConstants::NoneValueString;
    if (singlePropertyValue->GetValueType() != SgfcPropertyValueType::Text)
      return SgfcConstants::NoneValueString;
    if (! singlePropertyValue->HasTypedValue())
      return singlePropertyValue->GetRawValue();
    return singlePropertyValue->ToTextValue()->GetTextValue();
  }
}
