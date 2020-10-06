#pragma once

// Project includes
#include "../../../include/ISgfcPointPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPointPropertyValue class provides an implementation of
  /// the ISgfcPointPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcPointPropertyValue : public SgfcSinglePropertyValue, virtual public ISgfcPointPropertyValue
  {
  public:
    SgfcPointPropertyValue(const std::string& rawValue);
    virtual ~SgfcPointPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual std::string GetRawPointValue() const;
    virtual const ISgfcPointPropertyValue* ToPointValue() const;
    virtual const ISgfcGoPointPropertyValue* ToGoPointValue() const;
  };
}
