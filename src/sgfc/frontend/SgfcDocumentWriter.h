#pragma once

// Project includes
#include "../../../include/ISgfcDocumentWriter.h"
#include "../backend/SgfcBackendController.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDocumentWriter class provides an implementation of the
  /// ISgfcDocumentWriter interface. See the interface header file for
  /// documentation.
  class SgfcDocumentWriter : public ISgfcDocumentWriter
  {
  public:
    SgfcDocumentWriter();
    virtual ~SgfcDocumentWriter();

    virtual std::shared_ptr<ISgfcDocumentWriteResult> WriteSgfFile(
      std::shared_ptr<ISgfcDocument> document,
      const std::string& sgfFilePath);
    virtual std::shared_ptr<ISgfcDocumentWriteResult> WriteSgfContent(
      std::shared_ptr<ISgfcDocument> document,
      std::string& sgfContent);
    virtual void DebugPrintToConsole(
      std::shared_ptr<ISgfcDocument> document) const;

  private:
    std::shared_ptr<SgfcBackendController> backendController;

    std::shared_ptr<ISgfcDocumentWriteResult> DeleteTempFileOrCreateWriteResultWithErrorMessage(
      const std::string& tempFilePath) const;
    std::shared_ptr<ISgfcDocumentWriteResult> CreateWriteResultWithErrorMessage(
      int messageID,
      const std::string& messageText) const;
  };
}
