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
    if (this->rootNode == nullptr)
      return SgfcGameType::Unknown;

    auto property = this->rootNode->GetProperty(SgfcPropertyType::GM);
    if (property == nullptr)
      return SgfcGameType::Unknown;

    return property->ToGameTypeProperty()->GetGameType();
  }

  SgfcNumber SgfcGame::GetGameTypeAsNumber() const
  {
    // We can't base the implementation of this method on the return value of
    // GetGameType(), because this does allow us to distinguish between the two
    // cases 1) Property is not present; and 2) Property is present but has no
    // value.

    if (this->rootNode == nullptr)
      return SgfcConstants::GameTypeNone;

    auto property = this->rootNode->GetProperty(SgfcPropertyType::GM);
    if (property == nullptr)
      return SgfcConstants::GameTypeNone;

    return property->ToGameTypeProperty()->GetGameTypeAsNumber();
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
