// Library includes
#include "../TestDataGenerator.h"
#include <document/SgfcGame.h>
#include <document/SgfcNode.h>
#include <document/SgfcProperty.h>
#include <document/SgfcTreeBuilder.h>
#include <document/typedproperty/SgfcBoardSizeProperty.h>
#include <document/typedproperty/SgfcGameTypeProperty.h>
#include <ISgfcNumberPropertyValue.h>
#include <ISgfcPropertyFactory.h>
#include <ISgfcPropertyValueFactory.h>
#include <SgfcConstants.h>
#include <SgfcPlusPlusFactory.h>
#include <SgfcUtility.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;


void SetupGameWithGameAndBoardSizeProperties(std::shared_ptr<SgfcGame> game, SgfcGameType gameType, SgfcBoardSize boardSize);
void SetupGameWithBoardSizeProperty(std::shared_ptr<SgfcGame> game, SgfcBoardSize boardSize);
void AddGameTypeProperty(SgfcGameType gameType, std::vector<std::shared_ptr<ISgfcProperty>>& properties);
void AddBoardSizeProperty(SgfcBoardSize boardSize, std::vector<std::shared_ptr<ISgfcProperty>>& properties);


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
    auto gameTypePropertyWithoutValue = propertyFactory->CreateGameTypeProperty();
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
    SgfcNumber gameTypeAsNumberNotDefinedInSgfStandard = 1000;
    auto gameTypePropertyValueNotDefinedInSgfStandard = propertyValueFactory->CreateNumberPropertyValue(
      gameTypeAsNumberNotDefinedInSgfStandard);
    auto gameTypePropertyWithValueNotDefinedInSgfStandard = propertyFactory->CreateGameTypeProperty(
      gameTypePropertyValueNotDefinedInSgfStandard);
    properties.push_back(gameTypePropertyWithValueNotDefinedInSgfStandard);

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
    SgfcGameType gameTypeDefinedInSgfStandard = SgfcGameType::Kuba;
    auto gameTypePropertyValueDefinedInSgfStandard = propertyValueFactory->CreateNumberPropertyValue(
      SgfcUtility::MapGameTypeToNumberValue(gameTypeDefinedInSgfStandard));
    auto gameTypePropertyWithValueDefinedInSgfStandard = propertyFactory->CreateGameTypeProperty(
      gameTypePropertyValueDefinedInSgfStandard);
    properties.push_back(gameTypePropertyWithValueDefinedInSgfStandard);

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

  GIVEN( "The game has a property of type SgfcPropertyType::GM but the object type is not an instance of ISgfcGameTypeProperty" )
  {
    SgfcGameType gameTypeDefinedInSgfStandard = SgfcGameType::Gipf;
    auto gameTypePropertyValueDefinedInSgfStandard = propertyValueFactory->CreateNumberPropertyValue(
      SgfcUtility::MapGameTypeToNumberValue(gameTypeDefinedInSgfStandard));
    std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues = { gameTypePropertyValueDefinedInSgfStandard };

    auto gameTypePropertyWithWrongType = std::shared_ptr<ISgfcProperty>(new SgfcProperty(
      SgfcPropertyType::GM,
      std::string("GM"),
      propertyValues));
    properties.push_back(gameTypePropertyWithWrongType);

    game->SetRootNode(node);
    node->SetProperties(properties);

    WHEN( "SgfcGame is queried for the game type" )
    {
      THEN( "SgfcGame throws an exception" )
      {
        REQUIRE_THROWS_AS(
          game->GetGameType(),
          std::logic_error);
        REQUIRE_THROWS_AS(
          game->GetGameTypeAsNumber(),
          std::logic_error);
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
    auto testData = GENERATE( from_range(TestDataGenerator::GetValidBoardSizes()) );

    SetupGameWithGameAndBoardSizeProperties(game, std::get<1>(testData), std::get<0>(testData));

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
    auto testData = GENERATE( from_range(TestDataGenerator::GetInvalidBoardSizes()) );

    SetupGameWithGameAndBoardSizeProperties(game, std::get<1>(testData), std::get<0>(testData));

    WHEN( "SgfcGame is queried for the board size" )
    {
      THEN( "SgfcGame returns SgfcConstants::BoardSizeInvalid" )
      {
        REQUIRE( game->HasBoardSize() == false );
        REQUIRE( game->GetBoardSize() == SgfcConstants::BoardSizeInvalid );
      }
    }
  }

  GIVEN( "The game has a property of type SgfcPropertyType::SZ but the object type is not an instance of ISgfcBoardSizeProperty" )
  {
    auto boardSizePropertyValue = propertyValueFactory->CreateNumberPropertyValue(
      SgfcConstants::BoardSizeDefaultGo.Columns);
    std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues = { boardSizePropertyValue };

    auto boardSizePropertyWithWrongType = std::shared_ptr<ISgfcProperty>(new SgfcProperty(
      SgfcPropertyType::SZ,
      std::string("SZ"),
      propertyValues));
    properties.push_back(boardSizePropertyWithWrongType);

    game->SetRootNode(node);
    node->SetProperties(properties);

    WHEN( "SgfcGame is queried for the board size" )
    {
      THEN( "SgfcGame throws an exception" )
      {
        REQUIRE_THROWS_AS(
          game->HasBoardSize(),
          std::logic_error);
        REQUIRE_THROWS_AS(
          game->GetBoardSize(),
          std::logic_error);
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

    SetupGameWithBoardSizeProperty(game, std::get<0>(testData));

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

    SetupGameWithBoardSizeProperty(game, std::get<0>(testData));

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

void SetupGameWithGameAndBoardSizeProperties(std::shared_ptr<SgfcGame> game, SgfcGameType gameType, SgfcBoardSize boardSize)
{
  std::vector<std::shared_ptr<ISgfcProperty>> properties;
  AddGameTypeProperty(gameType, properties);
  AddBoardSizeProperty(boardSize, properties);

  auto rootNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  rootNode->SetProperties(properties);

  game->SetRootNode(rootNode);
}

void SetupGameWithBoardSizeProperty(std::shared_ptr<SgfcGame> game, SgfcBoardSize boardSize)
{
  std::vector<std::shared_ptr<ISgfcProperty>> properties;
  AddBoardSizeProperty(boardSize, properties);

  auto rootNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  rootNode->SetProperties(properties);

  game->SetRootNode(rootNode);
}

void AddGameTypeProperty(SgfcGameType gameType, std::vector<std::shared_ptr<ISgfcProperty>>& properties)
{
  auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
  auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();

  auto gameTypePropertyValue = propertyValueFactory->CreateNumberPropertyValue(
    SgfcUtility::MapGameTypeToNumberValue(gameType));
  auto gameTypeProperty = propertyFactory->CreateGameTypeProperty(
    gameTypePropertyValue);

  properties.push_back(gameTypeProperty);
}

void AddBoardSizeProperty(SgfcBoardSize boardSize, std::vector<std::shared_ptr<ISgfcProperty>>& properties)
{
  auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
  auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();

  std::shared_ptr<ISgfcBoardSizeProperty> boardSizeProperty;
  if (boardSize.IsSquare())
  {
    auto boardSizePropertyValue = propertyValueFactory->CreateNumberPropertyValue(
      boardSize.Columns);
    boardSizeProperty = propertyFactory->CreateBoardSizeProperty(
      boardSizePropertyValue);
  }
  else
  {
    auto boardSizePropertyValue = propertyValueFactory->CreateComposedNumberAndNumberPropertyValue(
      boardSize.Columns,
      boardSize.Rows);
    boardSizeProperty = propertyFactory->CreateBoardSizeProperty(
      boardSizePropertyValue);
  }

  properties.push_back(boardSizeProperty);
}
