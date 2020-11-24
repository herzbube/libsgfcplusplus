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
#include "../../interface/internal/ISgfcPropertyValueTypeDescriptor.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyListValueTypeDescriptor class provides an
  /// implementation of the ISgfcPropertyValueTypeDescriptor interface.
  /// See the interface header file for documentation.
  ///
  /// @ingroup internals
  /// @ingroup parsing
  ///
  /// SgfcPropertyListValueTypeDescriptor expresses the fact that some
  /// SGF properties can have more than one value.
  /// GetDescriptorElementValueType() returns a descriptor for the list element
  /// value type.
  ///
  /// @note The descriptor must be either an
  /// SgfcPropertyBasicValueTypeDescriptor or an
  /// SgfcPropertyComposedValueTypeDescriptor object. In both cases the basic
  /// value types must not be SgfcPropertyValueType::None.
  ///
  /// @note A list type property has at least one value. Properties which allow
  /// zero values are "elists".
  ///
  /// Example: The "LB" property value is a list of composed Point/SimpleText
  /// elements. GetDescriptorElementValueType() in this case returns an
  /// SgfcPropertyComposedValueTypeDescriptor object, which in turn is composed
  /// of two descriptors of type SgfcPropertyBasicValueTypeDescriptor, the first
  /// having the basic value type SgfcPropertyValueType::Point and the second.
  /// having the basic value type SgfcPropertyValueType::SimpleText.
  class SgfcPropertyListValueTypeDescriptor : public ISgfcPropertyValueTypeDescriptor
  {
  public:
    /// @brief Initializes a newly constructed
    /// SgfcPropertyListValueTypeDescriptor object.
    ///
    /// @exception std::logic_error Is thrown if the descriptor object is
    /// neither an SgfcPropertyBasicValueTypeDescriptor nor an
    /// SgfcPropertyComposedValueTypeDescriptor object, or if the basic value
    /// type is SgfcPropertyValueType::None.
    SgfcPropertyListValueTypeDescriptor(
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorElementValueType);

    /// @brief Destroys and cleans up the SgfcPropertyListValueTypeDescriptor
    /// object.
    virtual ~SgfcPropertyListValueTypeDescriptor();

    virtual SgfcPropertyValueTypeDescriptorType GetDescriptorType() const override;
    virtual const SgfcPropertyListValueTypeDescriptor* ToListValueTypeDescriptor() const override;

    /// @brief Returns an ISgfcPropertyValueTypeDescriptor object that describes
    /// the value type of the list elements.
    virtual std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetDescriptorElementValueType() const;

  private:
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorElementValueType;
  };
}
