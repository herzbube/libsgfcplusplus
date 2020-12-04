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
        // ------------------------------------
        // x      x    x      Ok             Ok
        // x      x    -      Ok       Ok
        // x      -    x
        // x      -    -
        // -      x    x      Ok             Ok
        // -      x    -      Ok       Ok
        // -      -    x      Ok             Ok
        // -      -    -

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

      gameDates.push_back(date);

      precedingDate = date;
      isPrecedingDatePresent = true;
    }

    return gameDates;
  }

  SgfcSimpleText SgfcDate::ToPropertyValue(const std::vector<SgfcDate>& gameDates)
  {
    std::stringstream propertyValue;
    // Make sure that decimal point is always a period (".") character and that
    // there are no thousands separators
    propertyValue.imbue(std::locale::classic());

    SgfcDate precedingDate;
    bool isPrecedingDatePresent = false;

    for (auto gameDate : gameDates)
    {
      if (gameDate.Year < 0 || gameDate.Month < 0 || gameDate.Day < 0)
        return SgfcConstants::NoneValueString;

      if (! isPrecedingDatePresent)
      {
        propertyValue << gameDate.Year;
        if (gameDate.Month != 0)
        {
          propertyValue << "-" << gameDate.Month;
          if (gameDate.Day != 0)
          {
            propertyValue << "-" << gameDate.Day;
          }
        }
        else
        {
          // Ignore the day if there was no month
        }
      }
      else
      {
        if (gameDate.Year != precedingDate.Year)
        {
          propertyValue << gameDate.Year;
          if (gameDate.Month != 0)
          {
            propertyValue << "-" << gameDate.Month;
            if (gameDate.Day != 0)
            {
              propertyValue << "-" << gameDate.Day;
            }
          }
          else
          {
            // Ignore the day if there was no month
          }
        }
        else
        {
          if (gameDate.Month != 0)
          {
            if (gameDate.Month != precedingDate.Month)
            {
              propertyValue << gameDate.Month;
              if (gameDate.Day != 0)
              {
                propertyValue << "-" << gameDate.Day;
              }
            }
            else
            {
              if (gameDate.Day != 0)
              {
                if (gameDate.Day != precedingDate.Day)
                {
                  propertyValue << gameDate.Day;
                }
                else
                {
                  // The date is the same as its predecessor. This doesn't make
                  // sense.
                  return SgfcConstants::NoneValueString;
                }
              }
              else
              {
                // The date has the same year and month as the predecessor, but
                // it has no day to distinguish it from the predecessor. This
                // doesn't make sense.
                return SgfcConstants::NoneValueString;
              }
            }
          }
          else
          {
            // The date has the same year as the predecessor, but it has no
            // month to distinguish it from the predecessor. This doesn't
            // make sense.
            return SgfcConstants::NoneValueString;
          }
        }
      }

      precedingDate = gameDate;
      isPrecedingDatePresent = true;
    }

    return propertyValue.str();
  }
}
