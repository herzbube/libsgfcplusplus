#pragma once

// Project includes
#include "../../interface/internal/ISgfcPropertyValueTypeDescriptor.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyListValueTypeDescriptor interface provides an
  /// implementation of the ISgfcPropertyValueTypeDescriptor interface.
  /// See the interface header file for documentation.
  ///
  /// SgfcPropertyListValueTypeDescriptor expresses the fact that some
  /// SGF properties can have more than one value.
  /// GetDescriptorElementValueType() returns a descriptor for the list element
  /// value type.
  ///
  /// @note A list type property has at least one value. Properties which allow
  /// zero values are "elists".
  ///
  /// @example The "LB" property value is a list of composed Point/SimpleText
  /// elements. GetDescriptorElementValueType() in this case returns an
  /// SgfcPropertyComposedValueTypeDescriptor object, which in turn is composed
  /// of two descriptors of type SgfcPropertyBasicValueTypeDescriptor, the first
  /// having the basic value type SgfcPropertyValueType::Point and the second.
  /// having the basic value type SgfcPropertyValueType::SimpleText.
  class SgfcPropertyListValueTypeDescriptor : public ISgfcPropertyValueTypeDescriptor
  {
  public:
    /// @brief Initializes a newly constructed
    /// SgfcPropertyListValueTypeDescriptor object.
    SgfcPropertyListValueTypeDescriptor(
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorElementValueType);

    /// @brief Destroys and cleans up the SgfcPropertyListValueTypeDescriptor
    /// object.
    virtual ~SgfcPropertyListValueTypeDescriptor();

    virtual SgfcPropertyValueTypeDescriptorType GetDescriptorType() const;

    virtual const SgfcPropertyDualValueTypeDescriptor* ToDualValueTypeDescriptor() const;
    virtual const SgfcPropertyElistValueTypeDescriptor* ToElistValueTypeDescriptor() const;
    virtual const SgfcPropertyListValueTypeDescriptor* ToListValueTypeDescriptor() const;
    virtual const SgfcPropertyComposedValueTypeDescriptor* ToComposedValueTypeDescriptor() const;
    virtual const SgfcPropertyBasicValueTypeDescriptor* ToBasicValueTypeDescriptor() const;

    /// @brief Returns an ISgfcPropertyValueTypeDescriptor object that describes
    /// the value type of the list elements.
    virtual std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetDescriptorElementValueType() const;

  private:
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorElementValueType;
  };
}
