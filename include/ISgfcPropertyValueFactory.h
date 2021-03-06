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
#include "SgfcBoardSize.h"
#include "SgfcColor.h"
#include "SgfcDouble.h"
#include "SgfcGameType.h"
#include "SgfcTypedefs.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>
#include <string>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcColorPropertyValue;
  class ISgfcComposedPropertyValue;
  class ISgfcDoublePropertyValue;
  class ISgfcGoMovePropertyValue;
  class ISgfcGoPointPropertyValue;
  class ISgfcGoStonePropertyValue;
  class ISgfcMovePropertyValue;
  class ISgfcNumberPropertyValue;
  class ISgfcPointPropertyValue;
  class ISgfcPropertyValue;
  class ISgfcRealPropertyValue;
  class ISgfcSimpleTextPropertyValue;
  class ISgfcSinglePropertyValue;
  class ISgfcStonePropertyValue;
  class ISgfcTextPropertyValue;

  /// @brief The ISgfcPropertyValueFactory interface provides factory methods
  /// for creating ISgfcPropertyValue objects, and objects of every known
  /// sub-type of ISgfcPropertyValue.
  ///
  /// @ingroup public-api
  /// @ingroup factory
  /// @ingroup property-value
  class SGFCPLUSPLUS_EXPORT ISgfcPropertyValueFactory
  {
  public:
    /// @brief Initializes a newly constructed ISgfcPropertyValueFactory object.
    ISgfcPropertyValueFactory();

    /// @brief Destroys and cleans up the ISgfcPropertyValueFactory object.
    virtual ~ISgfcPropertyValueFactory();

    /// @name Single property values - Basic value types
    //@{
    /// @brief Returns a newly constructed ISgfcNumberPropertyValue object
    /// that has the SgfcNumber value @a numberValue.
    virtual std::shared_ptr<ISgfcNumberPropertyValue> CreateNumberPropertyValue(
      SgfcNumber numberValue) const = 0;

    /// @brief Returns a newly constructed ISgfcRealPropertyValue object
    /// that has the SgfcReal value @a realValue.
    virtual std::shared_ptr<ISgfcRealPropertyValue> CreateRealPropertyValue(
      SgfcReal realValue) const = 0;

    /// @brief Returns a newly constructed ISgfcDoublePropertyValue object
    /// that has the SgfcDouble value @a doubleValue.
    virtual std::shared_ptr<ISgfcDoublePropertyValue> CreateDoublePropertyValue(
      SgfcDouble doubleValue) const = 0;

    /// @brief Returns a newly constructed ISgfcColorPropertyValue object
    /// that has the SgfcColor value @a colorValue.
    virtual std::shared_ptr<ISgfcColorPropertyValue> CreateColorPropertyValue(
      SgfcColor colorValue) const = 0;

    /// @brief Returns a newly constructed ISgfcSimpleTextPropertyValue object
    /// that has the SgfcSimpleText value @a simpleTextValue.
    virtual std::shared_ptr<ISgfcSimpleTextPropertyValue> CreateSimpleTextPropertyValue(
      const SgfcSimpleText& simpleTextValue) const = 0;

    /// @brief Returns a newly constructed ISgfcTextPropertyValue object
    /// that has the SgfcText value @a textValue.
    virtual std::shared_ptr<ISgfcTextPropertyValue> CreateTextPropertyValue(
      const SgfcText& textValue) const = 0;

    /// @brief Returns a newly constructed ISgfcPointPropertyValue object
    /// that has the SgfcPoint value @a pointValue.
    virtual std::shared_ptr<ISgfcPointPropertyValue> CreatePointPropertyValue(
      const SgfcPoint& pointValue) const = 0;

    /// @brief Returns a newly constructed ISgfcMovePropertyValue object
    /// that has the SgfcMove value @a moveValue.
    virtual std::shared_ptr<ISgfcMovePropertyValue> CreateMovePropertyValue(
      const SgfcMove& moveValue) const = 0;

    /// @brief Returns a newly constructed ISgfcStonePropertyValue object
    /// that has the SgfcStone value @a stoneValue.
    virtual std::shared_ptr<ISgfcStonePropertyValue> CreateStonePropertyValue(
      const SgfcStone& stoneValue) const = 0;

    /// @brief Returns a newly constructed ISgfcSinglePropertyValue object
    /// that has the string value @a value. The object has value type
    /// SgfcPropertyValueType::Unknown.
    virtual std::shared_ptr<ISgfcSinglePropertyValue> CreateCustomPropertyValue(
      const std::string& value) const = 0;
    //@}

    /// @name Single property values - Special value types
    //@{
    /// @brief Returns a newly constructed ISgfcNumberPropertyValue object
    /// that has an SgfcNumber value that corresponds to @a gameType.
    /// @a gameType must not be #SgfcGameType::Unknown.
    ///
    /// @exception std::invalid_argument Is thrown if @a gameType is
    /// #SgfcGameType::Unknown.
    virtual std::shared_ptr<ISgfcNumberPropertyValue> CreateGameTypePropertyValue(
      SgfcGameType gameType) const = 0;

    /// @brief Returns a newly constructed ISgfcPropertyValue object that has
    /// a value that corresponds to @a boardSize. @a boardSize must be valid.
    /// @a gameType must be provided for validating @a boardSize. @a gameType
    /// must not be #SgfcGameType::Unknown.
    ///
    /// The returned ISgfcPropertyValue object is an ISgfcNumberPropertyValue
    /// object if SgfcBoardSize::IsSquare() returns true for @a boardSize.
    ///
    /// The returned ISgfcPropertyValue object is an ISgfcComposedPropertyValue
    /// object consisting of two ISgfcNumberPropertyValue objects if
    /// SgfcBoardSize::IsSquare() returns false for @a boardSize.
    ///
    /// @exception std::invalid_argument Is thrown if @a gameType is
    /// #SgfcGameType::Unknown, or if @a boardSize is not valid, i.e. if it's
    /// IsValid() method returns false.
    virtual std::shared_ptr<ISgfcPropertyValue> CreateBoardSizePropertyValue(
      SgfcBoardSize boardSize,
      SgfcGameType gameType) const = 0;
    //@}

    /// @name Single property values - Go game value types
    //@{
    /// @brief Returns a newly constructed ISgfcGoPointPropertyValue object
    /// that has the SgfcPoint value @a pointValue. @a boardSize indicates the
    /// size of the Go board that the Go point is located on.
    ///
    /// @a pointValue can be given in any one of the notations enumerated in
    /// SgfcGoPointNotation.
    ///
    /// Regardless of the notation in which @a pointValue is given, the
    /// resulting ISgfcGoPointPropertyValue object uses the SGF notation as
    /// the raw property value.
    ///
    /// @exception std::invalid_argument Is thrown if @a boardSize refers to
    /// a board with size smaller than the minimum required by the SGF standard
    /// (SgfcConstants::BoardSizeMinimum), or a board with size larger than the
    /// maximum allowed by the SGF standard (SgfcConstants::BoardSizeMaximumGo).
    /// Is also thrown if @a pointValue is not given in one of the notations
    /// enumerated in SgfcGoPointNotation, or if @a pointValue violates one of
    /// the restrictions imposed by the used notation (e.g. y-axis compound
    /// larger than 25 when #SgfcGoPointNotation::Hybrid is used), or if
    /// @a pointValue refers to an invalid location on the board (e.g. an x-axis
    /// or y-axis location that exceeds the board size specified by
    /// @a boardSize, or a compound < 1 when #SgfcGoPointNotation::Figure is
    /// used).
    virtual std::shared_ptr<ISgfcGoPointPropertyValue> CreateGoPointPropertyValue(
      const SgfcPoint& pointValue,
      SgfcBoardSize boardSize) const = 0;

    /// @brief Returns a newly constructed ISgfcGoMovePropertyValue object
    /// that has the SgfcMove value @a moveValue. @a color is the color of the
    /// player who made the move. The move is not a pass move. @a boardSize
    /// indicates the size of the Go board that the Go move is played on.
    ///
    /// @a moveValue refers to the location (a Go point) of the stone that is
    /// placed by the move on the board. @a moveValue can be given in any one of
    /// the notations enumerated in SgfcGoPointNotation.
    ///
    /// Regardless of the notation in which @a moveValue is given, the
    /// resulting ISgfcGoMovePropertyValue object uses the SGF notation as
    /// the raw property value.
    ///
    /// @exception std::invalid_argument Is thrown if @a boardSize refers to
    /// a board with size smaller than the minimum required by the SGF standard
    /// (SgfcConstants::BoardSizeMinimum), or a board with size larger than the
    /// maximum allowed by the SGF standard (SgfcConstants::BoardSizeMaximumGo).
    /// Is also thrown if @a moveValue is not given in one of the notations
    /// enumerated in SgfcGoPointNotation, or if @a moveValue violates one of
    /// the restrictions imposed by the used notation (e.g. y-axis compound
    /// larger than 25 when #SgfcGoPointNotation::Hybrid is used), or if
    /// @a moveValue refers to an invalid location on the board (e.g. an x-axis
    /// or y-axis location that exceeds the board size specified by
    /// @a boardSize, or a compound < 1 when #SgfcGoPointNotation::Figure is
    /// used).
    virtual std::shared_ptr<ISgfcGoMovePropertyValue> CreateGoMovePropertyValue(
      const SgfcMove& moveValue,
      SgfcBoardSize boardSize,
      SgfcColor color) const = 0;

    /// @brief Returns a newly constructed ISgfcGoMovePropertyValue object
    /// that has no value. @a color is the color of the player who made the
    /// move. The move is a pass move.
    ///
    /// The resulting ISgfcGoMovePropertyValue object uses
    /// SgfcConstants::GoMovePassString as the raw property value.
    virtual std::shared_ptr<ISgfcGoMovePropertyValue> CreateGoMovePropertyValue(
      SgfcColor color) const = 0;

    /// @brief Returns a newly constructed ISgfcGoStonePropertyValue object
    /// that has the SgfcStone value @a stoneValue. @a color is the color of the
    /// stone. @a boardSize indicates the size of the Go board that the Go
    /// stone is located on.
    ///
    /// @a stoneValue refers to the Go point on which the stone is located.
    /// @a stoneValue can be given in any one of the notations enumerated in
    /// SgfcGoPointNotation.
    ///
    /// Regardless of the notation in which @a stoneValue is given, the
    /// resulting ISgfcGoStonePropertyValue object uses the SGF notation as
    /// the raw property value.
    ///
    /// @exception std::invalid_argument Is thrown if @a boardSize refers to
    /// a board with size smaller than the minimum required by the SGF standard
    /// (SgfcConstants::BoardSizeMinimum), or a board with size larger than the
    /// maximum allowed by the SGF standard (SgfcConstants::BoardSizeMaximumGo).
    /// Is also thrown if @a stoneValue is not given in one of the notations
    /// enumerated in SgfcGoPointNotation, or if @a stoneValue violates one of
    /// the restrictions imposed by the used notation (e.g. y-axis compound
    /// larger than 25 when #SgfcGoPointNotation::Hybrid is used), or if
    /// @a stoneValue refers to an invalid location on the board (e.g. an x-axis
    /// or y-axis location that exceeds the board size specified by
    /// @a boardSize, or a compound < 1 when #SgfcGoPointNotation::Figure is
    /// used).
    virtual std::shared_ptr<ISgfcGoStonePropertyValue> CreateGoStonePropertyValue(
      const SgfcStone& stoneValue,
      SgfcBoardSize boardSize,
      SgfcColor color) const = 0;
    //@}

    /// @name Composed property values - Basic value types
    //@{
    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of two ISgfcNumberPropertyValue objects, which have
    /// the SgfcNumber values @a numberValue1 and @a numberValue2.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedNumberAndNumberPropertyValue(
      SgfcNumber numberValue1,
      SgfcNumber numberValue2) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of two ISgfcSimpleTextPropertyValue objects, which have
    /// the SgfcSimpleText values @a simpleTextValue1 and @a simpleTextValue2.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedSimpleTextAndSimpleTextPropertyValue(
      const SgfcSimpleText& simpleTextValue1,
      const SgfcSimpleText& simpleTextValue2) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of an ISgfcNumberPropertyValue object and an
    /// ISgfcSimpleTextPropertyValue object, which have the SgfcNumber and
    /// SgfcSimpleText values @a numberValue and @a simpleTextValue,
    /// respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedNumberAndSimpleTextPropertyValue(
      SgfcNumber numberValue,
      const SgfcSimpleText& simpleTextValue) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of two ISgfcPointPropertyValue objects, which have the
    /// SgfcPoint values @a pointValue1 and @a pointValue2, respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedPointAndPointPropertyValue(
      const SgfcPoint& pointValue1,
      const SgfcPoint& pointValue2) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of an ISgfcPointPropertyValue object and an
    /// ISgfcSimpleTextPropertyValue object, which have the SgfcPoint and
    /// SgfcSimpleText values @a pointValue and @a simpleTextValue,
    /// respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedPointAndSimpleTextPropertyValue(
      const SgfcPoint& pointValue,
      const SgfcSimpleText& simpleTextValue) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of an ISgfcStonePropertyValue object and an
    /// ISgfcPointPropertyValue object, which have the SgfcStone and SgfcPoint
    /// values @a stoneValue and @a pointValue, respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedStoneAndPointPropertyValue(
      const SgfcStone& stoneValue,
      const SgfcPoint& pointValue) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of two ISgfcSinglePropertyValue objects @a valueObject1
    /// and @a valueObject2.
    ///
    /// @exception std::invalid_argument Is thrown if @a value1 is @e nullptr
    /// or if @a value2 is @e nullptr.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateCustomComposedPropertyValue(
      std::shared_ptr<ISgfcSinglePropertyValue> valueObject1,
      std::shared_ptr<ISgfcSinglePropertyValue> valueObject2) const = 0;
    //@}

    /// @name Composed property values - Go game value types
    //@{
    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of two ISgfcGoPointPropertyValue objects, which have the
    /// SgfcPoint values @a pointValue1 and @a pointValue2, respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedGoPointAndGoPointPropertyValue(
      const SgfcPoint& pointValue1,
      const SgfcPoint& pointValue2,
      SgfcBoardSize boardSize) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of an ISgfcGoPointPropertyValue object and an
    /// ISgfcSimpleTextPropertyValue object, which have the SgfcPoint and
    /// SgfcSimpleText values @a pointValue and @a simpleTextValue,
    /// respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedGoPointAndSimpleTextPropertyValue(
      const SgfcPoint& pointValue,
      SgfcBoardSize boardSize,
      const SgfcSimpleText& simpleTextValue) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of an ISgfcGoStonePropertyValue object and an
    /// ISgfcGoPointPropertyValue object, which have the SgfcStone and SgfcPoint
    /// values @a stoneValue and @a pointValue, respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedGoStoneAndPointPropertyValue(
      const SgfcStone& stoneValue,
      SgfcColor color,
      const SgfcPoint& pointValue,
      SgfcBoardSize boardSize) const = 0;
    //@}
  };
}
