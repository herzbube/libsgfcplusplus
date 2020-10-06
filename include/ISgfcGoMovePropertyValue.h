#pragma once

// Project includes
#include "ISgfcGoMove.h"
#include "ISgfcMovePropertyValue.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcGoMovePropertyValue interface makes the property value
  /// data of a property of type SgfcPropertyValueType::Move available as
  /// an ISgfcGoMove object.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  /// @ingroup go
  class SGFCPLUSPLUS_EXPORT ISgfcGoMovePropertyValue : virtual public ISgfcMovePropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGoMovePropertyValue object.
    ISgfcGoMovePropertyValue();

    /// @brief Destroys and cleans up the ISgfcGoMovePropertyValue object.
    virtual ~ISgfcGoMovePropertyValue();

    /// @brief Returns an ISgfcGoMove object that contains the property value
    /// data. The ISgfcGoMove object does not contain an ISgfcGoPoint object
    /// if interpretation of the property value data is not possible.
    virtual std::shared_ptr<ISgfcGoMove> GetGoMove() const = 0;
  };
}
