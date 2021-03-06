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

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcNumber type represents the Number value type defined by
  /// the SGF standard. Values are signed integer numbers.
  ///
  /// @ingroup public-api
  typedef long SgfcNumber;

  /// @brief The SgfcReal type represents the Real value type defined by
  /// the SGF standard. Values are signed floating point numbers.
  ///
  /// @ingroup public-api
  typedef double SgfcReal;

  /// @brief The SgfcSimpleText type represents the SimpleText value type
  /// defined by the SGF standard. Values are strings that contain only space
  /// characters as whitespace, i.e. no linebreaks, tabs, vertical tabs, etc..
  ///
  /// @ingroup public-api
  typedef std::string SgfcSimpleText;

  /// @brief The SgfcText type represents the Text value type defined by
  /// the SGF standard. Values are strings that contain only space characters
  /// and linebreaks as whitespace, i.e. no tabs, vertical tabs, etc..
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
}
