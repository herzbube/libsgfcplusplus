// Project includes
#include "SgfcGoStone.h"

namespace LibSgfcPlusPlus
{
  SgfcGoStone::SgfcGoStone(SgfcColor color, std::shared_ptr<ISgfcGoPoint> location)
    : color(color)
    , location(location)
  {
  }

  SgfcGoStone::~SgfcGoStone()
  {
  }

  SgfcColor SgfcGoStone::GetColor() const
  {
    return this->color;
  }

  std::shared_ptr<ISgfcGoPoint> SgfcGoStone::GetLocation() const
  {
    return this->location;
  }
}
