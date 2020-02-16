#pragma once

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcConstants class is a container class for constants.
  class SgfcConstants
  {
  public:
    static const std::string LibraryName;

    static const std::string EmptyString;
    static const std::string SpaceCharacter;
    static const char NewlineCharacter;

    static const std::string LineToken;
    static const std::string ColumnToken;
    static const std::string DashToken;
    static const std::string WarningToken;
    static const std::string ErrorToken;
    static const std::string FatalErrorToken;
    static const std::string CriticalToken;

    static const std::string ShortHelpOption;
    static const std::string LongHelpOption;
    static const std::string VersionOption;
    static const std::string InteractiveModeOption;
  };
}
