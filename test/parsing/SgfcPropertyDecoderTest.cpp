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
#include <ISgfcColorPropertyValue.h>
#include <ISgfcComposedPropertyValue.h>
#include <ISgfcDoublePropertyValue.h>
#include <ISgfcGoMove.h>
#include <ISgfcGoMovePropertyValue.h>
#include <ISgfcGoPoint.h>
#include <ISgfcGoPointPropertyValue.h>
#include <ISgfcGoStone.h>
#include <ISgfcGoStonePropertyValue.h>
#include <ISgfcMovePropertyValue.h>
#include <ISgfcNumberPropertyValue.h>
#include <ISgfcPointPropertyValue.h>
#include <ISgfcRealPropertyValue.h>
#include <ISgfcSimpleTextPropertyValue.h>
#include <ISgfcSinglePropertyValue.h>
#include <ISgfcStonePropertyValue.h>
#include <ISgfcTextPropertyValue.h>
#include <SgfcConstants.h>
#include <parsing/SgfcPropertyDecoder.h>
#include <SgfcUtility.h>

// SGFC includes
extern "C"
{
  #include <../sgfc/src/all.h>
  #include <../sgfc/src/protos.h>
}

// Unit test library includes
#include <catch2/catch.hpp>

// C++ Standard Library includes
#include <utility>

using namespace LibSgfcPlusPlus;


void AssertValidNumberString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& expectedRawValue, SgfcNumber expectedNumberValue);
void AssertInvalidNumberString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& expectedRawValue);
void AssertValidSimpleTextString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& expectedRawValue, const SgfcSimpleText& expectedParsedValue);
void AssertValidPointString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& rawValue, const SgfcPoint& pointValue);
void AssertValidStoneString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& rawValue, const SgfcStone& stoneValue);
void AssertValidGoPointStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcPoint& pointValue, int xPosition, int yPosition);
void AssertValidGoPointString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& rawValue, const SgfcPoint& pointValue, int xPosition, int yPosition);
void AssertInvalidGoPointStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcPoint& pointValue);
void AssertInvalidGoPointString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& rawValue, const SgfcPoint& pointValue);
void AssertValidGoMoveStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcMove& moveValue, int xPosition, int yPosition);
void AssertValidGoMoveStrings(const ISgfcSinglePropertyValue* propertySingleValue, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcMove& moveValue, int xPosition, int yPosition);
void AssertValidMoveStrings(const ISgfcSinglePropertyValue* propertySingleValue, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcMove& moveValue);
void AssertInvalidGoMoveStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcMove& moveValue);
void AssertValidGoStoneStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& rawValue, const std::string& stoneValue, int xPosition, int yPosition);
void AssertInvalidGoStoneStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& rawValue, const std::string& stoneValue);
void AssertDecodeOfPropertyValueFailsWhenNoValueIsGiven(const std::string& propertyID, SgfcPropertyType propertyType);
void AssertDecodeOfSinglePropertyValueFailsWhenSecondValueIsGiven(const std::string& propertyID, SgfcPropertyType propertyType, const std::string& rawPropertyValue, const std::string& rawPropertyValue2);
void AssertDecodeOfComposedPropertyValueFailsWhenNoSecondValueIsGiven(const std::string& propertyID, SgfcPropertyType propertyType, const std::string& rawPropertyValue);


// General structure of tests that exercise
// SgfcPropertyDecoder::GetPropertyValue():
// - One SCENARIO for each group of value type descriptor. The grouping of value
//   type descriptors can be seen in SgfcPropertyMetaInfo.cpp: This file
//   contains a lot of constant definitions near the top, those constants are
//   grouped into sections of related value type descriptors.
//   - One GIVEN for each concrete value type descriptor. Again, see the list of
//     constants defined in SgfcPropertyMetaInfo.cpp for value type descriptors
//     that are tested. Basically these are things that are actually described
//     somewhere in the SGF standard. For instance, a composed value type that
//     consists of a combination of the Number and Real basic value types is
//     never described in the SGF standard, so there is no value type descriptor
//     for it and therefore we don't test it here.
//     - At least one WHEN for valid values and one WHEN for invalid values
//       of the basic value type. Possibly additional WHEN for cases where a
//       special test setup is required. Typically the WHEN uses a data
//       generator to produce different valid/invalid values
//       - One THEN for each WHEN that contains the actual assertions
// - Reusable helper functions with assertions to be invoked from THEN

SCENARIO( "SgfcPropertyDecoder is constructed", "[parsing]" )
{
  token propertyId = TKN_AB;
  std::string propertyName = "AB";

  PropValue propertyValue;

  Property sgfProperty;
  sgfProperty.id = propertyId;
  sgfProperty.idstr = const_cast<char*>(propertyName.c_str());
  sgfProperty.value = &propertyValue;

  SgfcGameType gameType = SgfcGameType::Go;
  SgfcBoardSize boardSize = { 19, 19 };

  GIVEN( "The SgfcPropertyDecoder constructor is used" )
  {
    WHEN( "SgfcPropertyDecoder is constructed with valid data" )
    {
      THEN( "SgfcPropertyDecoder is constructed successfully" )
      {
        REQUIRE_NOTHROW( SgfcPropertyDecoder(&sgfProperty, gameType, boardSize) );
      }
    }

    WHEN( "SgfcPropertyDecoder is constructed with a nullptr Property object" )
    {
      THEN( "The SgfcPropertyDecoder constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder(nullptr, gameType, boardSize),
          std::domain_error);
      }
    }

    WHEN( "SgfcPropertyDecoder is constructed with a nullptr ID string" )
    {
      sgfProperty.idstr = nullptr;

      THEN( "The SgfcPropertyDecoder constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder(&sgfProperty, gameType, boardSize),
          std::domain_error);
      }
    }

    WHEN( "SgfcPropertyDecoder is constructed with a nullptr PropValue object" )
    {
      sgfProperty.value = nullptr;

      THEN( "The SgfcPropertyDecoder constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder(&sgfProperty, gameType, boardSize),
          std::domain_error);
      }
    }

    WHEN( "SgfcPropertyDecoder is constructed with mismatching ID string and ID enumeration value" )
    {
      sgfProperty.id = TKN_SZ;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder uses the ID string value to determine the property type" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::AB );
        REQUIRE( propertyDecoder.GetPropertyName() == propertyName );
      }
    }

    WHEN( "SgfcPropertyDecoder is constructed with an ID string value that is not known" )
    {
      // The ID string value is not known even if it doesn't match case
      std::string propertyName2 = GENERATE( "", "ab", "XX", "foo" );
      sgfProperty.idstr = const_cast<char*>(propertyName2.c_str());
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder converts the ID string value to property type Unknown" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::Unknown );
        REQUIRE( propertyDecoder.GetPropertyName() == propertyName2 );
      }
    }

    WHEN( "SgfcPropertyDecoder is constructed with any of the known ID string values" )
    {
      auto mapEntry = GENERATE( from_range(SgfcConstants::PropertyNameToPropertyTypeMap) );
      sgfProperty.idstr = const_cast<char*>(mapEntry.first.c_str());
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder converts the ID string value to a matching property type" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == mapEntry.second );
        REQUIRE( propertyDecoder.GetPropertyName() == mapEntry.first );
      }
    }
  }
}

