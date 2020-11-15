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
#include "SgfcTypedefs.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcGoMovePropertyValue;

  /// @brief The ISgfcMovePropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Move.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  ///
  /// ISgfcMovePropertyValue is immutable, i.e. once the
  /// ISgfcMovePropertyValue object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcMovePropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcMovePropertyValue object.
    ISgfcMovePropertyValue();

    /// @brief Destroys and cleans up the ISgfcMovePropertyValue object.
    virtual ~ISgfcMovePropertyValue();

    /// @brief Returns the property value interpreted as an SgfcMove value.
    virtual SgfcMove GetMoveValue() const = 0;

    /// @brief Returns an ISgfcGoMovePropertyValue object if the property
    /// value object was created specifically for SgfcGameType::Go. Returns
    /// @e nullptr otherwise. The caller is not the owner of the returned
    /// object.
    virtual const ISgfcGoMovePropertyValue* ToGoMoveValue() const = 0;
  };
}
