// Project includes
#include "../../include/ISgfcComposedPropertyValue.h"
#include "../../include/ISgfcSinglePropertyValue.h"
#include "../document/typedproperty/SgfcBoardSizeProperty.h"
#include "../document/typedproperty/SgfcGameTypeProperty.h"
#include "../document/typedpropertyvalue/SgfcNumberPropertyValue.h"
#include "../document/SgfcProperty.h"
#include "../SgfcUtility.h"
#include "SgfcPropertyFactory.h"

// C++ Standard Library includes
#include <stdexcept>

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

  std::shared_ptr<ISgfcBoardSizeProperty> SgfcPropertyFactory::CreateBoardSizeProperty()
  {
    std::shared_ptr<ISgfcBoardSizeProperty> property =
      std::shared_ptr<ISgfcBoardSizeProperty>(new SgfcBoardSizeProperty());

    return property;
  }

  std::shared_ptr<ISgfcBoardSizeProperty> SgfcPropertyFactory::CreateBoardSizeProperty(
    std::shared_ptr<ISgfcNumberPropertyValue> propertyValue)
  {
    std::shared_ptr<ISgfcBoardSizeProperty> property =
      std::shared_ptr<ISgfcBoardSizeProperty>(new SgfcBoardSizeProperty(propertyValue));

    return property;
  }

  std::shared_ptr<ISgfcBoardSizeProperty> SgfcPropertyFactory::CreateBoardSizeProperty(
    std::shared_ptr<ISgfcComposedPropertyValue> propertyValue)
  {
    std::shared_ptr<ISgfcBoardSizeProperty> property =
      std::shared_ptr<ISgfcBoardSizeProperty>(new SgfcBoardSizeProperty(propertyValue));

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
    if (propertyType == SgfcPropertyType::SZ)
    {
      if (propertyValues.size() == 0)
      {
        return CreateBoardSizeProperty();
      }
      else if (propertyValues.size() >= 2)
      {
        throw std::invalid_argument("SgfcPropertyFactory::CreateProperty failed: More than one value specified for property type SZ");
      }
      else
      {
        auto propertyValue = propertyValues.front();

        if (propertyValue->IsComposedValue())
        {
          std::shared_ptr<ISgfcComposedPropertyValue> composedValueSharedPtr =
            std::dynamic_pointer_cast<ISgfcComposedPropertyValue>(propertyValue);

          return CreateBoardSizeProperty(composedValueSharedPtr);
        }
        else
        {
          std::shared_ptr<ISgfcNumberPropertyValue> numberValueSharedPtr =
            std::dynamic_pointer_cast<ISgfcNumberPropertyValue>(propertyValue);

          // Can also throw std::invalid_argument
          return CreateBoardSizeProperty(numberValueSharedPtr);
        }
      }
    }
    else if (propertyType == SgfcPropertyType::GM)
    {
      if (propertyValues.size() == 0)
      {
        return CreateGameTypeProperty();
      }
      else if (propertyValues.size() >= 2)
      {
        throw std::invalid_argument("SgfcPropertyFactory::CreateProperty failed: More than one value specified for property type GM");
      }
      else
      {
        auto propertyValue = propertyValues.front();
        if (propertyValue->IsComposedValue())
        {
          throw std::invalid_argument("SgfcPropertyFactory::CreateProperty failed: Composed value specified for property type GM");
        }

        const ISgfcNumberPropertyValue* numberValue = propertyValue->ToSingleValue()->ToNumberValue();
        if (numberValue == nullptr)
        {
            throw std::invalid_argument("SgfcPropertyFactory::CreateProperty failed: Value specified for property type GM is not a Number value");
        }

        std::shared_ptr<ISgfcNumberPropertyValue> numberValueSharedPtr =
          std::dynamic_pointer_cast<ISgfcNumberPropertyValue>(propertyValue);

        // Can also throw std::invalid_argument
        return CreateGameTypeProperty(numberValueSharedPtr);
      }
    }
    else
    {
      std::shared_ptr<ISgfcProperty> property = std::shared_ptr<ISgfcProperty>(new SgfcProperty(
        propertyType,
        propertyName));

      property->SetPropertyValues(propertyValues);

      return property;
    }
  }
}
