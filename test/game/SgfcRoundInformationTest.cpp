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
#include "../TestDataGenerator.h"
#include <SgfcConstants.h>
#include <SgfcRoundInformation.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcRoundInformation is constructed", "[game]" )
{
  GIVEN( "SgfcRoundInformation is constructed" )
  {
    WHEN( "SgfcRoundInformation is constructed" )
    {
      SgfcRoundInformation roundInformation;

      THEN( "SgfcRoundInformation is constructed successfully" )
      {
        REQUIRE( roundInformation.RoundNumber == SgfcConstants::NoneValueString );
        REQUIRE( roundInformation.RoundType == SgfcConstants::NoneValueString );
        REQUIRE( roundInformation.IsValid == false );
      }
    }
  }

  GIVEN( "Two SgfcRoundInformation objects have different values for IsValid" )
  {
    SgfcRoundInformation roundInformation1;
    SgfcRoundInformation roundInformation2 = roundInformation1;
    roundInformation2.IsValid = ! roundInformation2.IsValid;

    WHEN( "The two SgfcRoundInformation objects are compared for equality" )
    {
      bool areEqual = (roundInformation1 == roundInformation2);

      THEN( "The two SgfcRoundInformation objects are not equal" )
      {
        REQUIRE( areEqual == false );
      }
    }

    WHEN( "The two SgfcRoundInformation objects are compared for inequality" )
    {
      bool areNotEqual = (roundInformation1 != roundInformation2);

      THEN( "The two SgfcRoundInformation objects are not equal" )
      {
        REQUIRE( areNotEqual == true );
      }
    }
  }
}

SCENARIO( "An SgfcPropertyType::RO property value is decomposed", "[game]" )
{
  GIVEN( "The property value is valid" )
  {
    auto& testData = GENERATE( from_range(TestDataGenerator::GetValidPropertyValuesRO()) );

    WHEN( "The property value is decomposed" )
    {
      auto decomposedPropertyValue = SgfcRoundInformation::FromPropertyValue(std::get<0>(testData));
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
    auto& testData = GENERATE( from_range(TestDataGenerator::GetInvalidPropertyValuesRO()) );

    WHEN( "The property value is decomposed" )
    {
      auto decomposedPropertyValue = SgfcRoundInformation::FromPropertyValue(testData);

      THEN( "The result of the decomposition is an empty collection" )
      {
        REQUIRE( decomposedPropertyValue.IsValid == false );
      }
    }
  }
}

SCENARIO( "An SgfcPropertyType::RO property value is composed", "[game]" )
{
  GIVEN( "The SgfcRoundInformation object is valid" )
  {
    auto& testData = GENERATE( from_range(TestDataGenerator::GetValidSgfcRoundInformations()) );

    WHEN( "The property value is composed" )
    {
      auto composedPropertyValue = SgfcRoundInformation::ToPropertyValue(std::get<0>(testData));
      auto expectedComposedPropertyValue = std::get<1>(testData);

      THEN( "The result of the composition is an SgfcPropertyType::RO property value" )
      {
        REQUIRE( composedPropertyValue == expectedComposedPropertyValue );
      }
    }
  }

  GIVEN( "The SgfcRoundInformation object is not valid" )
  {
    auto& testData = GENERATE( from_range(TestDataGenerator::GetInvalidSgfcRoundInformations()) );

    WHEN( "The property value is composed" )
    {
      auto composedPropertyValue = SgfcRoundInformation::ToPropertyValue(testData);

      THEN( "The result of the composition is SgfcConstants::NoneValueString" )
      {
        REQUIRE( composedPropertyValue == SgfcConstants::NoneValueString );
      }
    }
  }
}
