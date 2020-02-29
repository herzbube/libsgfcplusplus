// Project includes
#include "ISgfcPropertyValueTypeDescriptor.h"

namespace LibSgfcPlusPlus
{
  ISgfcPropertyValueTypeDescriptor::ISgfcPropertyValueTypeDescriptor()
  {
  }

  ISgfcPropertyValueTypeDescriptor::~ISgfcPropertyValueTypeDescriptor()
  {
  }

  const SgfcPropertyDualValueTypeDescriptor* ISgfcPropertyValueTypeDescriptor::ToDualValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyElistValueTypeDescriptor* ISgfcPropertyValueTypeDescriptor::ToElistValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyListValueTypeDescriptor* ISgfcPropertyValueTypeDescriptor::ToListValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyComposedValueTypeDescriptor* ISgfcPropertyValueTypeDescriptor::ToComposedValueTypeDescriptor() const
  {
    return nullptr;
  }

  const SgfcPropertyBasicValueTypeDescriptor* ISgfcPropertyValueTypeDescriptor::ToBasicValueTypeDescriptor() const
  {
    return nullptr;
  }
}
