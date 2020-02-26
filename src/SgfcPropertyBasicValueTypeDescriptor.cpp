// Project includes
#include "SgfcPropertyBasicValueTypeDescriptor.h"

namespace LibSgfcPlusPlus
{
  SgfcPropertyBasicValueTypeDescriptor::SgfcPropertyBasicValueTypeDescriptor(
    SgfcPropertyValueType valueType)
    : valueType(valueType)
  {
  }

  SgfcPropertyBasicValueTypeDescriptor::~SgfcPropertyBasicValueTypeDescriptor()
  {
  }

  SgfcPropertyValueTypeDescriptorType SgfcPropertyBasicValueTypeDescriptor::GetDescriptorType() const
  {
    return SgfcPropertyValueTypeDescriptorType::BasicValueType;
  }

  const SgfcPropertyDualValueTypeDescriptor* SgfcPropertyBasicValueTypeDescriptor::ToDualValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyElistValueTypeDescriptor* SgfcPropertyBasicValueTypeDescriptor::ToElistValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyListValueTypeDescriptor* SgfcPropertyBasicValueTypeDescriptor::ToListValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyComposedValueTypeDescriptor* SgfcPropertyBasicValueTypeDescriptor::ToComposedValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyBasicValueTypeDescriptor* SgfcPropertyBasicValueTypeDescriptor::ToBasicValueTypeDescriptor() const
  {
    return this;
  }

  SgfcPropertyValueType SgfcPropertyBasicValueTypeDescriptor::GetValueType() const
  {
    return this->valueType;
  }
}
