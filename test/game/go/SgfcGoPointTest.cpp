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

// Library includes
#include "../../TestDataGenerator.h"
#include <game/go/SgfcGoPoint.h>
#include <SgfcUtility.h>

// Unit test library includes
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcGoPoint is constructed", "[go]" )
{
  GIVEN( "The SgfcGoPoint constructor is used" )
  {
    WHEN( "SgfcGoPoint is constructed with valid data" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetGoPointStrings()) );

      SgfcGoPoint goPoint(std::get<0>(testData), std::get<1>(testData));

      THEN( "SgfcGoPoint is constructed successfully" )
      {
        REQUIRE( goPoint.GetXPosition(SgfcCoordinateSystem::UpperLeftOrigin) == std::get<2>(testData) );
        REQUIRE( goPoint.GetYPosition(SgfcCoordinateSystem::UpperLeftOrigin) == std::get<3>(testData) );
        REQUIRE( goPoint.GetXPosition(SgfcCoordinateSystem::LowerLeftOrigin) == std::get<4>(testData) );
        REQUIRE( goPoint.GetYPosition(SgfcCoordinateSystem::LowerLeftOrigin) == std::get<5>(testData) );
        REQUIRE( goPoint.HasPosition(SgfcGoPointNotation::Sgf) == std::get<6>(testData) );
        REQUIRE( goPoint.HasPosition(SgfcGoPointNotation::Figure) == std::get<7>(testData) );
        REQUIRE( goPoint.HasPosition(SgfcGoPointNotation::Hybrid) == std::get<8>(testData) );
        if (goPoint.HasPosition(SgfcGoPointNotation::Sgf))
        {
          REQUIRE( goPoint.GetPosition(SgfcGoPointNotation::Sgf) == std::get<9>(testData) );
          REQUIRE( goPoint.GetXPosition(SgfcGoPointNotation::Sgf) == std::get<9>(testData).substr(0, 1) );
          REQUIRE( goPoint.GetYPosition(SgfcGoPointNotation::Sgf) == std::get<9>(testData).substr(1, 1) );
        }
        if (goPoint.HasPosition(SgfcGoPointNotation::Figure))
        {
          std::string positionFigureNotation = std::get<10>(testData);
          REQUIRE( goPoint.GetPosition(SgfcGoPointNotation::Figure) == positionFigureNotation );

          std::vector<std::string> substrings = SgfcUtility::SplitString(positionFigureNotation, '-');
          REQUIRE( goPoint.GetXPosition(SgfcGoPointNotation::Figure) == substrings[0] );
          REQUIRE( goPoint.GetYPosition(SgfcGoPointNotation::Figure) == substrings[1] );
        }
        if (goPoint.HasPosition(SgfcGoPointNotation::Hybrid))
        {
          REQUIRE( goPoint.GetPosition(SgfcGoPointNotation::Hybrid) == std::get<11>(testData) );
          REQUIRE( goPoint.GetXPosition(SgfcGoPointNotation::Hybrid) == std::get<11>(testData).substr(0, 1) );
          REQUIRE( goPoint.GetYPosition(SgfcGoPointNotation::Hybrid) == std::get<11>(testData).substr(1) );
        }
      }
    }

    WHEN( "SgfcGoPoint is constructed with an invalid board size" )
    {
      auto invalidGoBoardSize = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidGoBoardSizes()) );

      THEN( "The SgfcGoPoint constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcGoPoint("A1", invalidGoBoardSize),
          std::invalid_argument);
      }
    }

    WHEN( "SgfcGoPoint is constructed with an invalid point value" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidGoPointStrings()) );

      THEN( "The SgfcGoPoint constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcGoPoint(testData.first, testData.second),
          std::invalid_argument);
      }
    }
  }
}
