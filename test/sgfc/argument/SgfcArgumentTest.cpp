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
        REQUIRE( argument.HasStringTypeParameter() == false );
        REQUIRE( argument.HasPropertyTypeParameter() == false );
        REQUIRE( argument.HasMessageIDParameter() == false );
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
        REQUIRE( argument.HasStringTypeParameter() == false );
        REQUIRE( argument.HasPropertyTypeParameter() == false );
        REQUIRE( argument.HasMessageIDParameter() == false );
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

    GIVEN( "The constructor taking an argument type and a string type parameter is used" )
    {
      WHEN( "Valid arguments are passed to the constructor" )
      {
        auto testData = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithValidStringTypeParameter()) );

        THEN( "SgfcArgument is constructed successfully and has default state" )
        {
          auto argument = SgfcArgument(std::get<0>(testData), std::get<1>(testData));
          REQUIRE( argument.GetArgumentType() == std::get<0>(testData) );
          REQUIRE( argument.HasIntegerTypeParameter() == false );
          REQUIRE( argument.HasStringTypeParameter() == true );
          REQUIRE( argument.GetStringTypeParameter() == std::get<1>(testData) );
          REQUIRE( argument.HasPropertyTypeParameter() == false );
          REQUIRE( argument.HasMessageIDParameter() == false );
          REQUIRE( argument.ToString() == std::get<2>(testData) );
        }

        WHEN( "Invalid arguments are passed to the constructor" )
        {
          auto argumentType = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithoutStringTypeParameter()) );
          std::string parameter = "UTF-8";

          THEN( "The SgfcArgument constructor throws an exception" )
          {
            REQUIRE_THROWS_AS(
              SgfcArgument(argumentType, parameter),
              std::invalid_argument);
          }
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
          REQUIRE( argument.HasStringTypeParameter() == false );
          REQUIRE( argument.HasPropertyTypeParameter() == true );
          REQUIRE( argument.GetPropertyTypeParameter() == std::get<1>(testData) );
          REQUIRE( argument.HasMessageIDParameter() == false );
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

    GIVEN( "The constructor taking an argument type and an SgfcMessageID parameter is used" )
    {
      WHEN( "Valid arguments are passed to the constructor" )
      {
        auto testData = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithValidMessageIDParameter()) );

        THEN( "SgfcArgument is constructed successfully and has default state" )
        {
          auto argument = SgfcArgument(std::get<0>(testData), std::get<1>(testData));
          REQUIRE( argument.GetArgumentType() == std::get<0>(testData) );
          REQUIRE( argument.HasIntegerTypeParameter() == false );
          REQUIRE( argument.HasStringTypeParameter() == false );
          REQUIRE( argument.HasPropertyTypeParameter() == false );
          REQUIRE( argument.HasMessageIDParameter() == true );
          REQUIRE( argument.GetMessageIDParameter() == std::get<1>(testData) );
          REQUIRE( argument.ToString() == std::get<2>(testData) );
        }
      }

      WHEN( "Invalid arguments are passed to the constructor" )
      {
        auto argumentType = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithoutMessageIDParameter()) );
        SgfcMessageID parameter = SgfcMessageID::UnknownPropertyDeleted;

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
