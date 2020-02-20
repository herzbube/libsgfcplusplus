#pragma once

// Project includes
#include "ISgfcProperty.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcNode interface provides access to the data of a single
  /// SGF node in a tree of SGF nodes.
  class ISgfcNode
  {
  public:
    /// @brief Initializes a newly constructed ISgfcNode object.
     ISgfcNode();

     /// @brief Destroys and cleans up the ISgfcNode object.
     virtual ~ISgfcNode();

    /// @brief Returns the node's first child node.
    /// The node may be @e nullptr.
    virtual std::shared_ptr<ISgfcNode> GetFirstChild() const = 0;

    /// @brief Sets the node's first child node to @a firstChild.
    /// @a firstChild may be @e nullptr.
    ///
    /// The previous first child node and the entire sub tree dangling from
    /// it, is discarded.
    virtual void SetFirstChild(std::shared_ptr<ISgfcNode> firstChild) = 0;

    /// @brief Returns the node's next sibling node.
    /// The node may be @e nullptr.
    virtual std::shared_ptr<ISgfcNode> GetNextSibling() const = 0;

    /// @brief Sets the node's next sibling node to @a nextSibling.
    /// @a nextSibling may be @e nullptr.
    ///
    /// The previous next sibling node, the siblings behind that, and the sub
    /// trees dangling from all of these siblings, are discarded.
    virtual void SetNextSibling(std::shared_ptr<ISgfcNode> nextSibling) = 0;

    /// @brief Returns the node's parent node.
    /// The node may be @e nullptr.
    virtual std::shared_ptr<ISgfcNode> GetParent() const = 0;

    /// @brief Sets the node's parent node to @a parent.
    /// @a parent may be @e nullptr.
    ///
    /// If @a parent is @e nullptr then this node and the entire sub tree
    /// dangling from it, is discarded once no one holds a reference to it
    /// anymore.
    virtual void SetParent(std::shared_ptr<ISgfcNode> parent) = 0;

    /// @brief Returns a collection with the properties of the node. The
    /// collection may be empty. The collection has no particular order.
    ///
    /// The SGF standard does not define an order in which properties have to
    /// appear within a node. In fact, it explicitly states that different
    /// applications may use different ordering, and that the order may change
    /// every time that the SGF data is saved.
    virtual std::vector<std::shared_ptr<ISgfcProperty>> GetProperties() const = 0;

    /// @brief Sets the properties of the node to the collection @a properties.
    /// The collection may be empty. The order in which properties appear in
    /// the collection is irrelevant.
    virtual void SetProperties(std::vector<std::shared_ptr<ISgfcProperty>> properties) = 0;
  };
}
