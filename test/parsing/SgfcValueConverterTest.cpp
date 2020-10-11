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
#include <parsing/SgfcValueConverter.h>
#include <SgfcConstants.h>

// Unit test library includes
#include <catch2/catch.hpp>

// C++ Standard Library includes
#include <utility>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcValueConverter is constructed", "[parsing]" )
{
  GIVEN( "The default constructor is used" )
  {
    WHEN( "SgfcValueConverter is constructed" )
    {
      THEN( "SgfcValueConverter is constructed successfully" )
      {
        REQUIRE_NOTHROW( SgfcValueConverter() );
      }
    }
  }
}

SCENARIO( "SgfcValueConverter converts between string and SgfcNumber", "[parsing]" )
{
  SgfcValueConverter valueConverter;
  SgfcNumber convertedNumberValue;
  std::string typeConversionErrorMessage;

  GIVEN( "The converter receives a valid Number string for conversion" )
  {
    auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetValidNumberStrings()) );

    WHEN( "SgfcValueConverter tries to convert the string" )
    {
      bool conversionResult = valueConverter.TryConvertStringToNumberValue(
        testData.first, convertedNumberValue, typeConversionErrorMessage);

      THEN( "SgfcValueConverter succeeds with the conversion" )
      {
        REQUIRE( conversionResult == true );
        REQUIRE( convertedNumberValue == testData.second );
        REQUIRE( typeConversionErrorMessage.size() == 0 );
      }
    }
  }

  GIVEN( "The converter receives an invalid Number string for conversion" )
  {
    auto stringValue = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidNumberStrings()) );

    WHEN( "SgfcValueConverter tries to convert the string" )
    {
      bool conversionResult = valueConverter.TryConvertStringToNumberValue(
        stringValue, convertedNumberValue, typeConversionErrorMessage);

      THEN( "SgfcValueConverter fails with the conversion" )
      {
        REQUIRE( conversionResult == false );
        REQUIRE( typeConversionErrorMessage.size() > 0 );
      }
    }
  }

  GIVEN( "The converter receives a Number value for conversion" )
  {
    auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetNumberValues()) );

    WHEN( "SgfcValueConverter tries to convert the Number value" )
    {
      auto stringValue = valueConverter.ConvertNumberValueToString(testData.first);

      THEN( "SgfcValueConverter succeeds with the conversion" )
      {
        REQUIRE( stringValue == testData.second );
      }
    }
  }
}

SCENARIO( "SgfcValueConverter converts between string and SgfcReal", "[parsing]" )
{
  SgfcValueConverter valueConverter;
  SgfcReal convertedRealValue;
  std::string typeConversionErrorMessage;

  GIVEN( "The converter receives a valid Real string for conversion" )
  {
    auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetValidRealStrings()) );

    WHEN( "SgfcValueConverter tries to convert the string" )
    {
      bool conversionResult = valueConverter.TryConvertStringToRealValue(
        testData.first, convertedRealValue, typeConversionErrorMessage);

      THEN( "SgfcValueConverter succeeds with the conversion" )
      {
        REQUIRE( conversionResult == true );
        REQUIRE( convertedRealValue == testData.second );
        REQUIRE( typeConversionErrorMessage.size() == 0 );
      }
    }
  }

  GIVEN( "The converter receives an invalid Real string for conversion" )
  {
    auto stringValue = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidRealStrings()) );

    WHEN( "SgfcValueConverter tries to convert the string" )
    {
      bool conversionResult = valueConverter.TryConvertStringToRealValue(
        stringValue, convertedRealValue, typeConversionErrorMessage);

      THEN( "SgfcValueConverter fails with the conversion" )
      {
        REQUIRE( conversionResult == false );
        REQUIRE( typeConversionErrorMessage.size() > 0 );
      }
    }
  }

  GIVEN( "The converter receives a Real value for conversion" )
  {
    auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetRealValues()) );

    WHEN( "SgfcValueConverter tries to convert the Real value" )
    {
      auto stringValue = valueConverter.ConvertRealValueToString(testData.first);

      THEN( "SgfcValueConverter succeeds with the conversion" )
      {
        REQUIRE( stringValue == testData.second );
      }
    }
  }
}

