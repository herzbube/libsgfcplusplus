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
#include "SgfcStonePropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcStonePropertyValue::SgfcStonePropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(rawValue, SgfcPropertyValueType::Stone)
  {
  }

  SgfcStonePropertyValue::~SgfcStonePropertyValue()
  {
  }

  std::string SgfcStonePropertyValue::GetStoneValue() const
  {
    return SgfcSinglePropertyValue::GetRawValue();
  }

  const ISgfcStonePropertyValue* SgfcStonePropertyValue::ToStoneValue() const
  {
    return this;
  }

  const ISgfcGoStonePropertyValue* SgfcStonePropertyValue::ToGoStoneValue() const
  {
    return nullptr;
  }
}
