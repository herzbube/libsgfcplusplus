#pragma once

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcGame;
  class ISgfcNode;

  /// @brief The ISgfcTreeBuilder interface provides methods to manipulate the
  /// nodes of a game tree.
  class SGFCPLUSPLUS_EXPORT ISgfcTreeBuilder
  {
  public:
    /// @brief Initializes a newly constructed ISgfcTreeBuilder object.
    ISgfcTreeBuilder();

    /// @brief Destroys and cleans up the ISgfcTreeBuilder object.
    virtual ~ISgfcTreeBuilder();

    /// @brief Returns the ISgfcGame object whose game tree the methods in the
    /// ISgfcTreeBuilder operate on.
    virtual std::weak_ptr<ISgfcGame> GetGame() const = 0;

    /// @brief Sets the first child node of @a node to @a child.
    /// @a child may be @e nullptr.
    ///
    /// If @a child is already part of the game tree in some other
    /// location, it is moved from its current location to the new location.
    ///
    /// The previous first child node and the entire sub tree dangling from it,
    /// is discarded once no one holds a reference to it anymore.
    ///
    /// @exception std::invalid_argument Is thrown if @a node is @e nullptr,
    /// if @a child is an ancestor of @a node, or if @a child is equal to
    /// @a node.
    virtual void SetFirstChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> child) const = 0;

    /// @brief Adds @a child as the last child to @a node. @a child may not
    /// be @e nullptr.
    ///
    /// If @a child is already part of the game tree in some other
    /// location, it is moved from its current location to the new location.
    ///
    /// @exception std::invalid_argument Is thrown if @a node is @e nullptr,
    /// if @a child is @e nullptr, if @a child is an ancestor of @a node, or
    /// if @a child is equal to @a node.
    virtual void AppendChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> child) const = 0;

    /// @brief Inserts @a child as a child to @a node, before the reference
    /// child node @a referenceChild. @a child may not be @e nullptr.
    /// @a referenceChild may be nullptr, but if it's not then it must be a
    /// child of @a node.
    ///
    /// If @a referenceChild is @e nullptr then @a child is inserted as the
    /// last child of @a node. The result is the same as if AppendChild() had
    /// been invoked.
    ///
    /// If @a child is already part of the game tree in some other
    /// location, it is moved from its current location to the new location.
    ///
    /// @exception std::invalid_argument Is thrown if @a node is @e nullptr,
    /// if @a child is @e nullptr, if @a referenceChild is not @e nullptr
    /// but it's not a child of the node, if @a child is an ancestor of @a node,
    /// or if @a child is equal to @a node.
    virtual void InsertChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> child,
      std::shared_ptr<ISgfcNode> referenceChild) const = 0;

    /// @brief Removes @a child from @a node. @a child may not be @e nullptr.
    /// @a child must be a child of the node.
    ///
    /// @a child and the entire sub tree dangling from it, is discarded once
    /// no one holds a reference to it anymore.
    ///
    /// @exception std::invalid_argument Is thrown if @a node is @e nullptr,
    /// if @a child is @e nullptr, or if @a child is not a child of @a node.
    virtual void RemoveChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> child) const = 0;

    /// @brief Replaces @a oldChild with @a newChild. @a oldChild and
    /// @a newChild may not be @e nullptr. @a oldChild must be a child of
    /// @a node.
    ///
    /// If @a newChild is already part of the game tree in some other
    /// location, it is moved from its current location to the new location.
    ///
    /// @a oldChild and the entire sub tree dangling from it, is discarded
    /// once no one holds a reference to it anymore.
    ///
    /// @exception std::invalid_argument Is thrown if @a node is @e nullptr,
    /// if @a oldChild or @a newChild are @e nullptr, if @a oldChild is not a
    /// child of @a node, if @a newChild is an ancestor of @a node, or if
    /// @a newChild is equal to @a node.
    virtual void ReplaceChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> newChild,
      std::shared_ptr<ISgfcNode> oldChild) const = 0;

    /// @brief Sets the next sibling node of @a node to @a nextSibling. @a node
    /// must not be the root node of a game tree because by a root node by
    /// definition can't have siblings. @a nextSibling may be @e nullptr.
    ///
    /// If @a nextSibling is already part of the game tree in some other
    /// location, it is moved from its current location to the new location.
    ///
    /// The previous next sibling node, the siblings behind that, and the sub
    /// trees dangling from all of these siblings, are discarded once no one
    /// holds a reference to them anymore.
    ///
    /// @exception std::invalid_argument Is thrown if @a node is @e nullptr,
    /// if @a node is the root node of a game tree, if @a nextSibling is not
    /// @e nullptr and an ancestor of @a node, or if @a nextSibling is equal
    /// to @a node.
    virtual void SetNextSibling(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> nextSibling) const = 0;

    /// @brief Sets the parent node of @a node to @a parent.
    /// @a parent may be @e nullptr.
    ///
    /// If @a parent is not @e nullptr, then @a node is added as the last
    /// child of @a parent. The result is the same as if AppendChild() had
    /// been invoked on @a parent with @a node as the argument.
    ///
    /// If @a parent is not @e nullptr and if @a node is already part of the
    /// game tree in some other location, @a node is moved from its current
    /// location to the new location.
    ///
    /// If @a parent is @e nullptr then @a node and the entire sub tree
    /// dangling from it, is discarded once no one holds a reference to it
    /// anymore.
    ///
    /// @exception std::invalid_argument Is thrown if @a node is @e nullptr,
    /// if @a parent is a descendant of @a node, or if @a parent is equal to
    /// @a node.
    virtual void SetParent(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> parent) const = 0;
  };
}
