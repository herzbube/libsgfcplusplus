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
#include "../../../include/ISgfcStonePropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcStonePropertyValue class provides an implementation of
  /// the ISgfcStonePropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcStonePropertyValue : public SgfcSinglePropertyValue, virtual public ISgfcStonePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcStonePropertyValue
    /// object. The object holds the Stone value @a stoneValue and
    /// the corresponding raw string value @a rawValue.
    SgfcStonePropertyValue(const std::string& rawValue, const SgfcStone& stoneValue);

    /// @brief Destroys and cleans up the SgfcStonePropertyValue object.
    virtual ~SgfcStonePropertyValue();

    virtual SgfcStone GetStoneValue() const;
    virtual const ISgfcStonePropertyValue* ToStoneValue() const;
    virtual const ISgfcGoStonePropertyValue* ToGoStoneValue() const;

  private:
    SgfcStone stoneValue;
  };
}
