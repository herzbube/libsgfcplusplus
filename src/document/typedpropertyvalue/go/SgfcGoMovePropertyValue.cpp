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
#include "../../../../include/SgfcConstants.h"
#include "../../../game/go/SgfcGoMove.h"
#include "../../../game/go/SgfcGoPoint.h"
#include "../../../game/go/SgfcGoStone.h"
#include "SgfcGoMovePropertyValue.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcGoMovePropertyValue::SgfcGoMovePropertyValue(std::shared_ptr<ISgfcGoMove> goMove)
    : SgfcMovePropertyValue(GetRawValueOrThrow(goMove), GetRawValueOrThrow(goMove))
    , goMove(goMove)
  {
  }

  SgfcGoMovePropertyValue::~SgfcGoMovePropertyValue()
  {
  }

  const ISgfcGoMovePropertyValue* SgfcGoMovePropertyValue::ToGoMoveValue() const
  {
    return this;
  }

  std::shared_ptr<ISgfcGoMove> SgfcGoMovePropertyValue::GetGoMove() const
  {
    return this->goMove;
  }

  std::string SgfcGoMovePropertyValue::GetRawValueOrThrow(std::shared_ptr<ISgfcGoMove> goMove)
  {
    if (goMove == nullptr)
      throw std::invalid_argument("SgfcGoMovePropertyValue constructor failed: go move object is nullptr");

    if (goMove->IsPassMove())
      return SgfcConstants::GoMovePassString;
    else
      return goMove->GetStone()->GetLocation()->GetPosition(SgfcGoPointNotation::Sgf);
  }
}
