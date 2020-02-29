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
