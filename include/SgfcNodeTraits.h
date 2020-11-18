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

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

/// @brief file

namespace LibSgfcPlusPlus
{
  /// @brief An SgfcNodeTraits value describes the traits of an
  /// ISgfcNode object. The value is a combination of individual flags
  /// defined in the SgfcNodeTrait enumeration.
  ///
  /// @ingroup public-api
  ///
  /// All bitwise operators have been overloaded to make the SgfcNodeTraits
  /// typedef interoperate with the SgfcNodeTrait enumeration as
  /// conveniently as possible. There are some limitations, though, because
  /// SgfcNodeTraits is a typedef and not a true type (i.e. it's not a
  /// class or struct). For instance, the assignment operator cannot be
  /// overloaded so it's not possible to assign an SgfcNodeTrait enumeration
  /// member directly to an SgfcNodeTraits variable. Consequently, whenever
  /// SgfcNodeTrait (the enum type) needs to be treated interchangeably with
  /// SgfcNodeTraits (the typdef) a static_cast must be done. This works
  /// because SgfcNodeTraits (the typedef) is used as the underlying type
  /// of SgfcNodeTrait (the enum type).
  ///
  /// @verbatim
  /// SgfcNodeTraits traits = static_cast<SgfcNodeTraits>(SgfcNodeTrait::Inheritable);
  /// @endverbatim
  ///
  /// @see SgfcConstants::NodeTraitsNone
  /// @see SgfcConstants::NodeTraitsAll
  ///
  /// @note Using an unsigned numerical type as the underlying type of this
  /// typedef is important to make the bitwise operators, specifically the
  /// shift left and shift right operators, unambiguous and safe to use.
  typedef unsigned long long SgfcNodeTraits;

  /// @brief SgfcNodeTrait enumerates the individual traits that an
  /// ISgfcNode object can have. An ISgfcNode object can have several
  /// traits, which is why the enumeration values are defined as flags that can
  /// be combined into a single SgfcNodeTraits value.
  ///
  /// @ingroup public-api
  ///
  /// @see SgfcConstants::NodeTraitsNone
  /// @see SgfcConstants::NodeTraitsAll
  enum class SGFCPLUSPLUS_EXPORT SgfcNodeTrait : SgfcNodeTraits
  {
    /// @brief The node is a root node. Root nodes are nodes that are at the
    /// root of a tree of nodes, i.e. which have no parent node.
    ///
    /// As per the SGF standard, root properties can be stored only in root
    /// nodes. A root property is a property that is classified as
    /// SgfcPropertyCategory::Root.
    Root = 1ULL,

    /// @brief The node is a game info node. Game info nodes are nodes that
    /// contain one or more game info properties. A game info property is a
    /// property that is classified as SgfcPropertyCategory::GameInfo.
    ///
    /// As per the SGF standard, game info properties are usually (but not
    /// always) stored in root nodes. A root node is a node that has the trait
    /// SgfcNodeTrait::Root. When several game trees are located below a common
    /// root node, game info properties are stored in the nodes where a game
    /// first becomes distinguishable from all other games in the tree.
    ///
    /// As per the SGF standard, there may be only one game info node on any
    /// path within a tree of nodes, i.e. if some game info properties occur in
    /// one node there may not be any further game info properties in the
    /// following nodes:
    /// - On the path from the root node to this node.
    /// - In the subtree below this node.
    ///
    /// libsgfc++ does not enforce this rule from the SGF standard, but it uses
    /// the rule in certain parts of its implementation, such as when an
    /// ISgfcGame is queried for game info nodes.
    GameInfo = 2ULL,

    /// @brief The node is a move node. Move nodes are nodes that contain one
    /// or more move properties. A move property is a property that is
    /// classified as SgfcPropertyCategory::Move.
    ///
    /// As per the SGF standard, move properties must not be mixed with setup
    /// properties within the same node. In theory a node can therefore not have
    /// both traits SgfcNodeTrait::Move and SgfcNodeTrait::Setup at the same
    /// time. In practice libsgfc++ does not enforce the SGF standard rule.
    ///
    /// As per the SGF standard, it's bad style to have move properties in
    /// root nodes, although it isn't forbidden. Ideally a node should therefore
    /// not have both traits SgfcNodeTrait::Move and SgfcNodeTrait::Root at the
    /// same time.
    Move = 4ULL,

    /// @brief The node is a setup node. Setup nodes are nodes that contain one
    /// or more setup properties. A setup property is a property that is
    /// classified as SgfcPropertyCategory::Setup.
    ///
    /// As per the SGF standard, setup properties must not be mixed with move
    /// properties within the same node. In theory a node can therefore not have
    /// both traits SgfcNodeTrait::Setup and SgfcNodeTrait::Move at the same
    /// time. In practice libsgfc++ does not enforce the SGF standard rule.
    Setup = 8ULL,

