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
#include "../../../include/ISgfcDocumentReader.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDocumentReader class provides an implementation of the
  /// ISgfcDocumentReader interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-frontend
  /// @ingroup document
  class SgfcDocumentReader : public ISgfcDocumentReader
  {
  public:
    SgfcDocumentReader();
    virtual ~SgfcDocumentReader();

    virtual std::shared_ptr<ISgfcArguments> GetArguments() const;
    virtual std::shared_ptr<ISgfcDocumentReadResult> ReadSgfFile(const std::string& sgfFilePath);
    virtual std::shared_ptr<ISgfcDocumentReadResult> ReadSgfContent(const std::string& sgfContent);

  private:
    std::shared_ptr<ISgfcArguments> arguments;

    std::shared_ptr<ISgfcDocumentReadResult> ReadSgfContentFromFilesystemOrInMemoryBuffer(
      const std::string& sgfFilePath,
      const std::string& sgfContent,
      SgfcDataLocation dataLocation);
  };
}
