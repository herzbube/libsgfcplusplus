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
#include "SgfcColor.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  class ISgfcGoPoint;

  /// @brief The ISgfcGoStone interface represents a Go stone.
  ///
  /// @ingroup public-api
  /// @ingroup go
  ///
  /// A Go stone on a Go board is defined by its color and by its location on
  /// the Go board. ISgfcGoStone stores an SgfcColor value and a reference to an
  /// ISgfcGoPoint object to record these two pieces of information.
  class SGFCPLUSPLUS_EXPORT ISgfcGoStone
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGoStone object.
    ISgfcGoStone();

    /// @brief Destroys and cleans up the ISgfcGoStone object.
    virtual ~ISgfcGoStone();

    /// @brief Returns the color of the stone.
    virtual SgfcColor GetColor() const = 0;

    /// @brief Returns the location of the stone on the Go board.
    virtual std::shared_ptr<ISgfcGoPoint> GetLocation() const = 0;
  };
}
