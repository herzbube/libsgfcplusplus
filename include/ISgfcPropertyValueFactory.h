#pragma once

// Project includes
#include "SgfcBoardSize.h"
#include "SgfcColor.h"
#include "SgfcDouble.h"
#include "SgfcTypedefs.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

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
  class ISgfcRealPropertyValue;
  class ISgfcSimpleTextPropertyValue;
  class ISgfcSinglePropertyValue;
  class ISgfcStonePropertyValue;
  class ISgfcTextPropertyValue;

  /// @brief The ISgfcPropertyValueFactory interface provides factory methods
  /// for creating ISgfcPropertyValue objects, and objects of every known
  /// sub-type of ISgfcPropertyValue.
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
    /// that has the string value @a simpleTextValue.
    virtual std::shared_ptr<ISgfcSimpleTextPropertyValue> CreateSimpleTextPropertyValue(
      const std::string& simpleTextValue) const = 0;

    /// @brief Returns a newly constructed ISgfcTextPropertyValue object
    /// that has the string value @a textValue.
    virtual std::shared_ptr<ISgfcTextPropertyValue> CreateTextPropertyValue(
      const std::string& textValue) const = 0;

    /// @brief Returns a newly constructed ISgfcPointPropertyValue object
    /// that has the string value @a pointValue.
    virtual std::shared_ptr<ISgfcPointPropertyValue> CreatePointPropertyValue(
      const std::string& pointValue) const = 0;

    /// @brief Returns a newly constructed ISgfcMovePropertyValue object
    /// that has the string value @a moveValue.
    virtual std::shared_ptr<ISgfcMovePropertyValue> CreateMovePropertyValue(
      const std::string& moveValue) const = 0;

    /// @brief Returns a newly constructed ISgfcStonePropertyValue object
    /// that has the string value @a stoneValue.
    virtual std::shared_ptr<ISgfcStonePropertyValue> CreateStonePropertyValue(
      const std::string& stoneValue) const = 0;

    /// @brief Returns a newly constructed ISgfcSinglePropertyValue object
    /// that has the string value @a value. The object has value type
    /// SgfcPropertyValueType::Unknown.
    virtual std::shared_ptr<ISgfcSinglePropertyValue> CreateCustomPropertyValue(
      const std::string& value) const = 0;
    //@}

    /// @name Single property values - Go game value types
    //@{
    /// @brief Returns a newly constructed ISgfcGoPointPropertyValue object
    /// that has the string value @a pointValue. @a boardSize indicates the size
    /// of the Go board that the Go point is located on.
    ///
    /// @a pointValue can be given in any one of the notations enumerated in
    /// SgfcGoPointNotation.
    ///
    /// @exception std::invalid_argument Is thrown if @a boardSize refers to
    /// a board that is not square, a board with size smaller than the minimum
    /// required by the SGF standard (#SgfcConstants::BoardSizeMinimum), or a
    /// board with size larger than the maximum allowed by the SGF standard
    /// (#SgfcConstants::BoardSizeMaximumGo). Is also thrown if @a pointValue is
    /// not given in one of the notations enumerated in SgfcGoPointNotation, or
    /// if @a pointValue violates one of the restrictions imposed by the used
    /// notation (e.g. y-axis compound larger than 25 when
    /// #SgfcGoPointNotation::Hybrid is used), or if @a pointValue refers to an
    /// invalid location on the board (e.g. an x-axis or y-axis location that
    /// exceeds the board size specified by @a boardSize, or a compound < 1 when
    /// #SgfcGoPointNotation::Figure is used).
    virtual std::shared_ptr<ISgfcGoPointPropertyValue> CreateGoPointPropertyValue(
      const std::string& pointValue,
      SgfcBoardSize boardSize) const = 0;

    /// @brief Returns a newly constructed ISgfcGoMovePropertyValue object
    /// that has the string value @a moveValue. @a color is the color of the
    /// player who made the move. The move is not a pass move. @a boardSize
    /// indicates the size of the Go board that the Go move is played on.
    ///
    /// @a moveValue refers to the location (a Go point) of the stone that is
    /// placed by the move on the board. @a moveValue can be given in any one of
    /// the notations enumerated in SgfcGoPointNotation.
    ///
    /// @exception std::invalid_argument Is thrown if @a boardSize refers to
    /// a board that is not square, a board with size smaller than the minimum
    /// required by the SGF standard (#SgfcConstants::BoardSizeMinimum), or a
    /// board with size larger than the maximum allowed by the SGF standard
    /// (#SgfcConstants::BoardSizeMaximumGo). Is also thrown if @a moveValue is
    /// not given in one of the notations enumerated in SgfcGoPointNotation, or
    /// if @a moveValue violates one of the restrictions imposed by the used
    /// notation (e.g. y-axis compound larger than 25 when
    /// #SgfcGoPointNotation::Hybrid is used), or if @a moveValue refers to an
    /// invalid location on the board (e.g. an x-axis or y-axis location that
    /// exceeds the board size specified by @a boardSize, or a compound < 1 when
    /// #SgfcGoPointNotation::Figure is used).
    virtual std::shared_ptr<ISgfcGoMovePropertyValue> CreateGoMovePropertyValue(
      const std::string& moveValue,
      SgfcBoardSize boardSize,
      SgfcColor color) const = 0;

    /// @brief Returns a newly constructed ISgfcGoMovePropertyValue object
    /// that has no value. @a color is the color of the player who made the
    /// move. The move is a pass move.
    virtual std::shared_ptr<ISgfcGoMovePropertyValue> CreateGoMovePropertyValue(
      SgfcColor color) const = 0;

    /// @brief Returns a newly constructed ISgfcGoStonePropertyValue object
    /// that has the string value @a stoneValue.
    virtual std::shared_ptr<ISgfcGoStonePropertyValue> CreateGoStonePropertyValue(
      const std::string& stoneValue,
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
    /// the string values @a simpleTextValue1 and @a simpleTextValue2.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedSimpleTextAndSimpleTextPropertyValue(
      const std::string& simpleTextValue1,
      const std::string& simpleTextValue2) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of an ISgfcNumberPropertyValue object and an
    /// ISgfcSimpleTextPropertyValue object, which have the SgfcNumber and
    /// string values @a numberValue and @a simpleTextValue, respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedNumberAndSimpleTextPropertyValue(
      SgfcNumber numberValue,
      const std::string& simpleTextValue) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of two ISgfcPointPropertyValue objects, which have the
    /// string values @a pointValue1 and @a pointValue2, respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedPointAndPointPropertyValue(
      const std::string& pointValue1,
      const std::string& pointValue2) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of an ISgfcPointPropertyValue object and an
    /// ISgfcSimpleTextPropertyValue object, which have the string values
    /// @a pointValue and @a simpleTextValue, respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedPointAndSimpleTextPropertyValue(
      const std::string& pointValue,
      const std::string& simpleTextValue) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of an ISgfcStonePropertyValue object and an
    /// ISgfcPointPropertyValue object, which have the string values
    /// @a stoneValue and @a pointValue, respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedStoneAndPointPropertyValue(
      const std::string& stoneValue,
      const std::string& pointValue) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of two ISgfcSinglePropertyValue objects @a valueObject1
    /// and @a valueObject2.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateCustomComposedPropertyValue(
      std::shared_ptr<ISgfcSinglePropertyValue> valueObject1,
      std::shared_ptr<ISgfcSinglePropertyValue> valueObject2) const = 0;
    //@}

    /// @name Composed property values - Go game value types
    //@{
    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of two ISgfcGoPointPropertyValue objects, which have the
    /// string values @a pointValue1 and @a pointValue2, respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedGoPointAndGoPointPropertyValue(
      const std::string& pointValue1,
      const std::string& pointValue2,
      SgfcBoardSize boardSize) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of an ISgfcGoPointPropertyValue object and an
    /// ISgfcSimpleTextPropertyValue object, which have the string values
    /// @a pointValue and @a simpleTextValue, respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedGoPointAndSimpleTextPropertyValue(
      const std::string& pointValue,
      SgfcBoardSize boardSize,
      const std::string& simpleTextValue) const = 0;

    /// @brief Returns a newly constructed ISgfcComposedPropertyValue object
    /// that consists of an ISgfcGoStonePropertyValue object and an
    /// ISgfcGoPointPropertyValue object, which have the string values
    /// @a stoneValue and @a pointValue, respectively.
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedGoStoneAndPointPropertyValue(
      const std::string& stoneValue,
      SgfcColor color,
      const std::string& pointValue,
      SgfcBoardSize boardSize) const = 0;
    //@}
  };
}
