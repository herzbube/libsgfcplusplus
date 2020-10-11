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
#include <ISgfcArguments.h>
#include <ISgfcCommandLine.h>
#include <ISgfcDocumentReader.h>
#include <ISgfcDocumentWriter.h>
#include <ISgfcDocumentWriteResult.h>
#include <ISgfcGame.h>
#include <ISgfcMovePropertyValue.h>
#include <ISgfcNumberPropertyValue.h>
#include <ISgfcPropertyFactory.h>
#include <ISgfcPropertyValueFactory.h>
#include <ISgfcTreeBuilder.h>
#include <SgfcPlusPlusFactory.h>

// C++ Standard Library includes
#include <iostream>

using namespace LibSgfcPlusPlus;

/// @brief Prints the raw message text of all ISgfcMessage objects in the
/// supplied collection to standard output.
///
/// This is a helper function.
void PrintMessages(const std::vector<std::shared_ptr<ISgfcMessage>>& messages)
{
  int numberOfMessages = 0;
  for (const auto& message : messages)
  {
    numberOfMessages++;
    std::cout << "  " << message->GetRawMessageText() << std::endl;
  }
  if (numberOfMessages == 0)
  {
    std::cout << "  No messages." << std::endl;
  }
  std::cout << std::endl;
}

/// @brief Reads the SGF file @a inputFilePath. If @a doSave is true also saves
/// the SGF content back to @a outputFilePath.
///
/// This demonstrates the usage of ISgfcCommandLine.
int DoCommandLine(const std::string& inputFilePath, bool doSave, const std::string& outputFilePath)
{
  auto arguments = SgfcPlusPlusFactory::CreateSgfcArguments();

  // Uncomment the following to see an invalid command line
//  arguments->AddArgument(SgfcArgumentType::DeletePropertyType, SgfcPropertyType::BO);

  std::shared_ptr<ISgfcCommandLine> cmdline = SgfcPlusPlusFactory::CreateSgfcCommandLine(arguments);
  if (cmdline->IsCommandLineValid())
  {
    std::cout << "Command line arguments are valid" << std::endl;
  }
  else
  {
    std::cout << "Command line arguments are NOT valid" << std::endl;
    std::shared_ptr<ISgfcMessage> reason = cmdline->GetInvalidCommandLineReason();
    std::cout << "The reason is: " << reason->GetRawMessageText() << std::endl;
    return 0;
  }

  std::cout << std::endl;

  SgfcExitCode sgfcExitCodeLoadSgfFile = cmdline->LoadSgfFile(inputFilePath);
  std::cout << "LoadSgfFile sgfcExitCode = " << static_cast<int>(sgfcExitCodeLoadSgfFile) << std::endl;

  std::cout << "LoadSgfFile messages" << std::endl;
  std::vector<std::shared_ptr<ISgfcMessage>> parseResult = cmdline->GetParseResult();
  PrintMessages(parseResult);

  if (doSave)
  {
    if (cmdline->IsSgfContentValid())
    {
      std::cout << "SGF content is valid, saving file ..." << std::endl;

      SgfcExitCode sgfcExitCodeSaveSgfFile = cmdline->SaveSgfFile(outputFilePath);
      std::cout << "SaveSgfFile sgfcExitCode = " << static_cast<int>(sgfcExitCodeSaveSgfFile) << std::endl;

      std::cout << "SaveSgfFile messages" << std::endl;
      std::vector<std::shared_ptr<ISgfcMessage>> saveResult = cmdline->GetSaveResult();
      PrintMessages(saveResult);
    }
    else
    {
      std::cout << "SGF content is NOT valid, not saving file" << std::endl;
    }
  }

  return 0;
}

/// @brief Reads the SGF file @a inputFilePath.
///
/// This demonstrates the usage of ISgfcCommandLine.
int DoCommandLine(const std::string& inputFilePath)
{
  bool doSave = false;
  std::string outputFilePath;
  return DoCommandLine(inputFilePath, doSave, outputFilePath);
}

