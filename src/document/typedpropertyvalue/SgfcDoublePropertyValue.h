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
#include "../../../include/ISgfcDoublePropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDoublePropertyValue class provides an implementation of
  /// the ISgfcDoublePropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcDoublePropertyValue : public SgfcSinglePropertyValue, public ISgfcDoublePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcDoublePropertyValue object.
    /// The object holds the Double value @a doubleValue and
    /// the corresponding raw string value @a rawValue.
    SgfcDoublePropertyValue(const std::string& rawValue, SgfcDouble doubleValue);

    /// @brief Destroys and cleans up the SgfcDoublePropertyValue object.
    virtual ~SgfcDoublePropertyValue();

    virtual SgfcDouble GetDoubleValue() const override;
    virtual const ISgfcDoublePropertyValue* ToDoubleValue() const override;

  private:
    SgfcDouble doubleValue;
  };
}
