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
#include "ISgfcDocumentReadResult.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>
#include <string>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcArguments;

  /// @brief The ISgfcDocumentReader interface provides functions to generate
  /// ISgfcDocument objects by reading SGF data from the filesystem or from
  /// in-memory data. ISgfcDocumentReader operates the SGFC backend to achieve
  /// its task. Use SgfcPlusPlusFactory to construct new ISgfcDocumentReader
  /// objects.
  ///
  /// @ingroup public-api
  /// @ingroup sgfc-frontend
  /// @ingroup document
  class SGFCPLUSPLUS_EXPORT ISgfcDocumentReader
  {
  public:
    /// @brief Initializes a newly constructed ISgfcDocumentReader object.
    ISgfcDocumentReader();

    /// @brief Destroys and cleans up the ISgfcDocumentReader object.
    virtual ~ISgfcDocumentReader();

    /// @brief Returns an object with the collection of arguments that
    /// ISgfcDocumentReader passes on to SGFC whenever it performs a read
    /// operation.
    ///
    /// The collection of arguments is initially empty. Add arguments to the
    /// collection to change the way how SGFC reads SGF content. The collection
    /// retains its state between read operations so that repeated read
    /// operations use the same arguments.
    virtual std::shared_ptr<ISgfcArguments> GetArguments() const = 0;

    /// @brief Reads SGF data from a single .sgf file located at the specified
    /// path and puts the data through the SGFC parser, using the arguments that
    /// GetArguments() currently returns.
    ///
    /// @return An ISgfcDocumentReadResult object that provides the result of
    /// the read operation.
    virtual std::shared_ptr<ISgfcDocumentReadResult> ReadSgfFile(const std::string& sgfFilePath) const = 0;

    /// @brief Reads SGF data from the specified string and puts the data
    /// through the SGFC parser, using the arguments that GetArguments()
    /// currently returns.
    ///
    /// @return An ISgfcDocumentReadResult object that provides the result of
    /// the read operation.
    virtual std::shared_ptr<ISgfcDocumentReadResult> ReadSgfContent(const std::string& sgfContent) const = 0;
  };
}
