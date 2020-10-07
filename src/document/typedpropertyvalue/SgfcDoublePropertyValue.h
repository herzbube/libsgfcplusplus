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
    /// @brief Initializes a newly constructed SgfcDoublePropertyValue object.
    /// The object holds the Double value @a doubleValue which was successfully
    /// converted from the raw string value @a rawValue.
    SgfcDoublePropertyValue(const std::string& rawValue, SgfcDouble doubleValue);

    /// @brief Initializes a newly constructed SgfcDoublePropertyValue object.
    /// The object holds no typed Doube value because conversion from the raw
    /// string value @a rawValue failed. @a typeConversionErrorMessage indicates
    /// the reason for the conversion failure.
    SgfcDoublePropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage);

    /// @brief Destroys and cleans up the SgfcDoublePropertyValue object.
    virtual ~SgfcDoublePropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual SgfcDouble GetDoubleValue() const;
    virtual const ISgfcDoublePropertyValue* ToDoubleValue() const;

  private:
    SgfcDouble doubleValue;
  };
}
