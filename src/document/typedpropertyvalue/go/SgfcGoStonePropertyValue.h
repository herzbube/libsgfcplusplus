#pragma once

// Project includes
#include "../../../../include/ISgfcGoStonePropertyValue.h"
#include "../../../../include/SgfcBoardSize.h"
#include "../SgfcStonePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoStonePropertyValue class provides an implementation of
  /// the ISgfcGoStonePropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcGoStonePropertyValue : public SgfcStonePropertyValue, public ISgfcGoStonePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcGoStonePropertyValue object.
    /// The object holds an ISgfcGoStone object that refers to the stone
    /// specified by @a rawValue and @a color. @a boardSize indicates the size
    /// of the Go board that the Go stone is located on.
    ///
    /// @a rawValue refers to the Go point on which the stone is located.
    /// @a rawValue can be given in any one of the notations enumerated in
    /// SgfcGoPointNotation.
    ///
    /// @exception std::invalid_argument Is thrown if @a boardSize refers to
    /// a board that is not square, a board with size smaller than the minimum
    /// required by the SGF standard (#SgfcConstants::BoardSizeMinimum), or a
    /// board with size larger than the maximum allowed by the SGF standard
    /// (#SgfcConstants::BoardSizeMaximumGo). Is also thrown if @a rawValue is
    /// not given in one of the notations enumerated in SgfcGoPointNotation, or
    /// if @a rawValue violates one of the restrictions imposed by the used
    /// notation (e.g. y-axis compound larger than 25 when
    /// #SgfcGoPointNotation::Hybrid is used), or if @a rawValue refers to an
    /// invalid location on the board (e.g. an x-axis or y-axis location that
    /// exceeds the board size specified by @a boardSize, or a compound < 1 when
    /// #SgfcGoPointNotation::Figure is used).
    SgfcGoStonePropertyValue(const std::string& rawValue, SgfcBoardSize boardSize, SgfcColor color);

    /// @brief Initializes a newly constructed SgfcGoStonePropertyValue object.
    /// The object holds an ISgfcGoStone object that refers to the stone
    /// specified by @a rawValue and @a color. No attempt is made to interpret
    /// @a rawValue. As a consequence, the SgfcGoStonePropertyValue object
    /// contains an ISgfcGoStone object that does not hold an ISgfcGoPoint
    /// object.
    ///
    /// @a rawValue refers to the Go point on which the stone is located.
    SgfcGoStonePropertyValue(const std::string& rawValue, SgfcColor color);

    /// @brief Destroys and cleans up the SgfcGoStonePropertyValue object.
    virtual ~SgfcGoStonePropertyValue();

    virtual const ISgfcGoStonePropertyValue* ToGoStoneValue() const;
    virtual std::shared_ptr<ISgfcGoStone> GetGoStone() const;

  private:
    std::shared_ptr<ISgfcGoStone> goStone;
  };
}
