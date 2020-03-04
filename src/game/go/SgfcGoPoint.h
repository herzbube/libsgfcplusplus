#pragma once

// Project includes
#include "../../../include/ISgfcGoPoint.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoPoint class provides an implementation of the
  /// ISgfcGoPoint interface. See the interface header file for
  /// documentation.
  class SgfcGoPoint : public ISgfcGoPoint
  {
  public:
    SgfcGoPoint(const std::string& sgfNotation);
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
    std::string sgfNotation;
    std::string xCompoundSgfNotation;
    std::string yCompoundSgfNotation;
    std::string figureNotation;
    std::string xCompoundFigureNotation;
    std::string yCompoundFigureNotation;

    void DecomposeSgfNotation(const std::string& sgfNotation);
    bool IsValidSgfCharacter(char character) const;
    unsigned int MapSgfCharacterToPosition(char character) const;

    void ThrowInvalidCoordinateSystem(SgfcCoordinateSystem coordinateSystem) const;
    void ThrowInvalidGoPointNotation(SgfcGoPointNotation goPointNotation) const;
  };
}
