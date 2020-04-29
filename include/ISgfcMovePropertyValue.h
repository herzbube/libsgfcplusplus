#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcGoMovePropertyValue;

  /// @brief The ISgfcMovePropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Move.
  ///
  /// ISgfcMovePropertyValue is immutable, i.e. once the
  /// ISgfcMovePropertyValue object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcMovePropertyValue : virtual public ISgfcSinglePropertyValue
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
    virtual std::string GetRawMoveValue() const = 0;

    /// @brief Returns an ISgfcGoMovePropertyValue object if the game tree that
    /// this property value is associated with has SgfcGameType::Go. Returns
    /// @e nullptr otherwise. The caller is not the owner of the returned
    /// object.
    ///
    /// @todo There should be a method that allows the user to check whether
    /// this method returns nullptr. Example: GetGameType().
    virtual const ISgfcGoMovePropertyValue* ToGoMoveValue() const = 0;
  };
}
