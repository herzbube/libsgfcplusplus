// Library includes
#include "../TestDataGenerator.h"
#include <ISgfcColorPropertyValue.h>
#include <ISgfcDoublePropertyValue.h>
#include <ISgfcGoMove.h>
#include <ISgfcGoMovePropertyValue.h>
#include <ISgfcGoPoint.h>
#include <ISgfcGoPointPropertyValue.h>
#include <ISgfcGoStone.h>
#include <ISgfcMovePropertyValue.h>
#include <ISgfcNumberPropertyValue.h>
#include <ISgfcPointPropertyValue.h>
#include <ISgfcRealPropertyValue.h>
#include <ISgfcSimpleTextPropertyValue.h>
#include <ISgfcSinglePropertyValue.h>
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


void AssertValidGoMoveStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& moveString, int xPosition, int yPosition);
void AssertInvalidGoMoveStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& moveString);


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
          std::logic_error);
      }
    }

    WHEN( "SgfcPropertyDecoder is constructed with a nullptr ID string" )
    {
      sgfProperty.idstr = nullptr;

      THEN( "The SgfcPropertyDecoder constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder(&sgfProperty, gameType, boardSize),
          std::logic_error);
      }
    }

    WHEN( "SgfcPropertyDecoder is constructed with a nullptr PropValue object" )
    {
      sgfProperty.value = nullptr;

      THEN( "The SgfcPropertyDecoder constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder(&sgfProperty, gameType, boardSize),
          std::logic_error);
      }
    }

    WHEN( "SgfcPropertyDecoder is constructed with an unexpected ID enumeration value" )
    {
      sgfProperty.id = static_cast<token>(12345);

      THEN( "The SgfcPropertyDecoder constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcPropertyDecoder(&sgfProperty, gameType, boardSize),
          std::logic_error);
      }
    }

    WHEN( "SgfcPropertyDecoder is constructed with mismatching ID string and ID enumeration value" )
    {
      sgfProperty.id = TKN_SZ;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder uses the ID enumeration value to determine the property type" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::SZ );
        REQUIRE( propertyDecoder.GetPropertyName() == propertyName );
      }
    }

    WHEN( "SgfcPropertyDecoder is constructed with ID enumeration value None or Unknown" )
    {
      sgfProperty.id = GENERATE( TKN_NONE, TKN_UNKNOWN );
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder converts the ID enumeration value to property type Unknown" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::Unknown );
        REQUIRE( propertyDecoder.GetPropertyName() == propertyName );
      }
    }

    WHEN( "SgfcPropertyDecoder is constructed with any ID enumeration value that is not None or Unknown" )
    {
      int firstIdToken = TKN_B;
      int lastIdToken = TKN_EX;
      sgfProperty.id = static_cast<token>(GENERATE_COPY( range(firstIdToken, lastIdToken) ));
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder converts the ID enumeration value to a property type that is not Unknown" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() != SgfcPropertyType::Unknown );
        REQUIRE( propertyDecoder.GetPropertyName() == propertyName );
      }
    }
  }
}

