#pragma once

// Project includes
#include "../include/ISgfcMessage.h"
#include "../include/SgfcExitCode.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcUtility class is a container for static helper functions.
  class SgfcUtility
  {
  public:
    static SgfcExitCode GetSgfcExitCodeFromMessageCollection(
      const std::vector<std::shared_ptr<ISgfcMessage>>& messageCollection);
    static bool GetIsSgfDataValidFromMessageCollection(
      const std::vector<std::shared_ptr<ISgfcMessage>>& messageCollection);
  };
}
