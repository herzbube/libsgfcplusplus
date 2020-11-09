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
#include <sgfc/save/SgfcSaveStream.h>
#include <sgfc/message/SgfcMessageStream.h>
#include <ISgfcSgfContent.h>

// Unit test library includes
#include <catch2/catch.hpp>

// SGFC includes
extern "C"
{
  #include <../sgfc/src/all.h>
  #include <../sgfc/src/protos.h>
}

using namespace LibSgfcPlusPlus;


static void SetupEmptySgfInfo(SGFInfo* sgfInfo, char* buffer, size_t bufferSize);


SCENARIO( "SgfcSaveStream acquires save stream content from SGFC", "[sgfc-save]" )
{
  // We need this to suppress SGFC messages on stdout
  SgfcMessageStream messageStream;

  SGFInfo* sgfInfo = SetupSGFInfo(NULL, SetupSaveBufferIO(NULL));
  int (*originalOpenHook)(struct SaveFileHandler *, const char *, const char *) = sgfInfo->sfh->open;
  int (*originalCloseHook)(struct SaveFileHandler *, U_LONG) = sgfInfo->sfh->close;

  char inputContent[] = "(;)";
  std::string expectedSaveContent = "(;FF[4]GM[1]SZ[19]AP[SGFC:1.18])\n";
  SetupEmptySgfInfo(sgfInfo, inputContent, strlen(inputContent) + 1);
  LoadSGFFromFileBuffer(sgfInfo);
  ParseSGF(sgfInfo);

  std::string fileName = "foo";

  GIVEN( "SgfcSaveStream is constructed" )
  {
    WHEN( "SgfcSaveStream is constructed" )
    {
      SgfcSaveStream saveStream(sgfInfo);

      THEN( "The SgfcSaveStream object reconfigures some hooks/callbacks" )
      {
        REQUIRE( sgfInfo->sfh->open != originalOpenHook );
        REQUIRE( sgfInfo->sfh->close != originalCloseHook );
      }
    }
  }

  GIVEN( "SgfcSaveStream is destroyed" )
  {
    WHEN( "SgfcSaveStream is destroyed" )
    {
      THEN( "The SgfcSaveStream object restores the original hooks/callbacks" )
      {
        {
          SgfcSaveStream saveStream(sgfInfo);
          REQUIRE( sgfInfo->sfh->open != originalOpenHook );
          REQUIRE( sgfInfo->sfh->close != originalCloseHook );
        }
        REQUIRE( sgfInfo->sfh->open == originalOpenHook );
        REQUIRE( sgfInfo->sfh->close == originalCloseHook );
      }
    }
  }

  GIVEN( "The save stream is empty" )
  {
    SgfcSaveStream saveStream(sgfInfo);

    WHEN( "SgfcSaveStream is queried" )
    {
      auto sgfContents = saveStream.GetSgfContents();

      THEN( "The SgfcSaveStream object has no content" )
      {
        REQUIRE( sgfContents.size() == 0 );
      }
    }
  }

  GIVEN( "The save stream contains a single piece of SGF content" )
  {
    SgfcSaveStream saveStream(sgfInfo);

    SaveSGF(sgfInfo, fileName.c_str());

    WHEN( "SgfcSaveStream is queried" )
    {
      auto sgfContents = saveStream.GetSgfContents();

      THEN( "The SgfcSaveStream object has one piece of SGF content" )
      {
        REQUIRE( sgfContents.size() == 1 );

        auto sgfContent = sgfContents.front();
        REQUIRE( sgfContent->GetSgfContent() == expectedSaveContent );
        REQUIRE( sgfContent->GetFilePath() == fileName );
      }
    }
  }

  GIVEN( "The save stream contains two pieces of SGF content" )
  {
    SgfcSaveStream saveStream(sgfInfo);

    SaveSGF(sgfInfo, fileName.c_str());

    SGFInfo* sgfInfo2 = SetupSGFInfo(NULL, SetupSaveBufferIO(NULL));
    // Redirect hooks/callbacks to be the same as the ones that were
    // installed by SgfcSaveStream in sgfInfo. If we don't do this the
    // SgfcSaveStream object does not see the output of the second invocation
    // of SaveSGF().
    sgfInfo2->sfh->open = sgfInfo->sfh->open;
    sgfInfo2->sfh->close = sgfInfo->sfh->close;

    // Repeat the setup stuff at the beginning of the scenario
    char inputContent2[] = "(;C[a comment])";
    std::string expectedSaveContent2 = "(;FF[4]GM[1]SZ[19]AP[SGFC:1.18]C[a comment])\n";
    SetupEmptySgfInfo(sgfInfo2, inputContent2, strlen(inputContent2) + 1);
    LoadSGFFromFileBuffer(sgfInfo2);
    ParseSGF(sgfInfo2);

    std::string fileName2 = "bar";
    SaveSGF(sgfInfo2, fileName2.c_str());

    sgfInfo2->buffer = NULL;
    FreeSGFInfo(sgfInfo2);

    WHEN( "SgfcSaveStream is queried" )
    {
      auto sgfContents = saveStream.GetSgfContents();

      THEN( "The SgfcSaveStream object has two pieces of SGF content" )
      {
        REQUIRE( sgfContents.size() == 2 );

        // Test note: The order in which the pieces of SGF content appear
        // in sgfContents is important: It must match the order in which
        // they were captured.

        auto sgfContent1 = sgfContents.front();
        REQUIRE( sgfContent1->GetSgfContent() == expectedSaveContent );
        REQUIRE( sgfContent1->GetFilePath() == fileName );

        auto sgfContent2 = sgfContents.back();
        REQUIRE( sgfContent2->GetSgfContent() == expectedSaveContent2 );
        REQUIRE( sgfContent2->GetFilePath() == fileName2 );
      }
    }
  }

  GIVEN( "Two SgfcSaveStream object are constructed" )
  {
    SgfcSaveStream saveStream(sgfInfo);

    WHEN( "The second SgfcSaveStream object is constructed" )
    {
      THEN( "The second SgfcSaveStream object has no content" )
      {
        REQUIRE_THROWS_AS(
          SgfcSaveStream(sgfInfo),
          std::logic_error);
      }
    }
  }

  sgfInfo->buffer = NULL;
  FreeSGFInfo(sgfInfo);
}

void SetupEmptySgfInfo(SGFInfo* sgfInfo, char* buffer, size_t bufferSize)
{
  sgfInfo->buffer = buffer;
  sgfInfo->start = sgfInfo->buffer;
  sgfInfo->b_end = sgfInfo->start + bufferSize;
  sgfInfo->root = nullptr;
  sgfInfo->tree = nullptr;
}
