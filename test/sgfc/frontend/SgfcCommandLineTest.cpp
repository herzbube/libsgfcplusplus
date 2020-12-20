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
#include <sgfc/frontend/SgfcCommandLine.h>
#include <SgfcConstants.h>
#include <SgfcUtility.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;


void AssertErrorLoadResultWhenNoValidSgfContent(const SgfcCommandLine& commandLine, SgfcExitCode sgfExitCode);
void AssertLoadResultWhenSgfDataHasNoWarningsOrErrors(const SgfcCommandLine& commandLine, SgfcExitCode sgfExitCode);
void AssertLoadResultWhenSgfDataHasWarningsOrErrors(const SgfcCommandLine& commandLine1, const SgfcCommandLine& commandLine2, const SgfcCommandLine& commandLine3, SgfcExitCode sgfExitCode1, SgfcExitCode sgfExitCode2, SgfcExitCode sgfExitCode3);
void AssertLoadResultWhenSgfDataHasCriticalError(const SgfcCommandLine& commandLine, SgfcExitCode sgfExitCode);
void AssertSaveResult(const SgfcCommandLine& commandLine, SgfcExitCode sgfExitCode, const std::string& actualSgfContent, const std::string& expectedSgfContent);


SCENARIO( "SgfcCommandLine is constructed", "[frontend]" )
{
  GIVEN( "The constructor that takes command line arguments is used" )
  {
    WHEN( "SgfcCommandLine is constructed with valid command line arguments" )
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
      SgfcCommandLine commandLine(expectedArguments);

      THEN( "SgfcCommandLine has the expected state" )
      {
        auto actualArguments = commandLine.GetArguments();
        REQUIRE( actualArguments == expectedArguments );

        REQUIRE( commandLine.IsCommandLineValid() == true );

        REQUIRE_THROWS_AS(
          commandLine.GetInvalidCommandLineReason(),
          std::logic_error);
      }
    }

    WHEN( "SgfcCommandLine is constructed with invalid command line arguments" )
    {
      struct TestData
      {
        std::vector<std::shared_ptr<ISgfcArgument>> CommandLineArguments;
        SgfcMessageID InvalidCommandLineReasonMessageID;
      };
      auto testData = GENERATE(
        TestData
        {
          std::vector<std::shared_ptr<ISgfcArgument>>
          {
            std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::HardLineBreakMode, 42))
          }, SgfcMessageID::BadCommandLineOptionParameter
        }
      );

      SgfcCommandLine commandLine(testData.CommandLineArguments);

      THEN( "SgfcCommandLine has the expected state" )
      {
        auto actualArguments = commandLine.GetArguments();
        REQUIRE( actualArguments == testData.CommandLineArguments );

        REQUIRE( commandLine.IsCommandLineValid() == false );

        auto invalidCommandLineReason = commandLine.GetInvalidCommandLineReason();
        REQUIRE( invalidCommandLineReason->GetMessageType() == SgfcMessageType::FatalError );
        REQUIRE( invalidCommandLineReason->GetMessageID() == testData.InvalidCommandLineReasonMessageID );
        REQUIRE( invalidCommandLineReason->GetMessageText().length() > 0 );
      }
    }
  }
}

