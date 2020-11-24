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
#include "../../../include/ISgfcGoMove.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoMove class provides an implementation of the
  /// ISgfcGoMove interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup go
  class SgfcGoMove : public ISgfcGoMove
  {
  public:
    /// @brief Initializes a newly constructed SgfcGoMove object. The move is
    /// not a pass move. @a stone indicates the color and location of the stone
    /// that was placed by the move on the board.
    ///
    /// @exception std::invalid_argument Is thrown if @a stone is nullptr.
    SgfcGoMove(std::shared_ptr<ISgfcGoStone> stone);

    /// @brief Initializes a newly constructed SgfcGoMove object. The move is
    /// a pass move. @a playerColor indicates the color of the player who made
    /// the move.
    SgfcGoMove(SgfcColor playerColor);

    /// @brief Destroys and cleans up the SgfcGoMove object.
    virtual ~SgfcGoMove();

    virtual bool IsPassMove() const override;
    virtual std::shared_ptr<ISgfcGoStone> GetStone() const override;
    virtual SgfcColor GetPlayerColor() const override;
    virtual std::shared_ptr<ISgfcGoPoint> GetStoneLocation() const override;

  private:
    SgfcColor playerColor;
    std::shared_ptr<ISgfcGoStone> stone;
  };
}
