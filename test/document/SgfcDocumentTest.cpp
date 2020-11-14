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

// Library includes
#include <document/SgfcDocument.h>
#include <document/SgfcGame.h>

// SGFC includes
extern "C"
{
  #include <../sgfc/src/all.h>
}

// Unit test library includes
#include <catch2/catch.hpp>

// C++ Standard Library includes
#include <cstring>  //  needed for strlen

using namespace LibSgfcPlusPlus;


void SetupEmptySgfInfo(SGFInfo* sgfInfo, char* buffer, size_t bufferSize);
void AddEmptyRootNodeToSgfInfo(SGFInfo* sgfInfo, Node* sgfRootNode, TreeInfo* sgfTreeInfo);


SCENARIO( "SgfcDocument is constructed", "[document]" )
{
  GIVEN( "The SgfcDocument default constructor is used" )
  {
    WHEN( "SgfcDocument is constructed" )
    {
      THEN( "SgfcDocument is constructed successfully" )
      {
        REQUIRE_NOTHROW( SgfcDocument() );
      }
    }

    WHEN( "SgfcDocument is constructed" )
    {
      SgfcDocument document;

      THEN( "SgfcDocument has the expected default state" )
      {
        REQUIRE( document.IsEmpty() == true );
        REQUIRE( document.GetGames().size() == 0 );
      }
    }
  }

  GIVEN( "The SgfcDocument constructor taking an SGFInfo parameter is used" )
  {
    WHEN( "SgfcDocument is constructed with an SGFInfo object" )
    {
      char buffer[] = "";
      SGFInfo sgfInfo;
      SetupEmptySgfInfo(&sgfInfo, buffer, strlen(buffer) + 1);

      THEN( "SgfcDocument is constructed successfully" )
      {
        REQUIRE_NOTHROW( SgfcDocument(&sgfInfo) );
      }
    }

    WHEN( "SgfcDocument is constructed with an SGFInfo object" )
    {
      char buffer[] = "";
      SGFInfo sgfInfo;
      SetupEmptySgfInfo(&sgfInfo, buffer, strlen(buffer) + 1);

      SgfcDocument document(&sgfInfo);

      THEN( "SgfcDocument has the expected state" )
      {
        REQUIRE( document.IsEmpty() == true );
        REQUIRE( document.GetGames().size() == 0 );
      }
    }

    WHEN( "SgfcDocument is constructed with a nullptr SGFInfo object" )
    {
      THEN( "The SgfcDocument constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcDocument(nullptr),
          std::invalid_argument);
      }
    }
  }
}

SCENARIO( "SgfcDocument is constructed with SGF content", "[document]" )
{
  char buffer[] = "";
  SGFInfo sgfInfo;
  SetupEmptySgfInfo(&sgfInfo, buffer, strlen(buffer) + 1);

  GIVEN( "The SGF content contains a single game" )
  {
    Node sgfRootNode;
    TreeInfo sgfTreeInfo;
    AddEmptyRootNodeToSgfInfo(&sgfInfo, &sgfRootNode, &sgfTreeInfo);

    WHEN( "SgfcDocument is constructed" )
    {
      SgfcDocument document(&sgfInfo);

      THEN( "SgfcDocument contains one game" )
      {
        REQUIRE( document.IsEmpty() == false );
        REQUIRE( document.GetGames().size() == 1 );
      }
    }
  }

  GIVEN( "The SGF content contains multiple games" )
  {
    Node sgfRootNode1;
    TreeInfo sgfTreeInfo1;
    AddEmptyRootNodeToSgfInfo(&sgfInfo, &sgfRootNode1, &sgfTreeInfo1);
    Node sgfRootNode2;
    TreeInfo sgfTreeInfo2;
    AddEmptyRootNodeToSgfInfo(&sgfInfo, &sgfRootNode2, &sgfTreeInfo2);

    WHEN( "SgfcDocument is constructed" )
    {
      SgfcDocument document(&sgfInfo);

      THEN( "SgfcDocument contains multiple game" )
      {
        REQUIRE( document.IsEmpty() == false );
        REQUIRE( document.GetGames().size() == 2 );
      }
    }
  }

  // No more tests here. It is too complicated to manually set up an SGFInfo
  // object for all but the most simple scenarios. More complex SGF content
  // scenarios are tested in the SgfcDocumentReader unit tests.
}

