// -----------------------------------------------------------------------------
// Copyright 2020-2026 Patrick Näf (herzbube@herzbube.ch)
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

// Project includes
#include "SgfcGoPoint.h"
#include "../../SgfcPrivateConstants.h"
#include "../../SgfcUtility.h"
#include "../../parsing/SgfcValueConverter.h"
#include "../../../include/SgfcConstants.h"

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcGoPoint::SgfcGoPoint(const SgfcPoint& pointValue, SgfcBoardSize boardSize)
    : xPositionUpperLeftOrigin(0)
    , yPositionUpperLeftOrigin(0)
    , yPositionLowerLeftOrigin(0)
  {
    if (boardSize.Columns < SgfcConstants::BoardSizeMinimum.Columns ||
        boardSize.Rows < SgfcConstants::BoardSizeMinimum.Rows)
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Board size parameter indicates a board smaller than the minimum required by the SGF standard ("
        << SgfcConstants::BoardSizeMinimum.Columns << "x" << SgfcConstants::BoardSizeMinimum.Rows << "). Size = "
        << boardSize.Columns << "x" << boardSize.Rows;
      throw std::invalid_argument(message.str());
    }

    if (boardSize.Columns > SgfcConstants::BoardSizeMaximumGo.Columns ||
        boardSize.Rows > SgfcConstants::BoardSizeMaximumGo.Rows)
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Board size parameter indicates a board larger than the maximum allowed by the SGF standard ("
        << SgfcConstants::BoardSizeMaximumGo.Columns << "x" << SgfcConstants::BoardSizeMaximumGo.Rows << "). Size = "
        << boardSize.Columns << "x" << boardSize.Rows;
      throw std::invalid_argument(message.str());
    }

    DecomposePointValue(pointValue, boardSize);
  }

  SgfcGoPoint::~SgfcGoPoint()
  {
  }

  SgfcGoPointAxisPosition SgfcGoPoint::GetXPosition(SgfcCoordinateSystem coordinateSystem) const
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

  SgfcGoPointAxisPosition SgfcGoPoint::GetYPosition(SgfcCoordinateSystem coordinateSystem) const
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

  void SgfcGoPoint::DecomposePointValue(const SgfcPoint& pointValue, SgfcBoardSize boardSize)
  {
    auto substrings = SgfcUtility::SplitString(pointValue, '-');
    if (substrings.size() > 2)
      ThrowPointValueNotInValidNotation(pointValue);

    if (substrings.size() == 2)
    {
      ParseFigureCompoundsOrThrow(substrings.front(), substrings.back(), pointValue, boardSize);
    }
    else
    {
      if (pointValue.size() < 2 || pointValue.size() > 3)
        ThrowPointValueNotInValidNotation(pointValue);

      if (IsDigit(pointValue.at(1)))
      {
        ParseHybridCompoundsOrThrow(pointValue, boardSize);
      }
      else
      {
        if (pointValue.size() != 2)
          ThrowPointValueNotInValidNotation(pointValue);

        ParseSgfCompoundsOrThrow(pointValue, boardSize);
      }
    }

    BuildSgfNotation();
    BuildFigureNotation();
    BuildHybridNotation();
  }

  void SgfcGoPoint::ParseSgfCompoundsOrThrow(
    const SgfcPoint& pointValue,
    SgfcBoardSize boardSize)
  {
    char xCompoundCharacterSgfNotation = pointValue.at(0);
    char yCompoundCharacterSgfNotation = pointValue.at(1);

    if (! IsValidSgfCharacter(xCompoundCharacterSgfNotation))
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Point value given in SGF notation has invalid x-axis compound. Point value = " << pointValue;
      throw std::invalid_argument(message.str());
    }

    if (! IsValidSgfCharacter(yCompoundCharacterSgfNotation))
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Point value given in SGF notation has invalid y-axis compound. Point value = " << pointValue;
      throw std::invalid_argument(message.str());
    }

    SetPositionOrThrow(MapSgfCharacterToPositionUpperLeftOrigin(xCompoundCharacterSgfNotation),
                       MapSgfCharacterToPositionUpperLeftOrigin(yCompoundCharacterSgfNotation),
                       pointValue,
                       boardSize);
  }

  void SgfcGoPoint::ParseFigureCompoundsOrThrow(
    const std::string& xCompoundFigureNotation,
    const std::string& yCompoundFigureNotation,
    const SgfcPoint& pointValue,
    SgfcBoardSize boardSize)
  {
    if (DoesCompoundStringContainNonDigitCharacters(xCompoundFigureNotation))
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Point value given in Figure notation has non-numeric x-axis compound. Point value = " << pointValue;
      throw std::invalid_argument(message.str());
    }

    if (DoesCompoundStringContainNonDigitCharacters(yCompoundFigureNotation))
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Point value given in Figure notation has non-numeric y-axis compound. Point value = " << pointValue;
      throw std::invalid_argument(message.str());
    }

    SgfcNumber xCompoundFigureNotationAsNumber = ConvertFigureCompoundOrThrow(xCompoundFigureNotation,
                                                                              "x-axis",
                                                                              pointValue);

    SgfcNumber yCompoundFigureNotationAsNumber = ConvertFigureCompoundOrThrow(yCompoundFigureNotation,
                                                                              "y-axis",
                                                                              pointValue);

    SetPositionOrThrow(xCompoundFigureNotationAsNumber,
                       yCompoundFigureNotationAsNumber,
                       pointValue,
                       boardSize);
  }

  void SgfcGoPoint::ParseHybridCompoundsOrThrow(
    const SgfcPoint& pointValue,
    SgfcBoardSize boardSize)
  {
    char xCompoundHybridNotation = pointValue.at(0);
    std::string yCompoundHybridNotation = pointValue.substr(1);

    if (! IsValidXCompoundHybridNotation(xCompoundHybridNotation))
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Point value given in Hybrid notation has invalid x-axis compound. Point value = " << pointValue;
      throw std::invalid_argument(message.str());
    }

    if (DoesCompoundStringContainNonDigitCharacters(yCompoundHybridNotation))
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Point value given in Hybrid notation has non-numeric y-axis compound. Point value = " << pointValue;
      throw std::invalid_argument(message.str());
    }

    // The caller of this function has made sure that yCompoundHybridNotation
    // cannot have more than 2 characters => the y-axis compound is guaranteed
    // to be in the range 0-99, therefore SgfcValueConverter is not needed,
    // stoi() is sufficient.
    SgfcGoPointAxisPosition yPositionLowerLeftOrigin = stoi(yCompoundHybridNotation);
    if (yPositionLowerLeftOrigin > 25)
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Point value given in Hybrid notation has y-axis compound that exceeds the maximum allowed value. Point value = " << pointValue;
      throw std::invalid_argument(message.str());
    }

    // Can be negative if the point value exceeds the board size => use a signed
    // data type to store the result
    SgfcNumber yPositionUpperLeftOrigin = static_cast<SgfcNumber>(boardSize.Rows + 1 - yPositionLowerLeftOrigin);

    SetPositionOrThrow(MapXCompoundHybridNotationToPositionUpperLeftOrigin(xCompoundHybridNotation),
                       yPositionUpperLeftOrigin,
                       pointValue,
                       boardSize);
  }

  // Function takes SgfcNumber values, which are signed, because some callers
  // may supply a negative number
  void SgfcGoPoint::SetPositionOrThrow(
    SgfcNumber xPositionUpperLeftOrigin,
    SgfcNumber yPositionUpperLeftOrigin,
    const SgfcPoint& pointValue,
    SgfcBoardSize boardSize)
  {
    if (xPositionUpperLeftOrigin < 1)
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Point value refers to an x-axis location less than 1. Point value = " << pointValue;
      throw std::invalid_argument(message.str());
    }
    else if (xPositionUpperLeftOrigin > boardSize.Columns)
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Point value refers to an x-axis location that exceeds the board size " << boardSize.Columns << ". Point value = " << pointValue;
      throw std::invalid_argument(message.str());
    }
    else if (yPositionUpperLeftOrigin < 1)
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Point value refers to an y-axis location less than 1. Point value = " << pointValue;
      throw std::invalid_argument(message.str());
    }
    else if (yPositionUpperLeftOrigin > boardSize.Rows)
    {
      std::stringstream message;
      message << "SgfcGoPoint constructor failed: Point value refers to an y-axis location that exceeds the board size " << boardSize.Columns << ". Point value = " << pointValue;
      throw std::invalid_argument(message.str());
    }

    this->xPositionUpperLeftOrigin = static_cast<SgfcGoPointAxisPosition>(xPositionUpperLeftOrigin);
    this->yPositionUpperLeftOrigin = static_cast<SgfcGoPointAxisPosition>(yPositionUpperLeftOrigin);
    this->yPositionLowerLeftOrigin = static_cast<SgfcGoPointAxisPosition>(boardSize.Rows + 1 - this->yPositionUpperLeftOrigin);
  }

  void SgfcGoPoint::BuildSgfNotation()
  {
    if (this->xPositionUpperLeftOrigin > 52 || this->yPositionUpperLeftOrigin > 52)
      return;

    this->xCompoundSgfNotation = MapPositionUpperLeftOriginToSgfCharacter(this->xPositionUpperLeftOrigin);
    this->yCompoundSgfNotation = MapPositionUpperLeftOriginToSgfCharacter(this->yPositionUpperLeftOrigin);
    this->sgfNotation = this->xCompoundSgfNotation + this->yCompoundSgfNotation;
  }

  void SgfcGoPoint::BuildFigureNotation()
  {
    std::stringstream stream;
    stream << this->xPositionUpperLeftOrigin;
    this->xCompoundFigureNotation = stream.str();

    stream.str(SgfcPrivateConstants::EmptyString);
    stream << this->yPositionUpperLeftOrigin;
    this->yCompoundFigureNotation = stream.str();

    this->figureNotation = this->xCompoundFigureNotation + "-" + this->yCompoundFigureNotation;
  }

  void SgfcGoPoint::BuildHybridNotation()
  {
    if (this->xPositionUpperLeftOrigin > 25 || this->yPositionLowerLeftOrigin > 25)
      return;

    this->xCompoundHybridNotation = MapPositionToXCompoundHybridNotation(this->xPositionUpperLeftOrigin);

    std::stringstream stream;
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

  SgfcGoPointAxisPosition SgfcGoPoint::MapSgfCharacterToPositionUpperLeftOrigin(char character) const
  {
    if (character >= 'a' && character <= 'z')
      return character - 'a' + 1;
    else if (character >= 'A' && character <= 'Z')
      return character - 'A' + 26 + 1;
    else
      return 0;
  }

  char SgfcGoPoint::MapPositionUpperLeftOriginToSgfCharacter(SgfcGoPointAxisPosition position) const
  {
    char characterSgfNotation;

    if (position <= 26)
      characterSgfNotation = 'a' + position - 1;
    else
      characterSgfNotation = 'A' + position - 26 - 1;

    return characterSgfNotation;
  }

  SgfcNumber SgfcGoPoint::ConvertFigureCompoundOrThrow(const std::string& compoundFigureNotation, const std::string& axisDescription, const std::string& pointValue)
  {
    // In theory, figure notation has the potential for arbitrary board sizes,
    // therefore we use SgfcValueConverter to support the whole value range of
    // rows and columns in SgfcBoardSize. In practice, any value larger than
    // SgfcConstants::BoardSizeMaximumGo will raise an exception, because the
    // constructor does not allow boards larger than
    // SgfcConstants::BoardSizeMaximumGo, hence SetPositionOrThrow() will
    // throw.
    SgfcValueConverter valueConverter;

    SgfcNumber compoundFigureNotationAsNumber;
    std::string typeConversionErrorMessage;
    bool conversionResult = valueConverter.TryConvertStringToNumberValue(compoundFigureNotation,
                                                                         compoundFigureNotationAsNumber,
                                                                         typeConversionErrorMessage);
    if (! conversionResult)
    {
      std::stringstream message;
      message
        << "SgfcGoPoint constructor failed: " << axisDescription << " compound of Point value given in Figure notation failed to convert to a number."
        << " Reason: " << typeConversionErrorMessage << "."
        << " Point value: " << pointValue;
      throw std::invalid_argument(message.str());
    }

    return compoundFigureNotationAsNumber;
  }

  bool SgfcGoPoint::IsValidXCompoundHybridNotation(char character) const
  {
    if (character >= 'A' && character <= 'H')
      return true;
    else if (character >= 'J' && character <= 'Z')
      return true;
    else
      return false;
  }

  SgfcGoPointAxisPosition SgfcGoPoint::MapXCompoundHybridNotationToPositionUpperLeftOrigin(char character)
  {
    if (character >= 'A' && character <= 'H')
      return character - 'A' + 1;
    else if (character >= 'J' && character <= 'Z')
      return character - 'J' + 8 + 1;
    else
      return 0;
  }

  char SgfcGoPoint::MapPositionToXCompoundHybridNotation(SgfcGoPointAxisPosition position)
  {
    // Position 9 = letter "I" - we want to skip "I"
    if (position >= 9)
      position++;

    char character = 'A' + position - 1;

    return character;
  }

  bool SgfcGoPoint::DoesCompoundStringContainNonDigitCharacters(const std::string& compoundString) const
  {
    for (auto character : compoundString)
    {
      if (! IsDigit(character))
        return true;
    }
    return false;
  }

  bool SgfcGoPoint::IsDigit(char character) const
  {
    // Don't use std::isdigit() - we don't want to depend on the locale as to
    // what counts as a digit and what doesn't
    if (character >= '0' && character <= '9')
      return true;
    else
      return false;
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

  void SgfcGoPoint::ThrowPointValueNotInValidNotation(const SgfcPoint& pointValue) const
  {
    std::stringstream message;
    message << "SgfcGoPoint constructor failed: Point value not given in any valid notation. Point value = " << pointValue;
    throw std::invalid_argument(message.str());
  }
}
