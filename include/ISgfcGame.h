#pragma once

// Project includes
#include "ISgfcNode.h"
#include "SgfcBoardSize.h"
#include "SgfcGameType.h"
#include "SgfcTypedefs.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcTreeBuilder;

  /// @brief The ISgfcGame interface provides access to the data of one SGF
  /// game, in the form of a tree of ISgfcNode objects. Each branch in the tree
  /// is a variation in game play. A tree without branches is a game without
  /// variations.
  class SGFCPLUSPLUS_EXPORT ISgfcGame
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
    ///         SgfcPropertyType::GM property. If the property has no value,
    ///         returns the Number value that corresponds to
    ///         SgfcConstants::DefaultGameType.
    /// @retval SgfcConstants::GameTypeNone If the property is not present in
    ///         the root node, or if the game has no root node.
    virtual SgfcNumber GetGameTypeAsNumber() const = 0;

    /// @brief Returns true if the game has a board size. Returns false if the
    /// game has no board size.
    ///
    /// The game has no board size if GetBoardSize() returns
    /// SgfcConstants::BoardSizeNone.
    virtual bool HasBoardSize() const = 0;

    /// @brief Returns the board size found in the root node property of type
    /// SgfcPropertyType::SZ, as an SgfcBoardSize value. Returns a game-specific
    /// default board size for a few game types mentioned in the SGF standard
    /// if the property is present but has no value.
    ///
    /// @retval SgfcBoardSize If the property is present and has a valid value.
    ///         The value is guaranteed not to be SgfcConstants::BoardSizeNone.
    /// @retval SgfcConstants::DefaultBoardSizeGo If the property is present
    ///         and has no value, and GetGameType() returns SgfcGameType::Go.
    /// @retval SgfcConstants::DefaultBoardSizeChess If the property is present
    ///         and has no value, and GetGameType() returns SgfcGameType::Chess.
    /// @retval SgfcConstants::BoardSizeNone If the property is not present, or
    ///         if the game has no root node. Also if the property is present
    ///         and has no value, but GetGameType() returns neither
    ///         SgfcGameType::Go nor SgfcGameType::Chess.
    virtual SgfcBoardSize GetBoardSize() const = 0;

    /// @brief Returns true if the game has a root node. Returns false if the
    /// game has no root node.
    virtual bool HasRootNode() const = 0;

    /// @brief Returns the game tree's root node. Returns @e nullptr if
    /// HasRootNode() returns false.
    virtual std::shared_ptr<ISgfcNode> GetRootNode() const = 0;

    /// @brief Sets the game tree's root node to @a rootNode. The previous
    /// root node, and with it the entire previous game tree, is discarded.
    virtual void SetRootNode(std::shared_ptr<ISgfcNode> rootNode) = 0;

    /// @brief Returns an ISgfcTreeBuilder object that can be used to
    /// manipulate the game tree.
    virtual std::shared_ptr<ISgfcTreeBuilder> GetTreeBuilder() const = 0;
  };
}
