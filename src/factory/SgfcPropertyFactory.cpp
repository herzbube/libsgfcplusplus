// Project includes
#include "../document/typedproperty/SgfcGameTypeProperty.h"
#include "../document/SgfcProperty.h"
#include "../SgfcUtility.h"
#include "SgfcPropertyFactory.h"

namespace LibSgfcPlusPlus
{
  SgfcPropertyFactory::SgfcPropertyFactory()
  {
  }

  SgfcPropertyFactory::~SgfcPropertyFactory()
  {
  }

  std::shared_ptr<ISgfcProperty> SgfcPropertyFactory::CreateProperty(
    SgfcPropertyType propertyType)
  {
    std::shared_ptr<ISgfcProperty> property = CreateProperty(
      propertyType,
      std::vector<std::shared_ptr<ISgfcPropertyValue>> {} );

    return property;
  }

  std::shared_ptr<ISgfcProperty> SgfcPropertyFactory::CreateProperty(
    SgfcPropertyType propertyType,
    std::shared_ptr<ISgfcPropertyValue> propertyValue)
  {
    std::shared_ptr<ISgfcProperty> property = CreateProperty(
      propertyType,
      std::vector<std::shared_ptr<ISgfcPropertyValue>> { propertyValue } );

    return property;
  }

  std::shared_ptr<ISgfcProperty> SgfcPropertyFactory::CreateProperty(
    SgfcPropertyType propertyType,
    const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
  {
    std::string propertyName = SgfcUtility::MapPropertyTypeToPropertyName(propertyType);

    std::shared_ptr<ISgfcProperty> property = CreateProperty(
      propertyType,
      propertyName,
      propertyValues);

    return property;
  }

  std::shared_ptr<ISgfcProperty> SgfcPropertyFactory::CreateProperty(
    const std::string& propertyName)
  {
    std::shared_ptr<ISgfcProperty> property = CreateProperty(
      propertyName,
      std::vector<std::shared_ptr<ISgfcPropertyValue>> {} );

    return property;
  }

  std::shared_ptr<ISgfcProperty> SgfcPropertyFactory::CreateProperty(
    const std::string& propertyName,
    std::shared_ptr<ISgfcPropertyValue> propertyValue)
  {
    std::shared_ptr<ISgfcProperty> property = CreateProperty(
      propertyName,
      std::vector<std::shared_ptr<ISgfcPropertyValue>> { propertyValue } );

    return property;
  }

  std::shared_ptr<ISgfcProperty> SgfcPropertyFactory::CreateProperty(
    const std::string& propertyName,
    const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
  {
    SgfcPropertyType propertyType = SgfcUtility::MapPropertyNameToPropertyType(propertyName);

    std::shared_ptr<ISgfcProperty> property = CreateProperty(
      propertyType,
      propertyName,
      propertyValues);

    return property;
  }

  std::shared_ptr<ISgfcGameTypeProperty> SgfcPropertyFactory::CreateGameTypeProperty()
  {
    std::shared_ptr<ISgfcGameTypeProperty> property =
      std::shared_ptr<ISgfcGameTypeProperty>(new SgfcGameTypeProperty());

    return property;
  }

  std::shared_ptr<ISgfcGameTypeProperty> SgfcPropertyFactory::CreateGameTypeProperty(
    std::shared_ptr<ISgfcNumberPropertyValue> propertyValue)
  {
    std::shared_ptr<ISgfcGameTypeProperty> property =
      std::shared_ptr<ISgfcGameTypeProperty>(new SgfcGameTypeProperty(propertyValue));

    return property;
  }

  std::shared_ptr<ISgfcProperty> SgfcPropertyFactory::CreateProperty(
    SgfcPropertyType propertyType,
    const std::string& propertyName,
    const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
  {
    std::shared_ptr<ISgfcProperty> property = std::shared_ptr<ISgfcProperty>(new SgfcProperty(
      propertyType,
      propertyName));

    property->SetPropertyValues(propertyValues);

    return property;
  }
}
