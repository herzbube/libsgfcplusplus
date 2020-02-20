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

    /// @brief Returns a collection of games that together make up the document.
    ///
    /// Different kinds of games may appear within the same document.
    virtual std::vector<std::shared_ptr<ISgfcGame>> GetGames() const = 0;
  };
}
