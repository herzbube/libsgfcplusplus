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
#include "../AssertHelperFunctions.h"
#include "../SetupHelperFunctions.h"

// Library includes
#include <ISgfcGameInfo.h>
#include <SgfcConstants.h>
#include <document/SgfcGame.h>
#include <document/SgfcNode.h>
#include <document/SgfcProperty.h>
#include <document/SgfcTreeBuilder.h>
#include <SgfcUtility.h>

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
      auto node = std::make_shared<SgfcNode>();

      THEN( "SgfcNode has default state" )
      {
        REQUIRE( node->GetFirstChild() == nullptr );
        REQUIRE( node->GetLastChild() == nullptr );
        REQUIRE( node->GetChildren().size() == 0 );
        REQUIRE( node->HasChildren() == false );
        REQUIRE( node->GetNextSibling() == nullptr );
        REQUIRE( node->HasNextSibling() == false );
        REQUIRE( node->GetPreviousSibling() == nullptr );
        REQUIRE( node->HasPreviousSibling() == false );
        REQUIRE( node->GetParent() == nullptr );
        REQUIRE( node->HasParent() == false );
        REQUIRE( node->IsRoot() == true );
        REQUIRE( node->GetTraits() == (SgfcConstants::NodeTraitsNone | SgfcNodeTrait::Root) );
        REQUIRE( node->HasTrait(SgfcNodeTrait::Root) == true );
        REQUIRE( node->GetRoot() == node );
        REQUIRE( node->GetGameInfoNode() == nullptr );
        auto mainVariationNodes = node->GetMainVariationNodes();
        REQUIRE( mainVariationNodes.size() == 1 );
        REQUIRE( mainVariationNodes.front() == node );
        REQUIRE( node->HasProperties() == false );
        REQUIRE( node->GetProperties().size() == 0 );
        REQUIRE( node->GetProperty(SgfcPropertyType::GM) == nullptr );
        REQUIRE( node->GetProperties(SgfcPropertyCategory::GameInfo).size() == 0 );
        REQUIRE( node->GetInheritedProperties().size() == 0 );
      }
    }
  }
}

