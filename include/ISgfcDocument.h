#pragma once

// Project includes
#include "ISgfcGame.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcDocument interface provides access to a collection of
  /// SGF games. When you read an SGF file, the SGF data in that file becomes
  /// an ISgfcDocument.
  class ISgfcDocument
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
    ///
    /// Different kinds of games may appear within the same document.
    virtual std::vector<std::shared_ptr<ISgfcGame>> GetGames() const = 0;

    /// @brief Sets the collection of games that together make up the document
    /// to @a games, replacing the previous collection.
    ///
    /// @todo Check for duplicates and @e nullptr to achieve the same
    /// consistency provided by AppendGame().
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
    ///
    /// @todo Remove this prior to release.
    virtual void DebugPrintToConsole() const = 0;
  };
}
