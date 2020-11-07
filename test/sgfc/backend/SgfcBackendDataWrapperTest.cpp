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
#include <sgfc/backend/SgfcBackendDataWrapper.h>
#include <SgfcPrivateConstants.h>

// Unit test library includes
#include <catch2/catch.hpp>

// SGFC includes to be able to invoke the SGFC function PrintError()
extern "C"
{
  #include <../sgfc/src/all.h>
  #include <../sgfc/src/protos.h>
}

// Function prototypes used to interact with SGFC behind the back of
// SgfcMessageStream
namespace LibSgfcPlusPlus
{
  void ResetSgfcMessageStream();
}

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcBackendDataWrapper does not wrap a copy of an externally-provided content buffer", "[backend]" )
{
  GIVEN( "No external content buffer is provided" )
  {
    WHEN( "SgfcBackendDataWrapper is constructed" )
    {
      SgfcBackendDataWrapper backendDataWrapper;

      THEN( "SgfcBackendDataWrapper wraps no content" )
      {
        auto sgfData = backendDataWrapper.GetSgfData();

        REQUIRE( sgfData != nullptr );

        REQUIRE( sgfData->first == nullptr );
        REQUIRE( sgfData->tail == nullptr );
        REQUIRE( sgfData->tree == nullptr );
        REQUIRE( sgfData->last == nullptr );
        REQUIRE( sgfData->info == nullptr );
        REQUIRE( sgfData->root == nullptr );
        // TODO sgfc reintegration: review commented code
//        REQUIRE( sgfData->name == nullptr );
//        REQUIRE( sgfData->file == nullptr );
        REQUIRE( sgfData->start == nullptr );

        REQUIRE( sgfData->buffer == nullptr );
        REQUIRE( sgfData->b_end == nullptr );
        REQUIRE( sgfData->current == nullptr );
      }
    }
  }
}

SCENARIO( "SgfcBackendDataWrapper wraps a copy of an externally-provided content buffer", "[backend]" )
{
  GIVEN( "An external content buffer that contains an empty string is provided" )
  {
    // Some implementations of malloc return nullptr when a zero-size buffer
    // is requested, others do not.
    void* zeroBuffer = malloc(0);
    bool mallocReturnsNullPtr = (zeroBuffer == nullptr);
    free(zeroBuffer);

    std::string contentBuffer;

    WHEN( "SgfcBackendDataWrapper is constructed" )
    {
      SgfcBackendDataWrapper backendDataWrapper(contentBuffer);

      THEN( "The content buffer copy wrapped by SgfcBackendDataWrapper contains an empty string" )
      {
        auto sgfData = backendDataWrapper.GetSgfData();

        REQUIRE( sgfData != nullptr );

        REQUIRE( sgfData->first == nullptr );
        REQUIRE( sgfData->tail == nullptr );
        REQUIRE( sgfData->tree == nullptr );
        REQUIRE( sgfData->last == nullptr );
        REQUIRE( sgfData->info == nullptr );
        REQUIRE( sgfData->root == nullptr );
        // TODO sgfc reintegration: review commented code
//        REQUIRE( sgfData->name == nullptr );
//        REQUIRE( sgfData->file == nullptr );
        REQUIRE( sgfData->start == nullptr );

        if (mallocReturnsNullPtr)
          REQUIRE( sgfData->buffer == nullptr );
        else
          REQUIRE( sgfData->buffer != nullptr );
        REQUIRE( sgfData->b_end == sgfData->buffer );
        REQUIRE( sgfData->current == sgfData->buffer );
      }
    }
  }

  GIVEN( "An external content buffer that contains a non-empty string is provided" )
  {
    std::string contentBuffer = GENERATE("", "f", "foobar");

    WHEN( "SgfcBackendDataWrapper is constructed" )
    {
      SgfcBackendDataWrapper backendDataWrapper(contentBuffer);

      THEN( "The content buffer copy wrapped by SgfcBackendDataWrapper has the same content as the external content buffer" )
      {
        auto sgfData = backendDataWrapper.GetSgfData();

        REQUIRE( sgfData != nullptr );

        REQUIRE( sgfData->first == nullptr );
        REQUIRE( sgfData->tail == nullptr );
        REQUIRE( sgfData->tree == nullptr );
        REQUIRE( sgfData->last == nullptr );
        REQUIRE( sgfData->info == nullptr );
        REQUIRE( sgfData->root == nullptr );
        // TODO sgfc reintegration: review commented code
//        REQUIRE( sgfData->name == nullptr );
//        REQUIRE( sgfData->file == nullptr );
        REQUIRE( sgfData->start == nullptr );

        REQUIRE( sgfData->buffer != nullptr );
        // sgfData->buffer does not have a zero-byte terminator, we must provide
        // the buffer length
        REQUIRE( std::string(sgfData->buffer, contentBuffer.size()) == contentBuffer );
        REQUIRE( sgfData->b_end == sgfData->buffer + contentBuffer.size() );
        // current must point to the beginning of the buffer so that parsing
        // will start from the beginning
        REQUIRE( sgfData->current == sgfData->buffer );
      }
    }
  }
}