SCENARIO( "SgfcNode is queried for traits", "[document]" )
{
  auto game = std::make_shared<SgfcGame>();
  SgfcTreeBuilder treeBuilder(game);

  auto rootNode = std::make_shared<SgfcNode>();
  game->SetRootNode(rootNode);
  auto leafNode = std::make_shared<SgfcNode>();
  treeBuilder.SetFirstChild(rootNode, leafNode);

  auto rootProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM"));
  auto gameInfoProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::AN, "AN"));
  auto moveProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::B, "B"));
  auto setupProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::AB, "AB"));
  auto nodeAnnotationProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::C, "C"));
  auto moveAnnotationProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::BM, "BM"));
  auto markupProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::AR, "AR"));
  auto timingProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::BL, "BL"));
  auto miscellaneousProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::FG, "FG"));
  auto inheritableProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::PM, "PM"));

  GIVEN( "The node has no properties" )
  {
    WHEN( "The node is the root node" )
    {
      THEN( "The node has the trait SgfcNodeTrait::Root" )
      {
        REQUIRE( rootNode->GetTraits() == (SgfcConstants::NodeTraitsNone | SgfcNodeTrait::Root) );
        REQUIRE( rootNode->HasTrait(SgfcNodeTrait::Root) == true );
      }
    }

    WHEN( "The node is not the root node" )
    {
      THEN( "The node has the traits SgfcConstants::NodeTraitsNone" )
      {
        REQUIRE( leafNode->GetTraits() == SgfcConstants::NodeTraitsNone );
        REQUIRE( leafNode->HasTrait(SgfcNodeTrait::Root) == false );
      }
    }
  }

  GIVEN( "The node has a single property of a category that determines the node traits" )
  {
    std::map<std::shared_ptr<ISgfcProperty>, SgfcNodeTrait> testDataMap =
    {
      { gameInfoProperty, SgfcNodeTrait::GameInfo },
      { moveProperty, SgfcNodeTrait::Move },
      { setupProperty, SgfcNodeTrait::Setup },
      { nodeAnnotationProperty, SgfcNodeTrait::NodeAnnotation },
      { moveAnnotationProperty, SgfcNodeTrait::MoveAnnotation },
      { markupProperty, SgfcNodeTrait::Markup },
      { timingProperty, SgfcNodeTrait::Timing },
      { inheritableProperty, SgfcNodeTrait::Inheritable },
    };
    auto testData = GENERATE_COPY( from_range(testDataMap) );

    WHEN( "The node is the root node" )
    {
      rootNode->SetProperties({testData.first});

      THEN( "The node has the trait SgfcNodeTrait::Root and the trait resulting from the property category" )
      {
        REQUIRE( rootNode->GetTraits() == (testData.second | SgfcNodeTrait::Root) );
        REQUIRE( rootNode->HasTrait(testData.second) == true );
        REQUIRE( rootNode->HasTrait(SgfcNodeTrait::Root) == true );
      }
    }

    WHEN( "The node is not the root node" )
    {
      leafNode->SetProperties({testData.first});

      THEN( "The node has the trait resulting from the property category" )
      {
        REQUIRE( leafNode->GetTraits() == (SgfcConstants::NodeTraitsNone | testData.second) );
        REQUIRE( leafNode->HasTrait(testData.second) == true );
        REQUIRE( leafNode->HasTrait(SgfcNodeTrait::Root) == false );
      }
    }
  }

  GIVEN( "The node has a single property of a category that does not determine the node traits" )
  {
    std::vector<std::shared_ptr<ISgfcProperty>> testDataList = { rootProperty, miscellaneousProperty };
    auto property = GENERATE_COPY( from_range(testDataList) );

    WHEN( "The node is the root node" )
    {
      rootNode->SetProperties({property});

      THEN( "The node has the trait SgfcNodeTrait::Root and the trait resulting from the property category" )
      {
        REQUIRE( rootNode->GetTraits() == (SgfcConstants::NodeTraitsNone | SgfcNodeTrait::Root) );
        REQUIRE( rootNode->HasTrait(SgfcNodeTrait::Root) == true );
      }
    }

    WHEN( "The node is not the root node" )
    {
      // There is an interesting test here: A root property does not make a
      // non-root node into a root node

      leafNode->SetProperties({property});

      THEN( "The node has the trait resulting from the property category" )
      {
        REQUIRE( leafNode->GetTraits() == SgfcConstants::NodeTraitsNone );
      }
    }
  }

  GIVEN( "The node has a single property that determines several node traits at once" )
  {
    auto inheritableAndMarkupProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::DD, "DD"));
    auto expectedTraits = SgfcNodeTrait::Inheritable | SgfcNodeTrait::Markup;

    WHEN( "The node is the root node" )
    {
      rootNode->SetProperties({inheritableAndMarkupProperty});

      THEN( "The node has the trait SgfcNodeTrait::Root and the traits resulting from the property" )
      {
        REQUIRE( rootNode->GetTraits() == (expectedTraits | SgfcNodeTrait::Root) );
        REQUIRE( rootNode->HasTrait(SgfcNodeTrait::Root) == true );
      }
    }

    WHEN( "The node is not the root node" )
    {
      leafNode->SetProperties({inheritableAndMarkupProperty});

      THEN( "The node has the traits resulting from the property" )
      {
        REQUIRE( leafNode->GetTraits() == expectedTraits );
      }
    }
  }

  GIVEN( "The node has multiple properties" )
  {
    std::vector<std::shared_ptr<ISgfcProperty>> properties =
    {
      gameInfoProperty, moveProperty, setupProperty,
      nodeAnnotationProperty, moveAnnotationProperty,
      markupProperty, timingProperty, inheritableProperty,
      // Adding a root property does not change anything
      rootProperty,
      // Adding a property that duplicates some traits (Inheritable and
      // Markup in this case) does not change anything
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::DD, "DD")),
    };
    auto expectedTraits = (SgfcNodeTrait::GameInfo | SgfcNodeTrait::Move | SgfcNodeTrait::Setup |
                           SgfcNodeTrait::NodeAnnotation | SgfcNodeTrait::MoveAnnotation |
                           SgfcNodeTrait::Markup | SgfcNodeTrait::Timing | SgfcNodeTrait::Inheritable);

    WHEN( "The node is the root node" )
    {
      rootNode->SetProperties(properties);

      THEN( "The node has the trait SgfcNodeTrait::Root and all the other traits resulting from the property categories combined" )
      {
        REQUIRE( rootNode->GetTraits() == (expectedTraits | SgfcNodeTrait::Root) );
        REQUIRE( rootNode->HasTrait(SgfcNodeTrait::Root) == true );
      }
    }

    WHEN( "The node is not the root node" )
    {
      leafNode->SetProperties(properties);

      THEN( "The node has all the traits resulting from the property categories combined" )
      {
        REQUIRE( leafNode->GetTraits() == expectedTraits );
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
        REQUIRE( node.HasProperties() == false );
        REQUIRE( node.GetProperties() == properties );
      }
    }

    WHEN( "SgfcNode is configured" )
    {
      node.SetProperties(properties);
      properties.push_back(nullptr);

      THEN( "SgfcNode makes a copy of the property list" )
      {
        REQUIRE( node.HasProperties() == false );
        REQUIRE( node.GetProperties() != properties );
      }
    }
  }

  GIVEN( "SgfcNode is configured with a valid non-empty list of properties" )
  {
    std::vector<std::shared_ptr<ISgfcProperty>> properties
    {
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM")),
      // SgfcNode doesn't care about a matching property name string and enum value
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "HA")),
    };

    WHEN( "SgfcNode is configured" )
    {
      node.SetProperties(properties);

      THEN( "SgfcNode returns the same property list that was configured" )
      {
        REQUIRE( node.HasProperties() == true );
        REQUIRE( node.GetProperties() == properties );
      }
    }

    WHEN( "SgfcNode is configured" )
    {
      node.SetProperties(properties);
      properties.clear();

      THEN( "SgfcNode makes a copy of the property list" )
      {
        REQUIRE( node.HasProperties() == true );
        REQUIRE( node.GetProperties() != properties );
      }
    }
  }

  GIVEN( "SgfcNode is configured with an invalid non-empty list of properties" )
  {
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
        REQUIRE( node.HasProperties() == false );
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
        REQUIRE( node.HasProperties() == false );
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
        REQUIRE( node.HasProperties() == false );
      }
    }
  }
}

