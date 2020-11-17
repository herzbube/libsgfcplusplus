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
#include "../../include/ISgfcColorPropertyValue.h"
#include "../../include/ISgfcComposedPropertyValue.h"
#include "../../include/ISgfcDoublePropertyValue.h"
#include "../../include/ISgfcGame.h"
#include "../../include/ISgfcGoMove.h"
#include "../../include/ISgfcGoMovePropertyValue.h"
#include "../../include/ISgfcGoPoint.h"
#include "../../include/ISgfcGoPointPropertyValue.h"
#include "../../include/ISgfcGoStone.h"
#include "../../include/ISgfcGoStonePropertyValue.h"
#include "../../include/ISgfcMovePropertyValue.h"
#include "../../include/ISgfcNumberPropertyValue.h"
#include "../../include/ISgfcNode.h"
#include "../../include/ISgfcPointPropertyValue.h"
#include "../../include/ISgfcProperty.h"
#include "../../include/ISgfcPropertyFactory.h"
#include "../../include/ISgfcRealPropertyValue.h"
#include "../../include/ISgfcSimpleTextPropertyValue.h"
#include "../../include/ISgfcStonePropertyValue.h"
#include "../../include/ISgfcTextPropertyValue.h"
#include "../../include/ISgfcTreeBuilder.h"
#include "../../include/SgfcPlusPlusFactory.h"
#include "../parsing/SgfcPropertyDecoder.h"
#include "../SgfcUtility.h"
#include "SgfcDocument.h"
#include "SgfcProperty.h"

// C++ Standard Library includes
#include <algorithm>
#include <iostream>
#include <set>
#include <stdexcept>

// SGFC includes
extern "C"
{
  #include "../../sgfc/src/all.h"
  #include "../../sgfc/src/protos.h"
}

namespace LibSgfcPlusPlus
{
  SgfcDocument::SgfcDocument()
  {
  }

  SgfcDocument::SgfcDocument(SGFInfo* sgfInfo)
  {
    if (sgfInfo == nullptr)
      throw std::invalid_argument("SgfcDocument constructor failed: SGFInfo object is nullptr");

    Node* sgfRootNode = sgfInfo->root;
    TreeInfo* sgfTreeInfo = sgfInfo->tree;
    while (sgfRootNode)
    {
      auto rootNode = SgfcPlusPlusFactory::CreateNode();

      // Both of these methods can throw std::domain_error
      SgfcGameType gameType = SgfcPropertyDecoder::GetGameTypeFromNode(sgfRootNode);
      SgfcBoardSize boardSize = SgfcPropertyDecoder::GetBoardSizeFromNode(sgfRootNode, gameType);

      ParseProperties(rootNode, sgfRootNode, gameType, boardSize);

      auto game = SgfcPlusPlusFactory::CreateGame(rootNode);
      this->games.push_back(game);

      std::shared_ptr<ISgfcTreeBuilder> treeBuilder = game->GetTreeBuilder();
      RecursiveParseDepthFirst(rootNode, sgfRootNode, gameType, boardSize, treeBuilder);

      sgfRootNode = sgfRootNode->sibling;
      sgfTreeInfo = sgfTreeInfo->next;
    }
  }

  void SgfcDocument::RecursiveParseDepthFirst(
    std::shared_ptr<ISgfcNode> parentNode,
    Node* sgfParentNode,
    SgfcGameType gameType,
    SgfcBoardSize boardSize,
    std::shared_ptr<ISgfcTreeBuilder> treeBuilder)
  {
    Node* sgfFirstChildNode = sgfParentNode->child;
    if (sgfFirstChildNode == nullptr)
      return;

    auto firstChildNode = SgfcPlusPlusFactory::CreateNode();
    treeBuilder->SetFirstChild(parentNode, firstChildNode);
    ParseProperties(firstChildNode, sgfFirstChildNode, gameType, boardSize);

    RecursiveParseDepthFirst(firstChildNode, sgfFirstChildNode, gameType, boardSize, treeBuilder);

    Node* sgfNextSiblingNode = sgfFirstChildNode->sibling;
    while (sgfNextSiblingNode != nullptr)
    {
      auto nextSiblingNode = SgfcPlusPlusFactory::CreateNode();
      treeBuilder->AppendChild(parentNode, nextSiblingNode);
      ParseProperties(nextSiblingNode, sgfNextSiblingNode, gameType, boardSize);

      RecursiveParseDepthFirst(nextSiblingNode, sgfNextSiblingNode, gameType, boardSize, treeBuilder);

      sgfNextSiblingNode = sgfNextSiblingNode->sibling;
    }
  }

