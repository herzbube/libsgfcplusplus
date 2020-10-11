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

// Project includes
#include "../../../include/ISgfcGoStone.h"
#include "SgfcGoMove.h"

// C++ Standard Library includes
#include <stdexcept>

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
