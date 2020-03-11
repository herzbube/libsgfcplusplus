// Project includes
#include "../../include/ISgfcGoMove.h"
#include "../../include/ISgfcGoMovePropertyValue.h"
#include "../../include/ISgfcGoPoint.h"
#include "../../include/ISgfcGoPointPropertyValue.h"
#include "../../include/ISgfcGoStone.h"
#include "../../include/ISgfcGoStonePropertyValue.h"
#include "../../include/ISgfcMovePropertyValue.h"
#include "../../include/ISgfcPointPropertyValue.h"
#include "../../include/ISgfcStonePropertyValue.h"
#include "../parsing/SgfcPropertyDecoder.h"
#include "SgfcComposedPropertyValue.h"
#include "SgfcDocument.h"
#include "SgfcGame.h"
#include "SgfcNode.h"
#include "SgfcProperty.h"

// C++ Standard Library includes
#include <iostream>

// SGFC includes
extern "C"
{
  #include "../../sgfc/all.h"
  #include "../../sgfc/protos.h"
}

namespace LibSgfcPlusPlus
{
  SgfcDocument::SgfcDocument()
  {
  }

  SgfcDocument::SgfcDocument(SGFInfo* sgfInfo)
  {
    // sgfInfo->b_end does not point to the last byte in the buffer.
    // sgfInfo->b_end points to the position behind the last byte of the buffer.
    // For instance, if the file is empty then sgfInfo->buffer and
    // sgfInfo->b_end point to the same address. See how sgfInfo->b_end is
    // initialized in LoadSGF().
    size_t rawContentLength = sgfInfo->b_end - sgfInfo->buffer;
    if (rawContentLength >= 0)
      this->rawContent = std::string(sgfInfo->buffer, rawContentLength);

    size_t leadingContentLength = sgfInfo->start - sgfInfo->buffer;
    if (leadingContentLength >= 0)
      this->leadingContent = std::string(sgfInfo->buffer, leadingContentLength);

    Node* sgfRootNode = sgfInfo->root;
    TreeInfo* sgfTreeInfo = sgfInfo->tree;
    while (sgfRootNode)
    {
      std::shared_ptr<ISgfcNode> rootNode = std::shared_ptr<ISgfcNode>(new SgfcNode());

      SgfcGameType gameType = SgfcPropertyDecoder::GetGameTypeFromNode(sgfRootNode);

      ParseProperties(rootNode, sgfRootNode, gameType);

      std::shared_ptr<ISgfcGame> game = std::shared_ptr<ISgfcGame>(new SgfcGame(rootNode));
      this->games.push_back(game);

      RecursiveParseDepthFirst(rootNode, sgfRootNode, gameType);

      sgfRootNode = sgfRootNode->sibling;
      sgfTreeInfo = sgfTreeInfo->next;
    }
  }

  void SgfcDocument::RecursiveParseDepthFirst(
    std::shared_ptr<ISgfcNode> parentNode,
    Node* sgfParentNode,
    SgfcGameType gameType)
  {
    Node* sgfFirstChildNode = sgfParentNode->child;
    if (sgfFirstChildNode == nullptr)
      return;

    std::shared_ptr<ISgfcNode> firstChildNode = std::shared_ptr<ISgfcNode>(new SgfcNode());
    parentNode->SetFirstChild(firstChildNode);
    firstChildNode->SetParent(parentNode);
    ParseProperties(firstChildNode, sgfFirstChildNode, gameType);

    RecursiveParseDepthFirst(firstChildNode, sgfFirstChildNode, gameType);

    Node* sgfPreviousSiblingNode = sgfFirstChildNode;
    std::shared_ptr<ISgfcNode> previousSiblingNode = firstChildNode;

    Node* sgfNextSiblingNode = sgfFirstChildNode->sibling;
    while (sgfNextSiblingNode != nullptr)
    {
      std::shared_ptr<ISgfcNode> nextSiblingNode = std::shared_ptr<ISgfcNode>(new SgfcNode());
      nextSiblingNode->SetParent(parentNode);
      previousSiblingNode->SetNextSibling(nextSiblingNode);
      ParseProperties(nextSiblingNode, sgfNextSiblingNode, gameType);

      RecursiveParseDepthFirst(nextSiblingNode, sgfNextSiblingNode, gameType);

      sgfPreviousSiblingNode = sgfNextSiblingNode;
      previousSiblingNode = nextSiblingNode;

      sgfNextSiblingNode = sgfNextSiblingNode->sibling;
    }
  }

  void SgfcDocument::ParseProperties(
    std::shared_ptr<ISgfcNode> node,
    Node* sgfNode,
    SgfcGameType gameType)
  {
    std::vector<std::shared_ptr<ISgfcProperty>> properties;

    Property* sgfProperty = sgfNode->prop;
    while (sgfProperty)
    {
      SgfcPropertyDecoder propertyDecoder(sgfProperty, gameType);

      SgfcPropertyType propertyType = propertyDecoder.GetPropertyType();
      std::string propertyName = propertyDecoder.GetPropertyName();
      std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues = propertyDecoder.GetPropertyValues();

      std::shared_ptr<ISgfcProperty> property = std::shared_ptr<ISgfcProperty>(new SgfcProperty(
        propertyType,
        propertyName,
        propertyValues));
      properties.push_back(property);

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

      std::vector<std::shared_ptr<ISgfcNode>> stack;

      std::shared_ptr<ISgfcNode> rootNode = sgfcGame->GetRootNode();
      stack.push_back(rootNode);

      while (stack.size() > 0)
      {
        std::shared_ptr<ISgfcNode> node = stack.back();
        stack.pop_back();

        DebugPrintNodeToConsole(node);

        std::shared_ptr<ISgfcNode> firstChild = node->GetFirstChild();
        if (firstChild)
        {
          stack.push_back(firstChild);

          std::shared_ptr<ISgfcNode> nextSibling = firstChild->GetNextSibling();
          while (nextSibling)
          {
            stack.push_back(nextSibling);
            nextSibling = nextSibling->GetNextSibling();
          }
        }
      }
    }
  }

