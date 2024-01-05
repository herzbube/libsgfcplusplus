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
#include "SgfcGameResultType.h"
#include "SgfcTypedefs.h"
#include "SgfcWinType.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGameResult struct is a simple type that can hold the
  /// decomposed values of an SgfcPropertyType::RE property value.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  /// @ingroup game
  struct SGFCPLUSPLUS_EXPORT SgfcGameResult
  {
  public:
    /// @brief The result type. The default is
    /// SgfcGameResultType::UnknownResult.
    SgfcGameResultType GameResultType = SgfcGameResultType::UnknownResult;

    /// @brief The win type. The default is SgfcWinType::WinWithScore.
    ///
    /// The win type only has meaning if SgfcGameResult::GameResultType is
    /// either SgfcGameResultType::BlackWin or SgfcGameResultType::WhiteWin.
    SgfcWinType WinType = SgfcWinType::WinWithScore;

    /// @brief The score. The default is 0.0.
    ///
    /// The score only has meaning if SgfcGameResult::GameResultType is
    /// either SgfcGameResultType::BlackWin or SgfcGameResultType::WhiteWin and
    /// if SgfcGameResult::WinType is SgfcWinType::WinWithScore.
    SgfcReal Score = 0.0;

    /// @brief True if the SgfcGameResult object holds a valid game result.
    /// False if the SgfcGameResult object holds an invalid game result. The
    /// default is false.
    ///
    /// This is mainly used to indicate whether
    /// SgfcGameResult::FromPropertyValue() was successful in decomposing
    /// the SgfcPropertyType::RE property value. A library client that manually
    /// creates an SgfcGameResult object can simply set this to true to
    /// assert a valid game result.
    bool IsValid = false;

    /// @brief Decomposes the content of @a propertyValue into distinct game
    /// result type, win type and score values.
    ///
    /// See the SGF standard specification for the mandatory structure of an
    /// SgfcPropertyType::RE property value.
    ///
    /// @return SgfcGameResult An object with the decomposed game
    /// result type, win type and score values. The object's
    /// SgfcGameResult::IsValid member is true if decomposition was successful,
    /// otherwise it is false.
    static SgfcGameResult FromPropertyValue(const SgfcSimpleText& propertyValue);

    /// @brief Composes a property value for SgfcPropertyType::RE from the
    /// game result type, win type and score values in @a gameResult.
    ///
    /// See the SGF standard specification for the mandatory structure of an
    /// SgfcPropertyType::RE property value.
    ///
    /// @return SgfcSimpleText A property value for SgfcPropertyType::RE that
    /// conforms to the SGF standard's mandatory formatting, or
    /// SgfcConstants::NoneValueString if the SgfcGameResult::IsValid
    /// member of @a gameResult is false.
    static SgfcSimpleText ToPropertyValue(SgfcGameResult gameResult);

    /// @brief Returns true if the properties @e GameResultType, @e WinType,
    /// @e Score and @e IsValid are the same for the current SgfcGameResult
    /// object and for @a other. Returns false if any of these properties are
    /// different.
    bool operator==(const SgfcGameResult& other) const;

    /// @brief Returns true if any of the properties @e GameResultType,
    /// @e WinType, @e Score or @e IsValid are different for the current
    /// SgfcGameResult object and for @a other. Returns false if all properties
    /// are the same.
    bool operator!=(const SgfcGameResult& other) const;
  };
}
