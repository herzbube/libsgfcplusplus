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
#include "SgfcPropertyDualValueTypeDescriptor.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcPropertyDualValueTypeDescriptor::SgfcPropertyDualValueTypeDescriptor(
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1,
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2)
    : descriptorValueType1(descriptorValueType1)
    , descriptorValueType2(descriptorValueType2)
  {
    if ((this->descriptorValueType1->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::BasicValueType &&
         this->descriptorValueType1->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::ComposedValueType) ||
        (this->descriptorValueType2->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::BasicValueType &&
         this->descriptorValueType2->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::ComposedValueType))
    {
      throw std::logic_error("One or both of the two descriptor objects are neither SgfcPropertyBasicValueTypeDescriptor nor SgfcPropertyComposedValueTypeDescriptor objects");
    }
  }

  SgfcPropertyDualValueTypeDescriptor::~SgfcPropertyDualValueTypeDescriptor()
  {
  }

  SgfcPropertyValueTypeDescriptorType SgfcPropertyDualValueTypeDescriptor::GetDescriptorType() const
  {
    return SgfcPropertyValueTypeDescriptorType::DualValueType;
  }

  const SgfcPropertyDualValueTypeDescriptor* SgfcPropertyDualValueTypeDescriptor::ToDualValueTypeDescriptor() const
  {
    return this;
  }

  std::shared_ptr<ISgfcPropertyValueTypeDescriptor> SgfcPropertyDualValueTypeDescriptor::GetDescriptorValueType1() const
  {
    return this->descriptorValueType1;
  }

  std::shared_ptr<ISgfcPropertyValueTypeDescriptor> SgfcPropertyDualValueTypeDescriptor::GetDescriptorValueType2() const
  {
    return this->descriptorValueType2;
  }
}
