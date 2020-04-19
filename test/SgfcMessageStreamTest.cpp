// Library includes
#include <sgfc/message/SgfcMessageStream.h>
#include <SgfcPrivateConstants.h>

// Unit test library includes
#include <catch2/catch.hpp>

// SGFC includes to be able to invoke the SGFC function PrintError()
extern "C"
{
  #include <../sgfc/all.h>
  #include <../sgfc/protos.h>
}

// Function prototypes used to interact with SGFC behind the back of
// SgfcMessageStream
namespace LibSgfcPlusPlus
{
  void ResetSgfcMessageStream();
}

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcMessageStream acquires message stream content from SGFC", "[sgfc-message]" )
{
  GIVEN( "The message stream is empty" )
  {
    ResetSgfcMessageStream();

    WHEN( "SgfcMessageStream is constructed" )
    {
      SgfcMessageStream messageStream;

      THEN( "The SgfcMessageStream object has no content" )
      {
        auto messageStreamLines = messageStream.GetMessageStreamLines();
        auto rawMessageStreamContent = messageStream.GetRawMessageStreamContent();

        REQUIRE( messageStreamLines.size() == 0 );
        REQUIRE( rawMessageStreamContent == "" );
      }
    }
  }

  GIVEN( "The message stream contains a single line" )
  {
    ResetSgfcMessageStream();

    WriteFormattedStringToLibSgfcPlusPlusMessageStream("%s", "foo");
    // Writing a second time to the stream does not create a new line
    WriteFormattedStringToLibSgfcPlusPlusMessageStream("%s", "bar");

    WHEN( "SgfcMessageStream is constructed" )
    {
      SgfcMessageStream messageStream;

      THEN( "The SgfcMessageStream object has one line of content" )
      {
        auto messageStreamLines = messageStream.GetMessageStreamLines();
        auto rawMessageStreamContent = messageStream.GetRawMessageStreamContent();

        REQUIRE( messageStreamLines.size() == 1 );
        REQUIRE( messageStreamLines.front() == "foobar" );
        REQUIRE( rawMessageStreamContent == "foobar" );
      }
    }

    GIVEN( "The message stream contains two lines using LF as line delimiter" )
    {
      ResetSgfcMessageStream();

      WriteFormattedStringToLibSgfcPlusPlusMessageStream("%s", "foo");
      WriteFormattedStringToLibSgfcPlusPlusMessageStream("%s", "\n");
      WriteFormattedStringToLibSgfcPlusPlusMessageStream("%s", "bar");

      WHEN( "SgfcMessageStream is constructed" )
      {
        SgfcMessageStream messageStream;

        THEN( "The SgfcMessageStream object has two lines of content" )
        {
          auto messageStreamLines = messageStream.GetMessageStreamLines();
          auto rawMessageStreamContent = messageStream.GetRawMessageStreamContent();

          REQUIRE( messageStreamLines.size() == 2 );
          REQUIRE( messageStreamLines.front() == "foo" );
          REQUIRE( messageStreamLines.back() == "bar" );
          REQUIRE( rawMessageStreamContent == "foo\nbar" );
        }
      }
    }

    // The difference to the previous test is that we let PrintError decide
    // what it wants to use as a line delimiter. This ***SHOULD*** be LF, but
    // a future implementation of SGFC might change this to something else.
    // If that happens SgfcMessageStream will break, and by testing it we will
    // notice.
    GIVEN( "The message stream contains two lines using the PrintError-internal line delimiter" )
    {
      ResetSgfcMessageStream();

      // Set up the buffer. For the message type that we want PrintError()
      // needs to scans the buffer to determine the line/column number.
      sgfc = new SGFInfo();
      sgfc->buffer = const_cast<char*>("");  // cast is safe, nobody is going to modify the buffer
      sgfc->start = sgfc->buffer;
      sgfc->b_end = sgfc->start + 1;

      // Without this PrintError() does not output any messages
      memset(error_enabled, TRUE, sizeof(error_enabled));

      PrintError(E_UNEXPECTED_EOF, sgfc->start);
      PrintError(E_UNEXPECTED_EOF, sgfc->start);

      WHEN( "SgfcMessageStream is constructed" )
      {
        SgfcMessageStream messageStream;

        THEN( "The SgfcMessageStream object has two lines of content" )
        {
          std::string expectedMessageLine = "Line:1 Col:1 - Error 10 (critical): unexpected end of file";
          std::string expectedRawMessageStreamContent =
            expectedMessageLine +
            SgfcPrivateConstants::NewlineCharacter +
            expectedMessageLine +
            SgfcPrivateConstants::NewlineCharacter;

          auto messageStreamLines = messageStream.GetMessageStreamLines();
          auto rawMessageStreamContent = messageStream.GetRawMessageStreamContent();

          REQUIRE( messageStreamLines.size() == 2 );
          // The CR character is not recognized by SgfcMessageStream as
          // belonging to the line delimiter. This is an implementation detail
          // that we test here in case
          REQUIRE( messageStreamLines.front() == expectedMessageLine );
          REQUIRE( messageStreamLines.back() == expectedMessageLine );
          REQUIRE( rawMessageStreamContent ==  expectedRawMessageStreamContent);
        }
      }

      delete sgfc;
    }

    GIVEN( "Two SgfcMessageStream object are constructed" )
    {
      ResetSgfcMessageStream();

      WriteFormattedStringToLibSgfcPlusPlusMessageStream("%s", "foo");
      SgfcMessageStream messageStream1;

      WHEN( "The second SgfcMessageStream object is constructed" )
      {
        SgfcMessageStream messageStream2;

        THEN( "The second SgfcMessageStream object has no content" )
        {
          auto messageStream1Lines = messageStream1.GetMessageStreamLines();
          auto rawMessageStream1Content = messageStream1.GetRawMessageStreamContent();

          REQUIRE( messageStream1Lines.size() == 1 );
          REQUIRE( messageStream1Lines.front() == "foo" );
          REQUIRE( rawMessageStream1Content == "foo" );

          auto messageStream2Lines = messageStream2.GetMessageStreamLines();
          auto rawMessageStream2Content = messageStream2.GetRawMessageStreamContent();

          REQUIRE( messageStream2Lines.size() == 0 );
          REQUIRE( rawMessageStream2Content == "" );
        }
      }
    }
  }
}
