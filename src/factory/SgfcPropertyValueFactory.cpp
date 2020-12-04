// -----------------------------------------------------------------------------
// Copyright 2020 Patrick Näf (herzbube@herzbube.ch)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -----------------------------------------------------------------------------

// Project includes
#include "../../include/SgfcConstants.h"
#include "../document/typedpropertyvalue/SgfcColorPropertyValue.h"
#include "../document/typedpropertyvalue/SgfcDoublePropertyValue.h"
#include "../document/typedpropertyvalue/SgfcMovePropertyValue.h"
#include "../document/typedpropertyvalue/SgfcNumberPropertyValue.h"
#include "../document/typedpropertyvalue/SgfcPointPropertyValue.h"
#include "../document/typedpropertyvalue/SgfcRealPropertyValue.h"
#include "../document/typedpropertyvalue/SgfcSimpleTextPropertyValue.h"
#include "../document/typedpropertyvalue/SgfcStonePropertyValue.h"
#include "../document/typedpropertyvalue/SgfcTextPropertyValue.h"
#include "../document/typedpropertyvalue/go/SgfcGoMovePropertyValue.h"
#include "../document/typedpropertyvalue/go/SgfcGoPointPropertyValue.h"
#include "../document/typedpropertyvalue/go/SgfcGoStonePropertyValue.h"
#include "../document/SgfcComposedPropertyValue.h"
#include "../game/go/SgfcGoMove.h"
#include "../game/go/SgfcGoPoint.h"
#include "../game/go/SgfcGoStone.h"
#include "SgfcPropertyValueFactory.h"

// C++ Standard Library includes
#include <sstream>

namespace LibSgfcPlusPlus
{
  SgfcPropertyValueFactory::SgfcPropertyValueFactory()
  {
  }

  SgfcPropertyValueFactory::~SgfcPropertyValueFactory()
  {
  }

  std::shared_ptr<ISgfcNumberPropertyValue> SgfcPropertyValueFactory::CreateNumberPropertyValue(
    SgfcNumber numberValue) const
  {
    std::stringstream stream;
    stream << numberValue;

    std::shared_ptr<ISgfcNumberPropertyValue> valueObject = std::shared_ptr<ISgfcNumberPropertyValue>(
      new SgfcNumberPropertyValue(stream.str(), numberValue));
    return valueObject;
  }

  std::shared_ptr<ISgfcRealPropertyValue> SgfcPropertyValueFactory::CreateRealPropertyValue(
    SgfcReal realValue) const
  {
    std::stringstream stream;
    // Make sure that decimal point is always a period (".") character and that
    // there are no thousands separators
    stream.imbue(std::locale::classic());
    stream << realValue;

    std::shared_ptr<ISgfcRealPropertyValue> valueObject = std::shared_ptr<ISgfcRealPropertyValue>(
      new SgfcRealPropertyValue(stream.str(), realValue));
    return valueObject;
  }

  std::shared_ptr<ISgfcDoublePropertyValue> SgfcPropertyValueFactory::CreateDoublePropertyValue(
    SgfcDouble doubleValue) const
  {
    std::string stringValue;
    if (doubleValue == SgfcDouble::Normal)
      stringValue = SgfcConstants::DoubleNormalString;
    else
      stringValue = SgfcConstants::DoubleEmphasizedString;

    std::shared_ptr<ISgfcDoublePropertyValue> valueObject = std::shared_ptr<ISgfcDoublePropertyValue>(
      new SgfcDoublePropertyValue(stringValue, doubleValue));
    return valueObject;
  }

  std::shared_ptr<ISgfcColorPropertyValue> SgfcPropertyValueFactory::CreateColorPropertyValue(
    SgfcColor colorValue) const
  {
    std::string stringValue;
    if (colorValue == SgfcColor::Black)
      stringValue = SgfcConstants::ColorBlackString;
    else
      stringValue = SgfcConstants::ColorWhiteString;

    std::shared_ptr<ISgfcColorPropertyValue> valueObject = std::shared_ptr<ISgfcColorPropertyValue>(
      new SgfcColorPropertyValue(stringValue, colorValue));
    return valueObject;
  }

