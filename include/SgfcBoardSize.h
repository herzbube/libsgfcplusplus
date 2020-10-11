// -----------------------------------------------------------------------------
// Copyright 2020 Patrick Näf (herzbube@herzbube.ch)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -----------------------------------------------------------------------------

#pragma once

// Project includes
#include "SgfcTypedefs.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcBoardSize struct is a simple type that can hold the value
  /// of SgfcPropertyType::SZ. The constant SgfcConstants::BoardSizeNone
  /// is used to indicate that SgfcPropertyType::SZ does not exist on a game
  /// tree's root node.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  /// @ingroup game
  ///
  /// The SGF standard specifies that for square boards the SGF property must
  /// hold only a single SgfcNumber value. SgfcBoardSize is not that flexible,
  /// it always stores two values. In case of a square board the two values hold
  /// the same numeric value.
  struct SGFCPLUSPLUS_EXPORT SgfcBoardSize
  {
  public:
    /// @brief The number of columns of the board. The default is 1, which is
    /// the minimum allowed by the SGF standard.
    SgfcNumber Columns = 1;

    /// @brief The number of rows of the board. The default is 1, which is
    /// the minimum allowed by the SGF standard.
    SgfcNumber Rows = 1;

    /// @brief Returns true if the board size represents a square board.
    /// Returns false if the board size represents a rectangular board.
    bool IsSquare() const;

    /// @brief Returns true if the number of columns and rows is the same for
    /// the current SgfcBoardSize object and for @a other. Returns false if
    /// either the number of columns or rows or both is different.
    bool operator==(const SgfcBoardSize& other) const;

    /// @brief Returns true if either the number of columns or rows or both
    /// is different for the current SgfcBoardSize object and for @a other.
    /// Returns false if the number of columns and rows is the same.
    bool operator!=(const SgfcBoardSize& other) const;
  };
}
