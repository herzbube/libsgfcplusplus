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
#include "SgfcMovePropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcMovePropertyValue::SgfcMovePropertyValue(const std::string& rawValue)
    : SgfcSinglePropertyValue(rawValue, true)
  {
  }

  SgfcMovePropertyValue::~SgfcMovePropertyValue()
  {
  }

  SgfcPropertyValueType SgfcMovePropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Move;
  }

  std::string SgfcMovePropertyValue::GetRawMoveValue() const
  {
    return SgfcSinglePropertyValue::GetRawValue();
  }

  const ISgfcMovePropertyValue* SgfcMovePropertyValue::ToMoveValue() const
  {
    return this;
  }

  const ISgfcGoMovePropertyValue* SgfcMovePropertyValue::ToGoMoveValue() const
  {
    return nullptr;
  }
}