SCENARIO( "A property is added to or replaced in SgfcNode", "[document]" )
{
  SgfcNode node;
  auto property = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::DO, "IN"));

  GIVEN( "The node contains no properties" )
  {
    WHEN( "A property is added to SgfcNode" )
    {
      node.SetProperty(property);

      THEN( "SgfcNode contains the added property" )
      {
        REQUIRE( node.HasProperties() == true );
        auto propertyList = node.GetProperties();
        REQUIRE( propertyList.size() == 1 );
        REQUIRE( propertyList.back() == property );
      }
    }
  }

  GIVEN( "The node already contains properties" )
  {
    auto propertyGM = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM"));
    // SgfcNode doesn't care about a matching property name string and enum value
    auto propertySZ = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "HA"));
    auto propertyB = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::B, "B"));
    std::vector<std::shared_ptr<ISgfcProperty>> initialPropertyList =
    {
      propertyGM,
      propertySZ,
      propertyB,
    };
    node.SetProperties(initialPropertyList);

    WHEN( "A property is added to SgfcNode" )
    {
      node.SetProperty(property);

      THEN( "SgfcNode adds the property to the end of the property list" )
      {
        REQUIRE( node.HasProperties() == true );
        auto propertyList = node.GetProperties();
        REQUIRE( propertyList.size() == 4 );
        REQUIRE( propertyList.back() == property );
        propertyList.pop_back();
        REQUIRE( propertyList == initialPropertyList );
      }
    }

    WHEN( "A property is added that is already part of the SgfcNode" )
    {
      node.SetProperty(initialPropertyList.back());

      THEN( "SgfcNode does nothing" )
      {
        REQUIRE( node.GetProperties() == initialPropertyList );
      }
    }

    WHEN( "A property is added but the SgfcNode already contains a property with the same property type" )
    {
      auto propertyWithDuplicatePropertyType = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "SZ"));
      std::vector<std::shared_ptr<ISgfcProperty>> expectedPropertyList =
      {
        propertyGM,
        propertyB,
        propertyWithDuplicatePropertyType,
      };
      node.SetProperty(propertyWithDuplicatePropertyType);

      THEN( "SgfcNode replaces the property" )
      {
        REQUIRE( node.GetProperties() == expectedPropertyList );
      }
    }

    WHEN( "A property is added but the SgfcNode already contains a property with the same property name" )
    {
      auto propertyWithDuplicatePropertyName = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::HA, "HA"));
      std::vector<std::shared_ptr<ISgfcProperty>> expectedPropertyList =
      {
        propertyGM,
        propertyB,
        propertyWithDuplicatePropertyName,
      };
      node.SetProperty(propertyWithDuplicatePropertyName);

      THEN( "SgfcNode replaces the property" )
      {
        REQUIRE( node.GetProperties() == expectedPropertyList );
      }
    }

    WHEN( "A custom property is added but the SgfcNode already contains a custom property with the same property name" )
    {
      auto customPropertyGM = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::Unknown, "GM"));
      // SgfcNode doesn't care about a matching property name string and enum value
      auto customPropertySZ = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::Unknown, "HA"));
      auto customPropertyB = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::Unknown, "B"));
      std::vector<std::shared_ptr<ISgfcProperty>> initialCustomPropertyList =
      {
        customPropertyGM,
        customPropertySZ,
        customPropertyB,
      };
      node.SetProperties(initialCustomPropertyList);

      auto customPropertyWithDuplicatePropertyName = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::Unknown, "HA"));
      std::vector<std::shared_ptr<ISgfcProperty>> expectedCustomPropertyList =
      {
        customPropertyGM,
        customPropertyB,
        customPropertyWithDuplicatePropertyName,
      };
      node.SetProperty(customPropertyWithDuplicatePropertyName);

      THEN( "SgfcNode replaces the property" )
      {
        REQUIRE( node.GetProperties() == expectedCustomPropertyList );
      }
    }
  }

  GIVEN( "A nullptr argument is passed to the add function" )
  {
    WHEN( "A nullptr argument is passed to the add function" )
    {
      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node.SetProperty(nullptr),
          std::invalid_argument);
        REQUIRE( node.HasProperties() == false );
      }
    }
  }
}

SCENARIO( "A property is added to SgfcNode", "[document]" )
{
  SgfcNode node;
  auto property = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::DO, "IN"));

  GIVEN( "The node contains no properties" )
  {
    WHEN( "A property is added to SgfcNode" )
    {
      node.AppendProperty(property);

      THEN( "SgfcNode contains the added property" )
      {
        REQUIRE( node.HasProperties() == true );
        auto propertyList = node.GetProperties();
        REQUIRE( propertyList.size() == 1 );
        REQUIRE( propertyList.back() == property );
      }
    }
  }

  GIVEN( "The node already contains properties" )
  {
    std::vector<std::shared_ptr<ISgfcProperty>> initialPropertyList =
    {
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM")),
      // SgfcNode doesn't care about a matching property name string and enum value
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "HA")),
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::B, "B")),
    };
    node.SetProperties(initialPropertyList);

    WHEN( "A property is added to SgfcNode" )
    {
      node.AppendProperty(property);

      THEN( "SgfcNode adds the property to the end of the property list" )
      {
        REQUIRE( node.HasProperties() == true );
        auto propertyList = node.GetProperties();
        REQUIRE( propertyList.size() == 4 );
        REQUIRE( propertyList.back() == property );
        propertyList.pop_back();
        REQUIRE( propertyList == initialPropertyList );
      }
    }

    WHEN( "A property is added that is already part of the SgfcNode" )
    {
      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node.AppendProperty(initialPropertyList.back()),
          std::invalid_argument);
        REQUIRE( node.GetProperties() == initialPropertyList );
      }
    }

    WHEN( "A property is added but the SgfcNode already contains a property with the same property type" )
    {
      auto propertyWithDuplicatePropertyType = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "SZ"));

      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node.AppendProperty(propertyWithDuplicatePropertyType),
          std::invalid_argument);
        REQUIRE( node.GetProperties() == initialPropertyList );
      }
    }

    WHEN( "A property is added but the SgfcNode already contains a property with the same property name" )
    {
      auto propertyWithDuplicatePropertyName = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::HA, "HA"));

      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node.AppendProperty(propertyWithDuplicatePropertyName),
          std::invalid_argument);
        REQUIRE( node.GetProperties() == initialPropertyList );
      }
    }
  }

  GIVEN( "A nullptr argument is passed to the add function" )
  {
    WHEN( "A nullptr argument is passed to the add function" )
    {
      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node.AppendProperty(nullptr),
          std::invalid_argument);
        REQUIRE( node.HasProperties() == false );
      }
    }
  }
}

