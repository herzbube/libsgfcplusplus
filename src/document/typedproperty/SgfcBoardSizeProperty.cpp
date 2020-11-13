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
#include "../../../include/ISgfcComposedPropertyValue.h"
#include "../../../include/ISgfcNumberPropertyValue.h"
#include "../../game/SgfcGameUtility.h"
#include "../../SgfcUtility.h"
#include "SgfcBoardSizeProperty.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcBoardSizeProperty::SgfcBoardSizeProperty()
    : SgfcProperty(SgfcPropertyType::SZ,
                   SgfcUtility::MapPropertyTypeToPropertyName(SgfcPropertyType::SZ))
  {
  }

  SgfcBoardSizeProperty::SgfcBoardSizeProperty(
    std::shared_ptr<ISgfcNumberPropertyValue> propertyValue)
    : SgfcProperty(SgfcPropertyType::SZ,
                   SgfcUtility::MapPropertyTypeToPropertyName(SgfcPropertyType::SZ),
                   std::vector<std::shared_ptr<ISgfcPropertyValue>>{propertyValue})
  {
    if (propertyValue == nullptr)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Property value is nullptr");
  }

  SgfcBoardSizeProperty::SgfcBoardSizeProperty(
    std::shared_ptr<ISgfcComposedPropertyValue> propertyValue)
    : SgfcProperty(SgfcPropertyType::SZ,
                   SgfcUtility::MapPropertyTypeToPropertyName(SgfcPropertyType::SZ),
                   std::vector<std::shared_ptr<ISgfcPropertyValue>>{propertyValue})
  {
    if (propertyValue == nullptr)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Property value is nullptr");

    auto singleValue1 = propertyValue->GetValue1();
    if (singleValue1 == nullptr)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Value 1 of composed property value is nullptr");
    if (singleValue1->ToNumberValue() == nullptr)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Value 1 of composed property value is not a Number value");

    auto singleValue2 = propertyValue->GetValue2();
    if (singleValue2 == nullptr)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Value 2 of composed property value is nullptr");
    if (singleValue2->ToNumberValue() == nullptr)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Value 2 of composed property value is not a Number value");
  }

  SgfcBoardSizeProperty::~SgfcBoardSizeProperty()
  {
  }

  const ISgfcBoardSizeProperty* SgfcBoardSizeProperty::ToBoardSizeProperty() const
  {
    return this;
  }

  SgfcBoardSize SgfcBoardSizeProperty::GetBoardSize(SgfcGameType gameType) const
  {
    return SgfcGameUtility::GetBoardSize(GetPropertyValues(), gameType);
  }
}
