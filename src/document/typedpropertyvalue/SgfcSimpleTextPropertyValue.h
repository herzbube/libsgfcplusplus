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
#include "../../../include/ISgfcSimpleTextPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcSimpleTextPropertyValue class provides an implementation of
  /// the ISgfcSimpleTextPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcSimpleTextPropertyValue : public SgfcSinglePropertyValue, public ISgfcSimpleTextPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcSimpleTextPropertyValue
    /// object. The object holds the SgfcSimpleText value @a simpleTextValue and
    /// the corresponding raw string value @a rawValue.
    SgfcSimpleTextPropertyValue(const std::string& rawValue, const SgfcSimpleText& simpleTextValue);

    /// @brief Destroys and cleans up the SgfcSimpleTextPropertyValue object.
    virtual ~SgfcSimpleTextPropertyValue();

    virtual SgfcSimpleText GetSimpleTextValue() const;
    virtual const ISgfcSimpleTextPropertyValue* ToSimpleTextValue() const;

  private:
    SgfcSimpleText simpleTextValue;
  };
}
