#pragma once

// Project includes
#include "ISgfcNode.h"
#include "SgfcGameType.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcGame interface provides access to the data of one SGF
  /// game, in the form of a tree of ISgfcNode objects. Each branch in the tree
  /// is a variation in game play. A tree without branches is a game without
  /// variations.
  class ISgfcGame
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGame object.
    ISgfcGame();

    /// @brief Destroys and cleans up the ISgfcGame object.
    virtual ~ISgfcGame();

    /// @brief Returns the game type.
    virtual SgfcGameType GetGameType() const = 0;

    /// @brief Returns the game tree's root node.
    virtual std::shared_ptr<ISgfcNode> GetRootNode() const = 0;

    /// @brief Sets the game tree's root node to @a rootNode. The previous
    /// root node, and with it the entire previous game tree, is discarded.
    virtual void SetRootNode(std::shared_ptr<ISgfcNode> rootNode) = 0;
  };
}
