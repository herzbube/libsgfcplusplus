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

  const SgfcPropertyDualValueTypeDescriptor* SgfcPropertyElistValueTypeDescriptor::ToDualValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyElistValueTypeDescriptor* SgfcPropertyElistValueTypeDescriptor::ToElistValueTypeDescriptor() const
  {
    return this;
  }

  const SgfcPropertyListValueTypeDescriptor* SgfcPropertyElistValueTypeDescriptor::ToListValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyComposedValueTypeDescriptor* SgfcPropertyElistValueTypeDescriptor::ToComposedValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyBasicValueTypeDescriptor* SgfcPropertyElistValueTypeDescriptor::ToBasicValueTypeDescriptor() const
  {
    return nullptr;
  }

  std::shared_ptr<SgfcPropertyListValueTypeDescriptor> SgfcPropertyElistValueTypeDescriptor::GetDescriptorListValueType() const
  {
    return this->descriptorListValueType;
  }
}
