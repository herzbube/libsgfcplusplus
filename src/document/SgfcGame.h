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

#pragma once

// Project includes
#include "../../include/ISgfcGame.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGame class provides an implementation of the
  /// ISgfcGame interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup game-tree
  class SgfcGame : public ISgfcGame
  {
  public:
    /// @brief Initializes a newly constructed SgfcGame object. The game has
    /// no root node.
    SgfcGame();

    /// @brief Initializes a newly constructed SgfcGame object. The game has
    /// the specified root node @a rootNode.
    ///
    /// @exception std::invalid_argument Is thrown if @a rootNode is @e nullptr.
    SgfcGame(std::shared_ptr<ISgfcNode> rootNode);
    
    /// @brief Destroys and cleans up the SgfcGame object.
    virtual ~SgfcGame();

    virtual SgfcGameType GetGameType() const override;
    virtual SgfcNumber GetGameTypeAsNumber() const override;

    virtual bool HasBoardSize() const override;
    virtual SgfcBoardSize GetBoardSize() const override;

    virtual bool HasRootNode() const override;
    virtual std::shared_ptr<ISgfcNode> GetRootNode() const override;
    virtual void SetRootNode(std::shared_ptr<ISgfcNode> rootNode) override;

    virtual std::vector<std::shared_ptr<ISgfcNode>> GetGameInfoNodes() const override;

    virtual std::shared_ptr<ISgfcGameInfo> CreateGameInfo() const override;

    virtual std::shared_ptr<ISgfcTreeBuilder> GetTreeBuilder() const override;
    /// @brief Configures the SgfcGame object with @a treeBuilder, an object
    /// that can be used to manipulate the game tree.
    void SetTreeBuilder(std::shared_ptr<ISgfcTreeBuilder> treeBuilder);

  private:
    std::shared_ptr<ISgfcNode> rootNode;
    std::shared_ptr<ISgfcTreeBuilder> treeBuilder;
  };
}
