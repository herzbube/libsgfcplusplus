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
#include <sgfc/message/SgfcMessageStream.h>
#include <SgfcPrivateConstants.h>
#include <ISgfcMessage.h>
#include <SgfcConstants.h>

// Unit test library includes
#include <catch2/catch.hpp>

// SGFC includes
extern "C"
{
  #include <../sgfc/src/all.h>
  #include <../sgfc/src/protos.h>
}

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcMessageStream acquires message stream content from SGFC", "[sgfc-message]" )
{
  SGFInfo* sgfc = SetupSGFInfo(NULL);

  GIVEN( "The message stream is empty" )
  {
    SgfcMessageStream messageStream;

    WHEN( "SgfcMessageStream is queried" )
    {
      auto messages = messageStream.GetMessagees();

      THEN( "The SgfcMessageStream object has no messages" )
      {
        REQUIRE( messages.size() == 0 );
      }
    }
  }

  GIVEN( "The message stream contains a single message" )
  {
    SgfcMessageStream messageStream;

    PrintError(E_UNEXPECTED_EOF, sgfc, 1, 1);

    WHEN( "SgfcMessageStream is queried" )
    {
      auto messages = messageStream.GetMessagees();
      std::string expectedMessageText = "Line:1 Col:1 - Error 10 (critical): unexpected end of file";

      THEN( "The SgfcMessageStream object returns one message" )
      {
        REQUIRE( messages.size() == 1 );
        auto message = messages.front();
        REQUIRE( message->GetFormattedMessageText() == expectedMessageText );
      }
    }
  }

  GIVEN( "The message stream contains two messages" )
  {
    SgfcMessageStream messageStream;

    PrintError(E_UNEXPECTED_EOF, sgfc, 1, 1);
    PrintError(E_MORE_THAN_ONE_TREE, sgfc);

    WHEN( "SgfcMessageStream is queried" )
    {
      auto messages = messageStream.GetMessagees();
      std::string expectedMessageText1 = "Line:1 Col:1 - Error 10 (critical): unexpected end of file";
      std::string expectedMessageText2 = "Error 60: file contains more than one game tree";

      THEN( "The SgfcMessageStream object has two lines of content" )
      {
        REQUIRE( messages.size() == 2 );
        auto message1 = messages.front();
        REQUIRE( message1->GetFormattedMessageText() == expectedMessageText1 );
        auto message2 = messages.back();
        REQUIRE( message2->GetFormattedMessageText() == expectedMessageText2 );
      }
    }
  }

  GIVEN( "Two SgfcMessageStream object are constructed" )
  {
    SgfcMessageStream messageStream1;

    WHEN( "The second SgfcMessageStream object is constructed" )
    {
      THEN( "The second SgfcMessageStream constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcMessageStream(),
          std::logic_error);
      }
    }
  }

  FreeSGFInfo(sgfc);
}