SCENARIO( "A property is removed from SgfcNode", "[document]" )
{
  std::vector<std::shared_ptr<ISgfcProperty>> initialPropertyList =
  {
    std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM")),
    // SgfcNode doesn't care about a matching property name string and enum value
    std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "HA")),
    std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::B, "B")),
  };
  SgfcNode node;

  GIVEN( "The node contains the property to be removed" )
  {
    auto propertyToRemove = initialPropertyList.back();
    node.SetProperties(initialPropertyList);

    WHEN( "A property is removed from SgfcNode" )
    {
      node.RemoveProperty(propertyToRemove);

      THEN( "SgfcNode removes the property" )
      {
        REQUIRE( node.HasProperties() == true );
        auto propertyList = node.GetProperties();
        REQUIRE( propertyList.size() == 2 );
        REQUIRE( propertyList.back() != propertyToRemove );
        propertyList.push_back(propertyToRemove);
        REQUIRE( propertyList == initialPropertyList );
      }
    }
  }

  GIVEN( "The node does not contain the property to be removed" )
  {
    auto propertyToRemove = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::W, "W"));
    node.SetProperties(initialPropertyList);

    WHEN( "The missing property is removed from SgfcNode" )
    {
      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node.RemoveProperty(propertyToRemove),
          std::invalid_argument);
        REQUIRE( node.GetProperties() == initialPropertyList );
      }
    }
  }

  GIVEN( "The node contains a property with the same type and name as the property to be removed but the objects are different" )
  {
    auto propertyToRemove = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::B, "B"));
    node.SetProperties(initialPropertyList);

    WHEN( "The similar property is removed from SgfcNode" )
    {
      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node.RemoveProperty(propertyToRemove),
          std::invalid_argument);
        REQUIRE( node.GetProperties() == initialPropertyList );
      }
    }
  }

  GIVEN( "The node contains properties" )
  {
    WHEN( "All propertiess are individually removed from the node" )
    {
      node.SetProperties(initialPropertyList);
      for (const auto& propertyToRemove : initialPropertyList)
        node.RemoveProperty(propertyToRemove);

      THEN( "The node becomes empty after removing the last property" )
      {
        REQUIRE( node.HasProperties() == false );
        REQUIRE( node.GetProperties().size() == 0 );
      }
    }

    WHEN( "Only some of the properties are removed from the node" )
    {
      node.SetProperties(initialPropertyList);
      node.RemoveProperty(initialPropertyList.front());
      node.RemoveProperty(initialPropertyList.back());

      THEN( "The node remains non-empty after removing the game" )
      {
        REQUIRE( node.HasProperties() == true );
        REQUIRE( node.GetProperties().size() == 1 );
      }
    }
  }

  GIVEN( "A nullptr argument is passed to the remove function" )
  {
    node.SetProperties(initialPropertyList);

    WHEN( "A nullptr argument is passed to the remove function" )
    {
      THEN( "SgfcNode throws an exception" )
      {
        REQUIRE_THROWS_AS(
          node.RemoveProperty(nullptr),
          std::invalid_argument);
        REQUIRE( node.GetProperties() == initialPropertyList );
      }
    }
  }
}

SCENARIO( "All properties are removed from SgfcNode", "[document]" )
{
  GIVEN( "The node contains properties to be removed" )
  {
    std::vector<std::shared_ptr<ISgfcProperty>> initialPropertyList =
    {
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM")),
      // SgfcNode doesn't care about a matching property name string and enum value
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "HA")),
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::B, "B")),
    };
    SgfcNode node;
    node.SetProperties(initialPropertyList);

    WHEN( "All properties are removed from the node" )
    {
      node.RemoveAllProperties();

      THEN( "The node becomes empty" )
      {
        REQUIRE( node.HasProperties() == false );
        REQUIRE( node.GetProperties().size() == 0 );
      }
    }
  }

  GIVEN( "The node does not contain any properties to be removed" )
  {
    SgfcNode node;

    WHEN( "All properties are removed from the node" )
    {
      node.RemoveAllProperties();

      THEN( "The node remains empty" )
      {
        REQUIRE( node.HasProperties() == false );
        REQUIRE( node.GetProperties().size() == 0 );
      }
    }
  }
}

