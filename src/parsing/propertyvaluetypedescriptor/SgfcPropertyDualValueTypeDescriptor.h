#pragma once

// Project includes
#include "../../interface/internal/ISgfcPropertyValueTypeDescriptor.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyDualValueTypeDescriptor interface provides an
  /// implementation of the ISgfcPropertyValueTypeDescriptor interface.
  /// See the interface header file for documentation.
  ///
  /// SgfcPropertyDualValueTypeDescriptor expresses the fact that for some
  /// properties the raw SGF property value can be either of a first type, or a
  /// second type. Which one needs to be determined by probing, i.e. by parsing
  /// the raw property value. GetDescriptorValueType1() returns a descriptor for
  /// the first possible value type, GetDescriptorValueType2() returns a
  /// descriptor for the second possible value type.
  ///
  /// @note The two descriptors must be either
  /// SgfcPropertyBasicValueTypeDescriptor or
  /// SgfcPropertyComposedValueTypeDescriptor objects.
  ///
  /// @example The "SZ" property value either is a single number, or it is a
  /// composed Number/Number. GetDescriptorValueType1() in this case returns an
  /// SgfcPropertyBasicValueTypeDescriptor object which has the basic value
  /// type SgfcPropertyValueType::Number. GetDescriptorValueType2() returns an
  /// SgfcPropertyComposedValueTypeDescriptor object, which in turn is composed
  /// of two descriptors of type SgfcPropertyBasicValueTypeDescriptor, both of
  /// which have the basic value type SgfcPropertyValueType::Number.
  class SgfcPropertyDualValueTypeDescriptor : public ISgfcPropertyValueTypeDescriptor
  {
  public:
    /// @brief Initializes a newly constructed
    /// SgfcPropertyDualValueTypeDescriptor object.
    ///
    /// @exception std::logic_error Is thrown if one or both of the
    /// two descriptor objects are neither SgfcPropertyBasicValueTypeDescriptor
    /// nor SgfcPropertyComposedValueTypeDescriptor objects.
    SgfcPropertyDualValueTypeDescriptor(
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1,
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2);

    /// @brief Destroys and cleans up the SgfcPropertyDualValueTypeDescriptor
    /// object.
    virtual ~SgfcPropertyDualValueTypeDescriptor();

    virtual SgfcPropertyValueTypeDescriptorType GetDescriptorType() const;

    virtual const SgfcPropertyDualValueTypeDescriptor* ToDualValueTypeDescriptor() const;
    virtual const SgfcPropertyElistValueTypeDescriptor* ToElistValueTypeDescriptor() const;
    virtual const SgfcPropertyListValueTypeDescriptor* ToListValueTypeDescriptor() const;
    virtual const SgfcPropertyComposedValueTypeDescriptor* ToComposedValueTypeDescriptor() const;
    virtual const SgfcPropertyBasicValueTypeDescriptor* ToBasicValueTypeDescriptor() const;

    /// @brief Returns an ISgfcPropertyValueTypeDescriptor object that describes
    /// the first of the two possible value types.
    virtual std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetDescriptorValueType1() const;

    /// @brief Returns an ISgfcPropertyValueTypeDescriptor object that describes
    /// the second of the two possible value types.
    virtual std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetDescriptorValueType2() const;

  private:
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1;
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2;
  };
}
