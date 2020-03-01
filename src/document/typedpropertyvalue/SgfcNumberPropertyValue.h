#pragma once

// Project includes
#include "../../../include/ISgfcNumberPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcNumberPropertyValue class provides an implementation of
  /// the ISgfcNumberPropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcNumberPropertyValue : public SgfcSinglePropertyValue, public ISgfcNumberPropertyValue
  {
  public:
    SgfcNumberPropertyValue(const std::string& rawValue, SgfcNumber numberValue);
    SgfcNumberPropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage);
    virtual ~SgfcNumberPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual SgfcNumber GetNumberValue() const;
    virtual const ISgfcNumberPropertyValue* ToNumberValue() const;

  private:
    SgfcNumber numberValue;
  };
}
