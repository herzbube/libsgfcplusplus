#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"
#include "SgfcTypedefs.h"

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcNumberPropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Number.
  ///
  /// ISgfcNumberPropertyValue is immutable, i.e. once the
  /// ISgfcNumberPropertyValue object is constructed it cannot be changed.
  class ISgfcNumberPropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcNumberPropertyValue object.
    ISgfcNumberPropertyValue();

    /// @brief Destroys and cleans up the ISgfcNumberPropertyValue object.
    virtual ~ISgfcNumberPropertyValue();

    /// @brief Returns the property value interpreted as a signed integer
    /// number.
    ///
    /// @exception std::logic_error Is thrown if HasTypedValue() returns false.
    virtual SgfcNumber GetNumberValue() const = 0;
  };
}
