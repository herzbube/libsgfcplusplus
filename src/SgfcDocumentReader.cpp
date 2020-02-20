// Project includes
#include "SgfcDocumentReader.h"
#include "SgfcDocumentReadResult.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcDocumentReader::SgfcDocumentReader()
  {
  }

  SgfcDocumentReader::~SgfcDocumentReader()
  {
  }

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::ReadSgfFile(const std::string& sgfFilePath)
  {
    std::shared_ptr<ISgfcDocumentReadResult> result = std::shared_ptr<ISgfcDocumentReadResult>(new SgfcDocumentReadResult());
    return result;
  }

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::ReadSgfContent(const std::string& sgfContent)
  {
    throw std::runtime_error("not yet implemented");
  }
}
