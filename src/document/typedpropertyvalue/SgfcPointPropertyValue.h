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
    /// @brief Initializes a newly constructed SgfcPointPropertyValue
    /// object. The object holds a Point value which was not interpreted in
    /// any way and equals the raw string value @a rawValue.
    SgfcPointPropertyValue(const std::string& rawValue);

    /// @brief Destroys and cleans up the SgfcPointPropertyValue object.
    virtual ~SgfcPointPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
    virtual std::string GetRawPointValue() const;
    virtual const ISgfcPointPropertyValue* ToPointValue() const;
    virtual const ISgfcGoPointPropertyValue* ToGoPointValue() const;
  };
}
