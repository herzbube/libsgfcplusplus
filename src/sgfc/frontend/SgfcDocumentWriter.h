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

    virtual std::shared_ptr<ISgfcArguments> GetArguments() const override;
    virtual std::shared_ptr<ISgfcDocumentWriteResult> WriteSgfFile(
      std::shared_ptr<ISgfcDocument> document,
      const std::string& sgfFilePath) const override;
    virtual std::shared_ptr<ISgfcDocumentWriteResult> WriteSgfContent(
      std::shared_ptr<ISgfcDocument> document,
      std::string& sgfContent) const override;
    virtual std::shared_ptr<ISgfcDocumentWriteResult> ValidateDocument(
      std::shared_ptr<ISgfcDocument> document) const override;
    virtual void DebugPrintToConsole(
      std::shared_ptr<ISgfcDocument> document) const override;

  private:
    std::shared_ptr<ISgfcArguments> arguments;

    std::shared_ptr<ISgfcDocumentWriteResult> WriteSgfContentToFilesystemOrInMemoryBuffer(
      std::shared_ptr<ISgfcDocument> document,
      const std::string& sgfFilePath,
      std::string& sgfContent,
      SgfcDataLocation dataLocation) const;
  };
}
