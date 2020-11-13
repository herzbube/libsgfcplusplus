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
#include "../../include/ISgfcComposedPropertyValue.h"
#include "../../include/ISgfcNumberPropertyValue.h"
#include "../../include/ISgfcSinglePropertyValue.h"
#include "../../include/SgfcConstants.h"
#include "../SgfcUtility.h"
#include "SgfcGameUtility.h"

namespace LibSgfcPlusPlus
{
  SgfcGameType SgfcGameUtility::GetGameType(const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
  {
    SgfcNumber gameTypeAsNumber = GetGameTypeAsNumber(propertyValues);

    return SgfcUtility::MapNumberValueToGameType(
      gameTypeAsNumber);
  }

  SgfcNumber SgfcGameUtility::GetGameTypeAsNumber(const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
  {
    if (propertyValues.size() == 0)
      return SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType);

    if (propertyValues.size() > 1)
      return SgfcConstants::GameTypeNaN;

    auto propertyValue = propertyValues.front();
    if (propertyValue == nullptr)
      return SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType);

    if (propertyValue->IsComposedValue())
      return SgfcConstants::GameTypeNaN;

    auto numberValue = propertyValue->ToSingleValue()->ToNumberValue();
    if (numberValue == nullptr)
      return SgfcConstants::GameTypeNaN;

    return numberValue->GetNumberValue();
  }

  SgfcBoardSize SgfcGameUtility::GetBoardSize(
    const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues,
    SgfcGameType gameType)
   {
     if (propertyValues.size() == 0)
       return SgfcUtility::GetDefaultBoardSize(gameType);

     if (propertyValues.size() > 1)
       return SgfcConstants::BoardSizeInvalid;

     auto propertyValue = propertyValues.front();

     if (propertyValue == nullptr)
       return SgfcUtility::GetDefaultBoardSize(gameType);

     SgfcBoardSize boardSize;
     if (propertyValue->IsComposedValue())
       boardSize = GetBoardSizeFromComposedValue(propertyValue->ToComposedValue());
     else
       boardSize = GetBoardSizeFromSingleValue(propertyValue->ToSingleValue());

     if (boardSize == SgfcConstants::BoardSizeInvalid)
       return boardSize;

     bool isBoardSizeValid = SgfcUtility::IsBoardSizeValid(boardSize, gameType);
     if (isBoardSizeValid)
       return boardSize;
     else
       return SgfcConstants::BoardSizeInvalid;
   }

   SgfcBoardSize SgfcGameUtility::GetBoardSizeFromSingleValue(const ISgfcSinglePropertyValue* singleValue)
   {
     if (singleValue->ToNumberValue() == nullptr)
       return SgfcConstants::BoardSizeInvalid;

     SgfcNumber numberOfColumnsAndRows = singleValue->ToNumberValue()->GetNumberValue();
     return { numberOfColumnsAndRows, numberOfColumnsAndRows };
   }

   SgfcBoardSize SgfcGameUtility::GetBoardSizeFromComposedValue(const ISgfcComposedPropertyValue* composedValue)
   {
     auto singleValue1 = composedValue->GetValue1();
     auto singleValue2 = composedValue->GetValue2();

     if (singleValue1->ToNumberValue() == nullptr || singleValue2->ToNumberValue() == nullptr)
       return SgfcConstants::BoardSizeInvalid;

     return
     {
       singleValue1->ToNumberValue()->GetNumberValue(),
       singleValue2->ToNumberValue()->GetNumberValue()
     };
   }
}
