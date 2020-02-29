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
