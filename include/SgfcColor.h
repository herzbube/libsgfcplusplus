#pragma once

namespace LibSgfcPlusPlus
{
  /// @brief SgfcColor enumerates the values that a property value of type
  /// SgfcPropertyValueType::Color can have.
  enum class SgfcColor
  {
    /// @brief The property value signifies the abstract color "Black".
    ///
    /// The raw property string value is "B".
    Black,
    /// @brief The property value signifies the abstract color "White".
    ///
    /// The raw property string value is "W".
    White,
  };
}