SCENARIO( "SgfcCommandLine loads SGF content from the filesystem", "[frontend][filesystem]" )
{
  std::vector<std::shared_ptr<ISgfcArgument>> emptyCommandLineArguments;

  // Using a random UUID as the filename, it is reasonably safe to assume that
  // the file does not exist
  std::string tempFilePath = SgfcUtility::JoinPathComponents(
    SgfcUtility::GetTempFolderPath(),
    SgfcUtility::CreateUuid());

  GIVEN( "SgfcCommandLine was constructed with invalid command line arguments" )
  {
    std::vector<std::shared_ptr<ISgfcArgument>> invalidCommandLineArguments =
    {
      std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::HardLineBreakMode, 42))
    };
    SgfcCommandLine commandLine(invalidCommandLineArguments);

    WHEN( "SgfcCommandLine attempts to perform the load operation" )
    {
      THEN( "The load operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          commandLine.LoadSgfFile(tempFilePath),
          std::logic_error);
        REQUIRE_THROWS_AS(
          commandLine.IsSgfContentValid(),
          std::logic_error);
        REQUIRE_THROWS_AS(
          commandLine.GetParseResult(),
          std::logic_error);
      }
    }
  }

  GIVEN( "SgfcCommandLine did not perform a load operation" )
  {
    SgfcCommandLine commandLine(emptyCommandLineArguments);

    WHEN( "SgfcCommandLine checks the SGF content validity and the load operation's parse result" )
    {
      THEN( "The SGF content is invalid and the parse result is empty" )
      {
        REQUIRE( commandLine.IsSgfContentValid() == false );
        REQUIRE( commandLine.GetParseResult().size() == 0 );
      }
    }
  }

  GIVEN( "The file does not exist" )
  {
    WHEN( "SgfcCommandLine performs the load operation" )
    {
      SgfcCommandLine commandLine(emptyCommandLineArguments);
      SgfcExitCode sgfExitCode = commandLine.LoadSgfFile(tempFilePath);

      THEN( "The load operation result indicates failure" )
      {
        REQUIRE( sgfExitCode == SgfcExitCode::FatalError );
        REQUIRE( commandLine.IsSgfContentValid() == false );

        auto parseResult = commandLine.GetParseResult();
        REQUIRE( parseResult.size() == 1 );

        auto errorMessage = parseResult.front();
        REQUIRE( errorMessage->GetMessageType() == SgfcMessageType::FatalError );
        REQUIRE( errorMessage->GetMessageID() == SgfcMessageID::CouldNotOpenSourceFile );
        REQUIRE( errorMessage->GetMessageText().length() > 0 );
      }
    }
  }

  GIVEN( "The file exists but is not an .sgf file" )
  {
    std::string fileContent = GENERATE ( "", "foobar" );
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcCommandLine performs the load operation" )
    {
      SgfcCommandLine commandLine(emptyCommandLineArguments);
      SgfcExitCode sgfExitCode = commandLine.LoadSgfFile(tempFilePath);

      THEN( "The load operation result indicates failure" )
      {
        AssertErrorLoadResultWhenNoValidSgfContent(commandLine, sgfExitCode);
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  GIVEN( "The file exists and is an .sgf file without warnings or errors" )
  {
    std::string fileContent = GENERATE ( "(;)", "(;SZ[9]KM[6.5]B[aa])" );
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcCommandLine performs the load operation" )
    {
      SgfcCommandLine commandLine(emptyCommandLineArguments);
      SgfcExitCode sgfExitCode = commandLine.LoadSgfFile(tempFilePath);

      THEN( "The load operation result indicates success" )
      {
        AssertLoadResultWhenSgfDataHasNoWarningsOrErrors(commandLine, sgfExitCode);
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  GIVEN( "The file exists and is an .sgf file with warnings or errors" )
  {
    std::string fileContent = "(;C[])(;)";
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcCommandLine performs the load operation" )
    {
      std::vector<std::shared_ptr<ISgfcArgument>> commandLineArguments1 =
      {
        std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::EnableRestrictiveChecking))
      };
      std::vector<std::shared_ptr<ISgfcArgument>> commandLineArguments2 =
      {
        std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DisableWarningMessages))
      };
      SgfcCommandLine commandLine1(commandLineArguments1);
      SgfcCommandLine commandLine2(commandLineArguments2);
      SgfcCommandLine commandLine3(emptyCommandLineArguments);
      SgfcExitCode sgfExitCode1 = commandLine1.LoadSgfFile(tempFilePath);
      SgfcExitCode sgfExitCode2 = commandLine2.LoadSgfFile(tempFilePath);
      SgfcExitCode sgfExitCode3 = commandLine3.LoadSgfFile(tempFilePath);

      THEN( "The SGF content is valid and the exit code and parse result match the expected warnings and errors" )
      {
        AssertLoadResultWhenSgfDataHasWarningsOrErrors(commandLine1, commandLine2, commandLine3, sgfExitCode1, sgfExitCode2, sgfExitCode3);
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }

  GIVEN( "The file exists and is an .sgf file with a critical error" )
  {
    std::string fileContent = "(;FF[9])";
    SgfcUtility::AppendTextToFile(tempFilePath, fileContent);

    WHEN( "SgfcCommandLine performs the load operation" )
    {
      SgfcCommandLine commandLine(emptyCommandLineArguments);
      SgfcExitCode sgfExitCode = commandLine.LoadSgfFile(tempFilePath);

      THEN( "The loaded SGF content is valid and the exit code and parse result match the expected critical error" )
      {
        AssertLoadResultWhenSgfDataHasCriticalError(commandLine, sgfExitCode);
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePath);
  }
}

SCENARIO( "SgfcCommandLine loads SGF content from a string", "[frontend]" )
{
  std::vector<std::shared_ptr<ISgfcArgument>> emptyCommandLineArguments;

  GIVEN( "SgfcCommandLine was constructed with invalid command line arguments" )
  {
    std::vector<std::shared_ptr<ISgfcArgument>> invalidCommandLineArguments =
    {
      std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::HardLineBreakMode, 42))
    };
    SgfcCommandLine commandLine(invalidCommandLineArguments);

    WHEN( "SgfcCommandLine attempts to perform the load operation" )
    {
      THEN( "The load operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          commandLine.LoadSgfContent("(;)"),
          std::logic_error);
        REQUIRE_THROWS_AS(
          commandLine.IsSgfContentValid(),
          std::logic_error);
        REQUIRE_THROWS_AS(
          commandLine.GetParseResult(),
          std::logic_error);
      }
    }
  }

  GIVEN( "SgfcCommandLine did not perform a load operation" )
  {
    SgfcCommandLine commandLine(emptyCommandLineArguments);

    WHEN( "SgfcCommandLine checks the SGF content validity and the load operation's parse result" )
    {
      THEN( "The SGF content is invalid and the parse result is empty" )
      {
        REQUIRE( commandLine.IsSgfContentValid() == false );
        REQUIRE( commandLine.GetParseResult().size() == 0 );
      }
    }
  }

  GIVEN( "The string does not contain valid SGF data" )
  {
    std::string sgfContent = GENERATE ( "", "foobar" );

    WHEN( "SgfcCommandLine performs the load operation" )
    {
      SgfcCommandLine commandLine(emptyCommandLineArguments);
      SgfcExitCode sgfExitCode = commandLine.LoadSgfContent(sgfContent);

      THEN( "The load operation result indicates failure" )
      {
        AssertErrorLoadResultWhenNoValidSgfContent(commandLine, sgfExitCode);
      }
    }
  }

  GIVEN( "The string contains SGF data without warnings or errors" )
  {
    std::string sgfContent = GENERATE ( "(;)", "(;SZ[9]KM[6.5]B[aa])" );

    WHEN( "SgfcCommandLine performs the load operation" )
    {
      SgfcCommandLine commandLine(emptyCommandLineArguments);
      SgfcExitCode sgfExitCode = commandLine.LoadSgfContent(sgfContent);

      THEN( "The load operation result indicates success" )
      {
        AssertLoadResultWhenSgfDataHasNoWarningsOrErrors(commandLine, sgfExitCode);
      }
    }
  }

  GIVEN( "The string contains SGF data with warnings or errors" )
  {
    std::string sgfContent = "(;C[])(;)";

    WHEN( "SgfcCommandLine performs the load operation" )
    {
      std::vector<std::shared_ptr<ISgfcArgument>> commandLineArguments1 =
      {
        std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::EnableRestrictiveChecking))
      };
      std::vector<std::shared_ptr<ISgfcArgument>> commandLineArguments2 =
      {
        std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::DisableWarningMessages))
      };
      SgfcCommandLine commandLine1(commandLineArguments1);
      SgfcCommandLine commandLine2(commandLineArguments2);
      SgfcCommandLine commandLine3(emptyCommandLineArguments);
      SgfcExitCode sgfExitCode1 = commandLine1.LoadSgfContent(sgfContent);
      SgfcExitCode sgfExitCode2 = commandLine2.LoadSgfContent(sgfContent);
      SgfcExitCode sgfExitCode3 = commandLine3.LoadSgfContent(sgfContent);

      THEN( "The SGF content is valid and the exit code and parse result match the expected warnings and errors" )
      {
        AssertLoadResultWhenSgfDataHasWarningsOrErrors(commandLine1, commandLine2, commandLine3, sgfExitCode1, sgfExitCode2, sgfExitCode3);
      }
    }
  }

  GIVEN( "The string contains SGF data with a critical error" )
  {
    std::string sgfContent = "(;FF[9])";

    WHEN( "SgfcCommandLine performs the load operation" )
    {
      SgfcCommandLine commandLine(emptyCommandLineArguments);
      SgfcExitCode sgfExitCode = commandLine.LoadSgfContent(sgfContent);

      THEN( "The loaded SGF content is valid and the exit code and parse result match the expected critical error" )
      {
        AssertLoadResultWhenSgfDataHasCriticalError(commandLine, sgfExitCode);
      }
    }
  }
}