  std::shared_ptr<ISgfcSimpleTextPropertyValue> SgfcPropertyValueFactory::CreateSimpleTextPropertyValue(
    const SgfcSimpleText& simpleTextValue) const
  {
    std::shared_ptr<ISgfcSimpleTextPropertyValue> valueObject = std::shared_ptr<ISgfcSimpleTextPropertyValue>(
      new SgfcSimpleTextPropertyValue(simpleTextValue, simpleTextValue));
    return valueObject;
  }

  std::shared_ptr<ISgfcTextPropertyValue> SgfcPropertyValueFactory::CreateTextPropertyValue(
    const SgfcText& textValue) const
  {
    std::shared_ptr<ISgfcTextPropertyValue> valueObject = std::shared_ptr<ISgfcTextPropertyValue>(
      new SgfcTextPropertyValue(textValue, textValue));
    return valueObject;
  }

  std::shared_ptr<ISgfcPointPropertyValue> SgfcPropertyValueFactory::CreatePointPropertyValue(
    const SgfcPoint& pointValue) const
  {
    std::shared_ptr<ISgfcPointPropertyValue> valueObject = std::shared_ptr<ISgfcPointPropertyValue>(
      new SgfcPointPropertyValue(pointValue, pointValue));
    return valueObject;
  }

  std::shared_ptr<ISgfcMovePropertyValue> SgfcPropertyValueFactory::CreateMovePropertyValue(
    const SgfcMove& moveValue) const
  {
    std::shared_ptr<ISgfcMovePropertyValue> valueObject = std::shared_ptr<ISgfcMovePropertyValue>(
      new SgfcMovePropertyValue(moveValue, moveValue));
    return valueObject;
  }

