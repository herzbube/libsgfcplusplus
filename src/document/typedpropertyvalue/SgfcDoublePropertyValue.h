#pragma once

// Project includes
#include "../../../include/ISgfcDoublePropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDoublePropertyValue class provides an implementation of
  /// the ISgfcDoublePropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcDoublePropertyValue : public SgfcSinglePropertyValue, public ISgfcDoublePropertyValue
  {
  public:
    SgfcDoublePropertyValue(const std::string& rawValue, SgfcDouble doubleValue);
    SgfcDoublePropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage);
    virtual ~SgfcDoublePropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual SgfcDouble GetDoubleValue() const;
    virtual const ISgfcDoublePropertyValue* ToDoubleValue() const;

  private:
    SgfcDouble doubleValue;
  };
}
