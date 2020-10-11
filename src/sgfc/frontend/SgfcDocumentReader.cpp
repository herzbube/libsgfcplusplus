// Project includes
#include "../../document/SgfcDocument.h"
#include "../../SgfcUtility.h"
#include "../argument/SgfcArguments.h"
#include "../backend/SgfcBackendController.h"
#include "SgfcDocumentReader.h"
#include "SgfcDocumentReadResult.h"

namespace LibSgfcPlusPlus
{
  SgfcDocumentReader::SgfcDocumentReader()
    : arguments(new SgfcArguments())
  {
  }

  SgfcDocumentReader::~SgfcDocumentReader()
  {
  }

  std::shared_ptr<ISgfcArguments> SgfcDocumentReader::GetArguments() const
  {
    return this->arguments;
  }

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::ReadSgfFile(const std::string& sgfFilePath)
  {
    std::string sgfContent;
    return ReadSgfContentFromFilesystemOrInMemoryBuffer(sgfFilePath, sgfContent, SgfcDataLocation::Filesystem);
  }

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::ReadSgfContent(const std::string& sgfContent)
  {
    std::string sgfFilePath;
    return ReadSgfContentFromFilesystemOrInMemoryBuffer(sgfFilePath, sgfContent, SgfcDataLocation::InMemoryBuffer);
  }

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::ReadSgfContentFromFilesystemOrInMemoryBuffer(
    const std::string& sgfFilePath,
    const std::string& sgfContent,
    SgfcDataLocation dataLocation)
  {
    SgfcBackendController backendController(this->arguments->GetArguments());
    if (backendController.IsCommandLineValid())
    {
      std::shared_ptr<SgfcBackendLoadResult> backendLoadResult;
      if (dataLocation == SgfcDataLocation::Filesystem)
        backendLoadResult = backendController.LoadSgfFile(sgfFilePath);
      else
        backendLoadResult = backendController.LoadSgfContent(sgfContent);

      SgfcExitCode sgfcExitCode = SgfcUtility::GetSgfcExitCodeFromMessageCollection(
        backendLoadResult->GetParseResult());

      std::shared_ptr<ISgfcDocument> document;
      if (sgfcExitCode != SgfcExitCode::FatalError)
        document = std::shared_ptr<ISgfcDocument>(new SgfcDocument(backendLoadResult->GetSgfDataWrapper()->GetSgfData()));
      else
        document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());

      std::shared_ptr<ISgfcDocumentReadResult> result = std::shared_ptr<ISgfcDocumentReadResult>(new SgfcDocumentReadResult(
        backendLoadResult->GetParseResult(),
        document));
      return result;
    }
    else
    {
      std::shared_ptr<ISgfcDocumentReadResult> result = std::shared_ptr<ISgfcDocumentReadResult>(new SgfcDocumentReadResult(
        backendController.GetInvalidCommandLineReason()));
      return result;
    }
  }
}