SCENARIO( "SgfcPropertyDecoder probes an SGF node for a property of type SgfcPropertyType::GM", "[parsing]" )
{
  // Use a game type that is different from SgfcConstants::DefaultGameType so
  // that tests can notice an error in the "default game type" logic
  SgfcGameType expectedGameType = SgfcGameType::Backgammon;
  SgfcNumber expectedGameTypeAsNumber = 6;
  std::string expectedGameTypeAsNumberString = "6";

  PropValue sgfPropertyValueGM;
  sgfPropertyValueGM.value = const_cast<char*>(expectedGameTypeAsNumberString.c_str());
  sgfPropertyValueGM.value2 = nullptr;
  sgfPropertyValueGM.next = nullptr;

  Property sgfPropertyGM;
  sgfPropertyGM.idstr = const_cast<char*>("GM");
  sgfPropertyGM.value = &sgfPropertyValueGM;
  sgfPropertyGM.next = nullptr;

  PropValue sgfPropertyValueSZ;
  // We intentionally don't set up the property value to show that probing
  // completely ignores the property if it doesn't have the right type
  sgfPropertyValueSZ.value = nullptr;
  sgfPropertyValueSZ.value2 = nullptr;
  sgfPropertyValueSZ.next = nullptr;

  Property sgfPropertySZ;
  sgfPropertySZ.idstr = const_cast<char*>("SZ");
  sgfPropertySZ.value = &sgfPropertyValueSZ;
  sgfPropertySZ.next = &sgfPropertyGM;

  Node sgfNode;
  sgfNode.prop = &sgfPropertySZ;

  GIVEN( "SgfcPropertyDecoder attempts to probe an invalid SGF Node or Property object" )
  {
    WHEN( "SgfcPropertyDecoder attempts to probe a nullptr SGF Node object" )
    {
      THEN( "Probing throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder::GetGameTypeFromNode(nullptr),
          std::domain_error);
      }
    }

    WHEN( "SgfcPropertyDecoder attempts to probe an SGF Property object which is of type SgfcPropertyType::GM, but without an SGF PropValue object" )
    {
      sgfPropertyGM.value = nullptr;

      THEN( "Probing throws an exception" )
      {
        // The exception is thrown by the SgfcPropertyDecoder constructor
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder::GetGameTypeFromNode(&sgfNode),
          std::domain_error);
      }
    }

    WHEN( "SgfcPropertyDecoder attempts to probe an SGF Property object which is of type SgfcPropertyType::GM, with an SGF PropValue object that has no value string" )
    {
      sgfPropertyValueGM.value = nullptr;

      THEN( "Probing throws an exception" )
      {
        // The exception is thrown by SgfcPropertyDecoder::GetPropertyValues
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder::GetGameTypeFromNode(&sgfNode),
          std::domain_error);
      }
    }

    WHEN( "SgfcPropertyDecoder probes a GM property that has a value that is not a Number value" )
    {
      std::vector<const char*> v = { SgfcConstants::NoneValueString.c_str(), "foo" };
      sgfPropertyValueGM.value = const_cast<char*>(GENERATE_COPY( from_range(v) ));

      THEN( "Probing throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder::GetGameTypeFromNode(&sgfNode),
          std::domain_error);
      }
    }

    WHEN( "SgfcPropertyDecoder probes a GM property that has a second value" )
    {
      sgfPropertyValueGM.value2 = const_cast<char*>(expectedGameTypeAsNumberString.c_str());

      THEN( "Probing throws an exception" )
      {
        // The exception is thrown by SgfcPropertyDecoder::GetPropertyValues
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder::GetGameTypeFromNode(&sgfNode),
          std::domain_error);
      }
    }
  }

  GIVEN( "SgfcPropertyDecoder probes a valid SGF Node and property object" )
  {
    WHEN( "SgfcPropertyDecoder probes an SGF Node object without an SGF property object" )
    {
      sgfNode.prop = nullptr;

      THEN( "Probing returns SgfcConstants::DefaultGameType" )
      {
        REQUIRE( SgfcPropertyDecoder::GetGameTypeFromNode(&sgfNode) == SgfcConstants::DefaultGameType );
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SGF Node object with a single SGF property object that is not of type SgfcPropertyType::GM" )
    {
      sgfPropertySZ.next = nullptr;

      THEN( "Probing returns SgfcConstants::DefaultGameType" )
      {
        REQUIRE( SgfcPropertyDecoder::GetGameTypeFromNode(&sgfNode) == SgfcConstants::DefaultGameType );
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SGF Node object with a single SGF property object that is of type SgfcPropertyType::GM" )
    {
      sgfNode.prop = &sgfPropertyGM;

      THEN( "Probing returns the game type that corresponds to the property value" )
      {
        REQUIRE( SgfcPropertyDecoder::GetGameTypeFromNode(&sgfNode) == expectedGameType );
      }
    }

    WHEN( "SgfcPropertyDecoder probes a Node object with multiple SGF property objects, one of which is of type SgfcPropertyType::GM" )
    {
      THEN( "Probing returns the game type that corresponds to the value of the property which is of type SgfcPropertyType::GM" )
      {
        REQUIRE( SgfcPropertyDecoder::GetGameTypeFromNode(&sgfNode) == expectedGameType );
      }
    }

    WHEN( "SgfcPropertyDecoder probes a GM property that has a value not defined in the SGF standard" )
    {
      std::vector<const char*> v = { "-1", "0", "1000" };
      sgfPropertyValueGM.value = const_cast<char*>(GENERATE_COPY( from_range(v) ));

      THEN( "Probing returns SgfcGameType::Unknown" )
      {
        REQUIRE( SgfcPropertyDecoder::GetGameTypeFromNode(&sgfNode) == SgfcGameType::Unknown );
      }
    }
  }
}

SCENARIO( "SgfcPropertyDecoder probes an SGF node for a property of type SgfcPropertyType::SZ", "[parsing]" )
{
  // Use a board size that is different from SgfcConstants::BoardSizeDefaultGo
  // and SgfcConstants::BoardSizeDefaultChess so that tests can notice an error
  // in the "default board size" logic
  SgfcBoardSize expectedBoardSizeSquare = { 11, 11 };
  SgfcNumber expectedBoardSizeSquareAsNumber = 11;
  std::string expectedBoardSizeSquareAsNumberString = "11";
  SgfcBoardSize expectedBoardSizeRectangular = { 6, 13 };
  SgfcNumber expectedBoardSizeRectangularAsNumber1 = 6;
  SgfcNumber expectedBoardSizeRectangularAsNumber2 = 13;
  std::string expectedBoardSizeRectangularAsNumberString1 = "6";
  std::string expectedBoardSizeRectangularAsNumberString2 = "13";

  PropValue sgfPropertyValueSZSquare;
  sgfPropertyValueSZSquare.value = const_cast<char*>(expectedBoardSizeSquareAsNumberString.c_str());
  sgfPropertyValueSZSquare.value2 = nullptr;
  sgfPropertyValueSZSquare.next = nullptr;

  PropValue sgfPropertyValueSZRectangular;
  sgfPropertyValueSZRectangular.value = const_cast<char*>(expectedBoardSizeRectangularAsNumberString1.c_str());
  sgfPropertyValueSZRectangular.value2 = const_cast<char*>(expectedBoardSizeRectangularAsNumberString2.c_str());;
  sgfPropertyValueSZRectangular.next = nullptr;

  Property sgfPropertySZ;
  sgfPropertySZ.idstr = const_cast<char*>("SZ");
  sgfPropertySZ.value = &sgfPropertyValueSZSquare;
  sgfPropertySZ.next = nullptr;

  PropValue sgfPropertyValueGM;
  // We intentionally don't set up the property value to show that probing
  // completely ignores the property if it doesn't have the right type
  sgfPropertyValueGM.value = nullptr;
  sgfPropertyValueGM.value2 = nullptr;
  sgfPropertyValueGM.next = nullptr;

  Property sgfPropertyGM;
  sgfPropertyGM.idstr = const_cast<char*>("GM");
  sgfPropertyGM.value = &sgfPropertyValueGM;
  sgfPropertyGM.next = &sgfPropertySZ;

  Node sgfNode;
  sgfNode.prop = &sgfPropertyGM;

  GIVEN( "SgfcPropertyDecoder attempts to probe an invalid SGF Node or Property object" )
  {
    WHEN( "SgfcPropertyDecoder attempts to probe a nullptr SGF Node object" )
    {
      THEN( "Probing throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder::GetBoardSizeFromNode(nullptr, SgfcGameType::Go),
          std::domain_error);
      }
    }

    WHEN( "SgfcPropertyDecoder attempts to probe an SGF Property object which is of type SgfcPropertyType:SZ, but without an SGF PropValue object" )
    {
      sgfPropertyValueSZSquare.value = nullptr;

      THEN( "Probing throws an exception" )
      {
        // The exception is thrown by the SgfcPropertyDecoder constructor
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, SgfcGameType::Go),
          std::domain_error);
      }
    }

    WHEN( "SgfcPropertyDecoder attempts to probe an SGF Property object which is of type SgfcPropertyType::SZ, with an SGF PropValue object that has no value string" )
    {
      sgfPropertyValueSZSquare.value = nullptr;

      THEN( "Probing throws an exception" )
      {
        // The exception is thrown by SgfcPropertyDecoder::GetPropertyValues
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, SgfcGameType::Go),
          std::domain_error);
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SZ property that has a single value that is not a Number value" )
    {
      std::vector<const char*> v = { SgfcConstants::NoneValueString.c_str(), "foo" };
      sgfPropertyValueSZSquare.value = const_cast<char*>(GENERATE_COPY( from_range(v) ));

      THEN( "Probing throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, SgfcGameType::Go),
          std::domain_error);
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SZ property that has a composed value of which the first value is not a Number value" )
    {
      sgfPropertySZ.value = &sgfPropertyValueSZRectangular;

      std::vector<const char*> v = { SgfcConstants::NoneValueString.c_str(), "foo" };
      sgfPropertyValueSZRectangular.value = const_cast<char*>(GENERATE_COPY( from_range(v) ));

      THEN( "Probing throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, SgfcGameType::Go),
          std::domain_error);
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SZ property that has a composed value of which the second value is not a Number value" )
    {
      sgfPropertySZ.value = &sgfPropertyValueSZRectangular;

      std::vector<const char*> v = { SgfcConstants::NoneValueString.c_str(), "foo" };
      sgfPropertyValueSZRectangular.value2 = const_cast<char*>(GENERATE_COPY( from_range(v) ));

      THEN( "Probing throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, SgfcGameType::Go),
          std::domain_error);
      }
    }
  }

  GIVEN( "SgfcPropertyDecoder probes a valid SGF Node and property object" )
  {
    // This test case covers SgfcConstants::BoardSizeDefaultGo,
    // SgfcConstants::BoardSizeDefaultChess or SgfcConstants::BoardSizeNone
    // being returned if the property is missing
    WHEN( "SgfcPropertyDecoder probes an SGF Node object without an SGF property object" )
    {
      sgfNode.prop = nullptr;

      auto mapEntry = GENERATE( from_range(SgfcConstants::GameTypeToGameTypeAsNumberMap) );
      auto gameType = mapEntry.first;
      auto expectedBoardSize = SgfcUtility::GetDefaultBoardSize(gameType);

      THEN( "Probing returns the default board size for the game type as specified by the SGF standard" )
      {
        REQUIRE( SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, gameType) == expectedBoardSize );
      }
    }

    // This test case covers SgfcConstants::BoardSizeDefaultGo,
    // SgfcConstants::BoardSizeDefaultChess or SgfcConstants::BoardSizeNone
    // being returned if the property is missing
    WHEN( "SgfcPropertyDecoder probes an SGF Node object with a single SGF property object that is not of type SgfcPropertyType::SZ" )
    {
      sgfPropertyGM.next = nullptr;

      auto mapEntry = GENERATE( from_range(SgfcConstants::GameTypeToGameTypeAsNumberMap) );
      auto gameType = mapEntry.first;
      auto expectedBoardSize = SgfcUtility::GetDefaultBoardSize(gameType);

      THEN( "Probing returns the default board size for the game type as specified by the SGF standard" )
      {
        REQUIRE( SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, gameType) == expectedBoardSize );
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SGF Node object with a single SGF property object that is of type SgfcPropertyType::SZ" )
    {
      sgfNode.prop = &sgfPropertySZ;

      THEN( "Probing returns the board size type that corresponds to the property value" )
      {
        REQUIRE( SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, SgfcGameType::Go) == expectedBoardSizeSquare );
      }
    }

    WHEN( "SgfcPropertyDecoder probes a Node object with multiple SGF property objects, one of which is of type SgfcPropertyType::SZ" )
    {
      THEN( "Probing returns the game type that corresponds to the value of the property which is of type SgfcPropertyType:SZ" )
      {
        REQUIRE( SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, SgfcGameType::Go) == expectedBoardSizeSquare );
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SZ property that has a single value" )
    {
      THEN( "Probing returns a square board size value" )
      {
        REQUIRE( SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, SgfcGameType::Go) == expectedBoardSizeSquare );
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SZ property that has a composed value and the game type is Go" )
    {
      sgfPropertySZ.value = &sgfPropertyValueSZRectangular;

      THEN( "Probing returns a rectangular board size value" )
      {
        REQUIRE( SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, SgfcGameType::Go) == expectedBoardSizeRectangular );
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SZ property that has a composed value and the game type is not Go" )
    {
      sgfPropertySZ.value = &sgfPropertyValueSZRectangular;

      THEN( "Probing returns a rectangular board size value" )
      {
        REQUIRE( SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, SgfcGameType::Dvonn) == expectedBoardSizeRectangular );
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SZ property that has a single valid value" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetValidSZSquareStrings()) );

      // Need a local string variable so that we can store a reference to its
      // c_str() in the PropValue object
      auto szString = std::get<0>(testData);
      sgfPropertyValueSZSquare.value = const_cast<char*>(szString.c_str());

      THEN( "Probing returns a square board size value" )
      {
        REQUIRE( SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, std::get<1>(testData)) == std::get<2>(testData) );
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SZ property that has a single invalid value" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidSZSquareStrings()) );

      // Need a local string variable so that we can store a reference to its
      // c_str() in the PropValue object
      auto szString = std::get<0>(testData);
      sgfPropertyValueSZSquare.value = const_cast<char*>(szString.c_str());

      THEN( "Probing returns SgfcConstants::BoardSizeInvalid" )
      {
        REQUIRE( SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, std::get<1>(testData)) == SgfcConstants::BoardSizeInvalid );
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SZ property that has a composed valid value" )
    {
      sgfPropertySZ.value = &sgfPropertyValueSZRectangular;

      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetValidSZRectangularStrings()) );

      // Need local string variables so that we can store a reference to their
      // c_str() in the PropValue object
      auto szString1 = std::get<0>(testData);
      auto szString2 = std::get<1>(testData);
      sgfPropertyValueSZRectangular.value = const_cast<char*>(szString1.c_str());
      sgfPropertyValueSZRectangular.value2 = const_cast<char*>(szString2.c_str());

      THEN( "Probing returns a rectangular board size value" )
      {
        REQUIRE( SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, std::get<2>(testData)) == std::get<3>(testData) );
      }
    }

    WHEN( "SgfcPropertyDecoder probes an SZ property that has a composed invalid value" )
    {
      sgfPropertySZ.value = &sgfPropertyValueSZRectangular;

      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidSZRectangularStrings()) );

      // Need local string variables so that we can store a reference to their
      // c_str() in the PropValue object
      auto szString1 = std::get<0>(testData);
      auto szString2 = std::get<1>(testData);
      sgfPropertyValueSZRectangular.value = const_cast<char*>(szString1.c_str());
      sgfPropertyValueSZRectangular.value2 = const_cast<char*>(szString2.c_str());

      THEN( "Probing returns SgfcConstants::BoardSizeInvalid" )
      {
        REQUIRE( SgfcPropertyDecoder::GetBoardSizeFromNode(&sgfNode, std::get<2>(testData)) == SgfcConstants::BoardSizeInvalid );
      }
    }
  }
}

