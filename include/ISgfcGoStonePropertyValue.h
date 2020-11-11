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
#include "ISgfcGoStone.h"
#include "ISgfcStonePropertyValue.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcGoStonePropertyValue interface makes the property value
  /// data of a property of type SgfcPropertyValueType::Stone available as
  /// an ISgfcGoStone object.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  /// @ingroup go
  class SGFCPLUSPLUS_EXPORT ISgfcGoStonePropertyValue : virtual public ISgfcStonePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGoStonePropertyValue object.
    ISgfcGoStonePropertyValue();

    /// @brief Destroys and cleans up the ISgfcGoStonePropertyValue object.
    virtual ~ISgfcGoStonePropertyValue();

    /// @brief Returns an ISgfcGoStone object that contains the property value
    /// data.
    virtual std::shared_ptr<ISgfcGoStone> GetGoStone() const = 0;
  };
}
