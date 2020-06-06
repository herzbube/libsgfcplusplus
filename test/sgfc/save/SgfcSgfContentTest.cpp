// Library includes
#include <sgfc/save/SgfcSgfContent.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcSgfContent is constructed", "[public-api]" )
{
  GIVEN( "The default constructor is used" )
  {
    WHEN( "SgfcSgfContent is constructed" )
    {
      SgfcSgfContent sgfContent;

      THEN( "SgfcSgfContent has no content" )
      {
        REQUIRE( std::string() == sgfContent.GetSgfContent() );
        REQUIRE( std::string() == sgfContent.GetFileName() );
      }
    }
  }

  GIVEN( "The constructor that takes content and filename arguments is used" )
  {
    struct TestData
    {
      std::string Content;
      std::string FileName;
    };
    auto testData = GENERATE(
      TestData { "", "" },
      TestData { "foo", "" },
      TestData { "", "bar" },
      TestData { "foo", "bar" }
    );

    WHEN( "SgfcSgfContent is constructed" )
    {
      SgfcSgfContent sgfContent(testData.Content, testData.FileName);

      THEN( "SgfcSgfContent has the expected content and file name" )
      {
        REQUIRE( testData.Content == sgfContent.GetSgfContent() );
        REQUIRE( testData.FileName == sgfContent.GetFileName() );
      }
    }
  }
}
