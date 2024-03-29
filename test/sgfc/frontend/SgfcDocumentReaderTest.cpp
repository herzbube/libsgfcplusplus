// -----------------------------------------------------------------------------
// Copyright 2024 Patrick Näf (herzbube@herzbube.ch)
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
#include <ISgfcSimpleTextPropertyValue.h>
#include <sgfc/frontend/SgfcDocumentReader.h>
#include <sgfc/argument/SgfcArguments.h>
#include <SgfcPrivateConstants.h>
#include <SgfcUtility.h>

// Unit test library includes
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_range.hpp>

using namespace LibSgfcPlusPlus;


void AssertErrorReadResultWhenNoValidSgfContent(std::shared_ptr<ISgfcDocumentReadResult> readResult);
void AssertSuccessReadResultWhenValidSgfContent(std::shared_ptr<ISgfcDocumentReadResult> readResult);
void AssertAllRootNodesContainCaProperty(std::shared_ptr<ISgfcDocumentReadResult> readResult, const SgfcSimpleText& textEncodingName);
void AssertRootNodeContainsCaProperty(std::shared_ptr<ISgfcGame> game, const SgfcSimpleText& textEncodingName);
void AssertRootNodeDoesNotContainCaProperty(std::shared_ptr<ISgfcGame> game);


SCENARIO( "SgfcDocumentReader is constructed", "[frontend]" )
{
  GIVEN( "The default constructor is used" )
  {
    WHEN( "SgfcDocumentReader is constructed" )
    {
      THEN( "SgfcDocumentReader is constructed successfully" )
      {
        REQUIRE_NOTHROW( SgfcDocumentReader() );
      }
    }

    WHEN( "SgfcDocumentReader is constructed" )
    {
      SgfcDocumentReader reader;

      THEN( "SgfcDocumentReader has the expected default state" )
      {
        auto arguments = reader.GetArguments();
        REQUIRE( arguments != nullptr );
        REQUIRE( arguments->HasArguments() == false );
        REQUIRE( arguments->GetArguments().size() == 0 );
      }
    }
  }
}

