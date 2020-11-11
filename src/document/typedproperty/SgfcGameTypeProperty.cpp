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
#include "../../../include/ISgfcNumberPropertyValue.h"
#include "../../../include/SgfcConstants.h"
#include "../../SgfcUtility.h"
#include "SgfcGameTypeProperty.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcGameTypeProperty::SgfcGameTypeProperty()
    : SgfcProperty(SgfcPropertyType::GM,
                   SgfcUtility::MapPropertyTypeToPropertyName(SgfcPropertyType::GM))
  {
  }

  SgfcGameTypeProperty::SgfcGameTypeProperty(
    std::shared_ptr<ISgfcNumberPropertyValue> propertyValue)
    : SgfcProperty(SgfcPropertyType::GM,
                   SgfcUtility::MapPropertyTypeToPropertyName(SgfcPropertyType::GM),
                   std::vector<std::shared_ptr<ISgfcPropertyValue>>{propertyValue})
  {
    if (propertyValue == nullptr)
      throw std::invalid_argument("SgfcGameTypeProperty constructor failed: Property value is nullptr");
  }

  SgfcGameTypeProperty::~SgfcGameTypeProperty()
  {
  }

  const ISgfcGameTypeProperty* SgfcGameTypeProperty::ToGameTypeProperty() const
  {
    return this;
  }

  SgfcGameType SgfcGameTypeProperty::GetGameType() const
  {
    SgfcNumber gameTypeAsNumber = GetGameTypeAsNumber();

    return SgfcUtility::MapNumberValueToGameType(
      gameTypeAsNumber);
  }

  SgfcNumber SgfcGameTypeProperty::GetGameTypeAsNumber() const
  {
    auto propertyValue = GetPropertyValue();

    if (propertyValue == nullptr)
      return SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType);

    // Constructor did checks for us
    const ISgfcNumberPropertyValue* numberValue =
      propertyValue->ToSingleValue()->ToNumberValue();

    return numberValue->GetNumberValue();
  }
}
