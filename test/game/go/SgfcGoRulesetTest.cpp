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
#include <SgfcConstants.h>
#include <SgfcGoRuleset.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcGoRuleset is constructed", "[game]" )
{
  GIVEN( "SgfcGoRuleset is constructed" )
  {
    WHEN( "SgfcGoRuleset is constructed" )
    {
      SgfcGoRuleset goRuleset;

      THEN( "SgfcGoRuleset is constructed successfully" )
      {
        REQUIRE( goRuleset.GoRulesetType == SgfcGoRulesetType::AGA );
        REQUIRE( goRuleset.IsValid == false );
      }
    }
  }

  GIVEN( "Two SgfcGoRuleset objects have different values for IsValid" )
  {
    SgfcGoRuleset goRuleset1;
    SgfcGoRuleset goRuleset2 = goRuleset1;
    goRuleset2.IsValid = ! goRuleset2.IsValid;

    WHEN( "The two SgfcGoRuleset objects are compared for equality" )
    {
      bool areEqual = (goRuleset1 == goRuleset2);

      THEN( "The two SgfcGoRuleset objects are equal" )
      {
        REQUIRE( areEqual == true );
      }
    }

    WHEN( "The two SgfcGoRuleset objects are compared for inequality" )
    {
      bool areNotEqual = (goRuleset1 != goRuleset2);

      THEN( "The two SgfcGoRuleset objects are equal" )
      {
        REQUIRE( areNotEqual == false );
      }
    }
  }
}

SCENARIO( "An SgfcPropertyType::RU property value is decomposed", "[game]" )
{
  GIVEN( "The property value is valid" )
  {
    auto& testData = GENERATE( from_range(TestDataGenerator::GetValidPropertyValuesRU()) );

    WHEN( "The property value is decomposed" )
    {
      auto decomposedPropertyValue = SgfcGoRuleset::FromPropertyValue(std::get<0>(testData));
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
    auto& testData = GENERATE( from_range(TestDataGenerator::GetInvalidPropertyValuesRU()) );

    WHEN( "The property value is decomposed" )
    {
      auto decomposedPropertyValue = SgfcGoRuleset::FromPropertyValue(testData);

      THEN( "The result of the decomposition is an empty collection" )
      {
        REQUIRE( decomposedPropertyValue.IsValid == false );
      }
    }
  }
}

SCENARIO( "An SgfcPropertyType::RU property value is composed", "[game]" )
{
  GIVEN( "The SgfcGoRuleset object is valid" )
  {
    auto& testData = GENERATE( from_range(TestDataGenerator::GetValidSgfcGoRulesets()) );

    WHEN( "The property value is composed" )
    {
      auto composedPropertyValue = SgfcGoRuleset::ToPropertyValue(std::get<0>(testData));
      auto expectedComposedPropertyValue = std::get<1>(testData);

      THEN( "The result of the composition is an SgfcPropertyType::RU property value" )
      {
        REQUIRE( composedPropertyValue == expectedComposedPropertyValue );
      }
    }
  }

  GIVEN( "The SgfcGoRuleset object is not valid" )
  {
    auto& testData = GENERATE( from_range(TestDataGenerator::GetInvalidSgfcGoRulesets()) );

    WHEN( "The property value is composed" )
    {
      auto composedPropertyValue = SgfcGoRuleset::ToPropertyValue(testData);

      THEN( "The result of the composition is SgfcConstants::NoneValueString" )
      {
        REQUIRE( composedPropertyValue == SgfcConstants::NoneValueString );
      }
    }
  }
}
