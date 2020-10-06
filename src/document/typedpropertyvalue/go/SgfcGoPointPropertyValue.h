#pragma once

// Project includes
#include "../../../../include/ISgfcGoPointPropertyValue.h"
#include "../../../../include/SgfcBoardSize.h"
#include "../SgfcPointPropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoPointPropertyValue class provides an implementation of
  /// the ISgfcGoPointPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  /// @ingroup go
  class SgfcGoPointPropertyValue : public SgfcPointPropertyValue, public ISgfcGoPointPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcGoPointPropertyValue object.
    /// The object holds an ISgfcGoPoint object that refers to the point
    /// specified by @a rawValue. @a boardSize indicates the size of the Go
    /// board that the Go point is located on.
    ///
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
    SgfcGoPointPropertyValue(const std::string& rawValue, SgfcBoardSize boardSize);

    /// @brief Initializes a newly constructed SgfcGoPointPropertyValue object.
    /// No attempt is made to interpret @a rawValue. As a consequence, the
    /// SgfcGoPointPropertyValue object does not hold an ISgfcGoPoint object.
    SgfcGoPointPropertyValue(const std::string& rawValue);

    /// @brief Destroys and cleans up the SgfcGoPointPropertyValue object.
    virtual ~SgfcGoPointPropertyValue();

    virtual const ISgfcGoPointPropertyValue* ToGoPointValue() const;
    virtual std::shared_ptr<ISgfcGoPoint> GetGoPoint() const;

  private:
    std::shared_ptr<ISgfcGoPoint> goPoint;
  };
}
