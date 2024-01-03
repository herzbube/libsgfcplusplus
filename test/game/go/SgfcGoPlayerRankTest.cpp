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
#include "../../TestDataGenerator.h"
#include <SgfcConstants.h>
#include <SgfcGoPlayerRank.h>

// Unit test library includes
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcGoPlayerRank is constructed", "[game]" )
{
  GIVEN( "SgfcGoPlayerRank is constructed" )
  {
    WHEN( "SgfcGoPlayerRank is constructed" )
    {
      SgfcGoPlayerRank goPlayerRank;

      THEN( "SgfcGoPlayerRank is constructed successfully" )
      {
        REQUIRE( goPlayerRank.Rank == 30 );
        REQUIRE( goPlayerRank.RankType == SgfcGoPlayerRankType::Kyu );
        REQUIRE( goPlayerRank.RatingType == SgfcGoPlayerRatingType::Unspecified );
        REQUIRE( goPlayerRank.IsValid == false );
      }
    }
  }

  GIVEN( "Two SgfcGoPlayerRank objects have different values for IsValid" )
  {
    SgfcGoPlayerRank goPlayerRank1;
    SgfcGoPlayerRank goPlayerRank2 = goPlayerRank1;
    goPlayerRank2.IsValid = ! goPlayerRank2.IsValid;

    WHEN( "The two SgfcGoPlayerRank objects are compared for equality" )
    {
      bool areEqual = (goPlayerRank1 == goPlayerRank2);

      THEN( "The two SgfcGoPlayerRank objects are not equal" )
      {
        REQUIRE( areEqual == false );
      }
    }

    WHEN( "The two SgfcGoPlayerRank objects are compared for inequality" )
    {
      bool areNotEqual = (goPlayerRank1 != goPlayerRank2);

      THEN( "The two SgfcGoPlayerRank objects are not equal" )
      {
        REQUIRE( areNotEqual == true );
      }
    }
  }
}

SCENARIO( "An SgfcPropertyType::BR or SgfcPropertyType::WR property value is decomposed", "[game]" )
{
  GIVEN( "The property value is valid" )
  {
    auto testData = GENERATE( from_range(TestDataGenerator::GetValidPropertyValuesBRWR()) );

    WHEN( "The property value is decomposed" )
    {
      auto decomposedPropertyValue = SgfcGoPlayerRank::FromPropertyValue(std::get<0>(testData));
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
    auto testData = GENERATE( from_range(TestDataGenerator::GetInvalidPropertyValuesBRWR()) );

    WHEN( "The property value is decomposed" )
    {
      auto decomposedPropertyValue = SgfcGoPlayerRank::FromPropertyValue(testData);

      THEN( "The result of the decomposition is an empty collection" )
      {
        REQUIRE( decomposedPropertyValue.IsValid == false );
      }
    }
  }
}

SCENARIO( "An SgfcPropertyType::BR or SgfcPropertyType::WR property value is composed", "[game]" )
{
  GIVEN( "The SgfcGoPlayerRank object is valid" )
  {
    auto testData = GENERATE( from_range(TestDataGenerator::GetValidSgfcGoPlayerRanks()) );

    WHEN( "The property value is composed" )
    {
      auto composedPropertyValue = SgfcGoPlayerRank::ToPropertyValue(std::get<0>(testData));
      auto expectedComposedPropertyValue = std::get<1>(testData);

      THEN( "The result of the composition is an SgfcPropertyType::BR or SgfcPropertyType::WR property value" )
      {
        REQUIRE( composedPropertyValue == expectedComposedPropertyValue );
      }
    }
  }

  GIVEN( "The SgfcGoPlayerRank object is not valid" )
  {
    auto testData = GENERATE( from_range(TestDataGenerator::GetInvalidSgfcGoPlayerRanks()) );

    WHEN( "The property value is composed" )
    {
      auto composedPropertyValue = SgfcGoPlayerRank::ToPropertyValue(testData);

      THEN( "The result of the composition is SgfcConstants::NoneValueString" )
      {
        REQUIRE( composedPropertyValue == SgfcConstants::NoneValueString );
      }
    }
  }
}
