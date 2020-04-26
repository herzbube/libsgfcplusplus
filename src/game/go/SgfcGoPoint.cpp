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
    , yPositionLowerLeftOrigin(0)
  {
    DecomposeSgfNotation(sgfNotation, boardSize);
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
        return this->xPositionUpperLeftOrigin;
      default:
        ThrowInvalidCoordinateSystem(coordinateSystem);
        // Some compilers don't see that we just threw an exception, so this
        // dummy return statement makes them happy.
        return this->xPositionUpperLeftOrigin;
    }
  }

  unsigned int SgfcGoPoint::GetYPosition(SgfcCoordinateSystem coordinateSystem) const
  {
    switch (coordinateSystem)
    {
      case SgfcCoordinateSystem::UpperLeftOrigin:
        return this->yPositionUpperLeftOrigin;
      case SgfcCoordinateSystem::LowerLeftOrigin:
        return this->yPositionLowerLeftOrigin;
      default:
        ThrowInvalidCoordinateSystem(coordinateSystem);
        // Some compilers don't see that we just threw an exception, so this
        // dummy return statement makes them happy.
        return this->yPositionUpperLeftOrigin;
    }
  }

  bool SgfcGoPoint::HasPosition(SgfcGoPointNotation goPointNotation) const
  {
    switch (goPointNotation)
    {
      case SgfcGoPointNotation::Sgf:
        return ! this->sgfNotation.empty();
      case SgfcGoPointNotation::Figure:
        return ! this->figureNotation.empty();
      case SgfcGoPointNotation::Hybrid:
        return ! this->hybridNotation.empty();
      default:
        ThrowInvalidGoPointNotation(goPointNotation);
        // Some compilers don't see that we just threw an exception, so this
        // dummy return statement makes them happy.
        return ! this->sgfNotation.empty();
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
        return this->hybridNotation;
      default:
        ThrowInvalidGoPointNotation(goPointNotation);
        // Some compilers don't see that we just threw an exception, so this
        // dummy return statement makes them happy.
        return this->sgfNotation;
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
        return this->xCompoundHybridNotation;
      default:
        ThrowInvalidGoPointNotation(goPointNotation);
        // Some compilers don't see that we just threw an exception, so this
        // dummy return statement makes them happy.
        return this->xCompoundSgfNotation;
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
        return this->yCompoundHybridNotation;
      default:
        ThrowInvalidGoPointNotation(goPointNotation);
        // Some compilers don't see that we just threw an exception, so this
        // dummy return statement makes them happy.
        return this->yCompoundSgfNotation;
    }
  }

  void SgfcGoPoint::DecomposeSgfNotation(const std::string& sgfNotation, SgfcBoardSize boardSize)
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

    this->xCompoundHybridNotation = MapPositionToXCompountHybridNotation(this->xPositionUpperLeftOrigin);
    // Because boardSize must refer to a square board we don't have to look at
    // the boardSize.Columns
    this->yPositionLowerLeftOrigin = static_cast<unsigned int>(boardSize.Rows + 1 - this->yPositionUpperLeftOrigin);
    stream.str(SgfcPrivateConstants::EmptyString);
    stream << this->yPositionLowerLeftOrigin;
    this->yCompoundHybridNotation = stream.str();
    this->hybridNotation = this->xCompoundHybridNotation + this->yCompoundHybridNotation;
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

  std::string SgfcGoPoint::MapPositionToXCompountHybridNotation(unsigned int position)
  {
    // Position 9 = letter "I" - we want to skip "I"
    if (position >= 9)
      position++;

    char character = 'A' + position - 1;
    return std::string(character, 1);
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