SCENARIO( "SgfcPropertyDecoder is constructed with a property that is a basic value type", "[parsing]" )
{
  SgfcGameType gameType = SgfcGameType::Go;
  SgfcBoardSize boardSize = { 19, 19 };

  WHEN( "The SGF property object has no value (an SGFC interfacing error)" )
  {
    THEN( "SgfcPropertyDecoder fails to decode the property value" )
    {
      // We use property "DO" because this has a value type None, but even
      // value type None requires that a value is present (an empty string).
      AssertDecodeOfPropertyValueFailsWhenNoValueIsGiven("DO", SgfcPropertyType::DO);
    }
  }

  WHEN( "The SGF property object has a second value (an SGFC interfacing error)" )
  {
    THEN( "SgfcPropertyDecoder fails to decode the property value" )
    {
      // Property "MN" has value type Number, so we provide two valid Number
      // strings. Decoding must fail because all basic value types are single
      // value.
      AssertDecodeOfSinglePropertyValueFailsWhenSecondValueIsGiven("MN", SgfcPropertyType::MN, "42", "17");
    }
  }

  GIVEN( "The property value type is None" )
  {
    WHEN( "The property value is decoded" )
    {
      PropValue propertyValue;
      // SGF defines the None value type to be an empty string. We add an
      // arbitrary string to the list of values because we expect
      // SgfcPropertyDecoder to ignore any property values when the property
      // type mandates value type None.
      std::vector<const char*> v = { SgfcConstants::NoneValueString.c_str(), "foo" };
      propertyValue.value = const_cast<char*>(GENERATE_COPY( from_range(v) ));
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("DO");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder returns an empty list of property values" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::DO );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 0 );
      }
    }
  }

  GIVEN( "The property value type is Number" )
  {
    WHEN( "The property value is a valid Number string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetValidNumberStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(testData.first.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("MN");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the Number string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::MN );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        AssertValidNumberString(propertySingleValue, testData.first, testData.second);
      }
    }

    WHEN( "The property value is an invalid Number string" )
    {
      auto stringValue = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidNumberStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(stringValue.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("MN");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Number string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::MN );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        AssertInvalidNumberString(propertySingleValue, stringValue);
      }
    }
  }

  GIVEN( "The property value type is Real" )
  {
    WHEN( "The property value is a valid Real string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetValidRealStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(testData.first.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("TM");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the Real string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::TM );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == testData.first );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Real );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto realValue = propertySingleValue->ToRealValue();
        REQUIRE( realValue != nullptr );
        REQUIRE( realValue->GetRealValue() == testData.second );
      }
    }

    WHEN( "The property value is an invalid Real string" )
    {
      auto stringValue = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidRealStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(stringValue.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("TM");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Real string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::TM );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == stringValue );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() > 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Real );
        REQUIRE( propertySingleValue->HasTypedValue() == false );
        auto realValue = propertySingleValue->ToRealValue();
        REQUIRE( realValue == nullptr );
      }
    }
  }

  GIVEN( "The property value type is Double" )
  {
    WHEN( "The property value is a valid Double string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetValidDoubleStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(testData.first.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("DM");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the Double string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::DM );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == testData.first );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Double );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto doubleValue = propertySingleValue->ToDoubleValue();
        REQUIRE( doubleValue != nullptr );
        REQUIRE( doubleValue->GetDoubleValue() == testData.second );
      }
    }

    WHEN( "The property value is an invalid Double string" )
    {
      auto stringValue = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidDoubleStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(stringValue.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("DM");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Double string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::DM );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == stringValue );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() > 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Double );
        REQUIRE( propertySingleValue->HasTypedValue() == false );
        auto doubleValue = propertySingleValue->ToDoubleValue();
        REQUIRE( doubleValue == nullptr );
      }
    }
  }

  GIVEN( "The property value type is Color" )
  {
    WHEN( "The property value is a valid Color string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetValidColorStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(testData.first.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("PL");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the Color string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::PL );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == testData.first );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Color );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto colorValue = propertySingleValue->ToColorValue();
        REQUIRE( colorValue != nullptr );
        REQUIRE( colorValue->GetColorValue() == testData.second );
      }
    }

    WHEN( "The property value is an invalid Color string" )
    {
      auto stringValue = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidColorStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(stringValue.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("PL");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Color string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::PL );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == stringValue );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() > 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Color );
        REQUIRE( propertySingleValue->HasTypedValue() == false );
        auto colorValue = propertySingleValue->ToColorValue();
        REQUIRE( colorValue == nullptr );
      }
    }
  }

  GIVEN( "The property value type is SimpleText" )
  {
    WHEN( "The property value is a valid SimpleText string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetSimpleTextStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(std::get<0>(testData).c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("N");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);
      propertyDecoder.SetEscapeProcessingEnabled(true);

      THEN( "SgfcPropertyDecoder successfully decodes the SimpleText string" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::N );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();

        AssertValidSimpleTextString(propertySingleValue, std::get<0>(testData), std::get<1>(testData));
      }
    }

    WHEN( "The property value is an invalid SimpleText string" )
    {
      // No tests because there are no invalid SimpleText strings
    }
  }

  GIVEN( "The property value type is Text" )
  {
    WHEN( "The property value is a valid Text string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetTextStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(std::get<0>(testData).c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("GC");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);
      propertyDecoder.SetEscapeProcessingEnabled(true);

      THEN( "SgfcPropertyDecoder successfully decodes the Text string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::GC );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == std::get<0>(testData) );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Text );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto textValue = propertySingleValue->ToTextValue();
        REQUIRE( textValue != nullptr );
        REQUIRE( textValue->GetTextValue() == std::get<1>(testData) );
      }
    }

    WHEN( "The property value is an invalid Text string" )
    {
      // No tests because there are no invalid Text values
    }
  }

  GIVEN( "The property value type is Point and the game type is not Go" )
  {
    WHEN( "The property value is a valid Point string" )
    {
      std::string rawValue = GENERATE(SgfcConstants::NoneValueString.c_str() , "foo" );
      SgfcPoint pointValue = rawValue;

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValue.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("SE");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, SgfcGameType::LinesOfAction, SgfcConstants::BoardSizeInvalid);

      THEN( "SgfcPropertyDecoder successfully decodes the Point string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::SE );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == rawValue );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Point );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto pointValueObject = propertySingleValue->ToPointValue();
        REQUIRE( pointValueObject != nullptr );
        REQUIRE( pointValueObject->GetPointValue() == pointValue );
        auto goPointValue = pointValueObject->ToGoPointValue();
        REQUIRE( goPointValue == nullptr );
      }
    }

    WHEN( "The property value is an invalid Point string" )
    {
      // No tests because there are no invalid Point strings for game types != Go
    }
  }

  GIVEN( "The property value type is Point and the game type is Go" )
  {
    WHEN( "The property value is a valid Point string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetGoPointStrings()) );

      // Need a local string variable so that we can store a reference to its
      // c_str() in the PropValue object
      std::string rawValueSgfNotation = std::get<12>(testData);
      SgfcPoint pointValueSgfNotation = std::get<14>(testData);

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValueSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AE");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, std::get<1>(testData));

      THEN( "SgfcPropertyDecoder successfully decodes the Point string value" )
      {
        AssertValidGoPointStrings(propertyDecoder, SgfcPropertyType::AE, rawValueSgfNotation, pointValueSgfNotation, std::get<2>(testData), std::get<3>(testData));
      }
    }

    WHEN( "The property value is a valid Point string but the board size is invalid" )
    {
      auto invalidGoBoardSize = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidGoBoardSizes()) );

      std::string rawValueSgfNotation = "aa";
      std::string pointValueSgfNotation = rawValueSgfNotation;

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValueSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AE");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, invalidGoBoardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Point string value but provides it as ISgfcPointPropertyValue" )
      {
        AssertInvalidGoPointStrings(propertyDecoder, SgfcPropertyType::AE, rawValueSgfNotation, pointValueSgfNotation);
      }
    }

    WHEN( "The property value is an invalid Point string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidGoPointStrings()) );

      std::string rawValueSgfNotation = testData.first;
      std::string pointValueSgfNotation = rawValueSgfNotation;

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValueSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AE");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, testData.second);

      THEN( "SgfcPropertyDecoder fails to decode the Point string value but provides it as ISgfcPointPropertyValue" )
      {
        AssertInvalidGoPointStrings(propertyDecoder, SgfcPropertyType::AE, rawValueSgfNotation, pointValueSgfNotation);
      }
    }
  }

  GIVEN( "The property value type is Move and the game type is not Go" )
  {
    WHEN( "The property value is a valid Move string" )
    {
      std::string rawValue = GENERATE( SgfcConstants::NoneValueString.c_str(), "foo" );
      SgfcMove moveValue = rawValue;

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValue.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("B");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, SgfcGameType::Ataxx, SgfcConstants::BoardSizeInvalid);

      THEN( "SgfcPropertyDecoder successfully decodes the Move string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::B );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == rawValue );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Move );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto moveValueObject = propertySingleValue->ToMoveValue();
        REQUIRE( moveValueObject != nullptr );
        REQUIRE( moveValueObject->GetMoveValue() == moveValue );
        auto goMoveValue = moveValueObject->ToGoMoveValue();
        REQUIRE( goMoveValue == nullptr );
      }
    }

    WHEN( "The property value is an invalid Move string" )
    {
      // No tests because there are no invalid Move strings for game types != Go
    }
  }

  GIVEN( "The property value type is Move and the game type is Go" )
  {
    WHEN( "The property value is a valid Move string that is not a pass move" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetGoPointStrings()) );

      // Need a local string variable so that we can store a reference to its
      // c_str() in the PropValue object
      std::string rawValueSgfNotation = std::get<12>(testData);
      SgfcMove moveValueSgfNotation = std::get<13>(testData);

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValueSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("B");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, std::get<1>(testData));

      THEN( "SgfcPropertyDecoder successfully decodes the Move string value" )
      {
        AssertValidGoMoveStrings(propertyDecoder, SgfcPropertyType::B, rawValueSgfNotation, moveValueSgfNotation, std::get<2>(testData), std::get<3>(testData));
      }
    }

    WHEN( "The property value is a valid Move string that is a pass move" )
    {
      std::string rawValue = SgfcConstants::GoMovePassString;
      SgfcMove moveValue = rawValue;

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValue.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("B");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, SgfcConstants::BoardSizeInvalid);

      THEN( "SgfcPropertyDecoder successfully decodes the Move string value" )
      {
        AssertValidGoMoveStrings(propertyDecoder, SgfcPropertyType::B, rawValue, moveValue, -1, -1);
      }
    }

    WHEN( "The property value is a valid Move string but the board size is invalid" )
    {
      auto invalidGoBoardSize = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidGoBoardSizes()) );

      std::string rawValueSgfNotation = "aa";
      SgfcMove moveValueSgfNotation = rawValueSgfNotation;

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValueSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("B");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, invalidGoBoardSize);

      SgfcColor expectedColor = propertyDecoder.GetPropertyType() == SgfcPropertyType::B ? SgfcColor::Black : SgfcColor::White;

      THEN( "SgfcPropertyDecoder fails to decode the Move string value but provides it as ISgfcMovePropertyValue" )
      {
        AssertInvalidGoMoveStrings(propertyDecoder, SgfcPropertyType::B, rawValueSgfNotation, moveValueSgfNotation);
      }
    }

    WHEN( "The property value is an invalid Move string" )
    {
      auto testData = GENERATE_COPY( filter(
        // Filter out Move strings that are pass moves - these are valid
        [](std::pair<std::string, SgfcBoardSize> i) { return i.first != SgfcConstants::GoMovePassString; },
        from_range(TestDataGenerator::GetInvalidGoPointStrings())
      ));

      std::string rawValue = testData.first;
      SgfcMove moveValue = rawValue;

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValue.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("B");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, testData.second);

      SgfcColor expectedColor = propertyDecoder.GetPropertyType() == SgfcPropertyType::B ? SgfcColor::Black : SgfcColor::White;

      THEN( "SgfcPropertyDecoder fails to decode the Move string value but provides it as ISgfcMovePropertyValue" )
      {
        AssertInvalidGoMoveStrings(propertyDecoder, SgfcPropertyType::B, rawValue, moveValue);
      }
    }
  }

  GIVEN( "The property value type is Stone and the game type is not Go" )
  {
    WHEN( "The property value is a valid Stone string" )
    {
      std::string rawValue = GENERATE(SgfcConstants::NoneValueString.c_str() , "foo" );
      SgfcStone stoneValue = rawValue;

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValue.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AB");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, SgfcGameType::LinesOfAction, SgfcConstants::BoardSizeInvalid);

      THEN( "SgfcPropertyDecoder successfully decodes the Stone string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::AB );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == rawValue );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Stone );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto stoneValueObject = propertySingleValue->ToStoneValue();
        REQUIRE( stoneValueObject != nullptr );
        REQUIRE( stoneValueObject->GetStoneValue() == stoneValue );
        auto goStoneValue = stoneValueObject->ToGoStoneValue();
        REQUIRE( goStoneValue == nullptr );
      }
    }

    WHEN( "The property value is an invalid Stone string" )
    {
      // No tests because there are no invalid Stone strings for game types != Go
    }
  }

  GIVEN( "The property value type is Stone and the game type is Go" )
  {
    WHEN( "The property value is a valid Stone string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetGoPointStrings()) );

      // Need a local string variable so that we can store a reference to its
      // c_str() in the PropValue object
      std::string rawValueSgfNotation = std::get<12>(testData);
      SgfcStone stoneValueSgfNotation = std::get<15>(testData);

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValueSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AB");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, std::get<1>(testData));

      THEN( "SgfcPropertyDecoder successfully decodes the Stone string value" )
      {
        AssertValidGoStoneStrings(propertyDecoder, SgfcPropertyType::AB, rawValueSgfNotation, stoneValueSgfNotation, std::get<2>(testData), std::get<3>(testData));
      }
    }

    WHEN( "The property value is a valid Stone string but the board size is invalid" )
    {
      auto invalidGoBoardSize = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidGoBoardSizes()) );

      std::string rawValueSgfNotation = "aa";
      SgfcMove stoneValueSgfNotation = rawValueSgfNotation;

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValueSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AB");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, invalidGoBoardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Stone string value but provides it as ISgfcStonePropertyValue" )
      {
        AssertInvalidGoStoneStrings(propertyDecoder, SgfcPropertyType::AB, rawValueSgfNotation, stoneValueSgfNotation);
      }
    }

    WHEN( "The property value is an invalid Stone string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidGoPointStrings()) );

      std::string rawValue = testData.first;
      SgfcStone stoneValue = rawValue;

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(rawValue.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AB");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, testData.second);

      THEN( "SgfcPropertyDecoder fails to decode the Stone string value but provides it as ISgfcStonePropertyValue" )
      {
        AssertInvalidGoStoneStrings(propertyDecoder, SgfcPropertyType::AB, rawValue, stoneValue);
      }
    }
  }

  GIVEN( "The property value type is Unknown" )
  {
    WHEN( "The property value is a valid Unknown string" )
    {
      std::string valueString = GENERATE(SgfcConstants::NoneValueString.c_str() , "foo" );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(valueString.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("QQ");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, SgfcGameType::Unknown, SgfcConstants::BoardSizeNone);

      THEN( "SgfcPropertyDecoder successfully decodes the Unknown string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::Unknown );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == valueString );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Unknown );
        REQUIRE( propertySingleValue->HasTypedValue() == false );
      }
    }

    WHEN( "The property value is an invalid Unknown string" )
    {
      // No tests because there are no invalid Unknown strings
    }
  }
}