SCENARIO( "SgfcMessageStream processes messages with varying content", "[sgfc-message]" )
{
  SGFInfo* sgfc = SetupSGFInfo(NULL);

  GIVEN( "A non-critical warning message is processed" )
  {
    SgfcMessageStream messageStream;
    PrintError(WS_UNKNOWN_PROPERTY, sgfc, 1, 1, "XX", "found");

    WHEN( "SgfcMessageStream is queried" )
    {
      auto messages = messageStream.GetMessagees();
      std::string expectedMessageText = "unknown property <XX> found";
      std::string expectedFormattedText = "Line:1 Col:1 - Warning 35: " + expectedMessageText;

      THEN( "The resulting SgfcMessage object has the expected values" )
      {
        REQUIRE( messages.size() == 1 );
        auto message = messages.front();

        REQUIRE( message->GetMessageID() == SgfcMessageID::UnknownPropertyDeleted );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Warning );
        REQUIRE( message->GetLineNumber() == 1 );
        REQUIRE( message->GetColumnNumber() == 1 );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetLibraryErrorNumber() == SgfcConstants::LibraryErrorNumberNoError );
        REQUIRE( message->GetMessageText() == expectedMessageText );
        REQUIRE( message->GetFormattedMessageText() == expectedFormattedText );
      }
    }
  }

  GIVEN( "A non-critical error message is processed" )
  {
    SgfcMessageStream messageStream;
    PrintError(E_LC_IN_PROPID, sgfc, 1, 1, "xx");

    WHEN( "SgfcMessageStream is queried" )
    {
      auto messages = messageStream.GetMessagees();
      std::string expectedMessageText = "lowercase char not allowed in property identifier";
      std::string expectedFormattedText = "Line:1 Col:1 - Error 16: " + expectedMessageText;

      THEN( "The resulting SgfcMessage object has the expected values" )
      {
        REQUIRE( messages.size() == 1 );
        auto message = messages.front();

        REQUIRE( message->GetMessageID() == SgfcMessageID::PropertyIdentifierWithLowercaseCharacter );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Error );
        REQUIRE( message->GetLineNumber() == 1 );
        REQUIRE( message->GetColumnNumber() == 1 );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetLibraryErrorNumber() == SgfcConstants::LibraryErrorNumberNoError );
        REQUIRE( message->GetMessageText() == expectedMessageText );
        REQUIRE( message->GetFormattedMessageText() == expectedFormattedText );
      }
    }
  }

  GIVEN( "A fatal error message is processed" )
  {
    SgfcMessageStream messageStream;
    PrintError(FE_NO_SGFDATA, sgfc);

    WHEN( "SgfcMessageStream is queried" )
    {
      auto messages = messageStream.GetMessagees();
      std::string expectedMessageText = "no SGF data found - start mark '(;' missing?";
      std::string expectedFormattedText = "Fatal error 7: " + expectedMessageText;

      THEN( "The resulting SgfcMessage object has the expected values" )
      {
        REQUIRE( messages.size() == 1 );
        auto message = messages.front();

        REQUIRE( message->GetMessageID() == SgfcMessageID::NoSgfData );
        REQUIRE( message->GetMessageType() == SgfcMessageType::FatalError );
        REQUIRE( message->GetLineNumber() == SgfcConstants::InvalidLineNumber );
        REQUIRE( message->GetColumnNumber() == SgfcConstants::InvalidColumnNumber );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetLibraryErrorNumber() == SgfcConstants::LibraryErrorNumberNoError );
        REQUIRE( message->GetMessageText() == expectedMessageText );
        REQUIRE( message->GetFormattedMessageText() == expectedFormattedText );
      }
    }
  }

  GIVEN( "A critical warning message is processed" )
  {
    SgfcMessageStream messageStream;
    PrintError(W_SGF_IN_HEADER, sgfc, 1, 1);

    WHEN( "SgfcMessageStream is queried" )
    {
      auto messages = messageStream.GetMessagees();
      std::string expectedMessageText = "possible SGF data found in front of game-tree (before '(;')";
      std::string expectedFormattedText = "Line:1 Col:1 - Warning 6 (critical): " + expectedMessageText;

      THEN( "The resulting SgfcMessage object has the expected values" )
      {
        REQUIRE( messages.size() == 1 );
        auto message = messages.front();

        REQUIRE( message->GetMessageID() == SgfcMessageID::SgfDataBeforeGameTree );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Warning );
        REQUIRE( message->GetLineNumber() == 1 );
        REQUIRE( message->GetColumnNumber() == 1 );
        REQUIRE( message->IsCriticalMessage() == true );
        REQUIRE( message->GetLibraryErrorNumber() == SgfcConstants::LibraryErrorNumberNoError );
        REQUIRE( message->GetMessageText() == expectedMessageText );
        REQUIRE( message->GetFormattedMessageText() == expectedFormattedText );
      }
    }
  }

  GIVEN( "A critical error message is processed" )
  {
    SgfcMessageStream messageStream;
    // false = print it now, don't accumulate
    PrintError(E_ILLEGAL_OUTSIDE_CHAR, sgfc, 1, 1, false, "");

    WHEN( "SgfcMessageStream is queried" )
    {
      auto messages = messageStream.GetMessagees();
      std::string expectedMessageText = "illegal char(s) found: \"\"";
      std::string expectedFormattedText = "Line:1 Col:1 - Error 8 (critical): " + expectedMessageText;

      THEN( "The resulting SgfcMessage object has the expected values" )
      {
        REQUIRE( messages.size() == 1 );
        auto message = messages.front();

        REQUIRE( message->GetMessageID() == SgfcMessageID::IllegalCharacters );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Error );
        REQUIRE( message->GetLineNumber() == 1 );
        REQUIRE( message->GetColumnNumber() == 1 );
        REQUIRE( message->IsCriticalMessage() == true );
        REQUIRE( message->GetLibraryErrorNumber() == SgfcConstants::LibraryErrorNumberNoError );
        REQUIRE( message->GetMessageText() == expectedMessageText );
        REQUIRE( message->GetFormattedMessageText() == expectedFormattedText );
      }
    }
  }

  GIVEN( "A message with line/column numbers is processed" )
  {
    SgfcMessageStream messageStream;
    PrintError(E_UNKNOWN_FILE_FORMAT, sgfc, 1, 1, 5);

    WHEN( "SgfcMessageStream is queried" )
    {
      auto messages = messageStream.GetMessagees();
      std::string expectedMessageText = "unknown file format FF[5] (only able to handle files up to FF[4])";
      std::string expectedFormattedText = "Line:1 Col:1 - Error 46 (critical): " + expectedMessageText;

      THEN( "The resulting SgfcMessage object has the expected values" )
      {
        REQUIRE( messages.size() == 1 );
        auto message = messages.front();

        REQUIRE( message->GetMessageID() == SgfcMessageID::UnknownFileFormat );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Error );
        REQUIRE( message->GetLineNumber() == 1 );
        REQUIRE( message->GetColumnNumber() == 1 );
        REQUIRE( message->IsCriticalMessage() == true );
        REQUIRE( message->GetLibraryErrorNumber() == SgfcConstants::LibraryErrorNumberNoError );
        REQUIRE( message->GetMessageText() == expectedMessageText );
        REQUIRE( message->GetFormattedMessageText() == expectedFormattedText );
      }
    }
  }

  GIVEN( "A message without line/column numbers is processed" )
  {
    SgfcMessageStream messageStream;
    PrintError(E_CRITICAL_NOT_SAVED, sgfc);

    WHEN( "SgfcMessageStream is queried" )
    {
      auto messages = messageStream.GetMessagees();
      std::string expectedMessageText = "file not saved (because of critical errors)";
      std::string expectedFormattedText = "Error 34: " + expectedMessageText;

      THEN( "The resulting SgfcMessage object has the expected values" )
      {
        REQUIRE( messages.size() == 1 );
        auto message = messages.front();

        REQUIRE( message->GetMessageID() == SgfcMessageID::NotSavedBecauseOfCriticalErrors );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Error );
        REQUIRE( message->GetLineNumber() == SgfcConstants::InvalidLineNumber );
        REQUIRE( message->GetColumnNumber() == SgfcConstants::InvalidColumnNumber );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetLibraryErrorNumber() == SgfcConstants::LibraryErrorNumberNoError );
        REQUIRE( message->GetMessageText() == expectedMessageText );
        REQUIRE( message->GetFormattedMessageText() == expectedFormattedText );
      }
    }
  }

  FreeSGFInfo(sgfc);
}
