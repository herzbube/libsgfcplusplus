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
#include "SgfcPropertyType.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcComposedPropertyValue;
  class ISgfcBoardSizeProperty;
  class ISgfcGameTypeProperty;
  class ISgfcNumberPropertyValue;
  class ISgfcProperty;
  class ISgfcPropertyValue;

  /// @brief The ISgfcPropertyFactory interface provides factory methods
  /// for creating ISgfcProperty objects, and objects of every known sub-type
  /// of ISgfcProperty.
  ///
  /// @ingroup public-api
  /// @ingroup factory
  /// @ingroup property
  class SGFCPLUSPLUS_EXPORT ISgfcPropertyFactory
  {
  public:
    /// @brief Initializes a newly constructed ISgfcPropertyFactory object.
    ISgfcPropertyFactory();

    /// @brief Destroys and cleans up the ISgfcPropertyFactory object.
    virtual ~ISgfcPropertyFactory();

    /// @brief Returns a newly constructed ISgfcProperty object that has the
    /// specified property type @a propertyType. The property has no values.
    /// The property is not associated with any node.
    ///
    /// If @a propertyType is SgfcPropertyType::SZ or SgfcPropertyType::GM, the
    /// returned ISgfcProperty object is an instance of ISgfcBoardSizeProperty
    /// or ISgfcGameTypeProperty.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyType is
    /// SgfcPropertyType::Unknown.
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(SgfcPropertyType propertyType) = 0;

    /// @brief Returns a newly constructed ISgfcProperty object that has the
    /// specified property type @a propertyType and the specified property
    /// value @a propertyValue. The property is not associated with any node.
    /// The ISgfcProperty object takes ownership of the ISgfcPropertyValue
    /// object @a propertyValue.
    ///
    /// If @a propertyType is SgfcPropertyType::SZ or SgfcPropertyType::GM, the
    /// returned ISgfcProperty object is an instance of ISgfcBoardSizeProperty
    /// or ISgfcGameTypeProperty.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyType is
    /// SgfcPropertyType::Unknown, or, in case @a propertyType is
    /// SgfcPropertyType::SZ or SgfcPropertyType::GM, if @a propertyValue does
    /// not meet the requirements of these property types. See the documentation
    /// of CreateBoardSizeProperty() or CreateGameTypeProperty() for details.
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(
      SgfcPropertyType propertyType,
      std::shared_ptr<ISgfcPropertyValue> propertyValue) = 0;

    /// @brief Returns a newly constructed ISgfcProperty object that has the
    /// specified property type @a propertyType and the specified property
    /// values @a propertyValues. The property is not associated with any node.
    /// The ISgfcProperty object takes ownership of the ISgfcPropertyValue
    /// objects in @a propertyValues.
    ///
    /// If @a propertyType is SgfcPropertyType::SZ or SgfcPropertyType::GM, the
    /// returned ISgfcProperty object is an instance of ISgfcBoardSizeProperty
    /// or ISgfcGameTypeProperty.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyType is
    /// SgfcPropertyType::Unknown, or, in case @a propertyType is
    /// SgfcPropertyType::SZ or SgfcPropertyType::GM, if @a propertyValues
    /// contains more than one value or the value does not meet the requirements
    /// of these property types. See the documentation of
    ///  CreateBoardSizeProperty() or CreateGameTypeProperty() for details.
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(
      SgfcPropertyType propertyType,
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues) = 0;

    /// @brief Returns a newly constructed ISgfcProperty object that has the
    /// specified property name @a propertyName. The property type is inferred
    /// from the property name. The property has no values. The property is not
    /// associated with any node.
    ///
    /// Attempts to map @a propertyName to a value in the enumeration
    /// SgfcPropertyType. If the mapping succeeds the result of invoking this
    /// method is the same as invoking the overload that takes an
    /// SgfcPropertyType value. If the mapping fails then the resulting
    /// ISgfcProperty object has SgfcPropertyType::Unknown.
    ///
    /// If the mapped SgfcPropertyType value is SgfcPropertyType::SZ or
    /// SgfcPropertyType::GM, the returned ISgfcProperty object is an instance
    /// of ISgfcBoardSizeProperty or ISgfcGameTypeProperty.
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(
      const std::string& propertyName) = 0;

    /// @brief Returns a newly constructed ISgfcProperty object that has the
    /// specified property name @a propertyName and the specified property
    /// value @a propertyValue. The property type is inferred from the
    /// property name. The property is not associated with any node.
    /// The ISgfcProperty object takes ownership of the ISgfcPropertyValue
    /// object @a propertyValue.
    ///
    /// Attempts to map @a propertyName to a value in the enumeration
    /// SgfcPropertyType. If the mapping succeeds the result of invoking this
    /// method is the same as invoking the overload that takes an
    /// SgfcPropertyType value. If the mapping fails then the resulting
    /// ISgfcProperty object has SgfcPropertyType::Unknown.
    ///
    /// If the mapped SgfcPropertyType value is SgfcPropertyType::SZ or
    /// SgfcPropertyType::GM, the returned ISgfcProperty object is an instance
    /// of ISgfcBoardSizeProperty or ISgfcGameTypeProperty.
    ///
    /// @exception std::invalid_argument Is thrown if the mapped
    /// SgfcPropertyType value is SgfcPropertyType::SZ or SgfcPropertyType::GM
    /// and @a propertyValue does not meet the requirements of these property
    /// types. See the documentation of CreateBoardSizeProperty() or
    /// CreateGameTypeProperty() for details.
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(
      const std::string& propertyName,
      std::shared_ptr<ISgfcPropertyValue> propertyValue) = 0;

    /// @brief Returns a newly constructed ISgfcProperty object that has the
    /// specified property name @a propertyName and the specified property
    /// values @a propertyValues. The property type is inferred from the
    /// property name. The property is not associated with any node.
    /// The ISgfcProperty object takes ownership of the ISgfcPropertyValue
    /// objects in @a propertyValues.
    ///
    /// Attempts to map @a propertyName to a value in the enumeration
    /// SgfcPropertyType. If the mapping succeeds the result of invoking this
    /// method is the same as invoking the overload that takes an
    /// SgfcPropertyType value. If the mapping fails then the resulting
    /// ISgfcProperty object has SgfcPropertyType::Unknown.
    ///
    /// If the mapped SgfcPropertyType value is SgfcPropertyType::SZ or
    /// SgfcPropertyType::GM, the returned ISgfcProperty object is an instance
    /// of ISgfcBoardSizeProperty or ISgfcGameTypeProperty.
    ///
    /// @exception std::invalid_argument Is thrown if the mapped
    /// SgfcPropertyType value is SgfcPropertyType::SZ or SgfcPropertyType::GM
    /// and @a propertyValues contains more than one value or the value does
    /// not meet the requirements of these property types. See the
    /// documentation of CreateBoardSizeProperty() or CreateGameTypeProperty()
    /// for details.
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(
      const std::string& propertyName,
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues) = 0;

    /// @brief Returns a newly constructed ISgfcBoardSizeProperty object that
    /// has no value. The property is not associated with any node.
    virtual std::shared_ptr<ISgfcBoardSizeProperty> CreateBoardSizeProperty() = 0;

    /// @brief Returns a newly constructed ISgfcBoardSizeProperty object that
    /// has the specified property value @a propertyValue. The property is not
    /// associated with any node. The ISgfcBoardSizeProperty object takes
    /// ownership of the ISgfcNumberPropertyValue object @a propertyValue.
    ///
    /// This overload constructs an ISgfcBoardSizeProperty object that
    /// describes a square board.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyValue is
    /// @e nullptr or if the @a propertyValue object's method HasTypedValue()
    /// returns false.
    virtual std::shared_ptr<ISgfcBoardSizeProperty> CreateBoardSizeProperty(
      std::shared_ptr<ISgfcNumberPropertyValue> propertyValue) = 0;

    /// @brief Returns a newly constructed ISgfcBoardSizeProperty object that
    /// has the specified property value @a propertyValue. The property is not
    /// associated with any node. The ISgfcBoardSizeProperty object takes
    /// ownership of the ISgfcComposedPropertyValue object @a propertyValue.
    ///
    /// This overload constructs an ISgfcBoardSizeProperty object that
    /// describes a rectangular board.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyValue is
    /// @e nullptr or if the @a propertyValue object is not composed of two
    /// ISgfcNumberPropertyValue objects, or if any of the
    /// ISgfcNumberPropertyValue object's method HasTypedValue() returns false.
    virtual std::shared_ptr<ISgfcBoardSizeProperty> CreateBoardSizeProperty(
      std::shared_ptr<ISgfcComposedPropertyValue> propertyValue) = 0;

    /// @brief Returns a newly constructed ISgfcGameTypeProperty object that
    /// has no value. The property is not associated with any node.
    virtual std::shared_ptr<ISgfcGameTypeProperty> CreateGameTypeProperty() = 0;

    /// @brief Returns a newly constructed ISgfcGameTypeProperty object that
    /// has the specified property value @a propertyValue. The property is not
    /// associated with any node. The ISgfcGameTypeProperty object takes
    /// ownership of the ISgfcNumberPropertyValue object @a propertyValue.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyValue is
    /// @e nullptr or if the @a propertyValue object's method HasTypedValue()
    /// returns false.
    virtual std::shared_ptr<ISgfcGameTypeProperty> CreateGameTypeProperty(
      std::shared_ptr<ISgfcNumberPropertyValue> propertyValue) = 0;
  };
}
