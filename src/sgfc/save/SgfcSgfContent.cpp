// Project includes
#include "SgfcSgfContent.h"

namespace LibSgfcPlusPlus
{
  SgfcSgfContent::SgfcSgfContent()
  {
  }

  SgfcSgfContent::SgfcSgfContent(
    const std::string& sgfContent,
    const std::string& fileName)
    : sgfContent(sgfContent)
    , fileName(fileName)
  {
  }

  SgfcSgfContent::~SgfcSgfContent()
  {
  }

  std::string SgfcSgfContent::GetSgfContent() const
  {
    return this->sgfContent;
  }

  std::string SgfcSgfContent::GetFileName() const
  {
    return this->fileName;
  }
}
