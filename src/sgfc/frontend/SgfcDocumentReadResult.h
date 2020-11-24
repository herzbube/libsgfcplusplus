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

    virtual SgfcExitCode GetExitCode() const override;
    virtual bool IsSgfDataValid() const override;
    virtual std::vector<std::shared_ptr<ISgfcMessage>> GetParseResult() const override;
    virtual std::shared_ptr<ISgfcDocument> GetDocument() const override;
    virtual void DebugPrintToConsole() const override;

  private:
    SgfcExitCode exitCode;
    bool isSgfDataValid;
    std::vector<std::shared_ptr<ISgfcMessage>> parseResult;
    std::shared_ptr<ISgfcDocument> document;
  };
}