SCENARIO( "SgfcDocument is configured with a list of games", "[document]" )
{
  std::vector<std::shared_ptr<ISgfcGame>> emptyGameList;
  std::vector<std::shared_ptr<ISgfcGame>> nonEmptyGameList =
  {
    std::shared_ptr<ISgfcGame>(new SgfcGame()),
    std::shared_ptr<ISgfcGame>(new SgfcGame()),
    std::shared_ptr<ISgfcGame>(new SgfcGame())
  };

  GIVEN( "SgfcDocument is configured with a list of games" )
  {
    SgfcDocument document;

    WHEN( "SgfcDocument is configured with an empty game list" )
    {
      document.SetGames(emptyGameList);
      emptyGameList.push_back(nullptr);

      THEN( "SgfcDocument makes a copy of the game list" )
      {
        REQUIRE( document.IsEmpty() == true );
        REQUIRE( document.GetGames() != emptyGameList );
      }
    }

    WHEN( "SgfcDocument is configured with a non-empty game list" )
    {
      document.SetGames(nonEmptyGameList);
      nonEmptyGameList.clear();

      THEN( "SgfcDocument makes a copy of the game list" )
      {
        REQUIRE( document.IsEmpty() == false );
        REQUIRE( document.GetGames() != nonEmptyGameList );
      }
    }
  }

  GIVEN( "The SgfcDocument contains no games" )
  {
    SgfcDocument document;

    WHEN( "SgfcDocument is configured with an empty game list" )
    {
      document.SetGames(emptyGameList);

      THEN( "SgfcDocument contains no games" )
      {
        REQUIRE( document.IsEmpty() == true );
        REQUIRE( document.GetGames().size() == 0 );
      }
    }

    WHEN( "SgfcDocument is configured with a non-empty game list" )
    {
      document.SetGames(nonEmptyGameList);

      THEN( "SgfcDocument contains the configured games" )
      {
        REQUIRE( document.IsEmpty() == false );
        REQUIRE( document.GetGames().size() == 3 );
      }
    }

    WHEN( "SgfcDocument is configured with a game list that contains duplicate elements" )
    {
      nonEmptyGameList.push_back(nonEmptyGameList.back());

      THEN( "SgfcDocument throws an exception" )
      {
        REQUIRE_THROWS_AS(
          document.SetGames(nonEmptyGameList),
          std::invalid_argument);
        REQUIRE( document.IsEmpty() == true );
      }
    }

    WHEN( "SgfcDocument is configured with a game list that contains a nullptr element" )
    {
      nonEmptyGameList.push_back(nullptr);

      THEN( "SgfcDocument throws an exception" )
      {
        REQUIRE_THROWS_AS(
          document.SetGames(nonEmptyGameList),
          std::invalid_argument);
        REQUIRE( document.IsEmpty() == true );
      }
    }
  }

  GIVEN( "The SgfcDocument contains one or more games" )
  {
    char buffer[] = "";
    SGFInfo sgfInfo;
    SetupEmptySgfInfo(&sgfInfo, buffer, strlen(buffer) + 1);

    Node sgfRootNode1;
    TreeInfo sgfTreeInfo1;
    AddEmptyRootNodeToSgfInfo(&sgfInfo, &sgfRootNode1, &sgfTreeInfo1);
    Node sgfRootNode2;
    TreeInfo sgfTreeInfo2;
    AddEmptyRootNodeToSgfInfo(&sgfInfo, &sgfRootNode2, &sgfTreeInfo2);

    SgfcDocument document(&sgfInfo);

    REQUIRE( document.IsEmpty() == false );
    REQUIRE( document.GetGames().size() == 2 );

    WHEN( "SgfcDocument is configured with an empty game list" )
    {
      document.SetGames(emptyGameList);

      THEN( "SgfcDocument replaces the previous list of games with an empty list of games" )
      {
        REQUIRE( document.IsEmpty() == true );
        REQUIRE( document.GetGames().size() == 0 );
      }
    }

    WHEN( "SgfcDocument is configured with a non-empty game list" )
    {
      document.SetGames(nonEmptyGameList);

      THEN( "SgfcDocument replaces the previous list of games with the new list of games" )
      {
        REQUIRE( document.IsEmpty() == false );
        REQUIRE( document.GetGames().size() == 3 );
      }
    }
  }
}