SCENARIO( "SgfcPropertyDecoder is constructed with a property that is a list type consisting of a basic value type", "[parsing]" )
{
  WHEN( "The SGF property object has no value (an SGFC interfacing error)" )
  {
    THEN( "SgfcPropertyDecoder fails to decode the property value" )
    {
      AssertDecodeOfPropertyValueFailsWhenNoValueIsGiven("AE", SgfcPropertyType::AE);
    }
  }

  WHEN( "The SGF property object has a second value (an SGFC interfacing error)" )
  {
    THEN( "SgfcPropertyDecoder fails to decode the property value" )
    {
      // Property "AE" has value type List of Points, so we provide two valid
      // Point strings. Decoding must fail because in a list of basic value
      // types each element is single valus.
      AssertDecodeOfSinglePropertyValueFailsWhenSecondValueIsGiven("AE", SgfcPropertyType::AE, "aa", "bb");
    }
  }

  GIVEN( "The property value type is List of Points and the game type is Go" )
  {
    WHEN( "The property values are decoded" )
    {
      std::string rawValueSgfNotation1 = "aa";
      std::string rawValueSgfNotation2 = "bb";
      SgfcPoint pointValueSgfNotation1 = rawValueSgfNotation1;
      SgfcPoint pointValueSgfNotation2 = rawValueSgfNotation2;

      PropValue propertyValue2;
      propertyValue2.value = const_cast<char*>(rawValueSgfNotation2.c_str());
      propertyValue2.value2 = nullptr;
      propertyValue2.next = nullptr;

      PropValue propertyValue1;
      propertyValue1.value = const_cast<char*>(rawValueSgfNotation1.c_str());
      propertyValue1.value2 = nullptr;
      propertyValue1.next = &propertyValue2;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AE");
      sgfProperty.value = &propertyValue1;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, SgfcGameType::Go, SgfcConstants::BoardSizeDefaultGo);

      THEN( "SgfcPropertyDecoder successfully decodes the Point string values" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::AE );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 2 );
        auto propertySingleValue1 = propertyValues.front()->ToSingleValue();
        AssertValidGoPointString(propertySingleValue1, rawValueSgfNotation1, pointValueSgfNotation1, 1, 1);
        auto propertySingleValue2 = propertyValues.back()->ToSingleValue();
        AssertValidGoPointString(propertySingleValue2, rawValueSgfNotation2, pointValueSgfNotation2, 2, 2);
      }
    }
  }

  GIVEN( "The property value type is List of Points and the game type is not Go and the property values contain rectangles" )
  {
    WHEN( "The property values are decoded" )
    {
      std::string rawValue1 = "foo";
      std::string rawValue2UpperLeftCorner = "bar";
      std::string rawValue2LowerRightCorner = "baz";
      SgfcPoint pointValue1 = rawValue1;
      SgfcPoint pointValue2UpperLeftCorner = rawValue2UpperLeftCorner;
      SgfcPoint pointValue2LowerRightCorner = rawValue2LowerRightCorner;

      PropValue propertyValue2;
      propertyValue2.value = const_cast<char*>(rawValue2UpperLeftCorner.c_str());
      propertyValue2.value2 = const_cast<char*>(rawValue2LowerRightCorner.c_str());
      propertyValue2.next = nullptr;

      PropValue propertyValue1;
      propertyValue1.value = const_cast<char*>(rawValue1.c_str());
      propertyValue1.value2 = nullptr;
      propertyValue1.next = &propertyValue2;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AE");
      sgfProperty.value = &propertyValue1;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, SgfcGameType::Amazons, SgfcConstants::BoardSizeNone);

      THEN( "SgfcPropertyDecoder inspects property values for rectangles" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::AE );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 2 );
        auto propertySingleValue1 = propertyValues.front()->ToSingleValue();
        AssertValidPointString(propertySingleValue1, rawValue1, pointValue1);
        auto propertyComposedValue2 = propertyValues.back()->ToComposedValue();
        REQUIRE( propertyComposedValue2 != nullptr );
        AssertValidPointString(propertyComposedValue2->GetValue1().get(), rawValue2UpperLeftCorner, pointValue2UpperLeftCorner);
        AssertValidPointString(propertyComposedValue2->GetValue2().get(), rawValue2LowerRightCorner, pointValue2LowerRightCorner);
      }
    }
  }


  GIVEN( "The property value type is List of Stones and the game type is not Go and the property values contain rectangles" )
  {
    WHEN( "The property values are decoded" )
    {
      std::string rawValue1 = "foo";
      std::string rawValue2UpperLeftCorner = "bar";
      std::string rawValue2LowerRightCorner = "baz";
      SgfcStone stoneValue1 = rawValue1;
      SgfcStone stoneValue2UpperLeftCorner = rawValue2UpperLeftCorner;
      SgfcStone stoneValue2LowerRightCorner = rawValue2LowerRightCorner;

      PropValue propertyValue2;
      propertyValue2.value = const_cast<char*>(rawValue2UpperLeftCorner.c_str());
      propertyValue2.value2 = const_cast<char*>(rawValue2LowerRightCorner.c_str());
      propertyValue2.next = nullptr;

      PropValue propertyValue1;
      propertyValue1.value = const_cast<char*>(rawValue1.c_str());
      propertyValue1.value2 = nullptr;
      propertyValue1.next = &propertyValue2;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AB");
      sgfProperty.value = &propertyValue1;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, SgfcGameType::Amazons, SgfcConstants::BoardSizeNone);

      THEN( "SgfcPropertyDecoder inspects property values for rectangles" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::AB );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 2 );
        auto propertySingleValue1 = propertyValues.front()->ToSingleValue();
        AssertValidStoneString(propertySingleValue1, rawValue1, stoneValue1);
        auto propertyComposedValue2 = propertyValues.back()->ToComposedValue();
        REQUIRE( propertyComposedValue2 != nullptr );
        AssertValidStoneString(propertyComposedValue2->GetValue1().get(), rawValue2UpperLeftCorner, stoneValue2UpperLeftCorner);
        AssertValidStoneString(propertyComposedValue2->GetValue2().get(), rawValue2LowerRightCorner, stoneValue2LowerRightCorner);
      }
    }
  }
}

