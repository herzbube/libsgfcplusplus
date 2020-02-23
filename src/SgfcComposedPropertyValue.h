#pragma once

// Project includes
#include "../include/ISgfcComposedPropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcComposedPropertyValue class provides an implementation of
  /// the ISgfcComposedPropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcComposedPropertyValue : public ISgfcComposedPropertyValue
  {
  public:
    SgfcComposedPropertyValue();
    SgfcComposedPropertyValue(
      std::shared_ptr<ISgfcSinglePropertyValue> value1,
      std::shared_ptr<ISgfcSinglePropertyValue> value2);
    virtual ~SgfcComposedPropertyValue();

    virtual std::shared_ptr<ISgfcSinglePropertyValue> GetValue1() const;
    virtual std::shared_ptr<ISgfcSinglePropertyValue> GetValue2() const;

  private:
    std::shared_ptr<ISgfcSinglePropertyValue> value1;
    std::shared_ptr<ISgfcSinglePropertyValue> value2;
  };
}
