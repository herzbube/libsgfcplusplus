#pragma once

// Project includes
#include "../../include/ISgfcPropertyValue.h"
#include "../../include/SgfcPropertyType.h"
#include "../../include/SgfcPropertyValueType.h"
#include "../interface/internal/ISgfcPropertyValueTypeDescriptor.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

// Forward declarations
struct Property;
struct PropValue;

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyDecoder class parses the raw strings that SGFC
  /// provides for SGF properties and their values, and generates proper
  /// objects from those parsing activities.
  class SgfcPropertyDecoder
  {
  public:
    /// @brief Returns the SgfcPropertyType value that corresponds to the
    /// SGF property @a sgfProperty.
    static SgfcPropertyType GetSgfcPropertyTypeFromSgfProperty(Property* sgfProperty);

    /// @brief Parses the specified SGF property @a sgfProperty and returns a
    /// list with the property's values.
    ///
    /// This method relies on certain pre-processing performed by SGFC. Notably:
    /// - Non-string values are trimmed (essential for Double and Color values)
    static std::vector<std::shared_ptr<ISgfcPropertyValue>> GetPropertyValuesFromSgfProperty(
      Property* sgfProperty);

  private:
    SgfcPropertyDecoder();
    virtual ~SgfcPropertyDecoder();

    static std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetValueTypeDescriptorForPropertyType(
      SgfcPropertyType propertyType);

    static std::vector<std::shared_ptr<ISgfcPropertyValue>> GetSgfcPropertyValuesFromSgfPropertyValue(
      PropValue* sgfPropertyValue,
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> elementValueTypeDescriptor);

    static std::shared_ptr<ISgfcPropertyValue> GetSgfcPropertyValueFromSgfPropertyValue(
      PropValue* sgfPropertyValue,
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> valueTypeDescriptor);

    static std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer,
      SgfcPropertyValueType propertyValueType);

    static std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcNumberPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer);
    static std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcRealPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer);
    static std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcDoublePropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer);
    static std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcColorPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer);

    static bool DoesSgfcPropertyHaveTypedValues(const std::shared_ptr<ISgfcPropertyValue>& propertyValue);
  };
}
