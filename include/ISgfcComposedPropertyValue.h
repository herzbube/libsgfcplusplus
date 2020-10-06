#pragma once

// Project includes
#include "ISgfcPropertyValue.h"
#include "ISgfcSinglePropertyValue.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcComposedPropertyValue interface provides access to one of
  /// the values of a property of an SGF node. The value is a composite of two
  /// ISgfcSinglePropertyValue objects.
  ///
  /// @ingroup public-api
  /// @ingroup property-value
  ///
  /// The class name uses the term "composed" because that is how it appears in
  /// the SGF standard.
  ///
  /// ISgfcComposedPropertyValue is immutable, i.e. once the
  /// ISgfcComposedPropertyValue object is constructed it cannot be changed.
  class SGFCPLUSPLUS_EXPORT ISgfcComposedPropertyValue : public ISgfcPropertyValue
  {
  public:
    /// @brief Initializes a newly constructed ISgfcComposedPropertyValue
    /// object.
    ISgfcComposedPropertyValue();

     /// @brief Destroys and cleans up the ISgfcComposedPropertyValue object.
     virtual ~ISgfcComposedPropertyValue();

    /// @brief Returns the first property value.
    virtual std::shared_ptr<ISgfcSinglePropertyValue> GetValue1() const = 0;

    /// @brief Returns the first property value.
    virtual std::shared_ptr<ISgfcSinglePropertyValue> GetValue2() const = 0;
  };
}
