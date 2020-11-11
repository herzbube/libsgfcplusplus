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
#include "../../../include/ISgfcNumberPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcNumberPropertyValue class provides an implementation of
  /// the ISgfcNumberPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcNumberPropertyValue : public SgfcSinglePropertyValue, public ISgfcNumberPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcNumberPropertyValue object.
    /// The object holds the Number value @a numberValue and
    /// the corresponding raw string value @a rawValue.
    SgfcNumberPropertyValue(const std::string& rawValue, SgfcNumber numberValue);

    /// @brief Destroys and cleans up the SgfcNumberPropertyValue object.
    virtual ~SgfcNumberPropertyValue();

    virtual SgfcNumber GetNumberValue() const;
    virtual const ISgfcNumberPropertyValue* ToNumberValue() const;

  private:
    SgfcNumber numberValue;
  };
}