SCENARIO( "SgfcPropertyDecoder is constructed with a property that is a composed value type", "[parsing]" )
{
  SgfcGameType gameType = SgfcGameType::Go;
  SgfcBoardSize boardSize = { 19, 19 };

  WHEN( "The SGF property object has no value (an SGFC interfacing error)" )
  {
    THEN( "SgfcPropertyDecoder fails to decode the property value" )
    {
      AssertDecodeOfPropertyValueFailsWhenNoValueIsGiven("AP", SgfcPropertyType::AP);
    }
  }

  WHEN( "The SGF property object has no second value (an SGFC interfacing error)" )
  {
    THEN( "SgfcPropertyDecoder fails to decode the property value" )
    {
      AssertDecodeOfComposedPropertyValueFailsWhenNoSecondValueIsGiven("AP", SgfcPropertyType::AP, "foo");
    }
  }

  GIVEN( "The property value type is a composition of SimpleText and SimpleText" )
  {
    WHEN( "The property value is a composition of two valid SimpleText strings" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetSimpleTextStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(std::get<0>(testData).c_str());
      propertyValue.value2 = const_cast<char*>(std::get<0>(testData).c_str());
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AP");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);
      propertyDecoder.SetEscapeProcessingEnabled(true);

      THEN( "SgfcPropertyDecoder successfully decodes the composition of two SimpleText strings" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::AP );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );

        REQUIRE( propertyValues.front()->IsComposedValue() == true );
        auto propertyComposedValue = propertyValues.front()->ToComposedValue();

        auto propertySingleValue1 = propertyComposedValue->GetValue1();
        AssertValidSimpleTextString(propertySingleValue1.get(), std::get<0>(testData), std::get<2>(testData));
        auto propertySingleValue2 = propertyComposedValue->GetValue2();
        AssertValidSimpleTextString(propertySingleValue2.get(), std::get<0>(testData), std::get<3>(testData));
      }
    }

    WHEN( "The property value is a composition of one or two invalid SimpleText strings" )
    {
      // No tests because there are no invalid SimpleText strings
    }
  }

  GIVEN( "The property value type is a composition of Number and Number" )
  {
    // No tests because this value type does not occur standalone - it occurs
    // only as one of the two options of a dual value type. In other words: the
    // value type will be tested later in the SCENARIO for dual value types.
  }

  GIVEN( "The property value type is a composition of Point and Point" )
  {
    // No tests because this value type does not occur standalone - it occurs
    // only in the context of the list value type. In other words: the value
    // type will be tested later in the SCENARIO for list types consisting of a
    // composed value type.
  }

  GIVEN( "The property value type is a composition of Point and SimpleText" )
  {
    // No tests because this value type does not occur standalone - it occurs
    // only in the context of the list value type. In other words: the value
    // type will be tested later in the SCENARIO for list types consisting of a
    // composed value type.
  }

  GIVEN( "The property value type is a composition of Number and SimpleText" )
  {
    // No tests because this value type does not occur standalone - it occurs
    // only as one of the two options of a dual value type. In other words: the
    // value type will be tested later in the SCENARIO for dual value types.
  }

  GIVEN( "The property value type is a composition of Stone and Point" )
  {
    // No tests because this value type does not occur standalone - it occurs
    // only in the context of the list value type. In other words: the value
    // type will be tested later in the SCENARIO for list types consisting of a
    // composed value type.
  }

  GIVEN( "The SGF property object has an unexpected structure" )
  {
    WHEN( "The SGF property object has no second value" )
    {
      THEN( "SgfcPropertyDecoder fails to decode the composed value" )
      {
        AssertDecodeOfComposedPropertyValueFailsWhenNoSecondValueIsGiven("AP", SgfcPropertyType::AP, "foo");
      }
    }
  }
}

