#pragma once

// Project includes
#include "../../interface/internal/ISgfcPropertyValueTypeDescriptor.h"
#include "SgfcPropertyListValueTypeDescriptor.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyElistValueTypeDescriptor interface provides an
  /// implementation of the ISgfcPropertyValueTypeDescriptor interface.
  /// See the interface header file for documentation.
  ///
  /// SgfcPropertyElistValueTypeDescriptor expresses the fact that for some
  /// properties the raw SGF property value can be either
  /// SgfcPropertyValueType::None or some other type. Which one needs to be
  /// determined by probing, i.e. by parsing the raw property value.
  /// GetDescriptorListValueType() always returns an
  /// SgfcPropertyListValueTypeDescriptor, which in turn is composed of another
  /// descriptor that defines the value type of the list elements.
  ///
  /// SgfcPropertyElistValueTypeDescriptor could also be expressed with an
  /// SgfcPropertyDualValueTypeDescriptor. SgfcPropertyElistValueTypeDescriptor
  /// exists as a dedicated type only because the SGF standard explicitly names
  /// and describes "elist" in its EBNF definition section.
  ///
  /// @example The "DD" property value either is None, or it is a list of
  /// Point. GetDescriptorListValueType() in this case returns an
  /// SgfcPropertyListValueTypeDescriptor object, which in turn is composed
  /// of a descriptor of type SgfcPropertyBasicValueTypeDescriptor which has
  /// the basic value type SgfcPropertyValueType::Point.
  class SgfcPropertyElistValueTypeDescriptor : public ISgfcPropertyValueTypeDescriptor
  {
  public:
    /// @brief Initializes a newly constructed
    /// SgfcPropertyElistValueTypeDescriptor object.
    SgfcPropertyElistValueTypeDescriptor(
      std::shared_ptr<SgfcPropertyListValueTypeDescriptor> descriptorListValueType);

    /// @brief Destroys and cleans up the SgfcPropertyElistValueTypeDescriptor
    /// object.
    virtual ~SgfcPropertyElistValueTypeDescriptor();

    virtual SgfcPropertyValueTypeDescriptorType GetDescriptorType() const;

    virtual const SgfcPropertyDualValueTypeDescriptor* ToDualValueTypeDescriptor() const;
    virtual const SgfcPropertyElistValueTypeDescriptor* ToElistValueTypeDescriptor() const;
    virtual const SgfcPropertyListValueTypeDescriptor* ToListValueTypeDescriptor() const;
    virtual const SgfcPropertyComposedValueTypeDescriptor* ToComposedValueTypeDescriptor() const;
    virtual const SgfcPropertyBasicValueTypeDescriptor* ToBasicValueTypeDescriptor() const;

    /// @brief Returns an SgfcPropertyListValueTypeDescriptor object that
    /// is composed of another descriptor that defines the value type of the
    /// list elements.
    virtual std::shared_ptr<SgfcPropertyListValueTypeDescriptor> GetDescriptorListValueType() const;

  private:
    std::shared_ptr<SgfcPropertyListValueTypeDescriptor> descriptorListValueType;
  };
}
