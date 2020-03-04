#pragma once

// Project includes
#include "../../../include/ISgfcGoStone.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoStone class provides an implementation of the
  /// ISgfcGoStone interface. See the interface header file for
  /// documentation.
  class SgfcGoStone : public ISgfcGoStone
  {
  public:
    SgfcGoStone(SgfcColor color, std::shared_ptr<ISgfcGoPoint> location);
    virtual ~SgfcGoStone();

    virtual SgfcColor GetColor() const;
    virtual std::shared_ptr<ISgfcGoPoint> GetLocation() const;

  private:
    SgfcColor color;
    std::shared_ptr<ISgfcGoPoint> location;
  };
}
