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
#include <sgfc/argument/SgfcArgument.h>
#include <sgfc/backend/SgfcBackendController.h>
#include <SgfcConstants.h>
#include <SgfcUtility.h>

// SGFC includes
extern "C"
{
  #include <../sgfc/src/all.h>
}

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;


void AssertErrorLoadResultWhenNoValidSgfContent(std::shared_ptr<SgfcBackendLoadResult> loadResult);
void AssertLoadResultWhenSgfDataHasNoWarningsOrErrors(std::shared_ptr<SgfcBackendLoadResult> loadResult, const std::string& sgfContent);
void AssertLoadResultWhenSgfDataHasWarningsOrErrors(std::shared_ptr<SgfcBackendLoadResult> loadResult1, std::shared_ptr<SgfcBackendLoadResult> loadResult2, std::shared_ptr<SgfcBackendLoadResult> loadResult3);
void AssertLoadResultWhenSgfDataHasCriticalError(std::shared_ptr<SgfcBackendLoadResult> loadResult);
void AssertSaveResult(std::shared_ptr<SgfcBackendSaveResult> backendSaveResult, const std::string& actualSgfContent, const std::string& expectedSgfContent);


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
        std::vector<std::shared_ptr<ISgfcArgument>> {},
        std::vector<std::shared_ptr<ISgfcArgument>>
        {
          std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DeleteEmptyNodes))
        },
        std::vector<std::shared_ptr<ISgfcArgument>>
        {
          std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DeleteEmptyNodes)),
          std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::UseOldPassMoveNotation)),
          std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DeleteUnknownProperties))
        },
        std::vector<std::shared_ptr<ISgfcArgument>>
        {
          std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DeleteEmptyNodes)),
          std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DeleteEmptyNodes))
        }
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
        std::vector<std::shared_ptr<ISgfcArgument>> CommandLineArguments;
        int InvalidCommandLineReasonMessageID;
      };
      auto testData = GENERATE(
        // 49 = SGFC error code "bad command line option parameter"
        TestData
        {
          std::vector<std::shared_ptr<ISgfcArgument>>
          {
            std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DeletePropertyType, SgfcPropertyType::BO))
          }, 49
        }
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
  std::vector<std::shared_ptr<ISgfcArgument>> emptyCommandLineArguments;

  // Using a random UUID as the filename, it is reasonably safe to assume that
  // the file does not exist
  std::string tempFilePath = SgfcUtility::JoinPathComponents(
    SgfcUtility::GetTempFolderPath(),
    SgfcUtility::CreateUuid());

  GIVEN( "SgfcBackendController was constructed with invalid command line arguments" )
  {
    std::vector<std::shared_ptr<ISgfcArgument>> invalidCommandLineArguments =
    {
      std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DeletePropertyType, SgfcPropertyType::BO))
    };
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
      SgfcBackendController backendController(emptyCommandLineArguments);
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
      SgfcBackendController backendController(emptyCommandLineArguments);
      auto loadResult = backendController.LoadSgfFile(tempFilePath);

      THEN( "The load operation result indicates failure" )
      {
        AssertErrorLoadResultWhenNoValidSgfContent(loadResult);
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  GIVEN( "The file exists and is an .sgf file without warnings or errors" )
  {
    std::string fileContent = GENERATE ( "(;)", "(;SZ[9]KM[6.5]B[aa])" );
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcBackendController performs the load operation" )
    {
      SgfcBackendController backendController(emptyCommandLineArguments);
      auto loadResult = backendController.LoadSgfFile(tempFilePath);

      THEN( "The load operation result indicates success" )
      {
        AssertLoadResultWhenSgfDataHasNoWarningsOrErrors(loadResult, fileContent);
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  GIVEN( "The file exists and is an .sgf file with warnings or errors" )
  {
    std::string fileContent = "(;C[])(;)";
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcBackendController performs the load operation" )
    {
      std::vector<std::shared_ptr<ISgfcArgument>> commandLineArguments1 =
      {
        std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::EnableRestrictiveChecking))
      };
      std::vector<std::shared_ptr<ISgfcArgument>> commandLineArguments2 =
      {
        std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DisableWarningMessages))
      };
      SgfcBackendController backendController1(commandLineArguments1);
      SgfcBackendController backendController2(commandLineArguments2);
      SgfcBackendController backendController3(emptyCommandLineArguments);
      auto loadResult1 = backendController1.LoadSgfFile(tempFilePath);
      auto loadResult2 = backendController2.LoadSgfFile(tempFilePath);
      auto loadResult3 = backendController3.LoadSgfFile(tempFilePath);

      THEN( "The SGF content is valid and the exit code and parse result match the expected warnings and errors" )
      {
        AssertLoadResultWhenSgfDataHasWarningsOrErrors(loadResult1, loadResult2, loadResult3);
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  GIVEN( "The file exists and is an .sgf file with a critical error" )
  {
    std::string fileContent = "(;FF[9])";
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcBackendController performs the load operation" )
    {
      SgfcBackendController backendController(emptyCommandLineArguments);
      auto loadResult = backendController.LoadSgfFile(tempFilePath);

      THEN( "The loaded SGF content is valid and the exit code and parse result match the expected critical error" )
      {
        AssertLoadResultWhenSgfDataHasCriticalError(loadResult);
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }
}

SCENARIO( "SgfcBackendController loads SGF content from a string", "[backend][zzz]" )
{
  std::vector<std::shared_ptr<ISgfcArgument>> emptyCommandLineArguments;

//  GIVEN( "SgfcBackendController was constructed with invalid command line arguments" )
//  {
//    std::vector<std::shared_ptr<ISgfcArgument>> invalidCommandLineArguments =
//    {
//      std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DeletePropertyType, SgfcPropertyType::BO))
//    };
//    SgfcBackendController backendController(invalidCommandLineArguments);
//
//    WHEN( "SgfcBackendController attempts to perform the load operation" )
//    {
//      THEN( "The load operation throws an exception" )
//      {
//        REQUIRE_THROWS_AS(
//          backendController.LoadSgfContent("(;)"),
//          std::logic_error);
//      }
//    }
//  }
//
//  GIVEN( "The string does not contain valid SGF data" )
//  {
//    std::string sgfContent = GENERATE ( "", "foobar" );
//
//    WHEN( "SgfcBackendController performs the load operation" )
//    {
//      SgfcBackendController backendController(emptyCommandLineArguments);
//      auto loadResult = backendController.LoadSgfContent(sgfContent);
//
//      THEN( "The load operation result indicates failure" )
//      {
//        AssertErrorLoadResultWhenNoValidSgfContent(loadResult);
//      }
//    }
//  }

  GIVEN( "The string contains SGF data without warnings or errors" )
  {
    std::string sgfContent = GENERATE ( "(;)", "(;SZ[9]KM[6.5]B[aa])" );

    WHEN( "SgfcBackendController performs the load operation" )
    {
      SgfcBackendController backendController(emptyCommandLineArguments);
      auto loadResult = backendController.LoadSgfContent(sgfContent);

      THEN( "The load operation result indicates success" )
      {
        AssertLoadResultWhenSgfDataHasNoWarningsOrErrors(loadResult, sgfContent);
      }
    }
  }

  GIVEN( "The string contains SGF data with warnings or errors" )
  {
    std::string sgfContent = "(;C[])(;)";

    WHEN( "SgfcBackendController performs the load operation" )
    {
      std::vector<std::shared_ptr<ISgfcArgument>> commandLineArguments1 =
      {
        std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::EnableRestrictiveChecking))
      };
      std::vector<std::shared_ptr<ISgfcArgument>> commandLineArguments2 =
      {
        std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DisableWarningMessages))
      };
      SgfcBackendController backendController1(commandLineArguments1);
      SgfcBackendController backendController2(commandLineArguments2);
      SgfcBackendController backendController3(emptyCommandLineArguments);
      auto loadResult1 = backendController1.LoadSgfContent(sgfContent);
      auto loadResult2 = backendController2.LoadSgfContent(sgfContent);
      auto loadResult3 = backendController3.LoadSgfContent(sgfContent);

      THEN( "The SGF content is valid and the exit code and parse result match the expected warnings and errors" )
      {
        AssertLoadResultWhenSgfDataHasWarningsOrErrors(loadResult1, loadResult2, loadResult3);
      }
    }
  }

  GIVEN( "The string contains SGF data with a fatal error" )
  {
    std::string sgfContent = "(;FF[9])";

    WHEN( "SgfcBackendController performs the load operation" )
    {
      SgfcBackendController backendController(emptyCommandLineArguments);
      auto loadResult = backendController.LoadSgfContent(sgfContent);

      THEN( "The loaded SGF content is valid and the exit code and parse result match the expected critical error" )
      {
        AssertLoadResultWhenSgfDataHasCriticalError(loadResult);
      }
    }
  }
}

