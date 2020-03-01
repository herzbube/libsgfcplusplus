#pragma once

// Project includes
#include "../../../include/ISgfcRealPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcRealPropertyValue class provides an implementation of
  /// the ISgfcRealPropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcRealPropertyValue : public SgfcSinglePropertyValue, public ISgfcRealPropertyValue
  {
  public:
    SgfcRealPropertyValue(const std::string& rawValue, SgfcReal realValue);
    SgfcRealPropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage);
    virtual ~SgfcRealPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual SgfcReal GetRealValue() const;
    virtual const ISgfcRealPropertyValue* ToRealValue() const;

  private:
    SgfcReal realValue;
  };
}
