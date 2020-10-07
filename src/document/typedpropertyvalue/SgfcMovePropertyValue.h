#pragma once

// Project includes
#include "../../../include/ISgfcMovePropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcMovePropertyValue class provides an implementation of
  /// the ISgfcMovePropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcMovePropertyValue : public SgfcSinglePropertyValue, virtual public ISgfcMovePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcMovePropertyValue
    /// object. The object holds a Move value which was not interpreted in
    /// any way and equals the raw string value @a rawValue.
    SgfcMovePropertyValue(const std::string& rawValue);

    /// @brief Destroys and cleans up the SgfcMovePropertyValue object.
    virtual ~SgfcMovePropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual std::string GetRawMoveValue() const;
    virtual const ISgfcMovePropertyValue* ToMoveValue() const;
    virtual const ISgfcGoMovePropertyValue* ToGoMoveValue() const;
  };
}
