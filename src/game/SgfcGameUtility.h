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
#include "../../include/SgfcBoardSize.h"
#include "../../include/SgfcGameType.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcPropertyValue;
  class ISgfcSinglePropertyValue;
  class ISgfcComposedPropertyValue;

  /// @brief The SgfcGameUtility class is a container for static helper
  /// functions related to game logic.
  ///
  /// @ingroup internals
  /// @ingroup library-support
  class SgfcGameUtility
  {
  public:
    SgfcGameUtility() = delete;
    ~SgfcGameUtility() = delete;

    /// @brief Returns the property value(s) in @a propertyValues interpreted as
    /// an SgfcGameType value.
    ///
    /// @retval SgfcGameType If @a propertyValues contains a single element,
    ///         and that element can be converted to an SgfcNumber value, and
    ///         that value is defined in the SGF standard, then the SgfcGameType
    ///         value that corresponds to the SgfcNumber value is returned.
    ///         The value is guaranteed not to be SgfcGameType::Unknown.
    /// @retval SgfcConstants::DefaultGameType If @a propertyValues has
    ///         no elements. The value is guaranteed not to be
    ///         SgfcGameType::Unknown.
    /// @retval SgfcGameType::Unknown If the property value(s) in
    ///         @a propertyValues cannot be converted to an SgfcNumber value
    ///         (@a propertyValues has more than one element, or it has a single
    ///         element that is not an ISgfcNumberPropertyValue object), or if
    ///         conversion is possible but the SgfcNumber value is not defined
    ///         in the SGF standard. Invoke GetGameTypeAsNumber() to obtain the
    ///         game type as SgfcNumber value.
    static SgfcGameType GetGameType(const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);

    /// @brief Returns the property value(s) in @a propertyValues interpreted as
    /// an SgfcNumber value.
    ///
    /// This is useful if GetGameType() returns SgfcGameType::Unknown because
    /// the SgfcNumber value is not defined in the SGF standard and cannot be
    /// mapped to a member of the enumeration SgfcGameType.
    ///
    /// @retval SgfcNumber If @a propertyValues contains a single element,
    ///         and that element can be converted to an SgfcNumber value,
    ///         then that SgfcNumber value is returned. If @a propertyValues
    ///         has no elements, then this method returns the SgfcNumber value
    ///         that corresponds to SgfcConstants::DefaultGameType.
    /// @retval SgfcConstants::GameTypeNaN If the property value(s) in
    ///         @a propertyValues cannot be converted to an SgfcNumber value,
    ///         either because @a propertyValues has more than one element, or
    ///         its single element is not an ISgfcNumberPropertyValue object.
    static SgfcNumber GetGameTypeAsNumber(const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);

    /// @brief Returns the property values in @a propertyValues interpreted as
    /// an SgfcBoardSize value.
    ///
    /// @retval SgfcBoardSize If @a propertyValues contains one element that can
    ///         be converted to a valid SgfcBoardSize value. The value is
    ///         guaranteed not to be SgfcConstants::BoardSizeNone nor
    ///         SgfcConstants::BoardSizeInvalid.
    /// @retval SgfcConstants::BoardSizeDefaultGo If @a propertyValues has
    ///         no elements, and @a gameType is SgfcGameType::Go.
    /// @retval SgfcConstants::BoardSizeDefaultChess If @a propertyValues has
    ///         no elements, and @a gameType is SgfcGameType::Chess.
    /// @retval SgfcConstants::BoardSizeNone If @a propertyValues has
    ///         no elements, but @a gameType is neither SgfcGameType::Go nor
    ///         SgfcGameType::Chess.
    /// @retval SgfcConstants::BoardSizeInvalid If the property value(s) in
    ///         @a propertyValues cannot be converted to an SgfcBoardSize value
    ///         (@a propertyValues has more than one element, or the element is
    ///         neither an ISgfcNumberPropertyValue object nor an
    ///         ISgfcComosedPropertyValue object consisting of two
    ///         ISgfcNumberPropertyValue objects), or if conversion is possible
    ///         but the SgfcBoardSize value violates the constraints defined by
    ///         the SGF standard. See the documentation of
    ///         SgfcConstants::BoardSizeInvalid for details.
    static SgfcBoardSize GetBoardSize(
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues,
      SgfcGameType gameType);

  private:
    static SgfcBoardSize GetBoardSizeFromSingleValue(const ISgfcSinglePropertyValue* singleValue);
    static SgfcBoardSize GetBoardSizeFromComposedValue(const ISgfcComposedPropertyValue* composedValue);
  };
}
