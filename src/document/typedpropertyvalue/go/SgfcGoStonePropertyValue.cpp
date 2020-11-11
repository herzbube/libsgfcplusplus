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
#include "SgfcGoStonePropertyValue.h"
#include "../../../game/go/SgfcGoPoint.h"
#include "../../../game/go/SgfcGoStone.h"

namespace LibSgfcPlusPlus
{
  SgfcGoStonePropertyValue::SgfcGoStonePropertyValue(std::shared_ptr<ISgfcGoStone> goStone)
    : SgfcStonePropertyValue(GetRawValueOrThrow(goStone))
    , goStone(goStone)
  {
  }

  SgfcGoStonePropertyValue::~SgfcGoStonePropertyValue()
  {
  }

  const ISgfcGoStonePropertyValue* SgfcGoStonePropertyValue::ToGoStoneValue() const
  {
    return this;
  }

  std::shared_ptr<ISgfcGoStone> SgfcGoStonePropertyValue::GetGoStone() const
  {
    return this->goStone;
  }

  std::string SgfcGoStonePropertyValue::GetRawValueOrThrow(std::shared_ptr<ISgfcGoStone> goStone)
  {
    if (goStone == nullptr)
      throw std::invalid_argument("SgfcGoStonePropertyValue constructor failed: go stone object is nullptr");

    return goStone->GetLocation()->GetPosition(SgfcGoPointNotation::Sgf);
  }
}
