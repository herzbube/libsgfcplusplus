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
#include "../../../../include/ISgfcGoPointPropertyValue.h"
#include "../SgfcPointPropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoPointPropertyValue class provides an implementation of
  /// the ISgfcGoPointPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  /// @ingroup go
  class SgfcGoPointPropertyValue : public SgfcPointPropertyValue, public ISgfcGoPointPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcGoPointPropertyValue object.
    /// The object holds a Point value represented by @a goPoint.
    ///
    /// SgfcGoPointPropertyValue uses the SGF notation of @a goPoint as the
    /// raw property value.
    ///
    /// @exception std::invalid_argument Is thrown if @a goPoint is nullptr.
    SgfcGoPointPropertyValue(std::shared_ptr<ISgfcGoPoint> goPoint);

    /// @brief Destroys and cleans up the SgfcGoPointPropertyValue object.
    virtual ~SgfcGoPointPropertyValue();

    virtual const ISgfcGoPointPropertyValue* ToGoPointValue() const override;
    virtual std::shared_ptr<ISgfcGoPoint> GetGoPoint() const override;

  private:
    std::shared_ptr<ISgfcGoPoint> goPoint;

    std::string GetRawValueOrThrow(std::shared_ptr<ISgfcGoPoint> goPoint);
  };
}