SCENARIO( "SgfcCommandLine saves SGF content to the filesystem", "[frontend][filesystem]" )
{
  std::vector<std::shared_ptr<ISgfcArgument>> emptyCommandLineArguments;

  // Using a random UUID as the filename, it is reasonably safe to assume that
  // the file does not exist
  std::string tempFilePathLoad = SgfcUtility::JoinPathComponents(
    SgfcUtility::GetTempFolderPath(),
    SgfcUtility::CreateUuid());
  std::string tempFilePathSave = SgfcUtility::JoinPathComponents(
    SgfcUtility::GetTempFolderPath(),
    SgfcUtility::CreateUuid());

  GIVEN( "SgfcCommandLine was constructed with invalid command line arguments" )
  {
    std::vector<std::shared_ptr<ISgfcArgument>> invalidCommandLineArguments =
    {
      std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::HardLineBreakMode, 42))
    };
    SgfcCommandLine commandLine(invalidCommandLineArguments);
    std::string sgfContent;

    WHEN( "SgfcCommandLine attempts to perform the save operation" )
    {
      THEN( "The save operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          commandLine.SaveSgfFile("foo.sgf"),
          std::logic_error);
        REQUIRE_THROWS_AS(
          commandLine.SaveSgfContent(sgfContent),
          std::logic_error);
        REQUIRE_THROWS_AS(
          commandLine.GetSaveResult(),
          std::logic_error);
      }
    }
  }

  GIVEN( "SgfcCommandLine did not perform a load operation" )
  {
    SgfcCommandLine commandLine(emptyCommandLineArguments);
    std::string sgfContent;

    WHEN( "SgfcCommandLine attempts to perform the save operation" )
    {
      THEN( "The save operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          commandLine.SaveSgfFile("foo.sgf"),
          std::logic_error);
        REQUIRE_THROWS_AS(
          commandLine.SaveSgfContent(sgfContent),
          std::logic_error);

        REQUIRE( commandLine.GetSaveResult().size() == 0 );
      }
    }
  }

  std::string fileContentToLoad = "(;)";
  std::string expectedFileContentSaved = "(;FF[4]CA[UTF-8]GM[1]SZ[19]AP[SGFC:" + SgfcConstants::SgfcVersion + "])\n";

  GIVEN( "The file does not exist" )
  {
    SgfcUtility::AppendTextToFile(tempFilePathLoad, fileContentToLoad);

    WHEN( "SgfcCommandLine performs the save operation" )
    {
      SgfcCommandLine commandLine(emptyCommandLineArguments);
      SgfcExitCode sgfExitCodeLoad = commandLine.LoadSgfFile(tempFilePathLoad);
      REQUIRE( sgfExitCodeLoad == SgfcExitCode::Ok );
      SgfcExitCode sgfExitCodeSave = commandLine.SaveSgfFile(tempFilePathSave);

      THEN( "The save operation succeeds" )
      {
        REQUIRE( sgfExitCodeSave == SgfcExitCode::Ok );

        auto saveResult = commandLine.GetSaveResult();
        REQUIRE( saveResult.size() == 0 );

        std::string fileContentSaved = SgfcUtility::ReadFileContent(tempFilePathSave);
        REQUIRE( fileContentSaved == expectedFileContentSaved );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePathLoad);
    SgfcUtility::DeleteFileIfExists(tempFilePathSave);
  }

  GIVEN( "The file already exists" )
  {
    SgfcUtility::AppendTextToFile(tempFilePathLoad, fileContentToLoad);

    WHEN( "SgfcCommandLine performs the save operation" )
    {
      SgfcUtility::AppendTextToFile(tempFilePathSave, "foo");

      SgfcCommandLine commandLine(emptyCommandLineArguments);
      SgfcExitCode sgfExitCodeLoad = commandLine.LoadSgfFile(tempFilePathLoad);
      REQUIRE( sgfExitCodeLoad == SgfcExitCode::Ok );
      SgfcExitCode sgfExitCodeSave = commandLine.SaveSgfFile(tempFilePathSave);

      THEN( "The save operation succeeds and overwrites the previous file content" )
      {
        REQUIRE( sgfExitCodeSave == SgfcExitCode::Ok );

        auto saveResult = commandLine.GetSaveResult();
        REQUIRE( saveResult.size() == 0 );

        std::string fileContentSaved = SgfcUtility::ReadFileContent(tempFilePathSave);
        REQUIRE( fileContentSaved == expectedFileContentSaved );
      }
    }

    SgfcUtility::DeleteFileIfExists(tempFilePathLoad);
    SgfcUtility::DeleteFileIfExists(tempFilePathSave);
  }

  // We would like to write more tests to verify that the save operations can
  // return an SgfExitCode that maps to a warning, error or fatal error.
  // Currently there are no known SGF contents where SGFC generates a warning
  // or error message during save, and fatal errors are all tied to filesystem
  // problems that are difficult to simulate in a test.
}

