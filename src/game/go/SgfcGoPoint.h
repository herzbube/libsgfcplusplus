#pragma once

// Project includes
#include "../../../include/ISgfcGoPoint.h"
#include "../../../include/SgfcBoardSize.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoPoint class provides an implementation of the
  /// ISgfcGoPoint interface. See the interface header file for
  /// documentation.
  class SgfcGoPoint : public ISgfcGoPoint
  {
  public:
    SgfcGoPoint(const std::string& sgfNotation, SgfcBoardSize boardSize);
    virtual ~SgfcGoPoint();

    virtual unsigned int GetXPosition(SgfcCoordinateSystem coordinateSystem) const;
    virtual unsigned int GetYPosition(SgfcCoordinateSystem coordinateSystem) const;

    virtual bool HasPosition(SgfcGoPointNotation goPointNotation) const;

    virtual std::string GetPosition(SgfcGoPointNotation goPointNotation) const;
    virtual std::string GetXPosition(SgfcGoPointNotation goPointNotation) const;
    virtual std::string GetYPosition(SgfcGoPointNotation goPointNotation) const;

  private:
    unsigned int xPositionUpperLeftOrigin;
    unsigned int yPositionUpperLeftOrigin;
    unsigned int yPositionLowerLeftOrigin;
    std::string sgfNotation;
    std::string xCompoundSgfNotation;
    std::string yCompoundSgfNotation;
    std::string figureNotation;
    std::string xCompoundFigureNotation;
    std::string yCompoundFigureNotation;
    std::string hybridNotation;
    std::string xCompoundHybridNotation;
    std::string yCompoundHybridNotation;

    void DecomposeSgfNotation(const std::string& sgfNotation, SgfcBoardSize boardSize);
    bool IsValidSgfCharacter(char character) const;
    unsigned int MapSgfCharacterToPosition(char character) const;
    std::string MapPositionToXCompountHybridNotation(unsigned int position);

    void ThrowInvalidCoordinateSystem(SgfcCoordinateSystem coordinateSystem) const;
    void ThrowInvalidGoPointNotation(SgfcGoPointNotation goPointNotation) const;
  };
}
