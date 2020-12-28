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
#include <SgfcBoardSize.h>
#include <SgfcGameType.h>
#include <SgfcPropertyType.h>
#include <SgfcTypedefs.h>

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcGameInfo;
  class ISgfcProperty;

  // Function prototypes
  void AssertGameInfoHasDefaultValues(std::shared_ptr<ISgfcGameInfo> gameInfo);
  void AssertGoGameInfoHasDefaultValues(std::shared_ptr<ISgfcGameInfo> gameInfo);
  void AssertGameInfoHasRootPropertyValues(std::shared_ptr<ISgfcGameInfo> gameInfo, SgfcGameType gameType, SgfcNumber gameTypeAsNumber, SgfcBoardSize boardSize);
  void AssertPropertiesContainRootPropertyValues(std::vector<std::shared_ptr<ISgfcProperty>>& properties, SgfcNumber gameTypeAsNumber, SgfcBoardSize boardSize);
  void AssertPropertiesContainsGameInfoPropertyValue(std::vector<std::shared_ptr<ISgfcProperty>>& properties, SgfcPropertyType propertyType, const SgfcSimpleText& propertyValue);
}
