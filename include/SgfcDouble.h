#pragma once

namespace LibSgfcPlusPlus
{
  /// @brief SgfcDouble enumerates the values that a property value of type
  /// SgfcPropertyValueType::Double can have.
  enum class SgfcDouble
  {
    /// @brief The property value signifies "normal" importance. Example: If the
    /// property SgfcPropertyType::GB has this value, then it means
    /// "good for black".
    ///
    /// The raw property string value is "1".
    Normal,
    /// @brief The property value signifies "emphasized" importance. Example: If
    /// the property SgfcPropertyType::GB has this value, then it means
    /// "very good for black".
    ///
    /// The raw property string value is "2".
    Emphasized,
  };
}
