#pragma once

// Project includes
#include "../../include/ISgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcSinglePropertyValue class provides an implementation of the
  /// ISgfcSinglePropertyValue interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcSinglePropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcSinglePropertyValue object
    /// that has the raw property string value @a rawValue. HasTypedValue()
    /// returns @a hasTypedValue and GetTypeConversionErrorMessage() returns an
    /// empty string.
    SgfcSinglePropertyValue(const std::string& rawValue, bool hasTypedValue);

    /// @brief Initializes a newly constructed SgfcSinglePropertyValue object
    /// that has the raw property string value @a rawValue. HasTypedValue()
    /// returns false and GetTypeConversionErrorMessage() returns
    /// @a typeConversionErrorMessage.
    SgfcSinglePropertyValue(const std::string& rawValue, const std::string& typeConversionErrorMessage);

    /// @brief Destroys and cleans up the SgfcSinglePropertyValue object.
    virtual ~SgfcSinglePropertyValue();

    virtual bool IsComposedValue() const;
    virtual const ISgfcSinglePropertyValue* ToSingleValue() const;

    virtual bool HasTypedValue() const;
    virtual std::string GetTypeConversionErrorMessage() const;

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
    std::string typeConversionErrorMessage;
    std::string rawValue;
  };
}
