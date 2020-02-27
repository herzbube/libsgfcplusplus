// Project includes
#include "../../document/SgfcDocument.h"
#include "../../SgfcUtility.h"
#include "SgfcDocumentReader.h"
#include "SgfcDocumentReadResult.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcDocumentReader::SgfcDocumentReader()
    : backendController(new SgfcBackendController())
  {
  }

  SgfcDocumentReader::~SgfcDocumentReader()
  {
  }

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::ReadSgfFile(const std::string& sgfFilePath)
  {
    std::shared_ptr<SgfcBackendLoadResult> backendLoadResult = this->backendController->LoadSgfFile(sgfFilePath);

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

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::ReadSgfContent(const std::string& sgfContent)
  {
    throw std::runtime_error("not yet implemented");
  }
}
