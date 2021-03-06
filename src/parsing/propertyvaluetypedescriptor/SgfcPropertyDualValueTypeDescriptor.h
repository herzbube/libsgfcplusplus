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
  /// @brief The SgfcPropertyDualValueTypeDescriptor class provides an
  /// implementation of the ISgfcPropertyValueTypeDescriptor interface.
  /// See the interface header file for documentation.
  ///
  /// @ingroup internals
  /// @ingroup parsing
  ///
  /// SgfcPropertyDualValueTypeDescriptor expresses the fact that for some
  /// properties the raw SGF property value can be either of a first type, or a
  /// second type. Which one needs to be determined by probing, i.e. by parsing
  /// the raw property value. GetDescriptorValueType1() returns a descriptor for
  /// the first possible value type, GetDescriptorValueType2() returns a
  /// descriptor for the second possible value type.
  ///
  /// @note The two descriptors must be either
  /// SgfcPropertyBasicValueTypeDescriptor or
  /// SgfcPropertyComposedValueTypeDescriptor objects.
  ///
  /// Example: The "SZ" property value either is a single number, or it is a
  /// composed Number/Number. GetDescriptorValueType1() in this case returns an
  /// SgfcPropertyBasicValueTypeDescriptor object which has the basic value
  /// type SgfcPropertyValueType::Number. GetDescriptorValueType2() returns an
  /// SgfcPropertyComposedValueTypeDescriptor object, which in turn is composed
  /// of two descriptors of type SgfcPropertyBasicValueTypeDescriptor, both of
  /// which have the basic value type SgfcPropertyValueType::Number.
  class SgfcPropertyDualValueTypeDescriptor : public ISgfcPropertyValueTypeDescriptor
  {
  public:
    /// @brief Initializes a newly constructed
    /// SgfcPropertyDualValueTypeDescriptor object.
    ///
    /// @exception std::logic_error Is thrown if one or both of the
    /// two descriptor objects are neither SgfcPropertyBasicValueTypeDescriptor
    /// nor SgfcPropertyComposedValueTypeDescriptor objects.
    SgfcPropertyDualValueTypeDescriptor(
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1,
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2);

    /// @brief Destroys and cleans up the SgfcPropertyDualValueTypeDescriptor
    /// object.
    virtual ~SgfcPropertyDualValueTypeDescriptor();

    virtual SgfcPropertyValueTypeDescriptorType GetDescriptorType() const override;
    virtual const SgfcPropertyDualValueTypeDescriptor* ToDualValueTypeDescriptor() const override;

    /// @brief Returns an ISgfcPropertyValueTypeDescriptor object that describes
    /// the first of the two possible value types.
    virtual std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetDescriptorValueType1() const;

    /// @brief Returns an ISgfcPropertyValueTypeDescriptor object that describes
    /// the second of the two possible value types.
    virtual std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetDescriptorValueType2() const;

  private:
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1;
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2;
  };
}
