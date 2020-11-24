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
#include "../../../include/ISgfcPointPropertyValue.h"
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPointPropertyValue class provides an implementation of
  /// the ISgfcPointPropertyValue interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  class SgfcPointPropertyValue : public SgfcSinglePropertyValue, virtual public ISgfcPointPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcPointPropertyValue
    /// object. The object holds the Point value @a pointValue and
    /// the corresponding raw string value @a rawValue.
    SgfcPointPropertyValue(const std::string& rawValue, const SgfcPoint& pointValue);

    /// @brief Destroys and cleans up the SgfcPointPropertyValue object.
    virtual ~SgfcPointPropertyValue();

    virtual SgfcPoint GetPointValue() const override;
    virtual const ISgfcPointPropertyValue* ToPointValue() const override;
    virtual const ISgfcGoPointPropertyValue* ToGoPointValue() const override;

  private:
    SgfcPoint pointValue;
  };
}
