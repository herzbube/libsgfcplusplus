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
#include "../SgfcSinglePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcUnknownPropertyValue class provides access to one of
  /// the values of a property of an SGF node. The value type is
  /// SgfcPropertyValueType::Unknown. SgfcUnknownPropertyValue is an
  /// implementation of the ISgfcSinglePropertyValue interface. See the
  /// interface header file for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property-value
  ///
  /// Unlike other values from the enumeration SgfcPropertyValueType,
  /// the value SgfcPropertyValueType::Unknown does not describe a concrete
  /// value type. To the contrary, SgfcPropertyValueType::Unknown signifies the
  /// @e absence of a known value type. Because of this the public interface of
  /// libsgfc++ has no interface type that corresponds to
  /// SgfcPropertyValueType::Unknown. Library users that encounter
  /// SgfcPropertyValueType::Unknown have to work with the raw property string
  /// value, and for that ISgfcSinglePropertyValue is sufficient.
  ///
  /// SgfcUnknownPropertyValue is immutable, i.e. once the
  /// SgfcUnknownPropertyValue object is constructed it cannot be changed.
  class SgfcUnknownPropertyValue : public SgfcSinglePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed SgfcUnknownPropertyValue object.
    /// The object holds no type value because the value type of the raw string
    /// value @a rawValue is not known.
    SgfcUnknownPropertyValue(const std::string& rawValue);

    /// @brief Destroys and cleans up the SgfcUnknownPropertyValue object.
    virtual ~SgfcUnknownPropertyValue();

    virtual SgfcPropertyValueType GetValueType() const;
  };
}
