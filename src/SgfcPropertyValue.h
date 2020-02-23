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

    virtual bool IsComposedValue() const;

    virtual std::shared_ptr<ISgfcSinglePropertyValue> ToSingleValue() const;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> ToComposedValue() const;

  private:
    bool isComposedValue;
    std::shared_ptr<ISgfcSinglePropertyValue> singleValue;
    std::shared_ptr<ISgfcComposedPropertyValue> composedValue;
  };
}
