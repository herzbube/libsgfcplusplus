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

// Library includes
#include <document/SgfcTreeBuilder.h>
#include <document/SgfcGame.h>
#include <document/SgfcNode.h>

// Unit test library includes
#include <catch2/catch_test_macros.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcTreeBuilder is constructed", "[document]" )
{
  GIVEN( "The SgfcTreeBuilder constructor is used" )
  {
    WHEN( "SgfcTreeBuilder is constructed with a valid SgfcGame object" )
    {
      std::shared_ptr<SgfcGame> game = std::shared_ptr<SgfcGame>(new SgfcGame());

      THEN( "SgfcTreeBuilder is constructed successfully" )
      {
        REQUIRE_NOTHROW( SgfcTreeBuilder(game) );
      }
    }

    WHEN( "SgfcTreeBuilder is constructed with a nullptr SgfcGame object" )
    {
      std::shared_ptr<SgfcGame> game = std::shared_ptr<SgfcGame>(nullptr);

      THEN( "The SgfcTreeBuilder constructor throws an exception" )
      {
        REQUIRE_THROWS_AS(
          SgfcTreeBuilder(game),
          std::invalid_argument);
      }
    }

    WHEN( "SgfcTreeBuilder is queried for its associated SgfcGame object" )
    {
      std::shared_ptr<SgfcGame> game = std::shared_ptr<SgfcGame>(new SgfcGame());
      SgfcTreeBuilder treeBuilder(game);

      THEN( "SgfcTreeBuilder returns the SgfcGame object that was used for construction" )
      {
        REQUIRE( treeBuilder.GetGame().lock() == game );
      }
    }
  }
}

// rootNode
// +-- nodeA
// |   +-- nodeA1
// |   +-- nodeA2
// |   |   +-- nodeA2a
// |   +-- nodeA3
// +-- nodeB
//     +-- nodeB1
//
// unlinkedNode
std::shared_ptr<SgfcGame> game;
std::shared_ptr<SgfcNode> rootNode;
std::shared_ptr<SgfcNode> nodeA;
std::shared_ptr<SgfcNode> nodeA1;
std::shared_ptr<SgfcNode> nodeA2;
std::shared_ptr<SgfcNode> nodeA2a;
std::shared_ptr<SgfcNode> nodeA3;
std::shared_ptr<SgfcNode> nodeB;
std::shared_ptr<SgfcNode> nodeB1;
std::shared_ptr<SgfcNode> unlinkedNode;

void CreateGameTree()
{
  game = std::shared_ptr<SgfcGame>(new SgfcGame());
  rootNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  nodeA = std::shared_ptr<SgfcNode>(new SgfcNode());
  nodeA1 = std::shared_ptr<SgfcNode>(new SgfcNode());
  nodeA2 = std::shared_ptr<SgfcNode>(new SgfcNode());
  nodeA2a = std::shared_ptr<SgfcNode>(new SgfcNode());
  nodeA3 = std::shared_ptr<SgfcNode>(new SgfcNode());
  nodeB = std::shared_ptr<SgfcNode>(new SgfcNode());
  nodeB1 = std::shared_ptr<SgfcNode>(new SgfcNode());
  unlinkedNode = std::shared_ptr<SgfcNode>(new SgfcNode());

  game->SetRootNode(rootNode);

  rootNode->SetFirstChild(nodeA);
  nodeA->SetNextSibling(nodeB);
  nodeA->SetParent(rootNode);
  nodeB->SetParent(rootNode);

  nodeA->SetFirstChild(nodeA1);
  nodeA1->SetNextSibling(nodeA2);
  nodeA2->SetNextSibling(nodeA3);
  nodeA1->SetParent(nodeA);
  nodeA2->SetParent(nodeA);
  nodeA3->SetParent(nodeA);

  nodeA2->SetFirstChild(nodeA2a);
  nodeA2a->SetParent(nodeA2);

  nodeB->SetFirstChild(nodeB1);
  nodeB1->SetParent(nodeB);
}

