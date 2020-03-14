// Project includes
#include "../../include/ISgfcComposedPropertyValue.h"
#include "../../include/ISgfcNumberPropertyValue.h"
#include "../../include/ISgfcProperty.h"
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

  bool SgfcGame::HasBoardSize() const
  {
    SgfcBoardSize boardSize = GetBoardSize();
    return (boardSize != SgfcConstants::BoardSizeNone);
  }

  SgfcBoardSize SgfcGame::GetBoardSize() const
  {
    if (this->rootNode == nullptr)
      return SgfcConstants::BoardSizeNone;

    auto property = this->rootNode->GetProperty(SgfcPropertyType::SZ);
    if (property == nullptr)
      return SgfcConstants::BoardSizeNone;

    // We are interested only in the first value because the property is
    // supposed to have only one value.
    auto propertyValue = property->GetPropertyValue();
    if (propertyValue == nullptr)
    {
      switch (GetGameType())
      {
        case SgfcGameType::Go:
          return SgfcConstants::BoardSizeDefaultGo;
        case SgfcGameType::Chess:
          return SgfcConstants::BoardSizeDefaultChess;
        default:
          return SgfcConstants::BoardSizeNone;
      }
    }

    if (propertyValue->IsComposedValue())
    {
      const auto* composedValue = propertyValue->ToComposedValue();

      SgfcNumber numberOfColumns = -1;
      SgfcNumber numberOfRows = -1;

      auto singleValue1 = composedValue->GetValue1();
      if (singleValue1->HasTypedValue())
      {
        if (singleValue1->GetValueType() == SgfcPropertyValueType::Number)
          numberOfColumns = singleValue1->ToNumberValue()->GetNumberValue();
      }
      auto singleValue2 = composedValue->GetValue2();
      if (singleValue2->HasTypedValue())
      {
        if (singleValue2->GetValueType() == SgfcPropertyValueType::Number)
          numberOfRows = singleValue2->ToNumberValue()->GetNumberValue();
      }

      if (numberOfColumns != -1 && numberOfRows != -1)
        return { numberOfColumns, numberOfRows };
    }
    else
    {
      const auto* singleValue = propertyValue->ToSingleValue();
      if (singleValue->HasTypedValue())
      {
        if (singleValue->GetValueType() == SgfcPropertyValueType::Number)
        {
          SgfcNumber numberOfColumnsAndRows = singleValue->ToNumberValue()->GetNumberValue();
          return { numberOfColumnsAndRows, numberOfColumnsAndRows };
        }
      }
    }

    return SgfcConstants::BoardSizeNone;
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