SCENARIO( "SgfcNode is queried for properties", "[document]" )
{
  auto node = std::make_shared<SgfcNode>();

  GIVEN( "SgfcNode contains no properties" )
  {
    WHEN( "SgfcNode is queried for properties" )
    {
      auto propertyQueriedByType = node->GetProperty(SgfcPropertyType::HA);
      auto propertyQueriedByName = node->GetProperty("HA");
      auto propertiesQueriedByCategory = node->GetProperties(SgfcPropertyCategory::GameInfo);
      auto inheritedProperties = node->GetInheritedProperties();

      THEN( "SgfcNode returns nullptr" )
      {
        REQUIRE( propertyQueriedByType == nullptr );
        REQUIRE( propertyQueriedByName == nullptr );
        REQUIRE( propertiesQueriedByCategory.size() == 0 );
        REQUIRE( inheritedProperties.size() == 0 );
      }
    }
  }

  GIVEN( "SgfcNode contains properties" )
  {
    std::vector<std::shared_ptr<ISgfcProperty>> properties
    {
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM")),
      // SgfcNode doesn't care about a matching property name string and enum value
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::SZ, "HA")),
    };
    node->SetProperties(properties);

    WHEN( "SgfcNode is queried for properties that it contains" )
    {
      auto propertyQueriedByType = node->GetProperty(SgfcPropertyType::SZ);
      auto propertyQueriedByName = node->GetProperty("HA");
      auto propertiesQueriedByCategory = node->GetProperties(SgfcPropertyCategory::Root);
      auto inheritedProperties = node->GetInheritedProperties();

      THEN( "SgfcNode returns the properties" )
      {
        REQUIRE( propertyQueriedByType->GetPropertyType() == SgfcPropertyType::SZ );
        REQUIRE( propertyQueriedByType->GetPropertyName() == "HA" );
        REQUIRE( propertyQueriedByType == properties.back() );

        REQUIRE( propertyQueriedByName->GetPropertyType() == SgfcPropertyType::SZ );
        REQUIRE( propertyQueriedByName->GetPropertyName() == "HA" );
        REQUIRE( propertyQueriedByName == properties.back() );

        REQUIRE( propertiesQueriedByCategory.size() == 2 );
        REQUIRE( propertiesQueriedByCategory == properties );
        REQUIRE( inheritedProperties.size() == 0 );
      }
    }

    WHEN( "SgfcNode is queried for properties that it does not contain" )
    {
      auto propertyQueriedByType = node->GetProperty(SgfcPropertyType::HA);
      auto propertyQueriedByName = node->GetProperty("SZ");
      auto propertiesQueriedByCategory = node->GetProperties(SgfcPropertyCategory::GameInfo);
      auto inheritedProperties = node->GetInheritedProperties();

      THEN( "SgfcNode returns nullptr" )
      {
        REQUIRE( propertyQueriedByType == nullptr );
        REQUIRE( propertyQueriedByName == nullptr );
        REQUIRE( propertiesQueriedByCategory.size() == 0 );
        REQUIRE( inheritedProperties.size() == 0 );
      }
    }
  }

  GIVEN( "SgfcNode contains custom properties" )
  {
    std::vector<std::shared_ptr<ISgfcProperty>> properties
    {
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::Unknown, "AA")),
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::GM, "GM")),
      std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::Unknown, "BB")),
    };
    node->SetProperties(properties);

    WHEN( "SgfcNode is queried for custom properties" )
    {
      auto propertyQueriedByType = node->GetProperty(SgfcPropertyType::Unknown);
      auto propertyQueriedByName = node->GetProperty("BB");
      auto propertiesQueriedByCategory = node->GetProperties(SgfcPropertyCategory::Miscellaneous);
      auto inheritedProperties = node->GetInheritedProperties();

      THEN( "SgfcNode returns the properties" )
      {
        REQUIRE( propertyQueriedByType->GetPropertyType() == SgfcPropertyType::Unknown );
        REQUIRE( propertyQueriedByType->GetPropertyName() == "AA" );
        REQUIRE( propertyQueriedByType == properties.front() );

        REQUIRE( propertyQueriedByName->GetPropertyType() == SgfcPropertyType::Unknown );
        REQUIRE( propertyQueriedByName->GetPropertyName() == "BB" );
        REQUIRE( propertyQueriedByName == properties.back() );

        REQUIRE( propertiesQueriedByCategory.size() == 2 );
        REQUIRE( propertiesQueriedByCategory.front()->GetPropertyType() == SgfcPropertyType::Unknown );
        REQUIRE( propertiesQueriedByCategory.front()->GetPropertyName() == "AA" );
        REQUIRE( propertiesQueriedByCategory.front() == properties.front() );
        REQUIRE( propertiesQueriedByCategory.back()->GetPropertyType() == SgfcPropertyType::Unknown );
        REQUIRE( propertiesQueriedByCategory.back()->GetPropertyName() == "BB" );
        REQUIRE( propertiesQueriedByCategory.back() == properties.back() );
        REQUIRE( inheritedProperties.size() == 0 );
      }
    }
  }
}

