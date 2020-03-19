#pragma once

// Project includes
#include "ISgfcProperty.h"
#include "SgfcBoardSize.h"
#include "SgfcGameType.h"

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcBoardSizeProperty interface is a specialization of
  /// ISgfcProperty for SgfcPropertyType::SZ. It simplifies access to the
  /// property value and provides the value in the form of an SgfcBoardSize
  /// object.
  class ISgfcBoardSizeProperty : virtual public ISgfcProperty
  {
  public:
    /// @brief Initializes a newly constructed ISgfcBoardSizeProperty object.
    ISgfcBoardSizeProperty();

    /// @brief Destroys and cleans up the ISgfcBoardSizeProperty object.
    virtual ~ISgfcBoardSizeProperty();

    /// @brief Returns the property value interpreted as an SgfcBoardSize value.
    /// Returns a game-specific default board size for a few game types
    /// mentioned in the SGF standard if the property has no value.
    virtual SgfcBoardSize GetBoardSize(SgfcGameType gameType) const = 0;
  };
}
