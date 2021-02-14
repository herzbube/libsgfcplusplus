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
#include <SgfcPlusPlusFactory.h>
#include <ISgfcArguments.h>
#include <ISgfcDocumentReader.h>
#include <ISgfcDocumentReadResult.h>
#include <ISgfcDocumentWriter.h>
#include <ISgfcDocumentWriteResult.h>
#include <ISgfcDocument.h>
#include <ISgfcGame.h>
#include <ISgfcNumberPropertyValue.h>
#include <ISgfcProperty.h>
#include <ISgfcPropertyFactory.h>
#include <ISgfcPropertyValueFactory.h>
#include <ISgfcSimpleTextPropertyValue.h>
#include <ISgfcTextPropertyValue.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

// Test strategy
// - Testing reading
//   - Detailed tests with encoding mode 1 to verify that decoding to UTF-8
//     actually works in various scenarios. Specifically test BOM handling,
//     which only works with encoding mode 1.
//   - Tests with encoding modes 2 and 3 only test the expected differences to
//     encoding mode 1. It would be too much effort to repeat all of the
//     encoding mode 1 tests for encoding modes 2 and 3.
// - Testing writing
//   - Only a few test cases to verify that a library client can provide
//     an object tree that has non-UTF-8 values.
// - Only selected encodings are tested, the number of supported encodings is
//   too large to have exhaustive coverage.
//
// Non-ASCII input/output is provided either in the form of hex bytes or as
// Unicode literals. This C++ source code file must be compilable by many
// different C++ compilers on many different platforms, so it can't have any
// special encoding.
//
// The following command line prints two lines of C++ source code. The first
// line initializes an unsigned char array with the content of an .sgf file,
// the second line initializes an std::string with the content of the buffer.
//   hexdumpResult=$(hexdump -ve '/1 "0x%02x, "' /path/to/sgf); echo "unsigned char sgfContentBuffer[] = { $hexdumpResult};"; echo "std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));";
// The output is ready to be copy&pasted from the terminal into this test suite.


void AssertDocumentReadResultHasNoWarningsOrErrors(std::shared_ptr<ISgfcDocumentReadResult> readResult);
void AssertDocumentWriteResultHasNoWarningsOrErrors(std::shared_ptr<ISgfcDocumentWriteResult> writeResult);
void AssertDocumentReadResultHasFatalError(std::shared_ptr<ISgfcDocumentReadResult> readResult, SgfcMessageID messageID);

void AssertDocumentReadResultHasNonFatalMessage(std::shared_ptr<ISgfcDocumentReadResult> readResult, SgfcMessageType messageType, SgfcMessageID messageID);
void AssertDocumentWriteResultHasNonFatalMessage(std::shared_ptr<ISgfcDocumentWriteResult> writeResult, SgfcMessageType messageType, SgfcMessageID messageID);
void AssertParseResultHasNonFatalMessage(std::vector<std::shared_ptr<ISgfcMessage>> parseResult, SgfcMessageType messageType, SgfcMessageID messageID);

void AssertParseResultContainsAtLeastOneMessageWithID(std::vector<std::shared_ptr<ISgfcMessage>> parseResult, SgfcMessageID messageID);
void AssertSingleGameHasRootNodeWithCommentPropertyValue(std::shared_ptr<ISgfcDocumentReadResult> readResult, const SgfcText& expectedValue);
void AssertMultipleGameHaveRootNodeWithCommentPropertyValue(std::shared_ptr<ISgfcDocumentReadResult> readResult, int numberOfGames, const SgfcText& expectedValue);
void AssertRootNodeHasCommentPropertyWithValue(std::shared_ptr<ISgfcGame> game, const SgfcText& expectedValue);


