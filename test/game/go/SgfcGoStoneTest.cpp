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
