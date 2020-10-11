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

// Project includes
#include "SgfcPropertyListValueTypeDescriptor.h"
#include "SgfcPropertyBasicValueTypeDescriptor.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcPropertyListValueTypeDescriptor::SgfcPropertyListValueTypeDescriptor(
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorElementValueType)
    : descriptorElementValueType(descriptorElementValueType)
  {
    if (this->descriptorElementValueType->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::BasicValueType &&
        this->descriptorElementValueType->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::ComposedValueType)
    {
      throw std::logic_error("The descriptor object is neither an SgfcPropertyBasicValueTypeDescriptor nor an SgfcPropertyComposedValueTypeDescriptor object");
    }

    // No need to check the value type for
    // SgfcPropertyComposedValueTypeDescriptor objects - the
    // SgfcPropertyComposedValueTypeDescriptor constructor already performs the
    // check.

    if (this->descriptorElementValueType->GetDescriptorType() == SgfcPropertyValueTypeDescriptorType::BasicValueType &&
        this->descriptorElementValueType->ToBasicValueTypeDescriptor()->GetValueType() == SgfcPropertyValueType::None)
    {
      throw std::logic_error("One or both of the two descriptor objects have value type SgfcPropertyValueType::None");
    }
  }

  SgfcPropertyListValueTypeDescriptor::~SgfcPropertyListValueTypeDescriptor()
  {
  }

  SgfcPropertyValueTypeDescriptorType SgfcPropertyListValueTypeDescriptor::GetDescriptorType() const
  {
    return SgfcPropertyValueTypeDescriptorType::ListValueType;
  }

  const SgfcPropertyListValueTypeDescriptor* SgfcPropertyListValueTypeDescriptor::ToListValueTypeDescriptor() const
  {
    return this;
  }

  std::shared_ptr<ISgfcPropertyValueTypeDescriptor> SgfcPropertyListValueTypeDescriptor::GetDescriptorElementValueType() const
  {
    return this->descriptorElementValueType;
  }
}
