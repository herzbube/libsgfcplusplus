#pragma once

// Project includes
#include "SgfcPropertyValueType.h"

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcPropertyValue interface provides access to one of the
  /// values of a property of an SGF node. If the value is a composite value,
  /// it actually consists of two values.
  ///
  /// ISgfcPropertyValue is immutable, i.e. the ISgfcPropertyValue object is
  /// constructed it cannot be changed.
  class ISgfcPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcPropertyValue object.
     ISgfcPropertyValue();

     /// @brief Destroys and cleans up the ISgfcPropertyValue object.
     virtual ~ISgfcPropertyValue();

    /// @brief Returns true if the ISgfcPropertyValue object is a composite
    /// value, i.e. if it is composed of two values. Returns false if the
    /// ISgfcPropertyValue object contains only a single value.
    virtual bool IsCompositeValue() const = 0;

    /// @brief Returns the type of the first property value.
    ///
    /// @todo Currently this always returns ISgfcPropertyValueType::Unknown.
    virtual SgfcPropertyValueType GetValueType1() const = 0;

    /// @brief Returns the first property value as a raw string.
    ///
    /// @todo Return the value without escaped characters.
    ///
    /// @todo How do we deal with formatting / linebreaks? Soft/hard linebreaks.
    ///
    /// @todo How do we deal with encodings?
    virtual std::string GetRawValue1() const = 0;

    /// @brief Returns the type of the second property value if
    /// IsCompositeValue() is true. Returns SgfcPropertyValueType::None if
    /// IsCompositeValue() is false.
    ///
    /// @todo Currently this always returns SgfcPropertyValueType::Unknown if
    /// IsCompositeValue() is true.
    virtual SgfcPropertyValueType GetValueType2() const = 0;

    /// @brief Returns the second property value as a raw string if
    /// IsCompositeValue() is true. Returns an empty string if
    /// IsCompositeValue() is false.
    ///
    /// @todo Return the value without escaped characters.
    ///
    /// @todo How do we deal with formatting / linebreaks? Soft/hard linebreaks.
    ///
    /// @todo How do we deal with encodings?
    virtual std::string GetRawValue2() const = 0;
  };
}
