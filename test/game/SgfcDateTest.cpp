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
#include <SgfcDate.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcDate is constructed", "[game]" )
{
  GIVEN( "SgfcDate is constructed" )
  {
    WHEN( "SgfcDate is constructed" )
    {
      SgfcDate date;

      THEN( "SgfcDate is constructed successfully" )
      {
        REQUIRE( date.Day == 0 );
        REQUIRE( date.Month == 0 );
        REQUIRE( date.Year == 0 );
        REQUIRE( date.IsPartialDate() == true );
        REQUIRE( date.IsValidCalendarDate() == false );
        REQUIRE( date.IsValidSgfDate() == false );
      }
    }
  }

  GIVEN( "SgfcDate is initialized" )
  {
    WHEN( "SgfcDate is initialized with partial date parts" )
    {
      auto date = GENERATE( SgfcDate { 2020, 1, 0 }, SgfcDate { 2020, 0, 1 }, SgfcDate { 2020, 0, 0 },
                            SgfcDate { 0, 1, 1 }, SgfcDate { 0, 1, 0 },
                            SgfcDate { 0, 0, 1 },
                            SgfcDate { 0, 0, 0} );

      THEN( "IsPartialDate returns true" )
      {
        REQUIRE( date.IsPartialDate() == true );
        REQUIRE( date.IsValidCalendarDate() == false );
      }
    }

    WHEN( "SgfcDate is initialized with valid calendar date parts" )
    {
      auto date = GENERATE( SgfcDate { 2020, 10, 22 }, SgfcDate { 2020, 1, 31 },
                            SgfcDate { 2020, 2, 29 }, SgfcDate { 2000, 2, 29 } );

      THEN( "IsValidCalendarDate returns true" )
      {
        REQUIRE( date.IsPartialDate() == false );
        REQUIRE( date.IsValidCalendarDate() == true );
        REQUIRE( date.IsValidSgfDate() == true );
      }
    }

    WHEN( "SgfcDate is initialized with invalid calendar date parts" )
    {
      auto date = GENERATE( SgfcDate { 2020, 4, 31 }, SgfcDate { 2019, 2, 29 }, SgfcDate { 1900, 2, 29 } );

      THEN( "IsValidCalendarDate returns false" )
      {
        REQUIRE( date.IsPartialDate() == false );
        REQUIRE( date.IsValidCalendarDate() == false );
        REQUIRE( date.IsValidSgfDate() == false );
      }
    }

    WHEN( "SgfcDate is initialized with valid SGF date parts" )
    {
      auto date = GENERATE( SgfcDate { 2020, 2, 29 }, SgfcDate { 0, 2, 29 },
                            SgfcDate { 0, 0, 31 },
                            SgfcDate { 1, 1, 0 } );

      THEN( "IsValidSgfDate returns true" )
      {
        REQUIRE( date.IsValidSgfDate() == true );
      }
    }

    WHEN( "SgfcDate is initialized with invalid SGF date parts" )
    {
      auto date = GENERATE( SgfcDate { 2019, 2, 29 },
                            SgfcDate { 0, 0, 32 },
                            SgfcDate { 2020, 0, 1 }, SgfcDate { 0, 0, 0 },
                            SgfcDate { -1, 1, 1 }, SgfcDate { 1, -1, 1 }, SgfcDate { 1, 1, -1 },
                            SgfcDate { 10000, 1, 1 }, SgfcDate { 1, 13, 1 }, SgfcDate { 1, 1, 32 } );

      THEN( "IsValidSgfDate returns true" )
      {
        REQUIRE( date.IsValidCalendarDate() == false );
        REQUIRE( date.IsValidSgfDate() == false );
      }
    }
  }
}

SCENARIO( "An SgfcPropertyType::DT property value is decomposed", "[game]" )
{
  GIVEN( "The property value is valid" )
  {
    auto& testData = GENERATE( from_range(TestDataGenerator::GetValidPropertyValuesDT()) );

    WHEN( "The property value is decomposed" )
    {
      auto decomposedPropertyValue = SgfcDate::FromPropertyValue(std::get<0>(testData));
      auto expectedDecomposedPropertyValue = std::get<1>(testData);

      THEN( "The result of the decomposition are SgfcDate objects" )
      {
        REQUIRE( decomposedPropertyValue.size() == expectedDecomposedPropertyValue.size() );
        REQUIRE( decomposedPropertyValue == expectedDecomposedPropertyValue );
        for (auto date : decomposedPropertyValue)
        {
          // The test data should only contain valid SGF dates, but let's
          // make a double-check. This also has the side-effect of exercising
          // IsValidSgfDate().
          REQUIRE( date.IsValidSgfDate() );
        }
      }
    }
  }

  GIVEN( "The property value is not valid" )
  {
    auto& testData = GENERATE( from_range(TestDataGenerator::GetInvalidPropertyValuesDT()) );

    WHEN( "The property value is decomposed" )
    {
      auto decomposedPropertyValue = SgfcDate::FromPropertyValue(testData);
      
      THEN( "The result of the decomposition is an empty collection" )
      {
        REQUIRE( decomposedPropertyValue.size() == 0 );
      }
    }
  }
}

SCENARIO( "An SgfcPropertyType::DT property value is composed", "[game]" )
{
  GIVEN( "The SgfcDate objects are valid" )
  {
    auto& testData = GENERATE( from_range(TestDataGenerator::GetValidSgfcDates()) );

    WHEN( "The property value is composed" )
    {
      auto composedPropertyValue = SgfcDate::ToPropertyValue(std::get<0>(testData));
      auto expectedComposedPropertyValue = std::get<1>(testData);

      THEN( "The result of the composition is an SgfcPropertyType::DT property value" )
      {
        REQUIRE( composedPropertyValue == expectedComposedPropertyValue );
      }
    }
  }

  GIVEN( "The SgfcDate objects are not valid" )
  {
    auto& testData = GENERATE( from_range(TestDataGenerator::GetInvalidSgfcDates()) );

    WHEN( "The property value is composed" )
    {
      auto composedPropertyValue = SgfcDate::ToPropertyValue(testData);

      THEN( "The result of the composition is SgfcConstants::NoneValueString" )
      {
        REQUIRE( composedPropertyValue == SgfcConstants::NoneValueString );
      }
    }
  }
}