/// @brief Reads the SGF file @a inputFilePath and saves the SGF content back
/// to @a outputFilePath.
///
/// This demonstrates the usage of ISgfcCommandLine.
int DoCommandLine(const std::string& inputFilePath, const std::string& outputFilePath)
{
  bool doSave = true;
  return DoCommandLine(inputFilePath, doSave, outputFilePath);
}

/// @brief Prints the content of @a document to standard output.
///
/// This is a helper function.
void PrintDocumentContent(std::shared_ptr<ISgfcDocument> document)
{
  std::cout << "Printing document content..." << std::endl;

  if (document->IsEmpty())
    std::cout << "  Document is empty" << std::endl;
  else
    document->DebugPrintToConsole();

  std::cout << std::endl;
}

/// @brief Reads the SGF file @a inputFilePath. If @a printOutput is true also
/// prints the document content to standard output.
///
/// This demonstrates the usage of ISgfcDocumentReader.
std::shared_ptr<ISgfcDocument> ReadDocument(const std::string& inputFilePath, bool printOutput)
{
  std::shared_ptr<ISgfcDocumentReader> documentReader = SgfcPlusPlusFactory::CreateDocumentReader();

  // Uncomment the following to see an invalid command line
//  documentReader->GetArguments()->AddArgument(SgfcArgumentType::DeletePropertyType, SgfcPropertyType::BO);

  std::shared_ptr<ISgfcDocumentReadResult> result = documentReader->ReadSgfFile(inputFilePath);

  if (printOutput)
  {
    std::cout << "ReadSgfFile sgfcExitCode = " << static_cast<int>(result->GetExitCode()) << std::endl;
    std::cout << "IsSgfDataValid = " << result->IsSgfDataValid() << std::endl;
    std::cout << std::endl;

    std::cout << "Printing parse results..." << std::endl;
    PrintMessages(result->GetParseResult());

    if (result->GetExitCode() != SgfcExitCode::FatalError)
      PrintDocumentContent(result->GetDocument());
  }

  return result->GetDocument();
}

/// @brief Reads the SGF file @a inputFilePath.
///
/// This demonstrates the usage of ISgfcDocumentReader.
int DoDocumentRead(const std::string& inputFilePath)
{
  bool printOutput = true;
  ReadDocument(inputFilePath, printOutput);

  return 0;
}

/// @brief Writes the content of @a document to the SGF file @a outputFilePath.
///
/// This demonstrates the usage of ISgfcDocumentWriter.
int WriteDocument(std::shared_ptr<ISgfcDocument> document, const std::string& outputFilePath)
{
  std::shared_ptr<ISgfcDocumentWriter> documentWriter = SgfcPlusPlusFactory::CreateDocumentWriter();

  // Uncomment the following to see an invalid command line
//  documentWriter->GetArguments()->AddArgument(SgfcArgumentType::DeletePropertyType, SgfcPropertyType::BO);

  std::shared_ptr<ISgfcDocumentWriteResult> result = documentWriter->WriteSgfFile(document, outputFilePath);

  std::cout << "WriteSgfFile sgfcExitCode = " << static_cast<int>(result->GetExitCode()) << std::endl;
  std::cout << std::endl;

  std::cout << "Printing write results..." << std::endl;
  PrintMessages(result->GetParseResult());

  if (result->GetExitCode() != SgfcExitCode::FatalError)
  {
    std::cout << "Printing encoded SGF content..." << std::endl;
    documentWriter->DebugPrintToConsole(document);
  }

  return 0;
}

/// @brief Reads the SGF file @a inputFilePath into a document and saves the
/// document content back to @a outputFilePath.
///
/// This demonstrates the usage of ISgfcDocumentReader and ISgfcDocumentWriter.
int DoDocumentWrite(const std::string& inputFilePath, const std::string& outputFilePath)
{
  bool printOutput = false;
  std::shared_ptr<ISgfcDocument> document = ReadDocument(inputFilePath, printOutput);

  return WriteDocument(document, outputFilePath);
}

