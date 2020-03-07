// Project includes
#include "../../document/SgfcDocument.h"
#include "SgfcDocumentWriter.h"
#include "SgfcDocumentWriteResult.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcDocumentWriter::SgfcDocumentWriter()
    : backendController(new SgfcBackendController())
  {
  }

  SgfcDocumentWriter::~SgfcDocumentWriter()
  {
  }

  std::shared_ptr<ISgfcDocumentWriteResult> SgfcDocumentWriter::WriteSgfFile(
    std::shared_ptr<ISgfcDocument> document,
    const std::string& sgfFilePath)
  {
    std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper =
      std::shared_ptr<SgfcBackendDataWrapper>(new SgfcBackendDataWrapper());

    // TODO: Populate sgfDataWrapper with data from document.

    std::shared_ptr<SgfcBackendSaveResult> backendSaveResult =
      this->backendController->SaveSgfFile(sgfFilePath, sgfDataWrapper);

    std::shared_ptr<ISgfcDocumentWriteResult> result = std::shared_ptr<ISgfcDocumentWriteResult>(new SgfcDocumentWriteResult(
      backendSaveResult->GetSaveResult()));
    return result;

  }

  std::shared_ptr<ISgfcDocumentWriteResult> SgfcDocumentWriter::WriteSgfContent(
    std::shared_ptr<ISgfcDocument> document,
    std::string& sgfContent)
  {
    throw std::runtime_error("not yet implemented");
  }
}
