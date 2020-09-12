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

    /// @brief Returns the game type found in the root node property of type
    /// SgfcPropertyType::GM, as an enumeration value.
    ///
    /// @retval SgfcGameType If the property is present and has a value defined
    ///         in the SGF standard, returns the SgfcGameType value that
    ///         corresponds to the property value. The value is guaranteed not
    ///         to be SgfcGameType::Unknown.
    /// @retval SgfcConstants::DefaultGameType If the property is not present,
    ///         or if the game has no root node, or if the property is present
    ///         but has no value (e.g. while the game tree is being set up
    ///         programmatically). The value is guaranteed not to be
    ///         SgfcGameType::Unknown.
    /// @retval SgfcGameType::Unknown If the property is present and has a value
    ///         that is not defined in the SGF standard. Invoke
    ///         GetGameTypeAsNumber() to obtain the game type as Number value.
    ///
    /// @exception std::logic_error Is thrown if a property object for
    /// SgfcPropertyType::GM is found in the game's root node, but the property
    /// object is not an instance of ISgfcGameTypeProperty.
    virtual SgfcGameType GetGameType() const = 0;

    /// @brief Returns the game type found in the root node property of type
    /// SgfcPropertyType::GM, as a Number value. This is useful if GetGameType()
    /// returns SgfcGameType::Unknown because the Number value is not defined
    /// in the SGF standard and cannot be mapped to a member of the enumeration
    /// SgfcGameType.
    ///
    /// @retval SgfcNumber The Number value of the root node's
    ///         SgfcPropertyType::GM property. If the property is not present,
    ///         or if the game has no root node, or if the property is present
    ///         but has no value (e.g. while the game tree is being set up
    ///         programmatically), this is the Number value that corresponds to
    ///         SgfcConstants::DefaultGameType.
    ///
    /// @exception std::logic_error Is thrown if a property object for
    /// SgfcPropertyType::GM is found in the game's root node, but the property
    /// object is not an instance of ISgfcGameTypeProperty.
    virtual SgfcNumber GetGameTypeAsNumber() const = 0;

    /// @brief Returns true if the game has a board size. Returns false if the
    /// game has no board size.
    ///
    /// The game has no board size if GetBoardSize() returns
    /// SgfcConstants::BoardSizeNone or SgfcConstants::BoardSizeInvalid.
    virtual bool HasBoardSize() const = 0;

    /// @brief Returns the board size found in the root node property of type
    /// SgfcPropertyType::SZ, as an SgfcBoardSize value.
    ///
    /// @retval SgfcBoardSize If the property is present and has a valid value.
    ///         The value is guaranteed not to be SgfcConstants::BoardSizeNone
    ///         nor SgfcConstants::BoardSizeInvalid.
    /// @retval SgfcConstants::BoardSizeDefaultGo If GetGameType() returns
    ///         SgfcGameType::Go and one of the following is true: The
    ///         property is not present, or the game has no root node, or the
    ///         property is present but has no value (e.g. while the game tree
    ///         is being set up programmatically).
    /// @retval SgfcConstants::BoardSizeDefaultChess If GetGameType() returns
    ///         SgfcGameType::Chess and one of the following is true: The
    ///         property is not present, or the game has no root node, or the
    ///         property is present but has no value (e.g. while the game tree
    ///         is being set up programmatically).
    /// @retval SgfcConstants::BoardSizeNone If GetGameType() returns
    ///         neither SgfcGameType::Go nor SgfcGameType::Chess and one of the
    ///         following is true: The property is not present, or the game has
    ///         no root node, or the property is present but has no value (e.g.
    ///         while the game tree is being set up programmatically).
    /// @retval SgfcConstants::BoardSizeInvalid If the property is present but
    ///         has an invalid value. A board size is invalid if it violates
    ///         the constraints defined by the SGF standard. See the
    ///         documentation of SgfcConstants::BoardSizeInvalid for details.
    ///
    /// @exception std::logic_error Is thrown if a property object for
    /// SgfcPropertyType::SZ is found in the game's root node, but the property
    /// object is not an instance of ISgfcBoardSizeProperty.
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
