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

    virtual std::vector<std::shared_ptr<ISgfcProperty>> GetProperties() const;
    virtual void SetProperties(const std::vector<std::shared_ptr<ISgfcProperty>>& properties);
    virtual std::shared_ptr<ISgfcProperty> GetProperty(SgfcPropertyType propertyType) const;

  private:
    std::shared_ptr<ISgfcNode> firstChild;
    std::shared_ptr<ISgfcNode> nextSibling;
    std::weak_ptr<ISgfcNode> parent;  // must be weak_ptr to break reference cycle
    std::vector<std::shared_ptr<ISgfcProperty>> properties;
  };
}
