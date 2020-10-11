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
#include <sgfc/argument/SgfcArguments.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcArguments is constructed", "[argument]" )
{
  GIVEN( "The SgfcArguments default constructor is used" )
  {
    WHEN( "SgfcArguments is constructed" )
    {
      THEN( "SgfcArguments is constructed successfully" )
      {
        REQUIRE_NOTHROW( SgfcArguments() );
      }
    }

    WHEN( "SgfcArguments is constructed" )
    {
      SgfcArguments arguments;

      THEN( "SgfcArguments has the expected default state" )
      {
        REQUIRE( arguments.HasArguments() == false );
        REQUIRE( arguments.GetArguments().size() == 0 );
      }
    }
  }
}

SCENARIO( "An argument is added to SgfcArguments", "[argument]" )
{
  SgfcArguments arguments;

  GIVEN( "An argument without parameter is added" )
  {
    WHEN( "The argument type requires no parameter" )
    {
      auto testData = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithoutParameters()) );
      auto argumentType = std::get<0>(testData);
      arguments.AddArgument(argumentType);

      THEN( "The argument is added successfully" )
      {
        REQUIRE( arguments.HasArguments() == true );
        REQUIRE( arguments.GetArguments().size() == 1 );

        auto argument = arguments.GetArguments().front();
        REQUIRE( argument->GetArgumentType() == argumentType );
        REQUIRE( argument->HasIntegerTypeParameter() == false );
        REQUIRE( argument->HasPropertyTypeParameter() == false );
        REQUIRE( argument->ToString() == std::get<1>(testData) );
      }
    }

    WHEN( "The argument type requires a parameter" )
    {
      auto argumentType = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithParameter()) );

      THEN( "The add operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          arguments.AddArgument(argumentType),
          std::invalid_argument);
      }
    }

    WHEN( "The same argument type is added more than once" )
    {
      auto testData = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithoutParameters()) );
      auto argumentType = std::get<0>(testData);
      arguments.AddArgument(argumentType);

      THEN( "The add operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          arguments.AddArgument(argumentType),
          std::invalid_argument);
      }
    }
  }

  GIVEN( "An argument with an integer type parameter is added" )
  {
    WHEN( "The argument type requires an integer type parameter" )
    {
      auto testData = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithValidIntegerTypeParameter()) );
      auto argumentType = std::get<0>(testData);
      auto parameter = std::get<1>(testData);
      arguments.AddArgument(argumentType, parameter);

      THEN( "The argument is added successfully" )
      {
        REQUIRE( arguments.HasArguments() == true );
        REQUIRE( arguments.GetArguments().size() == 1 );

        auto argument = arguments.GetArguments().front();
        REQUIRE( argument->GetArgumentType() == std::get<0>(testData) );
        REQUIRE( argument->HasIntegerTypeParameter() == true );
        REQUIRE( argument->GetIntegerTypeParameter() == std::get<1>(testData) );
        REQUIRE( argument->HasPropertyTypeParameter() == false );
        REQUIRE( argument->ToString() == std::get<2>(testData) );
      }
    }

    WHEN( "The argument type does not require an integer type parameter" )
    {
      auto argumentType = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithoutIntegerTypeParameter()) );
      int parameter = 1;

      THEN( "The add operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          arguments.AddArgument(argumentType, parameter),
          std::invalid_argument);
      }
    }

    WHEN( "The argument type that does not allow multiplicity is added more than once with different parameter values" )
    {
      auto argumentType = SgfcArgumentType::BeginningOfSgfData;
      int parameterValue1 = 1;
      int parameterValue2 = 2;
      arguments.AddArgument(argumentType, parameterValue1);

      THEN( "The add operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          arguments.AddArgument(argumentType, parameterValue2),
          std::invalid_argument);
      }
    }

    WHEN( "The argument type that allows multiplicity is added more than once with different parameter values" )
    {
      auto argumentType = SgfcArgumentType::DisableMessageNumber;
      int parameterValue1 = 1;
      int parameterValue2 = 2;
      arguments.AddArgument(argumentType, parameterValue1);
      arguments.AddArgument(argumentType, parameterValue2);

      THEN( "The argument is added successfully" )
      {
        REQUIRE( arguments.HasArguments() == true );
        REQUIRE( arguments.GetArguments().size() == 2 );

        auto argument1 = arguments.GetArguments().front();
        REQUIRE( argument1->GetArgumentType() == argumentType );
        REQUIRE( argument1->HasIntegerTypeParameter() == true );
        REQUIRE( argument1->GetIntegerTypeParameter() == parameterValue1 );
        REQUIRE( argument1->HasPropertyTypeParameter() == false );
        REQUIRE( argument1->ToString() == "-d1" );

        auto argument2 = arguments.GetArguments().back();
        REQUIRE( argument2->GetArgumentType() == argumentType );
        REQUIRE( argument2->HasIntegerTypeParameter() == true );
        REQUIRE( argument2->GetIntegerTypeParameter() == parameterValue2 );
        REQUIRE( argument2->HasPropertyTypeParameter() == false );
        REQUIRE( argument2->ToString() == "-d2" );
      }
    }

    WHEN( "The same argument type that allows multiplicity is added more than once with same parameter values" )
    {
      auto argumentType = SgfcArgumentType::DisableMessageNumber;
      int parameter = 1;
      arguments.AddArgument(argumentType, parameter);

      THEN( "The add operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          arguments.AddArgument(argumentType, parameter),
          std::invalid_argument);
      }
    }
  }

  GIVEN( "An argument with an SgfcPropertyType parameter is added" )
  {
    WHEN( "The argument type requires an SgfcPropertyType parameter" )
    {
      auto testData = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithValidPropertyTypeParameter()) );
      auto argumentType = std::get<0>(testData);
      auto parameter = std::get<1>(testData);
      arguments.AddArgument(argumentType, parameter);

      THEN( "The argument is added successfully" )
      {
        REQUIRE( arguments.HasArguments() == true );
        REQUIRE( arguments.GetArguments().size() == 1 );

        auto argument = arguments.GetArguments().front();
        REQUIRE( argument->GetArgumentType() == std::get<0>(testData) );
        REQUIRE( argument->HasIntegerTypeParameter() == false );
        REQUIRE( argument->HasPropertyTypeParameter() == true );
        REQUIRE( argument->GetPropertyTypeParameter() == std::get<1>(testData) );
        REQUIRE( argument->ToString() == std::get<2>(testData) );
      }
    }

    WHEN( "The argument type does not require an SgfcPropertyType parameter" )
    {
      auto argumentType = GENERATE( from_range(TestDataGenerator::GetArgumentTypesWithoutPropertyTypeParameter()) );
      SgfcPropertyType parameter = SgfcPropertyType::GM;

      THEN( "The add operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          arguments.AddArgument(argumentType, parameter),
          std::invalid_argument);
      }
    }

    WHEN( "The argument type that does not allow multiplicity is added more than once with different parameter values" )
    {
      // No tests, there is no argument type that does not allow multiplicity
      // and that requires an SgfcPropertyType parameter
    }

    WHEN( "The argument type that allows multiplicity is added more than once with different parameter values" )
    {
      auto argumentType = SgfcArgumentType::DeletePropertyType;
      SgfcPropertyType parameterValue1 = SgfcPropertyType::GM;
      SgfcPropertyType parameterValue2 = SgfcPropertyType::SZ;
      arguments.AddArgument(argumentType, parameterValue1);
      arguments.AddArgument(argumentType, parameterValue2);

      THEN( "The argument is added successfully" )
      {
        REQUIRE( arguments.HasArguments() == true );
        REQUIRE( arguments.GetArguments().size() == 2 );

        auto argument1 = arguments.GetArguments().front();
        REQUIRE( argument1->GetArgumentType() == argumentType );
        REQUIRE( argument1->HasIntegerTypeParameter() == false );
        REQUIRE( argument1->HasPropertyTypeParameter() == true );
        REQUIRE( argument1->GetPropertyTypeParameter() == parameterValue1 );
        REQUIRE( argument1->ToString() == "-yGM" );

        auto argument2 = arguments.GetArguments().back();
        REQUIRE( argument2->GetArgumentType() == argumentType );
        REQUIRE( argument2->HasIntegerTypeParameter() == false );
        REQUIRE( argument2->HasPropertyTypeParameter() == true );
        REQUIRE( argument2->GetPropertyTypeParameter() == parameterValue2 );
        REQUIRE( argument2->ToString() == "-ySZ" );
      }
    }

    WHEN( "The same argument type that allows multiplicity is added more than once with same parameter values" )
    {
      auto argumentType = SgfcArgumentType::DeletePropertyType;
      SgfcPropertyType parameter = SgfcPropertyType::GM;
      arguments.AddArgument(argumentType, parameter);

      THEN( "The add operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          arguments.AddArgument(argumentType, parameter),
          std::invalid_argument);
      }
    }
  }

  GIVEN( "SgfcArguments already contains arguments" )
  {
    arguments.AddArgument(SgfcArgumentType::DeleteEmptyNodes);
    arguments.AddArgument(SgfcArgumentType::DeleteUnknownProperties);
    REQUIRE( arguments.HasArguments() == true );
    REQUIRE( arguments.GetArguments().size() == 2 );

    WHEN( "Another arguments is added" )
    {
      auto argumentType = SgfcArgumentType::DeleteObsoleteProperties;
      arguments.AddArgument(argumentType);

      THEN( "The argument is added to the end of the collection" )
      {
        REQUIRE( arguments.HasArguments() == true );
        REQUIRE( arguments.GetArguments().size() == 3 );

        auto argument = arguments.GetArguments().back();
        REQUIRE( argument->GetArgumentType() == argumentType );
        REQUIRE( argument->HasIntegerTypeParameter() == false );
        REQUIRE( argument->HasPropertyTypeParameter() == false );
        REQUIRE( argument->ToString() == "-o" );
      }
    }
  }
}

