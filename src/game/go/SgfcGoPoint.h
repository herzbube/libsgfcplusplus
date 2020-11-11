// -----------------------------------------------------------------------------
// Copyright 2020 Patrick Näf (herzbube@herzbube.ch)
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

#pragma once

// Project includes
#include "../../../include/ISgfcGoPoint.h"
#include "../../../include/SgfcBoardSize.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoPoint class provides an implementation of the
  /// ISgfcGoPoint interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup go
  class SgfcGoPoint : public ISgfcGoPoint
  {
  public:
    /// @brief Initializes a newly constructed SgfcGoPoint object. The object
    /// refers to the point specified by @a pointValue. @a boardSize indicates
    /// the size of the Go board that the Go point is located on.
    ///
    /// @a pointValue can be given in any one of the notations enumerated in
    /// SgfcGoPointNotation.
    ///
    /// @exception std::invalid_argument Is thrown if @a boardSize refers to
    /// a board with size smaller than the minimum required by the SGF standard
    /// (SgfcConstants::BoardSizeMinimum), or a board with size larger than the
    /// maximum allowed by the SGF standard (SgfcConstants::BoardSizeMaximumGo).
    /// Is also thrown if @a pointValue is not given in one of the notations
    /// enumerated in SgfcGoPointNotation, or if @a pointValue violates one of
    /// the restrictions imposed by the used notation (e.g. y-axis compound
    /// larger than 25 when #SgfcGoPointNotation::Hybrid is used), or if
    /// @a pointValue refers to an invalid location on the board (e.g. an x-axis
    /// or y-axis location that exceeds the board size specified by
    /// @a boardSize, or a compound < 1 when #SgfcGoPointNotation::Figure is
    /// used).
    SgfcGoPoint(const std::string& pointValue, SgfcBoardSize boardSize);

    /// @brief Destroys and cleans up the SgfcGoPoint object.
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

    void DecomposePointValue(const std::string& pointValue, SgfcBoardSize boardSize);

    void ParseSgfCompoundsOrThrow(const std::string& pointValue, SgfcBoardSize boardSize);
    void ParseFigureCompoundsOrThrow(const std::string& xCompoundFigureNotation, const std::string& yCompoundFigureNotation, const std::string& pointValue, SgfcBoardSize boardSize);
    void ParseHybridCompoundsOrThrow(const std::string& pointValue, SgfcBoardSize boardSize);

    void SetPositionOrThrow(int xPositionUpperLeftOrigin, int yPositionUpperLeftOrigin, const std::string& pointValue, SgfcBoardSize boardSize);

    void BuildSgfNotation();
    void BuildFigureNotation();
    void BuildHybridNotation();

    bool IsValidSgfCharacter(char character) const;
    unsigned int MapSgfCharacterToPosition(char character) const;
    char MapPositionToSgfCharacter(unsigned int position) const;

    bool IsValidXCompoundHybridNotation(char character) const;
    unsigned int MapXCompoundHybridNotationToPosition(char character);
    char MapPositionToXCompoundHybridNotation(unsigned int position);

    bool DoesCompoundStringContainNonDigitCharacters(const std::string& compoundString) const;
    bool IsDigit(char character) const;

    void ThrowInvalidCoordinateSystem(SgfcCoordinateSystem coordinateSystem) const;
    void ThrowInvalidGoPointNotation(SgfcGoPointNotation goPointNotation) const;
    void ThrowPointValueNotInValidNotation(const std::string& pointValue) const;
  };
}
