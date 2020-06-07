// Library includes
#include <document/SgfcDocument.h>
#include <document/SgfcGame.h>
#include <document/SgfcNode.h>
#include <sgfc/frontend/SgfcDocumentWriter.h>
#include <sgfc/frontend/SgfcDocumentWriteResult.h>
#include <SgfcConstants.h>
#include <SgfcUtility.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

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

  std::string expectedFileContentSaved = "(;FF[4]GM[1]SZ[19]AP[SGFC:" + SgfcConstants::SgfcVersion + "])\n";

  GIVEN( "The file does not exist" )
  {
    WHEN( "SgfcDocumentWriter performs the write operation" )
    {
      SgfcDocumentWriter writer;
      auto writeResult = writer.WriteSgfFile(document, tempFilePath);

      THEN( "The write operation succeeds" )
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

// Mark the scenario with the [filesystem] tag because behind the scenes
// SgfcDocumentWriter writes the SGF content to a temporary file
SCENARIO( "SgfcDocumentWriter writes SGF content to a string", "[frontend][filesystem]" )
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
          std::runtime_error);
      }
    }
  }

  auto document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());
  auto rootNode = std::shared_ptr<ISgfcNode>(new SgfcNode());
  auto game = std::shared_ptr<ISgfcGame>(new SgfcGame(rootNode));
  document->AppendGame(game);

  GIVEN( "The string is empty" )
  {
    WHEN( "SgfcDocumentWriter performs the write operation" )
    {
      SgfcDocumentWriter writer;

      // TODO: Should be: The string contains the SGF content
      THEN( "The write operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          writer.WriteSgfContent(document, sgfContent),
          std::runtime_error);
      }
    }
  }

  GIVEN( "The string is not empty" )
  {
    WHEN( "SgfcDocumentWriter performs the write operation" )
    {
      SgfcDocumentWriter writer;

      // TODO: Should be: Overwrites the string content
      THEN( "The write operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          writer.WriteSgfContent(document, sgfContent),
          std::runtime_error);
      }
    }
  }

  // TODO: Add more tests for various compositions of the document
}
