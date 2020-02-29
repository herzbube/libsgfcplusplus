// Project includes
#include "SgfcPropertyListValueTypeDescriptor.h"
#include "SgfcPropertyBasicValueTypeDescriptor.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcPropertyListValueTypeDescriptor::SgfcPropertyListValueTypeDescriptor(
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorElementValueType)
    : descriptorElementValueType(descriptorElementValueType)
  {
    if (this->descriptorElementValueType->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::BasicValueType &&
        this->descriptorElementValueType->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::ComposedValueType)
    {
      throw std::logic_error("The descriptor object is neither an SgfcPropertyBasicValueTypeDescriptor nor an SgfcPropertyComposedValueTypeDescriptor object");
    }

    // No need to check the value type for
    // SgfcPropertyComposedValueTypeDescriptor objects - the
    // SgfcPropertyComposedValueTypeDescriptor constructor already performs the
    // check.

    if (this->descriptorElementValueType->GetDescriptorType() == SgfcPropertyValueTypeDescriptorType::BasicValueType &&
        this->descriptorElementValueType->ToBasicValueTypeDescriptor()->GetValueType() == SgfcPropertyValueType::None)
    {
      throw std::logic_error("One or both of the two descriptor objects have value type SgfcPropertyValueType::None");
    }
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