SCENARIO( "SgfcTreeBuilder sets the first child of a node", "[document]" )
{
  CreateGameTree();
  SgfcTreeBuilder treeBuilder(game);

  GIVEN( "The SetFirstChild operation is invoked with invalid arguments" )
  {
    WHEN( "The node argument is nullptr" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.SetFirstChild(nullptr, unlinkedNode),
          std::invalid_argument);
      }
    }

    WHEN( "The new first child node is an ancestor of the node" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.SetFirstChild(nodeA1, nodeA),
          std::invalid_argument);
      }
    }

    WHEN( "The new first child node is equal to the node" )
    {
      REQUIRE_THROWS_AS(
        treeBuilder.SetFirstChild(nodeA1, nodeA1),
        std::invalid_argument);
    }
  }

  GIVEN( "The SetFirstChild operation is invoked with no content below the node" )
  {
    WHEN( "The new first child node is nullptr" )
    {
      THEN( "SgfcTreeBuilder does nothing" )
      {
        REQUIRE( nodeA1->HasChildren() == false );

        treeBuilder.SetFirstChild(nodeA1, nullptr);

        REQUIRE( nodeA1->HasChildren() == false );
        REQUIRE( nodeA1->GetFirstChild() == nullptr );
      }
    }

    WHEN( "The new first child node is not nullptr" )
    {
      THEN( "SgfcTreeBuilder sets the new first child node as the node's first child" )
      {
        REQUIRE( nodeA1->HasChildren() == false );

        treeBuilder.SetFirstChild(nodeA1, unlinkedNode);

        REQUIRE( nodeA1->HasChildren() == true );

        REQUIRE( nodeA1->GetFirstChild() == unlinkedNode );
        REQUIRE( nodeA1->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA1 );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
      }
    }
  }

  GIVEN( "The SetFirstChild operation is invoked with content below the node" )
  {
    WHEN( "The new first child node is nullptr" )
    {
      THEN( "SgfcTreeBuilder replaces the content below the node with nothing" )
      {
        REQUIRE( nodeA->HasChildren() == true );
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );
        REQUIRE( nodeA1->HasParent() == true );
        REQUIRE( nodeA2->HasParent() == true );
        REQUIRE( nodeA3->HasParent() == true );

        treeBuilder.SetFirstChild(nodeA, nullptr);

        REQUIRE( nodeA->HasChildren() == false );
        REQUIRE( nodeA->GetFirstChild() == nullptr );
        REQUIRE( nodeA->GetLastChild() == nullptr );
        REQUIRE( nodeA1->HasParent() == false );
        REQUIRE( nodeA2->HasParent() == false );
        REQUIRE( nodeA3->HasParent() == false );
        // SetFirstChild not only removes nodeA1 - nodeA3 from the game tree,
        // it also breaks the nextSibling linkage between these nodes
        REQUIRE( nodeA1->GetNextSibling() == nullptr );
        REQUIRE( nodeA2->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new first child node is not nullptr" )
    {
      THEN( "SgfcTreeBuilder replaces the content below the node with the new first child node" )
      {
        REQUIRE( nodeA->HasChildren() == true );
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );
        REQUIRE( nodeA1->HasParent() == true );
        REQUIRE( nodeA2->HasParent() == true );
        REQUIRE( nodeA3->HasParent() == true );

        treeBuilder.SetFirstChild(nodeA, unlinkedNode);

        REQUIRE( nodeA->HasChildren() == true );
        REQUIRE( nodeA->GetFirstChild() == unlinkedNode );
        REQUIRE( nodeA->GetLastChild() == unlinkedNode );
        REQUIRE( nodeA1->HasParent() == false );
        REQUIRE( nodeA2->HasParent() == false );
        REQUIRE( nodeA3->HasParent() == false );
        // SetFirstChild not only removes nodeA1 - nodeA3 from the game tree,
        // it also breaks the nextSibling linkage between these nodes
        REQUIRE( nodeA1->GetNextSibling() == nullptr );
        REQUIRE( nodeA2->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nullptr );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );
      }
    }
  }

  GIVEN( "The SetFirstChild operation is invoked with nodes that originate from varying locations" )
  {
    WHEN( "The new first child node is already the node's first child" )
    {
      THEN( "SgfcTreeBuilder does nothing" )
      {
        REQUIRE( nodeA->HasChildren() == true );

        treeBuilder.SetFirstChild(nodeA, nodeA1);

        REQUIRE( nodeA->HasChildren() == true );

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA1->HasParent() == true );
        REQUIRE( nodeA1->GetParent() == nodeA );
        // Normally SetFirstChild replaces everything below the node with the
        // new first child. This does NOT happen here because this is a no-op:
        // nodeA2 and nodeA3 remain children of nodeA. Compare to the next
        // test case.
        REQUIRE( nodeA2->HasParent() == true );
        REQUIRE( nodeA3->HasParent() == true );
        REQUIRE( nodeA2->GetParent() == nodeA );
        REQUIRE( nodeA3->GetParent() == nodeA );
        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
      }
    }

    WHEN( "The new first child node is already a child of the node" )
    {
      THEN( "SgfcTreeBuilder moves the new first child node and relinks the game tree below the node" )
      {
        REQUIRE( nodeA->HasChildren() == true );
        REQUIRE( nodeA1->HasParent() == true );
        REQUIRE( nodeA2->HasParent() == true );
        REQUIRE( nodeA3->HasParent() == true );

        treeBuilder.SetFirstChild(nodeA, nodeA2);

        REQUIRE( nodeA->HasChildren() == true );
        REQUIRE( nodeA1->HasParent() == false );
        REQUIRE( nodeA3->HasParent() == false );
        // SetFirstChild not only removes nodeA1 and nodeA3 from the game tree,
        // it also breaks the nextSibling linkage between these nodes
        REQUIRE( nodeA1->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nullptr );

        REQUIRE( nodeA->GetFirstChild() == nodeA2 );
        REQUIRE( nodeA2->HasParent() == true );
        REQUIRE( nodeA2->GetParent() == nodeA );
        REQUIRE( nodeA2->GetNextSibling() == nullptr );
      }
    }

    WHEN( "The new first child node is part of the game tree in some other location" )
    {
      THEN( "SgfcTreeBuilder moves the new first child node and relinks the game tree in the old location" )
      {
        treeBuilder.SetFirstChild(nodeB, nodeA);

        REQUIRE( rootNode->GetFirstChild() == nodeB );
        REQUIRE( nodeB->GetFirstChild() == nodeA );
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetNextSibling() == nullptr );
        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA2->GetFirstChild() == nodeA2a );

        REQUIRE( nodeB1->HasParent() == false );
        REQUIRE( nodeB1->GetParent() == nullptr );
      }
    }
  }
}

