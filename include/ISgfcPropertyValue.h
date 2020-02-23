#pragma once

// Project includes
#include "ISgfcComposedPropertyValue.h"
#include "ISgfcSinglePropertyValue.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcPropertyValue interface provides access to one of the
  /// values of a property of an SGF node.
  ///
  /// ISgfcPropertyValue is immutable, i.e. once the ISgfcPropertyValue object
  /// is constructed it cannot be changed.
  class ISgfcPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcPropertyValue object.
    ISgfcPropertyValue();

    /// @brief Destroys and cleans up the ISgfcPropertyValue object.
    virtual ~ISgfcPropertyValue();

    /// @brief Returns true if the ISgfcPropertyValue object holds a "composed"
    /// value, i.e. a value that consists of a composite of two single values.
    /// Returns false if the ISgfcPropertyValue holds only a single value.
    virtual bool IsComposedValue() const = 0;

    /// @brief Returns @e nullptr if IsComposedValue() returns true. Returns an
    /// ISgfcSinglePropertyValue object if IsComposedValue() returns false.
    virtual std::shared_ptr<ISgfcSinglePropertyValue> ToSingleValue() const = 0;

    /// @brief Returns an ISgfcComposedPropertyValue object if IsComposedValue()
    /// returns true. Returns @e nullptr if IsComposedValue() returns false.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> ToComposedValue() const = 0;
  };
}
