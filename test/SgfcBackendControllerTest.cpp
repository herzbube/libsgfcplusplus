// Library includes
#include <sgfc/backend/SgfcBackendController.h>
#include <SgfcConstants.h>
#include <SgfcUtility.h>

// SGFC includes
extern "C"
{
//  #include <stdio.h>  // required to define size_t and FILE which are used in all.h
  #include "../../../sgfc/all.h"
}

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcBackendController is constructed", "[backend]" )
{
  GIVEN( "The default constructor is used" )
  {
    WHEN( "SgfcBackendController is constructed" )
    {
      SgfcBackendController backendController;

      THEN( "SgfcBackendController has the expected state" )
      {
        auto arguments = backendController.GetArguments();
        REQUIRE( arguments.size() == 0 );

        REQUIRE( backendController.IsCommandLineValid() == true );

        REQUIRE_THROWS_AS(
          backendController.GetInvalidCommandLineReason(),
          std::logic_error);
      }
    }
  }

  GIVEN( "The constructor that takes command line arguments is used" )
  {
    WHEN( "SgfcBackendController is constructed with valid command line arguments" )
    {
      auto expectedArguments = GENERATE(
        std::vector<std::string> {},
        std::vector<std::string> { "-n" },
        std::vector<std::string> { "-n", "-p", "-u" },
        std::vector<std::string> { "-n", "-n" }
      );
      SgfcBackendController backendController(expectedArguments);

      THEN( "SgfcBackendController has the expected state" )
      {
        auto actualArguments = backendController.GetArguments();
        REQUIRE( actualArguments == expectedArguments );

        REQUIRE( backendController.IsCommandLineValid() == true );

        REQUIRE_THROWS_AS(
          backendController.GetInvalidCommandLineReason(),
          std::logic_error);
      }
    }

    WHEN( "SgfcBackendController is constructed with invalid command line arguments" )
    {
      struct TestData
      {
        std::vector<std::string> CommandLineArguments;
        int InvalidCommandLineReasonMessageID;
      };
      auto testData = GENERATE(
        TestData { std::vector<std::string> { "foo" }, SgfcConstants::ArgumentIsNotAnOptionMessageID },
        TestData { std::vector<std::string> { "-h" }, SgfcConstants::ArgumentIsNotAllowedMessageID },
        // 2 = SGFC error code "unknown command line option"
        TestData { std::vector<std::string> { "-a" }, 2 },
        // 49 = SGFC error code "bad command line option parameter"
        TestData { std::vector<std::string> { "-yZZ" }, 49 }
      );

      SgfcBackendController backendController(testData.CommandLineArguments);

      THEN( "SgfcBackendController has the expected state" )
      {
        auto actualArguments = backendController.GetArguments();
        REQUIRE( actualArguments == testData.CommandLineArguments );

        REQUIRE( backendController.IsCommandLineValid() == false );

        auto invalidCommandLineReason = backendController.GetInvalidCommandLineReason();
        REQUIRE( invalidCommandLineReason->GetMessageType() == SgfcMessageType::FatalError );
        REQUIRE( invalidCommandLineReason->GetMessageID() == testData.InvalidCommandLineReasonMessageID );
        REQUIRE( invalidCommandLineReason->GetMessageText().length() > 0 );
      }
    }
  }
}

