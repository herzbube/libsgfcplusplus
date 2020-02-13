#pragma once

namespace LibSgfcPlusPlus
{
  /// @brief SgfcExitCode enumerates all SGFC exit codes supported by the
  /// library.
  ///
  /// @note If you know the SGFC documentation very well, then you may note
  /// that there is no exit code for fatal errors. The reason is that the
  /// library converts fatal error messages into exceptions.
  enum class SgfcExitCode
  {
    /// @brief The SGFC operation did not generate any warning or error
    /// messages. If the -d option was specified some messages may have been
    /// ignored.
    Ok = 0,

    /// @brief The SGFC operation generated one or more warning messages, but
    /// no error messages.
    Warnings = 5,

    /// @brief The SGFC operation generated one or more error messages. It may
    /// have generated 0-n warning messages.
    Errors = 10,
  };
}
