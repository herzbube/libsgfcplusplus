#pragma once

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief SgfcGoPointNotation enumerates all notations supported for
  /// representing a Point location for GoGameType::Go.
  enum class SGFCPLUSPLUS_EXPORT SgfcGoPointNotation
  {
    /// @brief The notation of the SGF standard for representing a Go Point
    /// location. Example: "fq".
    ///
    /// The SGF standard defines the following notation:
    /// - The coordinate system's origin is in the upper-left corner of the
    ///   board.
    /// - Positions on both axis are labeled with letters, starting with a
    ///   lowercase "a" at the coordinate system's origin and progressing
    ///   towards a lowercase "z". This allows 26 positions in both directions.
    ///   If the Go board dimension is larger than 26 then labeling continues
    ///   with uppercase letters. The lowercase letter "z" is followed by the
    ///   uppercase letter "A". The sequence looks like this: a...zA...Z.
    /// - The SGF notation of a point location (which corresponds to the raw SGF
    ///   property string) consists of two letters: The first letter designates
    ///   the x-axis, the second the y-axis. Examples: "aa", "fq", "Sc", etc.
    /// - The maximum board size that can be used with the SGF notation is
    ///   52x52.
    Sgf,

    /// @brief The "1-1" figure notation for representing a Go Point location.
    /// Example: "6-17".
    ///
    /// The "1-1" figure notation is defined like this:
    /// - The coordinate system's origin is in the upper-left corner of the
    ///   board.
    /// - Positions on both axis are labeled with figures that correspond to
    ///   numeric values. The first figure / numeric value at the coordinate
    ///   system's origin is "1", figures / numeric values then progress by
    ///   increases of 1.
    /// - The "1-1" figure notation of a point location consists of two figures
    ///   separated by a dash character ("-"). The first figure designates the
    ///   x-axis, the second the y-axis. Examples: "1-1", "6-17", "45-3", etc.
    /// - The "1-1" figure notation can be used for arbitrary board sizes.
    Figure,

    /// @brief The "A1" hybrid notation for representing a Go Point location.
    /// Example: "F17".
    ///
    /// The "A1" hybrid notation is defined like this:
    /// - The coordinate system's origin is in the lower-left corner of the
    ///   board.
    /// - Positions on the x-axis are labeled with uppercase letters, starting
    ///   with an uppercase "A" at the coordinate system's origin and
    ///   progressing towards an uppercase "Z". The letter "I" is not used to
    ///   avoid confusion with "J".
    /// - Positions on the y-axis are labeled with numbers, starting with 1 at
    ///   the coordinate system's origin and progressing by increases of 1.
    /// - The "A1" figure notation of a point location consists of a letter
    ///   followed by a number without any separator. The letter designates the
    ///   x-axis, the number the y-axis. Examples: "A1", "F17".
    /// - The maximum board size that can be used with the "A1" hybrid notation
    ///   is 25x25.
    Hybrid,
  };
}
