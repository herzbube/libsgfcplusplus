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
#include "../../../include/SgfcConstants.h"
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

    if (! propertyValue->HasTypedValue() || propertyValue->GetValueType() != SgfcPropertyValueType::Number)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Property value is not a Number value");
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
    if (! singleValue1->HasTypedValue() || singleValue1->GetValueType() != SgfcPropertyValueType::Number)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Value 1 of composed property value is not a Number value");

    auto singleValue2 = propertyValue->GetValue2();
    if (singleValue2 == nullptr)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Value 2 of composed property value is nullptr");
    if (! singleValue2->HasTypedValue() || singleValue2->GetValueType() != SgfcPropertyValueType::Number)
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
    auto propertyValue = GetPropertyValue();

    if (propertyValue == nullptr)
      return SgfcUtility::GetDefaultBoardSize(gameType);

    SgfcBoardSize boardSize;
    if (propertyValue->IsComposedValue())
      boardSize = GetBoardSizeFromComposedValue(propertyValue->ToComposedValue());
    else
      boardSize = GetBoardSizeFromSingleValue(propertyValue->ToSingleValue());

    bool isBoardSizeValid = SgfcUtility::IsBoardSizeValid(boardSize, gameType);
    if (isBoardSizeValid)
      return boardSize;
    else
      return SgfcConstants::BoardSizeInvalid;
  }

  SgfcBoardSize SgfcBoardSizeProperty::GetBoardSizeFromSingleValue(const ISgfcSinglePropertyValue* singleValue) const
  {
    // Constructor did checks for us
    SgfcNumber numberOfColumnsAndRows = singleValue->ToNumberValue()->GetNumberValue();
    return { numberOfColumnsAndRows, numberOfColumnsAndRows };
  }

  SgfcBoardSize SgfcBoardSizeProperty::GetBoardSizeFromComposedValue(const ISgfcComposedPropertyValue* composedValue) const
  {
    auto singleValue1 = composedValue->GetValue1();
    auto singleValue2 = composedValue->GetValue2();

    return
    {
      // Constructor did checks for us
      singleValue1->ToNumberValue()->GetNumberValue(),
      singleValue2->ToNumberValue()->GetNumberValue()
    };
  }
}
