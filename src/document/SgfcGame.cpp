// Project includes
#include "../../include/ISgfcBoardSizeProperty.h"
#include "../../include/ISgfcComposedPropertyValue.h"
#include "../../include/ISgfcGameTypeProperty.h"
#include "../../include/ISgfcNumberPropertyValue.h"
#include "../../include/ISgfcProperty.h"
#include "../../include/ISgfcSinglePropertyValue.h"
#include "../../include/SgfcConstants.h"
#include "../SgfcUtility.h"
#include "SgfcGame.h"

namespace LibSgfcPlusPlus
{
  SgfcGame::SgfcGame()
    : rootNode(nullptr)
    , treeBuilder(nullptr)
  {
  }

  SgfcGame::SgfcGame(std::shared_ptr<ISgfcNode> rootNode)
    : rootNode(rootNode)
    , treeBuilder(nullptr)
  {
  }

  SgfcGame::~SgfcGame()
  {
  }

  SgfcGameType SgfcGame::GetGameType() const
  {
    auto gameTypeAsNumber = GetGameTypeAsNumber();

    return SgfcUtility::MapNumberValueToGameType(
      gameTypeAsNumber);
  }

  SgfcNumber SgfcGame::GetGameTypeAsNumber() const
  {
    if (this->rootNode == nullptr)
      return SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType);

    auto property = this->rootNode->GetProperty(SgfcPropertyType::GM);
    if (property == nullptr)
      return SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType);

    auto gameTypeProperty = property->ToGameTypeProperty();
    if (gameTypeProperty == nullptr)
      throw std::logic_error("Property object for SgfcPropertyType::GM is not an instance of ISgfcGameTypeProperty");

    return gameTypeProperty->GetGameTypeAsNumber();
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

    return property->ToBoardSizeProperty()->GetBoardSize(this->GetGameType());
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
