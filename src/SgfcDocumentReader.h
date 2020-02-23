#pragma once

// Project includes
#include "../include/ISgfcDocumentReader.h"
#include "SgfcBackendController.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDocumentReader class provides an implementation of the
  /// ISgfcDocumentReader interface. See the interface header file for
  /// documentation.
  class SgfcDocumentReader : public ISgfcDocumentReader
  {
  public:
    SgfcDocumentReader();
    virtual ~SgfcDocumentReader();

    virtual std::shared_ptr<ISgfcDocumentReadResult> ReadSgfFile(const std::string& sgfFilePath);
    virtual std::shared_ptr<ISgfcDocumentReadResult> ReadSgfContent(const std::string& sgfContent);

  private:
    std::shared_ptr<SgfcBackendController> backendController;
  };
}
