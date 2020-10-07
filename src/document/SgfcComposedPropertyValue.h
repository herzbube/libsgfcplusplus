#pragma once

// Project includes
#include "../../include/ISgfcComposedPropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcComposedPropertyValue class provides an implementation of
  /// the ISgfcComposedPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcComposedPropertyValue : public ISgfcComposedPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcComposedPropertyValue object
    /// that consists of the two values @a value1 and @a value2.
    SgfcComposedPropertyValue(
      std::shared_ptr<ISgfcSinglePropertyValue> value1,
      std::shared_ptr<ISgfcSinglePropertyValue> value2);

    /// @brief Destroys and cleans up the SgfcSinglePropertyValue object.
    virtual ~SgfcComposedPropertyValue();

    virtual bool IsComposedValue() const;
    virtual const ISgfcComposedPropertyValue* ToComposedValue() const;

    virtual std::shared_ptr<ISgfcSinglePropertyValue> GetValue1() const;
    virtual std::shared_ptr<ISgfcSinglePropertyValue> GetValue2() const;

  private:
    std::shared_ptr<ISgfcSinglePropertyValue> value1;
    std::shared_ptr<ISgfcSinglePropertyValue> value2;
  };
}
