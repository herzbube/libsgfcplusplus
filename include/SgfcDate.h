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
    ///
    /// @see IsPartialDate()
    /// @see IsValidCalendarDate()
    /// @see IsValidSgfDate()
    SgfcNumber Year = 0;

    /// @brief The date's month part. Valid values are in the range from 0-12.
    /// The value 0 denotes that the date has no month part. The default is 0.
    ///
    /// @see IsPartialDate()
    /// @see IsValidCalendarDate()
    /// @see IsValidSgfDate()
    SgfcNumber Month = 0;

    /// @brief The date's day part. Valid values are based on the month part
    /// and, if the month is February, the year part (for leap years). The
    /// value 0 denotes that the date has no day part. The default is 0.
    ///
    /// @see IsPartialDate()
    /// @see IsValidCalendarDate()
    /// @see IsValidSgfDate()
    SgfcNumber Day = 0;

    /// @brief Returns true if the date is a partial date, i.e. if one or more
    /// of the date parts has value 0. Returns false if the date is not a
    /// partial date, i.e. if all date parts have values that are not equal
    /// than 0.
    bool IsPartialDate() const;

    /// @brief Returns true if the date is a valid calendar date. Returns false
    /// if the date is not a valid calendar date. Partial dates are not valid
    /// calendar dates.
    ///
    /// This method calculates leap years (in which 29 February is valid)
    /// according to the Gregorian calendar.
    bool IsValidCalendarDate() const;

    /// @brief Returns true if the date is a valid SGF date, i.e. one that can
    /// be passed to ToPropertyValue() for composing a property value for
    /// SgfcPropertyType::DT). Returns false if the date is not a valid SGF
    /// date, i.e. the date cannot be passed to ToPropertyValue().
    ///
    /// A date is a valid SGF date if IsCalendarDate() returns true. A date
    /// is also a valid SGF date if IsPartialDate() returns true and all of
    /// the following is true:
    /// - The date parts that don't have a zero value have a valid value for a
    ///   calendar date.
    /// - The date is not missing only the month
    /// - The date is not missing all date parts.
    ///
    /// Examples:
    /// - 2020-12-31: IsPartialDate() is false, IsCalendarDate() is true,
    ///   IsValidSgfDate() is true.
    /// - 2100-02-29: IsPartialDate() is false, IsCalendarDate() is false
    ///   (because year 2100 is not a leap year), IsValidSgfDate() is false
    ///   (same reason).
    /// - 2020-12-00: IsPartialDate() is true, IsCalendarDate() is false
    ///   (because partial dates are not calendar dates), IsValidSgfDate() is
    ///   true.
    /// - 2020-13-00: IsPartialDate() is true, IsCalendarDate() is false,
    ///   (because partial dates are not calendar dates and there is no month
    ///   13), IsValidSgfDate() is false (because there is no month 13).
    /// - 2020-00-01: IsPartialDate() is true, IsCalendarDate() is false,
    ///   (because partial dates are not calendar dates), IsValidSgfDate() is
    ///   false (because the month part is missing).
    /// - 0000-00-00: IsPartialDate() is true, IsCalendarDate() is false,
    ///   (because partial dates are not calendar dates), IsValidSgfDate() is
    ///   false (because all date parts are missing).
    ///
    /// Partial dates and validity of the day part:
    /// - If the year part is missing then 29 February is considered to be
    ///   valid.
    /// - If both the year part and the month part are missing then valid values
    ///   for the day part are in the range from 1-31.
    ///
    /// @note If a partial date is passed to ToPropertyValue() it may turn out
    /// that the day part is invalid after all, because a preceding date
    /// specifies a year and/or month that makes the day part invalid.
    ///
    /// This method calculates leap years (in which 29 February is valid)
    /// according to the Gregorian calendar.
    bool IsValidSgfDate() const;

    /// @brief Decomposes the content of @a propertyValue into a collection of
    /// distinct SgfcDate values. The order of the collection matches the order
    /// in which values appear in @a propertyValue. The collection is empty if
    /// decomposition fails.
    ///
    /// Decomposition fails if the SGF standard's specification of the
    /// mandatory structure of an SgfcPropertyType::DT property value is not
    /// met. Decomposition also fails if any of the dates encoded in
    /// @a propertyValue is not valid, i.e. its IsValidSgfDate() method returns
    /// false. As a corollary if decomposition succeeds the IsValidSgfDate()
    /// method of all date objects in the returned collection returns true.
    ///
    /// See the SGF standard specification for the mandatory structure of an
    /// SgfcPropertyType::DT property value.
    ///
    /// @see IsValidSgfDate()
    static std::vector<SgfcDate> FromPropertyValue(const SgfcSimpleText& propertyValue);

    /// @brief Composes a property value for SgfcPropertyType::DT from the
    /// collection of SgfcDate values in @a gameDates.
    ///
    /// @a gameDates is evaluated from beginning to end in order to compose the
    /// property value from left to right. As recommended by the SGF standard
    /// shortcuts are built from the dates in @a gameDates wherever possible.
    /// A date's IsValidSgfDate() method must return true, otherwise the compose
    /// operation fails and this method returns SgfcConstants::NoneValueString.
    ///
    /// @a gameDates may contain dates that already are shortcuts, to support
    /// the case that the caller wants to do the shortcutting herself. The
    /// compose operation does not attempt to generate shortcuts from dates that
    /// already are shortcuts. Dates that already are shortcuts are validated
    /// differently, but the outcome of a failed validation is the same: The
    /// compose operation fails and this method returns
    /// SgfcConstants::NoneValueString.
    ///
    /// Validation rules for dates that already are shortcut dates:
    /// - Step 1: Before the date's IsValidSgfDate() method is invoked the date
    ///   is first logically completed as far as possible using the preceding
    ///   dates' parts. Example: 2019-02-01 is followed by the shortcut
    ///   0000-00-29. The shortcut is completed to 2019-02-29 which causes
    ///   IsValidSgfDate() to return false. Only year and month are used for
    ///   completion - this matches the SGF standard specification which
    ///   mandates that shortcuts acquire the last preceding YYYY and MM.
    /// - Step 2: The date is compared to the preceding date in @a gameDates to
    ///   check whether the shortcut is valid according to the encoding rules in
    ///   the SGF standard. Example: 2020-01-01 followed by the shortcut
    ///   0000-02-00. The shortcut is not valid because an MM shortcut
    ///   after an YYYY-MM-DD date cannot be encoded (upon decoding a 2-digit
    ///   item that appears after an YYYY-MM-DD date is interpreted as DD).
    ///
    /// @return SgfcSimpleText A property value for SgfcPropertyType::DT that
    /// conforms to the SGF standard's mandatory formatting, or
    /// SgfcConstants::NoneValueString if the dates in @a gameDates contain
    /// erroneous data: A date whose IsValidSgfDate() method returns false, a
    /// shortcut date is invalid in relation to the preceding date in the
    /// @a gameDates collection (cf. the SGF standard for details), or a
    /// shortcut date whose date part is made invalid by the preceding date
    /// (e.g. 0000-00-29 after 2019-02-28), or a non-shortcut date that is the
    /// same as the preceding non-shortcut date.
    static SgfcSimpleText ToPropertyValue(const std::vector<SgfcDate>& gameDates);

    /// @brief Returns true if all date parts are the same for the current
    /// SgfcDate object and for @a other. Returns false if any of the date parts
    /// are different.
    bool operator==(const SgfcDate& other) const;

    /// @brief Returns true if any of the date parts are different for the
    /// current SgfcDate object and for @a other. Returns false if all date
    /// parts are the same.
    bool operator!=(const SgfcDate& other) const;
  };
}