SCENARIO( "SgfcPropertyDecoder is constructed with a property that is a list type consisting of a composed value type", "[parsing]" )
{
  SgfcGameType gameType = SgfcGameType::Go;
  SgfcBoardSize boardSize = { 19, 19 };

  WHEN( "The SGF property object has no value (an SGFC interfacing error)" )
  {
    THEN( "SgfcPropertyDecoder fails to decode the property value" )
    {
      AssertDecodeOfPropertyValueFailsWhenNoValueIsGiven("LB", SgfcPropertyType::LB);
    }
  }

  WHEN( "The SGF property object has no second value (an SGFC interfacing error)" )
  {
    THEN( "SgfcPropertyDecoder fails to decode the property value" )
    {
      AssertDecodeOfComposedPropertyValueFailsWhenNoSecondValueIsGiven("LB", SgfcPropertyType::LB, "A1");
    }
  }

  GIVEN( "The property value type is a list of composed Point and SimpleText strings and the game type is Go" )
  {
    WHEN( "Both the Point strings and the SimpleText strings are valid" )
    {
      // We are not particularly interested in testing the correctness of value
      // parsing, so we don't need a lot of test values
      std::string pointRawValue1 = "as";
      SgfcPoint pointValue1 = pointRawValue1;
      std::string simpleTextString1 = SgfcConstants::NoneValueString;
      SgfcSimpleText simpleTextValue1 = SgfcConstants::NoneValueString;
      int xPosition1 = 1;
      int yPosition1 = 19;
      std::string pointRawValue2 = "pc";
      SgfcPoint pointValue2 = pointRawValue2;
      std::string simpleTextString2 = "foo";
      SgfcSimpleText simpleTextValue2 = "foo";
      int xPosition2 = 16;
      int yPosition2 = 3;

      PropValue propertyValue2;
      propertyValue2.value = const_cast<char*>(pointRawValue2.c_str());
      propertyValue2.value2 = const_cast<char*>(simpleTextString2.c_str());
      propertyValue2.next = nullptr;

      PropValue propertyValue1;
      propertyValue1.value = const_cast<char*>(pointRawValue1.c_str());
      propertyValue1.value2 = const_cast<char*>(simpleTextString1.c_str());
      propertyValue1.next = &propertyValue2;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("LB");
      sgfProperty.value = &propertyValue1;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the list of composed Point and SimpleText string values" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::LB );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 2 );

        REQUIRE( propertyValues.front()->IsComposedValue() == true );
        auto propertyComposedValue1 = propertyValues.front()->ToComposedValue();
        REQUIRE( propertyValues.back()->IsComposedValue() == true );
        auto propertyComposedValue2 = propertyValues.back()->ToComposedValue();

        auto propertySingleValue1a = propertyComposedValue1->GetValue1();
        AssertValidGoPointString(propertySingleValue1a.get(), pointRawValue1, pointValue1, xPosition1, yPosition1);
        auto propertySingleValue1b = propertyComposedValue1->GetValue2();
        AssertValidSimpleTextString(propertySingleValue1b.get(), simpleTextString1, simpleTextValue1);

        auto propertySingleValue2a = propertyComposedValue2->GetValue1();
        AssertValidGoPointString(propertySingleValue2a.get(), pointRawValue2, pointValue2, xPosition2, yPosition2);
        auto propertySingleValue2b = propertyComposedValue2->GetValue2();
        AssertValidSimpleTextString(propertySingleValue2b.get(), simpleTextString2, simpleTextValue2);
      }
    }

    WHEN( "The Point strings are invalid and the SimpleText strings are valid" )
    {
      std::string pointRawValue = "foo";
      std::string pointValue = pointRawValue;
      std::string simpleTextString = "bar";
      SgfcSimpleText simpleTextValue = "bar";

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(pointRawValue.c_str());
      propertyValue.value2 = const_cast<char*>(simpleTextString.c_str());
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("LB");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Point string value but provides it as ISgfcGoPointPropertyValue without ISgfcGoPoint" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::LB );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );

        REQUIRE( propertyValues.front()->IsComposedValue() == true );
        auto propertyComposedValue = propertyValues.front()->ToComposedValue();

        auto propertySingleValue1 = propertyComposedValue->GetValue1();
        AssertInvalidGoPointString(propertySingleValue1.get(), pointRawValue, pointValue);
        auto propertySingleValue2 = propertyComposedValue->GetValue2();
        AssertValidSimpleTextString(propertySingleValue2.get(), simpleTextString, simpleTextValue);
      }
    }

    WHEN( "The Point strings are valid and the SimpleText strings are invalid" )
    {
      // No tests because there are no invalid SimpleText strings
    }
  }

  GIVEN( "The property value type is a list of composed Stone and Point strings and the game type is not Go" )
  {
    // TODO: Implement tests. Currently no tests are implemented because it
    // does not seem important. Tests above already cover the "list of composed
    // values" scenario. Implementing these tests seems to be merely an
    // excercise in completeness.
  }
}

