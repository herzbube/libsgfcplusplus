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

// SGFC includes
extern "C"
{
  #include <stdio.h>  // required to define size_t and FILE which are used in all.h
  #include "../../sgfc/all.h"
  #include "../../../sgfc/protos.h"
}

// Unit test library includes
#include <catch2/catch.hpp>

// C++ Standard Library includes
#include <utility>

using namespace LibSgfcPlusPlus;


void AssertValidNumberString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& expectedRawValue, SgfcNumber expectedNumberValue);
void AssertInvalidNumberString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& expectedRawValue);
void AssertValidSimpleTextString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& expectedRawValue, const std::string& expectedParsedValue);
void AssertValidGoPointStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& pointString, int xPosition, int yPosition);
void AssertValidGoPointString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& pointString, int xPosition, int yPosition);
void AssertInvalidGoPointStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& pointString);
void AssertInvalidGoPointString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& pointString);
void AssertValidGoMoveStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& moveString, int xPosition, int yPosition);
void AssertValidGoMoveStrings(const ISgfcSinglePropertyValue* propertySingleValue, SgfcPropertyType propertyType, const std::string& moveString, int xPosition, int yPosition);
void AssertValidMoveStrings(const ISgfcSinglePropertyValue* propertySingleValue, SgfcPropertyType propertyType, const std::string& moveString);
void AssertInvalidGoMoveStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& moveString);
void AssertValidGoStoneStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& stoneString, int xPosition, int yPosition);
void AssertInvalidGoStoneStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& stoneString);
void AssertDecodeOfPropertyValueFailsWhenNoValueIsGiven(const std::string& propertyID, SgfcPropertyType propertyType);
void AssertDecodeOfSinglePropertyValueFailsWhenSecondValueIsGiven(const std::string& propertyID, SgfcPropertyType propertyType, const std::string& rawPropertyValue, const std::string& rawPropertyValue2);
void AssertDecodeOfComposedPropertyValueFailsWhenNoSecondValueIsGiven(const std::string& propertyID, SgfcPropertyType propertyType, const std::string& rawPropertyValue);


