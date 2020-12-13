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

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>
#include <string>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcArguments;
  class ISgfcDocument;
  class ISgfcDocumentWriteResult;

  /// @brief The ISgfcDocumentWriter interface provides functions to generate
  /// SGF data from ISgfcDocument objects and to either write that data to the
  /// filesystem or make it available as an in-memory string.
  /// ISgfcDocumentWriter operates the SGFC backend to achieve its task. Use
  /// SgfcPlusPlusFactory to construct new ISgfcDocumentWriter objects.
  ///
  /// @ingroup public-api
  /// @ingroup sgfc-frontend
  /// @ingroup document
  ///
  /// Before ISgfcDocumentWriter can invoke the SGFC backend's write function
  /// it generates SGF data from the ISgfcDocument whose content should be
  /// written, then passes the SGF data through the SGFC backend's load/parse
  /// functions for data validation. For this to work ISgfcDocumentWriter has
  /// to perform escaping of characters in the SGF data that are also used for
  /// the SGF skeleton. See the SGF specification if you don't know what
  /// "escaping" is about.
  ///
  /// As the SGF skeleton is made up of ASCII characters only, the characters
  /// that require escaping are all ASCII characters. But the SGF standard
  /// allows SgfcSimpleText and SgfcText property values to have a non-ASCII
  /// character encoding. ISgfcDocumentWriter doesn't care about the actual
  /// character encoding that is in use, it simply scans property values for
  /// characters to escape on the byte level. This means that the character
  /// encoding used for property values of type SgfcSimpleText and SgfcText
  /// must be a character encoding that is "ASCII-safe".
  ///
  /// ASCII-safe means:
  /// - The character encoding must encode ASCII characters with their single
  ///   byte values from the ASCII table; and
  /// - The character encoding must not use the byte values of ASCII characters
  ///   to encode anything else but ASCII characters.
  ///
  /// For instance, the ASCII character "]" has the hex value 0x5d in the ASCII
  /// table. The character encoding must therefore use 0x5d to encode the
  /// character "]", and it must guarantee that, regardless of what else is
  /// encoded, the value 0x5d does not appear anywhere in the encoded byte
  /// stream except to encode the character "]".
  ///
  /// Single-byte character encodings such as the ISO-8859 family usually are
  /// ASCII-safe because they have been designed like that. Multi-byte
  /// encodings, however, should not be considered ASCII-safe unless they are
  /// known to be. Big5 and Shift_JIS are notable examples that are @b not
  /// ASCII-safe - see SgfNotes.md for concrete details. UTF-8 is a notable
  /// example that @b is ASCII-safe.
  ///
  /// As already mentioned ISgfcDocumentWriter passes the SGF data it has
  /// generated and escaped to the SGFC backend's load/parse functions, using
  /// the arguments that GetArguments() returns at that point. The processing
  /// is almost exactly the same as when ISgfcDocumentReader had been used to
  /// read the SGF data. If the library client does not do anything special,
  /// this is the default behahviour:
  /// - #SgfcArgumentType::EncodingMode 1 is used.
  /// - The first CA property value determines the encoding to use.
  /// - UTF-8 is used as the default encoding if there is no CA property value.
  ///
  /// The last point is the only difference to ISgfcDocumentReader, which uses
  /// ISO-8859-1 as the default encoding. ISgfcDocumentWriter uses UTF-8 because
  /// it assumes that library clients work with UTF-8. A library client that
  /// wants a different default encoding must change the arguments returned by
  /// GetArguments().
  class SGFCPLUSPLUS_EXPORT ISgfcDocumentWriter
  {
  public:
    /// @brief Initializes a newly constructed ISgfcDocumentWriter object.
    ISgfcDocumentWriter();

    /// @brief Destroys and cleans up the ISgfcDocumentWriter object.
    virtual ~ISgfcDocumentWriter();

    /// @brief Returns an object with the collection of arguments that
    /// ISgfcDocumentWriter passes on to SGFC whenever it performs a write
    /// operation.
    ///
    /// The collection of arguments initially contains
    /// SgfcArgumentType::DefaultEncoding with the parameter "UTF-8". This
    /// allows an ISgfcDocument to be passed to ISgfcDocumentWriter for writing
    /// whose game trees don't contain an #SgfcPropertyType::CA property value.
    /// Read the class documentation for details about encodings.
    ///
    /// Add arguments to the collection to change the way how SGFC writes SGF
    /// content. The collection retains its state between write operations so
    /// that repeated write operations use the same arguments.
    virtual std::shared_ptr<ISgfcArguments> GetArguments() const = 0;

    /// @brief Writes the content of @a document to a single .sgf file located
    /// at the specified path, using the arguments that GetArguments() currently
    /// returns.
    ///
    /// Before ISgfcDocumentWriter can invoke the SGFC backend's write function,
    /// it needs to pass the SGF content through the SGFC backend's load/parse
    /// functions. The messages in the result object therefore are a combination
    /// of a full cycle of SGFC backend load/parse/write operations.
    ///
    /// @attention Read the class documentation for a note about encodings.
    ///
    /// @return An ISgfcDocumentWriteResult object that provides the result of
    /// the write operation.
    ///
    /// @exception std::logic_error is thrown if @a document cannot be encoded
    /// into a string due to some fundamental error in the object tree.
    /// Currently the only known case is if the document contains one or more
    /// games that have no root node.
    virtual std::shared_ptr<ISgfcDocumentWriteResult> WriteSgfFile(
      std::shared_ptr<ISgfcDocument> document,
      const std::string& sgfFilePath) const = 0;

    /// @brief Writes the content of @a document into the specified string
    /// object @a sgfContent, using the arguments that GetArguments() currently
    /// returns.
    ///
    /// Before ISgfcDocumentWriter can invoke the SGFC backend's write function,
    /// it needs to pass the SGF content through the SGFC backend's load/parse
    /// functions. The messages in the result object therefore are a combination
    /// of a full cycle of SGFC backend load/parse/write operations.
    ///
    /// @attention Read the class documentation for a note about encodings.
    ///
    /// @return An ISgfcDocumentWriteResult object that provides the result of
    /// the write operation.
    ///
    /// @exception std::logic_error is thrown if @a document cannot be encoded
    /// into a string due to some fundamental error in the object tree.
    /// Currently the only known case is if the document contains one or more
    /// games that have no root node.
    virtual std::shared_ptr<ISgfcDocumentWriteResult> WriteSgfContent(
      std::shared_ptr<ISgfcDocument> document,
      std::string& sgfContent) const = 0;

    /// @brief Validates the content of @a document by simulating a write
    /// operation, using the arguments that GetArguments() currently returns.
    ///
    /// Before ISgfcDocumentWriter can invoke the SGFC backend's write function,
    /// it needs to pass the SGF content through the SGFC backend's load/parse
    /// functions. The messages in the result object therefore are a combination
    /// of a full cycle of SGFC backend load/parse/write operations.
    ///
    /// @attention Read the class documentation for a note about encodings.
    ///
    /// @return An ISgfcDocumentWriteResult object that provides the result of
    /// the validation operation.
    ///
    /// @exception std::logic_error is thrown if @a document cannot be encoded
    /// into a string due to some fundamental error in the object tree.
    /// Currently the only known case is if the document contains one or more
    /// games that have no root node.
    virtual std::shared_ptr<ISgfcDocumentWriteResult> ValidateDocument(
      std::shared_ptr<ISgfcDocument> document) const = 0;

    /// @brief Encodes the content of @a document into an SGF content stream
    /// and prints that stream to stdout for debugging purposes.
    ///
    /// This is useful to see the SGF content that the writer would pass to
    /// SGFC for parsing and writing.
    ///
    /// @todo Remove this prior to release.
    virtual void DebugPrintToConsole(
      std::shared_ptr<ISgfcDocument> document) const = 0;
  };
}
