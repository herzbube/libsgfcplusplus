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
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDate struct is a simple type that can hold one of the 1-n
  /// decomposed date values of an SgfcPropertyType::DT property value.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  /// @ingroup game
  struct SGFCPLUSPLUS_EXPORT SgfcDate
  {
  public:
    /// @brief The date's year part. Valid values are in the range from 0-9999.
    /// The default is 0.
    SgfcNumber Year = 0;

    /// @brief The date's month part. Valid values are in the range from 0-12.
    /// The value 0 denotes that the date has no month part. The default is 0.
    SgfcNumber Month = 0;

    /// @brief The date's day part. Valid values are in the range from 0-31.
    /// The value 0 denotes that the date has no day part. The default is 0.
    SgfcNumber Day = 0;

    /// @brief Decomposes the content of @a propertyValue into a collection of
    /// distinct SgfcDate values. The order of the collection matches the order
    /// in which values appear in @a propertyValue. The collection is empty if
    /// decomposition fails.
    ///
    /// See the SGF standard specification for the mandatory structure of an
    /// SgfcPropertyType::DT property value.
    ///
    /// Partial dates in @a propertyValue are completed if the formatting
    /// allows it so that the resulting SgfcDate objects are as concrete as
    /// possible.
    static std::vector<SgfcDate> FromPropertyValue(const SgfcSimpleText& propertyValue);

    /// @brief Composes a property value for SgfcPropertyType::DT from the
    /// collection of SgfcDate values in @a gameDates.
    ///
    /// See the SGF standard specification for the mandatory structure of an
    /// SgfcPropertyType::DT property value.
    ///
    /// As recommended by the SGF standard, the composed property value uses
    /// shortcuts whenever possible. The order in which dates appear in
    /// @a gameDates determines the order in which the shortcuts are built.
    ///
    /// @return SgfcSimpleText A property value for SgfcPropertyType::DT that
    /// conforms to the SGF standard's mandatory formatting, or
    /// SgfcConstants::NoneValueString if the dates in @a gameDates contain
    /// erroneous data: Negative date parts, two consecutive dates that
    /// are the same, a date is missing date parts to distinguish it from
    /// its predecessor in the @a gameDates collection.
    static SgfcSimpleText ToPropertyValue(const std::vector<SgfcDate>& gameDates);
  };
}
