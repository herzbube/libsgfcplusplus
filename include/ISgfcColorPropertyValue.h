#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"
#include "SgfcColor.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcColorPropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Color.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  ///
  /// ISgfcColorPropertyValue is immutable, i.e. once the
  /// ISgfcColorPropertyValue object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcColorPropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcColorPropertyValue object.
    ISgfcColorPropertyValue();

    /// @brief Destroys and cleans up the ISgfcColorPropertyValue object.
    virtual ~ISgfcColorPropertyValue();

    /// @brief Returns the property value interpreted as an SgfcColor value.
    ///
    /// @exception std::logic_error Is thrown if HasTypedValue() returns false.
    virtual SgfcColor GetColorValue() const = 0;
  };
}
