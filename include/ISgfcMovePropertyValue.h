#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcMovePropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Move.
  ///
  /// ISgfcMovePropertyValue is immutable, i.e. once the
  /// ISgfcMovePropertyValue object is constructed it cannot be changed.
  class ISgfcMovePropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcMovePropertyValue object.
    ISgfcMovePropertyValue();

    /// @brief Destroys and cleans up the ISgfcMovePropertyValue object.
    virtual ~ISgfcMovePropertyValue();

    /// @brief Returns the uninterpreted move value. This is the same value
    /// that GetRawValue() returns.
    ///
    /// The SGF standard does not provide a universal definition of how a move
    /// value should look like. Instead it says that the interpretation of
    /// move values is game specific.
    ///
    /// @todo Define at least a representation for Go moves (ISgfcMove).
    virtual std::string GetRawMoveValue() const = 0;
  };
}
