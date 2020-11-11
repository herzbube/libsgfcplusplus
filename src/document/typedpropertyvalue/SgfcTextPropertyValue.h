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
#include "../../../include/ISgfcTextPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcTextPropertyValue class provides an implementation of
  /// the ISgfcTextPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcTextPropertyValue : public SgfcSinglePropertyValue, public ISgfcTextPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcTextPropertyValue
    /// object. The object holds the SimpleText value @a textValue and
    /// the corresponding raw string value @a rawValue.
    SgfcTextPropertyValue(const std::string& rawValue, const std::string& textValue);

    /// @brief Destroys and cleans up the SgfcTextPropertyValue object.
    virtual ~SgfcTextPropertyValue();

    virtual std::string GetTextValue() const;
    virtual const ISgfcTextPropertyValue* ToTextValue() const;

  private:
    std::string textValue;
  };
}