SCENARIO( "SGF content is decoded for reading with encoding mode 1, Unicode BOM tests", "[frontend][encoding]" )
{
  auto reader = SgfcPlusPlusFactory::CreateDocumentReader();

  GIVEN( "The SGF content has an UTF-8 BOM" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // UTF-8 BOM
      0xef, 0xbb, 0xbf,
      // (;FF[4]CA[UTF-8]C[foo])
      0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x41, 0x5b, 0x55, 0x54, 0x46, 0x2d, 0x38, 0x5d, 0x43, 0x5b, 0x66, 0x6f, 0x6f, 0x5d, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    SgfcText expectedValue = "foo";

    WHEN( "The SGF content is read" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The encoding is detected" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValue);
      }
    }
  }

  GIVEN( "The SGF content has an UTF-16BE BOM" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // UTF-16BE BOM
      0xfe, 0xff,
      // (;FF[4]CA[UTF-16BE]C[foo])
      0x0, 0x28, 0x0, 0x3b, 0x0, 0x46, 0x0, 0x46, 0x0, 0x5b, 0x0, 0x34, 0x0, 0x5d, 0x0, 0x43, 0x0, 0x41, 0x0, 0x5b, 0x0, 0x55, 0x0, 0x54, 0x0, 0x46, 0x0, 0x2d, 0x0, 0x31, 0x0, 0x36, 0x0, 0x42, 0x0, 0x45, 0x0, 0x5d, 0x0, 0x43, 0x0, 0x5b, 0x0, 0x66, 0x0, 0x6f, 0x0, 0x6f, 0x0, 0x5d, 0x0, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    SgfcText expectedValue = "foo";

    WHEN( "The SGF content is read" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The encoding is detected" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValue);
      }
    }
  }

  GIVEN( "The SGF content has an UTF-16LE BOM" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // UTF-16LE BOM
      0xff, 0xfe,
      // (;FF[4]CA[UTF-16LE]C[foo])
      0x28, 0x0, 0x3b, 0x0, 0x46, 0x0, 0x46, 0x0, 0x5b, 0x0, 0x34, 0x0, 0x5d, 0x0, 0x43, 0x0, 0x41, 0x0, 0x5b, 0x0, 0x55, 0x0, 0x54, 0x0, 0x46, 0x0, 0x2d, 0x0, 0x31, 0x0, 0x36, 0x0, 0x4c, 0x0, 0x45, 0x0, 0x5d, 0x0, 0x43, 0x0, 0x5b, 0x0, 0x66, 0x0, 0x6f, 0x0, 0x6f, 0x0, 0x5d, 0x0, 0x29, 0x0,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    SgfcText expectedValue = "foo";

    WHEN( "The SGF content is read" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The encoding is detected" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValue);
      }
    }
  }

  GIVEN( "The SGF content has an UTF-32BE BOM" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // UTF-32BE BOM
      0x0, 0x0, 0xfe, 0xff,
      // (;FF[4]CA[UTF-32BE]C[foo])
      0x0, 0x0, 0x0, 0x28, 0x0, 0x0, 0x0, 0x3b, 0x0, 0x0, 0x0, 0x46, 0x0, 0x0, 0x0, 0x46, 0x0, 0x0, 0x0, 0x5b, 0x0, 0x0, 0x0, 0x34, 0x0, 0x0, 0x0, 0x5d, 0x0, 0x0, 0x0, 0x43, 0x0, 0x0, 0x0, 0x41, 0x0, 0x0, 0x0, 0x5b, 0x0, 0x0, 0x0, 0x55, 0x0, 0x0, 0x0, 0x54, 0x0, 0x0, 0x0, 0x46, 0x0, 0x0, 0x0, 0x2d, 0x0, 0x0, 0x0, 0x33, 0x0, 0x0, 0x0, 0x32, 0x0, 0x0, 0x0, 0x42, 0x0, 0x0, 0x0, 0x45, 0x0, 0x0, 0x0, 0x5d, 0x0, 0x0, 0x0, 0x43, 0x0, 0x0, 0x0, 0x5b, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x6f, 0x0, 0x0, 0x0, 0x6f, 0x0, 0x0, 0x0, 0x5d, 0x0, 0x0, 0x0, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    SgfcText expectedValue = "foo";

    WHEN( "The SGF content is read" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The encoding is detected" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValue);
      }
    }
  }

  GIVEN( "The SGF content has an UTF-32LE BOM" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // UTF-32LE BOM
      0xff, 0xfe, 0x0, 0x0,
      // (;FF[4]CA[UTF-32LE]C[foo])
      0x28, 0x0, 0x0, 0x0, 0x3b, 0x0, 0x0, 0x0, 0x46, 0x0, 0x0, 0x0, 0x46, 0x0, 0x0, 0x0, 0x5b, 0x0, 0x0, 0x0, 0x34, 0x0, 0x0, 0x0, 0x5d, 0x0, 0x0, 0x0, 0x43, 0x0, 0x0, 0x0, 0x41, 0x0, 0x0, 0x0, 0x5b, 0x0, 0x0, 0x0, 0x55, 0x0, 0x0, 0x0, 0x54, 0x0, 0x0, 0x0, 0x46, 0x0, 0x0, 0x0, 0x2d, 0x0, 0x0, 0x0, 0x33, 0x0, 0x0, 0x0, 0x32, 0x0, 0x0, 0x0, 0x4c, 0x0, 0x0, 0x0, 0x45, 0x0, 0x0, 0x0, 0x5d, 0x0, 0x0, 0x0, 0x43, 0x0, 0x0, 0x0, 0x5b, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x6f, 0x0, 0x0, 0x0, 0x6f, 0x0, 0x0, 0x0, 0x5d, 0x0, 0x0, 0x0, 0x29, 0x0, 0x0, 0x0,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    SgfcText expectedValue = "foo";

    WHEN( "The SGF content is read" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The encoding is detected" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValue);
      }
    }
  }

  GIVEN( "The SGF content is UTF-16BE encoded but has no UTF-16BE BOM" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // (;FF[4]CA[UTF-16BE]C[foo])
      0x0, 0x28, 0x0, 0x3b, 0x0, 0x46, 0x0, 0x46, 0x0, 0x5b, 0x0, 0x34, 0x0, 0x5d, 0x0, 0x43, 0x0, 0x41, 0x0, 0x5b, 0x0, 0x55, 0x0, 0x54, 0x0, 0x46, 0x0, 0x2d, 0x0, 0x31, 0x0, 0x36, 0x0, 0x42, 0x0, 0x45, 0x0, 0x5d, 0x0, 0x43, 0x0, 0x5b, 0x0, 0x66, 0x0, 0x6f, 0x0, 0x6f, 0x0, 0x5d, 0x0, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    SgfcText expectedValue = "foo";

    WHEN( "The SGF content is read" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The encoding is not detected" )
      {
        // Unfortunately the SGF content is not rejected with a fatal error,
        // but that's to be expected due to the fault tolerance of SGFC.
        REQUIRE( readResult->GetExitCode() == SgfcExitCode::Error );
        REQUIRE( readResult->IsSgfDataValid() == true );

        auto parseResult = readResult->GetParseResult();

        // Game-tree detection fails because the expected "(;" byte sequence
        // does not exist (there's a 0x00 byte in between)
        AssertParseResultContainsAtLeastOneMessageWithID(parseResult, SgfcMessageID::MissingSemicolonAtGameTreeStart);

        // The error is about an "F" property:
        //   Error 20 (critical): property <F> without any values found (ignored)
        // Because there is an 0x00 byte between the two "F" characters
        AssertParseResultContainsAtLeastOneMessageWithID(parseResult, SgfcMessageID::PropertyWithoutValuesIgnored);

        // No more tests for specific messages, the behaviour might change in
        // the future.
      }
    }
  }
}

