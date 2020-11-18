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
#include "../../include/SgfcPropertyTraits.h"

namespace LibSgfcPlusPlus
{
  SgfcPropertyTraits operator&(SgfcPropertyTraits lhs, SgfcPropertyTrait rhs)
  {
    return lhs & static_cast<SgfcPropertyTraits>(rhs);
  }

  SgfcPropertyTraits operator&(SgfcPropertyTrait lhs, SgfcPropertyTrait rhs)
  {
    return static_cast<SgfcPropertyTraits>(lhs) & static_cast<SgfcPropertyTraits>(rhs);
  }

  SgfcPropertyTraits& operator&=(SgfcPropertyTraits& lhs, SgfcPropertyTrait rhs)
  {
    lhs = lhs & static_cast<SgfcPropertyTraits>(rhs);
    return lhs;
  }

  SgfcPropertyTraits operator|(SgfcPropertyTraits lhs, SgfcPropertyTrait rhs)
  {
    return lhs | static_cast<SgfcPropertyTraits>(rhs);
  }

  SgfcPropertyTraits operator|(SgfcPropertyTrait lhs, SgfcPropertyTrait rhs)
  {
    return static_cast<SgfcPropertyTraits>(lhs) | static_cast<SgfcPropertyTraits>(rhs);
  }

  SgfcPropertyTraits& operator|=(SgfcPropertyTraits& lhs, SgfcPropertyTrait rhs)
  {
    lhs = lhs | static_cast<SgfcPropertyTraits>(rhs);
    return lhs;
  }

  SgfcPropertyTraits operator^(SgfcPropertyTraits lhs, SgfcPropertyTrait rhs)
  {
    return lhs ^ static_cast<SgfcPropertyTraits>(rhs);
  }

  SgfcPropertyTraits operator^(SgfcPropertyTrait lhs, SgfcPropertyTrait rhs)
  {
    return static_cast<SgfcPropertyTraits>(lhs) ^ static_cast<SgfcPropertyTraits>(rhs);
  }

  SgfcPropertyTraits& operator^=(SgfcPropertyTraits& lhs, SgfcPropertyTrait rhs)
  {
    lhs = lhs ^ static_cast<SgfcPropertyTraits>(rhs);
    return lhs;
  }

  SgfcPropertyTraits operator<<(SgfcPropertyTrait lhs, unsigned short numberOfBitsToShift)
  {
    return lhs << numberOfBitsToShift;
  }

  SgfcPropertyTraits operator>>(SgfcPropertyTrait lhs, unsigned short numberOfBitsToShift)
  {
    return lhs >> numberOfBitsToShift;
  }

  SgfcPropertyTraits operator~(SgfcPropertyTrait rhs)
  {
    return ~ static_cast<SgfcPropertyTraits>(rhs);
  }
}
