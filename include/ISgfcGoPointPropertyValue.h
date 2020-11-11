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
#include "ISgfcGoPoint.h"
#include "ISgfcPointPropertyValue.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcGoPointPropertyValue interface makes the property value
  /// data of a property of type SgfcPropertyValueType::Point available as
  /// an ISgfcGoPoint object.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  /// @ingroup go
  class SGFCPLUSPLUS_EXPORT ISgfcGoPointPropertyValue : virtual public ISgfcPointPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGoPointPropertyValue object.
    ISgfcGoPointPropertyValue();

    /// @brief Destroys and cleans up the ISgfcGoPointPropertyValue object.
    virtual ~ISgfcGoPointPropertyValue();

    /// @brief Returns an ISgfcGoPoint object that contains the property value
    /// data and makes it available in various forms and notations.
    virtual std::shared_ptr<ISgfcGoPoint> GetGoPoint() const = 0;
  };
}
