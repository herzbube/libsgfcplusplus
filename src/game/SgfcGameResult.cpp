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
#include "../../include/SgfcGameResult.h"
#include "../parsing/SgfcValueConverter.h"
#include "../SgfcPrivateConstants.h"

// C++ Standard Library includes
#include <regex>
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcGameResult SgfcGameResult::FromPropertyValue(const SgfcSimpleText& propertyValue)
  {
    // The regex pattern uses capture groups to identify each of the possible
    // results defined by the SGF standard. We only have to check for the
    // presence of a matched string in the capture groups.
    std::smatch gameResultMatch;
    bool matchResult = std::regex_match(
      propertyValue,
      gameResultMatch,
      SgfcPrivateConstants::GameResultRegex);
    if (! matchResult)
      return SgfcGameResult();

    SgfcGameResult gameResult;
    gameResult.IsValid = true;

    if (gameResultMatch[1].length() > 0)
    {
      gameResult.GameResultType = SgfcGameResultType::Draw;
    }
    else if (gameResultMatch[2].length() > 0)
    {
      gameResult.GameResultType = SgfcGameResultType::NoResult;
    }
    else if (gameResultMatch[3].length() > 0)
    {
      gameResult.GameResultType = SgfcGameResultType::UnknownResult;
    }
    else if (gameResultMatch[6].length() > 0)
    {
      gameResult.GameResultType = SgfcGameResultType::BlackWin;
    }
    else if (gameResultMatch[7].length() > 0)
    {
      gameResult.GameResultType = SgfcGameResultType::WhiteWin;
    }
    else
    {
      std::stringstream message;
      message << "SgfcGameResult::FromPropertyValue: Unexpected regex match result, unable to determine SgfcGameResultType value from string " << propertyValue;
      throw std::logic_error(message.str());
    }

    if (gameResult.GameResultType == SgfcGameResultType::BlackWin ||
        gameResult.GameResultType == SgfcGameResultType::WhiteWin)
    {
      if (gameResultMatch[9].length() > 0)
      {
        gameResult.WinType = SgfcWinType::WinByResignation;
      }
      else if (gameResultMatch[10].length() > 0)
      {
        gameResult.WinType = SgfcWinType::WinOnTime;
      }
      else if (gameResultMatch[11].length() > 0)
      {
        gameResult.WinType = SgfcWinType::WinByForfeit;
      }
      else if (gameResultMatch[12].length() == 0)
      {
        gameResult.WinType = SgfcWinType::WinWithoutScore;
      }
      else
      {
        gameResult.WinType = SgfcWinType::WinWithScore;

        SgfcValueConverter valueConverter;
        std::string typeConversionErrorMessage;

        SgfcReal score;
        bool conversionResult = valueConverter.TryConvertStringToRealValue(
          gameResultMatch[12], score, typeConversionErrorMessage);
        if (! conversionResult)
        {
          std::stringstream message;
          message << "SgfcGameResult::FromPropertyValue: Unexpected regex match result, unable to determine numeric score value from string " << gameResultMatch[12];
          throw std::logic_error(message.str());
        }

        gameResult.Score = score;
      }
    }

    return gameResult;
  }

  SgfcSimpleText SgfcGameResult::ToPropertyValue(SgfcGameResult gameResult)
  {
    if (! gameResult.IsValid)
      return SgfcConstants::NoneValueString;

    std::stringstream propertyValue;
    // Make sure that decimal point is always a period (".") character and that
    // there are no thousands separators
    propertyValue.imbue(std::locale::classic());

    switch (gameResult.GameResultType)
    {
      case SgfcGameResultType::BlackWin:
      {
        propertyValue << "B+";
        break;
      }
      case SgfcGameResultType::WhiteWin:
      {
        propertyValue << "W+";
        break;
      }
      case SgfcGameResultType::Draw:
      {
        propertyValue << "Draw";
        break;
      }
      case SgfcGameResultType::NoResult:
      {
        propertyValue << "Void";
        break;
      }
      case SgfcGameResultType::UnknownResult:
      {
        propertyValue << "?";
        break;
      }
      default:
      {
        std::stringstream message;
        message << "SgfcGameResult::ToPropertyValue: Unexpected game result type " << static_cast<int>(gameResult.GameResultType);
        throw std::logic_error(message.str());
      }
    }

    if (gameResult.GameResultType == SgfcGameResultType::BlackWin ||
        gameResult.GameResultType == SgfcGameResultType::WhiteWin)
    {
      switch (gameResult.WinType)
      {
        case SgfcWinType::WinWithScore:
        {
          propertyValue << gameResult.Score;
          break;
        }
        case SgfcWinType::WinWithoutScore:
        {
          break;
        }
        case SgfcWinType::WinByResignation:
        {
          propertyValue << "Resign";
          break;
        }
        case SgfcWinType::WinOnTime:
        {
          propertyValue << "Time";
          break;
        }
        case SgfcWinType::WinByForfeit:
        {
          propertyValue << "Forfeit";
          break;
        }
        default:
        {
          std::stringstream message;
          message << "SgfcGameResult::ToPropertyValue: Unexpected win type " << static_cast<int>(gameResult.WinType);
          throw std::logic_error(message.str());
        }
      }
    }

    return propertyValue.str();
  }


  bool SgfcGameResult::operator==(const SgfcGameResult& other) const
  {
    if (this == &other)
      return true;
    else if (this->GameResultType != other.GameResultType)
      return false;
    else if (this->WinType != other.WinType)
      return false;
    else if (this->Score != other.Score)
      return false;
    else
      return true;
  }

  bool SgfcGameResult::operator!=(const SgfcGameResult& other) const
  {
    return ! (*this == other);
  }
}
