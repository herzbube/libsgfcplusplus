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
#include "SgfcGoPointPropertyValue.h"
#include "../../../game/go/SgfcGoPoint.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcGoPointPropertyValue::SgfcGoPointPropertyValue(std::shared_ptr<ISgfcGoPoint> goPoint)
    : SgfcPointPropertyValue(GetRawValueOrThrow(goPoint), GetRawValueOrThrow(goPoint))
    , goPoint(goPoint)
  {
  }

  SgfcGoPointPropertyValue::~SgfcGoPointPropertyValue()
  {
  }

  const ISgfcGoPointPropertyValue* SgfcGoPointPropertyValue::ToGoPointValue() const
  {
    return this;
  }

  std::shared_ptr<ISgfcGoPoint> SgfcGoPointPropertyValue::GetGoPoint() const
  {
    return this->goPoint;
  }

  std::string SgfcGoPointPropertyValue::GetRawValueOrThrow(std::shared_ptr<ISgfcGoPoint> goPoint)
  {
    if (goPoint == nullptr)
      throw std::invalid_argument("SgfcGoPointPropertyValue constructor failed: go point object is nullptr");

    return goPoint->GetPosition(SgfcGoPointNotation::Sgf);
  }
}
