#pragma once

namespace LibSgfcPlusPlus
{
  /// @brief SgfcDataLocation enumerates the locations where SGF data can be
  /// read from or written to.
  ///
  /// @ingroup internals
  enum class SgfcDataLocation
  {
    /// @brief The SGF data is read from or written to a file in the filesystem.
    Filesystem,

    /// @brief The SGF data is read from or written to an in-memory buffer,
    /// typically an std::string.
    InMemoryBuffer,
  };
}
