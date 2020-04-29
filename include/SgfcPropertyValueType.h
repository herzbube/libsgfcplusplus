#pragma once

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief SgfcPropertyValueType enumerates the basic SGF property value
  /// types.
  enum class SGFCPLUSPLUS_EXPORT SgfcPropertyValueType
  {
    /// @brief The property has no value.
    None,
    /// @brief The property value is a positive or negative integer.
    Number,
    /// @brief The property value is a positive or negative decimal value.
    Real,
    /// @brief The property value is a Double value. A Double value can have
    /// one of two integer values: Either 1 (which means "normal") or 2 (which
    /// means "emphasized").
    ///
    /// Example: GB[1] means "good for black" (normal). GB[2] means "very good
    /// for black" (emphasized).
    Double,
    /// @brief The property value is a Color value. A Color value can have one
    /// of two string values: Either "B" (which means "black") or "W" (which
    /// means "white").
    Color,
    SimpleText,
    Text,
    Point,
    Move,
    Stone,
    /// @brief The property value has an unknown type. This is used for
    /// non-empty values of any property not defined in the SGF standard.
    Unknown,
  };
}
