#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcTextPropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Text.
  ///
  /// ISgfcTextPropertyValue is immutable, i.e. once the
  /// ISgfcTextPropertyValue object is constructed it cannot be changed.
  class ISgfcTextPropertyValue : public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcTextPropertyValue object.
    ISgfcTextPropertyValue();

    /// @brief Destroys and cleans up the ISgfcTextPropertyValue object.
    virtual ~ISgfcTextPropertyValue();

    /// @brief Returns the property value interpreted as a text string.
    ///
    /// @todo Do we need a dedicated type SgfcText?
    ///
    /// @exception std::logic_error Is thrown if HasTypedValue() returns false.
    virtual std::string GetTextValue() const = 0;
  };
}