SCENARIO( "SgfcValueConverter converts between string and SgfcDouble", "[parsing]" )
{
  SgfcValueConverter valueConverter;
  SgfcDouble convertedDoubleValue;
  std::string typeConversionErrorMessage;

  GIVEN( "The converter receives a valid Double string for conversion" )
  {
    auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetValidDoubleStrings()) );

    WHEN( "SgfcValueConverter tries to convert the string" )
    {
      bool conversionResult = valueConverter.TryConvertStringToDoubleValue(
        testData.first, convertedDoubleValue, typeConversionErrorMessage);

      THEN( "SgfcValueConverter succeeds with the conversion" )
      {
        REQUIRE( conversionResult == true );
        REQUIRE( convertedDoubleValue == testData.second );
        REQUIRE( typeConversionErrorMessage.size() == 0 );
      }
    }
  }

  GIVEN( "The converter receives an invalid Double string for conversion" )
  {
    auto stringValue = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidDoubleStrings()) );

    WHEN( "SgfcValueConverter tries to convert the string" )
    {
      bool conversionResult = valueConverter.TryConvertStringToDoubleValue(
        stringValue, convertedDoubleValue, typeConversionErrorMessage);

      THEN( "SgfcValueConverter fails with the conversion" )
      {
        REQUIRE( conversionResult == false );
        REQUIRE( typeConversionErrorMessage.size() > 0 );
      }
    }
  }

  GIVEN( "The converter receives a Double value for conversion" )
  {
    auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetDoubleValues()) );

    WHEN( "SgfcValueConverter tries to convert the Real value" )
    {
      auto stringValue = valueConverter.ConvertDoubleValueToString(testData.first);

      THEN( "SgfcValueConverter succeeds with the conversion" )
      {
        REQUIRE( stringValue == testData.second );
      }
    }
  }
}

SCENARIO( "SgfcValueConverter converts between string and SgfcColor", "[parsing]" )
{
  SgfcValueConverter valueConverter;
  SgfcColor convertedColorValue;
  std::string typeConversionErrorMessage;

  GIVEN( "The converter receives a valid Color string for conversion" )
  {
    auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetValidColorStrings()) );

    WHEN( "SgfcValueConverter tries to convert the string" )
    {
      bool conversionResult = valueConverter.TryConvertStringToColorValue(
        testData.first, convertedColorValue, typeConversionErrorMessage);

      THEN( "SgfcValueConverter succeeds with the conversion" )
      {
        REQUIRE( conversionResult == true );
        REQUIRE( convertedColorValue == testData.second );
        REQUIRE( typeConversionErrorMessage.size() == 0 );
      }
    }
  }

  GIVEN( "The converter receives an invalid Color string for conversion" )
  {
    auto stringValue = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidColorStrings()) );

    WHEN( "SgfcValueConverter tries to convert the string" )
    {
      bool conversionResult = valueConverter.TryConvertStringToColorValue(
        stringValue, convertedColorValue, typeConversionErrorMessage);

      THEN( "SgfcValueConverter fails with the conversion" )
      {
        REQUIRE( conversionResult == false );
        REQUIRE( typeConversionErrorMessage.size() > 0 );
      }
    }
  }

  GIVEN( "The converter receives a Color value for conversion" )
  {
    auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetColorValues()) );

    WHEN( "SgfcValueConverter tries to convert the Real value" )
    {
      auto stringValue = valueConverter.ConvertColorValueToString(testData.first);

      THEN( "SgfcValueConverter succeeds with the conversion" )
      {
        REQUIRE( stringValue == testData.second );
      }
    }
  }
}
