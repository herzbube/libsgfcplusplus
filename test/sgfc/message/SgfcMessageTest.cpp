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
#include <sgfc/message/SgfcMessage.h>
#include <SgfcConstants.h>

// Unit test library includes
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcMessage is constructed from an SGFC message", "[sgfc-message]" )
{
  SgfcMessageID messageID = SgfcMessageID::CombinationOfPropertiesConverted;
  SgfcMessageType messageType = SgfcMessageType::Warning;
  int lineNumber = 10;
  int columnNumber = 20;
  bool isCriticalMessage = true;
  int libraryInternalNumber = SgfcConstants::LibraryErrorNumberNoError;
  std::string messageText = "message text";
  std::string formattedMessageText = "formatted message text";

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
        libraryInternalNumber,
        messageText,
        formattedMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetLibraryErrorNumber() == libraryInternalNumber );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetFormattedMessageText() == formattedMessageText );
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
        libraryInternalNumber,
        messageText,
        formattedMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetLibraryErrorNumber() == libraryInternalNumber );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetFormattedMessageText() == formattedMessageText );
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
        libraryInternalNumber,
        messageText,
        formattedMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetLibraryErrorNumber() == libraryInternalNumber );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetFormattedMessageText() == formattedMessageText );
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
        libraryInternalNumber,
        messageText,
        formattedMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetLibraryErrorNumber() == libraryInternalNumber );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetFormattedMessageText() == formattedMessageText );
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
        libraryInternalNumber,
        messageText,
        formattedMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetLibraryErrorNumber() == libraryInternalNumber );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetFormattedMessageText() == formattedMessageText );
      }
    }

    WHEN( "An invalid line number is used in a fatal error message" )
    {
      messageType = SgfcMessageType::FatalError;
      columnNumber = SgfcConstants::InvalidColumnNumber;
      isCriticalMessage = false;

      SgfcMessage message(
        messageID,
        messageType,
        lineNumber,
        columnNumber,
        isCriticalMessage,
        libraryInternalNumber,
        messageText,
        formattedMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetLibraryErrorNumber() == libraryInternalNumber );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetFormattedMessageText() == formattedMessageText );
      }
    }

    WHEN( "An invalid column number is used in a fatal error message" )
    {
      messageType = SgfcMessageType::FatalError;
      lineNumber = SgfcConstants::InvalidLineNumber;
      isCriticalMessage = false;

      SgfcMessage message(
        messageID,
        messageType,
        lineNumber,
        columnNumber,
        isCriticalMessage,
        libraryInternalNumber,
        messageText,
        formattedMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetLibraryErrorNumber() == libraryInternalNumber );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetFormattedMessageText() == formattedMessageText );
      }
    }

    WHEN( "A non-zero library error number is used" )
    {
      libraryInternalNumber = GENERATE ( -17, 42 );

      SgfcMessage message(
        messageID,
        messageType,
        lineNumber,
        columnNumber,
        isCriticalMessage,
        libraryInternalNumber,
        messageText,
        formattedMessageText);

      THEN( "The SgfcMessage object has the values passed to the constructor" )
      {
        REQUIRE( message.GetMessageID() == messageID );
        REQUIRE( message.GetMessageType() == messageType );
        REQUIRE( message.GetLineNumber() == lineNumber );
        REQUIRE( message.GetColumnNumber() == columnNumber );
        REQUIRE( message.IsCriticalMessage() == isCriticalMessage );
        REQUIRE( message.GetLibraryErrorNumber() == libraryInternalNumber );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetFormattedMessageText() == formattedMessageText );
      }
    }
  }

  GIVEN( "Invalid parameter values are used" )
  {
    WHEN( "A libsgfc++ message ID is used" )
    {
      messageID = SgfcMessageID::ParseArgumentError;

      THEN( "The SgfcMessage constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcMessage(
            messageID,
            messageType,
            lineNumber,
            columnNumber,
            isCriticalMessage,
            libraryInternalNumber,
            messageText,
            formattedMessageText),
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
            libraryInternalNumber,
            messageText,
            formattedMessageText),
          std::invalid_argument);
      }
    }
  }
}

SCENARIO( "SgfcMessage is constructed from a libsgfc++ message", "[sgfc-message]" )
{
  SgfcMessageID messageID = SgfcMessageID::ParseArgumentError;
  std::string messageText = "message text";

  SgfcMessageType expectedMessageType = SgfcMessageType::FatalError;
  int expectedLineNumber = SgfcConstants::InvalidLineNumber;
  int expectedColumnNumber = SgfcConstants::InvalidColumnNumber;
  bool expectedIsCriticalMessage = false;
  int expectedLibraryInternalNumber = SgfcConstants::LibraryErrorNumberNoError;
  std::string expectedFormattedMessageText = messageText;

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
        REQUIRE( message.GetLibraryErrorNumber() == expectedLibraryInternalNumber );
        REQUIRE( message.GetMessageText() == messageText );
        REQUIRE( message.GetFormattedMessageText() == expectedFormattedMessageText );
      }
    }
  }

  GIVEN( "Invalid parameter values are used" )
  {
    WHEN( "An SGFC message ID is used" )
    {
      // Although SGFC does not actually have a message iD 0, libsgfc++
      // technically treats zero as an SGFC message iD
      messageID = GENERATE(static_cast<SgfcMessageID>(0), SgfcMessageID::CombinationOfPropertiesConverted);

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
