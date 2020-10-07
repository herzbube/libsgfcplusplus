#pragma once

namespace LibSgfcPlusPlus
{
  /// @brief SgfcPropertyValueTypeDescriptorType enumerates all types of
  /// ISgfcPropertyValueTypeDescriptor objects.
  ///
  /// @ingroup internals
  enum class SgfcPropertyValueTypeDescriptorType
  {
    DualValueType,
    ElistValueType,
    ListValueType,
    ComposedValueType,
    BasicValueType,
  };
}
