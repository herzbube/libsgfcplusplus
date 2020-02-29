// Project includes
#include "SgfcPropertyComposedValueTypeDescriptor.h"
#include "SgfcPropertyBasicValueTypeDescriptor.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcPropertyComposedValueTypeDescriptor::SgfcPropertyComposedValueTypeDescriptor(
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1,
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2)
    : descriptorValueType1(descriptorValueType1)
    , descriptorValueType2(descriptorValueType2)
  {
    if (this->descriptorValueType1->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::BasicValueType ||
        this->descriptorValueType2->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::BasicValueType)
    {
      throw std::logic_error("One or both of the two descriptor objects are not SgfcPropertyBasicValueTypeDescriptor objects");
    }

    if (this->descriptorValueType1->ToBasicValueTypeDescriptor()->GetValueType() == SgfcPropertyValueType::None ||
        this->descriptorValueType2->ToBasicValueTypeDescriptor()->GetValueType() == SgfcPropertyValueType::None)
    {
      throw std::logic_error("One or both of the two descriptor objects have value type SgfcPropertyValueType::None");
    }
  }

  SgfcPropertyComposedValueTypeDescriptor::~SgfcPropertyComposedValueTypeDescriptor()
  {
  }

  SgfcPropertyValueTypeDescriptorType SgfcPropertyComposedValueTypeDescriptor::GetDescriptorType() const
  {
    return SgfcPropertyValueTypeDescriptorType::ComposedValueType;
  }

  const SgfcPropertyComposedValueTypeDescriptor* SgfcPropertyComposedValueTypeDescriptor::ToComposedValueTypeDescriptor() const
  {
    return this;
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