SCENARIO( "SgfcCommandLine saves SGF content to a string", "[frontend]" )
{
  std::vector<std::shared_ptr<ISgfcArgument>> emptyCommandLineArguments;
  std::string sgfContent;

  GIVEN( "SgfcCommandLine was constructed with invalid command line arguments" )
  {
    std::vector<std::shared_ptr<ISgfcArgument>> invalidCommandLineArguments =
    {
      std::shared_ptr<ISgfcArgument>(new SgfcArgument(SgfcArgumentType::HardLineBreakMode, 42))
    };
    SgfcCommandLine commandLine(invalidCommandLineArguments);

    WHEN( "SgfcCommandLine attempts to perform the save operation" )
    {
      THEN( "The save operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          commandLine.SaveSgfContent(sgfContent),
          std::logic_error);
        REQUIRE_THROWS_AS(
          commandLine.GetSaveResult(),
          std::logic_error);
      }
    }
  }

  GIVEN( "SgfcCommandLine did not perform a load operation" )
  {
    SgfcCommandLine commandLine(emptyCommandLineArguments);

    WHEN( "SgfcCommandLine attempts to perform the save operation" )
    {
      THEN( "The save operation throws an exception" )
      {
        REQUIRE_THROWS_AS(
          commandLine.SaveSgfContent(sgfContent),
          std::logic_error);

        REQUIRE( commandLine.GetSaveResult().size() == 0 );
      }
    }
  }

  std::string sgfContentToLoad = "(;)";
  std::string expectedStringContentSaved = "(;FF[4]CA[UTF-8]GM[1]SZ[19]AP[SGFC:" + SgfcConstants::SgfcVersion + "])\n";

  GIVEN( "The string is empty" )
  {
    WHEN( "SgfcCommandLine performs the save operation" )
    {
      SgfcCommandLine commandLine(emptyCommandLineArguments);
      SgfcExitCode sgfExitCodeLoad = commandLine.LoadSgfContent(sgfContentToLoad);
      REQUIRE( sgfExitCodeLoad == SgfcExitCode::Ok );
      SgfcExitCode sgfcExitCode = commandLine.SaveSgfContent(sgfContent);

      THEN( "The save operation succeeds and writes the SGF content into the string" )
      {
        AssertSaveResult(commandLine, sgfcExitCode, sgfContent, expectedStringContentSaved);
      }
    }
  }

  GIVEN( "The string is not empty" )
  {
    WHEN( "SgfcCommandLine performs the save operation" )
    {
      sgfContent = "foo";

      SgfcCommandLine commandLine(emptyCommandLineArguments);
      SgfcExitCode sgfExitCodeLoad = commandLine.LoadSgfContent(sgfContentToLoad);
      REQUIRE( sgfExitCodeLoad == SgfcExitCode::Ok );
      SgfcExitCode sgfcExitCode = commandLine.SaveSgfContent(sgfContent);

      THEN( "The save operation succeeds and overwrites the string content with the SGF content" )
      {
        AssertSaveResult(commandLine, sgfcExitCode, sgfContent, expectedStringContentSaved);
      }
    }
  }
}

