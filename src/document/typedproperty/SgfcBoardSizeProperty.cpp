// Project includes
#include "../../../include/ISgfcComposedPropertyValue.h"
#include "../../../include/ISgfcNumberPropertyValue.h"
#include "../../../include/SgfcConstants.h"
#include "../../SgfcUtility.h"
#include "SgfcBoardSizeProperty.h"

namespace LibSgfcPlusPlus
{
  SgfcBoardSizeProperty::SgfcBoardSizeProperty()
    : SgfcProperty(SgfcPropertyType::SZ,
                   SgfcUtility::MapPropertyTypeToPropertyName(SgfcPropertyType::SZ))
  {
  }

  SgfcBoardSizeProperty::SgfcBoardSizeProperty(
    std::shared_ptr<ISgfcNumberPropertyValue> propertyValue)
    : SgfcProperty(SgfcPropertyType::SZ,
                   SgfcUtility::MapPropertyTypeToPropertyName(SgfcPropertyType::SZ),
                   std::vector<std::shared_ptr<ISgfcPropertyValue>>{propertyValue})
  {
    if (propertyValue == nullptr)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Property value is nullptr");

    if (! propertyValue->HasTypedValue())
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Property value is not a Number value");
  }

  SgfcBoardSizeProperty::SgfcBoardSizeProperty(
    std::shared_ptr<ISgfcComposedPropertyValue> propertyValue)
    : SgfcProperty(SgfcPropertyType::SZ,
                   SgfcUtility::MapPropertyTypeToPropertyName(SgfcPropertyType::SZ),
                   std::vector<std::shared_ptr<ISgfcPropertyValue>>{propertyValue})
  {
    if (propertyValue == nullptr)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Property value is nullptr");

    auto singleValue1 = propertyValue->GetValue1();
    if (singleValue1 == nullptr)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Value 1 of composed property value is nullptr");
    if (! singleValue1->HasTypedValue() || singleValue1->GetValueType() != SgfcPropertyValueType::Number)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Value 1 of composed property value is not a Number value");

    auto singleValue2 = propertyValue->GetValue2();
    if (singleValue2 == nullptr)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Value 2 of composed property value is nullptr");
    if (! singleValue2->HasTypedValue() || singleValue2->GetValueType() != SgfcPropertyValueType::Number)
      throw std::invalid_argument("SgfcBoardSizeProperty constructor failed: Value 2 of composed property value is not a Number value");
  }

  SgfcBoardSizeProperty::~SgfcBoardSizeProperty()
  {
  }

  const ISgfcBoardSizeProperty* SgfcBoardSizeProperty::ToBoardSizeProperty() const
  {
    return this;
  }

  SgfcBoardSize SgfcBoardSizeProperty::GetBoardSize(SgfcGameType gameType) const
  {
    auto propertyValue = GetPropertyValue();

    if (propertyValue == nullptr)
    {
      switch (gameType)
      {
        case SgfcGameType::Go:
          return SgfcConstants::BoardSizeDefaultGo;
        case SgfcGameType::Chess:
          return SgfcConstants::BoardSizeDefaultChess;
        default:
          return SgfcConstants::BoardSizeNone;
      }
    }

    if (propertyValue->IsComposedValue())
    {
      const auto* composedValue = propertyValue->ToComposedValue();

      SgfcNumber numberOfColumns = -1;
      SgfcNumber numberOfRows = -1;

      auto singleValue1 = composedValue->GetValue1();
      if (singleValue1->HasTypedValue())
      {
        if (singleValue1->GetValueType() == SgfcPropertyValueType::Number)
          numberOfColumns = singleValue1->ToNumberValue()->GetNumberValue();
      }
      auto singleValue2 = composedValue->GetValue2();
      if (singleValue2->HasTypedValue())
      {
        if (singleValue2->GetValueType() == SgfcPropertyValueType::Number)
          numberOfRows = singleValue2->ToNumberValue()->GetNumberValue();
      }

      if (numberOfColumns != -1 && numberOfRows != -1)
        return { numberOfColumns, numberOfRows };
    }
    else
    {
      const auto* singleValue = propertyValue->ToSingleValue();
      if (singleValue->HasTypedValue())
      {
        if (singleValue->GetValueType() == SgfcPropertyValueType::Number)
        {
          SgfcNumber numberOfColumnsAndRows = singleValue->ToNumberValue()->GetNumberValue();
          return { numberOfColumnsAndRows, numberOfColumnsAndRows };
        }
      }
    }

    return SgfcConstants::BoardSizeNone;
  }
}
