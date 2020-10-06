#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcTextPropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Text.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  ///
  /// ISgfcTextPropertyValue is immutable, i.e. once the
  /// ISgfcTextPropertyValue object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcTextPropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcTextPropertyValue object.
    ISgfcTextPropertyValue();

    /// @brief Destroys and cleans up the ISgfcTextPropertyValue object.
    virtual ~ISgfcTextPropertyValue();

    /// @brief Returns the property value interpreted as a text string.
    ///
    /// @exception std::logic_error Is thrown if HasTypedValue() returns false.
    virtual std::string GetTextValue() const = 0;
  };
}
