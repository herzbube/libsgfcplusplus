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
#include "ISgfcPropertyValue.h"
#include "ISgfcSinglePropertyValue.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcComposedPropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value is a composite of two
  /// ISgfcSinglePropertyValue objects.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  ///
  /// The class name uses the term "composed" because that is how it appears in
  /// the SGF standard.
  ///
  /// ISgfcComposedPropertyValue is immutable, i.e. once the
  /// ISgfcComposedPropertyValue object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcComposedPropertyValue : public ISgfcPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcComposedPropertyValue
    /// object.
    ISgfcComposedPropertyValue();

     /// @brief Destroys and cleans up the ISgfcComposedPropertyValue object.
     virtual ~ISgfcComposedPropertyValue();

    /// @brief Returns the first property value.
    virtual std::shared_ptr<ISgfcSinglePropertyValue> GetValue1() const = 0;

    /// @brief Returns the first property value.
    virtual std::shared_ptr<ISgfcSinglePropertyValue> GetValue2() const = 0;
  };
}
