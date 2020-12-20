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
#include <document/SgfcDocument.h>
#include <document/SgfcGame.h>
#include <document/SgfcNode.h>
#include <sgfc/argument/SgfcArgument.h>
#include <sgfc/argument/SgfcArguments.h>
#include <sgfc/frontend/SgfcDocumentWriter.h>
#include <sgfc/frontend/SgfcDocumentWriteResult.h>
#include <SgfcConstants.h>
#include <SgfcUtility.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;


void AssertWriteResult(std::shared_ptr<ISgfcDocumentWriteResult> writeResult, const std::string& actualSgfContent, const std::string& expectedSgfContent);


SCENARIO( "SgfcDocumentWriter is constructed", "[frontend]" )
{
  GIVEN( "The default constructor is used" )
  {
    WHEN( "SgfcDocumentWriter is constructed" )
    {
      THEN( "SgfcDocumentWriter is constructed successfully" )
      {
        REQUIRE_NOTHROW( SgfcDocumentWriter() );
      }
    }

    WHEN( "SgfcDocumentWriter is constructed" )
    {
      SgfcDocumentWriter writer;

      THEN( "SgfcDocumentWriter has the expected default state" )
      {
        auto arguments = writer.GetArguments();
        REQUIRE( arguments != nullptr );
        REQUIRE( arguments->HasArguments() == true );
        auto argumentsCollection = arguments->GetArguments();
        REQUIRE( argumentsCollection.size() == 1 );
        auto argument = argumentsCollection.front();
        REQUIRE( argument->GetArgumentType() == SgfcArgumentType::DefaultEncoding );
        REQUIRE( argument->HasStringTypeParameter() == true );
        REQUIRE( argument->GetStringTypeParameter() == "UTF-8" );
      }
    }
  }
}

