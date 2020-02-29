// Project includes
#include "SgfcComposedPropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcComposedPropertyValue::SgfcComposedPropertyValue()
  {
  }

  SgfcComposedPropertyValue::SgfcComposedPropertyValue(
    std::shared_ptr<ISgfcSinglePropertyValue> value1,
    std::shared_ptr<ISgfcSinglePropertyValue> value2)
    : value1(value1)
    , value2(value2)
  {
  }

  SgfcComposedPropertyValue::~SgfcComposedPropertyValue()
  {
  }

  bool SgfcComposedPropertyValue::IsComposedValue() const
  {
    return true;
  }

  const ISgfcComposedPropertyValue* SgfcComposedPropertyValue::ToComposedValue() const
  {
    return this;
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcComposedPropertyValue::GetValue1() const
  {
    return this->value1;
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcComposedPropertyValue::GetValue2() const
  {
    return this->value2;
  }
}
