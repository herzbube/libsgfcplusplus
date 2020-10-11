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
#include <game/go/SgfcGoStone.h>
#include <game/go/SgfcGoPoint.h>
#include <SgfcConstants.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcGoStone is constructed", "[go]" )
{
  GIVEN( "The SgfcGoStone constructor is used" )
  {
    WHEN( "SgfcGoStone is constructed with valid data" )
    {
      SgfcColor color = GENERATE( SgfcColor::Black, SgfcColor::White );
      std::shared_ptr<ISgfcGoPoint> goPoint = std::shared_ptr<ISgfcGoPoint>(
        new SgfcGoPoint("A1", SgfcConstants::BoardSizeDefaultGo));

      SgfcGoStone goStone(color, goPoint);

      THEN( "SgfcGoStone is constructed successfully" )
      {
        REQUIRE( goStone.GetColor() == color );
        REQUIRE( goStone.GetLocation() == goPoint );
      }
    }

    WHEN( "SgfcGoPoint is constructed with invalid data" )
    {
      SgfcColor color = GENERATE( SgfcColor::Black, SgfcColor::White );

      THEN( "The SgfcGoPoint contructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcGoStone(color, nullptr),
          std::invalid_argument);
      }
    }
  }
}
