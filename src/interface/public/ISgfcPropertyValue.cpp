// Project includes
#include "../../../include/ISgfcPropertyValue.h"

namespace LibSgfcPlusPlus
{
  ISgfcPropertyValue::ISgfcPropertyValue()
  {
  }

  ISgfcPropertyValue::~ISgfcPropertyValue()
  {
  }

  const ISgfcSinglePropertyValue* ISgfcPropertyValue::ToSingleValue() const
  {
    return nullptr;
  }

  const ISgfcComposedPropertyValue* ISgfcPropertyValue::ToComposedValue() const
  {
    return nullptr;
  }
}
