#pragma once

// Project includes
#include "../../../include/ISgfcTextPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcTextPropertyValue class provides an implementation of
  /// the ISgfcTextPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcTextPropertyValue : public SgfcSinglePropertyValue, public ISgfcTextPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcTextPropertyValue
    /// object. The object holds the SimpleText value @a textValue which
    /// was successfully converted from the raw string value @a rawValue.
    SgfcTextPropertyValue(const std::string& rawValue, const std::string& textValue);

    /// @brief Destroys and cleans up the SgfcTextPropertyValue object.
    virtual ~SgfcTextPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual std::string GetTextValue() const;
    virtual const ISgfcTextPropertyValue* ToTextValue() const;

  private:
    std::string textValue;
  };
}