SCENARIO( "A game is added to SgfcDocument", "[document]" )
{
  SgfcDocument document;
  auto game = std::shared_ptr<ISgfcGame>(new SgfcGame());

  GIVEN( "The document contains no games" )
  {
    WHEN( "A game is added to SgfcDocument" )
    {
      document.AppendGame(game);

      THEN( "SgfcDocument contains the added game" )
      {
        REQUIRE( document.IsEmpty() == false );
        auto gameList = document.GetGames();
        REQUIRE( gameList.size() == 1 );
        REQUIRE( gameList.back() == game );
      }
    }
  }

  GIVEN( "The document already contains games" )
  {
    std::vector<std::shared_ptr<ISgfcGame>> initialGameList =
    {
      std::shared_ptr<ISgfcGame>(new SgfcGame()),
      std::shared_ptr<ISgfcGame>(new SgfcGame()),
      std::shared_ptr<ISgfcGame>(new SgfcGame())
    };
    document.SetGames(initialGameList);

    WHEN( "A game is added to SgfcDocument" )
    {
      document.AppendGame(game);

      THEN( "SgfcDocument adds the game to the end of the game list" )
      {
        REQUIRE( document.IsEmpty() == false );
        auto gameList = document.GetGames();
        REQUIRE( gameList.size() == 4 );
        REQUIRE( gameList.back() == game );
        gameList.pop_back();
        REQUIRE( gameList == initialGameList );
      }
    }

    WHEN( "A game is added that is already part of the SgfcDocument" )
    {
      THEN( "SgfcDocument throws an exception" )
      {
        REQUIRE_THROWS_AS(
          document.AppendGame(initialGameList.back()),
          std::invalid_argument);
        REQUIRE( document.GetGames() == initialGameList );
      }
    }
  }

  GIVEN( "A nullptr argument is passed to the add function" )
  {
    WHEN( "A nullptr argument is passed to the add function" )
    {
      THEN( "SgfcDocument throws an exception" )
      {
        REQUIRE_THROWS_AS(
          document.AppendGame(nullptr),
          std::invalid_argument);
        REQUIRE( document.IsEmpty() == true );
      }
    }
  }
}

SCENARIO( "A game is removed from SgfcDocument", "[document]" )
{
  std::vector<std::shared_ptr<ISgfcGame>> initialGameList =
  {
    std::shared_ptr<ISgfcGame>(new SgfcGame()),
    std::shared_ptr<ISgfcGame>(new SgfcGame()),
    std::shared_ptr<ISgfcGame>(new SgfcGame())
  };
  SgfcDocument document;

  GIVEN( "The document contains the game to be removed" )
  {
    auto gameToRemove = initialGameList.back();
    document.SetGames(initialGameList);

    WHEN( "A game is removed from SgfcDocument" )
    {
      document.RemoveGame(gameToRemove);

      THEN( "SgfcDocument removes the game" )
      {
        REQUIRE( document.IsEmpty() == false );
        auto gameList = document.GetGames();
        REQUIRE( gameList.size() == 2 );
        REQUIRE( gameList.back() != gameToRemove );
        gameList.push_back(gameToRemove);
        REQUIRE( gameList == initialGameList );
      }
    }
  }

  GIVEN( "The document does not contain the game to be removed" )
  {
    auto gameToRemove = std::shared_ptr<ISgfcGame>(new SgfcGame());
    document.SetGames(initialGameList);

    WHEN( "The missing game is removed from SgfcDocument" )
    {
      THEN( "SgfcDocument throws an exception" )
      {
        REQUIRE_THROWS_AS(
          document.RemoveGame(gameToRemove),
          std::invalid_argument);
        REQUIRE( document.GetGames() == initialGameList );
      }
    }
  }

  GIVEN( "The document contains games" )
  {
    WHEN( "All games are individually removed from the document" )
    {
      document.SetGames(initialGameList);
      for (const auto& gameToRemove : initialGameList)
        document.RemoveGame(gameToRemove);

      THEN( "The document becomes empty after removing the last game" )
      {
        REQUIRE( document.IsEmpty() == true );
        REQUIRE( document.GetGames().size() == 0 );
      }
    }

    WHEN( "Only some of the games are removed from the document" )
    {
      document.SetGames(initialGameList);
      document.RemoveGame(initialGameList.front());
      document.RemoveGame(initialGameList.back());

      THEN( "The document remains non-empty after removing the game" )
      {
        REQUIRE( document.IsEmpty() == false );
        REQUIRE( document.GetGames().size() == 1 );
      }
    }
  }

  GIVEN( "A nullptr argument is passed to the remove function" )
  {
    document.SetGames(initialGameList);

    WHEN( "A nullptr argument is passed to the remove function" )
    {
      THEN( "SgfcDocument throws an exception" )
      {
        REQUIRE_THROWS_AS(
          document.RemoveGame(nullptr),
          std::invalid_argument);
        REQUIRE( document.GetGames() == initialGameList );
      }
    }
  }
}