SCENARIO( "SgfcBackendController saves SGF content to the filesystem", "[backend][filesystem]" )
{
  std::vector<std::shared_ptr<ISgfcArgument>> emptyCommandLineArguments;

  // Using a random UUID as the filename, it is reasonably safe to assume that
  // the file does not exist
  std::string tempFilePath = SgfcUtility::JoinPathComponents(
    SgfcUtility::GetTempFolderPath(),
    SgfcUtility::CreateUuid());

  GIVEN( "SgfcBackendController was constructed with invalid command line arguments" )
  {
    std::vector<std::shared_ptr<ISgfcArgument>> invalidCommandLineArguments =
    {
      std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DeletePropertyType, SgfcPropertyType::BO))
    };
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
      SgfcBackendController backendController(emptyCommandLineArguments);
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
      SgfcBackendController backendController(emptyCommandLineArguments);
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

SCENARIO( "SgfcBackendController saves SGF content to a string", "[backend]" )
{
  std::vector<std::shared_ptr<ISgfcArgument>> emptyCommandLineArguments;
  std::string sgfContent;

  GIVEN( "SgfcBackendController was constructed with invalid command line arguments" )
  {
    std::vector<std::shared_ptr<ISgfcArgument>> invalidCommandLineArguments =
    {
      std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DeletePropertyType, SgfcPropertyType::BO))
    };
    SgfcBackendController backendController(invalidCommandLineArguments);
    std::string contentBuffer;
    auto backendDataWrapper = std::shared_ptr<SgfcBackendDataWrapper>(new SgfcBackendDataWrapper(contentBuffer));

    WHEN( "SgfcBackendController attempts to perform the save operation" )
    {
      THEN( "The save operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          backendController.SaveSgfContent(sgfContent, backendDataWrapper),
          std::logic_error);
      }
    }
  }

  std::string contentBuffer = "(;)";
  std::string expectedStringContentSaved = "(;FF[4]GM[1]SZ[19]AP[SGFC:" + SgfcConstants::SgfcVersion + "])\n";

  GIVEN( "The string is empty" )
  {
    WHEN( "SgfcBackendController performs the save operation" )
    {
      auto backendDataWrapper = std::shared_ptr<SgfcBackendDataWrapper>(new SgfcBackendDataWrapper(contentBuffer));
      SgfcBackendController backendController(emptyCommandLineArguments);
      auto backendSaveResult = backendController.SaveSgfContent(sgfContent, backendDataWrapper);

      THEN( "The save operation succeeds and writes the SGF content into the string" )
      {
        AssertSaveResult(backendSaveResult, sgfContent, expectedStringContentSaved);
      }
    }
  }

  GIVEN( "The string is not empty" )
  {
    WHEN( "SgfcBackendController performs the save operation" )
    {
      sgfContent = "foo";

      auto backendDataWrapper = std::shared_ptr<SgfcBackendDataWrapper>(new SgfcBackendDataWrapper(contentBuffer));
      SgfcBackendController backendController(emptyCommandLineArguments);
      auto backendSaveResult = backendController.SaveSgfContent(sgfContent, backendDataWrapper);

      THEN( "The save operation succeeds and overwrites the string content with the SGF content" )
      {
        AssertSaveResult(backendSaveResult, sgfContent, expectedStringContentSaved);
      }
    }
  }
}

