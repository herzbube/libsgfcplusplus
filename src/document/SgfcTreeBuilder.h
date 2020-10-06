#pragma once

// Project includes
#include "../../include/ISgfcTreeBuilder.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcTreeBuilder class provides an implementation of the
  /// ISgfcTreeBuilder interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup game-tree
  class SgfcTreeBuilder : public ISgfcTreeBuilder
  {
  public:
    /// @brief Initializes a newly constructed SgfcTreeBuilder object. The
    /// tree builder operates on the game tree represented by @a game.
    ///
    /// @exception std::invalid_argument Is thrown if @a game is nullptr.
    SgfcTreeBuilder(std::weak_ptr<ISgfcGame> game);

    /// @brief Destroys and cleans up the SgfcTreeBuilder object.
    virtual ~SgfcTreeBuilder();

    virtual std::weak_ptr<ISgfcGame> GetGame() const;

    virtual void SetFirstChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> child) const;
    virtual void AppendChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> child) const;
    virtual void InsertChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> child,
      std::shared_ptr<ISgfcNode> referenceChild) const;
    virtual void RemoveChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> child) const;
    virtual void ReplaceChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> newChild,
      std::shared_ptr<ISgfcNode> oldChild) const;
    virtual void SetNextSibling(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> nextSibling) const;
    virtual void SetParent(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> parent) const;

  private:
    std::weak_ptr<ISgfcGame> game;

    void RemoveNodeFromCurrentLocation(
      std::shared_ptr<ISgfcNode> node) const;
    void RemoveNodeAndAllNextSiblingsFromParent(
      std::shared_ptr<ISgfcNode> node) const;
    void InsertNodeAtNewLocation(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> newParent,
      std::shared_ptr<ISgfcNode> newNextSibling) const;
  };
}