  std::shared_ptr<ISgfcStonePropertyValue> SgfcPropertyValueFactory::CreateStonePropertyValue(
    const SgfcStone& stoneValue) const
  {
    std::shared_ptr<ISgfcStonePropertyValue> valueObject = std::shared_ptr<ISgfcStonePropertyValue>(
      new SgfcStonePropertyValue(stoneValue, stoneValue));
    return valueObject;
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyValueFactory::CreateCustomPropertyValue(
    const std::string& value) const
  {
    std::shared_ptr<ISgfcSinglePropertyValue> valueObject = std::shared_ptr<ISgfcSinglePropertyValue>(
      new SgfcSinglePropertyValue(value));
    return valueObject;
  }

  std::shared_ptr<ISgfcGoPointPropertyValue> SgfcPropertyValueFactory::CreateGoPointPropertyValue(
    const SgfcPoint& pointValue,
    SgfcBoardSize boardSize) const
  {
    std::shared_ptr<ISgfcGoPoint> goPointObject = std::shared_ptr<ISgfcGoPoint>(new SgfcGoPoint(
      pointValue,
      boardSize));
    std::shared_ptr<ISgfcGoPointPropertyValue> valueObject = std::shared_ptr<ISgfcGoPointPropertyValue>(
      new SgfcGoPointPropertyValue(goPointObject));
    return valueObject;
  }

  std::shared_ptr<ISgfcGoMovePropertyValue> SgfcPropertyValueFactory::CreateGoMovePropertyValue(
    const SgfcMove& moveValue,
    SgfcBoardSize boardSize,
    SgfcColor color) const
  {
    std::shared_ptr<ISgfcGoMove> goMoveObject = std::shared_ptr<ISgfcGoMove>(
      new SgfcGoMove(
        std::shared_ptr<ISgfcGoStone>(new SgfcGoStone(
          color,
          std::shared_ptr<ISgfcGoPoint>(new SgfcGoPoint(
            moveValue,
            boardSize))))));
    std::shared_ptr<ISgfcGoMovePropertyValue> valueObject = std::shared_ptr<ISgfcGoMovePropertyValue>(
      new SgfcGoMovePropertyValue(goMoveObject));
    return valueObject;
  }

  std::shared_ptr<ISgfcGoMovePropertyValue> SgfcPropertyValueFactory::CreateGoMovePropertyValue(
    SgfcColor color) const
  {
    std::shared_ptr<ISgfcGoMove> goMoveObject = std::shared_ptr<ISgfcGoMove>(
      new SgfcGoMove(color));
    std::shared_ptr<ISgfcGoMovePropertyValue> valueObject = std::shared_ptr<ISgfcGoMovePropertyValue>(
      new SgfcGoMovePropertyValue(goMoveObject));
    return valueObject;
  }

  std::shared_ptr<ISgfcGoStonePropertyValue> SgfcPropertyValueFactory::CreateGoStonePropertyValue(
    const SgfcStone& stoneValue,
    SgfcBoardSize boardSize,
    SgfcColor color) const
  {
    std::shared_ptr<ISgfcGoStone> goStoneObject = std::shared_ptr<ISgfcGoStone>(
      new SgfcGoStone(
        color,
        std::shared_ptr<ISgfcGoPoint>(new SgfcGoPoint(
          stoneValue,
          boardSize))));
    std::shared_ptr<ISgfcGoStonePropertyValue> valueObject = std::shared_ptr<ISgfcGoStonePropertyValue>(
      new SgfcGoStonePropertyValue(goStoneObject));
    return valueObject;
  }

  std::shared_ptr<ISgfcComposedPropertyValue> SgfcPropertyValueFactory::CreateComposedNumberAndNumberPropertyValue(
    SgfcNumber numberValue1,
    SgfcNumber numberValue2) const
  {
    std::shared_ptr<ISgfcNumberPropertyValue> valueObject1 = CreateNumberPropertyValue(numberValue1);
    std::shared_ptr<ISgfcNumberPropertyValue> valueObject2 = CreateNumberPropertyValue(numberValue2);

    std::shared_ptr<ISgfcComposedPropertyValue> valueObject = std::shared_ptr<ISgfcComposedPropertyValue>(
      new SgfcComposedPropertyValue(valueObject1, valueObject2));
    return valueObject;
  }

  std::shared_ptr<ISgfcComposedPropertyValue> SgfcPropertyValueFactory::CreateComposedSimpleTextAndSimpleTextPropertyValue(
    const SgfcSimpleText& simpleTextValue1,
    const SgfcSimpleText& simpleTextValue2) const
  {
    std::shared_ptr<ISgfcSimpleTextPropertyValue> valueObject1 = CreateSimpleTextPropertyValue(simpleTextValue1);
    std::shared_ptr<ISgfcSimpleTextPropertyValue> valueObject2 = CreateSimpleTextPropertyValue(simpleTextValue2);

    std::shared_ptr<ISgfcComposedPropertyValue> valueObject = std::shared_ptr<ISgfcComposedPropertyValue>(
      new SgfcComposedPropertyValue(valueObject1, valueObject2));
    return valueObject;
  }

  std::shared_ptr<ISgfcComposedPropertyValue> SgfcPropertyValueFactory::CreateComposedNumberAndSimpleTextPropertyValue(
    SgfcNumber numberValue,
    const SgfcSimpleText& simpleTextValue) const
  {
    std::shared_ptr<ISgfcNumberPropertyValue> valueObject1 = CreateNumberPropertyValue(numberValue);
    std::shared_ptr<ISgfcSimpleTextPropertyValue> valueObject2 = CreateSimpleTextPropertyValue(simpleTextValue);

    std::shared_ptr<ISgfcComposedPropertyValue> valueObject = std::shared_ptr<ISgfcComposedPropertyValue>(
      new SgfcComposedPropertyValue(valueObject1, valueObject2));
    return valueObject;
  }

  std::shared_ptr<ISgfcComposedPropertyValue> SgfcPropertyValueFactory::CreateComposedPointAndPointPropertyValue(
    const SgfcPoint& pointValue1,
    const SgfcPoint& pointValue2) const
  {
    std::shared_ptr<ISgfcPointPropertyValue> valueObject1 = CreatePointPropertyValue(pointValue1);
    std::shared_ptr<ISgfcPointPropertyValue> valueObject2 = CreatePointPropertyValue(pointValue2);

    std::shared_ptr<ISgfcComposedPropertyValue> valueObject = std::shared_ptr<ISgfcComposedPropertyValue>(
      new SgfcComposedPropertyValue(valueObject1, valueObject2));
    return valueObject;
  }

  std::shared_ptr<ISgfcComposedPropertyValue> SgfcPropertyValueFactory::CreateComposedPointAndSimpleTextPropertyValue(
    const SgfcPoint& pointValue,
    const SgfcSimpleText& simpleTextValue) const
  {
    std::shared_ptr<ISgfcPointPropertyValue> valueObject1 = CreatePointPropertyValue(pointValue);
    std::shared_ptr<ISgfcSimpleTextPropertyValue> valueObject2 = CreateSimpleTextPropertyValue(simpleTextValue);

    std::shared_ptr<ISgfcComposedPropertyValue> valueObject = std::shared_ptr<ISgfcComposedPropertyValue>(
      new SgfcComposedPropertyValue(valueObject1, valueObject2));
    return valueObject;
  }

  std::shared_ptr<ISgfcComposedPropertyValue> SgfcPropertyValueFactory::CreateComposedStoneAndPointPropertyValue(
    const SgfcStone& stoneValue,
    const SgfcPoint& pointValue) const
  {
    std::shared_ptr<ISgfcStonePropertyValue> valueObject1 = CreateStonePropertyValue(stoneValue);
    std::shared_ptr<ISgfcPointPropertyValue> valueObject2 = CreatePointPropertyValue(pointValue);

    std::shared_ptr<ISgfcComposedPropertyValue> valueObject = std::shared_ptr<ISgfcComposedPropertyValue>(
      new SgfcComposedPropertyValue(valueObject1, valueObject2));
    return valueObject;
  }

  std::shared_ptr<ISgfcComposedPropertyValue> SgfcPropertyValueFactory::CreateCustomComposedPropertyValue(
    std::shared_ptr<ISgfcSinglePropertyValue> valueObject1,
    std::shared_ptr<ISgfcSinglePropertyValue> valueObject2) const
  {
    std::shared_ptr<ISgfcComposedPropertyValue> valueObject = std::shared_ptr<ISgfcComposedPropertyValue>(
      new SgfcComposedPropertyValue(valueObject1, valueObject2));
    return valueObject;
  }

  std::shared_ptr<ISgfcComposedPropertyValue> SgfcPropertyValueFactory::CreateComposedGoPointAndGoPointPropertyValue(
    const SgfcPoint& pointValue1,
    const SgfcPoint& pointValue2,
    SgfcBoardSize boardSize) const
  {
    std::shared_ptr<ISgfcGoPointPropertyValue> valueObject1 = CreateGoPointPropertyValue(pointValue1, boardSize);
    std::shared_ptr<ISgfcGoPointPropertyValue> valueObject2 = CreateGoPointPropertyValue(pointValue2, boardSize);

    std::shared_ptr<ISgfcComposedPropertyValue> valueObject = std::shared_ptr<ISgfcComposedPropertyValue>(
      new SgfcComposedPropertyValue(valueObject1, valueObject2));
    return valueObject;
  }

  std::shared_ptr<ISgfcComposedPropertyValue> SgfcPropertyValueFactory::CreateComposedGoPointAndSimpleTextPropertyValue(
    const SgfcPoint& pointValue,
    SgfcBoardSize boardSize,
    const SgfcSimpleText& simpleTextValue) const
  {
    std::shared_ptr<ISgfcGoPointPropertyValue> valueObject1 = CreateGoPointPropertyValue(pointValue, boardSize);
    std::shared_ptr<ISgfcSimpleTextPropertyValue> valueObject2 = CreateSimpleTextPropertyValue(simpleTextValue);

    std::shared_ptr<ISgfcComposedPropertyValue> valueObject = std::shared_ptr<ISgfcComposedPropertyValue>(
      new SgfcComposedPropertyValue(valueObject1, valueObject2));
    return valueObject;
  }

  std::shared_ptr<ISgfcComposedPropertyValue> SgfcPropertyValueFactory::CreateComposedGoStoneAndPointPropertyValue(
    const SgfcStone& stoneValue,
    SgfcColor color,
    const SgfcPoint& pointValue,
    SgfcBoardSize boardSize) const
  {
    std::shared_ptr<ISgfcGoStonePropertyValue> valueObject1 = CreateGoStonePropertyValue(stoneValue, boardSize, color);
    std::shared_ptr<ISgfcGoPointPropertyValue> valueObject2 = CreateGoPointPropertyValue(pointValue, boardSize);

    std::shared_ptr<ISgfcComposedPropertyValue> valueObject = std::shared_ptr<ISgfcComposedPropertyValue>(
      new SgfcComposedPropertyValue(valueObject1, valueObject2));
    return valueObject;
  }
}
