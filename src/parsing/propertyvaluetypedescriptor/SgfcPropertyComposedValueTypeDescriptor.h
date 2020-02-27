#pragma once

// Project includes
#include "../../interface/internal/ISgfcPropertyValueTypeDescriptor.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyComposedValueTypeDescriptor interface provides an
  /// implementation of the ISgfcPropertyValueTypeDescriptor interface.
  /// See the interface header file for documentation.
  ///
  /// SgfcPropertyComposedValueTypeDescriptor expresses the fact that for some
  /// properties the raw SGF property value is composed of two values, separated
  /// by a colon (":") character. GetDescriptorValueType1() returns a descriptor
  /// for the value type of the first value, GetDescriptorValueType2() returns a
  /// descriptor for the value type of the second value.
  ///
  /// @example The "AP" property value is composed of two SimpleText values
  /// separated by a ":" character. Both GetDescriptorValueType1() and
  /// GetDescriptorValueType2() in this case return
  /// SgfcPropertyBasicValueTypeDescriptor objects which both have the basic
  /// value type SgfcPropertyValueType::SimpleText.
  ///
  /// @note The example is simple, so it should be noted that in other cases the
  /// two value type descriptors do not necessarily describe the same value
  /// type, nor are they restricted to the SgfcPropertyBasicValueTypeDescriptor
  /// type.
  class SgfcPropertyComposedValueTypeDescriptor : public ISgfcPropertyValueTypeDescriptor
  {
  public:
    /// @brief Initializes a newly constructed
    /// SgfcPropertyComposedValueTypeDescriptor object.
    SgfcPropertyComposedValueTypeDescriptor(
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1,
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2);

    /// @brief Destroys and cleans up the
    /// SgfcPropertyComposedValueTypeDescriptor object.
    virtual ~SgfcPropertyComposedValueTypeDescriptor();

    virtual SgfcPropertyValueTypeDescriptorType GetDescriptorType() const;

    virtual const SgfcPropertyDualValueTypeDescriptor* ToDualValueTypeDescriptor() const;
    virtual const SgfcPropertyElistValueTypeDescriptor* ToElistValueTypeDescriptor() const;
    virtual const SgfcPropertyListValueTypeDescriptor* ToListValueTypeDescriptor() const;
    virtual const SgfcPropertyComposedValueTypeDescriptor* ToComposedValueTypeDescriptor() const;
    virtual const SgfcPropertyBasicValueTypeDescriptor* ToBasicValueTypeDescriptor() const;

    /// @brief Returns an ISgfcPropertyValueTypeDescriptor object that describes
    /// the value type of the first value.
    virtual std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetDescriptorValueType1() const;

    /// @brief Returns an ISgfcPropertyValueTypeDescriptor object that describes
    /// the value type of the second value.
    virtual std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetDescriptorValueType2() const;

  private:
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1;
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2;
  };
}
