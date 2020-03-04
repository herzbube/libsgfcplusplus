#pragma once

// Project includes
#include "../../../include/ISgfcStonePropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcStonePropertyValue class provides an implementation of
  /// the ISgfcStonePropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcStonePropertyValue : public SgfcSinglePropertyValue, virtual public ISgfcStonePropertyValue
  {
  public:
    SgfcStonePropertyValue(const std::string& rawValue);
    virtual ~SgfcStonePropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual std::string GetRawStoneValue() const;
    virtual const ISgfcStonePropertyValue* ToStoneValue() const;
    virtual const ISgfcGoStonePropertyValue* ToGoStoneValue() const;
  };
}