SCENARIO( "SgfcArguments is cleared", "[argument]" )
{
  SgfcArguments arguments;

  GIVEN( "SgfcArguments contains no arguments" )
  {
    WHEN( "SgfcArguments is cleared" )
    {
      arguments.ClearArguments();

      THEN( "The operation does nothing" )
      {
        REQUIRE( arguments.HasArguments() == false );
        REQUIRE( arguments.GetArguments().size() == 0 );
      }
    }
  }

  GIVEN( "SgfcArguments contains one argument" )
  {
    arguments.AddArgument(SgfcArgumentType::DeleteEmptyNodes);

    WHEN( "SgfcArguments is cleared" )
    {
      arguments.ClearArguments();

      THEN( "The operation removes 1 argument" )
      {
        REQUIRE( arguments.HasArguments() == false );
        REQUIRE( arguments.GetArguments().size() == 0 );
      }
    }
  }

  GIVEN( "SgfcArguments contains multiple arguments" )
  {
    auto testData = TestDataGenerator::GetArgumentTypesWithoutParameters();
    for (auto testDataElement : testData)
      arguments.AddArgument(std::get<0>(testDataElement));
    REQUIRE( arguments.HasArguments() == true );
    REQUIRE( arguments.GetArguments().size() == testData.size() );

    WHEN( "SgfcArguments is cleared" )
    {
      arguments.ClearArguments();

      THEN( "The operation removes 1 argument" )
      {
        REQUIRE( arguments.HasArguments() == false );
        REQUIRE( arguments.GetArguments().size() == 0 );
      }
    }
  }

  GIVEN( "SgfcArguments contains arguments" )
  {
    arguments.AddArgument(SgfcArgumentType::DeleteEmptyNodes);

    WHEN( "SgfcArguments is cleared twice" )
    {
      arguments.ClearArguments();
      REQUIRE( arguments.HasArguments() == false );
      REQUIRE( arguments.GetArguments().size() == 0 );

      arguments.ClearArguments();

      THEN( "The second operation does nothing" )
      {
        REQUIRE( arguments.HasArguments() == false );
        REQUIRE( arguments.GetArguments().size() == 0 );
      }
    }
  }
}
