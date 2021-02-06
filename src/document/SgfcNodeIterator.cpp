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

// Project includes
#include "SgfcNodeIterator.h"

// C++ Standard Library includes
#include <stack>

namespace LibSgfcPlusPlus
{
  SgfcNodeIterator::SgfcNodeIterator()
  {
  }

  SgfcNodeIterator::~SgfcNodeIterator()
  {
  }

  void SgfcNodeIterator::IterateOverNodesDepthFirst(
    std::shared_ptr<ISgfcNode> startNode,
    NodeVisitCallback nodeVisitCallback) const
  {
    if (nodeVisitCallback == nullptr)
      throw std::invalid_argument("IterateOverNodesDepthFirst failed: Node visit callback object is nullptr");

    if (startNode == nullptr)
      return;

    IterateOverNodesDepthFirstPrivate(startNode, nodeVisitCallback);
  }

  void SgfcNodeIterator::IterateOverNodesDepthFirstPrivate(
    std::shared_ptr<ISgfcNode> startNode,
    NodeVisitCallback nodeVisitCallback) const
  {
    std::stack<std::shared_ptr<ISgfcNode>> stack;

    std::shared_ptr<ISgfcNode> currentNode = startNode;

    SgfcNodeIterationContinuation iterationContinuation = SgfcNodeIterationContinuation::VerticalAndLateral;

    while (true)
    {
      while (currentNode)
      {
        iterationContinuation = nodeVisitCallback(currentNode);
        if (iterationContinuation == SgfcNodeIterationContinuation::Stop)
        {
          return;
        }
        else if (iterationContinuation == SgfcNodeIterationContinuation::VerticalAndLateral)
        {
          stack.push(currentNode);
          currentNode = currentNode->GetFirstChild();
        }
        else
        {
          break;
        }
      }

      // currentNode can be nullptr if the most recent request to continue
      // laterally could not be satisfied because there was no next sibling.
      if (iterationContinuation == SgfcNodeIterationContinuation::Lateral && currentNode != nullptr)
      {
        currentNode = currentNode->GetNextSibling();
      }
      else
      {
        if (! stack.empty())
        {
          currentNode = stack.top();
          stack.pop();

          currentNode = currentNode->GetNextSibling();
        }
        else
        {
          // We're done
          break;
        }
      }
    }
  }
}