  void SgfcDocument::ParseProperties(
    std::shared_ptr<ISgfcNode> node,
    Node* sgfNode,
    SgfcGameType gameType,
    SgfcBoardSize boardSize)
  {
    auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();

    std::vector<std::shared_ptr<ISgfcProperty>> properties;

    Property* sgfProperty = sgfNode->prop;
    while (sgfProperty)
    {
      // This can throw std::domain_error
      SgfcPropertyDecoder propertyDecoder(sgfProperty, gameType, boardSize);

      // This can throw std::domain_error
      std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues = propertyDecoder.GetPropertyValues();

      SgfcPropertyType propertyType = propertyDecoder.GetPropertyType();
      if (propertyType == SgfcPropertyType::Unknown)
      {
        std::string propertyName = propertyDecoder.GetPropertyName();
        auto property = propertyFactory->CreateProperty(propertyName, propertyValues);
        properties.push_back(property);
      }
      else
      {
        std::shared_ptr<ISgfcProperty> property;
        try
        {
          // Try to create an instance of that property class which best fits
          // propertyType (e.g. ISgfcBoardSizeProperty). This can throw
          // std::invalid_argument if the property values don't meet the
          // requirements of this best-fitting property class.
          property = propertyFactory->CreateProperty(propertyType, propertyValues);
        }
        catch (std::invalid_argument& exception)
        {
          // The property values didn't meet the requirements of the
          // best-fitting property class. We fall back to creating a property
          // object of an unspecific type. In theory this can still throw
          // std::invalid_argument, if the property values collection is
          // fundamentally broken (nullptr or duplicate elements in the
          // collection). In practice this should never occur, unless
          // SgfcPropertyDecoder generates fundamentally broken output.
          property = std::shared_ptr<ISgfcProperty>(new SgfcProperty(
            propertyType,
            SgfcUtility::MapPropertyTypeToPropertyName(propertyType),
            propertyValues));
        }
        properties.push_back(property);
      }

      sgfProperty = sgfProperty->next;
    }

    node->SetProperties(properties);
  }

  SgfcDocument::~SgfcDocument()
  {
  }

  bool SgfcDocument::IsEmpty() const
  {
    return this->games.empty();
  }

  std::vector<std::shared_ptr<ISgfcGame>> SgfcDocument::GetGames() const
  {
    return this->games;
  }

  void SgfcDocument::SetGames(const std::vector<std::shared_ptr<ISgfcGame>>& games)
  {
    std::set<std::shared_ptr<ISgfcGame>> uniqueGames(games.begin(), games.end());
    if (uniqueGames.size() != games.size())
      throw std::invalid_argument("SetGames failed: Game list contains duplicate elements");

    auto result = std::find(std::begin(games), std::end(games), nullptr);
    if (result != std::end(games))
      throw std::invalid_argument("SetGames failed: Game list contains nullptr element");

    this->games = games;
  }

  void SgfcDocument::AppendGame(std::shared_ptr<ISgfcGame> game)
  {
    if (game == nullptr)
      throw std::invalid_argument("AppendGame failed: Game argument is null");

    auto result = std::find(std::begin(this->games), std::end(this->games), game);
    if (result != std::end(this->games))
      throw std::invalid_argument("AppendGame failed: Game is already part of the document");

    this->games.push_back(game);
  }

  void SgfcDocument::RemoveGame(std::shared_ptr<ISgfcGame> game)
  {
    // This works because std::shared_ptr::operator==() compares pointer values
    auto result = std::find(std::begin(this->games), std::end(this->games), game);
    if (result == std::end(this->games))
      throw std::invalid_argument("RemoveGame failed: Game is not part of the document");

    this->games.erase(result);
  }

  void SgfcDocument::RemoveAllGames()
  {
    this->games.clear();
  }

  void SgfcDocument::DebugPrintToConsole() const
  {
    int gameCount = 0;
    for (const auto& sgfcGame : GetGames())
    {
      gameCount++;
      std::cout << "Game " << gameCount << std::endl;
      std::cout << "  Game type = " << static_cast<int>(sgfcGame->GetGameType()) << std::endl;

      int nodeCount = 0;
      std::shared_ptr<ISgfcNode> rootNode = sgfcGame->GetRootNode();

      nodeCount++;
      DebugPrintNodeToConsole(rootNode, nodeCount);
      DebugPrintToConsoleRecursiveParseDepthFirst(rootNode, nodeCount);
    }
  }

