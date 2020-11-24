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

    virtual std::weak_ptr<ISgfcGame> GetGame() const override;

    virtual void SetFirstChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> child) const override;
    virtual void AppendChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> child) const override;
    virtual void InsertChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> child,
      std::shared_ptr<ISgfcNode> referenceChild) const override;
    virtual void RemoveChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> child) const override;
    virtual void ReplaceChild(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> newChild,
      std::shared_ptr<ISgfcNode> oldChild) const override;
    virtual void SetNextSibling(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> nextSibling) const override;
    virtual void SetParent(
      std::shared_ptr<ISgfcNode> node,
      std::shared_ptr<ISgfcNode> parent) const override;

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
