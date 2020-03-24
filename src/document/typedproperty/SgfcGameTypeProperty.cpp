// Project includes
#include "../../../include/ISgfcNumberPropertyValue.h"
#include "../../../include/SgfcConstants.h"
#include "../../SgfcUtility.h"
#include "SgfcGameTypeProperty.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcGameTypeProperty::SgfcGameTypeProperty()
    : SgfcProperty(SgfcPropertyType::GM,
                   SgfcUtility::MapPropertyTypeToPropertyName(SgfcPropertyType::GM))
  {
  }

  SgfcGameTypeProperty::SgfcGameTypeProperty(
    std::shared_ptr<ISgfcNumberPropertyValue> propertyValue)
    : SgfcProperty(SgfcPropertyType::GM,
                   SgfcUtility::MapPropertyTypeToPropertyName(SgfcPropertyType::GM),
                   std::vector<std::shared_ptr<ISgfcPropertyValue>>{propertyValue})
  {
    if (propertyValue == nullptr)
      throw std::invalid_argument("SgfcGameTypeProperty constructor failed: Property value is nullptr");

    if (! propertyValue->HasTypedValue())
      throw std::invalid_argument("SgfcGameTypeProperty constructor failed: Property value is not a Number value");
  }

  SgfcGameTypeProperty::~SgfcGameTypeProperty()
  {
  }

  const ISgfcGameTypeProperty* SgfcGameTypeProperty::ToGameTypeProperty() const
  {
    return this;
  }

  SgfcGameType SgfcGameTypeProperty::GetGameType() const
  {
    SgfcNumber gameTypeAsNumber = GetGameTypeAsNumber();

    return SgfcUtility::MapNumberValueToGameType(
      gameTypeAsNumber);
  }

  SgfcNumber SgfcGameTypeProperty::GetGameTypeAsNumber() const
  {
    auto propertyValue = GetPropertyValue();

    if (propertyValue == nullptr)
      return SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType);

    // Constructor did checks for us
    const ISgfcNumberPropertyValue* numberValue =
      propertyValue->ToSingleValue()->ToNumberValue();

    return numberValue->GetNumberValue();
  }
}