  void SgfcDocument::DebugPrintToConsoleRecursiveParseDepthFirst(
    std::shared_ptr<ISgfcNode> parentNode,
    int& nodeCount) const
  {
    auto firstChildNode = parentNode->GetFirstChild();
    if (firstChildNode == nullptr)
      return;

    nodeCount++;
    DebugPrintNodeToConsole(firstChildNode, nodeCount);
    DebugPrintToConsoleRecursiveParseDepthFirst(firstChildNode, nodeCount);

    auto nextSiblingNode = firstChildNode->GetNextSibling();
    while (nextSiblingNode != nullptr)
    {
      nodeCount++;
      DebugPrintNodeToConsole(nextSiblingNode, nodeCount);
      DebugPrintToConsoleRecursiveParseDepthFirst(nextSiblingNode, nodeCount);

      nextSiblingNode = nextSiblingNode->GetNextSibling();
    }
  }

  void SgfcDocument::DebugPrintNodeToConsole(std::shared_ptr<ISgfcNode> node, int nodeNumber) const
  {
    std::cout << "  Node " << nodeNumber << std::endl;

    bool nodeHasAtLeastOneProperty = false;
    for (const auto& property : node->GetProperties())
    {
      nodeHasAtLeastOneProperty = true;
      auto propertyValues = property->GetPropertyValues();

      std::cout << "    Property type = " << static_cast<int>(property->GetPropertyType()) << std::endl;
      std::cout << "    Property name = " << property->GetPropertyName() << std::endl;
      std::cout << "    Value count   = " << propertyValues.size() << std::endl;

      int valueCount = 0;
      bool propertyHasAtLeastOneValue = false;
      for (const auto& propertyValue : propertyValues)
      {
        valueCount++;
        propertyHasAtLeastOneValue = true;

        std::cout << "    Property value " << valueCount << std::endl;

        std::cout << "      IsComposedValue    = " << propertyValue->IsComposedValue() << std::endl;
        if (propertyValue->IsComposedValue())
        {
          const ISgfcComposedPropertyValue* composedPropertyValue = propertyValue->ToComposedValue();
          std::cout << "      Value type 1       = " << static_cast<int>(composedPropertyValue->GetValue1()->GetValueType()) << std::endl;
          std::cout << "      Has typed value 1  = " << composedPropertyValue->GetValue1()->HasTypedValue() << std::endl;
          std::cout << "      Raw value 1        = \"" << composedPropertyValue->GetValue1()->GetRawValue() << "\"" << std::endl;
          DebugPrintGoPropertyValueToConsole(composedPropertyValue->GetValue1().get());
          std::cout << "      Value type 2       = " << static_cast<int>(composedPropertyValue->GetValue2()->GetValueType()) << std::endl;
          std::cout << "      Has typed value 2  = " << composedPropertyValue->GetValue2()->HasTypedValue() << std::endl;
          std::cout << "      Raw value 2        = \"" << composedPropertyValue->GetValue2()->GetRawValue() << "\"" << std::endl;
          DebugPrintGoPropertyValueToConsole(composedPropertyValue->GetValue2().get());
        }
        else
        {
          const ISgfcSinglePropertyValue* singlePropertyValue = propertyValue->ToSingleValue();
          std::cout << "      Value type         = " << static_cast<int>(singlePropertyValue->GetValueType()) << std::endl;
          std::cout << "      Has typed value    = " << singlePropertyValue->HasTypedValue() << std::endl;
          std::cout << "      Raw value          = \"" << singlePropertyValue->GetRawValue() << "\"" << std::endl;
          DebugPrintGoPropertyValueToConsole(singlePropertyValue);
        }
      }

      if (! propertyHasAtLeastOneValue)
      {
        std::cout << "      Property has no values" << std::endl;
      }
    }

    if (! nodeHasAtLeastOneProperty)
    {
      std::cout << "    Node has no properties" << std::endl;
    }
  }

