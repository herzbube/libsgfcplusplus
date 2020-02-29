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

  const SgfcPropertyBasicValueTypeDescriptor* SgfcPropertyBasicValueTypeDescriptor::ToBasicValueTypeDescriptor() const
  {
    return this;
  }

  SgfcPropertyValueType SgfcPropertyBasicValueTypeDescriptor::GetValueType() const
  {
    return this->valueType;
  }
}
