// Library includes
#include <sgfc/message/SgfcMessage.h>
#include <SgfcConstants.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcMessage is constructed from an SGFC message", "[sgfc-message]" )
{
  int messageID = 42;
  SgfcMessageType messageType = SgfcMessageType::Warning;
  int lineNumber = 10;
  int columnNumber = 20;
  bool isCriticalMessage = true;
  std::string messageText = "message text";
  std::string rawMessageText = "raw message text";

  GIVEN( "Valid parameter values are used" )
  {
    WHEN( "A warning message is constructed" )
    {
      SgfcMessage message(
        messageID,
        messageType,
        lineNumber,
        columnNumber,
        isCriticalMessage,
        messageText,
        rawMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "An error message is constructed" )
    {
      messageType = SgfcMessageType::Error;

      SgfcMessage message(
        messageID,
        messageType,
        lineNumber,
        columnNumber,
        isCriticalMessage,
        messageText,
        rawMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "A fatal error message is constructed" )
    {
      messageType = SgfcMessageType::FatalError;
      lineNumber = SgfcConstants::InvalidLineNumber;
      columnNumber = SgfcConstants::InvalidColumnNumber;
      isCriticalMessage = false;

      SgfcMessage message(
        messageID,
        messageType,
        lineNumber,
        columnNumber,
        isCriticalMessage,
        messageText,
        rawMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetRawMessageText() == rawMessageText );
      }
    }
  }

  GIVEN( "Invalid parameter values are used" )
  {
    WHEN( "A negative message ID is used" )
    {
      messageID = SgfcConstants::ArgumentIsNotAnOptionMessageID;

      THEN( "The SgfcMessage constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcMessage(
            messageID,
            messageType,
            lineNumber,
            columnNumber,
            isCriticalMessage,
            messageText,
            rawMessageText),
          std::invalid_argument);
      }
    }

    WHEN( "An invalid line number is used in a warning message" )
    {
      lineNumber = SgfcConstants::InvalidLineNumber;

      SgfcMessage message(
        messageID,
        messageType,
        lineNumber,
        columnNumber,
        isCriticalMessage,
        messageText,
        rawMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "An invalid column number is used in a warning message" )
    {
      columnNumber = SgfcConstants::InvalidColumnNumber;

      SgfcMessage message(
        messageID,
        messageType,
        lineNumber,
        columnNumber,
        isCriticalMessage,
        messageText,
        rawMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "An invalid line number is used in a fatal error message" )
    {
      messageType = SgfcMessageType::FatalError;
      columnNumber = SgfcConstants::InvalidColumnNumber;
      isCriticalMessage = false;

      THEN( "The SgfcMessage constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcMessage(
            messageID,
            messageType,
            lineNumber,
            columnNumber,
            isCriticalMessage,
            messageText,
            rawMessageText),
          std::invalid_argument);
      }
    }

    WHEN( "An invalid column number is used in a fatal error message" )
    {
      messageType = SgfcMessageType::FatalError;
      lineNumber = SgfcConstants::InvalidLineNumber;
      isCriticalMessage = false;

      THEN( "The SgfcMessage constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcMessage(
            messageID,
            messageType,
            lineNumber,
            columnNumber,
            isCriticalMessage,
            messageText,
            rawMessageText),
          std::invalid_argument);
      }
    }

    WHEN( "An invalid 'is critical message' value is used in a fatal error message" )
    {
      messageType = SgfcMessageType::FatalError;
      lineNumber = SgfcConstants::InvalidLineNumber;
      columnNumber = SgfcConstants::InvalidColumnNumber;

      THEN( "The SgfcMessage constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcMessage(
            messageID,
            messageType,
            lineNumber,
            columnNumber,
            isCriticalMessage,
            messageText,
            rawMessageText),
          std::invalid_argument);
      }
    }
  }
}

SCENARIO( "SgfcMessage is constructed from a libsgfc++ message", "[sgfc-message]" )
{
  int messageID = SgfcConstants::ArgumentIsNotAnOptionMessageID;
  std::string messageText = "message text";

  SgfcMessageType expectedMessageType = SgfcMessageType::FatalError;
  int expectedLineNumber = SgfcConstants::InvalidLineNumber;
  int expectedColumnNumber = SgfcConstants::InvalidColumnNumber;
  bool expectedIsCriticalMessage = false;
  std::string expectedRawMessageText = messageText;

  GIVEN( "Valid parameter values are used" )
  {
    WHEN( "A message is constructed" )
    {
      SgfcMessage message(
        messageID,
        messageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == expectedMessageType );
        REQUIRE( message.GetLineNumber() == expectedLineNumber );
        REQUIRE( message.GetColumnNumber() == expectedColumnNumber );
        REQUIRE( message.IsCriticalMessage() == expectedIsCriticalMessage );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetRawMessageText() == expectedRawMessageText );
      }
    }
  }

  GIVEN( "Invalid parameter values are used" )
  {
    WHEN( "A zero or positive message ID is used" )
    {
      messageID = GENERATE(0, 42);

      THEN( "The SgfcMessage constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcMessage(
            messageID,
            messageText),
          std::invalid_argument);
      }
    }
  }
}
