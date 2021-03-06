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

// Library includes
#include <SgfcArgumentType.h>
#include <SgfcBoardSize.h>
#include <SgfcColor.h>
#include <SgfcDate.h>
#include <SgfcDouble.h>
#include <SgfcGameResult.h>
#include <SgfcGameType.h>
#include <SgfcGoPlayerRank.h>
#include <SgfcGoRuleset.h>
#include <SgfcMessageID.h>
#include <SgfcPropertyType.h>
#include <SgfcRoundInformation.h>
#include <SgfcTypedefs.h>
#include <game/go/SgfcGoPoint.h>

// C++ Standard Library includes
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The TestDataGenerator class is a container for static methods that
  /// return test data to be used during unit testing.
  class TestDataGenerator
  {
  public:
    static std::vector<std::pair<std::string, SgfcNumber>> GetValidNumberStrings();
    static std::vector<std::string> GetInvalidNumberStrings();
    static std::vector<std::pair<SgfcNumber, std::string>> GetNumberValues();

    static std::vector<std::pair<std::string, SgfcReal>> GetValidRealStrings();
    static std::vector<std::string> GetInvalidRealStrings();
    static std::vector<std::pair<SgfcReal, std::string>> GetRealValues();

    static std::vector<std::pair<std::string, SgfcDouble>> GetValidDoubleStrings();
    static std::vector<std::string> GetInvalidDoubleStrings();
    static std::vector<std::pair<SgfcDouble, std::string>> GetDoubleValues();

    static std::vector<std::pair<std::string, SgfcColor>> GetValidColorStrings();
    static std::vector<std::string> GetInvalidColorStrings();
    static std::vector<std::pair<SgfcColor, std::string>> GetColorValues();

    static std::vector<std::tuple<std::string, SgfcSimpleText, SgfcSimpleText, SgfcSimpleText>> GetSimpleTextStrings();

    static std::vector<std::tuple<std::string, SgfcText, SgfcText, SgfcText>> GetTextStrings();

    static std::vector<std::tuple<SgfcPoint, SgfcBoardSize, int, int, int, int, bool, bool, bool, std::string, std::string, std::string, std::string, SgfcMove, SgfcPoint, SgfcStone>> GetGoPointStrings();
    static std::vector<SgfcBoardSize> GetInvalidGoBoardSizes();
    static std::vector<std::pair<std::string, SgfcBoardSize>> GetInvalidGoPointStrings();

    static std::vector<std::tuple<std::string, SgfcGameType, SgfcBoardSize>> GetValidSZSquareStrings();
    static std::vector<std::tuple<std::string, SgfcGameType>> GetInvalidSZSquareStrings();
    static std::vector<std::tuple<std::string, std::string, SgfcGameType, SgfcBoardSize>> GetValidSZRectangularStrings();
    static std::vector<std::tuple<std::string, std::string, SgfcGameType>> GetInvalidSZRectangularStrings();

    static std::vector<std::tuple<SgfcBoardSize, SgfcGameType, SgfcBoardSize>> GetValidBoardSizes();
    static std::vector<std::tuple<SgfcBoardSize, SgfcGameType>> GetInvalidBoardSizes();

    static std::vector<std::tuple<SgfcArgumentType, std::string>> GetArgumentTypesWithoutParameters();
    static std::vector<SgfcArgumentType> GetArgumentTypesWithIntegerTypeParameter();
    static std::vector<SgfcArgumentType> GetArgumentTypesWithStringTypeParameter();
    static std::vector<SgfcArgumentType> GetArgumentTypesWithPropertyTypeParameter();
    static std::vector<SgfcArgumentType> GetArgumentTypesWithMessageIDParameter();
    static std::vector<SgfcArgumentType> GetArgumentTypesWithParameter();
    static std::vector<SgfcArgumentType> GetArgumentTypesWithoutIntegerTypeParameter();
    static std::vector<SgfcArgumentType> GetArgumentTypesWithoutStringTypeParameter();
    static std::vector<SgfcArgumentType> GetArgumentTypesWithoutPropertyTypeParameter();
    static std::vector<SgfcArgumentType> GetArgumentTypesWithoutMessageIDParameter();
    static std::vector<std::tuple<SgfcArgumentType, int, std::string>> GetArgumentTypesWithValidIntegerTypeParameter();
    static std::vector<std::tuple<SgfcArgumentType, int>> GetArgumentTypesWithInvalidIntegerTypeParameter();
    static std::vector<std::tuple<SgfcArgumentType, std::string, std::string>> GetArgumentTypesWithValidStringTypeParameter();
    static std::vector<std::tuple<SgfcArgumentType, std::string>> GetArgumentTypesWithInvalidStringTypeParameter();
    static std::vector<std::tuple<SgfcArgumentType, SgfcPropertyType, std::string>> GetArgumentTypesWithValidPropertyTypeParameter();
    static std::vector<std::tuple<SgfcArgumentType, SgfcPropertyType>> GetArgumentTypesWithInvalidPropertyTypeParameter();
    static std::vector<std::tuple<SgfcArgumentType, SgfcMessageID, std::string>> GetArgumentTypesWithValidMessageIDParameter();
    static std::vector<std::tuple<SgfcArgumentType, SgfcMessageID>> GetArgumentTypesWithInvalidMessageIDParameter();

    static std::vector<std::tuple<std::string, std::vector<SgfcDate>, bool>> GetValidPropertyValuesDT();
    static std::vector<std::string> GetInvalidPropertyValuesDT();
    static std::vector<std::tuple<std::vector<SgfcDate>, std::string>> GetValidSgfcDates();
    static std::vector<std::vector<SgfcDate>> GetInvalidSgfcDates();

    static std::vector<std::tuple<std::string, SgfcGameResult, bool>> GetValidPropertyValuesRE();
    static std::vector<std::string> GetInvalidPropertyValuesRE();
    static std::vector<std::tuple<SgfcGameResult, std::string>> GetValidSgfcGameResults();
    static std::vector<SgfcGameResult> GetInvalidSgfcGameResults();

    static std::vector<std::tuple<std::string, SgfcRoundInformation, bool>> GetValidPropertyValuesRO();
    static std::vector<std::string> GetInvalidPropertyValuesRO();
    static std::vector<std::tuple<SgfcRoundInformation, std::string>> GetValidSgfcRoundInformations();
    static std::vector<SgfcRoundInformation> GetInvalidSgfcRoundInformations();

    static std::vector<std::tuple<std::string, SgfcGoPlayerRank, bool>> GetValidPropertyValuesBRWR();
    static std::vector<std::string> GetInvalidPropertyValuesBRWR();
    static std::vector<std::tuple<SgfcGoPlayerRank, std::string>> GetValidSgfcGoPlayerRanks();
    static std::vector<SgfcGoPlayerRank> GetInvalidSgfcGoPlayerRanks();

    static std::vector<std::tuple<std::string, SgfcGoRuleset, bool>> GetValidPropertyValuesRU();
    static std::vector<std::string> GetInvalidPropertyValuesRU();
    static std::vector<std::tuple<SgfcGoRuleset, std::string>> GetValidSgfcGoRulesets();
    static std::vector<SgfcGoRuleset> GetInvalidSgfcGoRulesets();

  private:
    TestDataGenerator();
    virtual ~TestDataGenerator();

    static SgfcNumber ConvertStringToNumberOrThrow(const std::string& string);
  };
}
