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

// C++ Standard Library includes
#include <functional>

namespace LibSgfcPlusPlus
{
  /// @brief SgfcNodeIterationContinuation enumerates how SgfcNodeIterator
  /// should continue with the iteration after it has visited a node.
  enum class SgfcNodeIterationContinuation
  {
    /// @brief SgfcNodeIterator will continue the iteration both vertically
    /// (firstChild) and laterally (nextSibling).
    VerticalAndLateral,

    /// @brief SgfcNodeIterator will continue the iteration laterally
    /// (nextSibling) but not vertically (firstChild).
    Lateral,

    /// @brief SgfcNodeIterator will stop the iteration on the current tree
    /// level, ascend one tree level, and then continue laterally (nextSibling)
    /// on the upper tree level.
    Ascend,

    /// @brief SgfcNodeIterator will stop the iteration.
    Stop,
  };

  /// @brief Defines the signature of the callback method that SgfcNodeIterator
  /// invokes when it visits a node.
  ///
  /// The callback parameter is the node that is being visited. The return value
  /// is an instruction to SgfcNodeIterator how it should continue with the
  /// iteration.
  typedef std::function<SgfcNodeIterationContinuation (std::shared_ptr<ISgfcNode>)> NodeVisitCallback;

  /// @brief The SgfcNodeIterator class encapsulates reusable algorithms for
  /// iterating over a tree of ISgfcNode objects.
  ///
  /// @ingroup internals
  /// @ingroup game-tree
  class SgfcNodeIterator
  {
  public:
    /// @brief Initializes a newly constructed SgfcNodeIterator object.
    SgfcNodeIterator();

    /// @brief Destroys and cleans up the SgfcNodeIterator object.
    virtual ~SgfcNodeIterator();

    /// @brief Iterates over the tree of nodes depth-first, starting with
    /// @a startNode. Invokes @a nodeVisitCallback whenever a node is visited.
    /// @a nodeVisitCallback must not be @e nullptr.
    ///
    /// When @a nodeVisitCallback returns the iteration continues according to
    /// the SgfcNodeIterationContinuation value that @a nodeVisitCallback
    /// returns.
    ///
    /// Does nothing if @a startNode is @e nullptr and returns immediately
    /// without invoking @a nodeVisitCallback.
    ///
    /// If @a startNode is not @e nullptr then @a nodeVisitCallback is invoked
    /// with @a startNode as the parameter, after which the depth-first
    /// iteration begins.
    ///
    /// @a startNode typically is the root node of a tree of nodes to be
    /// iterated. If this not the case the iteration may visit the next siblings
    /// of @a startNode, depending on the return value of @a nodeVisitCallback,
    /// but the iteration never visits the parent or previous siblings of
    /// @a startNode.
    ///
    /// @exception std::invalid_argument Is thrown if @a nodeVisitCallback is
    /// @e nullptr.
    void IterateOverNodesDepthFirst(
      std::shared_ptr<ISgfcNode> startNode,
      NodeVisitCallback nodeVisitCallback) const;

  private:
    void IterateOverNodesDepthFirstPrivate(
      std::shared_ptr<ISgfcNode> parentNode,
      NodeVisitCallback nodeVisitCallback) const;
  };
}