void AssertErrorLoadResultWhenNoValidSgfContent(
  std::shared_ptr<SgfcBackendLoadResult> loadResult)
{
  auto parseResult = loadResult->GetParseResult();
  REQUIRE( parseResult.size() == 1 );

  auto errorMessage = parseResult.front();
  REQUIRE( errorMessage->GetMessageType() == SgfcMessageType::FatalError );
  // 7 = SGFC error code "no SGF data found"
  REQUIRE( errorMessage->GetMessageID() == 7 );
  REQUIRE( errorMessage->GetMessageText().length() > 0 );
}

void AssertLoadResultWhenSgfDataHasNoWarningsOrErrors(
  std::shared_ptr<SgfcBackendLoadResult> loadResult,
  const std::string& sgfContent)
{
  auto parseResult = loadResult->GetParseResult();
  REQUIRE( parseResult.size() == 0 );

  auto sgfDataWrapper = loadResult->GetSgfDataWrapper();
  auto sgfData = sgfDataWrapper->GetSgfData();

  REQUIRE( sgfData->buffer != nullptr );
  // sgfData->buffer does not have a zero-byte terminator, we must provide
  // the buffer length
  REQUIRE( std::string(sgfData->buffer, sgfContent.size()) == sgfContent );
  REQUIRE( sgfData->b_end == sgfData->buffer + sgfContent.size() );
  // current must point to the end of the buffer because the buffer has
  // been parsed
  REQUIRE( sgfData->current == sgfData->b_end );
}

