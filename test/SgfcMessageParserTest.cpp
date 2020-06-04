// Library includes
#include <ISgfcMessage.h>
#include <sgfc/message/SgfcMessageParser.h>
#include <SgfcConstants.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcMessageParser parses an SGFC message", "[sgfc-message]" )
{
  GIVEN( "The message has an expected format" )
  {
    WHEN( "A non-critical warning message is parsed" )
    {
      std::string messageText = "unknown property <XX> found";
      std::string rawMessageText = "Line:42 Col:1 - Warning 35: " + messageText;
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The SgfcMessage object has the expected values" )
      {
        REQUIRE( message->GetMessageID() == 35 );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Warning );
        REQUIRE( message->GetLineNumber() == 42 );
        REQUIRE( message->GetColumnNumber() == 1 );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "A critical warning message is parsed" )
    {
      std::string messageText = "possible SGF data found in front of game-tree (before '(;')";
      std::string rawMessageText = "Line:2 Col:7 - Warning 6 (critical): " + messageText;
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The SgfcMessage object has the expected values" )
      {
        REQUIRE( message->GetMessageID() == 6 );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Warning );
        REQUIRE( message->GetLineNumber() == 2 );
        REQUIRE( message->GetColumnNumber() == 7 );
        REQUIRE( message->IsCriticalMessage() == true );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "A warning message without line/column number is parsed" )
    {
      // There's currently no known SGFC warning message without line/column
      // number, so we just make one up
      std::string messageText = "foo";
      std::string rawMessageText = "Warning 255: " + messageText;
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The SgfcMessage object has the expected values" )
      {
        REQUIRE( message->GetMessageID() == 255 );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Warning );
        REQUIRE( message->GetLineNumber() == SgfcConstants::InvalidLineNumber );
        REQUIRE( message->GetColumnNumber() == SgfcConstants::InvalidColumnNumber );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "A non-critical error message is parsed" )
    {
      std::string messageText = "lowercase char not allowed in property identifier";
      std::string rawMessageText = "Line:1 Col:10 - Error 16: " + messageText;
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The SgfcMessage object has the expected values" )
      {
        REQUIRE( message->GetMessageID() == 16 );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Error );
        REQUIRE( message->GetLineNumber() == 1 );
        REQUIRE( message->GetColumnNumber() == 10 );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "A critical error message is parsed" )
    {
      std::string messageText = "illegal char(s) found: \"fsgdf\"";
      std::string rawMessageText = "Line:2 Col:56 - Error 8 (critical): " + messageText;
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The SgfcMessage object has the expected values" )
      {
        REQUIRE( message->GetMessageID() == 8 );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Error );
        REQUIRE( message->GetLineNumber() == 2 );
        REQUIRE( message->GetColumnNumber() == 56 );
        REQUIRE( message->IsCriticalMessage() == true );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "An error message without line/column number is parsed" )
    {
      std::string messageText = "file contains more than one game tree";
      std::string rawMessageText = "Error 60: " + messageText;
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The SgfcMessage object has the expected values" )
      {
        REQUIRE( message->GetMessageID() == 60 );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Error );
        REQUIRE( message->GetLineNumber() == SgfcConstants::InvalidLineNumber );
        REQUIRE( message->GetColumnNumber() == SgfcConstants::InvalidColumnNumber );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "A fatal error message without line or column number is parsed" )
    {
      std::string messageText = "could not find start mark '(;' - no SGF data found";
      std::string rawMessageText = "Fatal error 7: " + messageText;
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The SgfcMessage object has the expected values" )
      {
        REQUIRE( message->GetMessageID() == 7 );
        REQUIRE( message->GetMessageType() == SgfcMessageType::FatalError );
        REQUIRE( message->GetLineNumber() == SgfcConstants::InvalidLineNumber );
        REQUIRE( message->GetColumnNumber() == SgfcConstants::InvalidColumnNumber );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "A fatal error message with line and column number is parsed" )
    {
      std::string messageText = "unknown file format (only able to handle files up to FF[4])";
      std::string rawMessageText = "Line:1 Col:5 - Fatal error 46: " + messageText;
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The SgfcMessage object has the expected values" )
      {
        REQUIRE( message->GetMessageID() == 46 );
        REQUIRE( message->GetMessageType() == SgfcMessageType::FatalError );
        REQUIRE( message->GetLineNumber() == 1 );
        REQUIRE( message->GetColumnNumber() == 5 );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }
  }

  GIVEN( "The message has an unexpected format" )
  {
    WHEN( "A random text is parsed" )
    {
      std::string rawMessageText = "foo bar baz";
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The text is treated as a fatal error message" )
      {
        REQUIRE( message->GetMessageID() == SgfcConstants::UnknownSgfcMessageID );
        REQUIRE( message->GetMessageType() == SgfcMessageType::FatalError );
        REQUIRE( message->GetLineNumber() == SgfcConstants::InvalidLineNumber );
        REQUIRE( message->GetColumnNumber() == SgfcConstants::InvalidColumnNumber );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == rawMessageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "The message contains consecutive whitespace" )
    {
      std::string messageText = "unknown property <XX> found";
      std::string rawMessageText = "Line:42     Col:1    -      Warning    35:     unknown   property   <XX>    found";
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The consecutive whitespace is condensed into a single space character" )
      {
        REQUIRE( message->GetMessageID() == 35 );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Warning );
        REQUIRE( message->GetLineNumber() == 42 );
        REQUIRE( message->GetColumnNumber() == 1 );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "The message contains whitespace other than space characters" )
    {
      std::string messageText = "unknown property <XX> found";
      std::string rawMessageText = "Line:42     Col:1  \r  -  \n    Warning  \t  35:  \r\n   unknown   property   <XX>    found";
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The special whitespace is treated just like space characters" )
      {
        REQUIRE( message->GetMessageID() == 35 );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Warning );
        REQUIRE( message->GetLineNumber() == 42 );
        REQUIRE( message->GetColumnNumber() == 1 );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "The message contains whitespace both at the start and the end" )
    {
      std::string messageText = "unknown property <XX> found";
      std::string rawMessageText = "   Line:42 Col:1 - Warning 35: unknown property <XX> found   ";
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The whitespace at the start and the end of the message is ignored" )
      {
        REQUIRE( message->GetMessageID() == 35 );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Warning );
        REQUIRE( message->GetLineNumber() == 42 );
        REQUIRE( message->GetColumnNumber() == 1 );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "A warning message without message ID is parsed" )
    {
      std::string messageText = "unknown property <XX> found";
      std::string rawMessageText = "Line:42 Col:1 - Warning " + messageText;
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The message can be parsed despite the missing message ID" )
      {
        REQUIRE( message->GetMessageID() == SgfcConstants::UnknownSgfcMessageID );
        REQUIRE( message->GetMessageType() == SgfcMessageType::Warning );
        REQUIRE( message->GetLineNumber() == 42 );
        REQUIRE( message->GetColumnNumber() == 1 );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "A fatal error message without message ID is parsed" )
    {
      std::string messageText = "possible SGF data found in front of game-tree (before '(;')";
      std::string rawMessageText = "Fatal error: " + messageText;
      auto message = SgfcMessageParser::CreateSgfcMessage(rawMessageText);

      THEN( "The message can be parsed despite the missing message ID" )
      {
        REQUIRE( message->GetMessageID() == SgfcConstants::UnknownSgfcMessageID );
        REQUIRE( message->GetMessageType() == SgfcMessageType::FatalError );
        REQUIRE( message->GetLineNumber() == SgfcConstants::InvalidLineNumber );
        REQUIRE( message->GetColumnNumber() == SgfcConstants::InvalidColumnNumber );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == messageText );
        REQUIRE( message->GetRawMessageText() == rawMessageText );
      }
    }

    WHEN( "A message with a non-numeric message ID is parsed" )
    {
      struct TestData
      {
        std::string RawMessageText;
        SgfcMessageType MessageType;
      };
      auto testData = GENERATE(
        TestData { "Warning foo: bar", SgfcMessageType::Warning },
        TestData { "Error foo: bar", SgfcMessageType::Error },
        TestData { "Fatal error foo: bar", SgfcMessageType::FatalError }
      );

      auto message = SgfcMessageParser::CreateSgfcMessage(testData.RawMessageText);

      THEN( "The message can be parsed despite the non-numeric message ID" )
      {
        REQUIRE( message->GetMessageID() == SgfcConstants::UnknownSgfcMessageID );
        REQUIRE( message->GetMessageType() == testData.MessageType );
        REQUIRE( message->GetLineNumber() == SgfcConstants::InvalidLineNumber );
        REQUIRE( message->GetColumnNumber() == SgfcConstants::InvalidColumnNumber );
        REQUIRE( message->IsCriticalMessage() == false );
        REQUIRE( message->GetMessageText() == "foo: bar" );
        REQUIRE( message->GetRawMessageText() == testData.RawMessageText );
      }
    }
  }
}
