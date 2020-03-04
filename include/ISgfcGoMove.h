#pragma once

// Project includes
#include "SgfcColor.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  class ISgfcGoPoint;
  class ISgfcGoStone;

  /// @brief The ISgfcGoMove interface represents a move in a Go game.
  ///
  /// A move in a Go game is defined by the color of the player who made the
  /// move and by the location of the stone that was placed by the move on the
  /// Go board. ISgfcGoMove uses a reference to an ISgfcGoStone object to record
  /// these two pieces of information. The color of the ISgfcGoStone object
  /// is the color of the player who made the move.
  class ISgfcGoMove
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGoMove object.
    ISgfcGoMove();

    /// @brief Destroys and cleans up the ISgfcGoMove object.
    virtual ~ISgfcGoMove();

    /// @brief Returns the stone that was placed on the Go board by the move.
    virtual std::shared_ptr<ISgfcGoStone> GetStone() const = 0;

    /// @brief Returns the color of the player who made the move.
    ///
    /// This is a convenience method that returns the same value as the
    /// ISgfcGoStone::GetColor() method of the ISgfcGoStone object returned
    /// by GetStone().
    virtual SgfcColor GetPlayerColor() const = 0;

    /// @brief Returns the location of the stone that was placed by the move on
    /// the Go board.
    ///
    /// This is a convenience method that returns the same value as the
    /// ISgfcGoStone::GetLocation() method of the ISgfcGoStone object returned
    /// by GetStone().
    virtual std::shared_ptr<ISgfcGoPoint> GetStoneLocation() const = 0;
  };
}
