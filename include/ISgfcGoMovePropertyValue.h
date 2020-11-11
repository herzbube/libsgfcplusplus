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
#include "ISgfcGoMove.h"
#include "ISgfcMovePropertyValue.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcGoMovePropertyValue interface makes the property value
  /// data of a property of type SgfcPropertyValueType::Move available as
  /// an ISgfcGoMove object.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  /// @ingroup go
  class SGFCPLUSPLUS_EXPORT ISgfcGoMovePropertyValue : virtual public ISgfcMovePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGoMovePropertyValue object.
    ISgfcGoMovePropertyValue();

    /// @brief Destroys and cleans up the ISgfcGoMovePropertyValue object.
    virtual ~ISgfcGoMovePropertyValue();

    /// @brief Returns an ISgfcGoMove object that contains the property value
    /// data.
    virtual std::shared_ptr<ISgfcGoMove> GetGoMove() const = 0;
  };
}