SCENARIO( "SGF content is decoded for reading with encoding mode 1, CA tests", "[frontend][encoding]" )
{
  auto reader = SgfcPlusPlusFactory::CreateDocumentReader();

  GIVEN( "The SGF content is encoded with UTF-8 and contains characters from non-latin character sets" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // (;FF[4]CA[UTF-8]C[...])
      // The comment contains the word "Go" in several languages, separated
      // with a space character.
      // 1. "Go" in latin/roman characters
      // 2. "Go" transcribed to Cyrillic (uppercase "G" + lowercase "o" characters)
      // 3. "Go" transcribed to Greek (uppercase Gamma + lowercase Omega characters)
      // 4. "Igo" in Japanese, Kanji characters
      // 5. "Weiqi" in Mandarin, Traditional Chinese characters
      // 6. "Baduk" in Korean, Hangul characters
      0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x41, 0x5b, 0x55, 0x54, 0x46, 0x2d, 0x38, 0x5d, 0x43, 0x5b, 0x47, 0x6f, 0x20, 0xd0, 0x93, 0xd0, 0xbe, 0x20, 0xce, 0x93, 0xcf, 0x89, 0x20, 0xe5, 0x9b, 0xb2, 0xe7, 0xa2, 0x81, 0x20, 0xe5, 0x9c, 0x8d, 0xe6, 0xa3, 0x8b, 0x20, 0xeb, 0xb0, 0x94, 0xeb, 0x91, 0x91, 0x5d, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    unsigned char expectedValueBufferInUtf8[] = { 0x47, 0x6f, 0x20, 0xd0, 0x93, 0xd0, 0xbe, 0x20, 0xce, 0x93, 0xcf, 0x89, 0x20, 0xe5, 0x9b, 0xb2, 0xe7, 0xa2, 0x81, 0x20, 0xe5, 0x9c, 0x8d, 0xe6, 0xa3, 0x8b, 0x20, 0xeb, 0xb0, 0x94, 0xeb, 0x91, 0x91, };
    SgfcText expectedValueInUtf8(reinterpret_cast<const char*>(expectedValueBufferInUtf8), sizeof(expectedValueBufferInUtf8));

    WHEN( "The SGF content is read" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The encoding is detected" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValueInUtf8);
      }
    }
  }

  GIVEN( "The SGF content is encoded with an 8-bit encoding and contains characters from a non-latin character set" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // (;FF[4]CA[Windows-1251]C[...])
      // The comment contains the sentence
      //   "Go is an abstract strategy board game"
      // translated to Russian in Cyrillic characters.
      0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x41, 0x5b, 0x57, 0x69, 0x6e, 0x64, 0x6f, 0x77, 0x73, 0x2d, 0x31, 0x32, 0x35, 0x31, 0x5d, 0x43, 0x5b, 0x47, 0x6f, 0x20, 0xfd, 0xf2, 0xee, 0x20, 0xe0, 0xe1, 0xf1, 0xf2, 0xf0, 0xe0, 0xea, 0xf2, 0xed, 0xe0, 0xff, 0x20, 0xf1, 0xf2, 0xf0, 0xe0, 0xf2, 0xe5, 0xe3, 0xe8, 0xf7, 0xe5, 0xf1, 0xea, 0xe0, 0xff, 0x20, 0xed, 0xe0, 0xf1, 0xf2, 0xee, 0xeb, 0xfc, 0xed, 0xe0, 0xff, 0x20, 0xe8, 0xe3, 0xf0, 0xe0, 0x5d, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    unsigned char expectedValueBufferInUtf8[] = { 0x47, 0x6f, 0x20, 0xd1, 0x8d, 0xd1, 0x82, 0xd0, 0xbe, 0x20, 0xd0, 0xb0, 0xd0, 0xb1, 0xd1, 0x81, 0xd1, 0x82, 0xd1, 0x80, 0xd0, 0xb0, 0xd0, 0xba, 0xd1, 0x82, 0xd0, 0xbd, 0xd0, 0xb0, 0xd1, 0x8f, 0x20, 0xd1, 0x81, 0xd1, 0x82, 0xd1, 0x80, 0xd0, 0xb0, 0xd1, 0x82, 0xd0, 0xb5, 0xd0, 0xb3, 0xd0, 0xb8, 0xd1, 0x87, 0xd0, 0xb5, 0xd1, 0x81, 0xd0, 0xba, 0xd0, 0xb0, 0xd1, 0x8f, 0x20, 0xd0, 0xbd, 0xd0, 0xb0, 0xd1, 0x81, 0xd1, 0x82, 0xd0, 0xbe, 0xd0, 0xbb, 0xd1, 0x8c, 0xd0, 0xbd, 0xd0, 0xb0, 0xd1, 0x8f, 0x20, 0xd0, 0xb8, 0xd0, 0xb3, 0xd1, 0x80, 0xd0, 0xb0, };
    SgfcText expectedValueInUtf8(reinterpret_cast<const char*>(expectedValueBufferInUtf8), sizeof(expectedValueBufferInUtf8));

    WHEN( "The SGF content is read" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The encoding is detected and the content is re-encoded to UTF-8" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValueInUtf8);
      }
    }
  }

