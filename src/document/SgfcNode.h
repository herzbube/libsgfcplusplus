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
  class SgfcNode : public ISgfcNode
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

    virtual bool HasProperties() const;
    virtual std::vector<std::shared_ptr<ISgfcProperty>> GetProperties() const;
    virtual void SetProperties(const std::vector<std::shared_ptr<ISgfcProperty>>& properties);
    virtual void AppendProperty(std::shared_ptr<ISgfcProperty> property);
    virtual void RemoveProperty(std::shared_ptr<ISgfcProperty> property);
    virtual void RemoveAllProperties();
    virtual std::shared_ptr<ISgfcProperty> GetProperty(SgfcPropertyType propertyType) const;

  private:
    std::shared_ptr<ISgfcNode> firstChild;
    std::shared_ptr<ISgfcNode> nextSibling;
    std::weak_ptr<ISgfcNode> parent;  // must be weak_ptr to break reference cycle
    std::vector<std::shared_ptr<ISgfcProperty>> properties;

    static bool ValidateProperties(const std::vector<std::shared_ptr<ISgfcProperty>>& properties, std::string& validationFailedReason);
  };
}
