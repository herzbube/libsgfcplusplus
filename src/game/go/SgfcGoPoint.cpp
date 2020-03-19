// Project includes
#include "SgfcGoPoint.h"
#include "../../SgfcPrivateConstants.h"

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcGoPoint::SgfcGoPoint(const std::string& sgfNotation, SgfcBoardSize boardSize)
    : xPositionUpperLeftOrigin(0)
    , yPositionUpperLeftOrigin(0)
  {
    DecomposeSgfNotation(sgfNotation);
  }

  SgfcGoPoint::~SgfcGoPoint()
  {
  }

  unsigned int SgfcGoPoint::GetXPosition(SgfcCoordinateSystem coordinateSystem) const
  {
    switch (coordinateSystem)
    {
      case SgfcCoordinateSystem::UpperLeftOrigin:
        return this->xPositionUpperLeftOrigin;
      case SgfcCoordinateSystem::LowerLeftOrigin:
        return 0;
      default:
        ThrowInvalidCoordinateSystem(coordinateSystem);
    }
  }

  unsigned int SgfcGoPoint::GetYPosition(SgfcCoordinateSystem coordinateSystem) const
  {
    switch (coordinateSystem)
    {
      case SgfcCoordinateSystem::UpperLeftOrigin:
        return this->yPositionUpperLeftOrigin;
      case SgfcCoordinateSystem::LowerLeftOrigin:
        return 0;
      default:
        ThrowInvalidCoordinateSystem(coordinateSystem);
    }
  }

  bool SgfcGoPoint::HasPosition(SgfcGoPointNotation goPointNotation) const
  {
    switch (goPointNotation)
    {
      case SgfcGoPointNotation::Sgf:
        return ! this->sgfNotation.empty();
      case SgfcGoPointNotation::Figure:
        return ! this->sgfNotation.empty();
      case SgfcGoPointNotation::Hybrid:
        return false;
      default:
        ThrowInvalidGoPointNotation(goPointNotation);
    }
  }

  std::string SgfcGoPoint::GetPosition(SgfcGoPointNotation goPointNotation) const
  {
    if (! HasPosition(goPointNotation))
      return SgfcPrivateConstants::EmptyString;

    switch (goPointNotation)
    {
      case SgfcGoPointNotation::Sgf:
        return this->sgfNotation;
      case SgfcGoPointNotation::Figure:
        return this->figureNotation;
      case SgfcGoPointNotation::Hybrid:
        return SgfcPrivateConstants::EmptyString;
      default:
        ThrowInvalidGoPointNotation(goPointNotation);
    }
  }

  std::string SgfcGoPoint::GetXPosition(SgfcGoPointNotation goPointNotation) const
  {
    if (! HasPosition(goPointNotation))
      return SgfcPrivateConstants::EmptyString;

    switch (goPointNotation)
    {
      case SgfcGoPointNotation::Sgf:
        return this->xCompoundSgfNotation;
      case SgfcGoPointNotation::Figure:
        return this->xCompoundFigureNotation;
      case SgfcGoPointNotation::Hybrid:
        return SgfcPrivateConstants::EmptyString;
      default:
        ThrowInvalidGoPointNotation(goPointNotation);
    }
  }

  std::string SgfcGoPoint::GetYPosition(SgfcGoPointNotation goPointNotation) const
  {
    if (! HasPosition(goPointNotation))
      return SgfcPrivateConstants::EmptyString;

    switch (goPointNotation)
    {
      case SgfcGoPointNotation::Sgf:
        return this->yCompoundSgfNotation;
      case SgfcGoPointNotation::Figure:
        return this->yCompoundFigureNotation;
      case SgfcGoPointNotation::Hybrid:
        return SgfcPrivateConstants::EmptyString;
      default:
        ThrowInvalidGoPointNotation(goPointNotation);
    }
  }

  void SgfcGoPoint::DecomposeSgfNotation(const std::string& sgfNotation)
  {
    if (sgfNotation.size() != 2)
      return;

    char xCompoundCharacterSgfNotation = sgfNotation.at(0);
    char yCompoundCharacterSgfNotation = sgfNotation.at(1);
    if (! IsValidSgfCharacter(xCompoundCharacterSgfNotation) ||
        ! IsValidSgfCharacter(yCompoundCharacterSgfNotation))
    {
      return;
    }

    this->xPositionUpperLeftOrigin = MapSgfCharacterToPosition(xCompoundCharacterSgfNotation);
    this->yPositionUpperLeftOrigin = MapSgfCharacterToPosition(yCompoundCharacterSgfNotation);

    this->sgfNotation = sgfNotation;
    this->xCompoundSgfNotation = xCompoundCharacterSgfNotation;
    this->yCompoundSgfNotation = yCompoundCharacterSgfNotation;

    std::stringstream stream;
    stream << this->xPositionUpperLeftOrigin;
    this->xCompoundFigureNotation = stream.str();
    stream.str(SgfcPrivateConstants::EmptyString);
    stream << this->yPositionUpperLeftOrigin;
    this->yCompoundFigureNotation = stream.str();
    this->figureNotation = this->xCompoundFigureNotation + "-" + this->yCompoundFigureNotation;
  }

  bool SgfcGoPoint::IsValidSgfCharacter(char character) const
  {
    if (character >= 'a' && character <= 'z')
      return true;
    else if (character >= 'A' && character <= 'Z')
      return true;
    else
      return false;
  }

  unsigned int SgfcGoPoint::MapSgfCharacterToPosition(char character) const
  {
    if (character >= 'a' && character <= 'z')
      return character - 'a' + 1;
    else if (character >= 'A' && character <= 'Z')
      return character - 'A' + 26 + 1;
    else
      return 0;
  }

  void SgfcGoPoint::ThrowInvalidCoordinateSystem(SgfcCoordinateSystem coordinateSystem) const
  {
    std::stringstream message;
    message << "Unexpected coordinate system. SgfcCoordinateSystem value = " << static_cast<int>(coordinateSystem);
    throw std::logic_error(message.str());
  }

  void SgfcGoPoint::ThrowInvalidGoPointNotation(SgfcGoPointNotation goPointNotation) const
  {
    std::stringstream message;
    message << "Unexpected Go point notation. SgfcGoPointNotation value = " << static_cast<int>(goPointNotation);
    throw std::logic_error(message.str());
  }
}
