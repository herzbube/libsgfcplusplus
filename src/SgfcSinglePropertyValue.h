#pragma once

// Project includes
#include "../include/ISgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcSinglePropertyValue class provides an implementation of the
  /// ISgfcSinglePropertyValue interface. See the interface header file for
  /// documentation.
  class SgfcSinglePropertyValue : public ISgfcSinglePropertyValue
  {
  public:
    SgfcSinglePropertyValue();
    SgfcSinglePropertyValue(const std::string& rawValue);
    virtual ~SgfcSinglePropertyValue();

    virtual bool IsComposedValue() const;
    virtual const ISgfcSinglePropertyValue* ToSingleValue() const;
    virtual const ISgfcComposedPropertyValue* ToComposedValue() const;

    virtual SgfcPropertyValueType GetValueType() const;
    virtual std::string GetRawValue() const;

  private:
    SgfcPropertyValueType valueType;
    std::string rawValue;
  };
}
