#pragma once

// Project includes
#include "../include/ISgfcPropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyValue class provides an implementation of the
  /// ISgfcPropertyValue interface. See the interface header file for
  /// documentation.
  class SgfcPropertyValue : public ISgfcPropertyValue
  {
  public:
    SgfcPropertyValue();
    SgfcPropertyValue(const std::string& rawValue);
    SgfcPropertyValue(const std::string& rawValue1, const std::string& rawValue2);
    virtual ~SgfcPropertyValue();

    virtual bool IsCompositeValue() const;

    virtual SgfcPropertyValueType GetValueType1() const;
    virtual std::string GetRawValue1() const;

    virtual SgfcPropertyValueType GetValueType2() const;
    virtual std::string GetRawValue2() const;

  private:
    bool isCompositeValue;
    SgfcPropertyValueType valueType1;
    std::string rawValue1;
    SgfcPropertyValueType valueType2;
    std::string rawValue2;
  };
}
