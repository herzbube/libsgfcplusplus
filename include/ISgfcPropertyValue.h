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

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcComposedPropertyValue;
  class ISgfcSinglePropertyValue;

  /// @brief The ISgfcPropertyValue interface provides access to one of the
  /// values of a property of an SGF node.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  ///
  /// ISgfcPropertyValue is immutable, i.e. once the ISgfcPropertyValue object
  /// is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcPropertyValue object.
    ISgfcPropertyValue();

    /// @brief Destroys and cleans up the ISgfcPropertyValue object.
    virtual ~ISgfcPropertyValue();

    /// @brief Returns true if the ISgfcPropertyValue object holds a "composed"
    /// value, i.e. a value that consists of a composite of two single values.
    /// Returns false if the ISgfcPropertyValue holds only a single value.
    virtual bool IsComposedValue() const = 0;

    /// @brief Returns @e nullptr if IsComposedValue() returns true. Returns an
    /// ISgfcSinglePropertyValue object if IsComposedValue() returns false. The
    /// caller is not the owner of the ISgfcSinglePropertyValue object.
    virtual const ISgfcSinglePropertyValue* ToSingleValue() const;

    /// @brief Returns an ISgfcComposedPropertyValue object if IsComposedValue()
    /// returns true. Returns @e nullptr if IsComposedValue() returns false. The
    /// caller is not the owner of the ISgfcComposedPropertyValue object.
    virtual const ISgfcComposedPropertyValue* ToComposedValue() const;
  };
}
