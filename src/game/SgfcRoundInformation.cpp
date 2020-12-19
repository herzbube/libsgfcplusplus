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
#include "../../include/SgfcRoundInformation.h"
#include "../SgfcPrivateConstants.h"

// C++ Standard Library includes
#include <regex>
#include <sstream>

namespace LibSgfcPlusPlus
{
  SgfcRoundInformation SgfcRoundInformation::FromPropertyValue(const SgfcSimpleText& propertyValue)
  {
    // The regex pattern uses capture groups to identify each of the possible
    // results defined by the SGF standard. We only have to check for the
    // presence of a matched string in the capture groups.
    std::smatch roundInformationMatch;
    bool matchResult = std::regex_match(
      propertyValue,
      roundInformationMatch,
      SgfcPrivateConstants::RoundInformationRegex);
    if (! matchResult)
      return SgfcRoundInformation();

    SgfcRoundInformation roundInformation;
    roundInformation.IsValid = true;

    roundInformation.RoundNumber = roundInformationMatch[1];
    roundInformation.RoundType = roundInformationMatch[2];

    return roundInformation;
  }

  SgfcSimpleText SgfcRoundInformation::ToPropertyValue(const SgfcRoundInformation& roundInformation)
  {
    if (! roundInformation.IsValid)
      return SgfcConstants::NoneValueString;

    std::stringstream propertyValue;

    propertyValue
      << roundInformation.RoundNumber
      << " (" << roundInformation.RoundType << ")";

    return propertyValue.str();
  }

  bool SgfcRoundInformation::operator==(const SgfcRoundInformation& other) const
  {
    if (this == &other)
      return true;
    else if (this->RoundNumber != other.RoundNumber)
      return false;
    else if (this->RoundType != other.RoundType)
      return false;
    else
      return true;
  }

  bool SgfcRoundInformation::operator!=(const SgfcRoundInformation& other) const
  {
    return ! (*this == other);
  }
}
