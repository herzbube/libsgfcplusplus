#pragma once

// Project includes
#include "ISgfcDocumentReadResult.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>
#include <string>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcArguments;

  /// @brief The ISgfcDocumentReader interface provides functions to generate
  /// ISgfcDocument objects by reading SGF data from the file system or from
  /// in-memory data. ISgfcDocumentReader operates the SGFC backend to achieve
  /// its task. Use SgfcPlusPlusFactory to construct new ISgfcDocumentReader
  /// objects.
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
    virtual std::shared_ptr<ISgfcDocumentReadResult> ReadSgfFile(const std::string& sgfFilePath) = 0;

    /// @brief Reads SGF data from the specified string and puts the data
    /// through the SGFC parser, using the arguments that GetArguments()
    /// currently returns.
    ///
    /// The implementation of this method saves the specified SGF content to a
    /// temporary file and then instructs SGFC to load that file. After the
    /// load operation the implementation deletes the temporary file.
    ///
    /// @return An ISgfcDocumentReadResult object that provides the result of
    /// the read operation. If an error related to temporary file handling
    /// occured the read result object contains an empty document and a parse
    /// result that contains a single message whose ID indicates the nature of
    /// the problem (e.g.
    /// SgfcConstants::SaveSgfContentToFilesystemErrorMessageID).
    virtual std::shared_ptr<ISgfcDocumentReadResult> ReadSgfContent(const std::string& sgfContent) = 0;
  };
}
