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
#include "../../include/ISgfcGameTypeProperty.h"
#include "../../include/ISgfcGoGameInfo.h"
#include "../../include/ISgfcNumberPropertyValue.h"
#include "../../include/ISgfcProperty.h"
#include "../../include/ISgfcSinglePropertyValue.h"
#include "../../include/SgfcConstants.h"
#include "../../include/SgfcPlusPlusFactory.h"
#include "../game/SgfcGameInfo.h"
#include "../game/SgfcGameUtility.h"
#include "../SgfcUtility.h"
#include "SgfcGame.h"
#include "SgfcNodeIterator.h"

// C++ Standard Library includes
#include <stdexcept>

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

    return SgfcGameUtility::GetGameTypeAsNumber(property->GetPropertyValues());
  }

  bool SgfcGame::HasBoardSize() const
  {
    SgfcBoardSize boardSize = GetBoardSize();
    return (boardSize != SgfcConstants::BoardSizeNone && boardSize != SgfcConstants::BoardSizeInvalid);
  }

  SgfcBoardSize SgfcGame::GetBoardSize() const
  {
    if (this->rootNode == nullptr)
      return SgfcBoardSize::GetDefaultBoardSize(this->GetGameType());

    auto property = this->rootNode->GetProperty(SgfcPropertyType::SZ);
    if (property == nullptr)
      return SgfcBoardSize::GetDefaultBoardSize(this->GetGameType());

    return SgfcGameUtility::GetBoardSize(property->GetPropertyValues(), this->GetGameType());
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

  std::vector<std::shared_ptr<ISgfcNode>> SgfcGame::GetGameInfoNodes() const
  {
    std::vector<std::shared_ptr<ISgfcNode>> gameInfoNodes;

    NodeVisitCallback nodeVisitCallback = [&gameInfoNodes](std::shared_ptr<ISgfcNode> node) -> SgfcNodeIterationContinuation
    {
      if (node->HasTrait(SgfcNodeTrait::GameInfo))
      {
        gameInfoNodes.push_back(node);
        return SgfcNodeIterationContinuation::Lateral;
      }
      else
      {
        return SgfcNodeIterationContinuation::VerticalAndLateral;
      }
    };

    SgfcNodeIterator nodeIterator;
    nodeIterator.IterateOverNodesDepthFirst(this->rootNode, nodeVisitCallback);

    return gameInfoNodes;
  }

  std::shared_ptr<ISgfcGameInfo> SgfcGame::CreateGameInfo() const
  {
    std::shared_ptr<ISgfcNode> firstGameInfoNode = GetFirstGameInfoNode();

    if (this->rootNode == nullptr)
      return SgfcPlusPlusFactory::CreateGameInfo();
    else if (firstGameInfoNode == nullptr)
      return SgfcPlusPlusFactory::CreateGameInfo(this->rootNode);
    else
      return SgfcPlusPlusFactory::CreateGameInfo(this->rootNode, firstGameInfoNode);
  }

  void SgfcGame::WriteGameInfo(std::shared_ptr<ISgfcGameInfo> gameInfo)
  {
    if (gameInfo == nullptr)
      throw std::invalid_argument("WriteGameInfo failed: Game info object is nullptr");

    std::shared_ptr<ISgfcNode> firstGameInfoNode;
    if (this->rootNode == nullptr)
    {
      this->rootNode = SgfcPlusPlusFactory::CreateNode();
      firstGameInfoNode = this->rootNode;
    }
    else
    {
      firstGameInfoNode = GetFirstGameInfoNode();
    }

    auto gameInfoImplementation = std::dynamic_pointer_cast<SgfcGameInfo>(gameInfo);
    gameInfoImplementation->WriteToRootNode(this->rootNode);
    gameInfoImplementation->WriteToGameInfoNode(firstGameInfoNode);
  }

  std::shared_ptr<ISgfcTreeBuilder> SgfcGame::GetTreeBuilder() const
  {
    return this->treeBuilder;
  }

  void SgfcGame::SetTreeBuilder(std::shared_ptr<ISgfcTreeBuilder> treeBuilder)
  {
    this->treeBuilder = treeBuilder;
  }

  std::shared_ptr<ISgfcNode> SgfcGame::GetFirstGameInfoNode() const
  {
    std::shared_ptr<ISgfcNode> firstGameInfoNode = nullptr;

    NodeVisitCallback nodeVisitCallback = [&firstGameInfoNode](std::shared_ptr<ISgfcNode> node) -> SgfcNodeIterationContinuation
    {
      if (node->HasTrait(SgfcNodeTrait::GameInfo))
      {
        firstGameInfoNode = node;
        return SgfcNodeIterationContinuation::Stop;
      }
      else
      {
        return SgfcNodeIterationContinuation::VerticalAndLateral;
      }
    };

    SgfcNodeIterator nodeIterator;
    nodeIterator.IterateOverNodesDepthFirst(this->rootNode, nodeVisitCallback);

    return firstGameInfoNode;
  }
}
