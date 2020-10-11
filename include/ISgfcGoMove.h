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
