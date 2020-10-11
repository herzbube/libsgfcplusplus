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
#include "../../include/ISgfcDocument.h"

// C++ Standard Library includes
#include <string>

// Forward declarations
class ISgfcGoPoint;
struct SGFInfo;
struct Node;

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDocument class provides an implementation of the
  /// ISgfcDocument interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup document
  class SgfcDocument : public ISgfcDocument
  {
  public:
    /// @brief Initializes a newly constructed SgfcDocument object. The document
    /// has no content.
    SgfcDocument();

    /// @brief Initializes a newly constructed SgfcDocument object with the
    /// SGF content in @a sgfInfo. The initialized document contains 0-n
    /// ISgfcGame objects that represent the game trees found during parsing
    /// of @a sgfInfo.
    ///
    /// @exception std::invalid_argument Is thrown if @a sgfInfo is @e nullptr.
    SgfcDocument(SGFInfo* sgfInfo);

    /// @brief Destroys and cleans up the SgfcDocument object.
    virtual ~SgfcDocument();

    virtual bool IsEmpty() const;

    virtual std::vector<std::shared_ptr<ISgfcGame>> GetGames() const;
    virtual void SetGames(const std::vector<std::shared_ptr<ISgfcGame>>& games);
    virtual void AppendGame(std::shared_ptr<ISgfcGame> game);
    virtual void RemoveGame(std::shared_ptr<ISgfcGame> game);
    virtual void RemoveAllGames();

    virtual void DebugPrintToConsole() const;

  private:
    std::vector<std::shared_ptr<ISgfcGame>> games;

    void RecursiveParseDepthFirst(
      std::shared_ptr<ISgfcNode> parentNode,
      Node* sgfParentNode,
      SgfcGameType gameType,
      SgfcBoardSize boardSize,
      std::shared_ptr<ISgfcTreeBuilder> treeBuilder);
    void ParseProperties(
      std::shared_ptr<ISgfcNode> node,
      Node* sgfNode,
      SgfcGameType gameType,
      SgfcBoardSize boardSize);

    void DebugPrintToConsoleRecursiveParseDepthFirst(
      std::shared_ptr<ISgfcNode> parentNode,
      int& nodeCount) const;
    void DebugPrintNodeToConsole(std::shared_ptr<ISgfcNode> node, int nodeNumber) const;
    void DebugPrintGoPropertyValueToConsole(const ISgfcSinglePropertyValue* propertyValue) const;
    void DebugPrintGoPointValueToConsole(const ISgfcGoPoint* goPoint) const;
  };
}
