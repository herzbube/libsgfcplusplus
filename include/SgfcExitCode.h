#pragma once

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief SgfcExitCode enumerates all SGFC exit codes supported by the
  /// library.
  enum class SGFCPLUSPLUS_EXPORT SgfcExitCode
  {
    /// @brief The SGFC operation did not generate any warning or error
    /// messages. If the -d option was specified some messages may have been
    /// ignored.
    Ok = 0,

    /// @brief The SGFC operation generated one or more warning messages, but
    /// no fatal error messages and no non-fatal error messages.
    Warning = 5,

    /// @brief The SGFC operation generated one or more error messages, but
    /// no fatal error messages. It may have generated 0-n warning messages.
    Error = 10,

    /// @brief The SGFC operation generated a fatal error message. It may have
    /// generated 0-n warning or error messages. Note that because the SGFC
    /// operation aborts immediately when a fatal error occurs, there is
    /// guaranteed to be exactly one fatal error message (i.e. not more than 1).
    FatalError = 20,
  };
}