/// @brief Programmatically builds a game tree and then writes the content
/// of the resulting document to the SGF file @a outputFilePath.
///
/// This demonstrates the usage of the various factories and of
/// ISgfcDocumentWriter.
int DoBuildTree(const std::string& outputFilePath)
{
  std::shared_ptr<ISgfcNode> rootNode = SgfcPlusPlusFactory::CreateNode();
  std::shared_ptr<ISgfcGame> game = SgfcPlusPlusFactory::CreateGame(rootNode);
  std::shared_ptr<ISgfcDocument> document = SgfcPlusPlusFactory::CreateDocument(game);

  std::shared_ptr<ISgfcNode> nodeA = SgfcPlusPlusFactory::CreateNode();
  std::shared_ptr<ISgfcNode> nodeA1 = SgfcPlusPlusFactory::CreateNode();
  std::shared_ptr<ISgfcNode> nodeA2 = SgfcPlusPlusFactory::CreateNode();
  std::shared_ptr<ISgfcNode> nodeB = SgfcPlusPlusFactory::CreateNode();
  std::shared_ptr<ISgfcNode> nodeB1 = SgfcPlusPlusFactory::CreateNode();
  std::shared_ptr<ISgfcNode> nodeC = SgfcPlusPlusFactory::CreateNode();
  std::shared_ptr<ISgfcNode> nodeC1 = SgfcPlusPlusFactory::CreateNode();
  std::shared_ptr<ISgfcNode> nodeC2 = SgfcPlusPlusFactory::CreateNode();
  std::shared_ptr<ISgfcNode> nodeC3 = SgfcPlusPlusFactory::CreateNode();

  auto builder = game->GetTreeBuilder();
  builder->AppendChild(rootNode, nodeA);
  builder->AppendChild(rootNode, nodeB);
  builder->AppendChild(rootNode, nodeC);
  builder->AppendChild(nodeA, nodeA1);
  builder->AppendChild(nodeA, nodeA2);
  builder->AppendChild(nodeB, nodeB1);
  builder->AppendChild(nodeC, nodeC1);
  builder->AppendChild(nodeC, nodeC2);
  builder->AppendChild(nodeC, nodeC3);

  auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();
  auto propertyValueGM = propertyValueFactory->CreateNumberPropertyValue(1);
  auto propertyValueSZ = propertyValueFactory->CreateNumberPropertyValue(19);
  auto propertyValueMove1 = propertyValueFactory->CreateMovePropertyValue("aa");
  auto propertyValueMove2 = propertyValueFactory->CreateMovePropertyValue("bb");

  auto propertyValueSimpleText = propertyValueFactory->CreateSimpleTextPropertyValue("kk ] ");
  auto propertyValuePoint1 = propertyValueFactory->CreatePointPropertyValue("aa");
  auto propertyValuePoint2 = propertyValueFactory->CreatePointPropertyValue("ab");
  auto propertyValuePoint3 = propertyValueFactory->CreatePointPropertyValue("ba");
  auto propertyValuePoint4 = propertyValueFactory->CreatePointPropertyValue("bb");
  auto propertyValuePoint5 = propertyValueFactory->CreatePointPropertyValue("ac");

  auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
  std::shared_ptr<ISgfcProperty> propertyGM = propertyFactory->CreateProperty(SgfcPropertyType::GM, propertyValueGM);
  std::shared_ptr<ISgfcProperty> propertySZ = propertyFactory->CreateProperty(SgfcPropertyType::SZ, propertyValueSZ);
  std::shared_ptr<ISgfcProperty> propertyB = propertyFactory->CreateProperty(SgfcPropertyType::B, propertyValueMove1);
  std::shared_ptr<ISgfcProperty> propertyW = propertyFactory->CreateProperty(SgfcPropertyType::W, propertyValueMove2);

  rootNode->SetProperties(std::vector<std::shared_ptr<ISgfcProperty>> { propertyGM, propertySZ });
  nodeA->SetProperties(std::vector<std::shared_ptr<ISgfcProperty>> { propertyB });
  nodeA1->SetProperties(std::vector<std::shared_ptr<ISgfcProperty>> { propertyW });

  PrintDocumentContent(document);

  return WriteDocument(document, outputFilePath);
}