#ifndef _WIN32
  GIVEN( "The SGF content is encoded with a multi-byte encoding and contains characters from a non-latin character set" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // (;FF[4]CA[EUC-CN]C[...])
      // The comment contains the sentence
      //   "Go is an abstract strategy board game"
      // translated to Chinese in Simplified Chinese characters.
      0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x41, 0x5b, 0x45, 0x55, 0x43, 0x2d, 0x43, 0x4e, 0x5d, 0x43, 0x5b, 0xce, 0xa7, 0xc6, 0xe5, 0xca, 0xc7, 0xd2, 0xbb, 0xd6, 0xd6, 0xb3, 0xe9, 0xcf, 0xf3, 0xb5, 0xc4, 0xb2, 0xdf, 0xc2, 0xd4, 0xc6, 0xe5, 0xc0, 0xe0, 0xd3, 0xce, 0xcf, 0xb7, 0x5d, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    unsigned char expectedValueBufferInUtf8[] = { 0xe5, 0x9b, 0xb4, 0xe6, 0xa3, 0x8b, 0xe6, 0x98, 0xaf, 0xe4, 0xb8, 0x80, 0xe7, 0xa7, 0x8d, 0xe6, 0x8a, 0xbd, 0xe8, 0xb1, 0xa1, 0xe7, 0x9a, 0x84, 0xe7, 0xad, 0x96, 0xe7, 0x95, 0xa5, 0xe6, 0xa3, 0x8b, 0xe7, 0xb1, 0xbb, 0xe6, 0xb8, 0xb8, 0xe6, 0x88, 0x8f, };
    SgfcText expectedValueInUtf8(reinterpret_cast<const char*>(expectedValueBufferInUtf8), sizeof(expectedValueBufferInUtf8));

    WHEN( "The SGF content is read" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The encoding is detected and the content is re-encoded to UTF-8" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValueInUtf8);
      }
    }
  }
#endif

  GIVEN( "The SGF content is encoded with the default encoding and the CA property is missing" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // (;FF[4]C[...])
      // The comment contains 5 pairs of uppercase and lowercase characters,
      // separated with a space characters.
      // 1. A/a with Diaresis (Umlaut)
      // 2. A/a with Grave
      // 3. A/A with Circumflex
      // 4. A/a with Ring Above
      // 5. Ae/ae
      0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x5b, 0xc4, 0xe4, 0x20, 0xc0, 0xe0, 0x20, 0xc2, 0xe2, 0x20, 0xc5, 0xe5, 0x20, 0xc6, 0xe6, 0x5d, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    unsigned char expectedValueBufferInUtf8[] = { 0xc3, 0x84, 0xc3, 0xa4, 0x20, 0xc3, 0x80, 0xc3, 0xa0, 0x20, 0xc3, 0x82, 0xc3, 0xa2, 0x20, 0xc3, 0x85, 0xc3, 0xa5, 0x20, 0xc3, 0x86, 0xc3, 0xa6, };
    SgfcText expectedValueInUtf8(reinterpret_cast<const char*>(expectedValueBufferInUtf8), sizeof(expectedValueBufferInUtf8));

    WHEN( "The SGF content is read using the default encoding" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The default encoding is used and the content is re-encoded to UTF-8" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValueInUtf8);
      }
    }
  }

#ifndef _WIN32
  GIVEN( "The SGF content is encoded with a non-default encoding and the CA property is missing" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // (;FF[4]C[...])
      // The comment contains the sentence
      //   "Go is an abstract strategy board game"
      // translated to Chinese in Simplified Chinese characters.
      // The encoding is EUC-CN. The content is the same as in another test in
      // this suite.
      0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x5b, 0xce, 0xa7, 0xc6, 0xe5, 0xca, 0xc7, 0xd2, 0xbb, 0xd6, 0xd6, 0xb3, 0xe9, 0xcf, 0xf3, 0xb5, 0xc4, 0xb2, 0xdf, 0xc2, 0xd4, 0xc6, 0xe5, 0xc0, 0xe0, 0xd3, 0xce, 0xcf, 0xb7, 0x5d, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    unsigned char expectedValueBufferInUtf8[] = { 0xe5, 0x9b, 0xb4, 0xe6, 0xa3, 0x8b, 0xe6, 0x98, 0xaf, 0xe4, 0xb8, 0x80, 0xe7, 0xa7, 0x8d, 0xe6, 0x8a, 0xbd, 0xe8, 0xb1, 0xa1, 0xe7, 0x9a, 0x84, 0xe7, 0xad, 0x96, 0xe7, 0x95, 0xa5, 0xe6, 0xa3, 0x8b, 0xe7, 0xb1, 0xbb, 0xe6, 0xb8, 0xb8, 0xe6, 0x88, 0x8f, };
    SgfcText expectedValueInUtf8(reinterpret_cast<const char*>(expectedValueBufferInUtf8), sizeof(expectedValueBufferInUtf8));

    WHEN( "The SGF content is read using the correct non-default encoding" )
    {
      reader->GetArguments()->AddArgument(SgfcArgumentType::DefaultEncoding, "EUC-CN");
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The specified default encoding is used and the content is re-encoded to UTF-8" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValueInUtf8);
      }
    }
  }
#endif

  GIVEN( "The SGF content is encoded with an encoding that is not the same as the encoding in the CA property" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // (;FF[4]CA[EUC-CN]C[...])
      // The comment contains the Trademark symbol.
      // The EUC-CN encoding in the CA property is wrong, the actual
      // encoding is Windows-1252.
      0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x41, 0x5b, 0x45, 0x55, 0x43, 0x2d, 0x43, 0x4e, 0x5d, 0x43, 0x5b, 0x99, 0x5d, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    unsigned char expectedValueBufferInUtf8[] = { 0xe2, 0x84, 0xa2, };
    SgfcText expectedValueInUtf8(reinterpret_cast<const char*>(expectedValueBufferInUtf8), sizeof(expectedValueBufferInUtf8));

    WHEN( "The SGF content is read using the correct forced encoding" )
    {
      reader->GetArguments()->AddArgument(SgfcArgumentType::ForcedEncoding, "Windows-1252");
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The forced encoding is used and the content is re-encoded to UTF-8" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValueInUtf8);
      }
    }
  }
}

