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
    if (startNode == nullptr)
      return;

    SgfcNodeIterationContinuation iterationContinuation = nodeVisitCallback(startNode);
    if (iterationContinuation == SgfcNodeIterationContinuation::VerticalAndLateral)
    {
      IterateOverNodesDepthFirstRecursive(startNode, nodeVisitCallback);
    }
  }

  SgfcNodeIterationContinuation SgfcNodeIterator::IterateOverNodesDepthFirstRecursive(
    std::shared_ptr<ISgfcNode> parentNode,
    NodeVisitCallback nodeVisitCallback) const
  {
    auto firstChildNode = parentNode->GetFirstChild();
    if (firstChildNode == nullptr)
      return SgfcNodeIterationContinuation::Ascend;

    SgfcNodeIterationContinuation iterationContinuation = nodeVisitCallback(firstChildNode);
    if (iterationContinuation == SgfcNodeIterationContinuation::VerticalAndLateral)
    {
      iterationContinuation = IterateOverNodesDepthFirstRecursive(firstChildNode, nodeVisitCallback);
      if (iterationContinuation == SgfcNodeIterationContinuation::Stop)
        return iterationContinuation;
    }
    else if (iterationContinuation == SgfcNodeIterationContinuation::Ascend ||
             iterationContinuation == SgfcNodeIterationContinuation::Stop)
    {
      return iterationContinuation;
    }

    auto nextSiblingNode = firstChildNode->GetNextSibling();
    while (nextSiblingNode != nullptr)
    {
      iterationContinuation = nodeVisitCallback(nextSiblingNode);
      if (iterationContinuation == SgfcNodeIterationContinuation::VerticalAndLateral)
      {
        IterateOverNodesDepthFirstRecursive(nextSiblingNode, nodeVisitCallback);
        if (iterationContinuation == SgfcNodeIterationContinuation::Stop)
          return iterationContinuation;
      }
      else if (iterationContinuation == SgfcNodeIterationContinuation::Ascend ||
               iterationContinuation == SgfcNodeIterationContinuation::Stop)
      {
        return iterationContinuation;
      }

      nextSiblingNode = nextSiblingNode->GetNextSibling();
    }

    return iterationContinuation;
  }
}
