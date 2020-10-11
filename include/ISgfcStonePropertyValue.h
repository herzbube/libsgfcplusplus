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
#include "ISgfcSinglePropertyValue.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcGoStonePropertyValue;

  /// @brief The ISgfcStonePropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Stone.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  ///
  /// ISgfcStonePropertyValue is immutable, i.e. once the
  /// ISgfcStonePropertyValue object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcStonePropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcStonePropertyValue object.
    ISgfcStonePropertyValue();

    /// @brief Destroys and cleans up the ISgfcStonePropertyValue object.
    virtual ~ISgfcStonePropertyValue();

    /// @brief Returns the uninterpreted stone value. This is the same value
    /// that GetRawValue() returns.
    ///
    /// The SGF standard does not provide a universal definition of how a stone
    /// value should look like. Instead it says that the interpretation of
    /// stone values is game specific.
    virtual std::string GetRawStoneValue() const = 0;

    /// @brief Returns an ISgfcGoStonePropertyValue object if the game tree that
    /// this property value is associated with has SgfcGameType::Go. Returns
    /// @e nullptr otherwise. The caller is not the owner of the returned
    /// object.
    virtual const ISgfcGoStonePropertyValue* ToGoStoneValue() const = 0;
  };
}
