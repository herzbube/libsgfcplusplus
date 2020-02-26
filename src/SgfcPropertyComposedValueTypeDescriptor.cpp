// Project includes
#include "SgfcPropertyComposedValueTypeDescriptor.h"

namespace LibSgfcPlusPlus
{
  SgfcPropertyComposedValueTypeDescriptor::SgfcPropertyComposedValueTypeDescriptor(
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1,
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2)
    : descriptorValueType1(descriptorValueType1)
    , descriptorValueType2(descriptorValueType2)
  {
  }

  SgfcPropertyComposedValueTypeDescriptor::~SgfcPropertyComposedValueTypeDescriptor()
  {
  }

  SgfcPropertyValueTypeDescriptorType SgfcPropertyComposedValueTypeDescriptor::GetDescriptorType() const
  {
    return SgfcPropertyValueTypeDescriptorType::ComposedValueType;
  }

  const SgfcPropertyDualValueTypeDescriptor* SgfcPropertyComposedValueTypeDescriptor::ToDualValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyElistValueTypeDescriptor* SgfcPropertyComposedValueTypeDescriptor::ToElistValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyListValueTypeDescriptor* SgfcPropertyComposedValueTypeDescriptor::ToListValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyComposedValueTypeDescriptor* SgfcPropertyComposedValueTypeDescriptor::ToComposedValueTypeDescriptor() const
  {
    return this;
  }

  const SgfcPropertyBasicValueTypeDescriptor* SgfcPropertyComposedValueTypeDescriptor::ToBasicValueTypeDescriptor() const
  {
    return nullptr;
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
