#pragma once

// Project includes
#include "ISgfcGoPoint.h"
#include "ISgfcPointPropertyValue.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcGoPointPropertyValue interface makes the property value
  /// data of a property of type SgfcPropertyValueType::Point available as
  /// an ISgfcGoPoint object.
  class SGFCPLUSPLUS_EXPORT ISgfcGoPointPropertyValue : virtual public ISgfcPointPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGoPointPropertyValue object.
    ISgfcGoPointPropertyValue();

    /// @brief Destroys and cleans up the ISgfcGoPointPropertyValue object.
    virtual ~ISgfcGoPointPropertyValue();

    /// @brief Returns an ISgfcGoPoint object that contains the property value
    /// data and makes it available in various forms and notations.
    virtual std::shared_ptr<ISgfcGoPoint> GetGoPoint() const = 0;
  };
}
