// -----------------------------------------------------------------------------
// Copyright 2024 Patrick Näf (herzbube@herzbube.ch)
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
#include "../AssertHelperFunctions.h"
#include "../SetupHelperFunctions.h"
#include "../TestDataGenerator.h"

// Library includes
#include <document/SgfcGame.h>
#include <document/SgfcNode.h>
#include <document/SgfcProperty.h>
#include <document/SgfcTreeBuilder.h>
#include <document/typedproperty/SgfcBoardSizeProperty.h>
#include <document/typedproperty/SgfcGameTypeProperty.h>
#include <ISgfcGoGameInfo.h>
#include <ISgfcPropertyFactory.h>
#include <ISgfcPropertyValueFactory.h>
#include <SgfcConstants.h>
#include <SgfcPlusPlusFactory.h>
#include <SgfcUtility.h>

// Unit test library includes
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcGame is constructed", "[document]" )
{
  GIVEN( "The SgfcGame default constructor is used" )
  {
    WHEN( "SgfcGame is constructed" )
    {
      THEN( "SgfcGame is constructed successfully" )
      {
        REQUIRE_NOTHROW( SgfcGame() );
      }
    }

    WHEN( "SgfcGame is constructed" )
    {
      SgfcGame game;

      THEN( "SgfcGame has the expected default state" )
      {
        REQUIRE( game.GetGameType() == SgfcConstants::DefaultGameType );
        REQUIRE( game.GetGameTypeAsNumber() == SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType) );
        REQUIRE( game.HasBoardSize() == true );
        REQUIRE( game.GetBoardSize() == SgfcConstants::BoardSizeDefaultGo );
        REQUIRE( game.HasRootNode() == false );
        REQUIRE( game.GetRootNode() == nullptr );
        REQUIRE( game.GetGameInfoNodes().size() == 0 );
        REQUIRE( game.CreateGameInfo() != nullptr );
        REQUIRE( game.GetTreeBuilder() == nullptr );
      }
    }
  }

  GIVEN( "The SgfcGame constructor taking an SgfcNode parameter is used" )
  {
    WHEN( "SgfcGame is constructed with an SgfcNode object" )
    {
      std::shared_ptr<SgfcNode> rootNode = std::shared_ptr<SgfcNode>(new SgfcNode());

      THEN( "SgfcGame is constructed successfully" )
      {
        REQUIRE_NOTHROW( SgfcGame(rootNode) );
      }
    }

    WHEN( "SgfcGame is constructed with an SgfcNode object" )
    {
      std::shared_ptr<SgfcNode> rootNode = std::shared_ptr<SgfcNode>(new SgfcNode());
      SgfcGame game(rootNode);

      THEN( "SgfcGame has the expected state" )
      {
        REQUIRE( game.GetGameType() == SgfcConstants::DefaultGameType );
        REQUIRE( game.GetGameTypeAsNumber() == SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType) );
        REQUIRE( game.HasBoardSize() == true );
        REQUIRE( game.GetBoardSize() == SgfcConstants::BoardSizeDefaultGo );
        REQUIRE( game.HasRootNode() == true );
        REQUIRE( game.GetRootNode() == rootNode );
        REQUIRE( game.GetGameInfoNodes().size() == 0 );
        REQUIRE( game.CreateGameInfo() != nullptr );
        REQUIRE( game.GetTreeBuilder() == nullptr );
      }
    }

    WHEN( "SgfcGame is constructed with a nullptr SgfcNode object" )
    {
      std::shared_ptr<SgfcNode> rootNode = std::shared_ptr<SgfcNode>(nullptr);

      THEN( "The SgfcGame constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcGame(rootNode),
          std::invalid_argument);
      }
    }
  }
}

SCENARIO( "SgfcGame is configured with an SgfcNode object", "[document]" )
{
  auto node = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto secondNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto nullNode = std::shared_ptr<SgfcNode>(nullptr);

  GIVEN( "The SgfcGame default constructor was used" )
  {
    SgfcGame game;

    WHEN( "SgfcGame is configured with an SgfcNode object" )
    {
      std::vector<std::shared_ptr<SgfcNode>> v = { node, nullNode };
      auto rootNode = GENERATE_COPY( from_range(v) );

      THEN( "The getter returns the SgfcNode object that was used in the setter" )
      {
        REQUIRE( game.HasRootNode() == false );
        REQUIRE( game.GetRootNode() == nullptr );
        game.SetRootNode(rootNode);
        REQUIRE( game.HasRootNode() == (rootNode != nullptr) );
        REQUIRE( game.GetRootNode() == rootNode );
      }
    }

    GIVEN( "The SgfcGame constructor taking an SgfcNode parameter was used" )
    {
      SgfcGame game(node);

      WHEN( "SgfcGame is configured with an SgfcNode object" )
      {
        // Include the same node that was used for construction
        std::vector<std::shared_ptr<SgfcNode>> v = { node, secondNode, nullNode };
        auto rootNode = GENERATE_COPY( from_range(v) );

        THEN( "The getter returns the SgfcNode object that was used in the setter" )
        {
          REQUIRE( game.GetRootNode() == node );
          game.SetRootNode(rootNode);
          REQUIRE( game.GetRootNode() == rootNode );
        }
      }
    }
  }
}