SCENARIO( "SgfcPropertyDecoder is constructed with a property that is a dual value type", "[parsing]" )
{
  SgfcGameType gameType = SgfcGameType::Go;
  SgfcBoardSize boardSize = { 19, 19 };

  WHEN( "The SGF property object has no value (an SGFC interfacing error)" )
  {
    THEN( "SgfcPropertyDecoder fails to decode the property value" )
    {
      AssertDecodeOfPropertyValueFailsWhenNoValueIsGiven("SZ", SgfcPropertyType::SZ);
    }
  }

  GIVEN( "The property value type is either a Number or a composition of Number and Number" )
  {
    WHEN( "The property value is a valid Number string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetValidNumberStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(testData.first.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("SZ");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the Number string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::SZ );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        AssertValidNumberString(propertySingleValue, testData.first, testData.second);
      }
    }

    WHEN( "The property value is a composition of two valid Number strings" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetValidNumberStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(testData.first.c_str());
      propertyValue.value2 = const_cast<char*>(testData.first.c_str());
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("SZ");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the Number string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::SZ );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );

        REQUIRE( propertyValues.front()->IsComposedValue() == true );
        auto propertyComposedValue = propertyValues.front()->ToComposedValue();

        auto propertySingleValue1 = propertyComposedValue->GetValue1();
        AssertValidNumberString(propertySingleValue1.get(), testData.first, testData.second);
        auto propertySingleValue2 = propertyComposedValue->GetValue2();
        AssertValidNumberString(propertySingleValue2.get(), testData.first, testData.second);
      }
    }

    WHEN( "The property value is an invalid Number string" )
    {
      auto stringValue = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidNumberStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(stringValue.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("SZ");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Number string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::SZ );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        AssertInvalidNumberString(propertySingleValue, stringValue);
      }
    }

    WHEN( "The property value is a composition of two invalid Number strings" )
    {
      auto stringValue = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidNumberStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(stringValue.c_str());
      propertyValue.value2 = const_cast<char*>(stringValue.c_str());
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("SZ");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Number string values" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::SZ );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );

        REQUIRE( propertyValues.front()->IsComposedValue() == true );
        auto propertyComposedValue = propertyValues.front()->ToComposedValue();

        auto propertySingleValue1 = propertyComposedValue->GetValue1();
        AssertInvalidNumberString(propertySingleValue1.get(), stringValue);
        auto propertySingleValue2 = propertyComposedValue->GetValue2();
        AssertInvalidNumberString(propertySingleValue2.get(), stringValue);
      }
    }
  }

  GIVEN( "The property value type is either None or a composition of Number and SimpleText" )
  {
    WHEN( "The property has value None" )
    {
      PropValue propertyValue;
      // SGF defines the None value type to be an empty string. We add an
      // arbitrary string to the list of values because we expect
      // SgfcPropertyDecoder to ignore any property values when it decides
      // that the property value has value type None (it decide this because
      // we don't provide a composed value, so for property FG the conclusion
      // is that the value must have value type None).
      std::vector<const char*> v = { SgfcConstants::NoneValueString.c_str(), "foo" };
      propertyValue.value = const_cast<char*>(GENERATE_COPY( from_range(v) ));
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("FG");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder returns an empty list of property values" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::FG );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 0 );
      }
    }

    WHEN( "The property value is a composition of a valid Number string and a valid SimpleText string" )
    {
      // We are not particularly interested in testing the correctness of value
      // parsing, so we don't need a lot of test values
      std::string numberString = "42";
      SgfcNumber numberValue = 42;
      std::string simpleTextString = "foo";
      SgfcSimpleText simpleTextValue = "foo";

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(numberString.c_str());
      propertyValue.value2 = const_cast<char*>(simpleTextString.c_str());
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("FG");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the composed Number and SimpleText strings" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::FG );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );

        REQUIRE( propertyValues.front()->IsComposedValue() == true );
        auto propertyComposedValue = propertyValues.front()->ToComposedValue();

        auto propertySingleValue1 = propertyComposedValue->GetValue1();
        AssertValidNumberString(propertySingleValue1.get(), numberString, numberValue);
        auto propertySingleValue2 = propertyComposedValue->GetValue2();
        AssertValidSimpleTextString(propertySingleValue2.get(), simpleTextString, simpleTextValue);
      }
    }

    WHEN( "The property value is a composition of an invalid Number string and a valid SimpleText string" )
    {
      auto numberString = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidNumberStrings()) );
      std::string simpleTextString = "foo";
      SgfcSimpleText simpleTextValue = "foo";

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(numberString.c_str());
      propertyValue.value2 = const_cast<char*>(simpleTextString.c_str());
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("FG");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Number string values" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::FG );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );

        REQUIRE( propertyValues.front()->IsComposedValue() == true );
        auto propertyComposedValue = propertyValues.front()->ToComposedValue();

        auto propertySingleValue1 = propertyComposedValue->GetValue1();
        AssertInvalidNumberString(propertySingleValue1.get(), numberString);
        auto propertySingleValue2 = propertyComposedValue->GetValue2();
        AssertValidSimpleTextString(propertySingleValue2.get(), simpleTextString, simpleTextValue);
      }
    }

    WHEN( "The property value is a composition of a valid or invalid Number string and an invalid SimpleText string" )
    {
      // No tests because there are no invalid SimpleText strings
    }
  }
}

SCENARIO( "SgfcPropertyDecoder is constructed with a property that is an elist value type", "[parsing]" )
{
  SgfcGameType gameType = SgfcGameType::Go;
  SgfcBoardSize boardSize = { 19, 19 };

  WHEN( "The SGF property object has no value (an SGFC interfacing error)" )
  {
    THEN( "SgfcPropertyDecoder fails to decode the property value" )
    {
      AssertDecodeOfPropertyValueFailsWhenNoValueIsGiven("DD", SgfcPropertyType::DD);
    }
  }

  WHEN( "The SGF property object has a second value (an SGFC interfacing error)" )
  {
    THEN( "SgfcPropertyDecoder fails to decode the property value" )
    {
      // Property "DD" has value type List of Points, so we provide two valid
      // Point strings. Decoding must fail because in a list of basic value
      // types each element is single valus.
      AssertDecodeOfSinglePropertyValueFailsWhenSecondValueIsGiven("DD", SgfcPropertyType::DD, "aa", "bb");
    }
  }

  GIVEN( "The property value type is elist of Points" )
  {
    WHEN( "The property values are a list of valid Point strings" )
    {
      std::string rawValueSgfNotation1 = "aa";
      std::string rawValueSgfNotation2 = "bb";
      SgfcPoint pointValueSgfNotation1 = rawValueSgfNotation1;
      SgfcPoint pointValueSgfNotation2 = rawValueSgfNotation2;

      PropValue propertyValue2;
      propertyValue2.value = const_cast<char*>(rawValueSgfNotation2.c_str());
      propertyValue2.value2 = nullptr;
      propertyValue2.next = nullptr;

      PropValue propertyValue1;
      propertyValue1.value = const_cast<char*>(rawValueSgfNotation1.c_str());
      propertyValue1.value2 = nullptr;
      propertyValue1.next = &propertyValue2;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("DD");
      sgfProperty.value = &propertyValue1;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the Point string values" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::DD );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 2 );
        auto propertySingleValue1 = propertyValues.front()->ToSingleValue();
        AssertValidGoPointString(propertySingleValue1, rawValueSgfNotation1, pointValueSgfNotation1, 1, 1);
        auto propertySingleValue2 = propertyValues.back()->ToSingleValue();
        AssertValidGoPointString(propertySingleValue2, rawValueSgfNotation2, pointValueSgfNotation2, 2, 2);
      }
    }

    WHEN( "The property values are a list of invalid Point strings" )
    {
      std::string invalidRawValue1 = "foo";
      std::string invalidRawValue2 = "bar";
      std::string invalidpointValue1 = invalidRawValue1;
      std::string invalidpointValue2 = invalidRawValue2;

      PropValue propertyValue2;
      propertyValue2.value = const_cast<char*>(invalidRawValue2.c_str());
      propertyValue2.value2 = nullptr;
      propertyValue2.next = nullptr;

      PropValue propertyValue1;
      propertyValue1.value = const_cast<char*>(invalidRawValue1.c_str());
      propertyValue1.value2 = nullptr;
      propertyValue1.next = &propertyValue2;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("DD");
      sgfProperty.value = &propertyValue1;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Point string values but provides them as ISgfcGoPointPropertyValue without ISgfcGoPoint" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::DD );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 2 );
        auto propertySingleValue1 = propertyValues.front()->ToSingleValue();
        AssertInvalidGoPointString(propertySingleValue1, invalidRawValue1, invalidpointValue1);
        auto propertySingleValue2 = propertyValues.back()->ToSingleValue();
        AssertInvalidGoPointString(propertySingleValue2, invalidRawValue2, invalidpointValue2);
      }
    }

    WHEN( "The property has value None" )
    {
      PropValue propertyValue;
      // SGF defines the None value type to be an empty string
      propertyValue.value = const_cast<char*>(SgfcConstants::NoneValueString.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("DD");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder returns an empty list of property values" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::DD );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 0 );
      }
    }
  }
}

void AssertValidNumberString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& expectedRawValue, SgfcNumber expectedNumberValue)
{
  REQUIRE( propertySingleValue->GetRawValue() == expectedRawValue );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Number );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto numberValue = propertySingleValue->ToNumberValue();
  REQUIRE( numberValue != nullptr );
  REQUIRE( numberValue->GetNumberValue() == expectedNumberValue );
}

void AssertInvalidNumberString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& expectedRawValue)
{
  REQUIRE( propertySingleValue->GetRawValue() == expectedRawValue );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() > 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Number );
  REQUIRE( propertySingleValue->HasTypedValue() == false );
  auto numberValue = propertySingleValue->ToNumberValue();
  REQUIRE( numberValue == nullptr );
}

void AssertValidSimpleTextString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& expectedRawValue, const SgfcSimpleText& expectedParsedValue)
{
  REQUIRE( propertySingleValue->GetRawValue() == expectedRawValue );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::SimpleText );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto simpleTextValue = propertySingleValue->ToSimpleTextValue();
  REQUIRE( simpleTextValue != nullptr );
  REQUIRE( simpleTextValue->GetSimpleTextValue() == expectedParsedValue );
}

void AssertValidPointString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& rawValue, const SgfcPoint& pointValue)
{
  REQUIRE( propertySingleValue->GetRawValue() == rawValue );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Point );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto pointValueObject = propertySingleValue->ToPointValue();
  REQUIRE( pointValueObject != nullptr );
  REQUIRE( pointValueObject->GetPointValue() == pointValue );
  auto goPointValue = pointValueObject->ToGoPointValue();
  REQUIRE( goPointValue == nullptr );
}

void AssertValidStoneString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& rawValue, const SgfcStone& stoneValue)
{
  REQUIRE( propertySingleValue->GetRawValue() == rawValue );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Stone );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto stoneValueObject = propertySingleValue->ToStoneValue();
  REQUIRE( stoneValueObject != nullptr );
  REQUIRE( stoneValueObject->GetStoneValue() == stoneValue );
  auto goStoneValue = stoneValueObject->ToGoStoneValue();
  REQUIRE( goStoneValue == nullptr );
}

void AssertValidGoPointStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcPoint& pointValue, int xPosition, int yPosition)
{
  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  auto propertyValues = propertyDecoder.GetPropertyValues();
  REQUIRE( propertyValues.size() == 1 );
  auto propertySingleValue = propertyValues.front()->ToSingleValue();
  AssertValidGoPointString(propertySingleValue, rawValue, pointValue, xPosition, yPosition);
}

