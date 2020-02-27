#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcPointPropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Point.
  ///
  /// ISgfcPointPropertyValue is immutable, i.e. once the
  /// ISgfcPointPropertyValue object is constructed it cannot be changed.
  class ISgfcPointPropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcPointPropertyValue object.
    ISgfcPointPropertyValue();

    /// @brief Destroys and cleans up the ISgfcPointPropertyValue object.
    virtual ~ISgfcPointPropertyValue();

    /// @brief Returns the uninterpreted point value. This is the same value
    /// that GetRawValue() returns.
    ///
    /// The SGF standard does not provide a universal definition of how a point
    /// value should look like. Instead it says that the interpretation of
    /// point values is game specific.
    ///
    /// @todo Define at least a representation for Go points (ISgfcPoint).
    virtual std::string GetRawPointValue() const = 0;
  };
}
