// Project includes
#include "SgfcProperty.h"

namespace LibSgfcPlusPlus
{
  SgfcProperty::SgfcProperty(
    SgfcPropertyType propertyType,
    const std::string& propertyName)
    : propertyType(propertyType)
    , propertyName(propertyName)
  {
  }

  SgfcProperty::SgfcProperty(
    SgfcPropertyType propertyType,
    const std::string& propertyName,
    const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
    : propertyType(propertyType)
    , propertyName(propertyName)
    , propertyValues(propertyValues)
  {
  }

  SgfcProperty::~SgfcProperty()
  {
  }

  SgfcPropertyType SgfcProperty::GetPropertyType() const
  {
    return this->propertyType;
  }

  std::string SgfcProperty::GetPropertyName() const
  {
    return this->propertyName;
  }

  std::vector<std::shared_ptr<ISgfcPropertyValue>> SgfcProperty::GetPropertyValues() const
  {
    return this->propertyValues;
  }

  void SgfcProperty::SetPropertyValues(
    const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
  {
    this->propertyValues = propertyValues;
  }

  std::shared_ptr<ISgfcPropertyValue> SgfcProperty::GetPropertyValue() const
  {
    auto it = this->propertyValues.cbegin();
    if (it != this->propertyValues.cend())
      return *it;
    else
      return nullptr;
  }

  const ISgfcBoardSizeProperty* SgfcProperty::ToBoardSizeProperty() const
  {
    return nullptr;
  }
}
