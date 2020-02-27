#pragma once

// Project includes
#include "../../include/ISgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcSinglePropertyValue class provides an implementation of the
  /// ISgfcSinglePropertyValue interface. See the interface header file for
  /// documentation.
  class SgfcSinglePropertyValue : public ISgfcSinglePropertyValue
  {
  public:
    SgfcSinglePropertyValue(bool hasTypedValue, const std::string& rawValue);
    virtual ~SgfcSinglePropertyValue();

    virtual bool IsComposedValue() const;
    virtual const ISgfcSinglePropertyValue* ToSingleValue() const;
    virtual const ISgfcComposedPropertyValue* ToComposedValue() const;

    virtual bool HasTypedValue() const;
    virtual std::string GetRawValue() const;

    virtual const ISgfcNumberPropertyValue* ToNumberValue() const;
    virtual const ISgfcRealPropertyValue* ToRealValue() const;
    virtual const ISgfcDoublePropertyValue* ToDoubleValue() const;
    virtual const ISgfcColorPropertyValue* ToColorValue() const;
    virtual const ISgfcSimpleTextPropertyValue* ToSimpleTextValue() const;
    virtual const ISgfcTextPropertyValue* ToTextValue() const;
    virtual const ISgfcPointPropertyValue* ToPointValue() const;
    virtual const ISgfcMovePropertyValue* ToMoveValue() const;
    virtual const ISgfcStonePropertyValue* ToStoneValue() const;

  protected:
    /// @brief Throws std::logic_error if HasTypedValue() returns false.
    ///
    /// This is a convenience method that subclasses may invoke in their getter
    /// method that returns the typed property value.
    void ThrowIfHasNotTypedValue() const;

  private:
    bool hasTypedValue;
    std::string rawValue;
  };
}