SCENARIO( "SgfcGame is configured with an SgfcTreeBuilder object", "[document]" )
{
  auto game = std::shared_ptr<SgfcGame>(new SgfcGame());
  auto treeBuilder = std::shared_ptr<SgfcTreeBuilder>(new SgfcTreeBuilder(game));
  auto nullTreeBuilder = std::shared_ptr<SgfcTreeBuilder>(nullptr);

  GIVEN( "SgfcGame is configured with an SgfcTreeBuilder object" )
  {
    WHEN( "SgfcGame is configured with an SgfcTreeBuilder object" )
    {
      std::vector<std::shared_ptr<SgfcTreeBuilder>> v = { treeBuilder, nullTreeBuilder };
      auto newTreeBuilder = GENERATE_COPY( from_range(v) );

      THEN( "The getter returns the SgfcTreeBuilder object that was used in the setter" )
      {
        REQUIRE( game->GetTreeBuilder() == nullptr );
        game->SetTreeBuilder(newTreeBuilder);
        REQUIRE( game->GetTreeBuilder() == newTreeBuilder );
      }
    }
  }
}

SCENARIO( "SgfcGame is queried for the game type", "[document]" )
{
  auto game = std::shared_ptr<SgfcGame>(new SgfcGame());
  auto node = std::shared_ptr<SgfcNode>(new SgfcNode());
  std::vector<std::shared_ptr<ISgfcProperty>> properties;

  auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
  auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();

  GIVEN( "The game has no root node" )
  {
    WHEN( "SgfcGame is queried for the game type" )
    {
      THEN( "SgfcGame returns SgfcConstants::DefaultGameType" )
      {
        REQUIRE( game->GetGameType() == SgfcConstants::DefaultGameType );
        REQUIRE( game->GetGameTypeAsNumber() == SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType) );
      }
    }
  }

  GIVEN( "The game has a root node but there is no property of type SgfcPropertyType::GM" )
  {
    game->SetRootNode(node);

    WHEN( "SgfcGame is queried for the game type" )
    {
      THEN( "SgfcGame returns SgfcConstants::DefaultGameType" )
      {
        REQUIRE( game->GetGameType() == SgfcConstants::DefaultGameType );
        REQUIRE( game->GetGameTypeAsNumber() == SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType) );
      }
    }
  }

  GIVEN( "The game has a property of type SgfcPropertyType::GM but the property has no value" )
  {
    bool setupWithTypedProperty = GENERATE( true, false );

    std::shared_ptr<ISgfcProperty> gameTypePropertyWithoutValue;
    if (setupWithTypedProperty)
      gameTypePropertyWithoutValue = propertyFactory->CreateGameTypeProperty();
    else
      gameTypePropertyWithoutValue = propertyFactory->CreateProperty(SgfcPropertyType::GM);
    properties.push_back(gameTypePropertyWithoutValue);

    game->SetRootNode(node);
    node->SetProperties(properties);

    WHEN( "SgfcGame is queried for the game type" )
    {
      THEN( "SgfcGame returns SgfcConstants::DefaultGameType" )
      {
        REQUIRE( game->GetGameType() == SgfcConstants::DefaultGameType );
        REQUIRE( game->GetGameTypeAsNumber() == SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType) );
      }
    }
  }

  GIVEN( "The game has a property of type SgfcPropertyType::GM and the property value is not defined in the SGF standard" )
  {
    bool setupWithTypedProperty = GENERATE( true, false );

    SgfcNumber gameTypeAsNumberNotDefinedInSgfStandard = 1000;
    AddGameTypeProperty(gameTypeAsNumberNotDefinedInSgfStandard, properties, setupWithTypedProperty);

    game->SetRootNode(node);
    node->SetProperties(properties);

    WHEN( "SgfcGame is queried for the game type" )
    {
      THEN( "SgfcGame returns SgfcGameType::Unknown" )
      {
        REQUIRE( game->GetGameType() == SgfcGameType::Unknown );
        REQUIRE( game->GetGameTypeAsNumber() == gameTypeAsNumberNotDefinedInSgfStandard );
      }
    }
  }

  GIVEN( "The game has a property of type SgfcPropertyType::GM and the property value is defined in the SGF standard" )
  {
    bool setupWithTypedProperty = GENERATE( true, false );

    SgfcGameType gameTypeDefinedInSgfStandard = SgfcGameType::Kuba;
    AddGameTypeProperty(gameTypeDefinedInSgfStandard, properties, setupWithTypedProperty);

    game->SetRootNode(node);
    node->SetProperties(properties);

    WHEN( "SgfcGame is queried for the game type" )
    {
      THEN( "SgfcGame returns an SgfcGameType value that is not SgfcGameType::Unknown" )
      {
        REQUIRE( game->GetGameType() == gameTypeDefinedInSgfStandard );
        REQUIRE( game->GetGameTypeAsNumber() == SgfcUtility::MapGameTypeToNumberValue(gameTypeDefinedInSgfStandard) );
      }
    }
  }

  GIVEN( "The game has a property of type SgfcPropertyType::GM and the property value(s) cannot be converted to a Number value" )
  {
    InvalidValueTypeGameType setupWithInvalidValueType = GENERATE(
      InvalidValueTypeGameType::MoreThanOneValue,
      InvalidValueTypeGameType::ComposedValue,
      InvalidValueTypeGameType::SingleValueTypeNotANumber );

    AddGameTypePropertyWithInvalidValues(properties, setupWithInvalidValueType);

    game->SetRootNode(node);
    node->SetProperties(properties);

    WHEN( "SgfcGame is queried for the game type" )
    {
      THEN( "SgfcGame returns SgfcGameType::Unknown" )
      {
        REQUIRE( game->GetGameType() == SgfcGameType::Unknown );
        REQUIRE( game->GetGameTypeAsNumber() == SgfcConstants::GameTypeNaN );
      }
    }
  }
}