SCENARIO( "SgfcNode is queried for inheritable properties", "[document]" )
{
  auto game = std::make_shared<SgfcGame>();
  SgfcTreeBuilder treeBuilder(game);

  auto rootNode = std::make_shared<SgfcNode>();
  game->SetRootNode(rootNode);
  auto intermediateNode = std::make_shared<SgfcNode>();
  auto intermediateSibling = std::make_shared<SgfcNode>();
  treeBuilder.SetFirstChild(rootNode, intermediateNode);
  treeBuilder.SetNextSibling(intermediateNode, intermediateSibling);
  auto leafNode = std::make_shared<SgfcNode>();
  treeBuilder.SetFirstChild(intermediateNode, leafNode);

  auto propertyDD1 = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::DD, "DD"));
  auto propertyPM1 = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::PM, "PM"));
  auto propertyVW1 = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::VW, "VW"));
  auto propertyDD2 = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::DD, "DD"));
  auto propertyPM2 = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::PM, "PM"));
  auto propertyVW2 = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::VW, "VW"));

  // This must never have an influence on the result because the intermediate
  // sibling node is not on the path to the root node
  auto propertyDD3 = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::DD, "DD"));
  intermediateSibling->SetProperties({propertyDD3});

  GIVEN( "No node in the path to the root node contains properties" )
  {
    WHEN( "Any node on the path is queried for properties" )
    {
      auto inheritedPropertiesLeaf = leafNode->GetInheritedProperties();
      auto inheritedPropertiesIntermediate = intermediateNode->GetInheritedProperties();
      auto inheritedPropertiesRoot = rootNode->GetInheritedProperties();

      THEN( "None of the nodes returns an empty collection" )
      {
        REQUIRE( inheritedPropertiesLeaf.size() == 0 );
        REQUIRE( inheritedPropertiesIntermediate.size() == 0 );
        REQUIRE( inheritedPropertiesRoot.size() == 0 );
      }
    }
  }

  GIVEN( "Some or all nodes in the path to the root node contain properties" )
  {
    WHEN( "Each node contains a single property that is different from all others" )
    {
      leafNode->SetProperties({propertyDD1});
      intermediateNode->SetProperties({propertyPM1});
      rootNode->SetProperties({propertyVW1});

      auto inheritedPropertiesLeaf = leafNode->GetInheritedProperties();
      auto inheritedPropertiesIntermediate = intermediateNode->GetInheritedProperties();
      auto inheritedPropertiesRoot = rootNode->GetInheritedProperties();

      THEN( "The query returns the node's own property and the properties of the ancestor nodes" )
      {
        REQUIRE( inheritedPropertiesLeaf.size() == 3 );
        REQUIRE( inheritedPropertiesLeaf == std::vector({propertyDD1, propertyPM1, propertyVW1}) );
        REQUIRE( inheritedPropertiesIntermediate.size() == 2 );
        REQUIRE( inheritedPropertiesIntermediate == std::vector({propertyPM1, propertyVW1}) );
        REQUIRE( inheritedPropertiesRoot.size() == 1 );
        REQUIRE( inheritedPropertiesRoot == std::vector({propertyVW1}) );
      }
    }

    WHEN( "Each node contains a different number of properties" )
    {
      leafNode->SetProperties({propertyVW1});
      // intermediateNode has no properties
      rootNode->SetProperties({propertyDD1, propertyPM1});

      auto inheritedPropertiesLeaf = leafNode->GetInheritedProperties();
      auto inheritedPropertiesIntermediate = intermediateNode->GetInheritedProperties();
      auto inheritedPropertiesRoot = rootNode->GetInheritedProperties();

      THEN( "The query returns the node's own property and the properties of the ancestor nodes" )
      {
        REQUIRE( inheritedPropertiesLeaf.size() == 3 );
        REQUIRE( inheritedPropertiesLeaf == std::vector({propertyVW1, propertyDD1, propertyPM1}) );
        REQUIRE( inheritedPropertiesIntermediate.size() == 2 );
        REQUIRE( inheritedPropertiesIntermediate == std::vector({propertyDD1, propertyPM1}) );
        REQUIRE( inheritedPropertiesRoot.size() == 2 );
        REQUIRE( inheritedPropertiesRoot == std::vector({propertyDD1, propertyPM1}) );
      }
    }

    WHEN( "Two nodes contain the same property" )
    {
      leafNode->SetProperties({propertyVW1, propertyPM1});
      intermediateNode->SetProperties({propertyVW2, propertyDD1});
      rootNode->SetProperties({propertyDD2, propertyPM2});

      auto inheritedPropertiesLeaf = leafNode->GetInheritedProperties();
      auto inheritedPropertiesIntermediate = intermediateNode->GetInheritedProperties();
      auto inheritedPropertiesRoot = rootNode->GetInheritedProperties();

      THEN( "The query returns the property that is closer to the node" )
      {
        REQUIRE( inheritedPropertiesLeaf.size() == 3 );
        REQUIRE( inheritedPropertiesLeaf == std::vector({propertyVW1, propertyPM1, propertyDD1}) );
        REQUIRE( inheritedPropertiesIntermediate.size() == 3 );
        REQUIRE( inheritedPropertiesIntermediate == std::vector({propertyVW2, propertyDD1, propertyPM2}) );
        REQUIRE( inheritedPropertiesRoot.size() == 2 );
        REQUIRE( inheritedPropertiesRoot == std::vector({propertyDD2, propertyPM2}) );
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
}

SCENARIO( "SgfcNode is used to perform a game tree search", "[document]" )
{
  auto game = std::make_shared<SgfcGame>();
  SgfcTreeBuilder treeBuilder(game);

  auto rootNode = std::make_shared<SgfcNode>();
  auto intermediateNode = std::make_shared<SgfcNode>();
  auto intermediateSiblingNode = std::make_shared<SgfcNode>();
  auto leafNode = std::make_shared<SgfcNode>();
  auto nodeInOtherTree = std::make_shared<SgfcNode>();;

  game->SetRootNode(rootNode);
  treeBuilder.SetFirstChild(rootNode, intermediateNode);
  treeBuilder.SetNextSibling(intermediateNode, intermediateSiblingNode);
  treeBuilder.SetFirstChild(intermediateNode, leafNode);

  GIVEN( "SgfcNode is queried for the root node" )
  {
    WHEN( "SgfcNode is queried with GetRoot and HasRoot" )
    {
      THEN( "SgfcNode returns the correct result" )
      {
        REQUIRE( intermediateNode->GetRoot() == rootNode );
        REQUIRE( intermediateNode->IsRoot() == false );

        REQUIRE( leafNode->GetRoot() == rootNode );
        REQUIRE( leafNode->IsRoot() == false );

        REQUIRE( intermediateSiblingNode->GetRoot() == rootNode );
        REQUIRE( intermediateSiblingNode->IsRoot() == false );

        REQUIRE( rootNode->GetRoot() == rootNode );
        REQUIRE( rootNode->IsRoot() == true );

        REQUIRE( nodeInOtherTree->GetRoot() == nodeInOtherTree );
        REQUIRE( nodeInOtherTree->IsRoot() == true );
      }
    }
  }

  GIVEN( "SgfcNode is queried for the game info node" )
  {
    auto gameInfoProperty = std::shared_ptr<ISgfcProperty>(new SgfcProperty(SgfcPropertyType::AN, "AN"));

    WHEN( "There is no game info node" )
    {
      THEN( "SgfcNode returns nullptr" )
      {
        REQUIRE( rootNode->GetGameInfoNode() == nullptr );
        REQUIRE( intermediateNode->GetGameInfoNode() == nullptr );
        REQUIRE( intermediateSiblingNode->GetGameInfoNode() == nullptr );
        REQUIRE( leafNode->GetGameInfoNode() == nullptr );
        REQUIRE( nodeInOtherTree->GetGameInfoNode() == nullptr );
      }
    }

    WHEN( "The root node is the game info node" )
    {
      rootNode->SetProperties({gameInfoProperty});

      THEN( "SgfcNode returns the root node" )
      {
        REQUIRE( rootNode->GetGameInfoNode() == rootNode );
        REQUIRE( intermediateNode->GetGameInfoNode() == rootNode );
        REQUIRE( intermediateSiblingNode->GetGameInfoNode() == rootNode );
        REQUIRE( leafNode->GetGameInfoNode() == rootNode );
        REQUIRE( nodeInOtherTree->GetGameInfoNode() == nullptr );
      }
    }

    WHEN( "An intermediate node is the game info node" )
    {
      intermediateNode->SetProperties({gameInfoProperty});

      THEN( "SgfcNode returns the intermediate node if possible, or null for ancestors" )
      {
        REQUIRE( rootNode->GetGameInfoNode() == nullptr );
        REQUIRE( intermediateNode->GetGameInfoNode() == intermediateNode );
        REQUIRE( intermediateSiblingNode->GetGameInfoNode() == nullptr );
        REQUIRE( leafNode->GetGameInfoNode() == intermediateNode );
        REQUIRE( nodeInOtherTree->GetGameInfoNode() == nullptr );
      }
    }

    WHEN( "The node itself is the game info node" )
    {
      intermediateNode->SetProperties({gameInfoProperty});

      THEN( "SgfcNode returns the node itself" )
      {
        REQUIRE( intermediateNode->GetGameInfoNode() == intermediateNode );
      }
    }

    WHEN( "The game tree contains several game info nodes" )
    {
      rootNode->SetProperties({gameInfoProperty});
      intermediateNode->SetProperties({gameInfoProperty});

      THEN( "SgfcNode returns the nearest game info node on the path to the game tree root" )
      {
        REQUIRE( rootNode->GetGameInfoNode() == rootNode );
        REQUIRE( intermediateNode->GetGameInfoNode() == intermediateNode );
        REQUIRE( intermediateSiblingNode->GetGameInfoNode() == rootNode );
        REQUIRE( leafNode->GetGameInfoNode() == intermediateNode );
        REQUIRE( nodeInOtherTree->GetGameInfoNode() == nullptr );
      }
    }
  }

  GIVEN( "SgfcNode is queried for the main variation" )
  {
    WHEN( "The root node is queried" )
    {
      std::vector<std::shared_ptr<ISgfcNode>> expectedMainVariationNodes = { rootNode, intermediateNode, leafNode };
      auto mainVariationNodes = rootNode->GetMainVariationNodes();

      THEN( "SgfcNode returns all direct descendants from the root node until the leaf node" )
      {
        REQUIRE( mainVariationNodes.size() == 3 );
        REQUIRE( mainVariationNodes == expectedMainVariationNodes );
      }
    }

    WHEN( "An intermediate node is queried" )
    {
      std::vector<std::shared_ptr<ISgfcNode>> expectedMainVariationNodes = { intermediateNode, leafNode };
      auto mainVariationNodes = intermediateNode->GetMainVariationNodes();

      THEN( "SgfcNode returns all direct descendants from the intermediate node until the leaf node" )
      {
        REQUIRE( mainVariationNodes.size() == 2 );
        REQUIRE( mainVariationNodes == expectedMainVariationNodes );
      }
    }

    WHEN( "A leaf node is queried" )
    {
      std::vector<std::shared_ptr<ISgfcNode>> expectedMainVariationNodes = { leafNode };
      auto mainVariationNodes = leafNode->GetMainVariationNodes();

      THEN( "SgfcNode returns only the leaf node itself" )
      {
        REQUIRE( mainVariationNodes.size() == 1 );
        REQUIRE( mainVariationNodes == expectedMainVariationNodes );
      }
    }
  }
}

SCENARIO( "SgfcNode creates an ISgfcGameInfo object", "[document]" )
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

  GIVEN( "SgfcNode is an empty root node and has no game info node" )
  {
    WHEN( "SgfcNode creates the ISgfcGameInfo object" )
    {
      SgfcGameType expectedGameType = SgfcConstants::DefaultGameType;
      SgfcNumber expectedGameTypeAsNumber = SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType);
      SgfcBoardSize expectedBoardSize = SgfcUtility::GetDefaultBoardSize(expectedGameType);

      auto gameInfo = rootNode->CreateGameInfo();

      THEN( "The ISgfcGameInfo object contains default values" )
      {
        AssertGameInfoHasRootPropertyValues(gameInfo, expectedGameType, expectedGameTypeAsNumber, expectedBoardSize);
      }
    }
  }

  GIVEN( "SgfcNode is the child of an empty root node and has no game info node" )
  {
    WHEN( "SgfcNode creates the ISgfcGameInfo object" )
    {
      SgfcGameType expectedGameType = SgfcConstants::DefaultGameType;
      SgfcNumber expectedGameTypeAsNumber = SgfcUtility::MapGameTypeToNumberValue(SgfcConstants::DefaultGameType);
      SgfcBoardSize expectedBoardSize = SgfcUtility::GetDefaultBoardSize(expectedGameType);

      auto gameInfo = leafNode->CreateGameInfo();

      THEN( "The ISgfcGameInfo object contains default values" )
      {
        AssertGameInfoHasRootPropertyValues(gameInfo, expectedGameType, expectedGameTypeAsNumber, expectedBoardSize);
      }
    }
  }

  GIVEN( "SgfcNode is the child of a non-empty root node and has no game info node" )
  {
    SgfcGameType gameType = GENERATE( SgfcGameType::Go, SgfcGameType::Backgammon );
    SgfcBoardSize boardSize = { 3, 10 };
    bool setupWithTypedProperties = GENERATE( true, false );
    SetupNodeWithGameAndBoardSizeProperties(rootNode, gameType, boardSize, setupWithTypedProperties);

    WHEN( "SgfcNode creates the ISgfcGameInfo object" )
    {
      auto gameInfo = leafNode->CreateGameInfo();

      THEN( "The ISgfcGameInfo object contains the root property values" )
      {
        AssertGameInfoHasRootPropertyValues(gameInfo, gameType, SgfcUtility::MapGameTypeToNumberValue(gameType), boardSize);
      }
    }
  }

  GIVEN( "SgfcNode has a game info node" )
  {
    SgfcSimpleText propertyValue = "foo";
    auto gameInfoProperty = CreateSimpleTextProperty(SgfcPropertyType::US, propertyValue);
    std::vector<std::shared_ptr<ISgfcNode>> testNodes = { rootNode, intermediateNode, leafNode };

    WHEN( "SgfcNode creates the ISgfcGameInfo object" )
    {
      THEN( "The ISgfcGameInfo object contains the game info property values" )
      {
        // TODO: Get this to work with GENERATE_COPY
        for (auto gameInfoNode : testNodes)
        {
          gameInfoNode->SetProperties({gameInfoProperty});
          auto gameInfo = leafNode->CreateGameInfo();

          REQUIRE( gameInfo->GetRecorderName() == propertyValue );

          gameInfoNode->RemoveAllProperties();
        }
      }
    }
  }
}