// General structure of tests
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
        REQUIRE( realValue != nullptr );
        REQUIRE_THROWS_AS(
          realValue->GetRealValue(),
          std::logic_error);
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
        REQUIRE( doubleValue != nullptr );
        REQUIRE_THROWS_AS(
          doubleValue->GetDoubleValue(),
          std::logic_error);
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
        REQUIRE( colorValue != nullptr );
        REQUIRE_THROWS_AS(
          colorValue->GetColorValue(),
          std::logic_error);
      }
    }
  }

  GIVEN( "The property value type is SimpleText" )
  {
    WHEN( "The property value is a valid SimpleText string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetSimpleTextStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(testData.first.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("N");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the SimpleText string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::N );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();

        AssertValidSimpleTextString(propertySingleValue, testData.first, testData.second);
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
      propertyValue.value = const_cast<char*>(testData.first.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("GC");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the Text string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::GC );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == testData.first );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Text );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto textValue = propertySingleValue->ToTextValue();
        REQUIRE( textValue != nullptr );
        REQUIRE( textValue->GetTextValue() == testData.second );
      }
    }

    WHEN( "The property value is an invalid Text string" )
    {
      // No tests because there are no invalid SimpleText strings
    }
  }

  GIVEN( "The property value type is Point and the game type is not Go" )
  {
    WHEN( "The property value is a valid Point string" )
    {
      std::string pointString = GENERATE(SgfcConstants::NoneValueString.c_str() , "foo" );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(pointString.c_str());
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
        REQUIRE( propertySingleValue->GetRawValue() == pointString );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Point );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto pointValue = propertySingleValue->ToPointValue();
        REQUIRE( pointValue != nullptr );
        REQUIRE( pointValue->GetRawPointValue() == pointString );
        auto goPointValue = pointValue->ToGoPointValue();
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
      auto pointStringSgfNotation = std::get<9>(testData);

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(pointStringSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AE");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, std::get<1>(testData));

      THEN( "SgfcPropertyDecoder successfully decodes the Point string value" )
      {
        AssertValidGoPointStrings(propertyDecoder, SgfcPropertyType::AE, pointStringSgfNotation, std::get<2>(testData), std::get<3>(testData));
      }
    }

    WHEN( "The property value is a valid Point string but the board size is invalid" )
    {
      auto invalidGoBoardSize = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidGoBoardSizes()) );

      std::string pointStringSgfNotation = "aa";

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(pointStringSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AE");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, invalidGoBoardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Point string value but provides it as ISgfcGoPointPropertyValue without ISgfcGoPoint" )
      {
        AssertInvalidGoPointStrings(propertyDecoder, SgfcPropertyType::AE, pointStringSgfNotation);
      }
    }

    WHEN( "The property value is an invalid Point string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidGoPointStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(testData.first.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AE");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, testData.second);

      THEN( "SgfcPropertyDecoder fails to decode the Point string value but provides it as ISgfcGoPointPropertyValue without ISgfcGoPoint" )
      {
        AssertInvalidGoPointStrings(propertyDecoder, SgfcPropertyType::AE, testData.first);
      }
    }
  }

  GIVEN( "The property value type is Move and the game type is not Go" )
  {
    WHEN( "The property value is a valid Move string" )
    {
      std::string moveString = GENERATE( SgfcConstants::NoneValueString.c_str(), "foo" );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(moveString.c_str());
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
        REQUIRE( propertySingleValue->GetRawValue() == moveString );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Move );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto moveValue = propertySingleValue->ToMoveValue();
        REQUIRE( moveValue != nullptr );
        REQUIRE( moveValue->GetRawMoveValue() == moveString );
        auto goMoveValue = moveValue->ToGoMoveValue();
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
      auto moveStringSgfNotation = std::get<9>(testData);

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(moveStringSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("B");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, std::get<1>(testData));

      THEN( "SgfcPropertyDecoder successfully decodes the Move string value" )
      {
        AssertValidGoMoveStrings(propertyDecoder, SgfcPropertyType::B, moveStringSgfNotation, std::get<2>(testData), std::get<3>(testData));
      }
    }

    WHEN( "The property value is a valid Move string that is a pass move" )
    {
      std::string moveString = SgfcConstants::MovePassString;

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(moveString.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("B");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, SgfcConstants::BoardSizeInvalid);

      THEN( "SgfcPropertyDecoder successfully decodes the Move string value" )
      {
        AssertValidGoMoveStrings(propertyDecoder, SgfcPropertyType::B, moveString, -1, -1);
      }
    }

    WHEN( "The property value is a valid Move string but the board size is invalid" )
    {
      auto invalidGoBoardSize = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidGoBoardSizes()) );

      std::string moveStringSgfNotation = "aa";

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(moveStringSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("B");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, invalidGoBoardSize);

      SgfcColor expectedColor = propertyDecoder.GetPropertyType() == SgfcPropertyType::B ? SgfcColor::Black : SgfcColor::White;

      THEN( "SgfcPropertyDecoder fails to decode the Move string value but provides it as ISgfcGoMovePropertyValue without ISgfcGoPoint" )
      {
        AssertInvalidGoMoveStrings(propertyDecoder, SgfcPropertyType::B, moveStringSgfNotation);
      }
    }

    WHEN( "The property value is an invalid Move string" )
    {
      auto testData = GENERATE_COPY( filter(
        // Filter out Move strings that are pass moves - these are valid
        [](std::pair<std::string, SgfcBoardSize> i) { return i.first != SgfcConstants::MovePassString; },
        from_range(TestDataGenerator::GetInvalidGoPointStrings())
      ));

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(testData.first.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("B");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, testData.second);

      SgfcColor expectedColor = propertyDecoder.GetPropertyType() == SgfcPropertyType::B ? SgfcColor::Black : SgfcColor::White;

      THEN( "SgfcPropertyDecoder fails to decode the Move string value but provides it as ISgfcGoMovePropertyValue without ISgfcGoPoint" )
      {
        AssertInvalidGoMoveStrings(propertyDecoder, SgfcPropertyType::B, testData.first);
      }
    }
  }

  GIVEN( "The property value type is Stone and the game type is not Go" )
  {
    WHEN( "The property value is a valid Stone string" )
    {
      std::string stoneString = GENERATE(SgfcConstants::NoneValueString.c_str() , "foo" );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(stoneString.c_str());
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
        REQUIRE( propertySingleValue->GetRawValue() == stoneString );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Stone );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto stoneValue = propertySingleValue->ToStoneValue();
        REQUIRE( stoneValue != nullptr );
        REQUIRE( stoneValue->GetRawStoneValue() == stoneString );
        auto goStoneValue = stoneValue->ToGoStoneValue();
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
      auto stoneStringSgfNotation = std::get<9>(testData);

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(stoneStringSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AB");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, std::get<1>(testData));

      THEN( "SgfcPropertyDecoder successfully decodes the Stone string value" )
      {
        AssertValidGoStoneStrings(propertyDecoder, SgfcPropertyType::AB, stoneStringSgfNotation, std::get<2>(testData), std::get<3>(testData));
      }
    }

    WHEN( "The property value is a valid Stone string but the board size is invalid" )
    {
      auto invalidGoBoardSize = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidGoBoardSizes()) );

      std::string stoneStringSgfNotation = "aa";

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(stoneStringSgfNotation.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AB");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, invalidGoBoardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Stone string value but provides it as ISgfcGoStonePropertyValue without ISgfcGoPoint" )
      {
        AssertInvalidGoStoneStrings(propertyDecoder, SgfcPropertyType::AB, stoneStringSgfNotation);
      }
    }

    WHEN( "The property value is an invalid Stone string" )
    {
      auto testData = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidGoPointStrings()) );

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(testData.first.c_str());
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AB");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, testData.second);

      THEN( "SgfcPropertyDecoder fails to decode the Stone string value but provides it as ISgfcGoStonePropertyValue without ISgfcGoPoint" )
      {
        AssertInvalidGoStoneStrings(propertyDecoder, SgfcPropertyType::AB, testData.first);
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

  GIVEN( "The property value type is List of Points" )
  {
    WHEN( "The property values are decoded" )
    {
      std::string pointStringSgfNotation1 = "aa";
      std::string pointStringSgfNotation2 = "bb";

      PropValue propertyValue2;
      propertyValue2.value = const_cast<char*>(pointStringSgfNotation2.c_str());
      propertyValue2.value2 = nullptr;
      propertyValue2.next = nullptr;

      PropValue propertyValue1;
      propertyValue1.value = const_cast<char*>(pointStringSgfNotation1.c_str());
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
        AssertValidGoPointString(propertySingleValue1, pointStringSgfNotation1, 1, 1);
        auto propertySingleValue2 = propertyValues.back()->ToSingleValue();
        AssertValidGoPointString(propertySingleValue2, pointStringSgfNotation2, 2, 2);
      }
    }
  }

  GIVEN( "The property value type is List of Moves" )
  {
    WHEN( "The property values are decoded" )
    {
      std::string moveString1 = "foo";
      std::string moveString2 = "bar";

      PropValue propertyValue2;
      propertyValue2.value = const_cast<char*>(moveString2.c_str());
      propertyValue2.value2 = nullptr;
      propertyValue2.next = nullptr;

      PropValue propertyValue1;
      propertyValue1.value = const_cast<char*>(moveString1.c_str());
      propertyValue1.value2 = nullptr;
      propertyValue1.next = &propertyValue2;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AA");
      sgfProperty.value = &propertyValue1;
      // Property "AA" is a list of moves only for the Amazons game
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, SgfcGameType::Amazons, SgfcConstants::BoardSizeNone);

      THEN( "SgfcPropertyDecoder successfully decodes the Point string values" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::AA );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 2 );

        auto propertySingleValue1 = propertyValues.front()->ToSingleValue();
        AssertValidMoveStrings(propertySingleValue1, SgfcPropertyType::AA, moveString1);
        auto propertySingleValue2 = propertyValues.back()->ToSingleValue();
        AssertValidMoveStrings(propertySingleValue2, SgfcPropertyType::AA, moveString2);
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
      propertyValue.value = const_cast<char*>(testData.first.c_str());
      propertyValue.value2 = const_cast<char*>(testData.first.c_str());
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("AP");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the composition of two SimpleText string values" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::AP );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );

        REQUIRE( propertyValues.front()->IsComposedValue() == true );
        auto propertyComposedValue = propertyValues.front()->ToComposedValue();

        auto propertySingleValue1 = propertyComposedValue->GetValue1();
        AssertValidSimpleTextString(propertySingleValue1.get(), testData.first, testData.second);
        auto propertySingleValue2 = propertyComposedValue->GetValue2();
        AssertValidSimpleTextString(propertySingleValue2.get(), testData.first, testData.second);
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
      std::string pointString1 = "A1";
      std::string simpleTextString1 = SgfcConstants::NoneValueString;
      int xPosition1 = 1;
      int yPosition1 = 19;
      std::string pointString2 = "16-3";
      std::string simpleTextString2 = "foo";
      int xPosition2 = 16;
      int yPosition2 = 3;

      PropValue propertyValue2;
      propertyValue2.value = const_cast<char*>(pointString2.c_str());
      propertyValue2.value2 = const_cast<char*>(simpleTextString2.c_str());
      propertyValue2.next = nullptr;

      PropValue propertyValue1;
      propertyValue1.value = const_cast<char*>(pointString1.c_str());
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
        AssertValidGoPointString(propertySingleValue1a.get(), pointString1, xPosition1, yPosition1);
        auto propertySingleValue1b = propertyComposedValue1->GetValue2();
        AssertValidSimpleTextString(propertySingleValue1b.get(), simpleTextString1, simpleTextString1);

        auto propertySingleValue2a = propertyComposedValue2->GetValue1();
        AssertValidGoPointString(propertySingleValue2a.get(), pointString2, xPosition2, yPosition2);
        auto propertySingleValue2b = propertyComposedValue2->GetValue2();
        AssertValidSimpleTextString(propertySingleValue2b.get(), simpleTextString2, simpleTextString2);
      }
    }

    WHEN( "The Point strings are invalid and the SimpleText strings are valid" )
    {
      std::string pointString = "foo";
      std::string simpleTextString = "bar";

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(pointString.c_str());
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
        AssertInvalidGoPointString(propertySingleValue1.get(), pointString);
        auto propertySingleValue2 = propertyComposedValue->GetValue2();
        AssertValidSimpleTextString(propertySingleValue2.get(), simpleTextString, simpleTextString);
      }
    }

    WHEN( "The Point strings are valid and the SimpleText strings are invalid" )
    {
      // No tests because there are no invalid SimpleText strings
    }
  }

  GIVEN( "The property value type is a list of composed SimpleText and SimpleText strings and the game type is not Go" )
  {
    WHEN( "Both SimpleText strings are valid" )
    {
      // We are not particularly interested in testing the correctness of value
      // parsing, so we don't need a lot of test values
      std::string simpleTextString1a = "foo";
      std::string simpleTextString1b = SgfcConstants::NoneValueString;
      std::string simpleTextString2a = ":";
      std::string simpleTextString2b = "bar";

      PropValue propertyValue2;
      propertyValue2.value = const_cast<char*>(simpleTextString2a.c_str());
      propertyValue2.value2 = const_cast<char*>(simpleTextString2b.c_str());
      propertyValue2.next = nullptr;

      PropValue propertyValue1;
      propertyValue1.value = const_cast<char*>(simpleTextString1a.c_str());
      propertyValue1.value2 = const_cast<char*>(simpleTextString1b.c_str());
      propertyValue1.next = &propertyValue2;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("MI");
      sgfProperty.value = &propertyValue1;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, SgfcGameType::Backgammon, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the list of composed SimpleText and SimpleText string values" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::MI );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 2 );

        REQUIRE( propertyValues.front()->IsComposedValue() == true );
        auto propertyComposedValue1 = propertyValues.front()->ToComposedValue();
        REQUIRE( propertyValues.back()->IsComposedValue() == true );
        auto propertyComposedValue2 = propertyValues.back()->ToComposedValue();

        auto propertySingleValue1a = propertyComposedValue1->GetValue1();
        AssertValidSimpleTextString(propertySingleValue1a.get(), simpleTextString1a, simpleTextString1a);
        auto propertySingleValue1b = propertyComposedValue1->GetValue2();
        AssertValidSimpleTextString(propertySingleValue1b.get(), simpleTextString1b, simpleTextString1b);

        auto propertySingleValue2a = propertyComposedValue2->GetValue1();
        AssertValidSimpleTextString(propertySingleValue2a.get(), simpleTextString2a, simpleTextString2a);
        auto propertySingleValue2b = propertyComposedValue2->GetValue2();
        AssertValidSimpleTextString(propertySingleValue2b.get(), simpleTextString2b, simpleTextString2b);
      }
    }

    WHEN( "One of the two SimpleText strings is invalid or both SimpleText strings are invalid" )
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

      PropValue propertyValue;
      propertyValue.value = const_cast<char*>(numberString.c_str());
      propertyValue.value2 = const_cast<char*>(simpleTextString.c_str());
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.idstr = const_cast<char*>("FG");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the composed Number and SimpleText string values" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::FG );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );

        REQUIRE( propertyValues.front()->IsComposedValue() == true );
        auto propertyComposedValue = propertyValues.front()->ToComposedValue();

        auto propertySingleValue1 = propertyComposedValue->GetValue1();
        AssertValidNumberString(propertySingleValue1.get(), numberString, numberValue);
        auto propertySingleValue2 = propertyComposedValue->GetValue2();
        AssertValidSimpleTextString(propertySingleValue2.get(), simpleTextString, simpleTextString);
      }
    }

    WHEN( "The property value is a composition of an invalid Number string and a valid SimpleText string" )
    {
      auto numberString = GENERATE_COPY( from_range(TestDataGenerator::GetInvalidNumberStrings()) );
      std::string simpleTextString = "foo";

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
        AssertValidSimpleTextString(propertySingleValue2.get(), simpleTextString, simpleTextString);
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
      std::string pointStringSgfNotation1 = "aa";
      std::string pointStringSgfNotation2 = "bb";

      PropValue propertyValue2;
      propertyValue2.value = const_cast<char*>(pointStringSgfNotation2.c_str());
      propertyValue2.value2 = nullptr;
      propertyValue2.next = nullptr;

      PropValue propertyValue1;
      propertyValue1.value = const_cast<char*>(pointStringSgfNotation1.c_str());
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
        AssertValidGoPointString(propertySingleValue1, pointStringSgfNotation1, 1, 1);
        auto propertySingleValue2 = propertyValues.back()->ToSingleValue();
        AssertValidGoPointString(propertySingleValue2, pointStringSgfNotation2, 2, 2);
      }
    }

    WHEN( "The property values are a list of invalid Point strings" )
    {
      std::string invalidPointString1 = "foo";
      std::string invalidPointString2 = "bar";

      PropValue propertyValue2;
      propertyValue2.value = const_cast<char*>(invalidPointString2.c_str());
      propertyValue2.value2 = nullptr;
      propertyValue2.next = nullptr;

      PropValue propertyValue1;
      propertyValue1.value = const_cast<char*>(invalidPointString1.c_str());
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
        AssertInvalidGoPointString(propertySingleValue1, invalidPointString1);
        auto propertySingleValue2 = propertyValues.back()->ToSingleValue();
        AssertInvalidGoPointString(propertySingleValue2, invalidPointString2);
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
  REQUIRE( numberValue != nullptr );
  REQUIRE_THROWS_AS(
    numberValue->GetNumberValue(),
    std::logic_error);
}

