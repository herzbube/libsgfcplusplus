#pragma once

// Project includes
#include "../../../include/ISgfcPointPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPointPropertyValue class provides an implementation of
  /// the ISgfcPointPropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcPointPropertyValue : public SgfcSinglePropertyValue, public ISgfcPointPropertyValue
  {
  public:
    SgfcPointPropertyValue(const std::string& rawValue);
    virtual ~SgfcPointPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual std::string GetRawPointValue() const;
    virtual const ISgfcPointPropertyValue* ToPointValue() const;
  };
}