// These tests demonstrate that with -E1 decoding takes place before unescaping
SCENARIO( "SGF content is decoded for reading with encoding mode 1, escaping tests", "[frontend][encoding]" )
{
  auto reader = SgfcPlusPlusFactory::CreateDocumentReader();

  GIVEN( "The SGF content contains unescaped byte values that are equal to the SGF end-of-property-value ASCII character" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // (;FF[4]CA[Big5]C[...])
      // The comment contains a character whose second byte value in the Big5
      // encoding is equal to the SGF end-of-property-value ASCII character ("]").
      0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x41, 0x5b, 0x42, 0x69, 0x67, 0x35, 0x5d, 0x43, 0x5b, 0xa6, 0x5d, 0x5d, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    unsigned char expectedValueBufferInUtf8[] = { 0xe5, 0x9b, 0xa0, };
    SgfcText expectedValueInUtf8(reinterpret_cast<const char*>(expectedValueBufferInUtf8), sizeof(expectedValueBufferInUtf8));

    WHEN( "The SGF content is read" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The property value end is recognized correctly" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValueInUtf8);
      }
    }
  }

  GIVEN( "The SGF content contains unescaped byte values that are equal to the SGF escape ASCII character" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // (;FF[4]CA[SJIS]C[...])
      // The comment contains a character whose second byte value in the SJIS
      // encoding is equal to the SGF escape ASCII character ("\").
      0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x41, 0x5b, 0x53, 0x4a, 0x49, 0x53, 0x5d, 0x43, 0x5b, 0x90, 0x5c, 0x5d, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    unsigned char expectedValueBufferInUtf8[] = { 0xe7, 0x94, 0xb3, };
    SgfcText expectedValueInUtf8(reinterpret_cast<const char*>(expectedValueBufferInUtf8), sizeof(expectedValueBufferInUtf8));

    WHEN( "The SGF content is read" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The property value end is recognized correctly" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValueInUtf8);
      }
    }
  }
}

SCENARIO( "SGF content is decoded for reading with encoding mode 1, multiple encodings tests", "[frontend][encoding]" )
{
  auto reader = SgfcPlusPlusFactory::CreateDocumentReader();

  GIVEN( "The SGF content contains two game trees with different encodings" )
  {
    std::string sgfContent;
    sgfContent += "(;FF[4]CA[UTF-8]C[foo])";
    sgfContent += "(;FF[4]CA[ISO-8859-1]C[foo])";

    WHEN( "The SGF content is read" )
    {
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "Decoding fails" )
      {
        AssertDocumentReadResultHasFatalError(readResult, SgfcMessageID::SgfContentHasDifferentEncodingsFatal);
      }
    }
  }
}

// These tests demonstrate that with -E2 decoding takes place after unescaping
SCENARIO( "SGF content is decoded for reading with encoding mode 2, escaping tests", "[frontend][encoding]" )
{
  auto reader = SgfcPlusPlusFactory::CreateDocumentReader();

  GIVEN( "The SGF content contains unescaped byte values that are equal to the SGF end-of-property-value ASCII character" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // (;FF[4]CA[Big5]C[...])
      // The comment contains a character whose second byte value in the Big5
      // encoding is equal to the SGF end-of-property-value ASCII character ("]").
      0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x41, 0x5b, 0x42, 0x69, 0x67, 0x35, 0x5d, 0x43, 0x5b, 0xa6, 0x5d, 0x5d, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    unsigned char expectedValueBufferInUtf8[] = { 0xe5, 0x9b, 0xa0, };
    SgfcText expectedValueInUtf8(reinterpret_cast<const char*>(expectedValueBufferInUtf8), sizeof(expectedValueBufferInUtf8));

    WHEN( "The SGF content is read" )
    {
      reader->GetArguments()->AddArgument(SgfcArgumentType::EncodingMode, 2);
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The property value end is not recognized correctly" )
      {
        auto parseResult = readResult->GetParseResult();
        AssertParseResultContainsAtLeastOneMessageWithID(parseResult, SgfcMessageID::IllegalCharacters);
        AssertParseResultContainsAtLeastOneMessageWithID(parseResult, SgfcMessageID::EncodingErrorsDetected);
      }
    }
  }

  GIVEN( "The SGF content contains unescaped byte values that are equal to the SGF escape ASCII character" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // (;FF[4]CA[SJIS]C[...])
      // The comment contains a character whose second byte value in the SJIS
      // encoding is equal to the SGF escape ASCII character ("\").
      0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x41, 0x5b, 0x53, 0x4a, 0x49, 0x53, 0x5d, 0x43, 0x5b, 0x90, 0x5c, 0x5d, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    unsigned char expectedValueBufferInUtf8[] = { 0xe7, 0x94, 0xb3, };
    SgfcText expectedValueInUtf8(reinterpret_cast<const char*>(expectedValueBufferInUtf8), sizeof(expectedValueBufferInUtf8));

    WHEN( "The SGF content is read" )
    {
      reader->GetArguments()->AddArgument(SgfcArgumentType::EncodingMode, 2);
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The property value end is not recognized correctly" )
      {
        auto parseResult = readResult->GetParseResult();
        AssertParseResultContainsAtLeastOneMessageWithID(parseResult, SgfcMessageID::UnexpectedEndOfFile);
      }
    }
  }
}

