#pragma once

namespace LibSgfcPlusPlus
{
  /// @brief SgfcPropertyValueType enumerates all SGF property value types.
  enum class SgfcPropertyValueType
  {
    /// @brief The property has no value.
    ///
    /// @todo Do we really need this?
    None,
    /// @brief A positive or negative integer value.
    Number,
    /// @brief A positive or negative decimal value.
    Real,
    /// @brief A Double value can have one of two values: Either "1" (which
    /// means "normal") or "2" (which means "emphasized").
    ///
    /// Example: GB[1] means "good for black" (normal). GB[2] means "very good
    /// for black" (emphasized).
    Double,
    /// @brief A Color value can have one of two values: Either "B" (which
    /// means "black") or "W" (which means "white").
    Color,
    SimpleText,
    Text,
    Point,
    Move,
    Stone,

    /// @brief The property value has a custom type. This is used for all
    /// values of a property that is not defined in the SGF standard.
    Custom,
    /// @brief The type of the property value is unknown.
    Unknown,
  };
}
