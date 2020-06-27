// Library includes
#include "../TestDataGenerator.h"
#include <ISgfcColorPropertyValue.h>
#include <ISgfcDoublePropertyValue.h>
#include <ISgfcNumberPropertyValue.h>
#include <ISgfcRealPropertyValue.h>
#include <ISgfcSimpleTextPropertyValue.h>
#include <ISgfcSinglePropertyValue.h>
#include <ISgfcTextPropertyValue.h>
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
      // SGF defines the None value type to be en empty string. We add nullptr
      // and an arbitrary string to the list of values because we expect
      // SgfcPropertyDecoder to ignore any property values when the property
      // type mandates value type None.
      std::vector<const char*> v = { "", nullptr, "foo" };
      propertyValue.value = const_cast<char*>(GENERATE_COPY( from_range(v) ));

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

      Property sgfProperty;
      sgfProperty.id = TKN_GC;
      sgfProperty.idstr = const_cast<char*>("GC");
      sgfProperty.value = &propertyValue;
      SgfcPropertyDecoder propertyDecoder(&sgfProperty, gameType, boardSize);

      THEN( "SgfcPropertyDecoder successfully decodes the SimpleText string value" )
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
}
