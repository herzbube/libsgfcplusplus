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
#include "../../../include/ISgfcMovePropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcMovePropertyValue class provides an implementation of
  /// the ISgfcMovePropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcMovePropertyValue : public SgfcSinglePropertyValue, virtual public ISgfcMovePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcMovePropertyValue
    /// object. The object holds the Move value @a moveValue and
    /// the corresponding raw string value @a rawValue.
    SgfcMovePropertyValue(const std::string& rawValue, const SgfcMove& moveValue);

    /// @brief Destroys and cleans up the SgfcMovePropertyValue object.
    virtual ~SgfcMovePropertyValue();

    virtual SgfcMove GetMoveValue() const override;
    virtual const ISgfcMovePropertyValue* ToMoveValue() const override;
    virtual const ISgfcGoMovePropertyValue* ToGoMoveValue() const override;

  private:
    SgfcMove moveValue;
  };
}
