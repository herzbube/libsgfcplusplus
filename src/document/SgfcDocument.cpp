// Project includes
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
      ParseProperties(rootNode, sgfRootNode);

      std::shared_ptr<ISgfcGame> game = std::shared_ptr<ISgfcGame>(new SgfcGame(rootNode));
      this->games.push_back(game);

      RecursiveParseDepthFirst(rootNode, sgfRootNode);

      sgfRootNode = sgfRootNode->sibling;
      sgfTreeInfo = sgfTreeInfo->next;
    }
  }

  void SgfcDocument::RecursiveParseDepthFirst(std::shared_ptr<ISgfcNode> parentNode, Node* sgfParentNode)
  {
    Node* sgfFirstChildNode = sgfParentNode->child;
    if (sgfFirstChildNode == nullptr)
      return;

    std::shared_ptr<ISgfcNode> firstChildNode = std::shared_ptr<ISgfcNode>(new SgfcNode());
    parentNode->SetFirstChild(firstChildNode);
    firstChildNode->SetParent(parentNode);
    ParseProperties(firstChildNode, sgfFirstChildNode);

    RecursiveParseDepthFirst(firstChildNode, sgfFirstChildNode);

    Node* sgfPreviousSiblingNode = sgfFirstChildNode;
    std::shared_ptr<ISgfcNode> previousSiblingNode = firstChildNode;

    Node* sgfNextSiblingNode = sgfPreviousSiblingNode->sibling;
    while (sgfNextSiblingNode != nullptr)
    {
      std::shared_ptr<ISgfcNode> nextSiblingNode = std::shared_ptr<ISgfcNode>(new SgfcNode());
      nextSiblingNode->SetParent(parentNode);
      previousSiblingNode->SetNextSibling(nextSiblingNode);
      ParseProperties(nextSiblingNode, sgfNextSiblingNode);

      RecursiveParseDepthFirst(nextSiblingNode, sgfNextSiblingNode);

      sgfPreviousSiblingNode = sgfNextSiblingNode;
      previousSiblingNode = nextSiblingNode;

      sgfNextSiblingNode = sgfNextSiblingNode->next;
    }
  }

  void SgfcDocument::ParseProperties(std::shared_ptr<ISgfcNode> node, Node* sgfNode)
  {
    std::vector<std::shared_ptr<ISgfcProperty>> properties;

    Property* sgfProperty = sgfNode->prop;
    while (sgfProperty)
    {
      SgfcPropertyDecoder propertyDecoder(sgfProperty);

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

  void SgfcDocument::DebugPrintToConsole() const
  {
    int gameCount = 0;
    for (const auto& sgfcGame : GetGames())
    {
      gameCount++;
      std::cout << "Game " << gameCount << std::endl;

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
      std::cout << "    Property values" << std::endl;

      bool propertyHasAtLeastOneValue = false;
      for (const auto& propertyValue : property->GetPropertyValues())
      {
        propertyHasAtLeastOneValue = true;

        std::cout << "      IsComposedValue = " << propertyValue->IsComposedValue() << std::endl;
        if (propertyValue->IsComposedValue())
        {
          const ISgfcComposedPropertyValue* composedPropertyValue = propertyValue->ToComposedValue();
          std::cout << "      Value type 1      = " << static_cast<int>(composedPropertyValue->GetValue1()->GetValueType()) << std::endl;
          std::cout << "      Has typed value 1 = " << composedPropertyValue->GetValue1()->HasTypedValue() << std::endl;
          std::cout << "      Raw value 1       = \"" << composedPropertyValue->GetValue1()->GetRawValue() << "\"" << std::endl;
          std::cout << "      Value type 2      = " << static_cast<int>(composedPropertyValue->GetValue2()->GetValueType()) << std::endl;
          std::cout << "      Has typed value 2 = \"" << composedPropertyValue->GetValue2()->HasTypedValue() << std::endl;
          std::cout << "      Raw value 2       = " << composedPropertyValue->GetValue2()->GetRawValue() << "\"" << std::endl;
        }
        else
        {
          const ISgfcSinglePropertyValue* singlePropertyValue = propertyValue->ToSingleValue();
          std::cout << "      Value type      = " << static_cast<int>(singlePropertyValue->GetValueType()) << std::endl;
          std::cout << "      Has typed value = " << singlePropertyValue->HasTypedValue() << std::endl;
          std::cout << "      Raw value       = \"" << singlePropertyValue->GetRawValue() << "\"" << std::endl;
        }
      }

      if (! propertyHasAtLeastOneValue)
      {
        std::cout << "      Property has no values" << std::endl;

      }
    }
  }
}
