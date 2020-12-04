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
#include "../../../include/SgfcConstants.h"
#include "../../../include/SgfcGoPlayerRank.h"
#include "../../parsing/SgfcValueConverter.h"
#include "../../SgfcPrivateConstants.h"

// C++ Standard Library includes
#include <regex>
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcGoPlayerRank SgfcGoPlayerRank::FromPropertyValue(const SgfcSimpleText& propertyValue)
  {
    // The regex pattern uses capture groups to identify each of the possible
    // results defined by the SGF standard. We only have to check for the
    // presence of a matched string in the capture groups.
    std::smatch goPlayerRankMatch;
    bool matchResult = std::regex_match(
      propertyValue,
      goPlayerRankMatch,
      SgfcPrivateConstants::GoPlayerRankRegex);
    if (! matchResult)
      return SgfcGoPlayerRank();

    SgfcGoPlayerRank goPlayerRank;
    goPlayerRank.IsValid = true;

    SgfcValueConverter valueConverter;
    std::string typeConversionErrorMessage;

    SgfcNumber rank;
    bool conversionResult = valueConverter.TryConvertStringToNumberValue(
      goPlayerRankMatch[1], rank, typeConversionErrorMessage);
    if (! conversionResult)
    {
      std::stringstream message;
      message << "SgfcGoPlayerRank::FromPropertyValue: Unexpected regex match result, unable to determine numeric rank value from string " << goPlayerRankMatch[1];
      throw std::logic_error(message.str());
    }

    if (goPlayerRankMatch[3].length() > 0)
    {
      goPlayerRank.RankType = SgfcGoPlayerRankType::Kyu;
    }
    else if (goPlayerRankMatch[4].length() > 0)
    {
      goPlayerRank.RankType = SgfcGoPlayerRankType::AmateurDan;
    }
    else if (goPlayerRankMatch[5].length() > 0)
    {
      goPlayerRank.RankType = SgfcGoPlayerRankType::ProfessionalDan;
    }
    else
    {
      std::stringstream message;
      message << "SgfcGoPlayerRank::FromPropertyValue: Unexpected regex match result, unable to determine SgfcGoPlayerRankType value from string " << goPlayerRankMatch[2];
      throw std::logic_error(message.str());
    }

    if (goPlayerRankMatch[7].length() > 0)
    {
      goPlayerRank.RatingType = SgfcGoPlayerRatingType::Uncertain;
    }
    else if (goPlayerRankMatch[8].length() > 0)
    {
      goPlayerRank.RatingType = SgfcGoPlayerRatingType::Established;
    }
    else if (goPlayerRankMatch[6].length() > 0)
    {
      std::stringstream message;
      message << "SgfcGoPlayerRank::FromPropertyValue: Unexpected regex match result, unable to determine SgfcGoPlayerRatingType value from string " << goPlayerRankMatch[6];
      throw std::logic_error(message.str());
    }
    else
    {
      goPlayerRank.RatingType = SgfcGoPlayerRatingType::Unspecified;
    }

    return goPlayerRank;
  }

  SgfcSimpleText SgfcGoPlayerRank::ToPropertyValue(SgfcGoPlayerRank goPlayerRank)
  {
    if (! goPlayerRank.IsValid)
      return SgfcConstants::NoneValueString;

    std::stringstream propertyValue;
    // Make sure that decimal point is always a period (".") character and that
    // there are no thousands separators
    propertyValue.imbue(std::locale::classic());

    propertyValue << goPlayerRank.Rank;

    switch (goPlayerRank.RankType)
    {
      case SgfcGoPlayerRankType::Kyu:
      {
        propertyValue << "k";
        break;
      }
      case SgfcGoPlayerRankType::AmateurDan:
      {
        propertyValue << "d";
        break;
      }
      case SgfcGoPlayerRankType::ProfessionalDan:
      {
        propertyValue << "p";
        break;
      }
      default:
      {
        std::stringstream message;
        message << "SgfcGoPlayerRank::ToPropertyValue: Unexpected go player rank type " << static_cast<int>(goPlayerRank.RankType);
        throw std::logic_error(message.str());
      }
    }

    switch (goPlayerRank.RatingType)
    {
      case SgfcGoPlayerRatingType::Uncertain:
      {
        propertyValue << "?";
        break;
      }
      case SgfcGoPlayerRatingType::Established:
      {
        propertyValue << "*";
        break;
      }
      case SgfcGoPlayerRatingType::Unspecified:
      {
        break;
      }
      default:
      {
        std::stringstream message;
        message << "SgfcGoPlayerRank::ToPropertyValue: Unexpected go player rating type " << static_cast<int>(goPlayerRank.RatingType);
        throw std::logic_error(message.str());
      }
    }

    return propertyValue.str();
  }
}
