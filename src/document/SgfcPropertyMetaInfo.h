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
#include "../../include/SgfcGameType.h"
#include "../../include/SgfcPropertyType.h"
#include "../../include/SgfcPropertyValueType.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcPropertyValueTypeDescriptor;
  class SgfcPropertyDualValueTypeDescriptor;
  class SgfcPropertyElistValueTypeDescriptor;
  class SgfcPropertyListValueTypeDescriptor;

  /// @brief The SgfcPropertyMetaInfo class provides meta information about a
  /// property and the values it can have according to the SGF standard.
  ///
  /// @ingroup internals
  /// @ingroup property
  ///
  /// At the moment SgfcPropertyMetaInfo is used to store a mapping between
  /// a property type / game type combination and a value type descriptor
  /// object.
  class SgfcPropertyMetaInfo
  {
  public:
    /// @brief Initializes a newly constructed SgfcPropertyMetaInfo object.
    SgfcPropertyMetaInfo(SgfcPropertyType propertyType, SgfcGameType gameType);

    /// @brief Destroys and cleans up the SgfcPropertyMetaInfo object.
    virtual ~SgfcPropertyMetaInfo();

    /// @brief Returns the type of the property that was passed to the
    /// constructor. The value SgfcPropertyType::Unknown indicates that the
    /// property is a custom property that is not defined in the SGF standard.
    SgfcPropertyType GetPropertyType() const;

    /// @brief Returns the game type for which the property can contain values.
    /// This is the value that was passed to the constructor. The value
    /// SgfcGameType::Unknown indicates that the game type is not defined in the
    /// SGF standard.
    ///
    /// The game type is important because for some properties the SGF standard
    /// specifies different value types for different game types.
    SgfcGameType GetGameType() const;

    /// @brief Returns a value type descriptor object which describes the types
    /// of all values that the property can possibly have.
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetValueTypeDescriptor() const;

    /// @brief Returns true if the property can have a value of the type
    /// @a propertyValueType. Returns true if the property cannot have a value
    /// of the type @a propertyValueType.
    ///
    /// This is a convenience method that queries the value type descriptor
    /// object returned by GetValueTypeDescriptor() on behalf of the caller.
    bool CanPropertyHaveValueType(SgfcPropertyValueType propertyValueType) const;

  private:
    SgfcPropertyType propertyType;
    SgfcGameType gameType;
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> valueTypeDescriptor;

    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetValueTypeDescriptorInternal() const;

    bool CanPropertyHaveValueTypeInternal(
      const SgfcPropertyDualValueTypeDescriptor* dualValueTypeDescriptor,
      SgfcPropertyValueType propertyValueType) const;

    bool CanPropertyHaveValueTypeInternal(
      const SgfcPropertyElistValueTypeDescriptor* elistValueTypeDescriptor,
      SgfcPropertyValueType propertyValueType) const;

    bool CanPropertyHaveValueTypeInternal(
      const SgfcPropertyListValueTypeDescriptor* listValueTypeDescriptor,
      SgfcPropertyValueType propertyValueType) const;

    bool CanPropertyHaveValueTypeInternal(
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> valueTypeDescriptor,
      SgfcPropertyValueType propertyValueType) const;
  };
}
