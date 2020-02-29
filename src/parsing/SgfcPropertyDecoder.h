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
    /// @brief Initializes a newly constructed SgfcPropertyDecoder object. The
    /// object parses the specified SGF property @a sgfProperty and its values.
    SgfcPropertyDecoder(const Property* sgfProperty);
    
    /// @brief Destroys and cleans up the SgfcPropertyDecoder object.
    virtual ~SgfcPropertyDecoder();

    /// @brief Returns the SgfcPropertyType value that corresponds to the
    /// SGF property with which SgfcPropertyDecoder was constructed.
    SgfcPropertyType GetPropertyType() const;

    /// @brief Returns the raw string name of the SGF property with which
    /// SgfcPropertyDecoder was constructed.
    std::string GetPropertyName() const;

    /// @brief Parses the SGF property with which SgfcPropertyDecoder was
    /// constructed and returns a list with the property's values.
    ///
    /// This method relies on certain pre-processing performed by SGFC. Notably:
    /// - Non-string values are trimmed (essential for Double and Color values)
    std::vector<std::shared_ptr<ISgfcPropertyValue>> GetPropertyValues() const;

  private:
    const Property* sgfProperty;
    SgfcPropertyType propertyType;

    SgfcPropertyType GetSgfcPropertyTypeForSgfProperty(const Property* sgfProperty) const;

    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetValueTypeDescriptorForPropertyType(
      SgfcPropertyType propertyType) const;

    std::vector<std::shared_ptr<ISgfcPropertyValue>> GetSgfcPropertyValuesFromSgfPropertyValue(
      PropValue* sgfPropertyValue,
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> elementValueTypeDescriptor) const;

    std::shared_ptr<ISgfcPropertyValue> GetSgfcPropertyValueFromSgfPropertyValue(
      PropValue* sgfPropertyValue,
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> valueTypeDescriptor) const;

    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer,
      SgfcPropertyValueType propertyValueType) const;

    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcNumberPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;
    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcRealPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;
    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcDoublePropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;
    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcColorPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;

    bool DoesSgfcPropertyHaveTypedValues(const std::shared_ptr<ISgfcPropertyValue>& propertyValue) const;
  };
}
