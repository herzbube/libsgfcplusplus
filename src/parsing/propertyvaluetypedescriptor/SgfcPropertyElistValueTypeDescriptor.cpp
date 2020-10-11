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
#include "SgfcPropertyElistValueTypeDescriptor.h"

namespace LibSgfcPlusPlus
{
  SgfcPropertyElistValueTypeDescriptor::SgfcPropertyElistValueTypeDescriptor(
    std::shared_ptr<SgfcPropertyListValueTypeDescriptor> descriptorListValueType)
    : descriptorListValueType(descriptorListValueType)
  {
  }

  SgfcPropertyElistValueTypeDescriptor::~SgfcPropertyElistValueTypeDescriptor()
  {
  }

  SgfcPropertyValueTypeDescriptorType SgfcPropertyElistValueTypeDescriptor::GetDescriptorType() const
  {
    return SgfcPropertyValueTypeDescriptorType::ElistValueType;
  }

  const SgfcPropertyElistValueTypeDescriptor* SgfcPropertyElistValueTypeDescriptor::ToElistValueTypeDescriptor() const
  {
    return this;
  }

  std::shared_ptr<SgfcPropertyListValueTypeDescriptor> SgfcPropertyElistValueTypeDescriptor::GetDescriptorListValueType() const
  {
    return this->descriptorListValueType;
  }
}