SCENARIO( "SGF content is decoded for reading with encoding mode 2, multiple encodings tests", "[frontend][encoding]" )
{
  auto reader = SgfcPlusPlusFactory::CreateDocumentReader();

  GIVEN( "The SGF content contains two game trees with different encodings" )
  {
    std::string sgfContent;
    sgfContent += "(;FF[4]CA[UTF-8]C[foo])";
    sgfContent += "(;FF[4]CA[ISO-8859-1]C[foo])";
    int expectedNumberOfGames = 2;
    SgfcText expectedValue = "foo";

    WHEN( "The SGF content is read" )
    {
      reader->GetArguments()->AddArgument(SgfcArgumentType::EncodingMode, 2);
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The encoding is detected" )
      {
        AssertDocumentReadResultHasNonFatalMessage(readResult, SgfcMessageType::Warning, SgfcMessageID::SgfContentHasDifferentEncodings);
        AssertMultipleGameHaveRootNodeWithCommentPropertyValue(readResult, expectedNumberOfGames, expectedValue);
      }
    }
  }
}

SCENARIO( "SGF content is decoded for reading with encoding mode 3", "[frontend][encoding]" )
{
  auto reader = SgfcPlusPlusFactory::CreateDocumentReader();

#ifndef _WIN32
  GIVEN( "The SGF content is encoded with an encoding that is not the same as the encoding in the CA property" )
  {
    unsigned char sgfContentBuffer[] =
    {
      // (;FF[4]CA[EUC-CN]C[...])
      // The comment contains the Trademark symbol.
      // The EUC-CN encoding in the CA property is wrong, the actual
      // encoding is Windows-1252.
      0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x41, 0x5b, 0x45, 0x55, 0x43, 0x2d, 0x43, 0x4e, 0x5d, 0x43, 0x5b, 0x99, 0x5d, 0x29,
    };
    std::string sgfContent(reinterpret_cast<const char*>(sgfContentBuffer), sizeof(sgfContentBuffer));
    unsigned char expectedValueBufferInOriginalEncoding[] = { 0x99, };
    SgfcText expectedValueInOriginalEncoding(reinterpret_cast<const char*>(expectedValueBufferInOriginalEncoding), sizeof(expectedValueBufferInOriginalEncoding));

    WHEN( "The SGF content is read" )
    {
      reader->GetArguments()->AddArgument(SgfcArgumentType::EncodingMode, 3);
      auto readResult = reader->ReadSgfContent(sgfContent);

      THEN( "The (wrong) encoding is ignored, the original encoding is preserved" )
      {
        AssertDocumentReadResultHasNoWarningsOrErrors(readResult);
        AssertSingleGameHasRootNodeWithCommentPropertyValue(readResult, expectedValueInOriginalEncoding);
      }
    }
  }
#endif
}

