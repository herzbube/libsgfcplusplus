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

// Project includes
#include "../../include/SgfcConstants.h"
#include "../../include/SgfcDate.h"
#include "../parsing/SgfcValueConverter.h"
#include "../SgfcUtility.h"

// C++ Standard Library includes
#include <iomanip>  // for std::setw()
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  std::vector<SgfcDate> SgfcDate::FromPropertyValue(const SgfcSimpleText& propertyValue)
  {
    std::vector<SgfcDate> gameDates;

    SgfcValueConverter valueConverter;
    std::string typeConversionErrorMessage;

    SgfcDate precedingDate;
    bool isPrecedingDatePresent = false;
    bool precedingDateHadYear = false;
    bool precedingDateHadMonth = false;
    bool precedingDateHadDay = false;

    std::vector<SgfcSimpleText> dateStrings = SgfcUtility::SplitString(propertyValue, ',');
    for (const auto& dateString : dateStrings)
    {
      std::vector<SgfcSimpleText> dateStringParts = SgfcUtility::SplitString(dateString, '-');
      size_t numberOfDateParts = dateStringParts.size();
      if (numberOfDateParts < 1 || numberOfDateParts > 3)
        return std::vector<SgfcDate>();

      bool dateHasYear;

      std::vector<SgfcNumber> dateParts;
      for (size_t indexOfDatePart = 0; indexOfDatePart < numberOfDateParts; indexOfDatePart++)
      {
        const auto& dateStringPart = dateStringParts[indexOfDatePart];
        if (indexOfDatePart == 0)
        {
          if (dateStringPart.size() == 4)
          {
            dateHasYear = true;
          }
          else if (dateStringPart.size() == 2)
          {
            dateHasYear = false;
            if (numberOfDateParts == 3)
              return std::vector<SgfcDate>();
          }
          else
          {
            return std::vector<SgfcDate>();
          }
        }
        else
        {
          if (dateStringPart.size() != 2)
            return std::vector<SgfcDate>();
        }

        SgfcNumber datePart;
        bool conversionResult = valueConverter.TryConvertStringToNumberValue(
          dateStringPart, datePart, typeConversionErrorMessage);
        if (! conversionResult)
          return std::vector<SgfcDate>();

        dateParts.push_back(datePart);
      }

      SgfcDate date;

      if (dateHasYear)
      {
        if (numberOfDateParts == 1)
        {
          date.Year = dateParts[0];
          date.Month = 0;
          date.Day = 0;

          precedingDateHadYear = true;
          precedingDateHadMonth = false;
          precedingDateHadDay = false;
        }
        else if (numberOfDateParts == 2)
        {
          date.Year = dateParts[0];
          date.Month = dateParts[1];
          date.Day = 0;

          precedingDateHadYear = true;
          precedingDateHadMonth = true;
          precedingDateHadDay = false;
        }
        else if (numberOfDateParts == 3)
        {
          date.Year = dateParts[0];
          date.Month = dateParts[1];
          date.Day = dateParts[2];

          precedingDateHadYear = true;
          precedingDateHadMonth = true;
          precedingDateHadDay = true;
        }
        else
        {
          std::stringstream message;
          message << "SgfcDate::FromPropertyValue: Reference date found with unexpected number of date parts " << numberOfDateParts;
          throw std::logic_error(message.str());
        }
      }
      else
      {
        if (! isPrecedingDatePresent)
          return std::vector<SgfcDate>();

        // The SGF standard precisely defines which date parts must be present
        // in the preceding date when a shortcut is encountered. These rules
        // exist for data validation on the one hand, but they are also required
        // for disambiguation of the case when there's only a single date part
        // present: Is that part a month or a day?
        //
        // The following table shows the definition, the code below implements
        // the logic.
        //
        // Preceding date     Shortcut types
        // YYYY   MM   DD     MM-DD    MM    DD
        // -------------------------------------------
        // x      x    x      Ok             dis.
        // x      x    -      Ok       dis.
        // x      -    x                           (1)
        // x      -    -
        // -      x    x      Ok             dis.  (2)
        // -      x    -      Ok       dis.        (2)
        // -      -    x      Ok             dis.  (2)
        // -      -    -                           (1)
        //
        // Ok = It's ok to use the MM-DD shortcut
        // dis. = disambiguation, i.e. if a single double-digit shorcut appears
        //        the shortcut's meaning is the column where "dis." appears.
        //
        // (1) Marks lines with a preceding date format that cannot be specified
        // at all. These lines are listed only to complete the table's
        // combinations.
        // (2) Marks lines with a preceding date format that is a shortcut
        // itself.

        if (numberOfDateParts == 2)
        {
          if (precedingDateHadYear && ! precedingDateHadMonth && precedingDateHadDay)
            return std::vector<SgfcDate>();
          else if (precedingDateHadYear && ! precedingDateHadMonth && ! precedingDateHadDay)
            return std::vector<SgfcDate>();

          date.Year = precedingDate.Year;
          date.Month = dateParts[0];
          date.Day = dateParts[1];

          precedingDateHadYear = false;
          precedingDateHadMonth = true;
          precedingDateHadDay = true;
        }
        else if (numberOfDateParts == 1)
        {
          if ((precedingDateHadYear && precedingDateHadMonth && ! precedingDateHadDay) ||
              (! precedingDateHadYear && precedingDateHadMonth && ! precedingDateHadDay))
          {
            date.Year = precedingDate.Year;
            date.Month = dateParts[0];
            date.Day = 0;

            precedingDateHadYear = false;
            precedingDateHadMonth = true;
            precedingDateHadDay = false;
          }
          else if ((precedingDateHadYear && precedingDateHadMonth && precedingDateHadDay) ||
                   (! precedingDateHadYear && precedingDateHadMonth && precedingDateHadDay) ||
                   (! precedingDateHadYear && ! precedingDateHadMonth && precedingDateHadDay))
          {
            date.Year = precedingDate.Year;
            date.Month = precedingDate.Month;
            date.Day = dateParts[0];

            precedingDateHadYear = false;
            precedingDateHadMonth = false;
            precedingDateHadDay = true;
          }
          else
          {
            return std::vector<SgfcDate>();
          }
        }
        else
        {
          std::stringstream message;
          message << "SgfcDate::FromPropertyValue: Shortcut date found with unexpected number of date parts " << numberOfDateParts;
          throw std::logic_error(message.str());
        }
      }

      // The first date must have a year. The property value might contain
      // something like "0000-01-01" which fools the string-based year presence
      // check, but logically the year is still missing.
      if (! isPrecedingDatePresent && date.Year == 0)
        return std::vector<SgfcDate>();
      else if (date.IsValidSgfDate())
        gameDates.push_back(date);
      else
        return std::vector<SgfcDate>();

      precedingDate = date;
      isPrecedingDatePresent = true;
    }

    return gameDates;
  }

  SgfcSimpleText SgfcDate::ToPropertyValue(const std::vector<SgfcDate>& gameDates)
  {
    std::stringstream propertyValue;

    // Date parts must be preceded with leading zeros
    propertyValue.fill('0');

    // Make sure that decimal point is always a period (".") character and that
    // there are no thousands separators
    propertyValue.imbue(std::locale::classic());

    // General indicator whether the date is the first one to be processed
    bool isPrecedingDatePresent = false;

    // We need this variable so that we can keep track of a date that is as
    // complete as possible across several iterations.
    SgfcDate precedingCompletedDate;

    // Shortcut generation scenarios:
    // Example 1: 2020-01-01, 2020-01-02, 2020-01-03
    // - The second AND the third date must be reduced to "02" and "03"
    // Example 2: 2020-01-01, 0000-00-02, 2020-01-03
    // - The third date must be reduced to "03"
    // Example 3: 2020-01-01, 0000-02-02, 2020-01-03
    // - The third date must be reduced to "01-03"
    // Conclusion:
    // - Use precedingCompletedDate

    // Shortcut validity checks: 2020-01-01, 2020-01-02, 0000-00-03
    // - The second third date must be reduced to a shortcut, then the generated
    //   shortcut must be shortcut-validated against the first date. It could be
    //   argued that this validation is not necessary because generation of the
    //   shortcut is guaranteed to be implemented according to the SGF
    //   standard's specification. However it's much simpler to code the
    //   shortcut-validation algorithm if we don't need to distinguish between
    //   our own shortcut generator or an external shortcut generator.
    // - The third date, which already is a shortcut, must be shortcut-validated
    //   against the shortcut that was generated from the second date. It might
    //   be possible to perform the validation against the original second
    //   date, but I haven't fully thought this through. Again it seems much
    //   simpler to code the shortcut-validation algorithm to always validate
    //   against the last date as it was output.
    // - This means that we need to remember how a date was output, so we need
    //   a set of precedingOutputDateHad... variables.
    bool precedingOutputDateHadYear = false;
    bool precedingOutputDateHadMonth = false;
    bool precedingOutputDateHadDay = false;

    for (auto gameDate : gameDates)
    {
      bool dateIsShortcut = (gameDate.Year == 0);

      // The first date must not be a shortcut
      if (dateIsShortcut && ! isPrecedingDatePresent)
        return SgfcConstants::NoneValueString;

      // Step 1: Perform basic validation of the date itself.
      SgfcDate completedDate = gameDate;
      if (dateIsShortcut)
      {
        completedDate.Year = precedingCompletedDate.Year;
        if (completedDate.Month == 0)
          completedDate.Month = precedingCompletedDate.Month;
      }
      if (! completedDate.IsValidSgfDate())
        return SgfcConstants::NoneValueString;

      // Step 2: Reduce a full date to a shortcut if that is possible.
      // Don't reduce a date any further that is already a shortcut.
      SgfcDate outputDate = gameDate;
      if (! dateIsShortcut && isPrecedingDatePresent)
      {
        bool dateHasYear = (gameDate.Year != 0);
        bool dateHasMonth = (gameDate.Month != 0);
        bool dateHasDay = (gameDate.Day != 0);
        bool precedingCompletedDateHadYear = (precedingCompletedDate.Year != 0);
        bool precedingCompletedDateHadMonth = (precedingCompletedDate.Month != 0);
        bool precedingCompletedDateHadDay = (precedingCompletedDate.Day != 0);

        if (dateHasYear && precedingCompletedDateHadYear && gameDate.Year == precedingCompletedDate.Year)
        {
          if (dateHasMonth && precedingCompletedDateHadMonth)
          {
            if (gameDate.Month == precedingCompletedDate.Month)
            {
              if (dateHasDay && precedingCompletedDateHadDay)
              {
                if (gameDate.Day == precedingCompletedDate.Day)
                {
                  // Identical full dates YYY-MM-DD
                  return SgfcConstants::NoneValueString;
                }
                else
                {
                  // gameDate     precedingCompleteDate  Result
                  // ------------------------------------------
                  // 2019-01-02   2019-01-01             02 (DD shortcut)
                  outputDate.Year = 0;
                  outputDate.Month = 0;
                }
              }
              else if (! dateHasDay && ! precedingCompletedDateHadDay)
              {
                // Identical partial dates YYYY-MM
                return SgfcConstants::NoneValueString;
              }
              else
              {
                // gameDate     precedingCompleteDate  Result
                // ------------------------------------------
                // 2019-01-00   2019-01-01             2019-01     (nothing to shortcut)
                // 2019-01-01   2019-01-00             2019-01-01  (DD shortcut not allowed after YYYY-MM)
              }
            }
            else  // if (gameDate.Month == precedingCompletedDate.Month)
            {
              if (dateHasDay)
              {
                // gameDate     precedingCompleteDate  Result
                // ------------------------------------------
                // 2019-02-02   2019-01-01             02-02 (MM-DD shortcut)
                // 2019-02-02   2019-01-00             02-02 (MM-DD shortcut)
                outputDate.Year = 0;
              }
              else
              {
                // gameDate     precedingCompleteDate  Result
                // ------------------------------------------
                // 2019-02-00   2019-01-01             02 (MM shortcut)
                // 2019-02-00   2019-01-00             02 (MM shortcut)
                outputDate.Year = 0;
                outputDate.Day = 0;
              }
            }
          }
          else if (dateHasMonth && ! precedingCompletedDateHadMonth)
          {
            if (dateHasDay)
            {
              // gameDate     precedingCompleteDate  Result
              // ------------------------------------------
              // 2019-01-01   2019-00-00             01-01 (MM-DD shortcut not allowed after YYYY)
              // 2019-01-01   2019-00-01             -     (not possible, precedingCompleteDate is invalid)
            }
            else
            {
              // gameDate     precedingCompleteDate  Result
              // ------------------------------------------
              // 2019-01-00   2019-00-00             2019-01  (MM shortcut not allowed after YYYY)
              // 2019-01-00   2019-00-01             -        (not possible, precedingCompleteDate is invalid)
            }
          }
          else if (! dateHasMonth && precedingCompletedDateHadMonth)
          {
            // gameDate     precedingCompleteDate  Result
            // ------------------------------------------
            // 2019-00-00   2019-01-00             2019  (nothing to shortcut)
            // 2019-00-00   2019-00-01             -     (not possible, precedingCompleteDate is invalid)
            // 2019-00-00   2019-01-01             2019  (nothing to shortcut)
            // 2019-00-01   2019-01-00             -     (not possible, gameDate is invalid)
            // 2019-00-01   2019-00-01             -     (not possible, gameDate and precedingCompleteDate are invalid)
            // 2019-00-01   2019-01-01             -     (not possible, gameDate is invalid)
          }
          else
          {
            if (! dateHasDay && ! precedingCompletedDateHadDay)
            {
              // Identical partial dates YYYY
              return SgfcConstants::NoneValueString;
            }
            else
            {
              // gameDate     precedingCompleteDate  Result
              // ------------------------------------------
              // 2019-00-00   2019-00-01             -        (not possible, precedingCompleteDate is invalid)
              // 2019-00-01   2019-00-00             -        (not possible, gameDate is invalid)
              // 2019-00-01   2019-00-01             -        (not possible, gameDate and precedingCompleteDate are invalid)
            }
          }
        }
      }
      bool outputDateHasYear = (outputDate.Year != 0);
      bool outputDateHasMonth = (outputDate.Month != 0);
      bool outputDateHasDay = (outputDate.Day != 0);

      if (isPrecedingDatePresent)
        propertyValue << ',';

      // Step 3: Output the date and. at the same time, perform shortcut
      // validation. The validation logic is the same as in
      // SgfcDate::FromPropertyValue. See the implementation of that method for
      // additional comments.
      if (outputDateHasYear)
      {
        if (outputDateHasMonth && outputDateHasDay)
        {
          propertyValue << std::setw(4) << outputDate.Year << "-" << std::setw(2) << outputDate.Month << "-" << std::setw(2) << outputDate.Day;

          precedingOutputDateHadYear = true;
          precedingOutputDateHadMonth = true;
          precedingOutputDateHadDay = true;
        }
        else if (outputDateHasMonth)
        {
          propertyValue << std::setw(4) << outputDate.Year << "-" << std::setw(2) << outputDate.Month;

          precedingOutputDateHadYear = true;
          precedingOutputDateHadMonth = true;
          precedingOutputDateHadDay = false;
        }
        else if (outputDateHasDay)
        {
          // IsValidSgfDate() should have prevented us from getting here
          std::stringstream message;
          message << "SgfcDate::ToPropertyValue: Invalid partial date found with missing month part";
          throw std::logic_error(message.str());
        }
        else
        {
          propertyValue << std::setw(4) << outputDate.Year;

          precedingOutputDateHadYear = true;
          precedingOutputDateHadMonth = false;
          precedingOutputDateHadDay = false;
        }
      }
      else
      {
        if (! isPrecedingDatePresent)
          return SgfcConstants::NoneValueString;

        if (outputDateHasMonth && outputDateHasDay)
        {
          if (precedingOutputDateHadYear && ! precedingOutputDateHadMonth && precedingOutputDateHadDay)
            return SgfcConstants::NoneValueString;
          else if (precedingOutputDateHadYear && ! precedingOutputDateHadMonth && ! precedingOutputDateHadDay)
            return SgfcConstants::NoneValueString;

          propertyValue << std::setw(2) << outputDate.Month << "-" << std::setw(2) << outputDate.Day;

          precedingOutputDateHadYear = false;
          precedingOutputDateHadMonth = true;
          precedingOutputDateHadDay = true;
        }
        else
        {
          if ((precedingOutputDateHadYear && precedingOutputDateHadMonth && ! precedingOutputDateHadDay) ||
              (! precedingOutputDateHadYear && precedingOutputDateHadMonth && ! precedingOutputDateHadDay))
          {
            if (outputDateHasMonth)
            {
              propertyValue << std::setw(2) << outputDate.Month;

              precedingOutputDateHadYear = false;
              precedingOutputDateHadMonth = true;
              precedingOutputDateHadDay = false;
            }
            else
            {
              return SgfcConstants::NoneValueString;
            }
          }
          else if ((precedingOutputDateHadYear && precedingOutputDateHadMonth && precedingOutputDateHadDay) ||
                   (! precedingOutputDateHadYear && precedingOutputDateHadMonth && precedingOutputDateHadDay) ||
                   (! precedingOutputDateHadYear && ! precedingOutputDateHadMonth && precedingOutputDateHadDay))
          {
            if (outputDateHasDay)
            {
              propertyValue << std::setw(2) << outputDate.Day;

              precedingOutputDateHadYear = false;
              precedingOutputDateHadMonth = false;
              precedingOutputDateHadDay = true;
            }
            else
            {
              return SgfcConstants::NoneValueString;
            }
          }
          else
          {
            return SgfcConstants::NoneValueString;
          }
        }
      }

      precedingCompletedDate = completedDate;
      isPrecedingDatePresent = true;
    }

    return propertyValue.str();
  }

  bool SgfcDate::IsPartialDate() const
  {
    return (this->Day == 0 || this->Month == 0 || this->Year == 0);
  }

  bool SgfcDate::IsValidCalendarDate() const
  {
    if (IsPartialDate())
      return false;
    else if (IsValidSgfDate())
      return true;
    else
      return false;
  }

  bool SgfcDate::IsValidSgfDate() const
  {
    if (this->Year < 0 || this->Year > 9999 ||
        this->Month < 0 || this->Month > 12 ||
        this->Day < 0)
    {
      return false;
    }

    // Partial date checks
    //   YYYY-MM-DD    Valid if YYYY = 1-9999 and MM = 1-12 and day part is valid
    //   YYYY-MM-00    Valid if YYYY = 1-9999 and MM = 1-12
    //   YYYY-00-DD    Invalid
    //   YYYY-00-00    Valid if YYYY = 1-9999
    //   0000-MM-DD    Valid if MM = 1-12 and day part is valid (February 29 is valid)
    //   0000-MM-00    Valid if MM = 1-12
    //   0000-00-DD    Valid if DD = 1-31
    //   0000-00-00    Invalid
    if (this->Year == 0)
    {
      if (this->Month == 0)
      {
        if (this->Day == 0)
          return false;             // all date parts are missing
        else
          return (this->Day <= 31); // since the month is missing we have to allow all possible values
      }
      else
      {
        // If the day part is missing then we don't need to perform the
        // complicated day part validation below
        if (this->Day == 0)
          return true;
      }
    }
    else
    {
      if (this->Month == 0)
      {
        // If the month part is missing then the day part must also be missing
        return (this->Day == 0);
      }
      else
      {
        // If the day part is missing then we don't need to perform the
        // complicated day part validation below
        if (this->Day == 0)
          return true;
      }
    }

    // Day part validation
    switch (this->Month)
    {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
      {
        return (this->Day <= 31);
      }
      case 4:
      case 6:
      case 9:
      case 11:
      {
        return (this->Day <= 30);
      }
      case 2:
      {
        if (this->Day == 29)
        {
          if (this->Year % 4 == 0)
          {
            if (this->Year % 100 == 0)
            {
              // Divisible by 100 -> it's usually NOT a leap year, unless
              // it happens to be divisible by 400 (century leap year).
              // This works also if the year part is missing (= value 0).
              if (this->Year % 400 == 0)
                return true;
              else
                return false;
            }
            else
            {
              // Not divisible by 100 -> it's a leap year, 29 is valid
              return true;
            }
          }
          else
          {
            // Not divisible by 4 -> it's not a leap year, 29 is invalid
            return false;
          }
        }
        else
        {
          return (this->Day <= 28);
        }
      }
      default:
      {
        std::stringstream message;
        message << "SgfcDate::IsValid: Unexpected month part " << this->Month;
        throw std::logic_error(message.str());
      }
    }
  }

  bool SgfcDate::operator==(const SgfcDate& other) const
  {
    if (this == &other)
      return true;
    else if (this->Year != other.Year)
      return false;
    else if (this->Month != other.Month)
      return false;
    else if (this->Day != other.Day)
      return false;
    else
      return true;
  }

  bool SgfcDate::operator!=(const SgfcDate& other) const
  {
    return ! (*this == other);
  }
}
