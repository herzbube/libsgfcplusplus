#pragma once

// Project includes
#include "../../../include/ISgfcDoublePropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDoublePropertyValue class provides an implementation of
  /// the ISgfcDoublePropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcDoublePropertyValue : public SgfcSinglePropertyValue, ISgfcDoublePropertyValue
  {
  public:
    SgfcDoublePropertyValue(const std::string& rawValue, SgfcDouble doubleValue);
    SgfcDoublePropertyValue(const std::string& rawValue);
    virtual ~SgfcDoublePropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual SgfcDouble GetDoubleValue() const;
    virtual const ISgfcDoublePropertyValue* ToDoubleValue() const;

  private:
    SgfcDouble doubleValue;
  };
}
