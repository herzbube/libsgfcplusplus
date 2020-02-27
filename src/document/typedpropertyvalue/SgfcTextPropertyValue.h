#pragma once

// Project includes
#include "../../../include/ISgfcTextPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcTextPropertyValue class provides an implementation of
  /// the ISgfcTextPropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcTextPropertyValue : public SgfcSinglePropertyValue, public ISgfcTextPropertyValue
  {
  public:
    SgfcTextPropertyValue(const std::string& rawValue, const std::string& textValue);
    SgfcTextPropertyValue(const std::string& rawValue);
    virtual ~SgfcTextPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual std::string GetTextValue() const;
    virtual const ISgfcTextPropertyValue* ToTextValue() const;

  private:
    std::string textValue;
  };
}