void AssertValidSimpleTextString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& expectedRawValue, const std::string& expectedParsedValue)
{
  REQUIRE( propertySingleValue->GetRawValue() == expectedRawValue );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::SimpleText );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto simpleTextValue = propertySingleValue->ToSimpleTextValue();
  REQUIRE( simpleTextValue != nullptr );
  REQUIRE( simpleTextValue->GetSimpleTextValue() == expectedParsedValue );
}

void AssertValidGoPointStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& pointString, int xPosition, int yPosition)
{
  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  auto propertyValues = propertyDecoder.GetPropertyValues();
  REQUIRE( propertyValues.size() == 1 );
  auto propertySingleValue = propertyValues.front()->ToSingleValue();
  AssertValidGoPointString(propertySingleValue, pointString, xPosition, yPosition);
}

void AssertValidGoPointString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& pointString, int xPosition, int yPosition)
{
  REQUIRE( propertySingleValue->GetRawValue() == pointString );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Point );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto pointValue = propertySingleValue->ToPointValue();
  REQUIRE( pointValue != nullptr );
  REQUIRE( pointValue->GetRawPointValue() == pointString );
  auto goPointValue = pointValue->ToGoPointValue();
  REQUIRE( goPointValue != nullptr );
  auto goPoint = goPointValue->GetGoPoint();
  REQUIRE( goPoint != nullptr );
  REQUIRE( goPoint->GetXPosition(SgfcCoordinateSystem::UpperLeftOrigin) == xPosition );
  REQUIRE( goPoint->GetYPosition(SgfcCoordinateSystem::UpperLeftOrigin) == yPosition );
}

void AssertInvalidGoPointStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& pointString)
{
  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  auto propertyValues = propertyDecoder.GetPropertyValues();
  REQUIRE( propertyValues.size() == 1 );
  auto propertySingleValue = propertyValues.front()->ToSingleValue();
  AssertInvalidGoPointString(propertySingleValue, pointString);
}

void AssertInvalidGoPointString(const ISgfcSinglePropertyValue* propertySingleValue, const std::string& pointString)
{
  REQUIRE( propertySingleValue->GetRawValue() == pointString );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Point );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto pointValue = propertySingleValue->ToPointValue();
  REQUIRE( pointValue != nullptr );
  REQUIRE( pointValue->GetRawPointValue() == pointString );
  auto goPointValue = pointValue->ToGoPointValue();
  REQUIRE( goPointValue != nullptr );
  auto goPoint = goPointValue->GetGoPoint();
  REQUIRE( goPoint == nullptr );
}

void AssertValidGoMoveStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& moveString, int xPosition, int yPosition)
{
  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  auto propertyValues = propertyDecoder.GetPropertyValues();
  REQUIRE( propertyValues.size() == 1 );
  auto propertySingleValue = propertyValues.front()->ToSingleValue();

  AssertValidGoMoveStrings(propertySingleValue, propertyType, moveString, xPosition, yPosition);
}