SCENARIO( "SgfcNode writes an ISgfcGameInfo object", "[document]" )
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

  GIVEN( "SgfcNode has no game info node" )
  {
    SgfcGameType gameType = SgfcGameType::Go;
    SgfcBoardSize boardSize = { 15, 15 };
    bool setupWithTypedProperties = false;
    SetupNodeWithGameAndBoardSizeProperties(rootNode, gameType, boardSize, setupWithTypedProperties);
    auto propertyType = SgfcPropertyType::US;
    SgfcSimpleText recorderName = "foo";
    auto gameInfoProperty = CreateSimpleTextProperty(propertyType, recorderName);
    rootNode->AppendProperty(gameInfoProperty);

    auto gameInfo = leafNode->CreateGameInfo();
    REQUIRE( gameInfo->GetRecorderName() == recorderName );

    rootNode->RemoveAllProperties();

    WHEN( "SgfcNode writes the ISgfcGameInfo object" )
    {
      leafNode->WriteGameInfo(gameInfo);

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

  GIVEN( "SgfcNode has a game info node" )
  {
    auto propertyType = SgfcPropertyType::US;
    SgfcSimpleText recorderName = "foo";
    auto gameInfoProperty = CreateSimpleTextProperty(propertyType, recorderName);
    leafNode->AppendProperty(gameInfoProperty);
    auto gameInfo = leafNode->CreateGameInfo();
    REQUIRE( gameInfo->GetRecorderName() == recorderName );
    SgfcSimpleText newRecorderName = "bar";
    gameInfo->SetRecorderName(newRecorderName);

    WHEN( "SgfcNode writes the ISgfcGameInfo object" )
    {
      leafNode->WriteGameInfo(gameInfo);

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

