#pragma once

// Project includes
#include "SgfcColor.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  class ISgfcGoPoint;
  class ISgfcGoStone;

  /// @brief The ISgfcGoMove interface represents a move in a Go game.
  ///
  /// A move in a Go game is defined by the color of the player who made the
  /// move and, if it is not a pass move, by the location of the stone that was
  /// placed by the move on the Go board. ISgfcGoMove uses a reference to an
  /// ISgfcGoStone object to record the latter of these two pieces of
  /// information.
  ///
  /// @ingroup public-api
  /// @ingroup go
  class SGFCPLUSPLUS_EXPORT ISgfcGoMove
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGoMove object.
    ISgfcGoMove();

    /// @brief Destroys and cleans up the ISgfcGoMove object.
    virtual ~ISgfcGoMove();

    /// @brief Returns true if the move is a pass move. Returns false if the
    /// move is not a pass move.
    virtual bool IsPassMove() const = 0;

    /// @brief Returns the stone that was placed on the Go board by the move.
    /// Returns @e nullptr if IsPassMove() returns true.
    virtual std::shared_ptr<ISgfcGoStone> GetStone() const = 0;

    /// @brief Returns the color of the player who made the move.
    ///
    /// If IsPassMove() returns false, this method returns the same value as
    /// the ISgfcGoStone::GetColor() method of the ISgfcGoStone object returned
    /// by GetStone().
    virtual SgfcColor GetPlayerColor() const = 0;

    /// @brief Returns the location of the stone that was placed by the move on
    /// the Go board. Returns @e nullptr if IsPassMove() returns true.
    ///
    /// Also returns @e nullptr if IsPassMove() returns false but the location
    /// of the stone that was placed by the move on the Go board is not known.
    /// This special case may occur if this ISgfcGoMove object is constructed
    /// during parsing of SGF content and the move property's value for some
    /// reason could not be interpreted.
    ///
    /// This is a convenience method that returns the same value as the
    /// ISgfcGoStone::GetLocation() method of the ISgfcGoStone object returned
    /// by GetStone().
    virtual std::shared_ptr<ISgfcGoPoint> GetStoneLocation() const = 0;
  };
}
