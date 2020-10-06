#pragma once

namespace LibSgfcPlusPlus
{
  /// @brief SgfcPropertyValueTypeDescriptorType enumerates all types of
  /// ISgfcPropertyValueTypeDescriptor objects.
  ///
  /// @ingroup internals
  /// @ingroup parsing
  enum class SgfcPropertyValueTypeDescriptorType
  {
    DualValueType,
    ElistValueType,
    ListValueType,
    ComposedValueType,
    BasicValueType,
  };
}
