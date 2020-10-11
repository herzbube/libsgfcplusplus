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
    if (rootNode == nullptr)
      throw std::invalid_argument("SgfcGame constructor failed: Root node is nullptr");
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
    return (boardSize != SgfcConstants::BoardSizeNone && boardSize != SgfcConstants::BoardSizeInvalid);
  }

  SgfcBoardSize SgfcGame::GetBoardSize() const
  {
    if (this->rootNode == nullptr)
      return SgfcUtility::GetDefaultBoardSize(this->GetGameType());

    auto property = this->rootNode->GetProperty(SgfcPropertyType::SZ);
    if (property == nullptr)
      return SgfcUtility::GetDefaultBoardSize(this->GetGameType());

    auto boardSizeProperty = property->ToBoardSizeProperty();
    if (boardSizeProperty == nullptr)
      throw std::logic_error("Property object for SgfcPropertyType::SZ is not an instance of ISgfcBoardSizeProperty");

    return boardSizeProperty->GetBoardSize(this->GetGameType());
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
