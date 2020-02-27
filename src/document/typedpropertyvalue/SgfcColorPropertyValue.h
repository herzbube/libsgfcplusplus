#pragma once

// Project includes
#include "../../../include/ISgfcColorPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcColorPropertyValue class provides an implementation of
  /// the ISgfcColorPropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcColorPropertyValue : public SgfcSinglePropertyValue, public ISgfcColorPropertyValue
  {
  public:
    SgfcColorPropertyValue(const std::string& rawValue, SgfcColor colorValue);
    SgfcColorPropertyValue(const std::string& rawValue);
    virtual ~SgfcColorPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual SgfcColor GetColorValue() const;
    virtual const ISgfcColorPropertyValue* ToColorValue() const;

  private:
    SgfcColor colorValue;
  };
}
