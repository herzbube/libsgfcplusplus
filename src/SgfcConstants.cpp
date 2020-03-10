// Project includes
#include "../include/SgfcConstants.h"
#include "SgfcPrivateConstants.h"

namespace LibSgfcPlusPlus
{
  const std::string SgfcConstants::LibraryName = "libsgfc++";

  const std::string NoneString = SgfcPrivateConstants::EmptyString;
  const std::string SgfcConstants::DoubleNormalString = "1";
  const std::string SgfcConstants::DoubleEmphasizedString = "2";
  const std::string SgfcConstants::ColorBlackString = "B";
  const std::string SgfcConstants::ColorWhiteString = "W";

  const SgfcGameType SgfcConstants::DefaultGameType = SgfcGameType::Go;
}
