// Project includes
#include "SgfcPropertyListValueTypeDescriptor.h"

namespace LibSgfcPlusPlus
{
  SgfcPropertyListValueTypeDescriptor::SgfcPropertyListValueTypeDescriptor(
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorElementValueType)
    : descriptorElementValueType(descriptorElementValueType)
  {
  }

  SgfcPropertyListValueTypeDescriptor::~SgfcPropertyListValueTypeDescriptor()
  {
  }

  SgfcPropertyValueTypeDescriptorType SgfcPropertyListValueTypeDescriptor::GetDescriptorType() const
  {
    return SgfcPropertyValueTypeDescriptorType::ListValueType;
  }

  const SgfcPropertyDualValueTypeDescriptor* SgfcPropertyListValueTypeDescriptor::ToDualValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyElistValueTypeDescriptor* SgfcPropertyListValueTypeDescriptor::ToElistValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyListValueTypeDescriptor* SgfcPropertyListValueTypeDescriptor::ToListValueTypeDescriptor() const
  {
    return this;
  }

  const SgfcPropertyComposedValueTypeDescriptor* SgfcPropertyListValueTypeDescriptor::ToComposedValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyBasicValueTypeDescriptor* SgfcPropertyListValueTypeDescriptor::ToBasicValueTypeDescriptor() const
  {
    return nullptr;
  }

  std::shared_ptr<ISgfcPropertyValueTypeDescriptor> SgfcPropertyListValueTypeDescriptor::GetDescriptorElementValueType() const
  {
    return this->descriptorElementValueType;
  }
}