void AssertErrorLoadResultWhenNoValidSgfContent(const SgfcCommandLine& commandLine, SgfcExitCode sgfExitCode)
{
  REQUIRE( sgfExitCode == SgfcExitCode::FatalError );
  REQUIRE( commandLine.IsSgfContentValid() == false );

  auto parseResult = commandLine.GetParseResult();
  REQUIRE( parseResult.size() == 1 );

  auto errorMessage = parseResult.front();
  REQUIRE( errorMessage->GetMessageType() == SgfcMessageType::FatalError );
  REQUIRE( errorMessage->GetMessageID() == SgfcMessageID::NoSgfData );
  REQUIRE( errorMessage->GetMessageText().length() > 0 );
}

void AssertLoadResultWhenSgfDataHasNoWarningsOrErrors(
  const SgfcCommandLine& commandLine,
  SgfcExitCode sgfExitCode)
{
  REQUIRE( sgfExitCode == SgfcExitCode::Ok );
  REQUIRE( commandLine.IsSgfContentValid() == true );

  auto parseResult = commandLine.GetParseResult();
  REQUIRE( parseResult.size() == 0 );
}

void AssertLoadResultWhenSgfDataHasWarningsOrErrors(
  const SgfcCommandLine& commandLine1,
  const SgfcCommandLine& commandLine2,
  const SgfcCommandLine& commandLine3,
  SgfcExitCode sgfExitCode1,
  SgfcExitCode sgfExitCode2,
  SgfcExitCode sgfExitCode3)
{
  // This part of the test verifies that message types are correctly
  // mapped to exit codes. FatalError is verified in a different test.
  REQUIRE( sgfExitCode1 == SgfcExitCode::Error );
  REQUIRE( sgfExitCode2 == SgfcExitCode::Ok );
  REQUIRE( sgfExitCode3 == SgfcExitCode::Warning );

  REQUIRE( commandLine1.IsSgfContentValid() == true );
  REQUIRE( commandLine2.IsSgfContentValid() == true );
  REQUIRE( commandLine3.IsSgfContentValid() == true );

  auto parseResult1 = commandLine1.GetParseResult();
  auto parseResult2 = commandLine2.GetParseResult();
  auto parseResult3 = commandLine3.GetParseResult();
  REQUIRE( parseResult1.size() == 2 );
  REQUIRE( parseResult2.size() == 0 );
  REQUIRE( parseResult3.size() == 1 );

  auto errorMessage1a = parseResult1.front();
  auto errorMessage1b = parseResult1.back();
  auto errorMessage3 = parseResult3.front();

  REQUIRE( errorMessage1a->GetMessageType() == SgfcMessageType::Warning );
  REQUIRE( errorMessage1b->GetMessageType() == SgfcMessageType::Error );
  REQUIRE( errorMessage3->GetMessageType() == SgfcMessageType::Warning );
  REQUIRE( errorMessage1a->GetMessageID() == SgfcMessageID::EmptyValueDeleted );
  REQUIRE( errorMessage3->GetMessageID() == SgfcMessageID::EmptyValueDeleted );
  REQUIRE( errorMessage1b->GetMessageID() == SgfcMessageID::MoreThanOneGameTree );
}

void AssertLoadResultWhenSgfDataHasCriticalError(
  const SgfcCommandLine& commandLine,
  SgfcExitCode sgfExitCode)
{
  REQUIRE( sgfExitCode == SgfcExitCode::Error );
  REQUIRE( commandLine.IsSgfContentValid() == true );

  auto parseResult = commandLine.GetParseResult();
  REQUIRE( parseResult.size() == 1 );

  auto errorMessage1 = parseResult.front();
  REQUIRE( errorMessage1->GetMessageType() == SgfcMessageType::Error );
  REQUIRE( errorMessage1->GetMessageID() == SgfcMessageID::UnknownFileFormat );
  REQUIRE( errorMessage1->IsCriticalMessage() == true );
  REQUIRE( errorMessage1->GetMessageText().length() > 0 );
}

void AssertSaveResult(
  const SgfcCommandLine& commandLine,
  SgfcExitCode sgfExitCode,
  const std::string& actualSgfContent,
  const std::string& expectedSgfContent)
{
  REQUIRE( sgfExitCode == SgfcExitCode::Ok );
  REQUIRE( commandLine.GetSaveResult().size() == 0 );
  REQUIRE( actualSgfContent == expectedSgfContent );
}
