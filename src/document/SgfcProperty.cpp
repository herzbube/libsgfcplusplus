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
#include "SgfcProperty.h"

namespace LibSgfcPlusPlus
{
  SgfcProperty::SgfcProperty(
    SgfcPropertyType propertyType,
    const std::string& propertyName)
    : propertyType(propertyType)
    , propertyName(propertyName)
  {
  }

  SgfcProperty::SgfcProperty(
    SgfcPropertyType propertyType,
    const std::string& propertyName,
    const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
    : propertyType(propertyType)
    , propertyName(propertyName)
    , propertyValues(propertyValues)
  {
  }

  SgfcProperty::~SgfcProperty()
  {
  }

  SgfcPropertyType SgfcProperty::GetPropertyType() const
  {
    return this->propertyType;
  }

  std::string SgfcProperty::GetPropertyName() const
  {
    return this->propertyName;
  }

  std::vector<std::shared_ptr<ISgfcPropertyValue>> SgfcProperty::GetPropertyValues() const
  {
    return this->propertyValues;
  }

  void SgfcProperty::SetPropertyValues(
    const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
  {
    this->propertyValues = propertyValues;
  }

  std::shared_ptr<ISgfcPropertyValue> SgfcProperty::GetPropertyValue() const
  {
    auto it = this->propertyValues.cbegin();
    if (it != this->propertyValues.cend())
      return *it;
    else
      return nullptr;
  }

  const ISgfcGameTypeProperty* SgfcProperty::ToGameTypeProperty() const
  {
    return nullptr;
  }

  const ISgfcBoardSizeProperty* SgfcProperty::ToBoardSizeProperty() const
  {
    return nullptr;
  }
}
