// Project includes
#include "../../../include/ISgfcComposedPropertyValue.h"
#include "../../../include/ISgfcNumberPropertyValue.h"
#include "../../../include/SgfcConstants.h"
#include "../../SgfcUtility.h"
#include "SgfcBoardSizeProperty.h"

// C++ Standard Library includes
#include <stdexcept>

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
      return GetDefaultBoardSize(gameType);

    SgfcBoardSize boardSize;
    if (propertyValue->IsComposedValue())
      boardSize = GetBoardSizeFromComposedValue(propertyValue->ToComposedValue());
    else
      boardSize = GetBoardSizeFromSingleValue(propertyValue->ToSingleValue());

    bool isBoardSizeValid = IsBoardSizeValid(boardSize, gameType);
    if (isBoardSizeValid)
      return boardSize;
    else
      return SgfcConstants::BoardSizeInvalid;
  }

  SgfcBoardSize SgfcBoardSizeProperty::GetDefaultBoardSize(SgfcGameType gameType) const
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

  SgfcBoardSize SgfcBoardSizeProperty::GetBoardSizeFromSingleValue(const ISgfcSinglePropertyValue* singleValue) const
  {
    if (! singleValue->HasTypedValue())
      return SgfcConstants::BoardSizeNone;

    if (singleValue->GetValueType() != SgfcPropertyValueType::Number)
      return SgfcConstants::BoardSizeNone;

    SgfcNumber numberOfColumnsAndRows = singleValue->ToNumberValue()->GetNumberValue();
    return { numberOfColumnsAndRows, numberOfColumnsAndRows };
  }

  SgfcBoardSize SgfcBoardSizeProperty::GetBoardSizeFromComposedValue(const ISgfcComposedPropertyValue* composedValue) const
  {
    auto singleValue1 = composedValue->GetValue1();
    auto singleValue2 = composedValue->GetValue2();

    if (! singleValue1->HasTypedValue() || ! singleValue2->HasTypedValue())
      return SgfcConstants::BoardSizeNone;

    if (singleValue1->GetValueType() != SgfcPropertyValueType::Number ||
        singleValue2->GetValueType() != SgfcPropertyValueType::Number)
    {
      return SgfcConstants::BoardSizeNone;
    }

    return
    {
      singleValue1->ToNumberValue()->GetNumberValue(),
      singleValue2->ToNumberValue()->GetNumberValue()
    };
  }

  bool SgfcBoardSizeProperty::IsBoardSizeValid(SgfcBoardSize boardSize, SgfcGameType gameType) const
  {
    if (boardSize.Columns < SgfcConstants::BoardSizeMinimum.Columns ||
        boardSize.Rows < SgfcConstants::BoardSizeMinimum.Rows)
    {
      return false;
    }

    if (gameType == SgfcGameType::Go)
    {
      if (boardSize.Columns != boardSize.Rows)
        return false;

      if (boardSize.Columns > SgfcConstants::BoardSizeMaximumGo.Columns ||
          boardSize.Rows > SgfcConstants::BoardSizeMaximumGo.Rows)
      {
        return false;
      }
    }

    return true;
  }
}
