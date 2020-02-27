#pragma once

// Project includes
#include "../../include/SgfcPropertyType.h"
#include "../interface/internal/ISgfcPropertyValueTypeDescriptor.h"

// C++ Standard Library includes
#include <memory>

// Forward declarations
struct Property;

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyDecoder class parses the raw strings that SGFC
  /// provides for SGF properties and their values, and generates proper
  /// objects from those parsing activities.
  class SgfcPropertyDecoder
  {
  public:
    static SgfcPropertyType GetSgfcPropertyTypeFromSgfProperty(Property* sgfProperty);
    static std::shared_ptr<ISgfcPropertyValueTypeDescriptor> GetValueTypeDescriptorForPropertyType(
      SgfcPropertyType propertyType);

  private:
    SgfcPropertyDecoder();
    virtual ~SgfcPropertyDecoder();
  };
}
