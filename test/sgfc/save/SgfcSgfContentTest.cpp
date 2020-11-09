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
        REQUIRE( std::string() == sgfContent.GetFilePath() );
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
        REQUIRE( testData.FileName == sgfContent.GetFilePath() );
      }
    }
  }
}