SCENARIO( "SgfcGame is queried for the board size", "[document]" )
{
  struct TestData1
  {
    std::shared_ptr<ISgfcProperty> GameTypeProperty;
    bool ExpectedHasBoardSize;
    SgfcBoardSize ExpectedBoardSize;
  };
  struct TestData2
  {
    SgfcBoardSize BoardSize;
    bool ExpectedHasBoardSize;
    SgfcBoardSize ExpectedBoardSize;
  };

  auto game = std::shared_ptr<SgfcGame>(new SgfcGame());
  auto node = std::shared_ptr<SgfcNode>(new SgfcNode());
  std::vector<std::shared_ptr<ISgfcProperty>> properties;

  auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
  auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();

  auto gameTypePropertyValueGo = propertyValueFactory->CreateNumberPropertyValue(
    SgfcUtility::MapGameTypeToNumberValue(SgfcGameType::Go));
  auto gameTypePropertyGo = propertyFactory->CreateGameTypeProperty(
    gameTypePropertyValueGo);

  auto gameTypePropertyValueChess = propertyValueFactory->CreateNumberPropertyValue(
    SgfcUtility::MapGameTypeToNumberValue(SgfcGameType::Chess));
  auto gameTypePropertyChess = propertyFactory->CreateGameTypeProperty(
    gameTypePropertyValueChess);

  SgfcGameType gameTypeNeitherGoNorChess = SgfcGameType::Hnefatal;
  auto gameTypePropertyValueNeitherGoNorChess = propertyValueFactory->CreateNumberPropertyValue(
    SgfcUtility::MapGameTypeToNumberValue(gameTypeNeitherGoNorChess));
  auto gameTypePropertyNeitherGoNorChess = propertyFactory->CreateGameTypeProperty(
    gameTypePropertyValueNeitherGoNorChess);

  GIVEN( "The game has no root node" )
  {
    WHEN( "SgfcGame is queried for the board size" )
    {
      THEN( "SgfcGame returns SgfcConstants::BoardSizeDefaultGo" )
      {
        REQUIRE( game->HasBoardSize() == true );
        REQUIRE( game->GetBoardSize() == SgfcConstants::BoardSizeDefaultGo );
      }
    }
  }

  GIVEN( "The game has a root node but no properties" )
  {
    game->SetRootNode(node);

    WHEN( "SgfcGame is queried for the board size" )
    {
      THEN( "SgfcGame returns SgfcConstants::BoardSizeDefaultGo" )
      {
        REQUIRE( game->HasBoardSize() == true );
        REQUIRE( game->GetBoardSize() == SgfcConstants::BoardSizeDefaultGo );
      }
    }
  }

  GIVEN( "The game has a root node with a property of type SgfcPropertyType::GM, but with no property of type SgfcPropertyType::SZ" )
  {
    auto testData = GENERATE_COPY(
      TestData1 { gameTypePropertyGo, true, SgfcConstants::BoardSizeDefaultGo },
      TestData1 { gameTypePropertyChess, true, SgfcConstants::BoardSizeDefaultChess },
      TestData1 { gameTypePropertyNeitherGoNorChess, false, SgfcConstants::BoardSizeNone }
    );

    game->SetRootNode(node);
    properties.push_back(testData.GameTypeProperty);
    node->SetProperties(properties);

    WHEN( "SgfcGame is queried for the board size" )
    {
      THEN( "SgfcGame returns a default board size that matches the game type" )
      {
        REQUIRE( game->HasBoardSize() == testData.ExpectedHasBoardSize );
        REQUIRE( game->GetBoardSize() == testData.ExpectedBoardSize );
      }
    }
  }

  GIVEN( "The game has a root node with a property of type SgfcPropertyType::GM and a property of type SgfcPropertyType::SZ without value" )
  {
    auto boardSizePropertyWithoutValue = propertyFactory->CreateBoardSizeProperty();
    properties.push_back(boardSizePropertyWithoutValue);

    auto testData = GENERATE_COPY(
      TestData1 { gameTypePropertyGo, true, SgfcConstants::BoardSizeDefaultGo },
      TestData1 { gameTypePropertyChess, true, SgfcConstants::BoardSizeDefaultChess },
      TestData1 { gameTypePropertyNeitherGoNorChess, false, SgfcConstants::BoardSizeNone }
    );
    properties.push_back(testData.GameTypeProperty);

    game->SetRootNode(node);
    node->SetProperties(properties);

    WHEN( "SgfcGame is queried for the board size" )
    {
      THEN( "SgfcGame returns a default board size that matches the game type" )
      {
        REQUIRE( game->HasBoardSize() == testData.ExpectedHasBoardSize );
        REQUIRE( game->GetBoardSize() == testData.ExpectedBoardSize );
      }
    }
  }

  GIVEN( "The game has a root node with a property of type SgfcPropertyType::GM and a property of type SgfcPropertyType::SZ with a valid value" )
  {
    bool setupWithTypedProperties = GENERATE( true, false );
    auto testData = GENERATE( from_range(TestDataGenerator::GetValidBoardSizes()) );

    SetupGameWithGameAndBoardSizeProperties(game, std::get<1>(testData), std::get<0>(testData), setupWithTypedProperties);

    WHEN( "SgfcGame is queried for the board size" )
    {
      THEN( "SgfcGame returns an valid SgfcBoardSize value" )
      {
        REQUIRE( game->HasBoardSize() == true );
        REQUIRE( game->GetBoardSize() == std::get<2>(testData) );
      }
    }
  }

  GIVEN( "The game has a root node with a property of type SgfcPropertyType::GM and a property of type SgfcPropertyType::SZ with an invalid value" )
  {
    bool setupWithTypedProperties = GENERATE( true, false );
    auto testData = GENERATE( from_range(TestDataGenerator::GetInvalidBoardSizes()) );

    SetupGameWithGameAndBoardSizeProperties(game, std::get<1>(testData), std::get<0>(testData), setupWithTypedProperties);

    WHEN( "SgfcGame is queried for the board size" )
    {
      THEN( "SgfcGame returns SgfcConstants::BoardSizeInvalid" )
      {
        REQUIRE( game->HasBoardSize() == false );
        REQUIRE( game->GetBoardSize() == SgfcConstants::BoardSizeInvalid );
      }
    }
  }

  GIVEN( "The game has a property of type SgfcPropertyType::SZ and the property value(s) cannot be converted to an SgfcBoardSize value" )
  {
    bool setupWithGameTypePropery = GENERATE( true, false );

    if (setupWithGameTypePropery)
      properties.push_back(gameTypePropertyGo);

    InvalidValueTypeBoardSize setupWithInvalidValueType = GENERATE(
      InvalidValueTypeBoardSize::MoreThanOneValue,
      InvalidValueTypeBoardSize::ComposedValueNotANumberAndNumber,
      InvalidValueTypeBoardSize::SingleValueTypeNotANumber );

    AddBoardSizePropertyWithInvalidValues(properties, setupWithInvalidValueType);

    game->SetRootNode(node);
    node->SetProperties(properties);

    WHEN( "SgfcGame is queried for the board size" )
    {
      THEN( "SgfcGame returns SgfcConstants::BoardSizeInvalid" )
      {
        REQUIRE( game->HasBoardSize() == false );
        REQUIRE( game->GetBoardSize() == SgfcConstants::BoardSizeInvalid );
      }
    }
  }

  GIVEN( "The game has a root node with no property of type SgfcPropertyType::GM and a property of type SgfcPropertyType::SZ without value" )
  {
    auto boardSizePropertyWithoutValue = propertyFactory->CreateBoardSizeProperty();
    properties.push_back(boardSizePropertyWithoutValue);

    game->SetRootNode(node);
    node->SetProperties(properties);

    WHEN( "SgfcGame is queried for the board size" )
    {
      THEN( "SgfcGame returns SgfcConstants::BoardSizeDefaultGo" )
      {
        REQUIRE( game->HasBoardSize() == true );
        REQUIRE( game->GetBoardSize() == SgfcConstants::BoardSizeDefaultGo );
      }
    }
  }

  GIVEN( "The game has a root node with no property of type SgfcPropertyType::GM and a property of type SgfcPropertyType::SZ with a valid value" )
  {
    bool setupWithTypedProperty = GENERATE( true, false );
    auto testData = GENERATE(
      filter(
        // This is a predicate that examines the elements in the from_range
        // generator and returns true for those elements that the filter should
        // let pass
        [](const std::tuple<SgfcBoardSize, SgfcGameType, SgfcBoardSize>& tuple)
        {
          // Because the property of type SgfcPropertyType::GM is missing, the
          // default game type is SgfcGameType::Go. Because of this we can only
          // let test data through that is intended for that game type.
          return std::get<1>(tuple) == SgfcGameType::Go;
        },
        from_range(TestDataGenerator::GetValidBoardSizes())
      )
    );

    SetupGameWithBoardSizeProperty(game, std::get<0>(testData), setupWithTypedProperty);

    WHEN( "SgfcGame is queried for the board size" )
    {
      THEN( "SgfcGame returns an valid SgfcBoardSize value" )
      {
        REQUIRE( game->HasBoardSize() == true );
        REQUIRE( game->GetBoardSize() == std::get<2>(testData) );
      }
    }
  }

  GIVEN( "The game has a root node with no property of type SgfcPropertyType::GM and a property of type SgfcPropertyType::SZ with an invalid value" )
  {
    bool setupWithTypedProperty = GENERATE( true, false );
    auto testData = GENERATE(
      filter(
        // This is a predicate that examines the elements in the from_range
        // generator and returns true for those elements that the filter should
        // let pass
        [](const std::tuple<SgfcBoardSize, SgfcGameType>& tuple)
        {
          // Because the property of type SgfcPropertyType::GM is missing, the
          // default game type is SgfcGameType::Go. Because of this we can only
          // let test data through that is intended for that game type.
          return std::get<1>(tuple) == SgfcGameType::Go;
        },
        from_range(TestDataGenerator::GetInvalidBoardSizes())
      )
    );

    SetupGameWithBoardSizeProperty(game, std::get<0>(testData), setupWithTypedProperty);

    WHEN( "SgfcGame is queried for the board size" )
    {
      THEN( "SgfcGame returns an valid SgfcBoardSize value" )
      {
        REQUIRE( game->HasBoardSize() == false );
        REQUIRE( game->GetBoardSize() == SgfcConstants::BoardSizeInvalid );
      }
    }
  }
}

