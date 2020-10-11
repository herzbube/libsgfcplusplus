#pragma once

// Project includes
#include "../backend/SgfcDataLocation.h"
#include "../../../include/ISgfcDocumentWriter.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDocumentWriter class provides an implementation of the
  /// ISgfcDocumentWriter interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-frontend
  /// @ingroup document
  class SgfcDocumentWriter : public ISgfcDocumentWriter
  {
  public:
    SgfcDocumentWriter();
    virtual ~SgfcDocumentWriter();

    virtual std::shared_ptr<ISgfcArguments> GetArguments() const;
    virtual std::shared_ptr<ISgfcDocumentWriteResult> WriteSgfFile(
      std::shared_ptr<ISgfcDocument> document,
      const std::string& sgfFilePath);
    virtual std::shared_ptr<ISgfcDocumentWriteResult> WriteSgfContent(
      std::shared_ptr<ISgfcDocument> document,
      std::string& sgfContent);
    virtual void DebugPrintToConsole(
      std::shared_ptr<ISgfcDocument> document) const;

  private:
    std::shared_ptr<ISgfcArguments> arguments;

    std::shared_ptr<ISgfcDocumentWriteResult> WriteSgfContentToFilesystemOrInMemoryBuffer(
      std::shared_ptr<ISgfcDocument> document,
      const std::string& sgfFilePath,
      std::string& sgfContent,
      SgfcDataLocation dataLocation);
  };
}
