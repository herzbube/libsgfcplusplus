#pragma once

// Project includes
#include "../../../include/ISgfcDocumentWriteResult.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDocumentWriteResult class provides an implementation of the
  /// ISgfcDocumentWriteResult interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-frontend
  /// @ingroup document
  class SgfcDocumentWriteResult : public ISgfcDocumentWriteResult
  {
  public:
    /// @brief Initializes a newly constructed SgfcDocumentWriteResult object
    /// that encapsulates a write operation result consisting of no messages,
    /// i.e. the write operation was successful.
    SgfcDocumentWriteResult();

    /// @brief Initializes a newly constructed SgfcDocumentWriteResult object
    /// that encapsulates a write operation result consisting of a single
    /// message @a invalidCommandLineReason.
    ///
    /// This constructor is intended to be used when the write operation failed
    /// due to invalid arguments passed to SGFC.
    SgfcDocumentWriteResult(
      std::shared_ptr<ISgfcMessage> invalidCommandLineReason);

    /// @brief Initializes a newly constructed SgfcDocumentWriteResult object
    /// that encapsulates a write operation result consisting of the collection
    /// of messages @a parseResult.
    ///
    /// This constructor is intended to be used when the arguments passed to
    /// SGFC were valid. The write operation may still have failed due to other
    /// reasons.
    SgfcDocumentWriteResult(
      std::vector<std::shared_ptr<ISgfcMessage>> parseResult);

    /// @brief Destroys and cleans up the SgfcDocumentReadResult object.
    virtual ~SgfcDocumentWriteResult();

    virtual SgfcExitCode GetExitCode() const;
    virtual std::vector<std::shared_ptr<ISgfcMessage>> GetParseResult() const;
    virtual void DebugPrintToConsole() const;

  private:
    SgfcExitCode exitCode;
    std::vector<std::shared_ptr<ISgfcMessage>> parseResult;
  };
}