SCENARIO( "SgfcTreeBuilder sets the last child of a node", "[document]" )
{
  CreateGameTree();
  SgfcTreeBuilder treeBuilder(game);

  GIVEN( "The AppendChild operation is invoked with invalid arguments" )
  {
    WHEN( "The node argument is nullptr" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.AppendChild(nullptr, unlinkedNode),
          std::invalid_argument);
      }
    }

    WHEN( "The new last child node argument is nullptr" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.AppendChild(nodeA, nullptr),
          std::invalid_argument);
      }
    }

    WHEN( "The new last child node is an ancestor of the node" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.AppendChild(nodeA1, nodeA),
          std::invalid_argument);
      }
    }

    WHEN( "The new last child node is equal to the node" )
    {
      REQUIRE_THROWS_AS(
        treeBuilder.AppendChild(nodeA1, nodeA1),
        std::invalid_argument);
    }
  }

  GIVEN( "The AppendChild operation is invoked with varying existing content below the node" )
  {
    WHEN( "The node has no child nodes" )
    {
      THEN( "SgfcTreeBuilder sets the new last child node as the node's first and last child" )
      {
        // ------------------------------------------------------------
        // Keep the test case the same as the corresponding test case for
        // InsertChild() below
        // ------------------------------------------------------------

        REQUIRE( nodeA1->HasChildren() == false );

        treeBuilder.AppendChild(nodeA1, unlinkedNode);

        REQUIRE( nodeA1->HasChildren() == true );

        REQUIRE( nodeA1->GetFirstChild() == unlinkedNode );
        REQUIRE( nodeA1->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA1 );

        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The node has child nodes" )
    {
      THEN( "SgfcTreeBuilder sets the new last child node as the node's last child" )
      {
        // ------------------------------------------------------------
        // Keep the test case the same as the corresponding test case for
        // InsertChild() below
        // ------------------------------------------------------------

        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeB1 );

        treeBuilder.AppendChild(nodeB, unlinkedNode);

        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeB );

        REQUIRE( nodeB1->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeB1 );
        REQUIRE( nodeB1->GetPreviousSibling() == nullptr );
      }
    }
  }

  GIVEN( "The AppendChild operation is invoked with nodes that originate from varying locations" )
  {
    WHEN( "The new last child node is an unlinked node" )
    {
      THEN( "SgfcTreeBuilder sets the new last child node as the node's last child" )
      {
        // ------------------------------------------------------------
        // Keep the test case the same as the corresponding test case for
        // InsertChild() below
        // ------------------------------------------------------------

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.AppendChild(nodeA, unlinkedNode);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA3 );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new last child node is part of the game tree in some other location" )
    {
      THEN( "SgfcTreeBuilder moves the new last child node and relinks the game tree in the old location" )
      {
        // ------------------------------------------------------------
        // Keep the test case the same as the corresponding test case for
        // InsertChild() below
        // ------------------------------------------------------------

        REQUIRE( rootNode->GetFirstChild() == nodeA );
        REQUIRE( rootNode->GetLastChild() == nodeB );
        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeB1 );

        treeBuilder.AppendChild(nodeB, nodeA);

        REQUIRE( rootNode->GetFirstChild() == nodeB );
        REQUIRE( rootNode->GetLastChild() == nodeB );
        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeA );

        REQUIRE( nodeB1->GetNextSibling() == nodeA );
        REQUIRE( nodeA->GetNextSibling() == nullptr );
        REQUIRE( nodeA->GetPreviousSibling() == nodeB1 );
        REQUIRE( nodeB1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new last child node is already the node's last child" )
    {
      THEN( "SgfcTreeBuilder does nothing" )
      {
        // ------------------------------------------------------------
        // Keep the test case the same as the corresponding test case for
        // InsertChild() below
        // ------------------------------------------------------------

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.AppendChild(nodeA, nodeA3);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new last child node is already a child of the node" )
    {
      THEN( "SgfcTreeBuilder moves the new last child node and relinks the game tree below the node" )
      {
        // ------------------------------------------------------------
        // Keep the test case the same as the corresponding test case for
        // InsertChild() below
        // ------------------------------------------------------------

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.AppendChild(nodeA, nodeA1);

        REQUIRE( nodeA->GetFirstChild() == nodeA2 );
        REQUIRE( nodeA->GetLastChild() == nodeA1 );

        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nodeA1 );
        REQUIRE( nodeA1->GetNextSibling() == nullptr );
        REQUIRE( nodeA1->GetPreviousSibling() == nodeA3 );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );
      }
    }
  }
}

SCENARIO( "SgfcTreeBuilder inserts a child to a node", "[document]" )
{
  CreateGameTree();
  SgfcTreeBuilder treeBuilder(game);

  GIVEN( "The InsertChild operation is invoked with invalid arguments" )
  {
    WHEN( "The node argument is nullptr" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.InsertChild(nullptr, unlinkedNode, nodeA1),
          std::invalid_argument);
      }
    }

    WHEN( "The new child node argument is nullptr" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.InsertChild(nodeA, nullptr, nodeA1),
          std::invalid_argument);
      }
    }

    WHEN( "The reference child node is not nullptr but it's not a child of the node" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.InsertChild(nodeA, unlinkedNode, nodeB1),
          std::invalid_argument);
      }
    }

    WHEN( "The new child node is an ancestor of the node" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.InsertChild(nodeA1, nodeA, nullptr),
          std::invalid_argument);
      }
    }

    WHEN( "The new child node is equal to the node" )
    {
      REQUIRE_THROWS_AS(
        treeBuilder.InsertChild(nodeA, nodeA, nodeA1),
        std::invalid_argument);
    }
  }

  GIVEN( "The InsertChild operation is invoked with varying existing content below the node" )
  {
    WHEN( "The node has no child nodes" )
    {
      THEN( "SgfcTreeBuilder sets the new child node as the node's first and last child" )
      {
        // ------------------------------------------------------------
        // Keep the test case the same as the corresponding test case for
        // AppendChild() above
        // ------------------------------------------------------------

        REQUIRE( nodeA1->HasChildren() == false );

        treeBuilder.InsertChild(nodeA1, unlinkedNode, nullptr);

        REQUIRE( nodeA1->HasChildren() == true );

        REQUIRE( nodeA1->GetFirstChild() == unlinkedNode );
        REQUIRE( nodeA1->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA1 );

        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The node has child nodes" )
    {
      THEN( "SgfcTreeBuilder inserts the new child node at the correct position" )
      {
        // ------------------------------------------------------------
        // Keep the test case the same as the corresponding test case for
        // AppendChild() above
        // ------------------------------------------------------------

        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeB1 );

        treeBuilder.InsertChild(nodeB, unlinkedNode, nullptr);

        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeB );

        REQUIRE( nodeB1->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeB1 );
        REQUIRE( nodeB1->GetPreviousSibling() == nullptr );
      }
    }
  }

  GIVEN( "The InsertChild operation is invoked with nodes that originate from varying locations" )
  {
    WHEN( "The new child node is an unlinked node" )
    {
      THEN( "SgfcTreeBuilder inserts the new child node at the correct position" )
      {
        // ------------------------------------------------------------
        // Keep the test case the same as the corresponding test case for
        // AppendChild() above
        // ------------------------------------------------------------

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.InsertChild(nodeA, unlinkedNode, nullptr);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA3 );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new child node is part of the game tree in some other location" )
    {
      THEN( "SgfcTreeBuilder moves the new child node and relinks the game tree in the old location" )
      {
        // ------------------------------------------------------------
        // Keep the test case the same as the corresponding test case for
        // AppendChild() above
        // ------------------------------------------------------------

        REQUIRE( rootNode->GetFirstChild() == nodeA );
        REQUIRE( rootNode->GetLastChild() == nodeB );
        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeB1 );

        treeBuilder.InsertChild(nodeB, nodeA, nullptr);

        REQUIRE( rootNode->GetFirstChild() == nodeB );
        REQUIRE( rootNode->GetLastChild() == nodeB );
        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeA );

        REQUIRE( nodeB1->GetNextSibling() == nodeA );
        REQUIRE( nodeA->GetNextSibling() == nullptr );
        REQUIRE( nodeA->GetPreviousSibling() == nodeB1 );
        REQUIRE( nodeB1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new child node is a child of the node and is already located at the insert position" )
    {
      THEN( "SgfcTreeBuilder does nothing" )
      {
        // ------------------------------------------------------------
        // Keep the test case the same as the corresponding test case for
        // AppendChild() above
        // ------------------------------------------------------------

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.InsertChild(nodeA, nodeA3, nullptr);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new child node is already a child of the node" )
    {
      THEN( "SgfcTreeBuilder moves the child node and relinks the game tree below the node" )
      {
        // ------------------------------------------------------------
        // Keep the test case the same as the corresponding test case for
        // AppendChild() above
        // ------------------------------------------------------------

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.InsertChild(nodeA, nodeA1, nullptr);

        REQUIRE( nodeA->GetFirstChild() == nodeA2 );
        REQUIRE( nodeA->GetLastChild() == nodeA1 );

        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nodeA1 );
        REQUIRE( nodeA1->GetNextSibling() == nullptr );
        REQUIRE( nodeA1->GetPreviousSibling() == nodeA3 );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );
      }
    }
  }

  GIVEN( "The InsertChild operation is invoked with varying insert positions" )
  {
    WHEN( "The new child node is inserted before the current first child node" )
    {
      THEN( "SgfcTreeBuilder sets the new child node as the node's first child" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.InsertChild(nodeA, unlinkedNode, nodeA1);

        REQUIRE( nodeA->GetFirstChild() == unlinkedNode );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( unlinkedNode->GetNextSibling() == nodeA1 );
        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new child node is inserted in between the current child nodes" )
    {
      THEN( "SgfcTreeBuilder inserts the new child node in the correct position" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.InsertChild(nodeA, unlinkedNode, nodeA3);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new child node is inserted after the current last child node" )
    {
      THEN( "SgfcTreeBuilder sets the new child node as the node's last child" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.InsertChild(nodeA, unlinkedNode, nullptr);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA3 );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }
  }
}

SCENARIO( "SgfcTreeBuilder removes a child from a node", "[document]" )
{
  CreateGameTree();
  SgfcTreeBuilder treeBuilder(game);

  GIVEN( "The RemoveChild operation is invoked with invalid arguments" )
  {
    WHEN( "The node argument is nullptr" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.RemoveChild(nullptr, nodeA1),
          std::invalid_argument);
      }
    }

    WHEN( "The child node argument is nullptr" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.RemoveChild(nodeA, nullptr),
          std::invalid_argument);
      }
    }

    WHEN( "The child node is not a child of the node" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.RemoveChild(nodeA, nodeB),
          std::invalid_argument);
      }
    }

    WHEN( "The child node is equal to the node (special case of \"is not a child\")" )
    {
      REQUIRE_THROWS_AS(
        treeBuilder.RemoveChild(nodeA, nodeA),
        std::invalid_argument);
    }
  }

  GIVEN( "The RemoveChild operation is invoked with varying existing content below the node" )
  {
    WHEN( "The node has a single child node" )
    {
      THEN( "SgfcTreeBuilder removes the single child node" )
      {
        REQUIRE( nodeA2->GetFirstChild() == nodeA2a );
        REQUIRE( nodeA2->GetLastChild() == nodeA2a );

        treeBuilder.RemoveChild(nodeA2, nodeA2a);

        REQUIRE( nodeA2->HasChildren() == false );
        REQUIRE( nodeA2->GetFirstChild() == nullptr );
        REQUIRE( nodeA2->GetLastChild() == nullptr );

        REQUIRE( nodeA2a->HasParent() == false );
        REQUIRE( nodeA2a->GetParent() == nullptr );
      }
    }

    WHEN( "The node has several child nodes" )
    {
      THEN( "SgfcTreeBuilder removes the child node at the correct position" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.RemoveChild(nodeA, nodeA2);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( nodeA2->HasParent() == false );
        REQUIRE( nodeA2->GetParent() == nullptr );
        REQUIRE( nodeA2->GetNextSibling() == nullptr );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );

        REQUIRE( nodeA1->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }
  }

  GIVEN( "The RemoveChild operation is invoked with varying remove positions" )
  {
    WHEN( "The first child node is removed" )
    {
      THEN( "SgfcTreeBuilder removes the first child node" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.RemoveChild(nodeA, nodeA1);

        REQUIRE( nodeA->GetFirstChild() == nodeA2 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( nodeA1->HasParent() == false );
        REQUIRE( nodeA1->GetParent() == nullptr );
        REQUIRE( nodeA1->GetNextSibling() == nullptr );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );

        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "An intermediate child node is removed" )
    {
      THEN( "SgfcTreeBuilder removes the intermediate child node" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.RemoveChild(nodeA, nodeA2);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( nodeA2->HasParent() == false );
        REQUIRE( nodeA2->GetParent() == nullptr );
        REQUIRE( nodeA2->GetNextSibling() == nullptr );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );

        REQUIRE( nodeA1->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The last child node is removed" )
    {
      THEN( "SgfcTreeBuilder removes the last child node" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.RemoveChild(nodeA, nodeA3);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA2 );

        REQUIRE( nodeA3->HasParent() == false );
        REQUIRE( nodeA3->GetParent() == nullptr );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nullptr );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nullptr );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }
  }
}

SCENARIO( "SgfcTreeBuilder replaces a child node", "[document]" )
{
  CreateGameTree();
  SgfcTreeBuilder treeBuilder(game);

  GIVEN( "The ReplaceChild operation is invoked with invalid arguments" )
  {
    WHEN( "The node argument is nullptr" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.ReplaceChild(nullptr, unlinkedNode, nodeA1),
          std::invalid_argument);
      }
    }

    WHEN( "The old child node argument is nullptr" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.ReplaceChild(nodeA, unlinkedNode, nullptr),
          std::invalid_argument);
      }
    }

    WHEN( "The new child node argument is nullptr" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.ReplaceChild(nodeA, nullptr, nodeA1),
          std::invalid_argument);
      }
    }

    WHEN( "The old child node is not a child of the node" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.ReplaceChild(nodeA, unlinkedNode, nodeB),
          std::invalid_argument);
      }
    }

    WHEN( "The new child node is an ancestor of the node" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.ReplaceChild(nodeA, rootNode, nodeA1),
          std::invalid_argument);
      }
    }

    WHEN( "The old child node is equal to the node (special case of \"is not a child\")" )
    {
      REQUIRE_THROWS_AS(
        treeBuilder.ReplaceChild(nodeA, unlinkedNode, nodeA),
        std::invalid_argument);
    }

    WHEN( "The new child node is equal to the node" )
    {
      REQUIRE_THROWS_AS(
        treeBuilder.ReplaceChild(nodeA, nodeA, nodeA1),
        std::invalid_argument);
    }
  }

  GIVEN( "The ReplaceChild operation is invoked with varying existing content below the node" )
  {
    WHEN( "The node has a single child node" )
    {
      THEN( "SgfcTreeBuilder replaces the single child node" )
      {
        REQUIRE( nodeA2->GetFirstChild() == nodeA2a );
        REQUIRE( nodeA2->GetLastChild() == nodeA2a );

        treeBuilder.ReplaceChild(nodeA2, unlinkedNode, nodeA2a);

        REQUIRE( nodeA2->GetFirstChild() == unlinkedNode );
        REQUIRE( nodeA2->GetLastChild() == unlinkedNode );

        REQUIRE( nodeA2a->HasParent() == false );
        REQUIRE( nodeA2a->GetParent() == nullptr );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA2 );
      }
    }

    WHEN( "The node has several child nodes" )
    {
      THEN( "SgfcTreeBuilder replaces the child node at the correct position" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.ReplaceChild(nodeA, unlinkedNode, nodeA2);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( nodeA2->HasParent() == false );
        REQUIRE( nodeA2->GetParent() == nullptr );
        REQUIRE( nodeA2->GetNextSibling() == nullptr );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }
  }

  GIVEN( "The ReplaceChild operation is invoked with nodes that originate from varying locations" )
  {
    WHEN( "The new child node is an unlinked node" )
    {
      THEN( "SgfcTreeBuilder replaces the new child node at the correct position" )
      {
        REQUIRE( rootNode->GetFirstChild() == nodeA );
        REQUIRE( rootNode->GetLastChild() == nodeB );

        treeBuilder.ReplaceChild(rootNode, unlinkedNode, nodeB);

        REQUIRE( rootNode->GetFirstChild() == nodeA );
        REQUIRE( rootNode->GetLastChild() == unlinkedNode );

        REQUIRE( nodeB->HasParent() == false );
        REQUIRE( nodeB->GetParent() == nullptr );
        REQUIRE( nodeB->GetNextSibling() == nullptr );
        REQUIRE( nodeB->GetPreviousSibling() == nullptr );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == rootNode );

        REQUIRE( nodeA->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA );
        REQUIRE( nodeA->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new child node is part of the game tree in some other location" )
    {
      THEN( "SgfcTreeBuilder moves the new child node and relinks the game tree in the old location" )
      {
        REQUIRE( rootNode->GetFirstChild() == nodeA );
        REQUIRE( rootNode->GetLastChild() == nodeB );
        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeB1 );

        treeBuilder.ReplaceChild(nodeB, nodeA, nodeB1);

        REQUIRE( rootNode->GetFirstChild() == nodeB );
        REQUIRE( rootNode->GetLastChild() == nodeB );
        REQUIRE( nodeB->GetFirstChild() == nodeA );
        REQUIRE( nodeB->GetLastChild() == nodeA );

        REQUIRE( nodeB1->HasParent() == false );
        REQUIRE( nodeB1->GetParent() == nullptr );
        REQUIRE( nodeB1->GetNextSibling() == nullptr );
        REQUIRE( nodeB1->GetPreviousSibling() == nullptr );

        REQUIRE( nodeA->HasParent() == true );
        REQUIRE( nodeA->GetParent() == nodeB );

        REQUIRE( nodeA->GetNextSibling() == nullptr );
        REQUIRE( nodeA->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new child node is a child of the node and is already located at the replace position" )
    {
      THEN( "SgfcTreeBuilder does nothing" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.ReplaceChild(nodeA, nodeA3, nodeA3);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( nodeA3->HasParent() == true );
        REQUIRE( nodeA3->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new child node is already a child of the node" )
    {
      THEN( "SgfcTreeBuilder moves the child node and relinks the game tree below the node" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.ReplaceChild(nodeA, nodeA1, nodeA3);

        REQUIRE( nodeA->GetFirstChild() == nodeA2 );
        REQUIRE( nodeA->GetLastChild() == nodeA1 );

        REQUIRE( nodeA3->HasParent() == false );
        REQUIRE( nodeA3->GetParent() == nullptr );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nullptr );

        REQUIRE( nodeA2->GetNextSibling() == nodeA1 );
        REQUIRE( nodeA1->GetNextSibling() == nullptr );
        REQUIRE( nodeA1->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );
      }
    }
  }

  GIVEN( "The ReplaceChild operation is invoked with varying replace positions" )
  {
    WHEN( "The new child node replaces the first child node" )
    {
      THEN( "SgfcTreeBuilder sets the new child node as the node's first child" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.ReplaceChild(nodeA, unlinkedNode, nodeA1);

        REQUIRE( nodeA->GetFirstChild() == unlinkedNode );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( nodeA1->HasParent() == false );
        REQUIRE( nodeA1->GetParent() == nullptr );
        REQUIRE( nodeA1->GetNextSibling() == nullptr );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( unlinkedNode->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new child node replaces an intermediate child node" )
    {
      THEN( "SgfcTreeBuilder replaces the intermediate child node with new child node" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.ReplaceChild(nodeA, unlinkedNode, nodeA2);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( nodeA2->HasParent() == false );
        REQUIRE( nodeA2->GetParent() == nullptr );
        REQUIRE( nodeA2->GetNextSibling() == nullptr );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new child node replaces the last child node" )
    {
      THEN( "SgfcTreeBuilder sets the new child node as the node's last child" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.ReplaceChild(nodeA, unlinkedNode, nodeA3);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == unlinkedNode );

        REQUIRE( nodeA3->HasParent() == false );
        REQUIRE( nodeA3->GetParent() == nullptr );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nullptr );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }
  }
}

SCENARIO( "SgfcTreeBuilder sets the next sibling of a node", "[document]" )
{
  CreateGameTree();
  SgfcTreeBuilder treeBuilder(game);

  GIVEN( "The SetNextSibling operation is invoked with invalid arguments" )
  {
    WHEN( "The node argument is nullptr" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.SetNextSibling(nullptr, unlinkedNode),
          std::invalid_argument);
      }
    }

    WHEN( "The node is the root node" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.SetNextSibling(rootNode, unlinkedNode),
          std::invalid_argument);

        // An unlinked node is also a root node, of a game tree that consists
        // of only 1 node
        REQUIRE_THROWS_AS(
          treeBuilder.SetNextSibling(unlinkedNode, nodeB1),
          std::invalid_argument);
      }
    }

    WHEN( "The next sibling node is an ancestor of the node" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.SetNextSibling(nodeA1, nodeA),
          std::invalid_argument);
      }
    }

    WHEN( "The next sibling node is equal to the node" )
    {
      REQUIRE_THROWS_AS(
        treeBuilder.SetNextSibling(nodeA, nodeA),
        std::invalid_argument);
    }
  }

  GIVEN( "The SetNextSibling operation is invoked with varying existing content behind the node" )
  {
    WHEN( "The node has no next sibling" )
    {
      THEN( "SgfcTreeBuilder sets the next sibling of the node" )
      {
        REQUIRE( nodeA2->GetFirstChild() == nodeA2a );
        REQUIRE( nodeA2->GetLastChild() == nodeA2a );

        treeBuilder.SetNextSibling(nodeA2a, unlinkedNode);

        REQUIRE( nodeA2->GetFirstChild() == nodeA2a );
        REQUIRE( nodeA2->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA2 );

        REQUIRE( nodeA2a->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA2a );
        REQUIRE( nodeA2a->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The node has a next sibling" )
    {
      THEN( "SgfcTreeBuilder replaces the next sibling of the node, and all siblings behind that" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.SetNextSibling(nodeA1, unlinkedNode);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == unlinkedNode );

        REQUIRE( nodeA2->HasParent() == false );
        REQUIRE( nodeA2->GetParent() == nullptr );
        REQUIRE( nodeA3->HasParent() == false );
        REQUIRE( nodeA3->GetParent() == nullptr );
        // SetNextSibling not only removes nodeA2 and nodeA3 from the game tree,
        // it also breaks the nextSibling linkage between these two nodes.
        REQUIRE( nodeA2->GetNextSibling() == nullptr );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nullptr );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }
  }

  GIVEN( "The SetNextSibling operation is invoked with nodes that originate from varying locations" )
  {
    WHEN( "The new next sibling node is an unlinked node" )
    {
      THEN( "SgfcTreeBuilder sets the next sibling of the node" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.SetNextSibling(nodeA3, unlinkedNode);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA3 );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new next sibling node is part of the game tree in some other location" )
    {
      THEN( "SgfcTreeBuilder moves the new next sibling node and relinks the game tree in the old location" )
      {
        REQUIRE( rootNode->GetFirstChild() == nodeA );
        REQUIRE( rootNode->GetLastChild() == nodeB );
        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeB1 );

        treeBuilder.SetNextSibling(nodeB1, nodeA);

        REQUIRE( rootNode->GetFirstChild() == nodeB );
        REQUIRE( rootNode->GetLastChild() == nodeB );
        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeA );

        REQUIRE( nodeB1->GetNextSibling() == nodeA );
        REQUIRE( nodeA->GetNextSibling() == nullptr );
        REQUIRE( nodeA->GetPreviousSibling() == nodeB1 );
        REQUIRE( nodeB1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new next sibling node is a child of the node and is already located at the insert position" )
    {
      THEN( "SgfcTreeBuilder does nothing" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.SetNextSibling(nodeA2, nodeA3);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new next sibling node is already a child of the node" )
    {
      THEN( "SgfcTreeBuilder moves the child node and relinks the game tree below the node" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.SetNextSibling(nodeA3, nodeA1);

        REQUIRE( nodeA->GetFirstChild() == nodeA2 );
        REQUIRE( nodeA->GetLastChild() == nodeA1 );

        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nodeA1 );
        REQUIRE( nodeA1->GetNextSibling() == nullptr );
        REQUIRE( nodeA1->GetPreviousSibling() == nodeA3 );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );
      }
    }
  }

  GIVEN( "The SetNextSibling operation is invoked with varying insert positions" )
  {
    WHEN( "The new next sibling node is inserted after the first sibling node" )
    {
      THEN( "SgfcTreeBuilder replaces the next sibling of the first sibling node, and all siblings behind that" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.SetNextSibling(nodeA1, unlinkedNode);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == unlinkedNode );

        REQUIRE( nodeA2->HasParent() == false );
        REQUIRE( nodeA2->GetParent() == nullptr );
        REQUIRE( nodeA3->HasParent() == false );
        REQUIRE( nodeA3->GetParent() == nullptr );
        // SetNextSibling not only removes nodeA2 and nodeA3 from the game tree,
        // it also breaks the nextSibling linkage between these two nodes.
        REQUIRE( nodeA2->GetNextSibling() == nullptr );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nullptr );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new child node is inserted in between sibling nodes" )
    {
      THEN( "SgfcTreeBuilder replaces the next sibling of the intermediate sibling node, and all siblings behind that" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.SetNextSibling(nodeA2, unlinkedNode);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == unlinkedNode );

        REQUIRE( nodeA3->HasParent() == false );
        REQUIRE( nodeA3->GetParent() == nullptr );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nullptr );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new child node is inserted after the last sibling node" )
    {
      THEN( "SgfcTreeBuilder sets the next sibling of the last sibling node" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.SetNextSibling(nodeA3, unlinkedNode);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA3 );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }
  }
}

SCENARIO( "SgfcTreeBuilder sets the parent of a node", "[document]" )
{
  CreateGameTree();
  SgfcTreeBuilder treeBuilder(game);

  GIVEN( "The SetParent operation is invoked with invalid arguments" )
  {
    WHEN( "The node argument is nullptr" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.SetParent(nullptr, unlinkedNode),
          std::invalid_argument);
      }
    }

    WHEN( "The parent node is a descendant of the node" )
    {
      THEN( "SgfcTreeBuilder throws an exception" )
      {
        REQUIRE_THROWS_AS(
          treeBuilder.SetParent(nodeA, nodeA1),
          std::invalid_argument);
      }
    }

    WHEN( "The parent node is equal to the node" )
    {
      REQUIRE_THROWS_AS(
        treeBuilder.SetParent(nodeA, nodeA),
        std::invalid_argument);
    }
  }

  GIVEN( "The SetParent operation is invoked when node has no parent" )
  {
    WHEN( "The new parent node is nullptr" )
    {
      THEN( "SgfcTreeBuilder does nothing" )
      {
        REQUIRE( rootNode->HasParent() == false );

        treeBuilder.SetParent(rootNode, nullptr);

        REQUIRE( rootNode->HasParent() == false );
        REQUIRE( rootNode->GetParent() == nullptr );
      }
    }

    WHEN( "The new parent node is not nullptr" )
    {
      THEN( "SgfcTreeBuilder sets the new parent node as the node's parent" )
      {
        REQUIRE( rootNode->HasParent() == false );

        treeBuilder.SetParent(rootNode, unlinkedNode);

        REQUIRE( rootNode->HasParent() == true );
        REQUIRE( rootNode->GetParent() == unlinkedNode );

        REQUIRE( unlinkedNode->GetFirstChild() == rootNode );
        REQUIRE( unlinkedNode->GetLastChild() == rootNode );
      }
    }
  }

  GIVEN( "The SetParent operation is invoked when node has a parent" )
  {
    WHEN( "The new parent node is nullptr" )
    {
      THEN( "SgfcTreeBuilder removes the node from the game tree" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.SetParent(nodeA2, nullptr);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( nodeA2->HasParent() == false );
        REQUIRE( nodeA2->GetParent() == nullptr );
        REQUIRE( nodeA2->GetNextSibling() == nullptr );
        REQUIRE( nodeA2->GetPreviousSibling() == nullptr );

        REQUIRE( nodeA1->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The new parent node is not nullptr" )
    {
      THEN( "SgfcTreeBuilder moves the node to a new location" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );
        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeB1 );

        treeBuilder.SetParent(nodeA3, nodeB);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA2 );
        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeA3 );

        REQUIRE( nodeA3->HasParent() == true );
        REQUIRE( nodeA3->GetParent() == nodeB );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nullptr );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );

        REQUIRE( nodeB1->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeB1 );
        REQUIRE( nodeB1->GetPreviousSibling() == nullptr );
      }
    }
  }

  GIVEN( "The SetParent operation is invoked with varying existing content in the parent node" )
  {
    WHEN( "The parent node has no child nodes" )
    {
      THEN( "SgfcTreeBuilder sets the node as the parent node's first and last child" )
      {
        REQUIRE( nodeA1->HasChildren() == false );

        treeBuilder.SetParent(unlinkedNode, nodeA1);

        REQUIRE( nodeA1->HasChildren() == true );

        REQUIRE( nodeA1->GetFirstChild() == unlinkedNode );
        REQUIRE( nodeA1->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA1 );

        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The parent node has child nodes" )
    {
      THEN( "SgfcTreeBuilder sets the node as the parent node's last child" )
      {
        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeB1 );

        treeBuilder.SetParent(unlinkedNode, nodeB);

        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeB );

        REQUIRE( nodeB1->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeB1 );
        REQUIRE( nodeB1->GetPreviousSibling() == nullptr );
      }
    }
  }

  GIVEN( "The SetParent operation is invoked with nodes that originate from varying locations" )
  {
    WHEN( "The node to reparent is an unlinked node" )
    {
      THEN( "SgfcTreeBuilder sets the node as the parent node's last child" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.SetParent(unlinkedNode, nodeA);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == unlinkedNode );

        REQUIRE( unlinkedNode->HasParent() == true );
        REQUIRE( unlinkedNode->GetParent() == nodeA );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == unlinkedNode );
        REQUIRE( unlinkedNode->GetNextSibling() == nullptr );
        REQUIRE( unlinkedNode->GetPreviousSibling() == nodeA3 );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The node to reparent is part of the game tree in some other location" )
    {
      THEN( "SgfcTreeBuilder moves the node to reparent and relinks the game tree in the old location" )
      {
        REQUIRE( rootNode->GetFirstChild() == nodeA );
        REQUIRE( rootNode->GetLastChild() == nodeB );
        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeB1 );

        treeBuilder.SetParent(nodeA, nodeB);

        REQUIRE( rootNode->GetFirstChild() == nodeB );
        REQUIRE( rootNode->GetLastChild() == nodeB );
        REQUIRE( nodeB->GetFirstChild() == nodeB1 );
        REQUIRE( nodeB->GetLastChild() == nodeA );

        REQUIRE( nodeB1->GetNextSibling() == nodeA );
        REQUIRE( nodeA->GetNextSibling() == nullptr );
        REQUIRE( nodeA->GetPreviousSibling() == nodeB1 );
        REQUIRE( nodeB1->GetPreviousSibling() == nullptr );
      }
    }

    WHEN( "The node to reparent is already a child of the parent node and it is not the last child" )
    {
      THEN( "SgfcTreeBuilder does nothing" )
      {
        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        treeBuilder.SetParent(nodeA1, nodeA);

        REQUIRE( nodeA->GetFirstChild() == nodeA1 );
        REQUIRE( nodeA->GetLastChild() == nodeA3 );

        REQUIRE( nodeA1->GetNextSibling() == nodeA2 );
        REQUIRE( nodeA2->GetNextSibling() == nodeA3 );
        REQUIRE( nodeA3->GetNextSibling() == nullptr );
        REQUIRE( nodeA3->GetPreviousSibling() == nodeA2 );
        REQUIRE( nodeA2->GetPreviousSibling() == nodeA1 );
        REQUIRE( nodeA1->GetPreviousSibling() == nullptr );
      }
    }
  }
}
