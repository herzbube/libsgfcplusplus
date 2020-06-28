// Project includes
#include "../../../include/ISgfcGoStone.h"
#include "SgfcGoMove.h"

namespace LibSgfcPlusPlus
{
  SgfcGoMove::SgfcGoMove(std::shared_ptr<ISgfcGoStone> stone)
    : playerColor(SgfcColor::Black)
    , stone(stone)
  {
    if (this->stone == nullptr)
      throw std::invalid_argument("SgfcGoMove constructor failed: stone object is nullptr");

    this->playerColor = this->stone->GetColor();
  }

  SgfcGoMove::SgfcGoMove(SgfcColor playerColor)
    : playerColor(playerColor)
    , stone(nullptr)
  {
  }

  SgfcGoMove::~SgfcGoMove()
  {
  }

  bool SgfcGoMove::IsPassMove() const
  {
    return (this->stone == nullptr);
  }

  std::shared_ptr<ISgfcGoStone> SgfcGoMove::GetStone() const
  {
    return this->stone;
  }

  SgfcColor SgfcGoMove::GetPlayerColor() const
  {
    return this->playerColor;
  }

  std::shared_ptr<ISgfcGoPoint> SgfcGoMove::GetStoneLocation() const
  {
    if (IsPassMove())
      return nullptr;
    else
      return this->stone->GetLocation();
  }
}
