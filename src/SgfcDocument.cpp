// Project includes
#include "SgfcDocument.h"
#include "SgfcGame.h"
#include "SgfcNode.h"
#include "SgfcProperty.h"
#include "SgfcPropertyValue.h"

// C++ Standard Library includes
#include <sstream>
#include <iostream>

// SGFC includes
extern "C"
{
  #include "../sgfc/all.h"
  #include "../sgfc/protos.h"
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
      SgfcPropertyType propertyType = GetSgfcPropertyTypeFromSgfProperty(sgfProperty);
      std::string propertyName = sgfProperty->idstr;
      std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues;

      PropValue* sgfPropertyValue = sgfProperty->value;
      while (sgfPropertyValue)
      {
        std::shared_ptr<ISgfcPropertyValue> propertyValue;
        if (sgfPropertyValue->value2 == nullptr)
        {
          propertyValue = std::shared_ptr<ISgfcPropertyValue>(new SgfcPropertyValue(
            sgfPropertyValue->value));
        }
        else
        {
          propertyValue = std::shared_ptr<ISgfcPropertyValue>(new SgfcPropertyValue(
            sgfPropertyValue->value,
            sgfPropertyValue->value2));
        }

        propertyValues.push_back(propertyValue);

        sgfPropertyValue = sgfPropertyValue->next;
      }

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

  SgfcPropertyType SgfcDocument::GetSgfcPropertyTypeFromSgfProperty(Property* sgfProperty)
  {
    switch (sgfProperty->id)
    {
      case TKN_NONE:
        return SgfcPropertyType::Unknown;
      case TKN_UNKNOWN:
        return SgfcPropertyType::Unknown;
      case TKN_B:
        return SgfcPropertyType::B;
      case TKN_W:
        return SgfcPropertyType::W;
      case TKN_AB:
        return SgfcPropertyType::AB;
      case TKN_AW:
        return SgfcPropertyType::AW;
      case TKN_AE:
        return SgfcPropertyType::AE;
      case TKN_N:
        return SgfcPropertyType::N;
      case TKN_C:
        return SgfcPropertyType::C;
      case TKN_BL:
        return SgfcPropertyType::BL;
      case TKN_WL:
        return SgfcPropertyType::WL;
      case TKN_OB:
        return SgfcPropertyType::OB;
      case TKN_OW:
        return SgfcPropertyType::OW;
      case TKN_FF:
        return SgfcPropertyType::FF;
      case TKN_GM:
        return SgfcPropertyType::GM;
      case TKN_SZ:
        return SgfcPropertyType::SZ;
      case TKN_ST:
        return SgfcPropertyType::ST;
      case TKN_CA:
        return SgfcPropertyType::CA;
      case TKN_AP:
        return SgfcPropertyType::AP;
      case TKN_GN:
        return SgfcPropertyType::GN;
      case TKN_GC:
        return SgfcPropertyType::GC;
      case TKN_PB:
        return SgfcPropertyType::PB;
      case TKN_PW:
        return SgfcPropertyType::PW;
      case TKN_BR:
        return SgfcPropertyType::BR;
      case TKN_WR:
        return SgfcPropertyType::WR;
      case TKN_PC:
        return SgfcPropertyType::PC;
      case TKN_DT:
        return SgfcPropertyType::DT;
      case TKN_RE:
        return SgfcPropertyType::RE;
      case TKN_KM:
        return SgfcPropertyType::KM;
      case TKN_KI:
        return SgfcPropertyType::KI;
      case TKN_HA:
        return SgfcPropertyType::HA;
      case TKN_TM:
        return SgfcPropertyType::TM;
      case TKN_EV:
        return SgfcPropertyType::EV;
      case TKN_RO:
        return SgfcPropertyType::RO;
      case TKN_SO:
        return SgfcPropertyType::SO;
      case TKN_US:
        return SgfcPropertyType::US;
      case TKN_BT:
        return SgfcPropertyType::BT;
      case TKN_WT:
        return SgfcPropertyType::WT;
      case TKN_RU:
        return SgfcPropertyType::RU;
      case TKN_AN:
        return SgfcPropertyType::AN;
      case TKN_OT:
        return SgfcPropertyType::OT;
      case TKN_ON:
        return SgfcPropertyType::ON;
      case TKN_CP:
        return SgfcPropertyType::CP;
      case TKN_L:
        return SgfcPropertyType::L;
      case TKN_LB:
        return SgfcPropertyType::LB;
      case TKN_AR:
        return SgfcPropertyType::AR;
      case TKN_LN:
        return SgfcPropertyType::LN;
      case TKN_M:
        return SgfcPropertyType::M;
      case TKN_MA:
        return SgfcPropertyType::MA;
      case TKN_TR:
        return SgfcPropertyType::TR;
      case TKN_CR:
        return SgfcPropertyType::CR;
      case TKN_TB:
        return SgfcPropertyType::TB;
      case TKN_TW:
        return SgfcPropertyType::TW;
      case TKN_SQ:
        return SgfcPropertyType::SQ;
      case TKN_SL:
        return SgfcPropertyType::SL;
      case TKN_DD:
        return SgfcPropertyType::DD;
      case TKN_PL:
        return SgfcPropertyType::PL;
      case TKN_V:
        return SgfcPropertyType::V;
      case TKN_GB:
        return SgfcPropertyType::GB;
      case TKN_GW:
        return SgfcPropertyType::GW;
      case TKN_UC:
        return SgfcPropertyType::UC;
      case TKN_DM:
        return SgfcPropertyType::DM;
      case TKN_TE:
        return SgfcPropertyType::TE;
      case TKN_BM:
        return SgfcPropertyType::BM;
      case TKN_DO:
        return SgfcPropertyType::DO;
      case TKN_IT:
        return SgfcPropertyType::IT;
      case TKN_HO:
        return SgfcPropertyType::HO;
      case TKN_KO:
        return SgfcPropertyType::KO;
      case TKN_FG:
        return SgfcPropertyType::FG;
      case TKN_MN:
        return SgfcPropertyType::MN;
      case TKN_VW:
        return SgfcPropertyType::VW;
      case TKN_PM:
        return SgfcPropertyType::PM;
      case TKN_CH:
        return SgfcPropertyType::CH;
      case TKN_SI:
        return SgfcPropertyType::SI;
      case TKN_BS:
        return SgfcPropertyType::BS;
      case TKN_WS:
        return SgfcPropertyType::WS;
      case TKN_ID:
        return SgfcPropertyType::ID;
      case TKN_TC:
        return SgfcPropertyType::TC;
      case TKN_OM:
        return SgfcPropertyType::OM;
      case TKN_OP:
        return SgfcPropertyType::OP;
      case TKN_OV:
        return SgfcPropertyType::OV;
      case TKN_LT:
        return SgfcPropertyType::LT;
      case TKN_RG:
        return SgfcPropertyType::RG;
      case TKN_SC:
        return SgfcPropertyType::SC;
      case TKN_SE:
        return SgfcPropertyType::SE;
      case TKN_EL:
        return SgfcPropertyType::EL;
      case TKN_EX:
        return SgfcPropertyType::EX;
      default:
        std::stringstream message;
        message << "Unexpected SGFC token value: " << sgfProperty->id;
        throw std::logic_error(message.str());
    }
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
      for (const auto& propertyValue : property->GetPropertyValues())
      {
        std::cout << "      IsCompositeValue = " << propertyValue->IsComposedValue() << std::endl;
        if (propertyValue->IsComposedValue())
        {
          std::shared_ptr<ISgfcComposedPropertyValue> composedPropertyValue = propertyValue->ToComposedValue();
          std::cout << "      Value type 1 = " << static_cast<int>(composedPropertyValue->GetValue1()->GetValueType()) << std::endl;
          std::cout << "      Raw value 1 = " << composedPropertyValue->GetValue1()->GetRawValue() << std::endl;
          std::cout << "      Value type 2 = " << static_cast<int>(composedPropertyValue->GetValue2()->GetValueType()) << std::endl;
          std::cout << "      Raw value 2 = " << composedPropertyValue->GetValue2()->GetRawValue() << std::endl;

        }
        else
        {
          std::shared_ptr<ISgfcSinglePropertyValue> singlePropertyValue = propertyValue->ToSingleValue();
          std::cout << "      Value type= " << static_cast<int>(singlePropertyValue->GetValueType()) << std::endl;
          std::cout << "      Raw value= " << singlePropertyValue->GetRawValue() << std::endl;
        }
      }
    }
  }
}
