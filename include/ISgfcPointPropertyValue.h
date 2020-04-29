#pragma once

// Project includes
#include "ISgfcSinglePropertyValue.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcGoPointPropertyValue;

  /// @brief The ISgfcPointPropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Point.
  ///
  /// ISgfcPointPropertyValue is immutable, i.e. once the
  /// ISgfcPointPropertyValue object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcPointPropertyValue : virtual public ISgfcSinglePropertyValue
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
    virtual std::string GetRawPointValue() const = 0;

    /// @brief Returns an ISgfcGoPointPropertyValue object if the game tree that
    /// this property value is associated with has SgfcGameType::Go. Returns
    /// @e nullptr otherwise. The caller is not the owner of the returned
    /// object.
    ///
    /// @todo There should be a method that allows the user to check whether
    /// this method returns nullptr. Example: GetGameType().
    virtual const ISgfcGoPointPropertyValue* ToGoPointValue() const = 0;
  };
}
