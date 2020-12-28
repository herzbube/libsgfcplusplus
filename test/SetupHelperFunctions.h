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
  class ISgfcNode;
  class ISgfcProperty;
  class SgfcGame;

  // Enum declarations
  enum class InvalidValueTypeGameType
  {
    MoreThanOneValue,
    ComposedValue,
    SingleValueTypeNotANumber,
  };

  enum class InvalidValueTypeBoardSize
  {
    MoreThanOneValue,
    ComposedValueNotANumberAndNumber,
    SingleValueTypeNotANumber,
  };

  // Function prototypes
  void SetupGameWithGameAndBoardSizeProperties(std::shared_ptr<SgfcGame> game, SgfcGameType gameType, SgfcBoardSize boardSize, bool setupWithTypedProperties);
  void SetupNodeWithGameAndBoardSizeProperties(std::shared_ptr<ISgfcNode> node, SgfcGameType gameType, SgfcBoardSize boardSize, bool setupWithTypedProperties);
  void SetupGameWithBoardSizeProperty(std::shared_ptr<SgfcGame> game, SgfcBoardSize boardSize, bool setupWithTypedProperty);
  void AddGameTypeProperty(SgfcGameType gameType, std::vector<std::shared_ptr<ISgfcProperty>>& properties, bool setupWithTypedProperty);
  void AddGameTypeProperty(SgfcNumber gameTypeAsNumber, std::vector<std::shared_ptr<ISgfcProperty>>& properties, bool setupWithTypedProperty);
  void AddGameTypePropertyWithInvalidValues(std::vector<std::shared_ptr<ISgfcProperty>>& properties, InvalidValueTypeGameType invalidValueType);
  std::shared_ptr<ISgfcProperty> CreateGameTypeProperty(SgfcNumber gameTypeAsNumber, bool createTypedProperty);
  void AddBoardSizeProperty(SgfcBoardSize boardSize, std::vector<std::shared_ptr<ISgfcProperty>>& properties, bool setupWithTypedProperty);
  void AddBoardSizePropertyWithInvalidValues(std::vector<std::shared_ptr<ISgfcProperty>>& properties, InvalidValueTypeBoardSize invalidValueType);
  std::shared_ptr<ISgfcProperty> CreateSimpleTextProperty(SgfcPropertyType propertyType, const SgfcSimpleText& propertyValue);
}