SCENARIO( "SgfcDocumentWriter writes SGF content to the filesystem", "[frontend][filesystem]" )
{
  // Using a random UUID as the filename, it is reasonably safe to assume that
  // the file does not exist
  std::string tempFilePath = SgfcUtility::JoinPathComponents(
    SgfcUtility::GetTempFolderPath(),
    SgfcUtility::CreateUuid());

  GIVEN( "The document cannot be encoded because a root node is missing" )
  {
    auto document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());
    auto game = std::shared_ptr<ISgfcGame>(new SgfcGame());
    document->AppendGame(game);

    WHEN( "SgfcDocumentWriter performs the write operation" )
    {
      SgfcDocumentWriter writer;

      THEN( "The write operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          writer.WriteSgfFile(document, tempFilePath),
          std::logic_error);
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  auto document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());
  auto rootNode = std::shared_ptr<ISgfcNode>(new SgfcNode());
  auto game = std::shared_ptr<ISgfcGame>(new SgfcGame(rootNode));
  document->AppendGame(game);

  std::string expectedFileContentSaved = "(;FF[4]CA[UTF-8]GM[1]SZ[19]AP[SGFC:" + SgfcConstants::SgfcVersion + "])\n";

  GIVEN( "The file does not exist" )
  {
    WHEN( "SgfcDocumentWriter performs the write operation" )
    {
      SgfcDocumentWriter writer;
      auto writeResult = writer.WriteSgfFile(document, tempFilePath);

      THEN( "The write operation succeeds" )
      {
        std::string fileContentSaved = SgfcUtility::ReadFileContent(tempFilePath);
        AssertWriteResult(writeResult, fileContentSaved, expectedFileContentSaved);
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  GIVEN( "The file already exists" )
  {
    SgfcUtility::AppendTextToFile(tempFilePath, "foo");

    WHEN( "SgfcDocumentWriter performs the write operation" )
    {
      SgfcDocumentWriter writer;
      auto writeResult = writer.WriteSgfFile(document, tempFilePath);

      THEN( "The save operation succeeds and overwrites the previous file content" )
      {
        REQUIRE( writeResult->GetExitCode() == SgfcExitCode::Ok );

        auto parseResult = writeResult->GetParseResult();
        REQUIRE( parseResult.size() == 0 );

        std::string fileContentSaved = SgfcUtility::ReadFileContent(tempFilePath);
        REQUIRE( fileContentSaved == expectedFileContentSaved );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  // We would like to write more tests to verify that the write operations can
  // return an SgfExitCode that maps to a warning, error or fatal error.
  // Currently there are no known SGF contents where SGFC generates a warning
  // or error message during save, and fatal errors are all tied to filesystem
  // problems that are difficult to simulate in a test.
}

SCENARIO( "SgfcDocumentWriter writes SGF content to a string", "[frontend]" )
{
  std::string sgfContent;

  GIVEN( "The document cannot be encoded because a root node is missing" )
  {
    auto document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());
    auto game = std::shared_ptr<ISgfcGame>(new SgfcGame());
    document->AppendGame(game);

    WHEN( "SgfcDocumentWriter performs the write operation" )
    {
      SgfcDocumentWriter writer;

      THEN( "The write operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          writer.WriteSgfContent(document, sgfContent),
          std::logic_error);
      }
    }
  }

  auto document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());
  auto rootNode = std::shared_ptr<ISgfcNode>(new SgfcNode());
  auto game = std::shared_ptr<ISgfcGame>(new SgfcGame(rootNode));
  document->AppendGame(game);

  std::string expectedSgfContent = "(;FF[4]CA[UTF-8]GM[1]SZ[19]AP[SGFC:" + SgfcConstants::SgfcVersion + "])\n";

  GIVEN( "The string is empty" )
  {
    WHEN( "SgfcDocumentWriter performs the write operation" )
    {
      SgfcDocumentWriter writer;
      auto writeResult = writer.WriteSgfContent(document, sgfContent);

      THEN( "The write operation writes the SGF content into the string" )
      {
        AssertWriteResult(writeResult, sgfContent, expectedSgfContent);
      }
    }
  }

  GIVEN( "The string is not empty" )
  {
    WHEN( "SgfcDocumentWriter performs the write operation" )
    {
      sgfContent = "foo";

      SgfcDocumentWriter writer;
      auto writeResult = writer.WriteSgfContent(document, sgfContent);

      THEN( "The write operation overwrites the string content with the SGF content" )
      {
        AssertWriteResult(writeResult, sgfContent, expectedSgfContent);
      }
    }
  }

  // TODO: Add more tests for various compositions of the document
}

SCENARIO("The write operation behaviour is changed by arguments", "[frontend]")
{
  SgfcDocumentWriter writer;
  std::string sgfContent;

  auto document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());
  auto rootNode = std::shared_ptr<ISgfcNode>(new SgfcNode());
  auto game = std::shared_ptr<ISgfcGame>(new SgfcGame(rootNode));
  document->AppendGame(game);

  GIVEN( "All warning messages are disabled" )
  {
    writer.GetArguments()->AddArgument(SgfcArgumentType::DeleteEmptyNodes);
    writer.GetArguments()->AddArgument(SgfcArgumentType::DisableWarningMessages);

    WHEN( "SgfcDocumentWriter performs the write operation" )
    {
      // SgfcArgumentType::DeleteEmptyNodes deletes the empty root node. It
      // also normally generates warning 55 = empty node deleted, but we
      // suppress it.
      std::string expectedSgfContent = "";
      auto writeResult = writer.WriteSgfContent(document, sgfContent);

      THEN( "The write operation result indicates success" )
      {
        AssertWriteResult(writeResult, sgfContent, expectedSgfContent);
      }
    }
  }

  GIVEN( "The arguments are invalid" )
  {
    writer.GetArguments()->AddArgument(SgfcArgumentType::HardLineBreakMode, 42);

    WHEN( "SgfcDocumentReader performs the read operation" )
    {
      auto writeResult = writer.WriteSgfContent(document, sgfContent);

      THEN( "The write operation result indicates failure" )
      {
        REQUIRE( writeResult->GetExitCode() == SgfcExitCode::FatalError );

        auto parseResult = writeResult->GetParseResult();
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

void AssertWriteResult(
  std::shared_ptr<ISgfcDocumentWriteResult> writeResult,
  const std::string& actualSgfContent,
  const std::string& expectedSgfContent)
{
  REQUIRE( writeResult->GetExitCode() == SgfcExitCode::Ok );

  auto parseResult = writeResult->GetParseResult();
  REQUIRE( parseResult.size() == 0 );

  REQUIRE( actualSgfContent == expectedSgfContent );
}
