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
#include "../../include/ISgfcNode.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcNode class provides an implementation of the
  /// ISgfcNode interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup game-tree
  ///
  /// The SgfcNode class inherits from std::enable_shared_from_this so that it
  /// can return a std::shared_ptr for itself (using the "this" pointer) from
  /// some of its methods. This only works if the SgfcNode object is owned by
  /// another external std::shared_ptr somewhere. If there is no such external
  /// std::shared_ptr the method in question will throw std::bad_weak_ptr.
  /// This is documented on the public interface for all affected methods.
  ///
  /// The implementation of this class must take special care when it internally
  /// invokes one of the above-mentioned methods:
  /// - If the calling method A is const
  /// - And if the called method B is also const
  /// - And if the called method B returns a non-const object
  /// - Then the calling method A must not do anything non-const with the
  ///   returned non-const object
  /// The reason: The returned non-const object is actually the same object that
  /// invoked method B, so the const method A would do something non-const to
  /// itself. See GetRoot() for an example where const'ness is removed to open
  /// open the described hazard.
  class SgfcNode : public ISgfcNode, public std::enable_shared_from_this<SgfcNode>
  {
  public:
    /// @brief Initializes a newly constructed SgfcNode object. The node has
    /// no parent, children or siblings.
    SgfcNode();

    /// @brief Destroys and cleans up the SgfcNode object.
    virtual ~SgfcNode();

    virtual std::shared_ptr<ISgfcNode> GetFirstChild() const;
    /// @brief Sets the node's first child node to @a node, overwriting the
    /// previously set first child node. This method performs no relinking of
    /// any kind.
    ///
    /// This is a library-internal setter method. Library clients should never
    /// be able to invoke this directly. Instead library clients must use
    /// ISgfcTreeBuilder.
    void SetFirstChild(std::shared_ptr<ISgfcNode> node);
    virtual std::shared_ptr<ISgfcNode> GetLastChild() const;
    virtual std::vector<std::shared_ptr<ISgfcNode>> GetChildren() const;
    virtual bool HasChildren() const;

    virtual std::shared_ptr<ISgfcNode> GetNextSibling() const;
    /// @brief Sets the node's next sibling node to @a node, overwriting the
    /// previously set next sibling node. This method performs no relinking of
    /// any kind.
    ///
    /// This is a library-internal setter method. Library clients should never
    /// be able to invoke this directly. Instead library clients must use
    /// ISgfcTreeBuilder.
    void SetNextSibling(std::shared_ptr<ISgfcNode> node);
    virtual bool HasNextSibling() const;
    virtual std::shared_ptr<ISgfcNode> GetPreviousSibling() const;
    virtual bool HasPreviousSibling() const;

    virtual std::shared_ptr<ISgfcNode> GetParent() const;
    /// @brief Sets the node's parent node to @a node, overwriting the
    /// previously set parent node. This method performs no relinking of
    /// any kind.
    ///
    /// This is a library-internal setter method. Library clients should never
    /// be able to invoke this directly. Instead library clients must use
    /// ISgfcTreeBuilder.
    void SetParent(std::shared_ptr<ISgfcNode> node);
    virtual bool HasParent() const;
    virtual bool IsDescendantOf(std::shared_ptr<ISgfcNode> node) const;
    virtual bool IsAncestorOf(std::shared_ptr<ISgfcNode> node) const;
    virtual std::shared_ptr<ISgfcNode> GetRoot() const;
    virtual bool IsRoot() const;

    virtual SgfcNodeTraits GetTraits() const;
    virtual bool HasTrait(SgfcNodeTrait trait) const;

    virtual bool HasProperties() const;
    virtual std::vector<std::shared_ptr<ISgfcProperty>> GetProperties() const;
    virtual void SetProperties(const std::vector<std::shared_ptr<ISgfcProperty>>& properties);
    virtual void AppendProperty(std::shared_ptr<ISgfcProperty> property);
    virtual void RemoveProperty(std::shared_ptr<ISgfcProperty> property);
    virtual void RemoveAllProperties();
    virtual std::shared_ptr<ISgfcProperty> GetProperty(SgfcPropertyType propertyType) const;
    virtual std::shared_ptr<ISgfcProperty> GetProperty(const std::string& propertyName) const;

  private:
    std::shared_ptr<ISgfcNode> firstChild;
    std::shared_ptr<ISgfcNode> nextSibling;
    std::weak_ptr<ISgfcNode> parent;  // must be weak_ptr to break reference cycle
    std::vector<std::shared_ptr<ISgfcProperty>> properties;

    static bool ValidateProperties(const std::vector<std::shared_ptr<ISgfcProperty>>& properties, std::string& validationFailedReason);
  };
}
