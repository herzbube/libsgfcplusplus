#pragma once

// Project includes
#include "ISgfcPropertyValue.h"
#include "SgfcPropertyType.h"

// C++ Standard Library includes
#include <memory>
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcBoardSizeProperty;

  /// @brief The ISgfcProperty interface provides access to the data of a single
  /// property of an SGF node. One property has 0-n values.
  ///
  /// @todo Accept properties not defined in the standard. This is
  /// allowed by the standard.
  ///
  /// @todo The standard says that "Only one of each property is allowed per
  /// node, e.g. one cannot have two comments in one node." How does SGFC deal
  /// duplicate properties? Do we want to support this as well?
  class ISgfcProperty
  {
  public:
    /// @brief Initializes a newly constructed ISgfcProperty object.
    ISgfcProperty();

    /// @brief Destroys and cleans up the ISgfcProperty object.
    virtual ~ISgfcProperty();

    /// @brief Returns the type of the property. Returns
    /// SgfcPropertyType::Unknown if the property is a custom property that is
    /// not defined in the SGF standard.
    ///
    /// The property type cannot be changed after the ISgfcProperty has been
    /// constructed.
    virtual SgfcPropertyType GetPropertyType() const = 0;

    /// @brief Returns the name of the property.
    ///
    /// The property name cannot be changed after the ISgfcProperty has been
    /// constructed.
    ///
    /// All properties defined in the SGF standard have a name that consists of
    /// two uppercase letters. Application-specific properties not defined in
    /// the standard may not adhere to this restriction (although the standard
    /// advises against this).
    virtual std::string GetPropertyName() const = 0;

    /// @brief Returns the values of the property.
    ///
    /// @todo Is it possible that a property can have zero values? The EBNF in
    /// the standard says that at least one value must be present, but the list
    /// of value types includes "None", which is defined to be an empty string.
    /// The meaning for the file content is clear: Something like XY[] is
    /// possible. But how does this translate to our OO model? Do we return
    /// an empty list, or do we return a list with one element whose value is
    /// an empty string?
    virtual std::vector<std::shared_ptr<ISgfcPropertyValue>> GetPropertyValues() const = 0;

    /// @brief Sets the values of the property to @a propertyValues. The
    /// previous values are discarded.
    virtual void SetPropertyValues(
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues) = 0;

    /// @brief Returns the property's first value if the property has any
    /// values. Returns @e nullptr if the property has no values.
    ///
    /// This is a convenience method for properties that can have only value.
    virtual std::shared_ptr<ISgfcPropertyValue> GetPropertyValue() const = 0;

    /// @brief Returns an ISgfcBoardSizeProperty object if GetPropertyType()
    /// returns SgfcPropertyType::SZ. Returns @e nullptr otherwise.
    /// The caller is not the owner of the returned object.
    virtual const ISgfcBoardSizeProperty* ToBoardSizeProperty() const = 0;
  };
}
