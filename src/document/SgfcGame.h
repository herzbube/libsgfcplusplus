#pragma once

// Project includes
#include "../../include/ISgfcGame.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGame class provides an implementation of the
  /// ISgfcGame interface. See the interface header file for
  /// documentation.
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

    virtual SgfcGameType GetGameType() const;
    virtual SgfcNumber GetGameTypeAsNumber() const;

    virtual bool HasBoardSize() const;
    virtual SgfcBoardSize GetBoardSize() const;

    virtual bool HasRootNode() const;
    virtual std::shared_ptr<ISgfcNode> GetRootNode() const;
    virtual void SetRootNode(std::shared_ptr<ISgfcNode> rootNode);

    virtual std::shared_ptr<ISgfcTreeBuilder> GetTreeBuilder() const;
    /// @brief Configures the SgfcGame object with @a treeBuilder, an object
    /// that can be used to manipulate the game tree.
    void SetTreeBuilder(std::shared_ptr<ISgfcTreeBuilder> treeBuilder);

  private:
    std::shared_ptr<ISgfcNode> rootNode;
    std::shared_ptr<ISgfcTreeBuilder> treeBuilder;
  };
}
