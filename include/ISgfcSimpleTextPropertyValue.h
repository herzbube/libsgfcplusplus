#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcSimpleTextPropertyValue interface provides access to one
  /// of the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::SimpleText.
  ///
  /// ISgfcSimpleTextPropertyValue is immutable, i.e. once the
  /// ISgfcSimpleTextPropertyValue object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcSimpleTextPropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcSimpleTextPropertyValue
    /// object.
    ISgfcSimpleTextPropertyValue();

    /// @brief Destroys and cleans up the ISgfcSimpleTextPropertyValue object.
    virtual ~ISgfcSimpleTextPropertyValue();

    /// @brief Returns the property value interpreted as a simple text string.
    ///
    /// @todo Do we need a dedicated type SgfcSimpleText?
    ///
    /// @exception std::logic_error Is thrown if HasTypedValue() returns false.
    virtual std::string GetSimpleTextValue() const = 0;
  };
}