    /// @brief The node contains one or more properties that are classified as
    /// SgfcPropertyCategory::NodeAnnotation.
    NodeAnnotation = 16ULL,

    /// @brief The node contains one or more properties that are classified as
    /// SgfcPropertyCategory::MoveAnnotation.
    ///
    /// A node with this trait should also have the trait SgfcNodeTrait::Move.
    MoveAnnotation = 32ULL,

    /// @brief The node contains one or more properties that are classified as
    /// SgfcPropertyCategory::Markup.
    Markup = 64ULL,

    /// @brief The node contains one or more properties that are classified as
    /// SgfcPropertyCategory::Timing.
    Timing = 128ULL,

    /// @brief The node contains one or more properties with the trait
    /// SgfcPropertyTrait::Inheritable.
    Inheritable = 256ULL,
  };

  /// @name Bitwise AND operators
  //@{
  /// @brief Bitwise AND operator, applying the right-hand-side trait operand
  /// @a rhs to the left-hand-side traits operand @a lhs.
  SgfcNodeTraits operator&(SgfcNodeTraits lhs, SgfcNodeTrait rhs);
  /// @brief Bitwise AND operator, combining the left-hand-side trait operand
  /// @a lhs with the right-hand-side trait operand @ rhs.
  ///
  /// This operator does not make much sense - the result will always be
  /// SgfcConstants::NodeTraitsNone
  SgfcNodeTraits operator&(SgfcNodeTrait lhs, SgfcNodeTrait rhs);
  /// @brief Bitwise AND compound assignment operator, applying the
  /// right-hand-side trait operand @a rhs to the left-hand-side traits
  /// operand @a lhs.
  SgfcNodeTraits& operator&=(SgfcNodeTraits& lhs, SgfcNodeTrait rhs);
  //@}

  /// @name Bitwise OR operators
  //@{
  /// @brief Bitwise OR operator, applying the right-hand-side trait operand
  /// @a rhs to the left-hand-side traits operand @a lhs.
  SgfcNodeTraits operator|(SgfcNodeTraits lhs, SgfcNodeTrait rhs);
  /// @brief Bitwise OR operator, combining the left-hand-side trait operand
  /// @a lhs with the right-hand-side trait operand @ rhs.
  SgfcNodeTraits operator|(SgfcNodeTrait lhs, SgfcNodeTrait rhs);
  /// @brief Bitwise OR compound assignment operator, applying the
  /// right-hand-side trait operand @a rhs to the left-hand-side traits
  /// operand @a lhs.
  SgfcNodeTraits& operator|=(SgfcNodeTraits& lhs, SgfcNodeTrait rhs);
  //@}

  /// @name Bitwise XOR operators
  //@{
  /// @brief Bitwise XOR operator, applying the right-hand-side trait operand
  /// @a rhs to the left-hand-side traits operand @a lhs.
  SgfcNodeTraits operator^(SgfcNodeTraits lhs, SgfcNodeTrait rhs);
  /// @brief Bitwise XOR operator, combining the left-hand-side trait operand
  /// @a lhs with the right-hand-side trait operand @ rhs.
  ///
  /// This operator does not make much sense - the result will always be
  /// SgfcConstants::NodeTraitsNone
  SgfcNodeTraits operator^(SgfcNodeTrait lhs, SgfcNodeTrait rhs);
  /// @brief Bitwise XOR compound assignment operator, applying the
  /// right-hand-side trait operand @a rhs to the left-hand-side traits
  /// operand @a lhs.
  SgfcNodeTraits& operator^=(SgfcNodeTraits& lhs, SgfcNodeTrait rhs);
  //@}

  /// @name Bitwise shift operators
  //@{
  /// @brief Bitwise left shift operator, shifting the left-hand-side traits
  /// operand @a lhs by the number of bits in the right-hand-side operand
  /// @a numberOfBitsToShift.
  SgfcNodeTraits operator<<(SgfcNodeTrait lhs, unsigned short numberOfBitsToShift);

  /// @brief Bitwise right shift operator, shifting the left-hand-side traits
  /// operand @a lhs by the number of bits in the right-hand-side operand
  /// @a numberOfBitsToShift.
  SgfcNodeTraits operator>>(SgfcNodeTrait lhs, unsigned short numberOfBitsToShift);
  //@}

  /// @name Other bitwise operators
  //@{
  /// @brief Bitwise NOT operator, flipping all bits of the right-hand-side
  /// trait operand @a rhs.
  SgfcNodeTraits operator~(SgfcNodeTrait rhs);
  //@}
}