SCENARIO( "SgfcGame is queried for the game info nodes", "[document]" )
{
  auto game = std::make_shared<SgfcGame>();
  SgfcTreeBuilder treeBuilder(game);

  auto rootNode = std::make_shared<SgfcNode>();
  auto intermediateNode = std::make_shared<SgfcNode>();
  auto intermediateSiblingNode = std::make_shared<SgfcNode>();
  auto leafNode = std::make_shared<SgfcNode>();

  game->SetRootNode(rootNode);
  treeBuilder.SetFirstChild(rootNode, intermediateNode);
  treeBuilder.SetNextSibling(intermediateNode, intermediateSiblingNode);
  treeBuilder.SetFirstChild(intermediateNode, leafNode);

  auto gameInfoProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::AN, "AN"));

  GIVEN( "SgfcGame has no root node" )
  {
    game->SetRootNode(nullptr);

    WHEN( "SgfcGame is queried" )
    {
      auto gameInfoNodes = game->GetGameInfoNodes();

      THEN( "SgfcGame returns an empty collection" )
      {
        REQUIRE( gameInfoNodes.size() == 0 );
      }
    }
  }

  GIVEN( "SgfcGame has a root node but no game info nodes" )
  {
    WHEN( "SgfcGame is queried" )
    {
      auto gameInfoNodes = game->GetGameInfoNodes();

      THEN( "SgfcGame returns an empty collection" )
      {
        REQUIRE( gameInfoNodes.size() == 0 );
      }
    }
  }

  GIVEN( "SgfcGame has a single game info node" )
  {
    std::vector<std::shared_ptr<ISgfcNode>> testNodes = { rootNode, intermediateNode, intermediateSiblingNode, leafNode };

    WHEN( "SgfcGame is queried" )
    {
      THEN( "SgfcGame returns a collection with a single element" )
      {
        // TODO: Get this to work with GENERATE_COPY
        for (auto gameInfoNode : testNodes)
        {
          gameInfoNode->SetProperties({gameInfoProperty});
          auto gameInfoNodes = game->GetGameInfoNodes();

          REQUIRE( gameInfoNodes.size() == 1 );
          REQUIRE( gameInfoNodes.front() == gameInfoNode );

          gameInfoNode->RemoveAllProperties();
        }
      }
    }
  }

  GIVEN( "SgfcGame has multiple game info nodes" )
  {
    rootNode->SetProperties({gameInfoProperty});
    intermediateNode->SetProperties({gameInfoProperty});
    intermediateSiblingNode->SetProperties({gameInfoProperty});
    leafNode->SetProperties({gameInfoProperty});

    WHEN( "The root node hides the other game info nodes" )
    {
      auto gameInfoNodes = game->GetGameInfoNodes();

      THEN( "SgfcGame returns a collection that contains only the root node" )
      {
        REQUIRE( gameInfoNodes.size() == 1 );
        REQUIRE( gameInfoNodes.front() == rootNode );
      }
    }

    WHEN( "The intermediate node hides the leaf node" )
    {
      rootNode->RemoveAllProperties();
      auto gameInfoNodes = game->GetGameInfoNodes();

      THEN( "SgfcGame returns a collection that contains only the intermediate node and its sibling" )
      {
        REQUIRE( gameInfoNodes.size() == 2 );
        // The order is important - the search is performed depth-first
        REQUIRE( gameInfoNodes.front() == intermediateNode );
        REQUIRE( gameInfoNodes.back() == intermediateSiblingNode );
      }
    }

    WHEN( "The leaf node is not hidden by its ancestors" )
    {
      rootNode->RemoveAllProperties();
      intermediateNode->RemoveAllProperties();
      auto gameInfoNodes = game->GetGameInfoNodes();

      THEN( "SgfcGame returns a collection that contains the leaf node and the intermediate sibling" )
      {
        REQUIRE( gameInfoNodes.size() == 2 );
        // The order is important - the search is performed depth-first
        REQUIRE( gameInfoNodes.front() == leafNode );
        REQUIRE( gameInfoNodes.back() == intermediateSiblingNode );
      }
    }
  }
}

