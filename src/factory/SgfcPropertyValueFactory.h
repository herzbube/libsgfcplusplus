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

#pragma once

// Project includes
#include "../../include/ISgfcPropertyValueFactory.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyValueFactory class provides an implementation of
  /// the ISgfcPropertyValueFactory interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup factory
  class SgfcPropertyValueFactory : public ISgfcPropertyValueFactory
  {
  public:
    SgfcPropertyValueFactory();
    virtual ~SgfcPropertyValueFactory();

    /// @name Single property values - Basic value types
    //@{
    virtual std::shared_ptr<ISgfcNumberPropertyValue> CreateNumberPropertyValue(
      SgfcNumber numberValue) const override;
    virtual std::shared_ptr<ISgfcRealPropertyValue> CreateRealPropertyValue(
      SgfcReal realValue) const override;
    virtual std::shared_ptr<ISgfcDoublePropertyValue> CreateDoublePropertyValue(
      SgfcDouble doubleValue) const override;
    virtual std::shared_ptr<ISgfcColorPropertyValue> CreateColorPropertyValue(
      SgfcColor colorValue) const override;
    virtual std::shared_ptr<ISgfcSimpleTextPropertyValue> CreateSimpleTextPropertyValue(
      const SgfcSimpleText& simpleTextValue) const override;
    virtual std::shared_ptr<ISgfcTextPropertyValue> CreateTextPropertyValue(
      const SgfcText& textValue) const override;
    virtual std::shared_ptr<ISgfcPointPropertyValue> CreatePointPropertyValue(
      const SgfcPoint& pointValue) const override;
    virtual std::shared_ptr<ISgfcMovePropertyValue> CreateMovePropertyValue(
      const SgfcMove& moveValue) const override;
    virtual std::shared_ptr<ISgfcStonePropertyValue> CreateStonePropertyValue(
      const SgfcStone& stoneValue) const override;
    virtual std::shared_ptr<ISgfcSinglePropertyValue> CreateCustomPropertyValue(
      const std::string& value) const override;
    //@}

    /// @name Single property values - Special value types
    //@{
    virtual std::shared_ptr<ISgfcNumberPropertyValue> CreateGameTypePropertyValue(
      SgfcGameType gameType) const override;
    virtual std::shared_ptr<ISgfcPropertyValue> CreateBoardSizePropertyValue(
      SgfcBoardSize boardSize,
      SgfcGameType gameType) const override;
    //@}

    /// @name Single property values - Go game value types
    //@{
    virtual std::shared_ptr<ISgfcGoPointPropertyValue> CreateGoPointPropertyValue(
      const SgfcPoint& pointValue,
      SgfcBoardSize boardSize) const override;
    virtual std::shared_ptr<ISgfcGoMovePropertyValue> CreateGoMovePropertyValue(
      const SgfcMove& moveValue,
      SgfcBoardSize boardSize,
      SgfcColor color) const override;
    virtual std::shared_ptr<ISgfcGoMovePropertyValue> CreateGoMovePropertyValue(
      SgfcColor color) const override;
    virtual std::shared_ptr<ISgfcGoStonePropertyValue> CreateGoStonePropertyValue(
      const SgfcStone& stoneValue,
      SgfcBoardSize boardSize,
      SgfcColor color) const override;
    //@}

    /// @name Composed property values - Basic value types
    //@{
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedNumberAndNumberPropertyValue(
      SgfcNumber numberValue1,
      SgfcNumber numberValue2) const override;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedSimpleTextAndSimpleTextPropertyValue(
      const SgfcSimpleText& simpleTextValue1,
      const SgfcSimpleText& simpleTextValue2) const override;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedNumberAndSimpleTextPropertyValue(
      SgfcNumber numberValue,
      const SgfcSimpleText& simpleTextValue) const override;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedPointAndPointPropertyValue(
      const SgfcPoint& pointValue1,
      const SgfcPoint& pointValue2) const override;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedPointAndSimpleTextPropertyValue(
      const SgfcPoint& pointValue,
      const SgfcSimpleText& simpleTextValue) const override;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedStoneAndPointPropertyValue(
      const SgfcStone& stoneValue,
      const SgfcPoint& pointValue) const override;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateCustomComposedPropertyValue(
      std::shared_ptr<ISgfcSinglePropertyValue> valueObject1,
      std::shared_ptr<ISgfcSinglePropertyValue> valueObject2) const override;
    //@}

    /// @name Composed property values - Go game value types
    //@{
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedGoPointAndGoPointPropertyValue(
      const SgfcPoint& pointValue1,
      const SgfcPoint& pointValue2,
      SgfcBoardSize boardSize) const override;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedGoPointAndSimpleTextPropertyValue(
      const SgfcPoint& pointValue,
      SgfcBoardSize boardSize,
      const SgfcSimpleText& simpleTextValue) const override;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedGoStoneAndPointPropertyValue(
      const SgfcStone& stoneValue,
      SgfcColor color,
      const SgfcPoint& pointValue,
      SgfcBoardSize boardSize) const override;
    //@}
  };
}
