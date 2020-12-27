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
#include "ISgfcNode.h"
#include "SgfcBoardSize.h"
#include "SgfcGameType.h"
#include "SgfcTypedefs.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcGameInfo;
  class ISgfcTreeBuilder;

  /// @brief The ISgfcGame interface provides access to the data of one SGF
  /// game tree, in the form of a tree of ISgfcNode objects.
  ///
  /// @ingroup public-api
  /// @ingroup game-tree
  ///
  /// Each branch in the game tree is either a separate game, or a variation in
  /// game play for its parent game. A tree without branches is a single game
  /// without variations.
  ///
  /// A list of games can be obtained by invoking GetGameInfoNodes().
  ///
  /// According to the SGF standard, the game tree's root node must contain
  /// root properties, which are used to define some global "attributes" that
  /// affect all games. Notably these include the game type and the board size.
  /// This means that if a game tree contains multiple games, all of them must
  /// have the same game type and the same board size.
  class SGFCPLUSPLUS_EXPORT ISgfcGame
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGame object.
    ISgfcGame();

    /// @brief Destroys and cleans up the ISgfcGame object.
    virtual ~ISgfcGame();

    /// @brief Returns the property value(s) found in the root node property of
    /// type SgfcPropertyType::GM, interpreted as an SgfcGameType value.
    ///
    /// @retval SgfcGameType If the property is present and has a single Number
    ///         value, and that value is defined in the SGF standard, then the
    ///         SgfcGameType value that corresponds to the Number value is
    ///         returned. The value is guaranteed not to be
    ///         SgfcGameType::Unknown.
    /// @retval SgfcConstants::DefaultGameType If the property is not present,
    ///         or if the game has no root node, or if the property is present
    ///         but has no value. The value is guaranteed not to be
    ///         SgfcGameType::Unknown.
    /// @retval SgfcGameType::Unknown If the property is present but its
    ///         value(s) cannot be converted to a Number value (the property
    ///         has more than one value, or the single value is not a Number
    ///         value), or if conversion is possible but the Number value is
    ///         not defined in the SGF standard. Invoke GetGameTypeAsNumber()
    ///         to obtain the game type as Number value.
    virtual SgfcGameType GetGameType() const = 0;

    /// @brief Returns the property value(s) found in the root node property of
    /// type SgfcPropertyType::GM, as an SgfcNumber value.
    ///
    /// This is useful if GetGameType() returns SgfcGameType::Unknown because
    /// the Number value is not defined in the SGF standard and cannot be
    /// mapped to a member of the enumeration SgfcGameType.
    ///
    /// @retval SgfcNumber If the property is present and contains a single
    ///         Number value, then that Number value is returned. If the
    ///         property is not present, or if the game has no root node, or if
    ///         the property is present but has no value, then this method
    ///         returns the Number value that corresponds to
    ///         SgfcConstants::DefaultGameType.
    /// @retval SgfcConstants::GameTypeNaN If the property is present but its
    ///         value(s) cannot be converted to a Number value, either because
    ///         the property has more than one value, or its single value is
    ///         not a Number value.
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
    ///         SgfcGameType::Go and one of the following is true: The game has
    ///         no root node, or the game has a root node but the property is
    ///         not present, or the game has a root node and the property is
    ///         present but has no value (e.g. while the game tree is being set
    ///         up programmatically).
    /// @retval SgfcConstants::BoardSizeDefaultChess If GetGameType() returns
    ///         SgfcGameType::Chess and one of the following is true: The game
    ///         has a root node but the property is not present, or the game has
    ///         a root node and the property is present but has no value (e.g.
    ///         while the game tree is being set up programmatically).
    /// @retval SgfcConstants::BoardSizeNone If GetGameType() returns neither
    ///         SgfcGameType::Go nor SgfcGameType::Chess (these are the two game
    ///         types for which the SGF standard defines a default board size)
    ///         and one of the following is true: The game has a root node but
    ///         the property is not present, or the game has a root node and the
    ///         property is present but has no value (e.g. while the game tree
    ///         is being set up programmatically).
    /// @retval SgfcConstants::BoardSizeInvalid If the property is present but
    ///         either its property value(s) cannot be converted to an
    ///         SgfcBoardSize value (the property has more than one value, or
    ///         it has a single value that is neither a Number nor a composed
    ///         value consisting of two Number values), or if conversion is
    ///         possible but the SgfcBoardSize value violates the constraints
    ///         defined by the SGF standard. See the documentation of
    ///         SgfcConstants::BoardSizeInvalid for details.
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

    /// @brief Returns the game tree's game info nodes. Returns an empty list
    /// if the game tree has no game info nodes.
    ///
    /// This is a convenience method that searches the game tree's nodes on
    /// behalf of the caller and returns the result. The search logic is this:
    /// - Starting with the root node every node is examined whether it contains
    ///   one or more game info properties. These are properties that are
    ///   classified as SgfcPropertyCategory::GameInfo.
    /// - When a node contains at least one game info property it is
    ///   considered to be a game info node and included in the search result
    ///   returned by the method.
    /// - The search does not continue below a game info node. This is because
    ///   the SGF standard mandates that there may be only one game info node
    ///   on any path within a tree of nodes. If the root node contains at
    ///   least one game info property, the search result will therefore contain
    ///   only the root node. Since game info properties are usually stored in
    ///   the root node this is actually the expected outcome for most of the
    ///   SGF content out there.
    /// - The search is performed depth-first.
    ///
    /// @see SgfcNodeTraits::GameInfo
    virtual std::vector<std::shared_ptr<ISgfcNode>> GetGameInfoNodes() const = 0;

    /// @brief Returns a newly constructed ISgfcGameInfo object with values
    /// taken from the properties in the root node that GetRootNode() returns
    /// and the first game info node in the list of game info nodes returned by
    /// GetGameInfoNodes().
    ///
    /// This is a convenience method that is useful if a game contains only one
    /// game tree (GetGameInfoNodes() returns only one game info node). If the
    /// game contains more than one game tree, an ISgfcGameInfo object that
    /// describes the second, third, etc. game tree can be obtained by invoking
    /// ISgfcNode::CreateGameInfo() on the second, third, etc. game info nodes
    /// returned by GetGameInfoNodes().
    ///
    /// If the game has no game trees (GetGameInfoNodes() returns an empty list)
    /// then the ISgfcGameInfo object returned by this method contains only
    /// values taken from the properties in the root node, but all values that
    /// would normally be taken from the properties in the game info node have
    /// default values.
    ///
    /// If the game has no root node (HasRootNode() returns false) then the
    /// ISgfcGameInfo object contains default values.
    ///
    /// If GetGameType() returns #SgfcGameType::Go then the returned object is
    /// an ISgfcGoGameInfo object.
    ///
    /// @see ISgfcNode::CreateGameInfo()
    virtual std::shared_ptr<ISgfcGameInfo> CreateGameInfo() const = 0;

    /// @brief Writes all root property values in @a gameInfo to the
    /// corresponding properties in the root node that GetRootNode() returns,
    /// and all game info property values in @a gameInfo to the first game
    /// info node in the list of game info nodes returned by GetGameInfoNodes().
    ///
    /// This is a convenience method that is useful if a game contains only one
    /// game tree (GetGameInfoNodes() returns only one game info node). If the
    /// game contains more than one game tree, then ISgfcNode::WriteGameInfo()
    /// can be invoked to write the content of @a gameInfo to the second, third,
    /// etc. game info nodes returned by GetGameInfoNodes().
    ///
    /// If the game has no game trees (GetGameInfoNodes() returns an empty list)
    /// then the game info property values in @a gameInfo are written to the
    /// root node that GetRootNode() returns.
    ///
    /// If the game has no root node (HasRootNode() returns false) then a new
    /// root node is created and all property values in @a gameInfo are written
    /// to the new node.
    ///
    /// Game info property values are written only if they are not equal to
    /// their default values (already existing property values are overwritten).
    /// Game info property values that are equal to their default value cause
    /// the property to be removed, if it exists, from the game info node.
    ///
    /// Root property values are always written, regardless of whether they
    /// are equal to their default values.
    ///
    /// @exception std::invalid_argument Is thrown if @a gameInfo is @e nullptr.
    virtual void WriteGameInfo(std::shared_ptr<ISgfcGameInfo> gameInfo) = 0;

    /// @brief Returns an ISgfcTreeBuilder object that can be used to
    /// manipulate the game tree.
    virtual std::shared_ptr<ISgfcTreeBuilder> GetTreeBuilder() const = 0;
  };
}
