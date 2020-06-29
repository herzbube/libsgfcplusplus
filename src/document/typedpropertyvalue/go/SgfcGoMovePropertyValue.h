#pragma once

// Project includes
#include "../../../../include/ISgfcGoMovePropertyValue.h"
#include "../../../../include/SgfcBoardSize.h"
#include "../../../../include/SgfcColor.h"
#include "../SgfcMovePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoMovePropertyValue class provides an implementation of
  /// the ISgfcGoMovePropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcGoMovePropertyValue : public SgfcMovePropertyValue, public ISgfcGoMovePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcGoMovePropertyValue object.
    /// The object holds an ISgfcGoMove object that refers to the move
    /// specified by @a rawValue and @a color. The move is not a pass move.
    /// @a boardSize indicates the size of the Go board that the Go move is
    /// played on.
    ///
    /// @a rawValue refers to the location (a Go point) of the stone that is
    /// placed by the move on the board. @a rawValue can be given in any one of
    /// the notations enumerated in SgfcGoPointNotation.
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
    SgfcGoMovePropertyValue(const std::string& rawValue, SgfcBoardSize boardSize, SgfcColor color);

    /// @brief Initializes a newly constructed SgfcGoMovePropertyValue object.
    /// The object holds an ISgfcGoMove object that refers to the move
    /// specified by @a color. The move is a pass move.
    SgfcGoMovePropertyValue(SgfcColor color);

    /// @brief Destroys and cleans up the SgfcGoMovePropertyValue object.
    virtual ~SgfcGoMovePropertyValue();

    virtual const ISgfcGoMovePropertyValue* ToGoMoveValue() const;
    virtual std::shared_ptr<ISgfcGoMove> GetGoMove() const;

  private:
    std::shared_ptr<ISgfcGoMove> goMove;
  };
}
