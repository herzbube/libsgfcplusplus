#pragma once

// Project includes
#include "../../../include/ISgfcNumberPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcNumberPropertyValue class provides an implementation of
  /// the ISgfcNumberPropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcNumberPropertyValue : public SgfcSinglePropertyValue, ISgfcNumberPropertyValue
  {
  public:
    SgfcNumberPropertyValue(const std::string& rawValue, long numberValue);
    SgfcNumberPropertyValue(const std::string& rawValue);
    virtual ~SgfcNumberPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual long GetNumberValue() const;
    virtual const ISgfcNumberPropertyValue* ToNumberValue() const;

  private:
    long numberValue;
  };
}
