// Project includes
#include "SgfcGoStone.h"

namespace LibSgfcPlusPlus
{
  SgfcGoStone::SgfcGoStone(SgfcColor color, std::shared_ptr<ISgfcGoPoint> location)
    : color(color)
    , location(location)
  {
    if (this->location == nullptr)
      throw std::invalid_argument("SgfcGoStone constructor failed: location object is nullptr");
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
