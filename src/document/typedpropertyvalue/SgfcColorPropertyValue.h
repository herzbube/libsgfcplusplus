#pragma once

// Project includes
#include "../../../include/ISgfcColorPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcColorPropertyValue class provides an implementation of
  /// the ISgfcColorPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcColorPropertyValue : public SgfcSinglePropertyValue, public ISgfcColorPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcColorPropertyValue object.
    /// The object holds the Color value @a colorValue which was successfully
    /// converted from the raw string value @a rawValue.
    SgfcColorPropertyValue(const std::string& rawValue, SgfcColor colorValue);

    /// @brief Initializes a newly constructed SgfcColorPropertyValue object.
    /// The object holds no typed Color value because conversion from the raw
    /// string value @a rawValue failed. @a typeConversionErrorMessage indicates
    /// the reason for the conversion failure.
    SgfcColorPropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage);

    /// @brief Destroys and cleans up the SgfcColorPropertyValue object.
    virtual ~SgfcColorPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual SgfcColor GetColorValue() const;
    virtual const ISgfcColorPropertyValue* ToColorValue() const;

  private:
    SgfcColor colorValue;
  };
}
