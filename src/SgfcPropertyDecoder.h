#pragma once

// Project includes
#include "../include/SgfcPropertyType.h"

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

  private:
    SgfcPropertyDecoder();
    virtual ~SgfcPropertyDecoder();
  };
}
