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
  /// @brief The SgfcPropertyComposedValueTypeDescriptor interface provides an
  /// implementation of the ISgfcPropertyValueTypeDescriptor interface.
  /// See the interface header file for documentation.
  ///
  /// @ingroup internals
  /// @ingroup parsing
  ///
  /// SgfcPropertyComposedValueTypeDescriptor expresses the fact that for some
  /// properties the raw SGF property value is composed of two values, separated
  /// by a colon (":") character. GetDescriptorValueType1() returns a descriptor
  /// for the value type of the first value, GetDescriptorValueType2() returns a
  /// descriptor for the value type of the second value.
  ///
  /// @note The two descriptors must be SgfcPropertyBasicValueTypeDescriptor
  /// objects, and their value types must not be SgfcPropertyValueType::None.
  ///
  /// Example: The "AP" property value is composed of two SimpleText values
  /// separated by a ":" character. Both GetDescriptorValueType1() and
  /// GetDescriptorValueType2() in this case return
  /// SgfcPropertyBasicValueTypeDescriptor objects which both have the basic
  /// value type SgfcPropertyValueType::SimpleText.
  class SgfcPropertyComposedValueTypeDescriptor : public ISgfcPropertyValueTypeDescriptor
  {
  public:
    /// @brief Initializes a newly constructed
    /// SgfcPropertyComposedValueTypeDescriptor object.
    ///
    /// @exception std::logic_error Is thrown if one or both of the two
    /// descriptor objects are not SgfcPropertyBasicValueTypeDescriptor objects,
    /// or if the basic value type is SgfcPropertyValueType::None.
    SgfcPropertyComposedValueTypeDescriptor(
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1,
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2);

    /// @brief Destroys and cleans up the
    /// SgfcPropertyComposedValueTypeDescriptor object.
    virtual ~SgfcPropertyComposedValueTypeDescriptor();

    virtual SgfcPropertyValueTypeDescriptorType GetDescriptorType() const;
    virtual const SgfcPropertyComposedValueTypeDescriptor* ToComposedValueTypeDescriptor() const;

    /// @brief Returns an ISgfcPropertyValueTypeDescriptor object that describes
    /// the value type of the first value.
    virtual std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetDescriptorValueType1() const;

    /// @brief Returns an ISgfcPropertyValueTypeDescriptor object that describes
    /// the value type of the second value.
    virtual std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetDescriptorValueType2() const;

  private:
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1;
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2;
  };
}
