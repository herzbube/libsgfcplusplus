// Project includes
#include "SgfcPropertyValue.h"
#include "SgfcComposedPropertyValue.h"
#include "SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  SgfcPropertyValue::SgfcPropertyValue()
    : isComposedValue(false)
  {
  }

  SgfcPropertyValue::SgfcPropertyValue(const std::string& rawValue)
    : isComposedValue(false)
  {
    this->singleValue = std::shared_ptr<ISgfcSinglePropertyValue>(
      new SgfcSinglePropertyValue(rawValue));
  }

  SgfcPropertyValue::SgfcPropertyValue(const std::string& rawValue1, const std::string& rawValue2)
    : isComposedValue(true)
  {
    this->composedValue = std::shared_ptr<ISgfcComposedPropertyValue>(new SgfcComposedPropertyValue(
      std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcSinglePropertyValue(rawValue1)),
      std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcSinglePropertyValue(rawValue2))));
  }

  SgfcPropertyValue::~SgfcPropertyValue()
  {
  }

  bool SgfcPropertyValue::IsComposedValue() const
  {
    return this->isComposedValue;
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyValue::ToSingleValue() const
  {
    return this->singleValue;
  }

  std::shared_ptr<ISgfcComposedPropertyValue> SgfcPropertyValue::ToComposedValue() const
  {
    return this->composedValue;
  }
}