SCENARIO( "SgfcPropertyDecoder is constructed with a property that is a basic value type", "[parsing]" )
{
  SgfcGameType gameType = SgfcGameType::Go;
  SgfcBoardSize boardSize = { 19, 19 };

  GIVEN( "The property value type is None" )
  {
    WHEN( "The property value is decoded" )
    {
      PropValue propertyValue;
      // SGF defines the None value type to be an empty string. We add nullptr
      // and an arbitrary string to the list of values because we expect
      // SgfcPropertyDecoder to ignore any property values when the property
      // type mandates value type None.
      std::vector<const char*> v = { SgfcConstants::NoneValueString.c_str(), nullptr, "foo" };
      propertyValue.value = const_cast<char*>(GENERATE_COPY( from_range(v) ));
      propertyValue.value2 = nullptr;
      propertyValue.next = nullptr;

      Property sgfProperty;
      sgfProperty.id = TKN_DO;
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
      sgfProperty.id = TKN_MN;
      sgfProperty.idstr = const_cast<char*>("MN");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the Number string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::MN );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == testData.first );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Number );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto numberValue = propertySingleValue->ToNumberValue();
        REQUIRE( numberValue != nullptr );
        REQUIRE( numberValue->GetNumberValue() == testData.second );
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
      sgfProperty.id = TKN_MN;
      sgfProperty.idstr = const_cast<char*>("MN");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Number string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::MN );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == stringValue );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() > 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Number );
        REQUIRE( propertySingleValue->HasTypedValue() == false );
        auto numberValue = propertySingleValue->ToNumberValue();
        REQUIRE( numberValue != nullptr );
        REQUIRE_THROWS_AS(
          numberValue->GetNumberValue(),
          std::logic_error);
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
      sgfProperty.id = TKN_TM;
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
      sgfProperty.id = TKN_TM;
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
      sgfProperty.id = TKN_DM;
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
      sgfProperty.id = TKN_DM;
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
      sgfProperty.id = TKN_PL;
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
      sgfProperty.id = TKN_PL;
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
      sgfProperty.id = TKN_N;
      sgfProperty.idstr = const_cast<char*>("N");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the SimpleText string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::N );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == testData.first );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::SimpleText );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto simpleTextValue = propertySingleValue->ToSimpleTextValue();
        REQUIRE( simpleTextValue != nullptr );
        REQUIRE( simpleTextValue->GetSimpleTextValue() == testData.second );
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
      sgfProperty.id = TKN_GC;
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
      sgfProperty.id = TKN_SE;
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
      sgfProperty.id = TKN_AE;
      sgfProperty.idstr = const_cast<char*>("AE");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, std::get<1>(testData));

      THEN( "SgfcPropertyDecoder successfully decodes the Point string value" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::AE );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == pointStringSgfNotation );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Point );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto pointValue = propertySingleValue->ToPointValue();
        REQUIRE( pointValue != nullptr );
        REQUIRE( pointValue->GetRawPointValue() == pointStringSgfNotation );
        auto goPointValue = pointValue->ToGoPointValue();
        REQUIRE( goPointValue != nullptr );
        auto goPoint = goPointValue->GetGoPoint();
        REQUIRE( goPoint != nullptr );
        REQUIRE( goPoint->GetXPosition(SgfcCoordinateSystem::UpperLeftOrigin) == std::get<2>(testData) );
        REQUIRE( goPoint->GetYPosition(SgfcCoordinateSystem::UpperLeftOrigin) == std::get<3>(testData) );
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
      sgfProperty.id = TKN_AE;
      sgfProperty.idstr = const_cast<char*>("AE");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, invalidGoBoardSize);

      THEN( "SgfcPropertyDecoder fails to decode the Point string value but provides it as ISgfcGoPointPropertyValue without ISgfcGoPoint" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::AE );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == pointStringSgfNotation );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Point );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto pointValue = propertySingleValue->ToPointValue();
        REQUIRE( pointValue != nullptr );
        REQUIRE( pointValue->GetRawPointValue() == pointStringSgfNotation );
        auto goPointValue = pointValue->ToGoPointValue();
        REQUIRE( goPointValue != nullptr );
        auto goPoint = goPointValue->GetGoPoint();
        REQUIRE( goPoint == nullptr );
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
      sgfProperty.id = TKN_AE;
      sgfProperty.idstr = const_cast<char*>("AE");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, testData.second);

      THEN( "SgfcPropertyDecoder fails to decode the Point string value but provides it as ISgfcGoPointPropertyValue without ISgfcGoPoint" )
      {
        REQUIRE( propertyDecoder.GetPropertyType() == SgfcPropertyType::AE );
        auto propertyValues = propertyDecoder.GetPropertyValues();
        REQUIRE( propertyValues.size() == 1 );
        auto propertySingleValue = propertyValues.front()->ToSingleValue();
        REQUIRE( propertySingleValue->GetRawValue() == testData.first );
        REQUIRE( propertySingleValue->GetTypeConversionErrorMessage().size() == 0 );
        REQUIRE( propertySingleValue->GetValueType() == SgfcPropertyValueType::Point );
        REQUIRE( propertySingleValue->HasTypedValue() == true );
        auto pointValue = propertySingleValue->ToPointValue();
        REQUIRE( pointValue != nullptr );
        REQUIRE( pointValue->GetRawPointValue() == testData.first );
        auto goPointValue = pointValue->ToGoPointValue();
        REQUIRE( goPointValue != nullptr );
        auto goPoint = goPointValue->GetGoPoint();
        REQUIRE( goPoint == nullptr );
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
      sgfProperty.id = TKN_B;
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
      sgfProperty.id = TKN_B;
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
      sgfProperty.id = TKN_B;
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
      sgfProperty.id = TKN_B;
      sgfProperty.idstr = const_cast<char*>("B");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, invalidGoBoardSize);

      SgfcColor expectedColor = sgfProperty.id == TKN_B ? SgfcColor::Black : SgfcColor::White;

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
      sgfProperty.id = TKN_B;
      sgfProperty.idstr = const_cast<char*>("B");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, testData.second);

      SgfcColor expectedColor = sgfProperty.id == TKN_B ? SgfcColor::Black : SgfcColor::White;

      THEN( "SgfcPropertyDecoder fails to decode the Move string value but provides it as ISgfcGoMovePropertyValue without ISgfcGoPoint" )
      {
        AssertInvalidGoMoveStrings(propertyDecoder, SgfcPropertyType::B, testData.first);
      }
    }
  }
}

void AssertValidGoMoveStrings(const SgfcPropertyDecoder& propertyDecoder, SgfcPropertyType propertyType, const std::string& moveString, int xPosition, int yPosition)
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
