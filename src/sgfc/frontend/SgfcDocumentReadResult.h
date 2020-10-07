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
    /// @brief Initializes a newly constructed SgfcDocumentReadResult object
    /// that encapsulates a read operation result consisting of a single message
    /// @a invalidCommandLineReason and an empty document.
    ///
    /// This constructor is intended to be used when the read operation failed
    /// due to invalid arguments passed to SGFC.
    SgfcDocumentReadResult(
      std::shared_ptr<ISgfcMessage> invalidCommandLineReason);

    /// @brief Initializes a newly constructed SgfcDocumentReadResult object
    /// that encapsulates a read operation result consisting of the collection
    /// of messages @a parseResult and the document @a document.
    ///
    /// This constructor is intended to be used when the arguments passed to
    /// SGFC were valid. The read operation may still have failed due to other
    /// reasons.
    SgfcDocumentReadResult(
      std::vector<std::shared_ptr<ISgfcMessage>> parseResult,
      std::shared_ptr<ISgfcDocument> document);

    /// @brief Destroys and cleans up the SgfcDocumentReadResult object.
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
