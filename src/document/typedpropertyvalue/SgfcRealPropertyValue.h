#pragma once

// Project includes
#include "../../../include/ISgfcRealPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcRealPropertyValue class provides an implementation of
  /// the ISgfcRealPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcRealPropertyValue : public SgfcSinglePropertyValue, public ISgfcRealPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcRealPropertyValue object.
    /// The object holds the Real value @a realValue which was successfully
    /// converted from the raw string value @a rawValue.
    SgfcRealPropertyValue(const std::string& rawValue, SgfcReal realValue);

    /// @brief Initializes a newly constructed SgfcRealPropertyValue object.
    /// The object holds no typed Real value because conversion from the raw
    /// string value @a rawValue failed. @a typeConversionErrorMessage indicates
    /// the reason for the conversion failure.
    SgfcRealPropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage);

    /// @brief Destroys and cleans up the SgfcRealPropertyValue object.
    virtual ~SgfcRealPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual SgfcReal GetRealValue() const;
    virtual const ISgfcRealPropertyValue* ToRealValue() const;

  private:
    SgfcReal realValue;
  };
}
