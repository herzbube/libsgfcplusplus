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

#pragma once

// Project includes
#include "../../include/ISgfcProperty.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcProperty class provides an implementation of the
  /// ISgfcProperty interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup property
  class SgfcProperty : virtual public ISgfcProperty
  {
  public:
    /// @brief Initializes a newly constructed SgfcProperty object. The property
    /// has the specified type @a propertyType and name @a propertyName. The
    /// property has no values.
    SgfcProperty(
      SgfcPropertyType propertyType,
      const std::string& propertyName);

    /// @brief Initializes a newly constructed SgfcProperty object. The property
    /// has the specified type @a propertyType, name @a propertyName and
    /// property values @a propertyValues.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyValues contains
    /// a @e nullptr element, or if @a propertyValues contains duplicate
    /// elements.
    SgfcProperty(
      SgfcPropertyType propertyType,
      const std::string& propertyName,
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);

    /// @brief Destroys and cleans up the SgfcProperty object.
    virtual ~SgfcProperty();

    virtual SgfcPropertyType GetPropertyType() const override;
    virtual std::string GetPropertyName() const override;

    virtual SgfcPropertyCategory GetPropertyCategory() const override;
    virtual SgfcPropertyTraits GetTraits() const override;
    virtual bool HasTrait(SgfcPropertyTrait trait) const override;

    virtual bool HasPropertyValues() const override;
    virtual std::vector<std::shared_ptr<ISgfcPropertyValue>> GetPropertyValues() const override;
    virtual void SetPropertyValues(const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues) override;
    virtual void AppendPropertyValue(std::shared_ptr<ISgfcPropertyValue> propertyValue) override;
    virtual void RemovePropertyValue(std::shared_ptr<ISgfcPropertyValue> propertyValue) override;
    virtual void RemoveAllPropertyValues() override;
    virtual std::shared_ptr<ISgfcPropertyValue> GetPropertyValue() const override;

    virtual const ISgfcGameTypeProperty* ToGameTypeProperty() const override;
    virtual const ISgfcBoardSizeProperty* ToBoardSizeProperty() const override;

  private:
    SgfcPropertyType propertyType;
    std::string propertyName;
    std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues;
  };
}