SCENARIO( "SgfcGame creates an ISgfcGameInfo object", "[document]" )
{
  auto game = std::make_shared<SgfcGame>();
  SgfcTreeBuilder treeBuilder(game);

  auto rootNode = std::make_shared<SgfcNode>();
  auto intermediateNode = std::make_shared<SgfcNode>();
  auto intermediateSiblingNode = std::make_shared<SgfcNode>();
  auto leafNode = std::make_shared<SgfcNode>();

  game->SetRootNode(rootNode);
  treeBuilder.SetFirstChild(rootNode, intermediateNode);
  treeBuilder.SetNextSibling(intermediateNode, intermediateSiblingNode);
  treeBuilder.SetFirstChild(intermediateNode, leafNode);

  GIVEN( "SgfcGame has no root node and no game info nodes" )
  {
    game->SetRootNode(nullptr);

    WHEN( "SgfcGame creates the ISgfcGameInfo object" )
    {
      auto gameInfo = game->CreateGameInfo();

      THEN( "The ISgfcGameInfo object contains default values" )
      {
        AssertGoGameInfoHasDefaultValues(gameInfo);
      }
    }
  }

  GIVEN( "SgfcGame has an empty root node and no game info nodes" )
  {
    WHEN( "SgfcGame creates the ISgfcGameInfo object" )
    {
      auto gameInfo = game->CreateGameInfo();

      THEN( "The ISgfcGameInfo object contains default values" )
      {
        AssertGoGameInfoHasDefaultValues(gameInfo);
      }
    }
  }

  GIVEN( "SgfcGame has a non-empty root node and no game info nodes" )
  {
    SgfcGameType gameType = GENERATE( SgfcGameType::Go, SgfcGameType::Backgammon );
    SgfcBoardSize boardSize = { 3, 10 };
    bool setupWithTypedProperties = GENERATE( true, false );
    SetupNodeWithGameAndBoardSizeProperties(rootNode, gameType, boardSize, setupWithTypedProperties);

    WHEN( "SgfcGame creates the ISgfcGameInfo object" )
    {
      auto gameInfo = game->CreateGameInfo();

      THEN( "The ISgfcGameInfo object contains the root property values" )
      {
        AssertGameInfoHasRootPropertyValues(gameInfo, gameType, SgfcUtility::MapGameTypeToNumberValue(gameType), boardSize);
      }
    }
  }

  GIVEN( "SgfcGame has a single game info node" )
  {
    SgfcSimpleText propertyValue = "foo";
    auto gameInfoProperty = CreateSimpleTextProperty(SgfcPropertyType::US, propertyValue);
    std::vector<std::shared_ptr<ISgfcNode>> testNodes = { rootNode, intermediateNode, intermediateSiblingNode, leafNode };

    WHEN( "SgfcGame creates the ISgfcGameInfo object" )
    {
      THEN( "The ISgfcGameInfo object contains the game info property values" )
      {
        // TODO: Get this to work with GENERATE_COPY
        for (auto gameInfoNode : testNodes)
        {
          gameInfoNode->SetProperties({gameInfoProperty});
          auto gameInfo = game->CreateGameInfo();

          REQUIRE( gameInfo->GetRecorderName() == propertyValue );

          gameInfoNode->RemoveAllProperties();
        }
      }
    }
  }

  GIVEN( "SgfcGame has multiple game info nodes" )
  {
    SgfcSimpleText propertyValueRoot = "root";
    auto gameInfoPropertyRoot = CreateSimpleTextProperty(SgfcPropertyType::US, propertyValueRoot);
    SgfcSimpleText propertyValueIntermediate = "intermediate";
    auto gameInfoPropertyIntermediate = CreateSimpleTextProperty(SgfcPropertyType::US, propertyValueIntermediate);
    SgfcSimpleText propertyValueIntermediateSibling = "intermediate-sibling";
    auto gameInfoPropertyIntermediateSibling = CreateSimpleTextProperty(SgfcPropertyType::US, propertyValueIntermediateSibling);
    SgfcSimpleText propertyValueLeaf = "leaf";
    auto gameInfoPropertyLeaf = CreateSimpleTextProperty(SgfcPropertyType::US, propertyValueLeaf);

    rootNode->SetProperties({gameInfoPropertyRoot});
    intermediateNode->SetProperties({gameInfoPropertyIntermediate});
    intermediateSiblingNode->SetProperties({gameInfoPropertyIntermediateSibling});
    leafNode->SetProperties({gameInfoPropertyLeaf});

    WHEN( "The root node hides the other game info nodes" )
    {
      auto gameInfo = game->CreateGameInfo();

      THEN( "The ISgfcGameInfo object contains the game info property values from the root node" )
      {
        REQUIRE( gameInfo->GetRecorderName() == propertyValueRoot );
      }
    }

    WHEN( "The intermediate node hides the leaf node" )
    {
      rootNode->RemoveAllProperties();
      auto gameInfo = game->CreateGameInfo();

      THEN( "The ISgfcGameInfo object contains the game info property values from the intermediate node" )
      {
        REQUIRE( gameInfo->GetRecorderName() == propertyValueIntermediate );
      }
    }

    WHEN( "The leaf node is not hidden by its ancestors" )
    {
      rootNode->RemoveAllProperties();
      intermediateNode->RemoveAllProperties();
      auto gameInfo = game->CreateGameInfo();

      THEN( "The ISgfcGameInfo object contains the game info property values from the leaf node" )
      {
        REQUIRE( gameInfo->GetRecorderName() == propertyValueLeaf );
      }
    }

    WHEN( "The intermediate sibling node is not hidden by its siblings" )
    {
      rootNode->RemoveAllProperties();
      intermediateNode->RemoveAllProperties();
      leafNode->RemoveAllProperties();
      auto gameInfo = game->CreateGameInfo();

      THEN( "The ISgfcGameInfo object contains the game info property values from the intermediate sibling node" )
      {
        REQUIRE( gameInfo->GetRecorderName() == propertyValueIntermediateSibling );
      }
    }
  }
}

