#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcComposedPropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value is a composite of two
  /// ISgfcSinglePropertyValue objects.
  ///
  /// The class name uses the term "composed" because that is how it appears in
  /// the SGF standard.
  ///
  /// ISgfcComposedPropertyValue is immutable, i.e. once the
  /// ISgfcComposedPropertyValue object is constructed it cannot be changed.
  class ISgfcComposedPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcComposedPropertyValue
    /// object.
    ISgfcComposedPropertyValue();

     /// @brief Destroys and cleans up the ISgfcComposedPropertyValue object.
     virtual ~ISgfcComposedPropertyValue();

    /// @brief Returns the first property value.
    virtual std::shared_ptr<ISgfcSinglePropertyValue> GetValue1() const = 0;

    /// @brief Returns the first property value.
    virtual std::shared_ptr<ISgfcSinglePropertyValue> GetValue2() const = 0;
  };
}
