// -----------------------------------------------------------------------------
// Copyright 2024 Patrick Näf (herzbube@herzbube.ch)
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
#include "../TestDataGenerator.h"
#include <SgfcConstants.h>
#include <SgfcGameResult.h>

// Unit test library includes
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcGameResult is constructed", "[game]" )
{
  GIVEN( "SgfcGameResult is constructed" )
  {
    WHEN( "SgfcGameResult is constructed" )
    {
      SgfcGameResult gameResult;

      THEN( "SgfcGameResult is constructed successfully" )
      {
        REQUIRE( gameResult.GameResultType == SgfcGameResultType::UnknownResult );
        REQUIRE( gameResult.WinType == SgfcWinType::WinWithScore );
        REQUIRE( gameResult.Score == 0.0 );
        REQUIRE( gameResult.IsValid == false );
      }
    }
  }

  GIVEN( "Two SgfcGameResult objects have different values for IsValid" )
  {
    SgfcGameResult gameResult1;
    SgfcGameResult gameResult2 = gameResult1;
    gameResult2.IsValid = ! gameResult2.IsValid;

    WHEN( "The two SgfcGameResult objects are compared for equality" )
    {
      bool areEqual = (gameResult1 == gameResult2);

      THEN( "The two SgfcGameResult objects are not equal" )
      {
        REQUIRE( areEqual == false );
      }
    }

    WHEN( "The two SgfcGameResult objects are compared for inequality" )
    {
      bool areNotEqual = (gameResult1 != gameResult2);

      THEN( "The two SgfcGameResult objects are not equal" )
      {
        REQUIRE( areNotEqual == true );
      }
    }
  }
}

SCENARIO( "An SgfcPropertyType::RE property value is decomposed", "[game]" )
{
  GIVEN( "The property value is valid" )
  {
    auto testData = GENERATE( from_range(TestDataGenerator::GetValidPropertyValuesRE()) );

    WHEN( "The property value is decomposed" )
    {
      auto decomposedPropertyValue = SgfcGameResult::FromPropertyValue(std::get<0>(testData));
      auto expectedDecomposedPropertyValue = std::get<1>(testData);

      THEN( "The result of the decomposition are SgfcDate objects" )
      {
        REQUIRE( decomposedPropertyValue.IsValid == true );
        REQUIRE( decomposedPropertyValue == expectedDecomposedPropertyValue );
      }
    }
  }

  GIVEN( "The property value is not valid" )
  {
    auto testData = GENERATE( from_range(TestDataGenerator::GetInvalidPropertyValuesRE()) );

    WHEN( "The property value is decomposed" )
    {
      auto decomposedPropertyValue = SgfcGameResult::FromPropertyValue(testData);

      THEN( "The result of the decomposition is an empty collection" )
      {
        REQUIRE( decomposedPropertyValue.IsValid == false );
      }
    }
  }
}

SCENARIO( "An SgfcPropertyType::RE property value is composed", "[game]" )
{
  GIVEN( "The SgfcGameResult object is valid" )
  {
    auto testData = GENERATE( from_range(TestDataGenerator::GetValidSgfcGameResults()) );

    WHEN( "The property value is composed" )
    {
      auto composedPropertyValue = SgfcGameResult::ToPropertyValue(std::get<0>(testData));
      auto expectedComposedPropertyValue = std::get<1>(testData);

      THEN( "The result of the composition is an SgfcPropertyType::RE property value" )
      {
        REQUIRE( composedPropertyValue == expectedComposedPropertyValue );
      }
    }
  }

  GIVEN( "The SgfcGameResult object is not valid" )
  {
    auto testData = GENERATE( from_range(TestDataGenerator::GetInvalidSgfcGameResults()) );

    WHEN( "The property value is composed" )
    {
      auto composedPropertyValue = SgfcGameResult::ToPropertyValue(testData);

      THEN( "The result of the composition is SgfcConstants::NoneValueString" )
      {
        REQUIRE( composedPropertyValue == SgfcConstants::NoneValueString );
      }
    }
  }
}
