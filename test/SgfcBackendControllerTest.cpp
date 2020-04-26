// Library includes
#include <sgfc/backend/SgfcBackendController.h>
#include <SgfcConstants.h>

// Unit test library includes
#include <catch2/catch.hpp>

// C++ Standard Library includes
#include <cstdlib>

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
  // TODO: Find a cross-platform solution
  char filename[] = "/tmp/libsgfcplusplus-sgfcbackendcontroller-unittest.sgf.XXXXXXXXXX";
#ifdef _MSC_VER
  _mktemp(filename);
#else
  mktemp(filename);
#endif
  std::string tempFilePath = filename;  // the file is guaranteed to not exist

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
}
