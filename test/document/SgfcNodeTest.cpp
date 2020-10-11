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
#include <document/SgfcNode.h>
#include <document/SgfcProperty.h>

// Unit test library includes
#include <catch2/catch.hpp>

using namespace LibSgfcPlusPlus;

SCENARIO( "SgfcNode is constructed", "[document]" )
{
  GIVEN( "The default constructor is used" )
  {
    WHEN( "SgfcNode is constructed" )
    {
      THEN( "SgfcNode is constructed successfully" )
      {
        REQUIRE_NOTHROW( SgfcNode() );
      }
    }

    WHEN( "SgfcNode is constructed" )
    {
      auto node = SgfcNode();

      THEN( "SgfcNode has default state" )
      {
        REQUIRE( node.GetFirstChild() == nullptr );
        REQUIRE( node.GetLastChild() == nullptr );
        REQUIRE( node.GetChildren().size() == 0 );
        REQUIRE( node.HasChildren() == false );
        REQUIRE( node.GetNextSibling() == nullptr );
        REQUIRE( node.HasNextSibling() == false );
        REQUIRE( node.GetPreviousSibling() == nullptr );
        REQUIRE( node.HasPreviousSibling() == false );
        REQUIRE( node.GetParent() == nullptr );
        REQUIRE( node.HasParent() == false );
        REQUIRE( node.GetRoot() == nullptr );
        REQUIRE( node.IsRoot() == true );
        REQUIRE( node.GetProperties().size() == 0 );
        REQUIRE( node.GetProperty(SgfcPropertyType::GM) == nullptr );
      }
    }
  }
}

SCENARIO( "SgfcNode is configured with properties", "[document]" )
{
  auto node = SgfcNode();

  GIVEN( "SgfcNode is configured with an empty list of properties" )
  {
    std::vector<std::shared_ptr<ISgfcProperty>> properties;

    WHEN( "SgfcNode is configured" )
    {
      node.SetProperties(properties);

      THEN( "SgfcNode returns the same property list that was configured" )
      {
        REQUIRE( node.GetProperties() == properties );
      }
    }
  }

  GIVEN( "SgfcNode is configured with a non-empty list of properties" )
  {
    WHEN( "SgfcNode is configured with a non-empty valid list of properties" )
    {
      std::vector<std::shared_ptr<ISgfcProperty>> properties
      {
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM")),
        // SgfcNode doesn't care about a matching property name string and enum value
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "HA")),
      };
      node.SetProperties(properties);

      THEN( "SgfcNode returns the same property list that was configured" )
      {
        REQUIRE( node.GetProperties() == properties );
      }
    }

    WHEN( "SgfcNode is configured with a list of properties that contains a nullptr element" )
    {
      std::vector<std::shared_ptr<ISgfcProperty>> properties
      {
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM")),
        std::shared_ptr<ISgfcProperty>(nullptr)
      };

      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node.SetProperties(properties),
          std::invalid_argument);
      }
    }

    WHEN( "SgfcNode is configured with a list of properties that contains a duplicate property type" )
    {
      std::vector<std::shared_ptr<ISgfcProperty>> properties
      {
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM")),
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "SZ")),
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "HA")),
      };

      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node.SetProperties(properties),
          std::invalid_argument);
      }
    }

    WHEN( "SgfcNode is configured with a list of properties that contains a duplicate property name" )
    {
      std::vector<std::shared_ptr<ISgfcProperty>> properties
      {
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM")),
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::HA, "HA")),
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "HA")),
      };

      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node.SetProperties(properties),
          std::invalid_argument);
      }
    }

    WHEN( "SgfcNode is queried for a property that exists in the list" )
    {
      std::vector<std::shared_ptr<ISgfcProperty>> properties
      {
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM")),
        // SgfcNode doesn't care about a matching property name string and enum value
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "HA")),
      };
      node.SetProperties(properties);

      THEN( "SgfcNode returns the property" )
      {
        auto property = node.GetProperty(SgfcPropertyType::SZ);
        REQUIRE( property->GetPropertyType() == SgfcPropertyType::SZ );
        REQUIRE( property->GetPropertyName() == "HA" );
      }
    }

    WHEN( "SgfcNode is queried for a property that does not exist in the list" )
    {
      std::vector<std::shared_ptr<ISgfcProperty>> properties
      {
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM")),
        // SgfcNode doesn't care about a matching property name string and enum value
        std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "HA")),
      };
      node.SetProperties(properties);

      THEN( "SgfcNode returns nullptr" )
      {
        REQUIRE( node.GetProperty(SgfcPropertyType::HA) == nullptr );
      }
    }
  }
}

