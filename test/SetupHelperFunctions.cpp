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
#include "SetupHelperFunctions.h"

// Library includes
#include <document/typedproperty/SgfcBoardSizeProperty.h>
#include <document/typedproperty/SgfcGameTypeProperty.h>
#include <document/SgfcGame.h>
#include <document/SgfcNode.h>
#include <ISgfcComposedPropertyValue.h>
#include <ISgfcDoublePropertyValue.h>
#include <ISgfcNumberPropertyValue.h>
#include <ISgfcPropertyFactory.h>
#include <ISgfcPropertyValueFactory.h>
#include <ISgfcSimpleTextPropertyValue.h>
#include <SgfcPlusPlusFactory.h>
#include <SgfcUtility.h>

namespace LibSgfcPlusPlus
{
  void SetupGameWithGameAndBoardSizeProperties(std::shared_ptr<SgfcGame> game, SgfcGameType gameType, SgfcBoardSize boardSize, bool setupWithTypedProperties)
  {
    auto rootNode = std::shared_ptr<SgfcNode>(new SgfcNode());
    game->SetRootNode(rootNode);
    SetupNodeWithGameAndBoardSizeProperties(rootNode, gameType, boardSize, setupWithTypedProperties);
  }

  void SetupNodeWithGameAndBoardSizeProperties(std::shared_ptr<ISgfcNode> node, SgfcGameType gameType, SgfcBoardSize boardSize, bool setupWithTypedProperties)
  {
    std::vector<std::shared_ptr<ISgfcProperty>> properties;
    AddGameTypeProperty(gameType, properties, setupWithTypedProperties);
    AddBoardSizeProperty(boardSize, properties, setupWithTypedProperties);

    node->SetProperties(properties);
  }

  void SetupGameWithBoardSizeProperty(std::shared_ptr<SgfcGame> game, SgfcBoardSize boardSize, bool setupWithTypedProperty)
  {
    std::vector<std::shared_ptr<ISgfcProperty>> properties;
    AddBoardSizeProperty(boardSize, properties, setupWithTypedProperty);

    auto rootNode = std::shared_ptr<SgfcNode>(new SgfcNode());
    rootNode->SetProperties(properties);

    game->SetRootNode(rootNode);
  }

  void AddGameTypeProperty(SgfcGameType gameType, std::vector<std::shared_ptr<ISgfcProperty>>& properties, bool setupWithTypedProperty)
  {
    auto gameTypeProperty = CreateGameTypeProperty(
      SgfcUtility::MapGameTypeToNumberValue(gameType),
      setupWithTypedProperty);

    properties.push_back(gameTypeProperty);
  }

  void AddGameTypeProperty(SgfcNumber gameTypeAsNumber, std::vector<std::shared_ptr<ISgfcProperty>>& properties, bool setupWithTypedProperty)
  {
    auto gameTypeProperty = CreateGameTypeProperty(
      gameTypeAsNumber,
      setupWithTypedProperty);

    properties.push_back(gameTypeProperty);
  }

  void AddGameTypePropertyWithInvalidValues(std::vector<std::shared_ptr<ISgfcProperty>>& properties, InvalidValueTypeGameType invalidValueType)
  {
    auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
    std::shared_ptr<ISgfcProperty> gameTypeProperty = propertyFactory->CreateProperty(
        SgfcPropertyType::GM);

    auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();
    std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues;
    switch (invalidValueType)
    {
      case InvalidValueTypeGameType::MoreThanOneValue:
        propertyValues.push_back(propertyValueFactory->CreateNumberPropertyValue(1));
        propertyValues.push_back(propertyValueFactory->CreateNumberPropertyValue(12));
        break;
      case InvalidValueTypeGameType::ComposedValue:
        propertyValues.push_back(propertyValueFactory->CreateComposedNumberAndNumberPropertyValue(17, 42));
        break;
      case InvalidValueTypeGameType::SingleValueTypeNotANumber:
        propertyValues.push_back(propertyValueFactory->CreateDoublePropertyValue(SgfcDouble::Normal));
        break;
      default:
        throw std::logic_error("Unexpected InvalidValueTypeGameType value");
        break;
    }
    gameTypeProperty->SetPropertyValues(propertyValues);

    properties.push_back(gameTypeProperty);
  }

