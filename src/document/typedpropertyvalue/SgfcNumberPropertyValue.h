#pragma once

// Project includes
#include "../../../include/ISgfcNumberPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcNumberPropertyValue class provides an implementation of
  /// the ISgfcNumberPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcNumberPropertyValue : public SgfcSinglePropertyValue, public ISgfcNumberPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcNumberPropertyValue object.
    /// The object holds the Number value @a numberValue which was successfully
    /// converted from the raw string value @a rawValue.
    SgfcNumberPropertyValue(const std::string& rawValue, SgfcNumber numberValue);

    /// @brief Initializes a newly constructed SgfcNumberPropertyValue object.
    /// The object holds no typed Number value because conversion from the raw
    /// string value @a rawValue failed. @a typeConversionErrorMessage indicates
    /// the reason for the conversion failure.
    SgfcNumberPropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage);

    /// @brief Destroys and cleans up the SgfcNumberPropertyValue object.
    virtual ~SgfcNumberPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual SgfcNumber GetNumberValue() const;
    virtual const ISgfcNumberPropertyValue* ToNumberValue() const;

  private:
    SgfcNumber numberValue;
  };
}