void AssertValidGoMoveStrings(const ISgfcSinglePropertyValue* propertySingleValue, SgfcPropertyType propertyType, const std::string& moveString, int xPosition, int yPosition)
{
  AssertValidMoveStrings(propertySingleValue, propertyType, moveString);

  SgfcColor expectedColor = propertyType == SgfcPropertyType::B ? SgfcColor::Black : SgfcColor::White;

  auto goMoveValue = propertySingleValue->ToMoveValue()->ToGoMoveValue();
  REQUIRE( goMoveValue != nullptr );
  auto goMove = goMoveValue->GetGoMove();
  REQUIRE( goMove != nullptr );
  REQUIRE( goMove->GetPlayerColor() == expectedColor );
  if (moveString == SgfcConstants::MovePassString)
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

void AssertValidMoveStrings(const ISgfcSinglePropertyValue* propertySingleValue, SgfcPropertyType propertyType, const std::string& moveString)
{
  REQUIRE( propertySingleValue->GetRawValue() == moveString );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Move );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto moveValue = propertySingleValue->ToMoveValue();
  REQUIRE( moveValue != nullptr );
  REQUIRE( moveValue->GetRawMoveValue() == moveString );
}

void AssertInvalidGoMoveStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& moveString)
{
  SgfcColor expectedColor = propertyType == SgfcPropertyType::B ? SgfcColor::Black : SgfcColor::White;

  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  auto propertyValues = propertyDecoder.GetPropertyValues();
  REQUIRE( propertyValues.size() == 1 );
  auto propertySingleValue = propertyValues.front()->ToSingleValue();
  REQUIRE( propertySingleValue->GetRawValue() == moveString );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Move );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto moveValue = propertySingleValue->ToMoveValue();
  REQUIRE( moveValue != nullptr );
  REQUIRE( moveValue->GetRawMoveValue() == moveString );
  auto goMoveValue = moveValue->ToGoMoveValue();
  REQUIRE( goMoveValue != nullptr );
  auto goMove = goMoveValue->GetGoMove();
  REQUIRE( goMove != nullptr );
  REQUIRE( goMove->GetPlayerColor() == expectedColor );
  REQUIRE( goMove->IsPassMove() == false );
  auto goStone = goMove->GetStone();
  REQUIRE( goStone != nullptr );
  REQUIRE( goStone->GetColor() == expectedColor );
  REQUIRE( goMove->GetPlayerColor() == goStone->GetColor() );
  auto goPoint = goStone->GetLocation();
  REQUIRE( goPoint == nullptr );
  REQUIRE( goMove->GetStoneLocation() == nullptr );
}

void AssertValidGoStoneStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& stoneString, int xPosition, int yPosition)
{
  SgfcColor expectedColor = propertyType == SgfcPropertyType::AB ? SgfcColor::Black : SgfcColor::White;

  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  auto propertyValues = propertyDecoder.GetPropertyValues();
  REQUIRE( propertyValues.size() == 1 );
  auto propertySingleValue = propertyValues.front()->ToSingleValue();
  REQUIRE( propertySingleValue->GetRawValue() == stoneString );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Stone );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto stoneValue = propertySingleValue->ToStoneValue();
  REQUIRE( stoneValue != nullptr );
  REQUIRE( stoneValue->GetRawStoneValue() == stoneString );
  auto goStoneValue = stoneValue->ToGoStoneValue();
  REQUIRE( goStoneValue != nullptr );
  auto goStone = goStoneValue->GetGoStone();
  REQUIRE( goStone != nullptr );
  REQUIRE( goStone->GetColor() == expectedColor );
  auto goPoint = goStone->GetLocation();
  REQUIRE( goPoint != nullptr );
  REQUIRE( goPoint->GetXPosition(SgfcCoordinateSystem::UpperLeftOrigin) == xPosition );
  REQUIRE( goPoint->GetYPosition(SgfcCoordinateSystem::UpperLeftOrigin) == yPosition );
}

void AssertInvalidGoStoneStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& stoneString)
{
  SgfcColor expectedColor = propertyType == SgfcPropertyType::AB ? SgfcColor::Black : SgfcColor::White;

  REQUIRE( propertyDecoder.GetPropertyType() == propertyType );
  auto propertyValues = propertyDecoder.GetPropertyValues();
  REQUIRE( propertyValues.size() == 1 );
  auto propertySingleValue = propertyValues.front()->ToSingleValue();
  REQUIRE( propertySingleValue->GetRawValue() == stoneString );
  REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
  REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Stone );
  REQUIRE( propertySingleValue->HasTypedValue() == true );
  auto stoneValue = propertySingleValue->ToStoneValue();
  REQUIRE( stoneValue != nullptr );
  REQUIRE( stoneValue->GetRawStoneValue() == stoneString );
  auto goStoneValue = stoneValue->ToGoStoneValue();
  REQUIRE( goStoneValue != nullptr );
  auto goStone = goStoneValue->GetGoStone();
  REQUIRE( goStone != nullptr );
  REQUIRE( goStone->GetColor() == expectedColor );
  auto goPoint = goStone->GetLocation();
  REQUIRE( goPoint == nullptr );
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
