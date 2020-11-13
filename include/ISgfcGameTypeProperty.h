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
#include "ISgfcProperty.h"
#include "SgfcGameType.h"
#include "SgfcTypedefs.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcGameTypeProperty interface is a specialization of
  /// ISgfcProperty for SgfcPropertyType::GM. It simplifies access to the
  /// property value and provides the value in the form of an SgfcGameType
  /// value.
  ///
  /// @ingroup public-api
  /// @ingroup property
  class SGFCPLUSPLUS_EXPORT ISgfcGameTypeProperty : virtual public ISgfcProperty
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGameTypeProperty object.
    ISgfcGameTypeProperty();

    /// @brief Destroys and cleans up the ISgfcGameTypeProperty object.
    virtual ~ISgfcGameTypeProperty();

    /// @brief Returns the property value(s) interpreted as an SgfcGameType
    /// value.
    ///
    /// @retval SgfcGameType If the property has a single Number value, and
    ///         that value is defined in the SGF standard, then the SgfcGameType
    ///         value that corresponds to the Number value is returned. The
    ///         value is guaranteed not to be SgfcGameType::Unknown.
    /// @retval SgfcConstants::DefaultGameType If the property has no value.
    ///         The value is guaranteed not to be SgfcGameType::Unknown.
    /// @retval SgfcGameType::Unknown If the property's value(s) cannot be
    ///         converted to a Number value (the property has more than one
    ///         value, or the single value is not a Number value), or if
    ///         conversion is possible but the Number value is not defined in
    ///         the SGF standard. Invoke GetGameTypeAsNumber() to obtain the
    ///         game type as Number value.
    virtual SgfcGameType GetGameType() const = 0;

    /// @brief Returns the property value(s) interpreted as an SgfcNumber value.
    ///
    /// This is useful if GetGameType() returns SgfcGameType::Unknown because
    /// the Number value is not defined in the SGF standard and cannot be mapped
    /// to a member of the enumeration SgfcGameType.
    ///
    /// @retval SgfcNumber If the property contains a single Number value, then
    ///         that Number value is returned. If the property has no value,
    ///         then this method returns the Number value that corresponds to
    ///         SgfcConstants::DefaultGameType.
    /// @retval SgfcConstants::GameTypeNaN If the property's value(s) cannot be
    ///         converted to a Number value, either because the property has
    ///         more than one value, or its single value is not a Number value.
    virtual SgfcNumber GetGameTypeAsNumber() const = 0;
  };
}
