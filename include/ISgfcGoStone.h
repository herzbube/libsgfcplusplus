#pragma once

// Project includes
#include "SgfcColor.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  class ISgfcGoPoint;

  /// @brief The ISgfcGoStone interface represents a stone on a Go board.
  ///
  /// A stone on a Go board is defined by its color and by its location on the
  /// Go board. ISgfcGoStone stores an SgfcColor value and a reference to an
  /// ISgfcGoPoint object to record these two pieces of information.
  class ISgfcGoStone
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGoStone object.
    ISgfcGoStone();

    /// @brief Destroys and cleans up the ISgfcGoStone object.
    virtual ~ISgfcGoStone();

    /// @brief Returns the color of the stone.
    virtual SgfcColor GetColor() const = 0;

    /// @brief Returns the location of the stone on the Go board.
    virtual std::shared_ptr<ISgfcGoPoint> GetLocation() const = 0;
  };
}
