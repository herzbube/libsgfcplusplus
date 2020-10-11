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
#include "SgfcPropertyListValueTypeDescriptor.h"

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyElistValueTypeDescriptor interface provides an
  /// implementation of the ISgfcPropertyValueTypeDescriptor interface.
  /// See the interface header file for documentation.
  ///
  /// @ingroup internals
  /// @ingroup parsing
  ///
  /// SgfcPropertyElistValueTypeDescriptor expresses the fact that for some
  /// properties the raw SGF property value can be either
  /// SgfcPropertyValueType::None or some other type. Which one needs to be
  /// determined by probing, i.e. by parsing the raw property value.
  /// GetDescriptorListValueType() always returns an
  /// SgfcPropertyListValueTypeDescriptor, which in turn is composed of another
  /// descriptor that defines the value type of the list elements.
  ///
  /// @note The SgfcPropertyListValueTypeDescriptor object must be composed of
  /// either an SgfcPropertyBasicValueTypeDescriptor or an
  /// SgfcPropertyComposedValueTypeDescriptor object.
  ///
  /// SgfcPropertyElistValueTypeDescriptor could also be expressed with an
  /// SgfcPropertyDualValueTypeDescriptor. SgfcPropertyElistValueTypeDescriptor
  /// exists as a dedicated type only because the SGF standard explicitly names
  /// and describes "elist" in its EBNF definition section.
  ///
  /// Example: The "DD" property value either is None, or it is a list of
  /// Point. GetDescriptorListValueType() in this case returns an
  /// SgfcPropertyListValueTypeDescriptor object, which in turn is composed
  /// of a descriptor of type SgfcPropertyBasicValueTypeDescriptor which has
  /// the basic value type SgfcPropertyValueType::Point.
  class SgfcPropertyElistValueTypeDescriptor : public ISgfcPropertyValueTypeDescriptor
  {
  public:
    /// @brief Initializes a newly constructed
    /// SgfcPropertyElistValueTypeDescriptor object.
    SgfcPropertyElistValueTypeDescriptor(
      std::shared_ptr<SgfcPropertyListValueTypeDescriptor> descriptorListValueType);

    /// @brief Destroys and cleans up the SgfcPropertyElistValueTypeDescriptor
    /// object.
    virtual ~SgfcPropertyElistValueTypeDescriptor();

    virtual SgfcPropertyValueTypeDescriptorType GetDescriptorType() const;
    virtual const SgfcPropertyElistValueTypeDescriptor* ToElistValueTypeDescriptor() const;

    /// @brief Returns an SgfcPropertyListValueTypeDescriptor object that
    /// is composed of another descriptor that defines the value type of the
    /// list elements.
    virtual std::shared_ptr<SgfcPropertyListValueTypeDescriptor> GetDescriptorListValueType() const;

  private:
    std::shared_ptr<SgfcPropertyListValueTypeDescriptor> descriptorListValueType;
  };
}
