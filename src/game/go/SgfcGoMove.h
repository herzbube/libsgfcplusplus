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
    SgfcGoMove(std::shared_ptr<ISgfcGoStone> stone);
    virtual ~SgfcGoMove();

    virtual std::shared_ptr<ISgfcGoStone> GetStone() const;
    virtual SgfcColor GetPlayerColor() const;
    virtual std::shared_ptr<ISgfcGoPoint> GetStoneLocation() const;

  private:
    std::shared_ptr<ISgfcGoStone> stone;
  };
}