SCENARIO( "SgfcNode is configured with a first child", "[document]" )
{
  auto node = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto secondNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto thirdNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto nullNode = std::shared_ptr<SgfcNode>(nullptr);

  GIVEN( "SgfcNode is configured with arbitrary values" )
  {
    WHEN( "SgfcNode is queried for the first child" )
    {
      std::vector<std::shared_ptr<SgfcNode>> v = { secondNode, nullNode, node };
      auto firstChildNode = GENERATE_COPY( from_range(v) );
      node->SetFirstChild(firstChildNode);

      THEN( "SgfcNode returns the previously configured value" )
      {
        REQUIRE( node->GetFirstChild() == firstChildNode );
      }
    }
  }

  GIVEN( "SgfcNode is configured with changing values" )
  {
    WHEN( "SgfcNode is queried for the last child" )
    {
      THEN( "SgfcNode returns the correct value" )
      {
        REQUIRE( node->GetLastChild() == nullNode );
        node->SetFirstChild(secondNode);
        REQUIRE( node->GetLastChild() == secondNode );
        secondNode->SetNextSibling(thirdNode);
        REQUIRE( node->GetLastChild() == thirdNode );
        node->SetFirstChild(nullNode);
        REQUIRE( node->GetLastChild() == nullNode );
      }
    }

    WHEN( "SgfcNode is queried for its children" )
    {
      std::vector<std::shared_ptr<ISgfcNode>> noChildren;
      std::vector<std::shared_ptr<ISgfcNode>> oneChild = { secondNode };
      std::vector<std::shared_ptr<ISgfcNode>> twoChildren = { secondNode, thirdNode };

      THEN( "SgfcNode returns the correct value" )
      {
        REQUIRE( node->GetChildren() == noChildren );
        node->SetFirstChild(secondNode);
        REQUIRE( node->GetChildren() == oneChild );
        secondNode->SetNextSibling(thirdNode);
        REQUIRE( node->GetChildren() == twoChildren );
        node->SetFirstChild(nullNode);
        REQUIRE( node->GetChildren() == noChildren );
      }
    }

    WHEN( "SgfcNode is queried whether it has children" )
    {
      THEN( "SgfcNode returns the correct value" )
      {
        REQUIRE( node->HasChildren() == false );
        node->SetFirstChild(secondNode);
        REQUIRE( node->HasChildren() == true );
        secondNode->SetNextSibling(thirdNode);
        REQUIRE( node->HasChildren() == true );
        node->SetFirstChild(nullNode);
        REQUIRE( node->HasChildren() == false );
      }
    }
  }
}

SCENARIO( "SgfcNode is configured with a next sibling", "[document]" )
{
  auto node = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto secondNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto thirdNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto nullNode = std::shared_ptr<SgfcNode>(nullptr);

  GIVEN( "SgfcNode is configured with arbitrary values" )
  {
    WHEN( "SgfcNode is queried for the next sibling" )
    {
      std::vector<std::shared_ptr<SgfcNode>> v = { secondNode, nullNode, node };
      auto nextSiblingNode = GENERATE_COPY( from_range(v) );
      node->SetNextSibling(nextSiblingNode);

      THEN( "SgfcNode returns the previously configured value" )
      {
        REQUIRE( node->GetNextSibling() == nextSiblingNode );
      }
    }
  }

  GIVEN( "SgfcNode is configured with changing values" )
  {
    WHEN( "SgfcNode is queried whether it has a next sibling" )
    {
      THEN( "SgfcNode returns the correct value" )
      {
        REQUIRE( node->HasNextSibling() == false );
        node->SetNextSibling(secondNode);
        REQUIRE( node->HasNextSibling() == true );
        secondNode->SetNextSibling(thirdNode);
        REQUIRE( node->HasNextSibling() == true );
        node->SetNextSibling(nullNode);
        REQUIRE( node->HasNextSibling() == false );
      }
    }

    WHEN( "SgfcNode is queried for the previous sibling" )
    {
      THEN( "SgfcNode returns the correct value when nodes are correctly linked" )
      {
        REQUIRE( secondNode->GetPreviousSibling() == nullNode );
        node->SetNextSibling(secondNode);
        REQUIRE( secondNode->GetPreviousSibling() == nullNode );
        REQUIRE( secondNode->HasPreviousSibling() == false );
        secondNode->SetParent(thirdNode);
        REQUIRE( secondNode->GetPreviousSibling() == nullNode );
        REQUIRE( secondNode->HasPreviousSibling() == false );
        thirdNode->SetFirstChild(node);
        // Finally nodes are correctly linked
        REQUIRE( secondNode->GetPreviousSibling() == node );
        REQUIRE( secondNode->HasPreviousSibling() == true );
      }
    }
  }
}

