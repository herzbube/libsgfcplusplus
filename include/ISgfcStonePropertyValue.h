#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcGoStonePropertyValue;

  /// @brief The ISgfcStonePropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Stone.
  ///
  /// ISgfcStonePropertyValue is immutable, i.e. once the
  /// ISgfcStonePropertyValue object is constructed it cannot be changed.
  class ISgfcStonePropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcStonePropertyValue object.
    ISgfcStonePropertyValue();

    /// @brief Destroys and cleans up the ISgfcStonePropertyValue object.
    virtual ~ISgfcStonePropertyValue();

    /// @brief Returns the uninterpreted stone value. This is the same value
    /// that GetRawValue() returns.
    ///
    /// The SGF standard does not provide a universal definition of how a stone
    /// value should look like. Instead it says that the interpretation of
    /// stone values is game specific.
    virtual std::string GetRawStoneValue() const = 0;

    /// @brief Returns an ISgfcGoStonePropertyValue object if the game tree that
    /// this property value is associated with has SgfcGameType::Go. Returns
    /// @e nullptr otherwise. The caller is not the owner of the returned
    /// object.
    ///
    /// @todo There should be a method that allows the user to check whether
    /// this method returns nullptr. Example: GetGameType().
    virtual const ISgfcGoStonePropertyValue* ToGoStoneValue() const = 0;
  };
}
