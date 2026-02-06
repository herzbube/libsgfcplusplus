// -----------------------------------------------------------------------------
// Copyright 2020-2026 Patrick Näf (herzbube@herzbube.ch)
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

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcNumber type represents the Number value type defined by
  /// the SGF standard. Values are signed integer numbers. The underlying data
  /// type is guaranteed to be 64 bit wide on all platforms.
  ///
  /// @ingroup public-api
  typedef int64_t SgfcNumber;

  /// @brief The SgfcReal type represents the Real value type defined by
  /// the SGF standard. Values are signed floating point numbers. The underlying
  /// data type is a double-precision floating point type on all platforms.
  ///
  /// @ingroup public-api
  typedef double SgfcReal;

  /// @brief The SgfcSimpleText type represents the SimpleText value type
  /// defined by the SGF standard. Values are strings that contain only space
  /// characters as whitespace, i.e. no linebreaks, tabs, vertical tabs, etc..
  /// The underlying data type consists of single-byte characters, catering to
  /// the UTF-8 encoding that is used by the SGFC backend in almost all use
  /// cases.
  ///
  /// @ingroup public-api
  typedef std::string SgfcSimpleText;

  /// @brief The SgfcText type represents the Text value type defined by
  /// the SGF standard. Values are strings that contain only space characters
  /// and linebreaks as whitespace, i.e. no tabs, vertical tabs, etc..
  /// The underlying data type consists of single-byte characters, catering to
  /// the UTF-8 encoding that is used by the SGFC backend in almost all use
  /// cases.
  ///
  /// @ingroup public-api
  typedef std::string SgfcText;

  /// @brief The SgfcMove type represents the Move value type defined by the
  /// SGF standard. The SGF standard does not provide a universal definition of
  /// how a Move value should look like. Instead it says that the
  /// interpretation of Move values is game specific.
  ///
  /// @ingroup public-api
  typedef std::string SgfcMove;

  /// @brief The SgfcPoint type represents the Point value type defined by the
  /// SGF standard. The SGF standard does not provide a universal definition of
  /// how a Point value should look like. Instead it says that the
  /// interpretation of Point values is game specific.
  ///
  /// @ingroup public-api
  typedef std::string SgfcPoint;

  /// @brief The SgfcStone type represents the Stone value type defined by the
  /// SGF standard. The SGF standard does not provide a universal definition of
  /// how a Stone value should look like. Instead it says that the
  /// interpretation of Stone values is game specific.
  ///
  /// @ingroup public-api
  typedef std::string SgfcStone;

  /// @brief The SgfcTextOffset type is used to store a value that is either a
  /// line number or a column number (both 1-based) in a piece of SGF content.
  ///
  /// @ingroup public-api
  ///
  /// @see ISgfcMessage
  typedef uint64_t SgfcTextOffset;

  /// @brief The SgfcGoPointAxisPosition type is used to store a value that is
  /// either an x-axis position or an y-axis position (both 1-based) of a point
  /// on a Go board.
  ///
  /// @ingroup public-api
  ///
  /// The underlying data type of SgfcGoPointAxisPosition is capable of
  /// expressing the whole positive value range that SgfcBoardSize::Columns
  /// and SgfcBoardSize::Rows support. In practice, the SGF standard limits the
  /// Go board size to SgfcConstants::BoardSizeMaximumGo.
  ///
  /// @see ISgfcGoPoint
  typedef uint64_t SgfcGoPointAxisPosition;
}
