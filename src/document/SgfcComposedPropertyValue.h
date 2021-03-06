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
#include "../../include/ISgfcComposedPropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcComposedPropertyValue class provides an implementation of
  /// the ISgfcComposedPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcComposedPropertyValue : public ISgfcComposedPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcComposedPropertyValue object
    /// that consists of the two values @a value1 and @a value2.
    ///
    /// @exception std::invalid_argument Is thrown if @a value1 is @e nullptr
    /// or if @a value2 is @e nullptr.
    SgfcComposedPropertyValue(
      std::shared_ptr<ISgfcSinglePropertyValue> value1,
      std::shared_ptr<ISgfcSinglePropertyValue> value2);

    /// @brief Destroys and cleans up the SgfcSinglePropertyValue object.
    virtual ~SgfcComposedPropertyValue();

    virtual bool IsComposedValue() const override;
    virtual const ISgfcComposedPropertyValue* ToComposedValue() const override;

    virtual std::shared_ptr<ISgfcSinglePropertyValue> GetValue1() const override;
    virtual std::shared_ptr<ISgfcSinglePropertyValue> GetValue2() const override;

  private:
    std::shared_ptr<ISgfcSinglePropertyValue> value1;
    std::shared_ptr<ISgfcSinglePropertyValue> value2;
  };
}
