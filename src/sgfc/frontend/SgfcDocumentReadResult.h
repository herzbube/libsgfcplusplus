#pragma once

// Project includes
#include "../../../include/ISgfcDocumentReadResult.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDocumentReadResult class provides an implementation of the
  /// ISgfcDocumentReadResult interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-frontend
  /// @ingroup document
  class SgfcDocumentReadResult : public ISgfcDocumentReadResult
  {
  public:
    SgfcDocumentReadResult();
    SgfcDocumentReadResult(
      std::shared_ptr<ISgfcMessage> invalidCommandLineReason);
    SgfcDocumentReadResult(
      std::vector<std::shared_ptr<ISgfcMessage>> parseResult,
      std::shared_ptr<ISgfcDocument> document);
    virtual ~SgfcDocumentReadResult();

    virtual SgfcExitCode GetExitCode() const;
    virtual bool IsSgfDataValid() const;
    virtual std::vector<std::shared_ptr<ISgfcMessage>> GetParseResult() const;
    virtual std::shared_ptr<ISgfcDocument> GetDocument() const;
    virtual void DebugPrintToConsole() const;

  private:
    SgfcExitCode exitCode;
    bool isSgfDataValid;
    std::vector<std::shared_ptr<ISgfcMessage>> parseResult;
    std::shared_ptr<ISgfcDocument> document;
  };
}
