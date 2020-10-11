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
#include "SgfcGoStone.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcGoStone::SgfcGoStone(SgfcColor color, std::shared_ptr<ISgfcGoPoint> location)
    : color(color)
    , location(location)
  {
    if (this->location == nullptr)
      throw std::invalid_argument("SgfcGoStone constructor failed: location object is nullptr");
  }

  SgfcGoStone::SgfcGoStone(SgfcColor color)
    : color(color)
    , location(nullptr)
  {
  }

  SgfcGoStone::~SgfcGoStone()
  {
  }

  SgfcColor SgfcGoStone::GetColor() const
  {
    return this->color;
  }

  bool SgfcGoStone::HasLocation() const
  {
    return this->location != nullptr;
  }

  std::shared_ptr<ISgfcGoPoint> SgfcGoStone::GetLocation() const
  {
    return this->location;
  }
}
