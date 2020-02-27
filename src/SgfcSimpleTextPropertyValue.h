#pragma once

// Project includes
#include "../include/ISgfcSimpleTextPropertyValue.h"
#include "SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcSimpleTextPropertyValue class provides an implementation of
  /// the ISgfcSimpleTextPropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcSimpleTextPropertyValue : public SgfcSinglePropertyValue, ISgfcSimpleTextPropertyValue
  {
  public:
    SgfcSimpleTextPropertyValue(const std::string& rawValue, const std::string& simpleTextValue);
    SgfcSimpleTextPropertyValue(const std::string& rawValue);
    virtual ~SgfcSimpleTextPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual std::string GetSimpleTextValue() const;
    virtual const ISgfcSimpleTextPropertyValue* ToSimpleTextValue() const;

  private:
    std::string simpleTextValue;
  };
}
