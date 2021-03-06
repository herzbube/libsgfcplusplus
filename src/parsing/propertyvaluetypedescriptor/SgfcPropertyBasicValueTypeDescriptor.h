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
#include "../../../include/SgfcPropertyValueType.h"
#include "../../interface/internal/ISgfcPropertyValueTypeDescriptor.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyBasicValueTypeDescriptor class provides an
  /// implementation of the ISgfcPropertyValueTypeDescriptor interface.
  /// See the interface header file for documentation.
  ///
  /// @ingroup internals
  /// @ingroup parsing
  ///
  /// SgfcPropertyBasicValueTypeDescriptor defines the basic value type that a
  /// single non-composed SGF property value can have. GetValueType() returns
  /// that value type.
  ///
  /// All ISgfcPropertyValueTypeDescriptor implementations except
  /// SgfcPropertyBasicValueTypeDescriptor define complex value types (lists,
  /// composed values) or alternate value types. Ultimately every one of these
  /// other descriptors can be broken down into one or more
  /// SgfcPropertyBasicValueTypeDescriptor objects.
  ///
  /// Example: The "CA" property value is a SimpleText. GetValueType() in this
  /// case returns SgfcPropertyValueType::SimpleText.
  class SgfcPropertyBasicValueTypeDescriptor : public ISgfcPropertyValueTypeDescriptor
  {
  public:
    /// @brief Initializes a newly constructed
    /// SgfcPropertyBasicValueTypeDescriptor object.
    SgfcPropertyBasicValueTypeDescriptor(
      SgfcPropertyValueType valueType);

    /// @brief Destroys and cleans up the SgfcPropertyBasicValueTypeDescriptor
    /// object.
    virtual ~SgfcPropertyBasicValueTypeDescriptor();

    virtual SgfcPropertyValueTypeDescriptorType GetDescriptorType() const override;
    virtual const SgfcPropertyBasicValueTypeDescriptor* ToBasicValueTypeDescriptor() const override;

    /// @brief Returns the value type defined by the
    /// SgfcPropertyBasicValueTypeDescriptor.
    virtual SgfcPropertyValueType GetValueType() const;

  private:
    SgfcPropertyValueType valueType;
  };
}
