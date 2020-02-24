#pragma once

// Project includes
#include "ISgfcPropertyValue.h"
#include "SgfcPropertyValueType.h"

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcSinglePropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value is a single value.
  /// Some properties allow composed values - see ISgfcComposedPropertyValue
  /// for details.
  ///
  /// ISgfcSinglePropertyValue is immutable, i.e. once the
  /// ISgfcSinglePropertyValue object is constructed it cannot be changed.
  class ISgfcSinglePropertyValue : public ISgfcPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcSinglePropertyValue object.
    ISgfcSinglePropertyValue();

    /// @brief Destroys and cleans up the ISgfcSinglePropertyValue object.
    virtual ~ISgfcSinglePropertyValue();

    /// @brief Returns the type of the property value.
    ///
    /// @todo Currently this always returns ISgfcPropertyValueType::Unknown.
    virtual SgfcPropertyValueType GetValueType() const = 0;

    /// @brief Returns the property value as a raw string.
    ///
    /// @todo Return the value without escaped characters.
    ///
    /// @todo How do we deal with formatting / linebreaks? Soft/hard linebreaks.
    ///
    /// @todo How do we deal with encodings?
    virtual std::string GetRawValue() const = 0;
  };
}
