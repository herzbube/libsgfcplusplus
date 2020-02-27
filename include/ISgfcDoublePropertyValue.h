#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"
#include "SgfcDouble.h"

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcDoublePropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Double.
  ///
  /// ISgfcDoublePropertyValue is immutable, i.e. once the
  /// ISgfcDoublePropertyValue object is constructed it cannot be changed.
  class ISgfcDoublePropertyValue : public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcDoublePropertyValue object.
    ISgfcDoublePropertyValue();

    /// @brief Destroys and cleans up the ISgfcDoublePropertyValue object.
    virtual ~ISgfcDoublePropertyValue();

    /// @brief Returns the property value interpreted as an SgfcDouble value.
    ///
    /// @exception std::logic_error Is thrown if HasTypedValue() returns false.
    virtual SgfcDouble GetDoubleValue() const = 0;
  };
}
