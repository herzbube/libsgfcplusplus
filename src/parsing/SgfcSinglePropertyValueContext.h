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

namespace LibSgfcPlusPlus
{
  /// @brief SgfcSinglePropertyValueContext enumerates in which context a
  /// ISgfcSinglePropertyValue object can appear.
  ///
  /// @ingroup internals
  /// @ingroup parsing
  enum class SgfcSinglePropertyValueContext
  {
    /// @brief The ISgfcSinglePropertyValue object is the first value of an
    /// ISgfcComposedPropertyValue object.
    FirstValueOfComposedValue,

    /// @brief The ISgfcSinglePropertyValue object is the second value of an
    /// ISgfcComposedPropertyValue object.
    SecondValueOfComposedValue,

    /// @brief The ISgfcSinglePropertyValue object is a standalone value, i.e.
    /// it is not part of an ISgfcComposedPropertyValue object.
    Standalone,
  };
}
