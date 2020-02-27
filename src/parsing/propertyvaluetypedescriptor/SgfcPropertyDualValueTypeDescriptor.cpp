// Project includes
#include "SgfcPropertyDualValueTypeDescriptor.h"

namespace LibSgfcPlusPlus
{
  SgfcPropertyDualValueTypeDescriptor::SgfcPropertyDualValueTypeDescriptor(
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1,
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2)
    : descriptorValueType1(descriptorValueType1)
    , descriptorValueType2(descriptorValueType2)
  {
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

  const SgfcPropertyElistValueTypeDescriptor* SgfcPropertyDualValueTypeDescriptor::ToElistValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyListValueTypeDescriptor* SgfcPropertyDualValueTypeDescriptor::ToListValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyComposedValueTypeDescriptor* SgfcPropertyDualValueTypeDescriptor::ToComposedValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyBasicValueTypeDescriptor* SgfcPropertyDualValueTypeDescriptor::ToBasicValueTypeDescriptor() const
  {
    return nullptr;
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
