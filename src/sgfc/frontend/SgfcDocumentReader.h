#pragma once

// Project includes
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

    std::shared_ptr<ISgfcDocumentReadResult> CreateReadResultWithErrorMessage(
      int messageID,
      const std::string& messageText) const;
  };
}