SCENARIO( "SGF content is decoded to UTF-8 for writing", "[frontend][encoding]" )
{
  auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
  auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();
  auto writer = SgfcPlusPlusFactory::CreateDocumentWriter();

  // Set up document
  auto document = SgfcPlusPlusFactory::CreateDocument();
  auto game1 = document->GetGames().front();
  auto rootNode1 = game1->GetRootNode();
  auto game2 = SgfcPlusPlusFactory::CreateGame();
  auto rootNode2 = game2->GetRootNode();

  // Set up properties + property values
  auto propertyValueFF = propertyValueFactory->CreateNumberPropertyValue(4);
  auto propertyFF = propertyFactory->CreateProperty(SgfcPropertyType::FF, propertyValueFF);

  // Although Big5 is not an ASCII-safe encoding, we can use it for our tests
  // as long as we don't use a character whose encoding contains a byte value
  // that corresponds to one of the SGF skeleton characters that need escaping.
  // See the discussion in ISgfcDocumentWriter class documentation.
  auto propertyValueCABig5 = propertyValueFactory->CreateSimpleTextPropertyValue("Big5");
  auto propertyCABig5 = propertyFactory->CreateProperty(SgfcPropertyType::CA, propertyValueCABig5);
  // The comment contains the word "Weiqi" (= Go) in Mandarin, in Traditional
  // Chinese characters
  unsigned char textPropertyValueBufferInBig5[] = { 0xb3, 0xf2, 0xb4, 0xd1 };
  SgfcText textPropertyValueBig5(reinterpret_cast<const char*>(textPropertyValueBufferInBig5), sizeof(textPropertyValueBufferInBig5));
  auto propertyValueCBig5 = propertyValueFactory->CreateTextPropertyValue(textPropertyValueBig5);
  auto propertyCBig5 = propertyFactory->CreateProperty(SgfcPropertyType::C, propertyValueCBig5);
  // (;FF[4]CA[UTF-8]GM[1]SZ[19]AP[SGFC:2.0]C[...])
  unsigned char expectedSgfContentBufferBig5InUtf8[] = { 0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x41, 0x5b, 0x55, 0x54, 0x46, 0x2d, 0x38, 0x5d, 0x47, 0x4d, 0x5b, 0x31, 0x5d, 0x53, 0x5a, 0x5b, 0x31, 0x39, 0x5d, 0x41, 0x50, 0x5b,
    // SGFC:2.0
    0x53, 0x47, 0x46, 0x43, 0x3a, 0x32, 0x2e, 0x30,
    0x5d, 0x43, 0x5b, 0xe5, 0x9c, 0x8d, 0xe6, 0xa3, 0x8b, 0x5d, 0x29, 0x0a, };

  auto propertyValueCAWindows1252 = propertyValueFactory->CreateSimpleTextPropertyValue("Windows-1252");
  auto propertyCAWindows1252 = propertyFactory->CreateProperty(SgfcPropertyType::CA, propertyValueCAWindows1252);
  // The comment contains the trademark symbol.
  unsigned char textPropertyValueBufferInWindows1252[] = { 0x99, };
  SgfcText textPropertyValueWindows1252(reinterpret_cast<const char*>(textPropertyValueBufferInWindows1252), sizeof(textPropertyValueBufferInWindows1252));
  auto propertyValueCWindows1252 = propertyValueFactory->CreateTextPropertyValue(textPropertyValueWindows1252);
  auto propertyCWindows1252 = propertyFactory->CreateProperty(SgfcPropertyType::C, propertyValueCWindows1252);
  // (;FF[4]CA[UTF-8]GM[1]SZ[19]AP[SGFC:2.0]C[...])
  unsigned char expectedSgfContentBufferWindows1252InUtf8[] = { 0x28, 0x3b, 0x46, 0x46, 0x5b, 0x34, 0x5d, 0x43, 0x41, 0x5b, 0x55, 0x54, 0x46, 0x2d, 0x38, 0x5d, 0x47, 0x4d, 0x5b, 0x31, 0x5d, 0x53, 0x5a, 0x5b, 0x31, 0x39, 0x5d, 0x41, 0x50, 0x5b,
    // SGFC:2.0
    0x53, 0x47, 0x46, 0x43, 0x3a, 0x32, 0x2e, 0x30,
    0x5d, 0x43, 0x5b, 0xe2, 0x84, 0xa2, 0x5d, 0x29, 0x0a, };

  GIVEN( "The SGF content is encoded with a double-byte encoding and the CA property exists" )
  {
    rootNode1->SetProperties( { propertyFF, propertyCABig5, propertyCBig5} );
    SgfcText expectedSgfContentInUtf8(reinterpret_cast<const char*>(expectedSgfContentBufferBig5InUtf8), sizeof(expectedSgfContentBufferBig5InUtf8));

    WHEN( "The document object tree is written" )
    {
      std::string sgfContent;
      auto writeResult = writer->WriteSgfContent(document, sgfContent);

      THEN( "The encoding is detected and the content is re-encoded to UTF-8" )
      {
        AssertDocumentWriteResultHasNoWarningsOrErrors(writeResult);
        REQUIRE (sgfContent == expectedSgfContentInUtf8);
      }
    }
  }

  GIVEN( "The SGF content is encoded with a single-byte encoding and the CA property exists" )
  {
    rootNode1->SetProperties( { propertyFF, propertyCAWindows1252, propertyCWindows1252} );
    SgfcText expectedSgfContentInUtf8(reinterpret_cast<const char*>(expectedSgfContentBufferWindows1252InUtf8), sizeof(expectedSgfContentBufferWindows1252InUtf8));

    WHEN( "The document object tree is written" )
    {
      std::string sgfContent;
      auto writeResult = writer->WriteSgfContent(document, sgfContent);

      THEN( "The encoding is detected and the content is re-encoded to UTF-8" )
      {
        AssertDocumentWriteResultHasNoWarningsOrErrors(writeResult);
        REQUIRE (sgfContent == expectedSgfContentInUtf8);
      }
    }
  }

  GIVEN( "The SGF content is encoded with two encodings and the CA property exists for both game trees" )
  {
    rootNode1->SetProperties( { propertyFF, propertyCABig5, propertyCBig5} );
    rootNode2->SetProperties( { propertyFF, propertyCAWindows1252, propertyCWindows1252} );
    document->AppendGame(game2);
    writer->GetArguments()->AddArgument(SgfcArgumentType::EncodingMode, 2);
    SgfcText expectedSgfContentInUtf8 =
      std::string(reinterpret_cast<const char*>(expectedSgfContentBufferBig5InUtf8), sizeof(expectedSgfContentBufferBig5InUtf8))
        +
      std::string(reinterpret_cast<const char*>(expectedSgfContentBufferWindows1252InUtf8), sizeof(expectedSgfContentBufferWindows1252InUtf8));

    WHEN( "The document object tree is written with encoding mode 2" )
    {
      std::string sgfContent;
      auto writeResult = writer->WriteSgfContent(document, sgfContent);

      THEN( "The encodings are detected and the content is re-encoded to UTF-8" )
      {
        AssertDocumentWriteResultHasNonFatalMessage(writeResult, SgfcMessageType::Warning, SgfcMessageID::SgfContentHasDifferentEncodings);
        REQUIRE (sgfContent == expectedSgfContentInUtf8);
      }
    }
  }

  GIVEN( "The SGF content is encoded with two encodings and the CA property exists only in one of the game tree" )
  {
    rootNode1->SetProperties( { propertyFF, propertyCABig5, propertyCBig5} );
    rootNode2->SetProperties( { propertyFF, propertyCWindows1252} );
    document->AppendGame(game2);
    writer->GetArguments()->ClearArguments();
    writer->GetArguments()->AddArgument(SgfcArgumentType::EncodingMode, 2);
    writer->GetArguments()->AddArgument(SgfcArgumentType::DefaultEncoding, "Windows-1252");
    SgfcText expectedSgfContentInUtf8 =
      std::string(reinterpret_cast<const char*>(expectedSgfContentBufferBig5InUtf8), sizeof(expectedSgfContentBufferBig5InUtf8))
        +
      std::string(reinterpret_cast<const char*>(expectedSgfContentBufferWindows1252InUtf8), sizeof(expectedSgfContentBufferWindows1252InUtf8));

    WHEN( "The document object tree is written with encoding mode 2 and a default encoding" )
    {
      std::string sgfContent;
      auto writeResult = writer->WriteSgfContent(document, sgfContent);

      THEN( "The encodings are detected and the content is re-encoded to UTF-8" )
      {
        AssertDocumentWriteResultHasNonFatalMessage(writeResult, SgfcMessageType::Warning, SgfcMessageID::SgfContentHasDifferentEncodings);
        REQUIRE (sgfContent == expectedSgfContentInUtf8);
      }
    }
  }
}

