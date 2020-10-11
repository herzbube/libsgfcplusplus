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
  SgfcGoStonePropertyValue::SgfcGoStonePropertyValue(const std::string& rawValue, SgfcBoardSize boardSize, SgfcColor color)
    : SgfcStonePropertyValue(rawValue)
    , goStone(new SgfcGoStone(color, std::shared_ptr<ISgfcGoPoint>(new SgfcGoPoint(rawValue, boardSize))))
  {
  }

  SgfcGoStonePropertyValue::SgfcGoStonePropertyValue(const std::string& rawValue, SgfcColor color)
    : SgfcStonePropertyValue(rawValue)
    , goStone(new SgfcGoStone(color))
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
}
