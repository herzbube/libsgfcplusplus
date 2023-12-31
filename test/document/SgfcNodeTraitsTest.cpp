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
#include <SgfcConstants.h>
#include <SgfcNodeTraits.h>

// Unit test library includes
#include <catch2/catch_test_macros.hpp>

// C++ Standard Library includes
#include <cmath>  // for pow()

using namespace LibSgfcPlusPlus;


// The tests in this file are used to demonstrate that the various bitwise
// operators defined for the type SgfcNodeTrait work as expected. Bitwise
// operators defined for other trait types (e.g. SgfcPropertyTrait) are assumed
// to work the same and are not explicitly tested.


SCENARIO( "An SgfcNodeTraits value is created from SgfcNodeTrait", "[document]" )
{
  GIVEN( "One of the bitwise AND operators is used" )
  {
    SgfcNodeTraits initialTraits = SgfcConstants::NodeTraitsAll;

    WHEN( "An SgfcNodeTraits value is AND'ed with an SgfcNodeTrait value" )
    {
      SgfcNodeTrait trait = SgfcNodeTrait::GameInfo;
      auto traitsResult = initialTraits & trait;

      THEN( "The result contains only the AND'ed SgfcNodeTrait value" )
      {
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsNone );
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsAll );
        REQUIRE( traitsResult == static_cast<SgfcNodeTraits>(trait) );
      }
    }

    WHEN( "An SgfcNodeTrait value is AND'ed with another SgfcNodeTrait value" )
    {
      SgfcNodeTrait trait1 = SgfcNodeTrait::GameInfo;
      SgfcNodeTrait trait2 = SgfcNodeTrait::NodeAnnotation;
      auto traitsResult = trait1 & trait2;

      THEN( "The result is SgfcConstants::NodeTraitsNone" )
      {
        REQUIRE( traitsResult == SgfcConstants::NodeTraitsNone );
      }
    }

    WHEN( "An SgfcNodeTraits value is AND'ed and assigned with an SgfcNodeTrait value" )
    {
      SgfcNodeTrait trait = SgfcNodeTrait::Setup;
      auto traitsResult = initialTraits;
      traitsResult &= trait;

      THEN( "The result contains only the AND'ed SgfcNodeTrait value" )
      {
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsNone );
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsAll );
        REQUIRE( traitsResult == static_cast<SgfcNodeTraits>(trait) );
      }
    }
  }

  GIVEN( "One of the bitwise OR operators is used" )
  {
    SgfcNodeTraits initialTraits = SgfcConstants::NodeTraitsNone;

    WHEN( "An SgfcNodeTraits value is OR'ed with an SgfcNodeTrait value" )
    {
      SgfcNodeTrait trait = SgfcNodeTrait::GameInfo;
      auto traitsResult = initialTraits | trait;

      THEN( "The result contains the OR'ed SgfcNodeTrait value" )
      {
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsNone );
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsAll );
        REQUIRE( traitsResult == static_cast<SgfcNodeTraits>(trait) );
      }
    }

    WHEN( "An SgfcNodeTrait value is OR'ed with another SgfcNodeTrait value" )
    {
      SgfcNodeTrait trait1 = SgfcNodeTrait::GameInfo;
      SgfcNodeTrait trait2 = SgfcNodeTrait::NodeAnnotation;
      auto traitsResult = trait1 | trait2;

      THEN( "The result contains both OR'ed SgfcNodeTrait values" )
      {
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsNone );
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsAll );
        REQUIRE( traitsResult == (static_cast<SgfcNodeTraits>(trait1) + static_cast<SgfcNodeTraits>(trait2)) );
      }
    }

    WHEN( "An SgfcNodeTraits value is OR'ed and assigned with an SgfcNodeTrait value" )
    {
      SgfcNodeTrait trait = SgfcNodeTrait::Setup;
      auto traitsResult = initialTraits;
      traitsResult |= trait;

      THEN( "The result contains the original SgfcNodeTraits value plus the OR'ed SgfcNodeTrait value" )
      {
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsNone );
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsAll );
        REQUIRE( traitsResult == static_cast<SgfcNodeTraits>(trait) );
      }
    }
  }

  GIVEN( "One of the bitwise XOR operators is used" )
  {
    SgfcNodeTraits initialTraits = SgfcConstants::NodeTraitsAll;

    WHEN( "An SgfcNodeTraits value is XOR'ed with an SgfcNodeTrait value" )
    {
      SgfcNodeTrait trait = SgfcNodeTrait::GameInfo;
      auto traitsResult = initialTraits ^ trait;

      THEN( "The result does not contain the XOR'ed SgfcNodeTrait value" )
      {
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsNone );
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsAll );
        REQUIRE( (traitsResult | trait) == SgfcConstants::NodeTraitsAll );
      }
    }

    WHEN( "An SgfcNodeTrait value is XOR'ed with another SgfcNodeTrait value" )
    {
      SgfcNodeTrait trait1 = SgfcNodeTrait::GameInfo;
      SgfcNodeTrait trait2 = SgfcNodeTrait::NodeAnnotation;
      auto traitsResult = trait1 ^ trait2;

      THEN( "The result contains both XOR'ed SgfcNodeTrait values" )
      {
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsNone );
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsAll );
        REQUIRE( traitsResult == (static_cast<SgfcNodeTraits>(trait1) + static_cast<SgfcNodeTraits>(trait2)) );
      }
    }

    WHEN( "An SgfcNodeTraits value that already contains an SgfcNodeTrait value is XOR'ed and assigned with the SgfcNodeTrait value" )
    {
      SgfcNodeTrait trait = SgfcNodeTrait::Setup;
      auto traitsResult = initialTraits;
      traitsResult ^= trait;

      THEN( "The result does not contain the XOR'ed SgfcNodeTrait value" )
      {
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsNone );
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsAll );
        REQUIRE( (traitsResult | trait) == SgfcConstants::NodeTraitsAll );
      }
    }

    WHEN( "An SgfcNodeTraits value that does not contain an SgfcNodeTrait value is XOR'ed and assigned with the SgfcNodeTrait value" )
    {
      SgfcNodeTrait trait = SgfcNodeTrait::Setup;
      auto traitsResult = SgfcConstants::NodeTraitsNone;
      traitsResult ^= trait;

      THEN( "The result contains the XOR'ed SgfcNodeTrait value" )
      {
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsNone );
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsAll );
        REQUIRE( traitsResult == static_cast<SgfcNodeTraits>(trait) );
      }
    }
  }

  GIVEN( "The left shift operator is used" )
  {
    SgfcNodeTraits initialTraits = SgfcConstants::NodeTraitsAll;

    WHEN( "An SgfcNodeTraits value is left shift'ed by 1" )
    {
      SgfcNodeTrait smallestTrait = SgfcNodeTrait::Root;
      auto traitsResult = initialTraits << 1;

      THEN( "The result does not contain the smallest trait bit" )
      {
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsNone );
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsAll );
        REQUIRE( (traitsResult | smallestTrait) == SgfcConstants::NodeTraitsAll );
      }
    }
  }

  GIVEN( "The right shift operator is used" )
  {
    SgfcNodeTraits initialTraits = SgfcConstants::NodeTraitsAll;

    WHEN( "An SgfcNodeTraits value is right shift'ed by 1" )
    {
      // Calculate this dynamically to support different sizes of the underlying
      // primitive type on different platforms
      int numberOfBits = sizeof(SgfcNodeTraits) * 8;
      int highestOrderBit = numberOfBits - 1;
      // Use static_cast to avoid a compiler warning (pow returns double).
      SgfcNodeTraits highestTrait = static_cast<SgfcNodeTraits>(pow(2, highestOrderBit));

      auto traitsResult = initialTraits >> 1;

      THEN( "The result does not contain the highest trait bit" )
      {
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsNone );
        REQUIRE( traitsResult != SgfcConstants::NodeTraitsAll );
        REQUIRE( (traitsResult | highestTrait) == SgfcConstants::NodeTraitsAll );
      }
    }
  }
}
