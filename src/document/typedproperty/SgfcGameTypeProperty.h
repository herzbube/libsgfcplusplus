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
#include "../../../include/ISgfcGameTypeProperty.h"
#include "../SgfcProperty.h"

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcNumberPropertyValue;

  /// @brief The SgfcGameTypeProperty class provides an implementation of
  /// the ISgfcGameTypeProperty interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property
  class SgfcGameTypeProperty : public SgfcProperty, public ISgfcGameTypeProperty
  {
  public:
    /// @brief Initializes a newly constructed SgfcGameTypeProperty object. The
    /// property has no value.
    SgfcGameTypeProperty();

    /// @brief Initializes a newly constructed SgfcGameTypeProperty object. The
    /// property has the specified property value @a propertyValue.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyValue is
    /// @e nullptr.
    SgfcGameTypeProperty(
      std::shared_ptr<ISgfcNumberPropertyValue> propertyValue);

    /// @brief Destroys and cleans up the SgfcGameTypeProperty object.
    virtual ~SgfcGameTypeProperty();

    virtual const ISgfcGameTypeProperty* ToGameTypeProperty() const override;

    virtual SgfcGameType GetGameType() const override;
    virtual SgfcNumber GetGameTypeAsNumber() const override;
  };
}