SCENARIO( "SgfcDocumentReader reads SGF content from the filesystem", "[frontend][filesystem]" )
{
  // Using a random UUID as the filename, it is reasonably safe to assume that
  // the file does not exist
  std::string tempFilePath = SgfcUtility::JoinPathComponents(
    SgfcUtility::GetTempFolderPath(),
    SgfcUtility::CreateUuid());

  GIVEN( "The file does not exist" )
  {
    WHEN( "SgfcDocumentReader performs the read operation" )
    {
      SgfcDocumentReader reader;
      auto readResult = reader.ReadSgfFile(tempFilePath);

      THEN( "The read operation result indicates failure" )
      {
        REQUIRE( readResult->GetExitCode() == SgfcExitCode::FatalError );
        REQUIRE( readResult->IsSgfDataValid() == false );

        auto parseResult = readResult->GetParseResult();
        REQUIRE( parseResult.size() == 1 );

        auto errorMessage = parseResult.front();
        REQUIRE( errorMessage->GetMessageType() == SgfcMessageType::FatalError );
        REQUIRE( errorMessage->GetMessageID() == SgfcMessageID::CouldNotOpenSourceFile );
        REQUIRE( errorMessage->GetMessageText().length() > 0 );

        auto document = readResult->GetDocument();
        REQUIRE( document->IsEmpty() == true );
        REQUIRE( document->GetGames().size() == 0 );
      }
    }
  }

  GIVEN( "The file exists but is not an .sgf file" )
  {
    std::string fileContent = GENERATE ( "", "foobar" );
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcDocumentReader performs the read operation" )
    {
      SgfcDocumentReader reader;
      auto readResult = reader.ReadSgfFile(tempFilePath);

      THEN( "The read operation result indicates failure" )
      {
        AssertErrorReadResultWhenNoValidSgfContent(readResult);
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  GIVEN( "The file exists and is an .sgf file without warnings or errors" )
  {
    std::string fileContent = GENERATE ( "(;)", "(;SZ[9]KM[6.5]B[aa])" );
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcDocumentReader performs the read operation" )
    {
      SgfcDocumentReader reader;
      auto readResult = reader.ReadSgfFile(tempFilePath);

      THEN( "The read operation result indicates success" )
      {
        REQUIRE( readResult->GetExitCode() == SgfcExitCode::Ok );
        REQUIRE( readResult->IsSgfDataValid() == true );

        auto parseResult = readResult->GetParseResult();
        REQUIRE( parseResult.size() == 0 );

        auto document = readResult->GetDocument();
        REQUIRE( document->IsEmpty() == false );
        REQUIRE( document->GetGames().size() == 1 );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  GIVEN( "The file exists and is an .sgf file with warnings or errors" )
  {
    std::string tempFilePath1 = tempFilePath + ".1";
    std::string tempFilePath2 = tempFilePath + ".2";
    std::string tempFilePath3 = tempFilePath + ".3";
    std::string fileContent1 = "(;C[foo]C[bar])";
    std::string fileContent2 = "(;)";
    std::string fileContent3 = "(;C[])";
    SgfcUtility::AppendTextToFile(tempFilePath1, fileContent1);
    SgfcUtility::AppendTextToFile(tempFilePath2, fileContent2);
    SgfcUtility::AppendTextToFile(tempFilePath3, fileContent3);

    WHEN( "SgfcDocumentReader performs the read operation" )
    {
      SgfcDocumentReader reader;
      auto readResult = reader.ReadSgfFile(tempFilePath);

      SgfcDocumentReader reader1;
      SgfcDocumentReader reader2;
      SgfcDocumentReader reader3;
      auto readResult1 = reader1.ReadSgfFile(tempFilePath1);
      auto readResult2 = reader2.ReadSgfFile(tempFilePath2);
      auto readResult3 = reader3.ReadSgfFile(tempFilePath3);

      THEN( "The SGF content is valid and the exit code and parse result match the expected warnings and errors" )
      {
        // This part of the test verifies that message types are correctly
        // mapped to exit codes. FatalError is verified in a different test.
        REQUIRE( readResult1->GetExitCode() == SgfcExitCode::Error );
        REQUIRE( readResult2->GetExitCode() == SgfcExitCode::Ok );
        REQUIRE( readResult3->GetExitCode() == SgfcExitCode::Warning );

        REQUIRE( readResult1->IsSgfDataValid() == true );
        REQUIRE( readResult2->IsSgfDataValid() == true );
        REQUIRE( readResult3->IsSgfDataValid() == true );

        auto parseResult1 = readResult1->GetParseResult();
        auto parseResult2 = readResult2->GetParseResult();
        auto parseResult3 = readResult3->GetParseResult();
        REQUIRE( parseResult1.size() == 1 );
        REQUIRE( parseResult2.size() == 0 );
        REQUIRE( parseResult3.size() == 1 );

        auto errorMessage1 = parseResult1.front();
        auto errorMessage3 = parseResult3.front();

        REQUIRE( errorMessage1->GetMessageType() == SgfcMessageType::Error );
        REQUIRE( errorMessage3->GetMessageType() == SgfcMessageType::Warning );
        REQUIRE( errorMessage1->GetMessageID() == SgfcMessageID::DuplicatePropertyDeleted );
        REQUIRE( errorMessage3->GetMessageID() == SgfcMessageID::EmptyValueDeleted );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath1);
    SgfcUtility::DeleteFileIfExists(tempFilePath2);
    SgfcUtility::DeleteFileIfExists(tempFilePath3);
  }

  GIVEN( "The file exists and is an .sgf file with a critical error" )
  {
    std::string fileContent = "(;FF[9])";
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcDocumentReader performs the read operation" )
    {
      SgfcDocumentReader reader;
      auto readResult = reader.ReadSgfFile(tempFilePath);

      THEN( "The SGF content is valid and the exit code and parse result match the expected critical error" )
      {
        REQUIRE( readResult->GetExitCode() == SgfcExitCode::Error );
        REQUIRE( readResult->IsSgfDataValid() == true );

        auto parseResult = readResult->GetParseResult();
        REQUIRE( parseResult.size() == 1 );

        auto errorMessage1 = parseResult.front();
        REQUIRE( errorMessage1->GetMessageType() == SgfcMessageType::Error );
        REQUIRE( errorMessage1->GetMessageID() == SgfcMessageID::UnknownFileFormat );
        REQUIRE( errorMessage1->IsCriticalMessage() == true );
        REQUIRE( errorMessage1->GetMessageText().length() > 0 );

        auto document = readResult->GetDocument();
        REQUIRE( document->IsEmpty() == false );
        REQUIRE( document->GetGames().size() == 1 );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }
}

SCENARIO( "SgfcDocumentReader reads SGF content from a string", "[frontend]" )
{
  GIVEN( "The string does not contain valid SGF data" )
  {
    std::string sgfContent = GENERATE ( "", "foobar" );

    WHEN( "SgfcDocumentReader performs the read operation" )
    {
      SgfcDocumentReader reader;
      auto readResult = reader.ReadSgfContent(sgfContent);

      THEN( "The read operation result indicates failure" )
      {
        AssertErrorReadResultWhenNoValidSgfContent(readResult);
      }
    }
  }

  // TODO: Add more tests that produce various compositions of a document
}

SCENARIO("The read operation behaviour is changed by arguments", "[frontend]")
{
  SgfcDocumentReader reader;

  GIVEN( "All warning messages are disabled" )
  {
    reader.GetArguments()->AddArgument(SgfcArgumentType::DisableWarningMessages);

    WHEN( "SgfcDocumentReader performs the read operation" )
    {
      // This normally generates warning 17 = SGFC error code "empty value deleted"
      std::string sgfContent = "(;C[])";
      auto readResult = reader.ReadSgfContent(sgfContent);

      THEN( "The read operation result indicates success" )
      {
        REQUIRE( readResult->GetExitCode() == SgfcExitCode::Ok );
        REQUIRE( readResult->IsSgfDataValid() == true );

        auto parseResult = readResult->GetParseResult();
        REQUIRE( parseResult.size() == 0 );
      }
    }
  }

  GIVEN( "The arguments are invalid" )
  {
    reader.GetArguments()->AddArgument(SgfcArgumentType::HardLineBreakMode, 42);

    WHEN( "SgfcDocumentReader performs the read operation" )
    {
      std::string sgfContent = "(;GM[1])";
      auto readResult = reader.ReadSgfContent(sgfContent);

      THEN( "The read operation result indicates failure" )
      {
        REQUIRE( readResult->GetExitCode() == SgfcExitCode::FatalError );
        REQUIRE( readResult->IsSgfDataValid() == false );

        auto parseResult = readResult->GetParseResult();
        REQUIRE( parseResult.size() == 1 );
        auto invalidCommandLineReason = parseResult.front();
        REQUIRE( invalidCommandLineReason->GetMessageType() == SgfcMessageType::FatalError );
        REQUIRE( invalidCommandLineReason->GetMessageID() == SgfcMessageID::BadCommandLineOptionParameter );
        REQUIRE( invalidCommandLineReason->GetMessageText().length() > 0 );
      }
    }
  }

  // TODO: Add more tests that excercise the argument types
}

SCENARIO( "SgfcDocumentReader performs post-processing", "[frontend]" )
{
  GIVEN( "Encoding mode 1 or 2 are used" )
  {
    int encodingMode = GENERATE ( SgfcPrivateConstants::EncodingModeSingleEncoding, SgfcPrivateConstants::EncodingModeMultipleEncodings );

    SgfcDocumentReader reader;
    reader.GetArguments()->AddArgument(SgfcArgumentType::EncodingMode, encodingMode);

    WHEN( "The SGF content does not contain a game tree" )
    {
      std::string sgfContent = GENERATE ( "", "foobar" );
      auto readResult = reader.ReadSgfContent(sgfContent);

      THEN( "No post-processing takes place" )
      {
        AssertErrorReadResultWhenNoValidSgfContent(readResult);
      }
    }

    WHEN( "The SGF content contains single game tree without a CA property" )
    {
      std::string sgfContent = "(;GM[1])";
      auto readResult = reader.ReadSgfContent(sgfContent);

      THEN( "The CA property value UTF-8 is added" )
      {
        AssertAllRootNodesContainCaProperty(readResult, SgfcPrivateConstants::TextEncodingNameUTF8);
      }
    }

    WHEN( "The SGF content contains multiple game trees without a CA property" )
    {
      std::string sgfContent = "(;GM[1])(;GM[1])";
      auto readResult = reader.ReadSgfContent(sgfContent);

      THEN( "The CA property value UTF-8 is added" )
      {
        AssertAllRootNodesContainCaProperty(readResult, SgfcPrivateConstants::TextEncodingNameUTF8);
      }
    }

    WHEN( "The SGF content contains multiple game trees, one with and one without a CA property" )
    {
      std::string sgfContent = "(;FF[4]GM[1]CA[ISO-8859-1])(;FF[4]GM[1])";
      auto readResult = reader.ReadSgfContent(sgfContent);

      THEN( "The CA property value UTF-8 is added or overwrites the previous value" )
      {
        AssertAllRootNodesContainCaProperty(readResult, SgfcPrivateConstants::TextEncodingNameUTF8);
      }
    }
  }

  GIVEN( "Encoding mode 2 is used" )
  {
    SgfcDocumentReader reader;
    reader.GetArguments()->AddArgument(SgfcArgumentType::EncodingMode, SgfcPrivateConstants::EncodingModeMultipleEncodings);
    reader.GetArguments()->AddArgument(SgfcArgumentType::DisableMessageID, SgfcMessageID::SgfContentHasDifferentEncodings);

    WHEN( "The SGF content contains multiple game trees with different CA property values" )
    {
      std::string sgfContent = "(;FF[4]GM[1]CA[ISO-8859-1])(;FF[4]GM[1]CA[UTF-8])(;FF[4]GM[1])";
      auto readResult = reader.ReadSgfContent(sgfContent);

      THEN( "The CA property value UTF-8 is added or overwrites the previous value" )
      {
        AssertAllRootNodesContainCaProperty(readResult, SgfcPrivateConstants::TextEncodingNameUTF8);
      }
    }
  }

  GIVEN( "Encoding mode 3 is used" )
  {
    SgfcDocumentReader reader;
    reader.GetArguments()->AddArgument(SgfcArgumentType::EncodingMode, SgfcPrivateConstants::EncodingModeNoDecoding);
    reader.GetArguments()->AddArgument(SgfcArgumentType::DisableMessageID, SgfcMessageID::SgfContentHasDifferentEncodings);

    WHEN( "The SGF content contains multiple game trees with different CA property values" )
    {
      std::string expectedTextEncodingName1 = "ISO-8859-1";
      std::string expectedTextEncodingName2 = "UTF-8";
      std::string sgfContent = "(;FF[4]GM[1]CA[" + expectedTextEncodingName1 + "])(;FF[4]GM[1]CA[" + expectedTextEncodingName2 + "])(;FF[4]GM[1])";
      auto readResult = reader.ReadSgfContent(sgfContent);

      THEN( "The CA property value UTF-8 is not added and does not overwrite the previous value" )
      {
        AssertSuccessReadResultWhenValidSgfContent(readResult);
        auto document = readResult->GetDocument();
        auto games = document->GetGames();
        REQUIRE( games.size() == 3 );
        AssertRootNodeContainsCaProperty(games[0], expectedTextEncodingName1);
        AssertRootNodeContainsCaProperty(games[1], expectedTextEncodingName2);
        AssertRootNodeDoesNotContainCaProperty(games[2]);
      }
    }
  }
}

void AssertErrorReadResultWhenNoValidSgfContent(std::shared_ptr<ISgfcDocumentReadResult> readResult)
{
  REQUIRE( readResult->GetExitCode() == SgfcExitCode::FatalError );
  REQUIRE( readResult->IsSgfDataValid() == false );

  auto parseResult = readResult->GetParseResult();
  REQUIRE( parseResult.size() == 1 );

  auto errorMessage = parseResult.front();
  REQUIRE( errorMessage->GetMessageType() == SgfcMessageType::FatalError );
  REQUIRE( errorMessage->GetMessageID() == SgfcMessageID::NoSgfData );
  REQUIRE( errorMessage->GetMessageText().length() > 0 );

  auto document = readResult->GetDocument();
  REQUIRE( document->IsEmpty() == true );
  REQUIRE( document->GetGames().size() == 0 );
}

void AssertSuccessReadResultWhenValidSgfContent(std::shared_ptr<ISgfcDocumentReadResult> readResult)
{
  REQUIRE( readResult->GetExitCode() == SgfcExitCode::Ok );
  REQUIRE( readResult->IsSgfDataValid() == true );

  auto parseResult = readResult->GetParseResult();
  REQUIRE( parseResult.size() == 0 );

  auto document = readResult->GetDocument();
  REQUIRE( document->IsEmpty() == false );
}

void AssertAllRootNodesContainCaProperty(std::shared_ptr<ISgfcDocumentReadResult> readResult, const SgfcSimpleText& textEncodingName)
{
  AssertSuccessReadResultWhenValidSgfContent(readResult);

  auto document = readResult->GetDocument();
  auto games = document->GetGames();
  REQUIRE( games.size() > 0 );

  for (auto game : games)
  {
    AssertRootNodeContainsCaProperty(game, textEncodingName);
  }
}

void AssertRootNodeContainsCaProperty(std::shared_ptr<ISgfcGame> game, const SgfcSimpleText& textEncodingName)
{
  REQUIRE( game->HasRootNode() == true );
  auto rootNode = game->GetRootNode();

  auto caProperty = rootNode->GetProperty(SgfcPropertyType::CA);
  REQUIRE( caProperty != nullptr );
  auto caPropertyValue = caProperty->GetPropertyValue();
  REQUIRE( caPropertyValue != nullptr );
  REQUIRE( caPropertyValue->IsComposedValue() == false );
  auto caSinglePropertyValue = caPropertyValue->ToSingleValue();
  REQUIRE( caSinglePropertyValue != nullptr );
  REQUIRE( caSinglePropertyValue->GetValueType() == LibSgfcPlusPlus::SgfcPropertyValueType::SimpleText );
  REQUIRE( caSinglePropertyValue->HasTypedValue() == true );
  auto caSimpleTextPropertyValue = caSinglePropertyValue->ToSimpleTextValue();
  REQUIRE( caSimpleTextPropertyValue->GetSimpleTextValue() == textEncodingName );
}

void AssertRootNodeDoesNotContainCaProperty(std::shared_ptr<ISgfcGame> game)
{
  REQUIRE( game->HasRootNode() == true );
  auto rootNode = game->GetRootNode();

  auto caProperty = rootNode->GetProperty(SgfcPropertyType::CA);
  REQUIRE( caProperty == nullptr );
}
