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
  ///
  /// ISgfcDocumentReader invokes the SGFC backend's load/parse functions using
  /// the arguments that GetArguments() returns. If the library client does not
  /// do anything special, this is the default behaviour:
  /// - #SgfcArgumentType::EncodingMode 1 is used.
  /// - The first CA property value found in the SGF data determines the
  ///   encoding to use.
  /// - #SgfcArgumentType::DefaultEncoding ISO-8859-1 is used if there is no
  ///   CA property value.
  ///
  /// When #SgfcArgumentType::EncodingMode 1 or 2 are used the SGFC backend
  /// converts the SGF data it reads into memory to UTF-8. However, without
  /// further measures the document object tree would still contain whatever
  /// CA property values were found in the SGF data. If these values are not
  /// UTF-8 then the document object tree would now contain wrong information
  /// about the encoding used in-memory. This would be a problem if, for
  /// instance, the document object tree were passed to ISgfcDocumentWriter,
  /// because the writer would then use the wrong CA property values. To avoid
  /// this situation ISgfcDocumentReader performs the following manipulations
  /// of the document object tree after the read operation is complete:
  /// - If #SgfcArgumentType::EncodingMode 1 or 2 were used for reading
  ///   ISgfcDocumentReader writes the CA property value "UTF-8" into the root
  ///   node of each ISgfcGame it finds in the document. Only the root node
  ///   needs to be treated such because the CA property is a root property
  ///   which according to the SGF standard is only allowed in the root node.
  ///   Note that the SGFC backend deletes any CA properties that it finds
  ///   outside of a root node.
  /// - If #SgfcArgumentType::EncodingMode 3 was used for reading
  ///   ISgfcDocumentReader does not write a CA property value because the SGF
  ///   data was read into memory as-is.
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
    /// Read the class documentation for details about encodings.
    ///
    /// @return An ISgfcDocumentReadResult object that provides the result of
    /// the read operation.
    virtual std::shared_ptr<ISgfcDocumentReadResult> ReadSgfFile(const std::string& sgfFilePath) const = 0;

    /// @brief Reads SGF data from the specified string and puts the data
    /// through the SGFC parser, using the arguments that GetArguments()
    /// currently returns.
    ///
    /// Read the class documentation for details about encodings.
    ///
    /// @return An ISgfcDocumentReadResult object that provides the result of
    /// the read operation.
    virtual std::shared_ptr<ISgfcDocumentReadResult> ReadSgfContent(const std::string& sgfContent) const = 0;
  };
}
