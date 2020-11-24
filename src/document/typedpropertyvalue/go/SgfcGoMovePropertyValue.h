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
#include "../../../../include/ISgfcGoMovePropertyValue.h"
#include "../SgfcMovePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoMovePropertyValue class provides an implementation of
  /// the ISgfcGoMovePropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  /// @ingroup go
  class SgfcGoMovePropertyValue : public SgfcMovePropertyValue, public ISgfcGoMovePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcGoMovePropertyValue object.
    /// The object holds a Move value represented by @a goMove.
    ///
    /// If @a goMove is a pass move SgfcGoMovePropertyValue uses
    /// SgfcConstants::GoMovePassString as the raw property value.
    ///
    /// If @a goMove is not a pass move SgfcGoMovePropertyValue uses the
    /// SGF notation of the ISgfcGoPoint object referenced by @a goMove
    /// (indirectly via ISgfcGoStone) as the raw property value. This refers to
    /// the location of the stone that is placed by the move on the board.
    ///
    /// @exception std::invalid_argument Is thrown if @a goMove is nullptr.
    SgfcGoMovePropertyValue(std::shared_ptr<ISgfcGoMove> goMove);

    /// @brief Destroys and cleans up the SgfcGoMovePropertyValue object.
    virtual ~SgfcGoMovePropertyValue();

    virtual const ISgfcGoMovePropertyValue* ToGoMoveValue() const override;
    virtual std::shared_ptr<ISgfcGoMove> GetGoMove() const override;

  private:
    std::shared_ptr<ISgfcGoMove> goMove;

    std::string GetRawValueOrThrow(std::shared_ptr<ISgfcGoMove> goMove);
  };
}