SCENARIO( "SgfcGame writes an ISgfcGameInfo object", "[document]" )
{
  auto game = std::make_shared<SgfcGame>();
  SgfcTreeBuilder treeBuilder(game);

  auto rootNode = std::make_shared<SgfcNode>();
  auto intermediateNode = std::make_shared<SgfcNode>();
  auto intermediateSiblingNode = std::make_shared<SgfcNode>();
  auto leafNode = std::make_shared<SgfcNode>();

  game->SetRootNode(rootNode);
  treeBuilder.SetFirstChild(rootNode, intermediateNode);
  treeBuilder.SetNextSibling(intermediateNode, intermediateSiblingNode);
  treeBuilder.SetFirstChild(intermediateNode, leafNode);

  GIVEN( "SgfcGame has no root node" )
  {
    SgfcGameType gameType = SgfcGameType::Backgammon;
    SgfcBoardSize boardSize = { 3, 10 };
    bool setupWithTypedProperties = false;
    SetupNodeWithGameAndBoardSizeProperties(rootNode, gameType, boardSize, setupWithTypedProperties);
    auto gameInfo = game->CreateGameInfo();

    game->SetRootNode(nullptr);

    WHEN( "SgfcGame writes the ISgfcGameInfo object" )
    {
      game->WriteGameInfo(gameInfo);

      THEN( "The root node is created" )
      {
        auto newRootNode = game->GetRootNode();
        REQUIRE( newRootNode != nullptr );
        auto properties = newRootNode->GetProperties();
        REQUIRE( properties.size() == 2 );
        AssertPropertiesContainRootPropertyValues(properties, SgfcUtility::MapGameTypeToNumberValue(gameType), boardSize);
      }
    }
  }

  GIVEN( "SgfcGame has no game info node" )
  {
    SgfcGameType gameType = SgfcGameType::Go;
    SgfcBoardSize boardSize = { 15, 15 };
    bool setupWithTypedProperties = false;
    SetupNodeWithGameAndBoardSizeProperties(rootNode, gameType, boardSize, setupWithTypedProperties);
    auto propertyType = SgfcPropertyType::US;
    SgfcSimpleText recorderName = "foo";
    auto gameInfoProperty = CreateSimpleTextProperty(propertyType, recorderName);
    rootNode->AppendProperty(gameInfoProperty);

    auto gameInfo = game->CreateGameInfo();
    REQUIRE( gameInfo->GetRecorderName() == recorderName );

    game->SetRootNode(nullptr);

    WHEN( "SgfcGame writes the ISgfcGameInfo object" )
    {
      game->WriteGameInfo(gameInfo);

      THEN( "The game info properties are written to the root node" )
      {
        auto newRootNode = game->GetRootNode();
        REQUIRE( newRootNode != nullptr );
        auto properties = newRootNode->GetProperties();
        REQUIRE( properties.size() == 3 );
        AssertPropertiesContainRootPropertyValues(properties, SgfcUtility::MapGameTypeToNumberValue(gameType), boardSize);
        AssertPropertiesContainsGameInfoPropertyValue(properties, propertyType, recorderName);
      }
    }
  }

  GIVEN( "SgfcGame has a game info node" )
  {
    auto propertyType = SgfcPropertyType::US;
    SgfcSimpleText recorderName = "foo";
    auto gameInfoProperty = CreateSimpleTextProperty(propertyType, recorderName);
    leafNode->AppendProperty(gameInfoProperty);
    auto gameInfo = game->CreateGameInfo();
    REQUIRE( gameInfo->GetRecorderName() == recorderName );
    SgfcSimpleText newRecorderName = "bar";
    gameInfo->SetRecorderName(newRecorderName);

    WHEN( "SgfcGame writes the ISgfcGameInfo object" )
    {
      game->WriteGameInfo(gameInfo);

      THEN( "The game info properties are written to the game info node" )
      {
        auto leafNodeProperties = leafNode->GetProperties();
        REQUIRE( leafNodeProperties.size() == 1 );
        AssertPropertiesContainsGameInfoPropertyValue(leafNodeProperties, propertyType, newRecorderName);
        REQUIRE( rootNode->GetProperties().size() == 2 );
        REQUIRE( intermediateNode->GetProperties().size() == 0 );
        REQUIRE( intermediateSiblingNode->GetProperties().size() == 0 );
      }
    }
  }
}
