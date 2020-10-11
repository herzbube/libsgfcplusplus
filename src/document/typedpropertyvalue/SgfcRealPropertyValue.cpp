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
#include "SgfcRealPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcRealPropertyValue::SgfcRealPropertyValue(const std::string& rawValue, SgfcReal realValue)
    : SgfcSinglePropertyValue(rawValue, true)
    , realValue(realValue)
  {
  }

  SgfcRealPropertyValue::SgfcRealPropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage)
    : SgfcSinglePropertyValue(rawValue, typeConversionErrorMessage)
    , realValue(0.0)
  {
  }

  SgfcRealPropertyValue::~SgfcRealPropertyValue()
  {
  }

  SgfcPropertyValueType SgfcRealPropertyValue::GetValueType() const
  {
    return SgfcPropertyValueType::Real;
  }

  SgfcReal SgfcRealPropertyValue::GetRealValue() const
  {
    ThrowIfHasNotTypedValue();
    return this->realValue;
  }

  const ISgfcRealPropertyValue* SgfcRealPropertyValue::ToRealValue() const
  {
    return this;
  }
}