/// @brief Prints the command line usage of the example program to standard
/// output.
void PrintUsage(const std::string& programName)
{
  std::cout << "Usage:" << std::endl;
  std::cout << "  " << programName << " cmdline   input-file [output-file]" << std::endl;
  std::cout << "  " << programName << " docread   input-file" << std::endl;
  std::cout << "  " << programName << " docwrite  input-file output-file" << std::endl;
  std::cout << "  " << programName << " buildtree output-file" << std::endl;
}

/// @brief Prints an error message and the command line usage of the example
/// program to standard output.
void PrintMissingModeAndFileParameters(const std::string& programName)
{
  std::cout << "Missing mode and file parameters" << std::endl;
  PrintUsage(programName);
}

/// @brief Prints an error message and the command line usage of the example
/// program to standard output.
void PrintMissingFileParameter(const std::string& programName)
{
  std::cout << "Missing file parameter" << std::endl;
  PrintUsage(programName);
}

/// @brief Prints an error message and the command line usage of the example
/// program to standard output.
void PrintTooManyParameters(const std::string& programName)
{
  std::cout << "Too many parameters" << std::endl;
  PrintUsage(programName);
}

/// @brief Prints an error message and the command line usage of the example
/// program to standard output.
void PrintMissingOutputFileParameter(const std::string& programName)
{
  std::cout << "Missing output file parameter" << std::endl;
  PrintUsage(programName);
}

/// @brief Prints an error message and the command line usage of the example
/// program to standard output.
void PrintUnknownMode(const std::string& programName, const std::string& mode)
{
  std::cout << "Unknown mode: " << mode << std::endl;
  PrintUsage(programName);
}

/// @brief The main routine of the example program.
int main(int argc, char** argv)
{
  std::string programName = argv[0];

  switch (argc)
  {
    case 0:
    case 1:
      PrintMissingModeAndFileParameters(programName);
      return 1;
    case 2:
      PrintMissingFileParameter(programName);
      return 1;
    case 3:
    case 4:
      break;
    default:
      PrintTooManyParameters(programName);
      return 1;
  }

  std::string mode = argv[1];

  int exitCode;
  if (mode == "cmdline")
  {
    std::string inputFilePath = argv[2];
    if (argc == 3)
    {
      exitCode = DoCommandLine(inputFilePath);
    }
    else if (argc == 4)
    {
      bool doSave = true;
      std::string outputFilePath = argv[3];
      exitCode = DoCommandLine(inputFilePath, doSave, outputFilePath);
    }
    else
    {
      PrintTooManyParameters(programName);
      exitCode = 1;
    }
  }
  else if (mode == "docread")
  {
    if (argc == 3)
    {
      std::string inputFilePath = argv[2];
      exitCode = DoDocumentRead(inputFilePath);
    }
    else if (argc == 4)
    {
      PrintTooManyParameters(programName);
      exitCode = 1;
    }
  }
  else if (mode == "docwrite")
  {
      if (argc == 3)
      {
        PrintMissingOutputFileParameter(programName);
      }
      else if (argc == 4)
      {
        std::string inputFilePath = argv[2];
        std::string outputFilePath = argv[3];
        exitCode = DoDocumentWrite(inputFilePath, outputFilePath);
      }
      else
      {
        PrintTooManyParameters(programName);
        exitCode = 1;
      }
  }
  else if (mode == "buildtree")
  {
    if (argc == 3)
    {
      std::string outputFilePath = argv[2];
      exitCode = DoBuildTree(outputFilePath);
    }
    else if (argc == 4)
    {
      PrintTooManyParameters(programName);
      exitCode = 1;
    }
  }
  else
  {
    PrintUnknownMode(programName, mode);
    exitCode = 1;
  }

  return exitCode;
}
