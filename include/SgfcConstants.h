#pragma once

// Project includes
#include "SgfcGameType.h"
#include "SgfcTypedefs.h"

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcConstants class is a container class for constants.
  class SgfcConstants
  {
  public:
    /// @name libsgfc++ constants
    //@{
    static const std::string LibraryName;
    //@}

    /// @name String constants defined by the SGF standard for specific property values
    //@{
    static const std::string NoneString;
    static const std::string DoubleNormalString;
    static const std::string DoubleEmphasizedString;
    static const std::string ColorBlackString;
    static const std::string ColorWhiteString;
    //@}

    /// @name Constants for defaults defined by the SGF standard
    //@{
    /// @brief The default game type if the SgfcPropertyType::GM property exists
    /// but has no value.
    ///
    /// The SGF standard defines this to be SgfcGameType::Go.
    static const SgfcGameType DefaultGameType;
    //@}
  };
}
