// Project includes
#include "../../include/ISgfcProperty.h"
#include "../../include/ISgfcNumberPropertyValue.h"
#include "../../include/ISgfcSinglePropertyValue.h"
#include "../../include/SgfcConstants.h"
#include "../parsing/SgfcPropertyDecoder.h"
#include "SgfcGame.h"

namespace LibSgfcPlusPlus
{
  SgfcGame::SgfcGame()
    : gameType(SgfcGameType::Unknown)
    , rootNode(nullptr)
    , treeBuilder(nullptr)
  {
  }

  SgfcGame::SgfcGame(std::shared_ptr<ISgfcNode> rootNode)
    : gameType(SgfcGameType::Unknown)
    , rootNode(rootNode)
    , treeBuilder(nullptr)
  {
  }

  SgfcGame::~SgfcGame()
  {
  }

  bool SgfcGame::HasGameType() const
  {
    SgfcNumber gameTypeAsNumber = GetGameTypeAsNumber();
    return (gameTypeAsNumber != SgfcConstants::GameTypeNone);
  }

  SgfcGameType SgfcGame::GetGameType() const
  {
    SgfcNumber gameTypeAsNumber = GetGameTypeAsNumber();

    if (gameTypeAsNumber == SgfcConstants::GameTypeNone)
      return SgfcGameType::Unknown;

    return SgfcPropertyDecoder::MapNumberValueToGameType(gameTypeAsNumber);
  }

  SgfcNumber SgfcGame::GetGameTypeAsNumber() const
  {
    if (this->rootNode == nullptr)
      return SgfcConstants::GameTypeNone;

    auto property = this->rootNode->GetProperty(SgfcPropertyType::GM);
    if (property == nullptr)
      return SgfcConstants::GameTypeNone;

    // We are interested only in the first value because the property is
    // supposed to have only one value.
    auto propertyValue = property->GetPropertyValue();
    if (propertyValue == nullptr || propertyValue->IsComposedValue())
      return SgfcConstants::GameTypeNone;

    const auto* singleValue = propertyValue->ToSingleValue();
    if (singleValue->HasTypedValue() && singleValue->GetValueType() == SgfcPropertyValueType::Number)
      return singleValue->ToNumberValue()->GetNumberValue();
    else
      return SgfcConstants::GameTypeNone;
  }

  bool SgfcGame::HasRootNode() const
  {
    return (this->rootNode != nullptr);
  }

  std::shared_ptr<ISgfcNode> SgfcGame::GetRootNode() const
  {
    return this->rootNode;
  }

  void SgfcGame::SetRootNode(std::shared_ptr<ISgfcNode> rootNode)
  {
    this->rootNode = rootNode;
  }

  std::shared_ptr<ISgfcTreeBuilder> SgfcGame::GetTreeBuilder() const
  {
    return this->treeBuilder;
  }

  void SgfcGame::SetTreeBuilder(std::shared_ptr<ISgfcTreeBuilder> treeBuilder)
  {
    this->treeBuilder = treeBuilder;
  }
}
