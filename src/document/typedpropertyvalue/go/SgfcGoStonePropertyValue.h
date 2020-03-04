#pragma once

// Project includes
#include "../../../../include/ISgfcGoStonePropertyValue.h"
#include "../SgfcStonePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoStonePropertyValue class provides an implementation of
  /// the ISgfcGoStonePropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcGoStonePropertyValue : public SgfcStonePropertyValue, public ISgfcGoStonePropertyValue
  {
  public:
    SgfcGoStonePropertyValue(const std::string& rawValue, SgfcColor color);
    virtual ~SgfcGoStonePropertyValue();

    virtual const ISgfcGoStonePropertyValue* ToGoStoneValue() const;
    virtual std::shared_ptr<ISgfcGoStone> GetGoStone() const;

  private:
    std::shared_ptr<ISgfcGoStone> goStone;
  };
}
