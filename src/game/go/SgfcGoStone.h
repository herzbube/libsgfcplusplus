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
#include "../../../include/ISgfcGoStone.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoStone class provides an implementation of the
  /// ISgfcGoStone interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup go
  class SgfcGoStone : public ISgfcGoStone
  {
  public:
    /// @brief Initializes a newly constructed SgfcGoStone object. @a color and
    /// @a location indicate the color and location of the stone.
    ///
    /// @exception std::invalid_argument Is thrown if @a location is nullptr.
    SgfcGoStone(SgfcColor color, std::shared_ptr<ISgfcGoPoint> location);

    /// @brief Destroys and cleans up the SgfcGoStone object.
    virtual ~SgfcGoStone();

    virtual SgfcColor GetColor() const override;
    virtual std::shared_ptr<ISgfcGoPoint> GetLocation() const override;

  private:
    SgfcColor color;
    std::shared_ptr<ISgfcGoPoint> location;
  };
}