SCENARIO( "SgfcNode is configured with a parent", "[document]" )
{
  auto node = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto secondNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto thirdNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto nullNode = std::shared_ptr<SgfcNode>(nullptr);

  GIVEN( "SgfcNode is configured with arbitrary values" )
  {
    WHEN( "SgfcNode is queried for the next sibling" )
    {
      std::vector<std::shared_ptr<SgfcNode>> v = { secondNode, nullNode, node };
      auto parentNode = GENERATE_COPY( from_range(v) );
      node->SetParent(parentNode);

      THEN( "SgfcNode returns the previously configured value" )
      {
        REQUIRE( node->GetParent() == parentNode );
      }
    }
  }

  GIVEN( "SgfcNode is configured with changing values" )
  {
    WHEN( "SgfcNode is queried whether it has a parent" )
    {
      THEN( "SgfcNode returns the correct value" )
      {
        REQUIRE( node->HasParent() == false );
        node->SetParent(secondNode);
        REQUIRE( node->HasParent() == true );
        secondNode->SetParent(thirdNode);
        REQUIRE( node->HasParent() == true );
        node->SetParent(nullNode);
        REQUIRE( node->HasParent() == false );
      }
    }
  }
}

SCENARIO( "SgfcNode is queried for its position in the game tree", "[document]" )
{
  auto node = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto childNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto siblingNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto parentNode = std::shared_ptr<SgfcNode>(new SgfcNode());
  auto nodeInOtherTree = std::shared_ptr<ISgfcNode>(new SgfcNode());

  parentNode->SetFirstChild(node);
  node->SetParent(parentNode);
  node->SetNextSibling(siblingNode);
  siblingNode->SetParent(parentNode);
  node->SetFirstChild(childNode);
  childNode->SetParent(node);

  GIVEN( "SgfcNode is queried with IsDescendantOf" )
  {
    WHEN( "SgfcNode is queried with illegal arguments" )
    {
      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node->IsDescendantOf(nullptr),
          std::invalid_argument);
      }
    }

    WHEN( "SgfcNode is queried with legal arguments" )
    {
      THEN( "SgfcNode returns the correct result" )
      {
        REQUIRE( node->IsDescendantOf(node) == false );
        REQUIRE( node->IsDescendantOf(childNode) == false );
        REQUIRE( node->IsDescendantOf(siblingNode) == false );
        // Direct child
        REQUIRE( node->IsDescendantOf(parentNode) == true );
        REQUIRE( node->IsDescendantOf(nodeInOtherTree) == false );

        // Direct child
        REQUIRE( childNode->IsDescendantOf(node) == true );
        REQUIRE( childNode->IsDescendantOf(childNode) == false );
        REQUIRE( childNode->IsDescendantOf(siblingNode) == false );
        // Indirect child = descendant
        REQUIRE( childNode->IsDescendantOf(parentNode) == true );
        REQUIRE( childNode->IsDescendantOf(nodeInOtherTree) == false );

        REQUIRE( siblingNode->IsDescendantOf(node) == false );
        REQUIRE( siblingNode->IsDescendantOf(childNode) == false );
        REQUIRE( siblingNode->IsDescendantOf(siblingNode) == false );
        // Direct child
        REQUIRE( siblingNode->IsDescendantOf(parentNode) == true );
        REQUIRE( siblingNode->IsDescendantOf(nodeInOtherTree) == false );

        REQUIRE( parentNode->IsDescendantOf(node) == false );
        REQUIRE( parentNode->IsDescendantOf(childNode) == false );
        REQUIRE( parentNode->IsDescendantOf(siblingNode) == false );
        REQUIRE( parentNode->IsDescendantOf(parentNode) == false );
        REQUIRE( parentNode->IsDescendantOf(nodeInOtherTree) == false );

        REQUIRE( nodeInOtherTree->IsDescendantOf(node) == false );
        REQUIRE( nodeInOtherTree->IsDescendantOf(childNode) == false );
        REQUIRE( nodeInOtherTree->IsDescendantOf(siblingNode) == false );
        REQUIRE( nodeInOtherTree->IsDescendantOf(parentNode) == false );
        REQUIRE( nodeInOtherTree->IsDescendantOf(nodeInOtherTree) == false );
      }
    }
  }

  GIVEN( "SgfcNode is queried with IsAncestorOf" )
  {
    WHEN( "SgfcNode is queried with illegal arguments" )
    {
      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node->IsAncestorOf(nullptr),
          std::invalid_argument);
      }
    }

    WHEN( "SgfcNode is queried with legal arguments" )
    {
      THEN( "SgfcNode returns the correct result" )
      {
        REQUIRE( node->IsAncestorOf(node) == false );
        // Direct parent
        REQUIRE( node->IsAncestorOf(childNode) == true );
        REQUIRE( node->IsAncestorOf(siblingNode) == false );
        REQUIRE( node->IsAncestorOf(parentNode) == false );
        REQUIRE( node->IsAncestorOf(nodeInOtherTree) == false );

        REQUIRE( childNode->IsAncestorOf(node) == false );
        REQUIRE( childNode->IsAncestorOf(childNode) == false );
        REQUIRE( childNode->IsAncestorOf(siblingNode) == false );
        REQUIRE( childNode->IsAncestorOf(parentNode) == false );
        REQUIRE( childNode->IsAncestorOf(nodeInOtherTree) == false );

        REQUIRE( siblingNode->IsAncestorOf(node) == false );
        REQUIRE( siblingNode->IsAncestorOf(childNode) == false );
        REQUIRE( siblingNode->IsAncestorOf(siblingNode) == false );
        REQUIRE( siblingNode->IsAncestorOf(parentNode) == false );
        REQUIRE( siblingNode->IsAncestorOf(nodeInOtherTree) == false );

        // Direct parent
        REQUIRE( parentNode->IsAncestorOf(node) == true );
        // Indirect parent = ancestor
        REQUIRE( parentNode->IsAncestorOf(childNode) == true );
        // Direct parent
        REQUIRE( parentNode->IsAncestorOf(siblingNode) == true );
        REQUIRE( parentNode->IsAncestorOf(parentNode) == false );
        REQUIRE( parentNode->IsAncestorOf(nodeInOtherTree) == false );

        REQUIRE( nodeInOtherTree->IsAncestorOf(node) == false );
        REQUIRE( nodeInOtherTree->IsAncestorOf(childNode) == false );
        REQUIRE( nodeInOtherTree->IsAncestorOf(siblingNode) == false );
        REQUIRE( nodeInOtherTree->IsAncestorOf(parentNode) == false );
        REQUIRE( nodeInOtherTree->IsAncestorOf(nodeInOtherTree) == false );
      }
    }
  }

  GIVEN( "SgfcNode is queried for the root node" )
  {
    WHEN( "SgfcNode is queried with GetRoot and HasRoot" )
    {
      THEN( "SgfcNode returns the correct result" )
      {
        REQUIRE( node->GetRoot() == parentNode );
        REQUIRE( node->IsRoot() == false );

        REQUIRE( childNode->GetRoot() == parentNode );
        REQUIRE( childNode->IsRoot() == false );

        REQUIRE( siblingNode->GetRoot() == parentNode );
        REQUIRE( siblingNode->IsRoot() == false );

        REQUIRE( parentNode->GetRoot() == nullptr );
        REQUIRE( parentNode->IsRoot() == true );

        REQUIRE( nodeInOtherTree->GetRoot() == nullptr );
        REQUIRE( nodeInOtherTree->IsRoot() == true );
      }
    }
  }
}