  std::shared_ptr<ISgfcProperty> CreateGameTypeProperty(SgfcNumber gameTypeAsNumber, bool createTypedProperty)
  {
    auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
    auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();

    auto gameTypePropertyValue = propertyValueFactory->CreateNumberPropertyValue(
      gameTypeAsNumber);

    std::shared_ptr<ISgfcProperty> gameTypeProperty;
    if (createTypedProperty)
    {
      gameTypeProperty = propertyFactory->CreateGameTypeProperty(
        gameTypePropertyValue);
    }
    else
    {
      gameTypeProperty = propertyFactory->CreateProperty(
        SgfcPropertyType::GM,
        gameTypePropertyValue);
    }

    return gameTypeProperty;
  }

  void AddBoardSizeProperty(SgfcBoardSize boardSize, std::vector<std::shared_ptr<ISgfcProperty>>& properties, bool setupWithTypedProperty)
  {
    auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
    auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();

    std::shared_ptr<ISgfcProperty> boardSizeProperty;
    if (boardSize.IsSquare())
    {
      auto boardSizePropertyValue = propertyValueFactory->CreateNumberPropertyValue(
        boardSize.Columns);
      if (setupWithTypedProperty)
      {
        boardSizeProperty = propertyFactory->CreateBoardSizeProperty(
          boardSizePropertyValue);
      }
      else
      {
        boardSizeProperty = propertyFactory->CreateProperty(
          SgfcPropertyType::SZ,
          boardSizePropertyValue);
      }
    }
    else
    {
      auto boardSizePropertyValue = propertyValueFactory->CreateComposedNumberAndNumberPropertyValue(
        boardSize.Columns,
        boardSize.Rows);
      if (setupWithTypedProperty)
      {
        boardSizeProperty = propertyFactory->CreateBoardSizeProperty(
          boardSizePropertyValue);
      }
      else
      {
        boardSizeProperty = propertyFactory->CreateProperty(
          SgfcPropertyType::SZ,
          boardSizePropertyValue);
      }
    }

    properties.push_back(boardSizeProperty);
  }

  void AddBoardSizePropertyWithInvalidValues(std::vector<std::shared_ptr<ISgfcProperty>>& properties, InvalidValueTypeBoardSize invalidValueType)
  {
    auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
    std::shared_ptr<ISgfcProperty> gameTypeProperty = propertyFactory->CreateProperty(
        SgfcPropertyType::SZ);

    auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();
    std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues;
    switch (invalidValueType)
    {
      case InvalidValueTypeBoardSize::MoreThanOneValue:
        propertyValues.push_back(propertyValueFactory->CreateNumberPropertyValue(1));
        propertyValues.push_back(propertyValueFactory->CreateNumberPropertyValue(12));
        break;
      case InvalidValueTypeBoardSize::ComposedValueNotANumberAndNumber:
        propertyValues.push_back(propertyValueFactory->CreateComposedNumberAndSimpleTextPropertyValue(17, "foo"));
        break;
      case InvalidValueTypeBoardSize::SingleValueTypeNotANumber:
        propertyValues.push_back(propertyValueFactory->CreateDoublePropertyValue(SgfcDouble::Normal));
        break;
      default:
        throw std::logic_error("Unexpected InvalidValueTypeBoardSize value");
        break;
    }
    gameTypeProperty->SetPropertyValues(propertyValues);

    properties.push_back(gameTypeProperty);
  }

  std::shared_ptr<ISgfcProperty> CreateSimpleTextProperty(SgfcPropertyType propertyType, const SgfcSimpleText& propertyValue)
  {
    auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
    auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();

    auto simpleTextPropertyValue = propertyValueFactory->CreateSimpleTextPropertyValue(
      propertyValue);

    std::shared_ptr<ISgfcProperty> property = propertyFactory->CreateProperty(propertyType, simpleTextPropertyValue);
    return property;
  }
}