SCENARIO( "SgfcBackendController loads SGF content from the filesystem", "[backend][filesystem]" )
{
  // Using a random UUID as the filename, it is reasonably safe to assume that
  // the file does not exist
  std::string tempFilePath = SgfcUtility::JoinPathComponents(
    SgfcUtility::GetTempFolderPath(),
    SgfcUtility::CreateUuid());

  GIVEN( "SgfcBackendController was constructed with invalid command line arguments" )
  {
    std::vector<std::string> invalidCommandLineArguments = { "-h" };
    SgfcBackendController backendController(invalidCommandLineArguments);

    WHEN( "SgfcBackendController attempts to perform the load operation" )
    {
      THEN( "The load operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          backendController.LoadSgfFile(tempFilePath),
          std::logic_error);
      }
    }
  }

  GIVEN( "The file does not exist" )
  {
    WHEN( "SgfcBackendController performs the load operation" )
    {
      SgfcBackendController backendController;
      auto loadResult = backendController.LoadSgfFile(tempFilePath);

      THEN( "The load operation result indicates failure" )
      {
        auto parseResult = loadResult->GetParseResult();
        REQUIRE( parseResult.size() == 1 );

        auto errorMessage = parseResult.front();
        REQUIRE( errorMessage->GetMessageType() == SgfcMessageType::FatalError );
        // 3 = SGFC error code "could not open source file"
        REQUIRE( errorMessage->GetMessageID() == 3 );
        REQUIRE( errorMessage->GetMessageText().length() > 0 );
      }
    }
  }

  GIVEN( "The file exists but is not an .sgf file" )
  {
    std::string fileContent = GENERATE ( "", "foobar" );
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcBackendController performs the load operation" )
    {
      SgfcBackendController backendController;
      auto loadResult = backendController.LoadSgfFile(tempFilePath);

      THEN( "The load operation result indicates failure" )
      {
        auto parseResult = loadResult->GetParseResult();
        REQUIRE( parseResult.size() == 1 );

        auto errorMessage = parseResult.front();
        REQUIRE( errorMessage->GetMessageType() == SgfcMessageType::FatalError );
        // 7 = SGFC error code "no SGF data found"
        REQUIRE( errorMessage->GetMessageID() == 7 );
        REQUIRE( errorMessage->GetMessageText().length() > 0 );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  GIVEN( "The file exists and is an .sgf file" )
  {
    std::string fileContent = GENERATE ( "(;)", "(;SZ[9]KM[6.5]B[aa])" );
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcBackendController performs the load operation" )
    {
      SgfcBackendController backendController;
      auto loadResult = backendController.LoadSgfFile(tempFilePath);

      THEN( "The load operation result indicates success" )
      {
        auto parseResult = loadResult->GetParseResult();
        REQUIRE( parseResult.size() == 0 );

        auto sgfDataWrapper = loadResult->GetSgfDataWrapper();
        auto sgfData = sgfDataWrapper->GetSgfData();

        REQUIRE( sgfData->buffer != nullptr );
        // sgfData->buffer does not have a zero-byte terminator, we must provide
        // the buffer length
        REQUIRE( std::string(sgfData->buffer, fileContent.size()) == fileContent );
        REQUIRE( sgfData->b_end == sgfData->buffer + fileContent.size() );
        // current must point to the end of the buffer because the buffer has
        // been parsed
        REQUIRE( sgfData->current == sgfData->b_end );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  GIVEN( "Several SgfcBackendController objects with different command line arguments are constructed" )
  {
    std::string fileContent = "(;C[])(;)";
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcBackendController performs the load operation" )
    {
      std::vector<std::string> commandLineArguments1 = { "-r" };  // Restrictive checking
      std::vector<std::string> commandLineArguments2 = { "-w" };  // Disable warnings
      SgfcBackendController backendController1(commandLineArguments1);
      SgfcBackendController backendController2(commandLineArguments2);
      SgfcBackendController backendController3;
      auto loadResult1 = backendController1.LoadSgfFile(tempFilePath);
      auto loadResult2 = backendController2.LoadSgfFile(tempFilePath);
      auto loadResult3 = backendController3.LoadSgfFile(tempFilePath);

      THEN( "The load operation result matches the the command line arguments" )
      {
        // The goal of this test is to verify that when SgfcBackendController
        // performs a load operation it resets the global state within SGFC to
        // match its own command line arguments. The order in which the
        // controllers are exercised is semi-relevant.

        auto parseResult1 = loadResult1->GetParseResult();
        auto parseResult2 = loadResult2->GetParseResult();
        auto parseResult3 = loadResult3->GetParseResult();
        REQUIRE( parseResult1.size() == 2 );
        REQUIRE( parseResult2.size() == 0 );
        REQUIRE( parseResult3.size() == 1 );

        auto errorMessage1a = parseResult1.front();
        auto errorMessage1b = parseResult1.back();
        auto errorMessage3 = parseResult3.front();

        REQUIRE( errorMessage1a->GetMessageType() == SgfcMessageType::Warning );
        REQUIRE( errorMessage1b->GetMessageType() == SgfcMessageType::Error );
        REQUIRE( errorMessage3->GetMessageType() == SgfcMessageType::Warning );
        // 17 = SGFC error code "empty value deleted"
        REQUIRE( errorMessage1a->GetMessageID() == 17 );
        REQUIRE( errorMessage3->GetMessageID() == 17 );
        // 60 = SGFC error code "file contains more than one game tree"
        REQUIRE( errorMessage1b->GetMessageID() == 60 );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }
}

SCENARIO( "SgfcBackendController saves SGF content to the filesystem", "[backend][filesystem]" )
{
  // Using a random UUID as the filename, it is reasonably safe to assume that
  // the file does not exist
  std::string tempFilePath = SgfcUtility::JoinPathComponents(
    SgfcUtility::GetTempFolderPath(),
    SgfcUtility::CreateUuid());

  GIVEN( "SgfcBackendController was constructed with invalid command line arguments" )
  {
    std::vector<std::string> invalidCommandLineArguments = { "-h" };
    SgfcBackendController backendController(invalidCommandLineArguments);
    std::string contentBuffer;
    auto backendDataWrapper = std::shared_ptr<SgfcBackendDataWrapper>(new SgfcBackendDataWrapper(contentBuffer));

    WHEN( "SgfcBackendController attempts to perform the save operation" )
    {
      THEN( "The save operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          backendController.SaveSgfFile(tempFilePath, backendDataWrapper),
          std::logic_error);
      }
    }
  }

  std::string expectedFileContent = "(;FF[4]GM[1]SZ[19]AP[SGFC:" + SgfcConstants::SgfcVersion + "])\n";

  GIVEN( "The file does not exist" )
  {
    WHEN( "SgfcBackendController performs the save operation" )
    {
      std::string contentBuffer = "(;)";
      auto backendDataWrapper = std::shared_ptr<SgfcBackendDataWrapper>(new SgfcBackendDataWrapper(contentBuffer));
      SgfcBackendController backendController;
      auto backendSaveResult = backendController.SaveSgfFile(tempFilePath, backendDataWrapper);

      THEN( "The save operation succeeds" )
      {
        auto saveResult = backendSaveResult->GetSaveResult();
        REQUIRE( saveResult.size() == 0 );

        std::string fileContent = SgfcUtility::ReadFileContent(tempFilePath);
        REQUIRE( fileContent == expectedFileContent );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  GIVEN( "The file already exists" )
  {
    WHEN( "SgfcBackendController performs the save operation" )
    {
      SgfcUtility::AppendTextToFile(tempFilePath, "foo");

      std::string contentBuffer = "(;)";
      auto backendDataWrapper = std::shared_ptr<SgfcBackendDataWrapper>(new SgfcBackendDataWrapper(contentBuffer));
      SgfcBackendController backendController;
      auto backendSaveResult = backendController.SaveSgfFile(tempFilePath, backendDataWrapper);

      THEN( "The save operation succeeds and overwrites the previous file content" )
      {
        auto saveResult = backendSaveResult->GetSaveResult();
        REQUIRE( saveResult.size() == 0 );

        std::string fileContent = SgfcUtility::ReadFileContent(tempFilePath);
        REQUIRE( fileContent == expectedFileContent );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }
}
