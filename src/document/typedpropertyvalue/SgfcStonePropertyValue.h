#pragma once

// Project includes
#include "../../../include/ISgfcStonePropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcStonePropertyValue class provides an implementation of
  /// the ISgfcStonePropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcStonePropertyValue : public SgfcSinglePropertyValue, virtual public ISgfcStonePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcStonePropertyValue
    /// object. The object holds a Stone value which was not interpreted in
    /// any way and equals the raw string value @a rawValue.
    SgfcStonePropertyValue(const std::string& rawValue);

    /// @brief Destroys and cleans up the SgfcStonePropertyValue object.
    virtual ~SgfcStonePropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual std::string GetRawStoneValue() const;
    virtual const ISgfcStonePropertyValue* ToStoneValue() const;
    virtual const ISgfcGoStonePropertyValue* ToGoStoneValue() const;
  };
}
