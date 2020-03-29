#pragma once

// Project includes
#include "SgfcPropertyType.h"

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
  class ISgfcPropertyFactory
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
    /// @exception std::invalid_argument Is thrown if @a propertyType is
    /// SgfcPropertyType::Unknown.
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(SgfcPropertyType propertyType) = 0;

    /// @brief Returns a newly constructed ISgfcProperty object that has the
    /// specified property type @a propertyType and the specified property
    /// value @a propertyValue. The property is not associated with any node.
    /// The ISgfcProperty object takes ownership of the ISgfcPropertyValue
    /// object @a propertyValue.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyType is
    /// SgfcPropertyType::Unknown.
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(
      SgfcPropertyType propertyType,
      std::shared_ptr<ISgfcPropertyValue> propertyValue) = 0;

    /// @brief Returns a newly constructed ISgfcProperty object that has the
    /// specified property type @a propertyType and the specified property
    /// values @a propertyValues. The property is not associated with any node.
    /// The ISgfcProperty object takes ownership of the ISgfcPropertyValue
    /// objects in @a propertyValues.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyType is
    /// SgfcPropertyType::Unknown.
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
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(const std::string& propertyName) = 0;

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
    /// null or if the @a propertyValue object's method HasTypedValue() returns
    /// false.
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
    /// null or if the @a propertyValue object is not composed of two
    /// ISgfcNumberPropertyValue objects, or if any of the
    /// ISgfcNumberPropertyValue object's method HasTypedValue() returns false.
    virtual std::shared_ptr<ISgfcBoardSizeProperty> CreateBoardSizeProperty(
      std::shared_ptr<ISgfcComposedPropertyValue> propertyValue) = 0;

    /// @brief Returns a newly constructed ISgfcGameTypeProperty object that
    /// has no vaue. The property is not associated with any node.
    virtual std::shared_ptr<ISgfcGameTypeProperty> CreateGameTypeProperty() = 0;

    /// @brief Returns a newly constructed ISgfcGameTypeProperty object that
    /// has the specified property value @a propertyValue. The property is not
    /// associated with any node. The ISgfcProperty object takes ownership of
    /// the ISgfcNumberPropertyValue object @a propertyValue.
    ///
    /// @exception std::invalid_argument is thrown if @a propertyValue is
    /// null or if the @a propertyValue object's method HasTypedValue() returns
    /// false.
    virtual std::shared_ptr<ISgfcGameTypeProperty> CreateGameTypeProperty(
      std::shared_ptr<ISgfcNumberPropertyValue> propertyValue) = 0;
  };
}
