#pragma once

// Project includes
#include "../../../include/ISgfcSimpleTextPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcSimpleTextPropertyValue class provides an implementation of
  /// the ISgfcSimpleTextPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcSimpleTextPropertyValue : public SgfcSinglePropertyValue, public ISgfcSimpleTextPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcSimpleTextPropertyValue
    /// object. The object holds the SimpleText value @a simpleTextValue which
    /// was successfully converted from the raw string value @a rawValue.
    SgfcSimpleTextPropertyValue(const std::string& rawValue, const std::string& simpleTextValue);

    /// @brief Destroys and cleans up the SgfcSimpleTextPropertyValue object.
    virtual ~SgfcSimpleTextPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual std::string GetSimpleTextValue() const;
    virtual const ISgfcSimpleTextPropertyValue* ToSimpleTextValue() const;

  private:
    std::string simpleTextValue;
  };
}
