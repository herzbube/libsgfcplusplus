#pragma once

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>
#include <string>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcDocument;
  class ISgfcDocumentWriteResult;

  /// @brief The ISgfcDocumentWriter interface provides functions to generate
  /// SGF data from ISgfcDocument objects and to either write that data to the
  /// file system or make it available as an in-memory string.
  /// ISgfcDocumentWriter operates the SGFC backend to achieve its task. Use
  /// SgfcPlusPlusFactory to construct new ISgfcDocumentWriter objects.
  class SGFCPLUSPLUS_EXPORT ISgfcDocumentWriter
  {
  public:
    /// @brief Initializes a newly constructed ISgfcDocumentWriter object.
    ISgfcDocumentWriter();

    /// @brief Destroys and cleans up the ISgfcDocumentWriter object.
    virtual ~ISgfcDocumentWriter();

    /// @brief Writes the content of @a document to a single .sgf file located
    /// at the specified path.
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
      const std::string& sgfFilePath) = 0;

    /// @brief Writes the content of @a document into the specified string
    /// object @a sgfContent.
    ///
    /// The implementation of this method saves the SGF data generated from
    /// @a document to a temporary file and then loads the content of that file
    /// into the specified string object @a sgfContent. After the load operation
    /// the implementation deletes the temporary file.
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
      std::string& sgfContent) = 0;

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
