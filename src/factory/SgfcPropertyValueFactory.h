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
      SgfcNumber numberValue) const;
    virtual std::shared_ptr<ISgfcRealPropertyValue> CreateRealPropertyValue(
      SgfcReal realValue) const;
    virtual std::shared_ptr<ISgfcDoublePropertyValue> CreateDoublePropertyValue(
      SgfcDouble doubleValue) const;
    virtual std::shared_ptr<ISgfcColorPropertyValue> CreateColorPropertyValue(
      SgfcColor colorValue) const;
    virtual std::shared_ptr<ISgfcSimpleTextPropertyValue> CreateSimpleTextPropertyValue(
      const std::string& simpleTextValue) const;
    virtual std::shared_ptr<ISgfcTextPropertyValue> CreateTextPropertyValue(
      const std::string& textValue) const;
    virtual std::shared_ptr<ISgfcPointPropertyValue> CreatePointPropertyValue(
      const std::string& pointValue) const;
    virtual std::shared_ptr<ISgfcMovePropertyValue> CreateMovePropertyValue(
      const std::string& moveValue) const;
    virtual std::shared_ptr<ISgfcStonePropertyValue> CreateStonePropertyValue(
      const std::string& stoneValue) const;
    virtual std::shared_ptr<ISgfcSinglePropertyValue> CreateCustomPropertyValue(
      const std::string& value) const;
    //@}

    /// @name Single property values - Go game value types
    //@{
    virtual std::shared_ptr<ISgfcGoPointPropertyValue> CreateGoPointPropertyValue(
      const std::string& pointValue,
      SgfcBoardSize boardSize) const;
    virtual std::shared_ptr<ISgfcGoPointPropertyValue> CreateGoPointPropertyValue(
      const std::string& pointValue) const;
    virtual std::shared_ptr<ISgfcGoMovePropertyValue> CreateGoMovePropertyValue(
      const std::string& moveValue,
      SgfcBoardSize boardSize,
      SgfcColor color) const;
    virtual std::shared_ptr<ISgfcGoMovePropertyValue> CreateGoMovePropertyValue(
      const std::string& moveValue,
      SgfcColor color) const;
    virtual std::shared_ptr<ISgfcGoMovePropertyValue> CreateGoMovePropertyValue(
      SgfcColor color) const;
    virtual std::shared_ptr<ISgfcGoStonePropertyValue> CreateGoStonePropertyValue(
      const std::string& stoneValue,
      SgfcBoardSize boardSize,
      SgfcColor color) const;
    virtual std::shared_ptr<ISgfcGoStonePropertyValue> CreateGoStonePropertyValue(
      const std::string& stoneValue,
      SgfcColor color) const;
    //@}

    /// @name Composed property values - Basic value types
    //@{
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedNumberAndNumberPropertyValue(
      SgfcNumber numberValue1,
      SgfcNumber numberValue2) const;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedSimpleTextAndSimpleTextPropertyValue(
      const std::string& simpleTextValue1,
      const std::string& simpleTextValue2) const;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedNumberAndSimpleTextPropertyValue(
      SgfcNumber numberValue,
      const std::string& simpleTextValue) const;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedPointAndPointPropertyValue(
      const std::string& pointValue1,
      const std::string& pointValue2) const;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedPointAndSimpleTextPropertyValue(
      const std::string& pointValue,
      const std::string& simpleTextValue) const;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedStoneAndPointPropertyValue(
      const std::string& stoneValue,
      const std::string& pointValue) const;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateCustomComposedPropertyValue(
      std::shared_ptr<ISgfcSinglePropertyValue> valueObject1,
      std::shared_ptr<ISgfcSinglePropertyValue> valueObject2) const;
    //@}

    /// @name Composed property values - Go game value types
    //@{
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedGoPointAndGoPointPropertyValue(
      const std::string& pointValue1,
      const std::string& pointValue2,
      SgfcBoardSize boardSize) const;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedGoPointAndSimpleTextPropertyValue(
      const std::string& pointValue,
      SgfcBoardSize boardSize,
      const std::string& simpleTextValue) const;
    virtual std::shared_ptr<ISgfcComposedPropertyValue> CreateComposedGoStoneAndPointPropertyValue(
      const std::string& stoneValue,
      SgfcColor color,
      const std::string& pointValue,
      SgfcBoardSize boardSize) const;
    //@}
  };
}
