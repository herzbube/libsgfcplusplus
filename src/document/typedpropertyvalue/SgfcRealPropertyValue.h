#pragma once

// Project includes
#include "../../../include/ISgfcRealPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcRealPropertyValue class provides an implementation of
  /// the ISgfcRealPropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcRealPropertyValue : public SgfcSinglePropertyValue, ISgfcRealPropertyValue
  {
  public:
    SgfcRealPropertyValue(const std::string& rawValue, double realValue);
    SgfcRealPropertyValue(const std::string& rawValue);
    virtual ~SgfcRealPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual double GetRealValue() const = 0;
    virtual const ISgfcRealPropertyValue* ToRealValue() const;

  private:
    double realValue;
  };
}
