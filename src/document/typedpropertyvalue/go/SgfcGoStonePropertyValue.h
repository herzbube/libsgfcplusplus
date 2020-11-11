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
#include "../../../../include/ISgfcGoStonePropertyValue.h"
#include "../SgfcStonePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoStonePropertyValue class provides an implementation of
  /// the ISgfcGoStonePropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  /// @ingroup go
  class SgfcGoStonePropertyValue : public SgfcStonePropertyValue, public ISgfcGoStonePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcGoStonePropertyValue object.
    /// The object holds a Point value represented by @a goStone.
    ///
    /// SgfcGoStonePropertyValue uses the SGF notation of the ISgfcGoPoint
    /// object referenced by @a goStone as the raw property value. This refers
    /// to the location of the stone on the board.
    ///
    /// @exception std::invalid_argument Is thrown if @a goStone is nullptr.
    SgfcGoStonePropertyValue(std::shared_ptr<ISgfcGoStone> goStone);

    /// @brief Destroys and cleans up the SgfcGoStonePropertyValue object.
    virtual ~SgfcGoStonePropertyValue();

    virtual const ISgfcGoStonePropertyValue* ToGoStoneValue() const;
    virtual std::shared_ptr<ISgfcGoStone> GetGoStone() const;

  private:
    std::shared_ptr<ISgfcGoStone> goStone;

    std::string GetRawValueOrThrow(std::shared_ptr<ISgfcGoStone> goStone);
  };
}
