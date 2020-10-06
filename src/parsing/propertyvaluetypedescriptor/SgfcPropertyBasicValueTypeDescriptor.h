#pragma once

// Project includes
#include "../../../include/SgfcPropertyValueType.h"
#include "../../interface/internal/ISgfcPropertyValueTypeDescriptor.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyBasicValueTypeDescriptor interface provides an
  /// implementation of the ISgfcPropertyValueTypeDescriptor interface.
  /// See the interface header file for documentation.
  ///
  /// @ingroup internals
  /// @ingroup parsing
  ///
  /// SgfcPropertyBasicValueTypeDescriptor defines the basic value type that a
  /// single non-composed SGF property value can have. GetValueType() returns
  /// that value type.
  ///
  /// All ISgfcPropertyValueTypeDescriptor implementations except
  /// SgfcPropertyBasicValueTypeDescriptor define complex value types (lists,
  /// composed values) or alternate value types. Ultimately every one of these
  /// other descriptors can be broken down into one or more
  /// SgfcPropertyBasicValueTypeDescriptor objects.
  ///
  /// Example: The "CA" property value is a SimpleText. GetValueType() in this
  /// case returns SgfcPropertyValueType::SimpleText.
  class SgfcPropertyBasicValueTypeDescriptor : public ISgfcPropertyValueTypeDescriptor
  {
  public:
    /// @brief Initializes a newly constructed
    /// SgfcPropertyBasicValueTypeDescriptor object.
    SgfcPropertyBasicValueTypeDescriptor(
      SgfcPropertyValueType valueType);

    /// @brief Destroys and cleans up the SgfcPropertyBasicValueTypeDescriptor
    /// object.
    virtual ~SgfcPropertyBasicValueTypeDescriptor();

    virtual SgfcPropertyValueTypeDescriptorType GetDescriptorType() const;
    virtual const SgfcPropertyBasicValueTypeDescriptor* ToBasicValueTypeDescriptor() const;

    /// @brief Returns the value type defined by the
    /// SgfcPropertyBasicValueTypeDescriptor.
    virtual SgfcPropertyValueType GetValueType() const;

  private:
    SgfcPropertyValueType valueType;
  };
}