void AssertLoadResultWhenSgfDataHasWarningsOrErrors(
  std::shared_ptr<SgfcBackendLoadResult> loadResult1,
  std::shared_ptr<SgfcBackendLoadResult> loadResult2,
  std::shared_ptr<SgfcBackendLoadResult> loadResult3)
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

void AssertLoadResultWhenSgfDataHasCriticalError(
  std::shared_ptr<SgfcBackendLoadResult> loadResult)
{
  auto parseResult = loadResult->GetParseResult();
  REQUIRE( parseResult.size() == 2 );

  auto errorMessage1 = parseResult.front();
  REQUIRE( errorMessage1->GetMessageType() == SgfcMessageType::Error );
  // 46 = unknown file format
  REQUIRE( errorMessage1->GetMessageID() == 46 );
  REQUIRE( errorMessage1->IsCriticalMessage() == true );
  REQUIRE( errorMessage1->GetMessageText().length() > 0 );

  auto errorMessage2 = parseResult.back();
  REQUIRE( errorMessage2->GetMessageType() == SgfcMessageType::Warning );
  // 40 = property <%s> is not defined in FF[%d]
  REQUIRE( errorMessage2->GetMessageID() == 40 );
  REQUIRE( errorMessage2->IsCriticalMessage() == false );
  REQUIRE( errorMessage2->GetMessageText().length() > 0 );
}

void AssertSaveResult(
  std::shared_ptr<SgfcBackendSaveResult> backendSaveResult,
  const std::string& actualSgfContent,
  const std::string& expectedSgfContent)
{
  auto saveResult = backendSaveResult->GetSaveResult();
  REQUIRE( saveResult.size() == 0 );

  REQUIRE( actualSgfContent == expectedSgfContent );
}
