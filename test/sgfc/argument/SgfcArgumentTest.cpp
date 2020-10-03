// Library includes
#include "../../TestDataGenerator.h"
#include <sgfc/argument/SgfcArgument.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcArgument is constructed", "[argument]" )
{
  GIVEN( "The constructor taking an argument type is used" )
  {
    WHEN( "Valid arguments are passed to the constructor" )
    {
      auto testData = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithoutParameters()) );

      THEN( "SgfcArgument is constructed successfully and has default state" )
      {
        auto argument = SgfcArgument(std::get<0>(testData));
        REQUIRE( argument.GetArgumentType() == std::get<0>(testData) );
        REQUIRE( argument.HasIntegerTypeParameter() == false );
        REQUIRE( argument.HasPropertyTypeParameter() == false );
        REQUIRE( argument.ToString() == std::get<1>(testData) );
      }
    }

    WHEN( "Invalid arguments are passed to the constructor" )
    {
      auto argumentType = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithParameter()) );

      THEN( "The SgfcArgument constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcArgument(argumentType),
          std::invalid_argument);
      }
    }
  }

  GIVEN( "The constructor taking an argument type and an integer type parameter is used" )
  {
    WHEN( "Valid arguments are passed to the constructor" )
    {
      auto testData = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithValidIntegerTypeParameter()) );

      THEN( "SgfcArgument is constructed successfully and has default state" )
      {
        auto argument = SgfcArgument(std::get<0>(testData), std::get<1>(testData));
        REQUIRE( argument.GetArgumentType() == std::get<0>(testData) );
        REQUIRE( argument.HasIntegerTypeParameter() == true );
        REQUIRE( argument.GetIntegerTypeParameter() == std::get<1>(testData) );
        REQUIRE( argument.HasPropertyTypeParameter() == false );
        REQUIRE( argument.ToString() == std::get<2>(testData) );
      }

      WHEN( "Invalid arguments are passed to the constructor" )
      {
        auto argumentType = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithoutIntegerTypeParameter()) );
        int parameter = 1;

        THEN( "The SgfcArgument constructor throws an exception" )
        {
          REQUIRE_THROWS_AS(
            SgfcArgument(argumentType, parameter),
            std::invalid_argument);
        }
      }
    }

    GIVEN( "The constructor taking an argument type and an SgfcPropertyTYpe parameter is used" )
    {
      WHEN( "Valid arguments are passed to the constructor" )
      {
        auto testData = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithValidPropertyTypeParameter()) );

        THEN( "SgfcArgument is constructed successfully and has default state" )
        {
          auto argument = SgfcArgument(std::get<0>(testData), std::get<1>(testData));
          REQUIRE( argument.GetArgumentType() == std::get<0>(testData) );
          REQUIRE( argument.HasIntegerTypeParameter() == false );
          REQUIRE( argument.HasPropertyTypeParameter() == true );
          REQUIRE( argument.GetPropertyTypeParameter() == std::get<1>(testData) );
          REQUIRE( argument.ToString() == std::get<2>(testData) );
        }
      }

      WHEN( "Invalid arguments are passed to the constructor" )
      {
        auto argumentType = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithoutPropertyTypeParameter()) );
        SgfcPropertyType parameter = SgfcPropertyType::GM;

        THEN( "The SgfcArgument constructor throws an exception" )
        {
          REQUIRE_THROWS_AS(
            SgfcArgument(argumentType, parameter),
            std::invalid_argument);
        }
      }
    }
  }
}
