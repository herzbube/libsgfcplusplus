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
#include "ISgfcGame.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcDocument interface provides access to a collection of
  /// SGF games. When you read an SGF file, the SGF data in that file becomes
  /// an ISgfcDocument.
  ///
  /// @ingroup public-api
  /// @ingroup document
  class SGFCPLUSPLUS_EXPORT ISgfcDocument
  {
  public:
    /// @brief Initializes a newly constructed ISgfcDocument object.
    ISgfcDocument();

    /// @brief Destroys and cleans up the ISgfcDocument object.
    virtual ~ISgfcDocument();

    /// @brief Returns true if the document has no content. Returns false if
    /// the document has some content.
    ///
    /// The document is empty if it contains no games.
    virtual bool IsEmpty() const = 0;

    /// @brief Returns a collection of games that together make up the document.
    virtual std::vector<std::shared_ptr<ISgfcGame>> GetGames() const = 0;

    /// @brief Returns the first game from the collection of games that
    /// GetGames() returns. Returns @e nullptr if GetGames() returns an empty
    /// collection.
    ///
    /// This is a convenience method which simplifies the majority of cases
    /// where a document only contains a single game.
    virtual std::shared_ptr<ISgfcGame> GetGame() const = 0;

    /// @brief Sets the collection of games that together make up the document
    /// to @a games, replacing the previous collection. @a games may not contain
    /// @e nullptr. @a games may not contain duplicates.
    ///
    /// @exception std::invalid_argument Is thrown if @a games contains a
    /// @e nullptr element, or if @a games contains duplicate elements.
    virtual void SetGames(const std::vector<std::shared_ptr<ISgfcGame>>& games) = 0;

    /// @brief Adds @a game as the last game to the collection of games that
    /// together make up the document. @a game may not be @e nullptr.
    ///
    /// @exception std::invalid_argument Is thrown if @a game is @e nullptr or
    /// if @a game is already in the collection.
    virtual void AppendGame(std::shared_ptr<ISgfcGame> game) = 0;

    /// @brief Removes @a game from the collection of games that together make
    /// up the document.
    ///
    /// @exception std::invalid_argument Is thrown if @a game is not part of
    /// the collection of games that together make up the document.
    virtual void RemoveGame(std::shared_ptr<ISgfcGame> game) = 0;

    /// @brief Removes all games from the collection of games that together make
    /// up the document.
    virtual void RemoveAllGames() = 0;

    /// @brief Prints the content of the ISgfcDocument to stdout for debugging
    /// purposes.
    virtual void DebugPrintToConsole() const = 0;
  };
}