void AssertValidGoPointString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& rawValue, const SgfcPoint& pointValue, int xPosition, int yPosition)
{
  REQUIRE( propertySingleValue->GetRawValue() == rawValue );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Point );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto pointValueObject = propertySingleValue->ToPointValue();
  REQUIRE( pointValueObject != nullptr );
  REQUIRE( pointValueObject->GetPointValue() == pointValue );
  auto goPointValue = pointValueObject->ToGoPointValue();
  REQUIRE( goPointValue != nullptr );
  auto goPoint = goPointValue->GetGoPoint();
  REQUIRE( goPoint != nullptr );
  REQUIRE( goPoint->GetXPosition(SgfcCoordinateSystem::UpperLeftOrigin) == xPosition );
  REQUIRE( goPoint->GetYPosition(SgfcCoordinateSystem::UpperLeftOrigin) == yPosition );
}

void AssertInvalidGoPointStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcPoint& pointValue)
{
  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  auto propertyValues = propertyDecoder.GetPropertyValues();
  REQUIRE( propertyValues.size() == 1 );
  auto propertySingleValue = propertyValues.front()->ToSingleValue();
  AssertInvalidGoPointString(propertySingleValue, rawValue, pointValue);
}

void AssertInvalidGoPointString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& rawValue, const SgfcPoint& pointValue)
{
  REQUIRE( propertySingleValue->GetRawValue() == rawValue );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Point );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto pointValueObject = propertySingleValue->ToPointValue();
  REQUIRE( pointValueObject != nullptr );
  REQUIRE( pointValueObject->GetPointValue() == pointValue );
  auto goPointValue = pointValueObject->ToGoPointValue();
  REQUIRE( goPointValue == nullptr );
}

void AssertValidGoMoveStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcMove& moveValue, int xPosition, int yPosition)
{
  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  auto propertyValues = propertyDecoder.GetPropertyValues();
  REQUIRE( propertyValues.size() == 1 );
  auto propertySingleValue = propertyValues.front()->ToSingleValue();

  AssertValidGoMoveStrings(propertySingleValue, propertyType, rawValue, moveValue, xPosition, yPosition);
}

void AssertValidGoMoveStrings(const ISgfcSinglePropertyValue* propertySingleValue, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcMove& moveValue, int xPosition, int yPosition)
{
  AssertValidMoveStrings(propertySingleValue, propertyType, rawValue, moveValue);

  SgfcColor expectedColor = propertyType == SgfcPropertyType::B ? SgfcColor::Black : SgfcColor::White;

  auto goMoveValue = propertySingleValue->ToMoveValue()->ToGoMoveValue();
  REQUIRE( goMoveValue != nullptr );
  auto goMove = goMoveValue->GetGoMove();
  REQUIRE( goMove != nullptr );
  REQUIRE( goMove->GetPlayerColor() == expectedColor );
  if (rawValue == SgfcConstants::GoMovePassString)
  {
    REQUIRE( goMove->IsPassMove() == true );
    auto goStone = goMove->GetStone();
    REQUIRE( goStone == nullptr );
    REQUIRE( goMove->GetStoneLocation() == nullptr );
  }
  else
  {
    REQUIRE( goMove->IsPassMove() == false );
    auto goStone = goMove->GetStone();
    REQUIRE( goStone != nullptr );
    REQUIRE( goStone->GetColor() == expectedColor );
    REQUIRE( goMove->GetPlayerColor() == goStone->GetColor() );
    auto goPoint = goStone->GetLocation();
    REQUIRE( goPoint != nullptr );
    REQUIRE( goMove->GetStoneLocation() == goPoint );
    REQUIRE( goPoint->GetXPosition(SgfcCoordinateSystem::UpperLeftOrigin) == xPosition );
    REQUIRE( goPoint->GetYPosition(SgfcCoordinateSystem::UpperLeftOrigin) == yPosition );
  }
}

void AssertValidMoveStrings(const ISgfcSinglePropertyValue* propertySingleValue, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcMove& moveValue)
{
  REQUIRE( propertySingleValue->GetRawValue() == rawValue );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Move );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto moveValueObject = propertySingleValue->ToMoveValue();
  REQUIRE( moveValueObject != nullptr );
  REQUIRE( moveValueObject->GetMoveValue() == moveValue );
}

void AssertInvalidGoMoveStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcMove& moveValue)
{
  SgfcColor expectedColor = propertyType == SgfcPropertyType::B ? SgfcColor::Black : SgfcColor::White;

  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  auto propertyValues = propertyDecoder.GetPropertyValues();
  REQUIRE( propertyValues.size() == 1 );
  auto propertySingleValue = propertyValues.front()->ToSingleValue();
  REQUIRE( propertySingleValue->GetRawValue() == rawValue );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Move );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto moveValueObject = propertySingleValue->ToMoveValue();
  REQUIRE( moveValueObject != nullptr );
  REQUIRE( moveValueObject->GetMoveValue() == moveValue );
  auto goMoveValue = moveValueObject->ToGoMoveValue();
  REQUIRE( goMoveValue == nullptr );
}

void AssertValidGoStoneStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcStone& stoneValue, int xPosition, int yPosition)
{
  SgfcColor expectedColor = propertyType == SgfcPropertyType::AB ? SgfcColor::Black : SgfcColor::White;

  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  auto propertyValues = propertyDecoder.GetPropertyValues();
  REQUIRE( propertyValues.size() == 1 );
  auto propertySingleValue = propertyValues.front()->ToSingleValue();
  REQUIRE( propertySingleValue->GetRawValue() == rawValue );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Stone );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto stoneValueObject = propertySingleValue->ToStoneValue();
  REQUIRE( stoneValueObject != nullptr );
  REQUIRE( stoneValueObject->GetStoneValue() == stoneValue );
  auto goStoneValue = stoneValueObject->ToGoStoneValue();
  REQUIRE( goStoneValue != nullptr );
  auto goStone = goStoneValue->GetGoStone();
  REQUIRE( goStone != nullptr );
  REQUIRE( goStone->GetColor() == expectedColor );
  auto goPoint = goStone->GetLocation();
  REQUIRE( goPoint != nullptr );
  REQUIRE( goPoint->GetXPosition(SgfcCoordinateSystem::UpperLeftOrigin) == xPosition );
  REQUIRE( goPoint->GetYPosition(SgfcCoordinateSystem::UpperLeftOrigin) == yPosition );
}

void AssertInvalidGoStoneStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& rawValue, const SgfcMove& stoneValue)
{
  SgfcColor expectedColor = propertyType == SgfcPropertyType::AB ? SgfcColor::Black : SgfcColor::White;

  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  auto propertyValues = propertyDecoder.GetPropertyValues();
  REQUIRE( propertyValues.size() == 1 );
  auto propertySingleValue = propertyValues.front()->ToSingleValue();
  REQUIRE( propertySingleValue->GetRawValue() == rawValue );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Stone );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto stoneValueObject = propertySingleValue->ToStoneValue();
  REQUIRE( stoneValueObject != nullptr );
  REQUIRE( stoneValueObject->GetStoneValue() == stoneValue );
  auto goStoneValue = stoneValueObject->ToGoStoneValue();
  REQUIRE( goStoneValue == nullptr );
}

void AssertDecodeOfPropertyValueFailsWhenNoValueIsGiven(const std::string& propertyID, SgfcPropertyType propertyType)
{
  SgfcGameType gameType = SgfcGameType::Go;
  SgfcBoardSize boardSize = { 19, 19 };

  PropValue propertyValue;
  propertyValue.value = nullptr;
  propertyValue.value2 = nullptr;
  propertyValue.next = nullptr;

  Property sgfProperty;
  sgfProperty.idstr = const_cast<char*>(propertyID.c_str());
  sgfProperty.value = &propertyValue;
  SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  REQUIRE_THROWS_AS(
    propertyDecoder.GetPropertyValues(),
    std::domain_error);
}

void AssertDecodeOfSinglePropertyValueFailsWhenSecondValueIsGiven(
  const std::string& propertyID,
  SgfcPropertyType propertyType,
  const std::string& rawPropertyValue,
  const std::string& rawPropertyValue2)
{
  SgfcGameType gameType = SgfcGameType::Go;
  SgfcBoardSize boardSize = { 19, 19 };

  PropValue propertyValue;
  propertyValue.value = const_cast<char*>(rawPropertyValue.c_str());
  propertyValue.value2 = const_cast<char*>(rawPropertyValue2.c_str());
  propertyValue.next = nullptr;

  Property sgfProperty;
  sgfProperty.idstr = const_cast<char*>(propertyID.c_str());
  sgfProperty.value = &propertyValue;
  SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  REQUIRE_THROWS_AS(
    propertyDecoder.GetPropertyValues(),
    std::domain_error);
}

void AssertDecodeOfComposedPropertyValueFailsWhenNoSecondValueIsGiven(
  const std::string& propertyID,
  SgfcPropertyType propertyType,
  const std::string& rawPropertyValue)
{
  SgfcGameType gameType = SgfcGameType::Go;
  SgfcBoardSize boardSize = { 19, 19 };

  PropValue propertyValue;
  propertyValue.value = const_cast<char*>(rawPropertyValue.c_str());
  propertyValue.value2 = nullptr;
  propertyValue.next = nullptr;

  Property sgfProperty;
  sgfProperty.idstr = const_cast<char*>(propertyID.c_str());
  sgfProperty.value = &propertyValue;
  SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  REQUIRE_THROWS_AS(
    propertyDecoder.GetPropertyValues(),
    std::domain_error);
}
