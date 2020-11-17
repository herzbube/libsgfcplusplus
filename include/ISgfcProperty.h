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
#include "ISgfcPropertyValue.h"
#include "SgfcPropertyType.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcBoardSizeProperty;
  class ISgfcGameTypeProperty;

  /// @brief The ISgfcProperty interface provides access to the data of a single
  /// property of an SGF node. One property has 0-n values.
  ///
  /// @ingroup public-api
  /// @ingroup property
  class SGFCPLUSPLUS_EXPORT ISgfcProperty
  {
  public:
    /// @brief Initializes a newly constructed ISgfcProperty object.
    ISgfcProperty();

    /// @brief Destroys and cleans up the ISgfcProperty object.
    virtual ~ISgfcProperty();

    /// @brief Returns the type of the property. Returns
    /// SgfcPropertyType::Unknown if the property is a custom property that is
    /// not defined in the SGF standard.
    ///
    /// The property type cannot be changed after the ISgfcProperty has been
    /// constructed.
    virtual SgfcPropertyType GetPropertyType() const = 0;

    /// @brief Returns the name of the property.
    ///
    /// The property name cannot be changed after the ISgfcProperty has been
    /// constructed.
    ///
    /// All properties defined in the SGF standard have a name that consists of
    /// two uppercase letters. Application-specific properties not defined in
    /// the standard may not adhere to this restriction (although the standard
    /// advises against this).
    virtual std::string GetPropertyName() const = 0;

    /// @brief Returns true if the property has one or more values. Returns
    /// false if the property has no values.
    virtual bool HasPropertyValues() const = 0;

    /// @brief Returns a collection with the values of the property. The
    /// collection is empty if the property has no values. The order in which
    /// values appear in the collection matches the order in which values were
    /// specified when the ISgfcProperty was constructed.
    ///
    /// The EBNF in the SGF standard says that at least one value must be
    /// present. This can be a value that has the value type "None", which is
    /// defined to be an empty string. The meaning for the file content is
    /// clear: Something like XY[] is possible. In the library's object model,
    /// however, a "None" value is translated to an empty collection.
    virtual std::vector<std::shared_ptr<ISgfcPropertyValue>> GetPropertyValues() const = 0;

    /// @brief Sets the values of the property to @a propertyValues. The
    /// previous values are discarded. @a propertyValues may not contain
    /// @e nullptr. @a propertyValues may not contain duplicates.
    ///
    /// This setter makes no attempt to check the validity of the property
    /// values. A last-ditch attempt at validation is made by SGFC later when
    /// the game tree is written to an SGF file or to an SGF content string, but
    /// this is unlikely to catch all mistakes. It is ultimately the
    /// responsibility of the library client to take care that the values
    /// are valid. The consequence of faulty values is that the library client
    /// might be unable to read in the game tree again after it has been written
    /// out.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyValues contains
    /// a @e nullptr element, or if @a propertyValues contains duplicate
    /// elements.
    virtual void SetPropertyValues(
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues) = 0;

    /// @brief Adds @a propertyValue as the last value to the property's
    /// collection of values. @a propertyValue may not be @e nullptr.
    ///
    /// This setter makes no attempt to check the validity of the property's
    /// collection of values after adding @a propertyValue.
    ///
    /// @see SetPropertyValues()
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyValue is
    /// @e nullptr or if @a propertyValue is already in the property's
    /// collection of values.
    virtual void AppendPropertyValue(std::shared_ptr<ISgfcPropertyValue> propertyValue) = 0;

    /// @brief Removes @a propertyValue from the property's collection of
    /// values.
    ///
    /// This setter makes no attempt to check the validity of the property's
    /// collection of values after removing @a propertyValue.
    ///
    /// @see SetPropertyValues()
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyValue is not
    /// part of the property's collection of values.
    virtual void RemovePropertyValue(std::shared_ptr<ISgfcPropertyValue> propertyValue) = 0;

    /// @brief Removes all values from the property's collection of values.
    ///
    /// This setter makes no attempt to check the validity of the property's
    /// collection of values after removing all values.
    ///
    /// @see SetPropertyValues()
    virtual void RemoveAllPropertyValues() = 0;

    /// @brief Returns the property's first value if the property has any
    /// values. Returns @e nullptr if the property has no values.
    ///
    /// This is a convenience method for properties that can have only a single
    /// value.
    virtual std::shared_ptr<ISgfcPropertyValue> GetPropertyValue() const = 0;

    /// @brief Returns an ISgfcGameTypeProperty object if GetPropertyType()
    /// returns SgfcPropertyType::GM. Returns @e nullptr otherwise.
    /// The caller is not the owner of the returned object.
    virtual const ISgfcGameTypeProperty* ToGameTypeProperty() const = 0;

    /// @brief Returns an ISgfcBoardSizeProperty object if GetPropertyType()
    /// returns SgfcPropertyType::SZ. Returns @e nullptr otherwise.
    /// The caller is not the owner of the returned object.
    virtual const ISgfcBoardSizeProperty* ToBoardSizeProperty() const = 0;
  };
}
