#pragma once

// Project includes
#include "ISgfcNode.h"
#include "SgfcGameType.h"
#include "SgfcTypedefs.h"

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

    /// @brief Returns true if the game has a game type. Returns false if the
    /// game has no game type.
    ///
    /// The game has no game type if GetGameTypeAsNumber() returns
    /// SgfcConstants::GameTypeNone.
    virtual bool HasGameType() const = 0;

    /// @brief Returns the game type found in the root node property of type
    /// SgfcPropertyType::GM, as an enumeration value.
    ///
    /// @retval SgfcGameType If the property is present and has a value defined
    ///         in the SGF standard, returns the SgfcGameType value that
    ///         corresponds to the property value. The value is guaranteed not
    ///         to be SgfcGameType::Unknown.
    /// @retval SgfcConstants::DefaultGameType If the property is present and
    ///         has no value. The value is guaranteed not to be
    ///         SgfcGameType::Unknown.
    /// @retval SgfcGameType::Unknown If the property is present and has a value
    ///         that is not defined in the SGF standard, or if the property is
    ///         not present, or if the game has no root node.
    virtual SgfcGameType GetGameType() const = 0;

    /// @brief Returns the game type found in the root node property of type
    /// SgfcPropertyType::GM, as a Number value. This is useful if GetGameType()
    /// returns SgfcGameType::Unknown.
    ///
    /// @retval SgfcNumber The Number value of the root node's
    ///         SgfcPropertyType::GM property
    /// @retval SgfcConstants::GameTypeNone If the property is not present in
    ///         the root node, or if the game has no root node.
    virtual SgfcNumber GetGameTypeAsNumber() const = 0;

    /// @brief Returns true if the game has a root node. Returns false if the
    /// game has no root node.
    virtual bool HasRootNode() const = 0;

    /// @brief Returns the game tree's root node. Returns @e nullptr if
    /// HasRootNode() returns false.
    virtual std::shared_ptr<ISgfcNode> GetRootNode() const = 0;

    /// @brief Sets the game tree's root node to @a rootNode. The previous
    /// root node, and with it the entire previous game tree, is discarded.
    virtual void SetRootNode(std::shared_ptr<ISgfcNode> rootNode) = 0;
  };
}