  void SgfcDocument::DebugPrintNodeToConsole(std::shared_ptr<ISgfcNode> node) const
  {
    std::cout << "  Node" << std::endl;
    for (const auto& property : node->GetProperties())
    {
      std::cout << "    Property type = " << static_cast<int>(property->GetPropertyType()) << std::endl;
      std::cout << "    Property name = " << property->GetPropertyName() << std::endl;

      int valueCount = 0;
      bool propertyHasAtLeastOneValue = false;
      for (const auto& propertyValue : property->GetPropertyValues())
      {
        valueCount++;
        propertyHasAtLeastOneValue = true;

        std::cout << "    Property value " << valueCount << std::endl;

        std::cout << "      IsComposedValue = " << propertyValue->IsComposedValue() << std::endl;
        if (propertyValue->IsComposedValue())
        {
          const ISgfcComposedPropertyValue* composedPropertyValue = propertyValue->ToComposedValue();
          std::cout << "      Value type 1      = " << static_cast<int>(composedPropertyValue->GetValue1()->GetValueType()) << std::endl;
          std::cout << "      Has typed value 1 = " << composedPropertyValue->GetValue1()->HasTypedValue() << std::endl;
          std::cout << "      Raw value 1       = \"" << composedPropertyValue->GetValue1()->GetRawValue() << "\"" << std::endl;
          DebugPrintGoPropertyValueToConsole(composedPropertyValue->GetValue1().get());
          std::cout << "      Value type 2      = " << static_cast<int>(composedPropertyValue->GetValue2()->GetValueType()) << std::endl;
          std::cout << "      Has typed value 2 = \"" << composedPropertyValue->GetValue2()->HasTypedValue() << std::endl;
          std::cout << "      Raw value 2       = " << composedPropertyValue->GetValue2()->GetRawValue() << "\"" << std::endl;
          DebugPrintGoPropertyValueToConsole(composedPropertyValue->GetValue2().get());
        }
        else
        {
          const ISgfcSinglePropertyValue* singlePropertyValue = propertyValue->ToSingleValue();
          std::cout << "      Value type      = " << static_cast<int>(singlePropertyValue->GetValueType()) << std::endl;
          std::cout << "      Has typed value = " << singlePropertyValue->HasTypedValue() << std::endl;
          std::cout << "      Raw value       = \"" << singlePropertyValue->GetRawValue() << "\"" << std::endl;
          DebugPrintGoPropertyValueToConsole(singlePropertyValue);
        }
      }

      if (! propertyHasAtLeastOneValue)
      {
        std::cout << "      Property has no values" << std::endl;

      }
    }
  }

  void SgfcDocument::DebugPrintGoPropertyValueToConsole(const ISgfcSinglePropertyValue* propertyValue) const
  {
    if (propertyValue->GetValueType() == SgfcPropertyValueType::Point)
    {
      const ISgfcPointPropertyValue* pointValue = propertyValue->ToPointValue();
      const ISgfcGoPointPropertyValue* goPointValue = pointValue->ToGoPointValue();
      std::cout << "      Is Go Point = " << (goPointValue != nullptr) << std::endl;
      if (goPointValue == nullptr)
        return;

      std::shared_ptr<ISgfcGoPoint> goPoint = goPointValue->GetGoPoint();
      DebugPrintGoPointValueToConsole(goPoint.get());
    }
    else if (propertyValue->GetValueType() == SgfcPropertyValueType::Stone)
    {
      const ISgfcStonePropertyValue* stoneValue = propertyValue->ToStoneValue();
      const ISgfcGoStonePropertyValue* goStoneValue = stoneValue->ToGoStoneValue();
      std::cout << "      Is Go Stone = " << (goStoneValue != nullptr) << std::endl;
      if (goStoneValue == nullptr)
        return;

      std::shared_ptr<ISgfcGoStone> goStone = goStoneValue->GetGoStone();
      std::cout << "        Stone color = " << static_cast<int>(goStone->GetColor()) << std::endl;

      std::shared_ptr<ISgfcGoPoint> location = goStone->GetLocation();
      DebugPrintGoPointValueToConsole(location.get());
    }
    else if (propertyValue->GetValueType() == SgfcPropertyValueType::Move)
    {
      const ISgfcMovePropertyValue* moveValue = propertyValue->ToMoveValue();
      const ISgfcGoMovePropertyValue* goMoveValue = moveValue->ToGoMoveValue();
      std::cout << "      Is Go Move = " << (goMoveValue != nullptr) << std::endl;
      if (goMoveValue == nullptr)
        return;

      std::shared_ptr<ISgfcGoMove> goMove = goMoveValue->GetGoMove();
      std::cout << "        Player color = " << static_cast<int>(goMove->GetPlayerColor()) << std::endl;

      std::shared_ptr<ISgfcGoPoint> location = goMove->GetStoneLocation();
      DebugPrintGoPointValueToConsole(location.get());
    }
  }

  void SgfcDocument::DebugPrintGoPointValueToConsole(const ISgfcGoPoint* goPoint) const
  {
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
