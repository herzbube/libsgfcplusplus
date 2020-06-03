// Library includes
#include <sgfc/save/SgfcSaveStream.h>
#include <ISgfcSgfContent.h>

// Unit test library includes
#include <catch2/catch.hpp>

// C++ Standard Library includes
#include <sstream>

// Function prototypes used to simulate the behaviour of SGFC
namespace LibSgfcPlusPlus
{
  extern std::stringstream saveStream;
  void CaptureSaveStreamContent(const std::string& saveStreamFileName);
  void ResetSaveStreamContentsAndFileNames();
  void ResetSaveStream();
}

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcSaveStream acquires save stream content from SGFC", "[sgfc-save]" )
{
  GIVEN( "The save stream is empty" )
  {
    ResetSaveStreamContentsAndFileNames();

    WHEN( "SgfcSaveStream is constructed" )
    {
      SgfcSaveStream saveStream;

      THEN( "The SgfcSaveStream object has no content" )
      {
        auto sgfContents = saveStream.GetSgfContents();

        REQUIRE( sgfContents.size() == 0 );
      }
    }
  }

  GIVEN( "The save stream contains a single piece of SGF content" )
  {
    std::string contentString = "foo";
    std::string fileName = "bar";

    ResetSaveStreamContentsAndFileNames();
    LibSgfcPlusPlus::saveStream << contentString;
    CaptureSaveStreamContent(fileName);
    ResetSaveStream();

    WHEN( "SgfcSaveStream is constructed" )
    {
      SgfcSaveStream saveStream;

      THEN( "The SgfcSaveStream object has one piece of SGF content" )
      {
        auto sgfContents = saveStream.GetSgfContents();

        REQUIRE( sgfContents.size() == 1 );

        auto sgfContent = sgfContents.front();
        REQUIRE( sgfContent->GetSgfContent() == contentString );
        REQUIRE( sgfContent->GetFileName() == fileName );
      }
    }
  }

  GIVEN( "The save stream contains two pieces of SGF content" )
  {
    std::string contentString1 = "foo";
    std::string fileName1 = "foo.sgf";
    std::string contentString2 = "bar";
    std::string fileName2 = "bar.sgf";

    ResetSaveStreamContentsAndFileNames();
    LibSgfcPlusPlus::saveStream << contentString1;
    CaptureSaveStreamContent(fileName1);
    ResetSaveStream();
    LibSgfcPlusPlus::saveStream << contentString2;
    CaptureSaveStreamContent(fileName2);
    ResetSaveStream();

    WHEN( "SgfcSaveStream is constructed" )
    {
      SgfcSaveStream saveStream;

      THEN( "The SgfcSaveStream object has two pieces of SGF content" )
      {
        auto sgfContents = saveStream.GetSgfContents();

        REQUIRE( sgfContents.size() == 2 );

        // Test note: The order in which the pieces of SGF content appear
        // in sgfContents is important: It must match the order in which
        // they were captured.

        auto sgfContent1 = sgfContents.front();
        REQUIRE( sgfContent1->GetSgfContent() == contentString1 );
        REQUIRE( sgfContent1->GetFileName() == fileName1 );

        auto sgfContent2 = sgfContents.back();
        REQUIRE( sgfContent2->GetSgfContent() == contentString2 );
        REQUIRE( sgfContent2->GetFileName() == fileName2 );
      }
    }
  }

  GIVEN( "Two SgfcSaveStream object are constructed" )
  {
    std::string contentString = "foo";
    std::string fileName = "bar";

    ResetSaveStreamContentsAndFileNames();
    LibSgfcPlusPlus::saveStream << contentString;
    CaptureSaveStreamContent(fileName);
    ResetSaveStream();

    SgfcSaveStream saveStream1;

    WHEN( "The second SgfcSaveStream object is constructed" )
    {
      SgfcSaveStream saveStream2;

      THEN( "The second SgfcSaveStream object has no content" )
      {
        auto sgfContents1 = saveStream1.GetSgfContents();

        REQUIRE( sgfContents1.size() == 1 );

        auto sgfContent1 = sgfContents1.front();
        REQUIRE( sgfContent1->GetSgfContent() == contentString );
        REQUIRE( sgfContent1->GetFileName() == fileName );

        auto sgfContents2 = saveStream2.GetSgfContents();

        REQUIRE( sgfContents2.size() == 0 );
      }
    }
  }
}
