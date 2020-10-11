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
#include "SgfcPropertyComposedValueTypeDescriptor.h"
#include "SgfcPropertyBasicValueTypeDescriptor.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcPropertyComposedValueTypeDescriptor::SgfcPropertyComposedValueTypeDescriptor(
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1,
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2)
    : descriptorValueType1(descriptorValueType1)
    , descriptorValueType2(descriptorValueType2)
  {
    if (this->descriptorValueType1->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::BasicValueType ||
        this->descriptorValueType2->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::BasicValueType)
    {
      throw std::logic_error("One or both of the two descriptor objects are not SgfcPropertyBasicValueTypeDescriptor objects");
    }

    if (this->descriptorValueType1->ToBasicValueTypeDescriptor()->GetValueType() == SgfcPropertyValueType::None ||
        this->descriptorValueType2->ToBasicValueTypeDescriptor()->GetValueType() == SgfcPropertyValueType::None)
    {
      throw std::logic_error("One or both of the two descriptor objects have value type SgfcPropertyValueType::None");
    }
  }

  SgfcPropertyComposedValueTypeDescriptor::~SgfcPropertyComposedValueTypeDescriptor()
  {
  }

  SgfcPropertyValueTypeDescriptorType SgfcPropertyComposedValueTypeDescriptor::GetDescriptorType() const
  {
    return SgfcPropertyValueTypeDescriptorType::ComposedValueType;
  }

  const SgfcPropertyComposedValueTypeDescriptor* SgfcPropertyComposedValueTypeDescriptor::ToComposedValueTypeDescriptor() const
  {
    return this;
  }

  std::shared_ptr<ISgfcPropertyValueTypeDescriptor> SgfcPropertyComposedValueTypeDescriptor::GetDescriptorValueType1() const
  {
    return this->descriptorValueType1;
  }

  std::shared_ptr<ISgfcPropertyValueTypeDescriptor> SgfcPropertyComposedValueTypeDescriptor::GetDescriptorValueType2() const
  {
    return this->descriptorValueType2;
  }
}