SCENARIO( "All games are removed from SgfcDocument", "[document]" )
{
  GIVEN( "The document contains games to be removed" )
  {
    std::vector<std::shared_ptr<ISgfcGame>> initialGameList =
    {
      std::shared_ptr<ISgfcGame>(new SgfcGame()),
      std::shared_ptr<ISgfcGame>(new SgfcGame()),
      std::shared_ptr<ISgfcGame>(new SgfcGame())
    };
    SgfcDocument document;
    document.SetGames(initialGameList);

    WHEN( "All games are removed from the document" )
    {
      document.RemoveAllGames();

      THEN( "The document becomes empty" )
      {
        REQUIRE( document.IsEmpty() == true );
        REQUIRE( document.GetGames().size() == 0 );
      }
    }
  }

  GIVEN( "The document does not contain any games to be removed" )
  {
    SgfcDocument document;

    WHEN( "All games are removed from the document" )
    {
      document.RemoveAllGames();

      THEN( "The document remains empty" )
      {
        REQUIRE( document.IsEmpty() == true );
        REQUIRE( document.GetGames().size() == 0 );
      }
    }
  }
}

void SetupEmptySgfInfo(SGFInfo* sgfInfo, char* buffer, size_t bufferSize)
{
  sgfInfo->buffer = buffer;
  sgfInfo->start = sgfInfo->buffer;
  sgfInfo->b_end = sgfInfo->start + bufferSize;
  sgfInfo->root = nullptr;
  sgfInfo->tree = nullptr;
}

void AddEmptyRootNodeToSgfInfo(SGFInfo* sgfInfo, Node* sgfRootNode, TreeInfo* sgfTreeInfo)
{
  Node* nextRootNode = sgfInfo->root;
  TreeInfo* nextTreeInfo = sgfInfo->tree;

  while (nextRootNode)
  {
    if (nextRootNode->sibling == nullptr)
      break;

    nextRootNode = nextRootNode->sibling;
    nextTreeInfo = nextTreeInfo->next;
  }

  if (nextRootNode == nullptr)
  {
    sgfInfo->root = sgfRootNode;
    sgfInfo->tree = sgfTreeInfo;
  }
  else
  {
    nextRootNode->sibling = sgfRootNode;
    nextTreeInfo->next = sgfTreeInfo;
  }

  // When root node has no properties, probing for game type and board size
  // by SgfcPropertyDecoder succeeds. Also property parsing by SgfcDocument
  // succeeds.
  sgfRootNode->prop = nullptr;

  // When root node has no child, recursive parsing of the tree by SgfcDocument
  // succeeds
  sgfRootNode->child = nullptr;

  // When root node and tree info have no sibling/next, iteration by
  // SgfcDocument stops
  sgfRootNode->sibling = nullptr;
  sgfTreeInfo->next = nullptr;

}
