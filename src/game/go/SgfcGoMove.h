#pragma once

// Project includes
#include "../../../include/ISgfcGoMove.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoMove class provides an implementation of the
  /// ISgfcGoMove interface. See the interface header file for
  /// documentation.
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

    virtual bool IsPassMove() const;
    virtual std::shared_ptr<ISgfcGoStone> GetStone() const;
    virtual SgfcColor GetPlayerColor() const;
    virtual std::shared_ptr<ISgfcGoPoint> GetStoneLocation() const;

  private:
    SgfcColor playerColor;
    std::shared_ptr<ISgfcGoStone> stone;
  };
}
