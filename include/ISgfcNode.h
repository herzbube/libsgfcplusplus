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
#include "ISgfcProperty.h"
#include "SgfcNodeTraits.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcNode interface provides access to the data of a single
  /// SGF node in a tree of SGF nodes. ISgfcNode also provides methods to
  /// navigate the game tree. ISgfcNode provides no methods to manipulate the
  /// game tree - use ISgfcTreeBuilder for that purpose.
  ///
  /// @ingroup public-api
  /// @ingroup game-tree
  class SGFCPLUSPLUS_EXPORT ISgfcNode
  {
  public:
    /// @brief Initializes a newly constructed ISgfcNode object.
    ISgfcNode();

    /// @brief Destroys and cleans up the ISgfcNode object.
    virtual ~ISgfcNode();

    /// @brief Returns the node's first child node. Returns @e nullptr if
    /// the node has no children.
    virtual std::shared_ptr<ISgfcNode> GetFirstChild() const = 0;

    /// @name Game tree navigation
    //@{
    /// @brief Returns the node's last child node. Returns @e nullptr if
    /// the node has no children.
    virtual std::shared_ptr<ISgfcNode> GetLastChild() const = 0;

    /// @brief Returns a collection of child nodes of the node. The collection
    /// is ordered, beginning with the first child node and ending with the
    /// last child node. The collection is empty if the node has no children.
    virtual std::vector<std::shared_ptr<ISgfcNode>> GetChildren() const = 0;

    /// @brief Returns true if the node has one or more children. Returns
    /// false if the node has no children.
    virtual bool HasChildren() const = 0;

    /// @brief Returns the node's next sibling node. Returns @e nullptr if
    /// the node has no next sibling node, i.e. if the node is the last child
    /// of its parent.
    virtual std::shared_ptr<ISgfcNode> GetNextSibling() const = 0;

    /// @brief Returns true if the node has a next sibling node. Returns false
    /// if the node has no next sibling node, i.e. if the node is the last child
    /// of its parent.
    virtual bool HasNextSibling() const = 0;

    /// @brief Returns the node's previous sibling node. Returns @e nullptr if
    /// the node has no previous sibling node, i.e. if the node is the first
    /// child of its parent.
    virtual std::shared_ptr<ISgfcNode> GetPreviousSibling() const = 0;

    /// @brief Returns true if the node has a previous sibling node. Returns
    /// false if the node has no previous sibling node, i.e. if the node is the
    /// first child of its parent.
    virtual bool HasPreviousSibling() const = 0;

    /// @brief Returns the node's parent node. Returns @e nullptr if the node
    /// has no parent node, i.e. if the node is the root node of a game tree.
    virtual std::shared_ptr<ISgfcNode> GetParent() const = 0;

    /// @brief Returns true if the node has a parent node. Returns false if the
    /// node has no parent node, i.e. if the node is the root node of a game
    /// tree.
    virtual bool HasParent() const = 0;

    /// @brief Returns true if the node is a descendant of @a node, i.e. if the
    /// node is anywhere below @a node in the game tree. Returns false if the
    /// node is not a descendant of @a node.
    ///
    /// @exception std::invalid_argument Is thrown if @a node is @e nullptr.
    virtual bool IsDescendantOf(std::shared_ptr<ISgfcNode> node) const = 0;

    /// @brief Returns true if the node is an ancestor of @a node, i.e. if the
    /// node is a direct or indirect parent of @a node. Returns false if the
    /// node is not an ancestor of @a node.
    ///
    /// @exception std::invalid_argument Is thrown if @a node is @e nullptr.
    virtual bool IsAncestorOf(std::shared_ptr<ISgfcNode> node) const = 0;

    /// @brief Returns the root node of the game tree that contains the node.
    /// Returns the node itself if the node has no parent, i.e. if it is
    /// itself the root node.
    ///
    /// @exception std::bad_weak_ptr Is thrown if the method would like to
    /// return the node itself, but the ISgfcNode object is not wrapped by an
    /// std::shared_ptr somewhere external. It is impossible for the library
    /// client to encounter this scenario, it can only occur during internal
    /// unit testing.
    virtual std::shared_ptr<ISgfcNode> GetRoot() const = 0;

    /// @brief Returns true if the node is the root node of a game tree. Returns
    /// false if the node is not the root node of a game tree.
    virtual bool IsRoot() const = 0;
    //@}

    /// @name Node traits
    //@{
    /// @brief Returns the node's traits.
    ///
    /// Returns SgfcConstants::NodeTraitsNone if the node is not the root node
    /// of a game tree and if it has either no properties or only properties
    /// with SgfcPropertyCategory::Miscellaneous.
    ///
    /// @see SgfcNodeTraits
    virtual SgfcNodeTraits GetTraits() const = 0;

    /// @brief Returns true if the node has the trait @a trait. Returns false
    /// if the node does not have the trait @a trait.
    ///
    /// @see SgfcNodeTrait
    virtual bool HasTrait(SgfcNodeTrait trait) const = 0;
    //@}

    /// @name Game tree search
    //@{
    /// @brief Returns the first node among the node itself and its ancestors
    /// that has the trait SgfcNodeTrait::GameInfo. Returns @e nullptr if there
    /// is no such node.
    ///
    /// The search starts with the node itself, then progresses to the node's
    /// parent, the node's parent's parent, etc. up to the root node of the
    /// game tree. The search returns the first node whose GetTraits() method
    /// returns a value that includes SgfcNodeTrait::GameInfo.
    ///
    /// @see SgfcNodeTrait::GameInfo
    ///
    /// @exception std::bad_weak_ptr Is thrown if the method would like to
    /// return the node itself, but the ISgfcNode object is not wrapped by an
    /// std::shared_ptr somewhere external. It is impossible for the library
    /// client to encounter this scenario, it can only occur during internal
    /// unit testing.
    virtual std::shared_ptr<ISgfcNode> GetGameInfoNode() const = 0;

    /// @brief Returns an ordered collection of nodes that form the main
    /// variation of game play found on the node itself and its first child
    /// descendants.
    ///
    /// The main variation is defined as the depth-first path that starts with
    /// the node itself and continues along the first child descendants down
    /// to the last node that has no more children. The collection that is
    /// returned therefore contains the following nodes in the listed order:
    ///
    /// - Element 0: The node itself
    /// - Element 1: The node's first child
    /// - Element 2: The node's first child's first child
    /// - Etc.
    ///
    /// If the node has no children the returned collection contains only the
    /// node itself.
    ///
    /// This is a convenience method that is most useful when invoked on a
    /// game info node, i.e. a node that has the trait SgfcNodeTrait::GameInfo.
    ///
    /// @exception std::bad_weak_ptr Is thrown if the method would like to
    /// return the node itself, but the ISgfcNode object is not wrapped by an
    /// std::shared_ptr somewhere external. It is impossible for the library
    /// client to encounter this scenario, it can only occur during internal
    /// unit testing.
    virtual std::vector<std::shared_ptr<ISgfcNode>> GetMainVariationNodes() const = 0;
    //@}

    /// @name Property access
    //@{
    /// @brief Returns true if the node has one or more properties. Returns
    /// false if the node has no properties.
    virtual bool HasProperties() const = 0;

    /// @brief Returns a collection with the properties of the node. The
    /// collection is empty if the node has no properties. The collection has
    /// no particular order.
    ///
    /// The SGF standard does not define an order in which properties have to
    /// appear within a node. In fact, it explicitly states that different
    /// applications may use different ordering, and that the order may change
    /// every time that the SGF data is saved.
    ///
    /// The SGF standard defines that only one of each property is allowed per
    /// node.
    virtual std::vector<std::shared_ptr<ISgfcProperty>> GetProperties() const = 0;

    /// @brief Sets the properties of the node to the collection @a properties.
    /// The collection may be empty. The order in which properties appear in
    /// the collection is irrelevant. No SgfcPropertyType except
    /// SgfcPropertyType::Unknown may appear more than once in the collection.
    /// No property name may appear more than once in the collection.
    ///
    /// The SGF standard defines that only one of each property is allowed per
    /// node. This is the reason why this method prevents setting a collection
    /// that contains duplicate property types or names. Names are checked to
    /// prevent duplicates of custom properties, which have
    /// SgfcPropertyType::Unknow.
    ///
    /// @exception std::invalid_argument Is thrown if @a properties contains
    /// @e nullptr elements, or if an SgfcPropertyType other than
    /// SgfcPropertyType::Unknown appears more than once, or if a property name
    /// appears more than once.
    virtual void SetProperties(const std::vector<std::shared_ptr<ISgfcProperty>>& properties) = 0;

    /// @brief Adds @a property as the last property to the node's
    /// collection of properties. @a property may not be @e nullptr.
    ///
    /// @exception std::invalid_argument Is thrown if @a property is @e nullptr,
    /// if @a property is already in the node's collection of properties, or
    /// the node's collection of properties already contains another property
    /// with the same SgfcPropertyType (except SgfcPropertyType::Unknown which
    /// may appear more than once) or the same property name.
    virtual void AppendProperty(std::shared_ptr<ISgfcProperty> property) = 0;

    /// @brief Removes @a property from the node's collection of properties.
    ///
    /// @exception std::invalid_argument Is thrown if @a property is not
    /// part of the node's collection of properties.
    virtual void RemoveProperty(std::shared_ptr<ISgfcProperty> property) = 0;

    /// @brief Removes all properties from the node's collection of properties.
    virtual void RemoveAllProperties() = 0;

    /// @brief Returns the property with the specified type @a propertyType if
    /// the node has such a property. Returns @e nullptr if the node has no
    /// such property.
    ///
    /// If @a propertyType is SgfcPropertyType::Unknown and the node has several
    /// such properties, returns the property that appears first in the list
    /// that is returned by GetProperties().
    ///
    /// The SGF standard defines that only one of each property is allowed per
    /// node.
    virtual std::shared_ptr<ISgfcProperty> GetProperty(SgfcPropertyType propertyType) const = 0;

    /// @brief Returns the property with the specified name @a propertyName if
    /// the node has such a property. Returns @e nullptr if the node has no
    /// such property.
    ///
    /// The SGF standard defines that only one of each property is allowed per
    /// node.
    virtual std::shared_ptr<ISgfcProperty> GetProperty(const std::string& propertyName) const = 0;
    //@}
  };
}
