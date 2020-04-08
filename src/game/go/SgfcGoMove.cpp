// Project includes
#include "../../../include/ISgfcGoStone.h"
#include "SgfcGoMove.h"

namespace LibSgfcPlusPlus
{
  SgfcGoMove::SgfcGoMove(std::shared_ptr<ISgfcGoStone> stone)
    : stone(stone)
  {
  }

  SgfcGoMove::~SgfcGoMove()
  {
  }

  std::shared_ptr<ISgfcGoStone> SgfcGoMove::GetStone() const
  {
    return this->stone;
  }

  SgfcColor SgfcGoMove::GetPlayerColor() const
  {
    return this->stone->GetColor();
  }

  std::shared_ptr<ISgfcGoPoint> SgfcGoMove::GetStoneLocation() const
  {
    return this->stone->GetLocation();
  }
}
