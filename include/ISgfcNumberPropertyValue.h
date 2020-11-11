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
  /// @brief The ISgfcNumberPropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Number.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  ///
  /// ISgfcNumberPropertyValue is immutable, i.e. once the
  /// ISgfcNumberPropertyValue object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcNumberPropertyValue : virtual public ISgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcNumberPropertyValue object.
    ISgfcNumberPropertyValue();

    /// @brief Destroys and cleans up the ISgfcNumberPropertyValue object.
    virtual ~ISgfcNumberPropertyValue();

    /// @brief Returns the property value interpreted as an SgfcNumber value.
    virtual SgfcNumber GetNumberValue() const = 0;
  };
}
