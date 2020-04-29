#pragma once

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief SgfcCoordinateSystem enumerates the coordinate systems supported
  /// by game-specific representations of Point values.
  enum class SGFCPLUSPLUS_EXPORT SgfcCoordinateSystem
  {
    /// @brief The coordinate system's origin is in the upper-left corner.
    ///
    /// For instance, this coordinate system is used by SgfcGoPointNotation::Sgf
    /// and SgfcGoPointNotation::Figure.
    UpperLeftOrigin,

    /// @brief The coordinate system's origin is in the lower-left corner.
    ///
    /// For instance, this coordinate system is used by
    /// SgfcGoPointNotation::Hybrid.
    LowerLeftOrigin,
  };
}
