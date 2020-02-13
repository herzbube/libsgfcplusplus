// Project includes
#include "../include/SgfcPlusPlusFactory.h"
#include "SgfcCommandLine.h"

namespace LibSgfcPlusPlus
{
  std::shared_ptr<LibSgfcPlusPlus::ISgfcCommandLine> SgfcPlusPlusFactory::CreateSgfcCommandLine(
    const std::vector<std::string>& arguments)
  {
    std::shared_ptr<ISgfcCommandLine> product = std::shared_ptr<SgfcCommandLine>(new SgfcCommandLine(arguments));
    return product;
  }

  std::shared_ptr<ISgfcCommandLine> SgfcPlusPlusFactory::CreateSgfcCommandLine()
  {
    std::vector<std::string> emptyArgumentList;
    return SgfcPlusPlusFactory::CreateSgfcCommandLine(emptyArgumentList);
  }
}
