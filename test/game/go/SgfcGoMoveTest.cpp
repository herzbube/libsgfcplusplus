// Library includes
#include <game/go/SgfcGoMove.h>
#include <game/go/SgfcGoPoint.h>
#include <game/go/SgfcGoStone.h>
#include <SgfcConstants.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcGoMove is constructed", "[go]" )
{
  GIVEN( "The SgfcGoMove constructor taking an ISgfcGoStone parameter is used" )
  {
    WHEN( "SgfcGoMove is constructed with valid data" )
    {
      std::shared_ptr<ISgfcGoPoint> goPoint = std::shared_ptr<ISgfcGoPoint>(
        new SgfcGoPoint("A1", SgfcConstants::BoardSizeDefaultGo));
      std::shared_ptr<ISgfcGoStone> goStone = std::shared_ptr<ISgfcGoStone>(
        new SgfcGoStone(SgfcColor::Black, goPoint));

      SgfcGoMove goMove(goStone);

      THEN( "SgfcGoMove is constructed successfully" )
      {
        REQUIRE( goMove.IsPassMove() == false );
        REQUIRE( goMove.GetStone() == goStone );
        REQUIRE( goMove.GetPlayerColor() == goStone->GetColor() );
        REQUIRE( goMove.GetStoneLocation() == goPoint );
      }
    }

    WHEN( "SgfcGoMove is constructed with invalid data" )
    {
      THEN( "The SgfcGoMove contructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcGoMove(nullptr),
          std::invalid_argument);
      }
    }
  }

  GIVEN( "The SgfcGoMove constructor taking an SgfcColor parameter is used" )
  {
    WHEN( "SgfcGoMove is constructed with valid data" )
    {
      SgfcColor playerColor = GENERATE( SgfcColor::Black, SgfcColor::White );

      SgfcGoMove goMove(playerColor);

      THEN( "SgfcGoMove is constructed successfully" )
      {
        REQUIRE( goMove.IsPassMove() == true );
        REQUIRE( goMove.GetStone() == nullptr );
        REQUIRE( goMove.GetPlayerColor() == playerColor );
        REQUIRE( goMove.GetStoneLocation() == nullptr );
      }
    }

    WHEN( "SgfcGoMove is constructed with invalid data" )
    {
      // No tests because there are no invalid SgfcColor values
    }
  }
}
