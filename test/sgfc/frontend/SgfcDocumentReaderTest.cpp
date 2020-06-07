// Library includes
#include <sgfc/frontend/SgfcDocumentReader.h>
#include <SgfcUtility.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

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
        // 3 = SGFC error code "could not open source file"
        REQUIRE( errorMessage->GetMessageID() == 3 );
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
        REQUIRE( readResult->GetExitCode() == SgfcExitCode::FatalError );
        REQUIRE( readResult->IsSgfDataValid() == false );

        auto parseResult = readResult->GetParseResult();
        REQUIRE( parseResult.size() == 1 );

        auto errorMessage = parseResult.front();
        REQUIRE( errorMessage->GetMessageType() == SgfcMessageType::FatalError );
        // 7 = SGFC error code "no SGF data found"
        REQUIRE( errorMessage->GetMessageID() == 7 );
        REQUIRE( errorMessage->GetMessageText().length() > 0 );

        auto document = readResult->GetDocument();
        REQUIRE( document->IsEmpty() == true );
        REQUIRE( document->GetGames().size() == 0 );
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
        // 28 = SGFC error code "property already exists"
        REQUIRE( errorMessage1->GetMessageID() == 28 );
        // 17 = SGFC error code "empty value deleted"
        REQUIRE( errorMessage3->GetMessageID() == 17 );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath1);
    SgfcUtility::DeleteFileIfExists(tempFilePath2);
    SgfcUtility::DeleteFileIfExists(tempFilePath3);
  }

  GIVEN( "The file exists and is an .sgf file with a fatal error" )
  {
    std::string fileContent = "(;FF[9])";
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcDocumentReader performs the read operation" )
    {
      SgfcDocumentReader reader;
      auto readResult = reader.ReadSgfFile(tempFilePath);

      THEN( "The SGF content is not valid and the exit code and parse result match the expected fatal error" )
      {
        REQUIRE( readResult->GetExitCode() == SgfcExitCode::FatalError );
        REQUIRE( readResult->IsSgfDataValid() == false );

        auto parseResult = readResult->GetParseResult();
        REQUIRE( parseResult.size() == 1 );

        auto errorMessage = parseResult.front();
        REQUIRE( errorMessage->GetMessageType() == SgfcMessageType::FatalError );
        // 46 = unknown file format
        REQUIRE( errorMessage->GetMessageID() == 46 );
        REQUIRE( errorMessage->GetMessageText().length() > 0 );

        auto document = readResult->GetDocument();
        REQUIRE( document->IsEmpty() == true );
        REQUIRE( document->GetGames().size() == 0 );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }
}

// Mark the scenario with the [filesystem] tag because behind the scenes
// SgfcDocumentReader saves the SGF content to a temporary file
SCENARIO( "SgfcDocumentReader reads SGF content from a string", "[frontend][filesystem]" )
{
  GIVEN( "The string does not contain valid SGF data" )
  {
    std::string sgfContent = GENERATE ( "", "foobar" );

    WHEN( "SgfcDocumentReader performs the read operation" )
    {
      SgfcDocumentReader reader;

      THEN( "The read operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          reader.ReadSgfContent(sgfContent),
          std::runtime_error);
      }
    }
  }

  // TODO: Add more tests that produce various compositions of a document
}