void AssertDocumentReadResultHasNoWarningsOrErrors(std::shared_ptr<ISgfcDocumentReadResult> readResult)
{
  REQUIRE( readResult->GetExitCode() == SgfcExitCode::Ok );
  REQUIRE( readResult->IsSgfDataValid() == true );
  REQUIRE( readResult->GetParseResult().size() == 0 );
}

void AssertDocumentWriteResultHasNoWarningsOrErrors(std::shared_ptr<ISgfcDocumentWriteResult> writeResult)
{
  REQUIRE( writeResult->GetExitCode() == SgfcExitCode::Ok );
  REQUIRE( writeResult->GetParseResult().size() == 0 );
}

void AssertDocumentReadResultHasFatalError(std::shared_ptr<ISgfcDocumentReadResult> readResult, SgfcMessageID messageID)
{
  REQUIRE( readResult->GetExitCode() == SgfcExitCode::FatalError );
  REQUIRE( readResult->IsSgfDataValid() == false );
  auto parseResult = readResult->GetParseResult();
  REQUIRE( parseResult.size() == 1 );
  auto message = parseResult.front();
  REQUIRE( message->GetMessageType() == SgfcMessageType::FatalError );
  REQUIRE( message->GetMessageID() == messageID );
}

void AssertDocumentReadResultHasNonFatalMessage(std::shared_ptr<ISgfcDocumentReadResult> readResult, SgfcMessageType messageType, SgfcMessageID messageID)
{
  if (messageType == SgfcMessageType::Warning)
    REQUIRE( readResult->GetExitCode() == SgfcExitCode::Warning );
  else
    REQUIRE( readResult->GetExitCode() == SgfcExitCode::Error );
  REQUIRE( readResult->IsSgfDataValid() == true );
  auto parseResult = readResult->GetParseResult();
  AssertParseResultHasNonFatalMessage(parseResult, messageType, messageID);
}

void AssertDocumentWriteResultHasNonFatalMessage(std::shared_ptr<ISgfcDocumentWriteResult> writeResult, SgfcMessageType messageType, SgfcMessageID messageID)
{
  if (messageType == SgfcMessageType::Warning)
    REQUIRE( writeResult->GetExitCode() == SgfcExitCode::Warning );
  else
    REQUIRE( writeResult->GetExitCode() == SgfcExitCode::Error );
  auto parseResult = writeResult->GetParseResult();
  AssertParseResultHasNonFatalMessage(parseResult, messageType, messageID);
}

void AssertParseResultHasNonFatalMessage(std::vector<std::shared_ptr<ISgfcMessage>> parseResult, SgfcMessageType messageType, SgfcMessageID messageID)
{
  REQUIRE( parseResult.size() == 1 );
  auto message = parseResult.front();
  REQUIRE( message->GetMessageType() == messageType );
  REQUIRE( message->GetMessageID() == messageID );
}

void AssertParseResultContainsAtLeastOneMessageWithID(std::vector<std::shared_ptr<ISgfcMessage>> parseResult, SgfcMessageID messageID)
{
  int messageCount = 0;
  for (auto message : parseResult)
  {
    if (message->GetMessageID() == messageID)
      messageCount++;
  }
  REQUIRE( messageCount > 0 );
}

void AssertSingleGameHasRootNodeWithCommentPropertyValue(std::shared_ptr<ISgfcDocumentReadResult> readResult, const SgfcText& expectedValue)
{
  auto document = readResult->GetDocument();
  auto games = document->GetGames();
  REQUIRE( games.size() == 1 );
  AssertRootNodeHasCommentPropertyWithValue(games.front(), expectedValue);
}

void AssertMultipleGameHaveRootNodeWithCommentPropertyValue(std::shared_ptr<ISgfcDocumentReadResult> readResult, int expectedNumberOfGames, const SgfcText& expectedValue)
{
  auto document = readResult->GetDocument();
  auto games = document->GetGames();
  REQUIRE( games.size() == expectedNumberOfGames );
  for (auto game : games)
    AssertRootNodeHasCommentPropertyWithValue(game, expectedValue);
}

void AssertRootNodeHasCommentPropertyWithValue(std::shared_ptr<ISgfcGame> game, const SgfcText& expectedValue)
{
  auto rootNode = game->GetRootNode();
  REQUIRE( rootNode != nullptr );
  auto property = rootNode->GetProperty(SgfcPropertyType::C);
  REQUIRE( property != nullptr );
  auto propertyValue = property->GetPropertyValue();
  REQUIRE( propertyValue != nullptr );
  REQUIRE( propertyValue->IsComposedValue() == false );
  auto singlePropertyValue = propertyValue->ToSingleValue();
  REQUIRE( singlePropertyValue->GetValueType() == SgfcPropertyValueType::Text );
  REQUIRE( singlePropertyValue->HasTypedValue() == true );
  REQUIRE( singlePropertyValue->GetRawValue() == expectedValue );
  auto textPropertyValue = singlePropertyValue->ToTextValue();
  REQUIRE( textPropertyValue->GetTextValue() == expectedValue );
}
