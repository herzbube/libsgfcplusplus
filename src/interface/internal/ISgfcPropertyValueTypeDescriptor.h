#pragma once

// Project includes
#include "SgfcPropertyValueTypeDescriptorType.h"

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class SgfcPropertyDualValueTypeDescriptor;
  class SgfcPropertyElistValueTypeDescriptor;
  class SgfcPropertyListValueTypeDescriptor;
  class SgfcPropertyComposedValueTypeDescriptor;
  class SgfcPropertyBasicValueTypeDescriptor;

  /// @brief The ISgfcPropertyValueTypeDescriptor interface provides a
  /// description of the potential types of values that a specific SGF property
  /// can have in the raw SGF content. This information helps with parsing the
  /// raw SGF property value string.
  ///
  /// @ingroup internals
  /// @ingroup parsing
  ///
  /// ISgfcPropertyValueTypeDescriptor contains a number of convenience methods
  /// that help casting an ISgfcPropertyValueTypeDescriptor object to a concrete
  /// type (e.g. ToDualValueTypeDescriptor()). The return value of
  /// GetDescriptorType() provides the information which casting method to use.
  ///
  /// With the exception of SgfcPropertyBasicValueTypeDescriptor, all
  /// implementations of ISgfcPropertyValueTypeDescriptor are composed of one
  /// or more other ISgfcPropertyValueTypeDescriptor objects. The goal is that
  /// the descriptor for a specific property can ultimately be broken down into
  /// one or more SgfcPropertyBasicValueTypeDescriptor.
  ///
  /// In theory the concept allows arbitrary nesting of descriptors. In practice
  /// the nesting is restricted by the current implementation of the decoder
  /// that parses property values. The restrictions are these:
  /// - SgfcPropertyDualValueTypeDescriptor,
  ///   SgfcPropertyElistValueTypeDescriptor and
  ///   SgfcPropertyListValueTypeDescriptor can only be composed of
  ///   SgfcPropertyBasicValueTypeDescriptor and/or
  ///   SgfcPropertyComposedValueTypeDescriptor.
  /// - SgfcPropertyComposedValueTypeDescriptor can only be composed of
  ///   SgfcPropertyBasicValueTypeDescriptor.
  ///
  /// The decoder implementation (and therefore the restrictions it imposes)
  /// are geared towards what is possible according to the definitions in the
  /// SGF standard. If a future version of the SGF standard allows more complex
  /// descriptor combinations, the decoder implementation will have to be
  /// expanded.
  ///
  /// @example The "AR" property contains a list of composed Point/Point values.
  /// The top-level descriptor for the property therefore is an
  /// SgfcPropertyListValueTypeDescriptor object, which is composed of another
  /// descriptor of type SgfcPropertyComposedValueTypeDescriptor, which in turn
  /// is composed of two descriptors of type
  /// SgfcPropertyBasicValueTypeDescriptor, both of which have the basic
  /// value type SgfcPropertyValueType::Number.
  ///
  /// ISgfcPropertyValueTypeDescriptor is immutable, i.e. once the
  /// ISgfcPropertyValueTypeDescriptor object is constructed it cannot be
  /// changed.
  class ISgfcPropertyValueTypeDescriptor
  {
  public:
    /// @brief Initializes a newly constructed ISgfcPropertyValueTypeDescriptor
    /// object.
    ISgfcPropertyValueTypeDescriptor();

    /// @brief Destroys and cleans up the ISgfcPropertyValueTypeDescriptor
    /// object.
    virtual ~ISgfcPropertyValueTypeDescriptor();

    /// @brief Returns the concrete type of the descriptor object. Depending on
    /// the value returned, a caller then knows which one of the convenience
    /// casting methods to use.
    virtual SgfcPropertyValueTypeDescriptorType GetDescriptorType() const = 0;

    /// @brief Returns an SgfcPropertyDualValueTypeDescriptor object if
    /// GetDescriptorType() returns
    /// SgfcPropertyValueTypeDescriptorType::DualValueType. Returns
    /// @e nullptr otherwise. The caller is not the owner of the returned
    /// object.
    virtual const SgfcPropertyDualValueTypeDescriptor* ToDualValueTypeDescriptor() const;

    /// @brief Returns an SgfcPropertyListValueTypeDescriptor object if
    /// GetDescriptorType() returns
    /// SgfcPropertyValueTypeDescriptorType::ElistValueType. Returns
    /// @e nullptr otherwise. The caller is not the owner of the returned
    /// object.
    virtual const SgfcPropertyElistValueTypeDescriptor* ToElistValueTypeDescriptor() const;

    /// @brief Returns an SgfcPropertyElistValueTypeDescriptor object if
    /// GetDescriptorType() returns
    /// SgfcPropertyValueTypeDescriptorType::ListValueType. Returns
    /// @e nullptr otherwise. The caller is not the owner of the returned
    /// object.
    virtual const SgfcPropertyListValueTypeDescriptor* ToListValueTypeDescriptor() const;

    /// @brief Returns an SgfcPropertyComposedValueTypeDescriptor object if
    /// GetDescriptorType() returns
    /// SgfcPropertyValueTypeDescriptorType::ComposedValueType. Returns
    /// @e nullptr otherwise. The caller is not the owner of the returned
    /// object.
    virtual const SgfcPropertyComposedValueTypeDescriptor* ToComposedValueTypeDescriptor() const;

    /// @brief Returns an SgfcPropertyBasicValueTypeDescriptor object if
    /// GetDescriptorType() returns
    /// SgfcPropertyValueTypeDescriptorType::BasicValueType. Returns
    /// @e nullptr otherwise. The caller is not the owner of the returned
    /// object.
    virtual const SgfcPropertyBasicValueTypeDescriptor* ToBasicValueTypeDescriptor() const;
  };
}