  void SgfcDocument::DebugPrintGoPropertyValueToConsole(const ISgfcSinglePropertyValue* propertyValue) const
  {
    if (! propertyValue->HasTypedValue())
    {
      std::cout << "      Type conversion error = \"" << propertyValue->GetTypeConversionErrorMessage() << "\"" << std::endl;
    }
    else if (propertyValue->GetValueType() == SgfcPropertyValueType::Number)
    {
      std::cout << "      Number value       = " << propertyValue->ToNumberValue()->GetNumberValue() << std::endl;
    }
    else if (propertyValue->GetValueType() == SgfcPropertyValueType::Real)
    {
      std::cout << "      Real value         = " << propertyValue->ToRealValue()->GetRealValue() << std::endl;
    }
    else if (propertyValue->GetValueType() == SgfcPropertyValueType::Double)
    {
      std::cout << "      Double value       = " << static_cast<int>(propertyValue->ToDoubleValue()->GetDoubleValue()) << std::endl;
    }
    else if (propertyValue->GetValueType() == SgfcPropertyValueType::Color)
    {
      std::cout << "      Color value        = " << static_cast<int>(propertyValue->ToColorValue()->GetColorValue()) << std::endl;
    }
    else if (propertyValue->GetValueType() == SgfcPropertyValueType::SimpleText)
    {
      std::cout << "      SimpleText value   = \"" << propertyValue->ToSimpleTextValue()->GetSimpleTextValue() << "\"" << std::endl;
    }
    else if (propertyValue->GetValueType() == SgfcPropertyValueType::Text)
    {
      std::cout << "      Text value         = \"" << propertyValue->ToTextValue()->GetTextValue() << "\"" << std::endl;
    }
    else if (propertyValue->GetValueType() == SgfcPropertyValueType::Point)
    {
      const ISgfcPointPropertyValue* pointValue = propertyValue->ToPointValue();
      std::cout << "      Point value        = \"" << pointValue->GetPointValue() << "\"" << std::endl;

      const ISgfcGoPointPropertyValue* goPointValue = pointValue->ToGoPointValue();
      std::cout << "      Is Go Point        = " << (goPointValue != nullptr) << std::endl;
      if (goPointValue != nullptr)
      {
        std::shared_ptr<ISgfcGoPoint> goPoint = goPointValue->GetGoPoint();
        DebugPrintGoPointValueToConsole(goPoint.get());
      }
    }
    else if (propertyValue->GetValueType() == SgfcPropertyValueType::Stone)
    {
      const ISgfcStonePropertyValue* stoneValue = propertyValue->ToStoneValue();
      std::cout << "      Stone value        = \"" << stoneValue->GetStoneValue() << "\"" << std::endl;

      const ISgfcGoStonePropertyValue* goStoneValue = stoneValue->ToGoStoneValue();
      std::cout << "      Is Go Stone        = " << (goStoneValue != nullptr) << std::endl;
      if (goStoneValue != nullptr)
      {
        std::shared_ptr<ISgfcGoStone> goStone = goStoneValue->GetGoStone();
        std::cout << "        Stone color = " << static_cast<int>(goStone->GetColor()) << std::endl;

        std::shared_ptr<ISgfcGoPoint> location = goStone->GetLocation();
        DebugPrintGoPointValueToConsole(location.get());
      }
    }
    else if (propertyValue->GetValueType() == SgfcPropertyValueType::Move)
    {
      const ISgfcMovePropertyValue* moveValue = propertyValue->ToMoveValue();
      std::cout << "      Move  value        = \"" << moveValue->GetMoveValue() << "\"" << std::endl;

      const ISgfcGoMovePropertyValue* goMoveValue = moveValue->ToGoMoveValue();
      std::cout << "      Is Go Move         = " << (goMoveValue != nullptr) << std::endl;
      if (goMoveValue != nullptr)
      {
        std::shared_ptr<ISgfcGoMove> goMove = goMoveValue->GetGoMove();
        std::cout << "        Player color = " << static_cast<int>(goMove->GetPlayerColor()) << std::endl;
        std::cout << "        Is pass move = " << goMove->IsPassMove() << std::endl;

        std::shared_ptr<ISgfcGoPoint> location = goMove->GetStoneLocation();
        DebugPrintGoPointValueToConsole(location.get());
      }
    }
  }

  void SgfcDocument::DebugPrintGoPointValueToConsole(const ISgfcGoPoint* goPoint) const
  {
    if (goPoint == nullptr)
    {
      std::cout << "        No Go point object" << std::endl;
      return;
    }
    std::vector<SgfcCoordinateSystem> coordinateSystems
    {
      SgfcCoordinateSystem::UpperLeftOrigin,
      SgfcCoordinateSystem::LowerLeftOrigin,
    };
    for (SgfcCoordinateSystem coordinateSystem : coordinateSystems)
    {
      int coordinateSystemAsInt = static_cast<int>(coordinateSystem);
      std::cout << "        Coordinate system " << coordinateSystemAsInt << std::endl;
      std::cout << "          GetXPosition = " << goPoint->GetXPosition(coordinateSystem) << std::endl;
      std::cout << "          GetYPosition = " << goPoint->GetYPosition(coordinateSystem) << std::endl;
    }
    std::vector<SgfcGoPointNotation> notations
    {
      SgfcGoPointNotation::Sgf,
      SgfcGoPointNotation::Figure,
      SgfcGoPointNotation::Hybrid,
    };
    for (SgfcGoPointNotation notation : notations)
    {
      int notationAsInt = static_cast<int>(notation);
      std::cout << "        Notation " << notationAsInt << std::endl;
      std::cout << "          HasPosition = " << goPoint->HasPosition(notation) << std::endl;
      std::cout << "          GetPosition = " << goPoint->GetPosition(notation) << std::endl;
      std::cout << "          GetXPosition = " << goPoint->GetXPosition(notation) << std::endl;
      std::cout << "          GetYPosition = " << goPoint->GetYPosition(notation) << std::endl;
    }
  }
}
