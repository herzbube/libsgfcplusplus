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

// C++ Standard Library includes
#include <algorithm>
#include <set>
#include <stdexcept>

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
  {
    SetPropertyValues(propertyValues);
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

  bool SgfcProperty::HasPropertyValues() const
  {
    return ! this->propertyValues.empty();
  }

  std::vector<std::shared_ptr<ISgfcPropertyValue>> SgfcProperty::GetPropertyValues() const
  {
    return this->propertyValues;
  }

  void SgfcProperty::SetPropertyValues(const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
  {
    std::set<std::shared_ptr<ISgfcPropertyValue>> uniquePropertyValues(propertyValues.begin(), propertyValues.end());
    if (uniquePropertyValues.size() != propertyValues.size())
      throw std::invalid_argument("SetPropertyValues failed: Property value list contains duplicate elements");

    auto result = std::find(std::begin(propertyValues), std::end(propertyValues), nullptr);
    if (result != std::end(propertyValues))
      throw std::invalid_argument("SetPropertyValues failed: Property value list contains nullptr element");

    this->propertyValues = propertyValues;
  }

  void SgfcProperty::AppendPropertyValue(std::shared_ptr<ISgfcPropertyValue> propertyValue)
  {
    if (propertyValue == nullptr)
      throw std::invalid_argument("AppendPropertyValue failed: Property value argument is null");

    auto result = std::find(std::begin(this->propertyValues), std::end(this->propertyValues), propertyValue);
    if (result != std::end(this->propertyValues))
      throw std::invalid_argument("AppendPropertyValue failed: Property value is already part of the property");

    this->propertyValues.push_back(propertyValue);
  }

  void SgfcProperty::RemovePropertyValue(std::shared_ptr<ISgfcPropertyValue> propertyValue)
  {
    // This works because std::shared_ptr::operator==() compares pointer values
    auto result = std::find(std::begin(this->propertyValues), std::end(this->propertyValues), propertyValue);
    if (result == std::end(this->propertyValues))
      throw std::invalid_argument("RemovePropertyValue failed: Property value is not part of the property");

    this->propertyValues.erase(result);
  }

  void SgfcProperty::RemoveAllPropertyValues()
  {
    this->propertyValues.clear();
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
