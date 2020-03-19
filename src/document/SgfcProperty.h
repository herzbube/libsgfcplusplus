#pragma once

// Project includes
#include "../../include/ISgfcProperty.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcProperty class provides an implementation of the
  /// ISgfcProperty interface. See the interface header file for
  /// documentation.
  class SgfcProperty : virtual public ISgfcProperty
  {
  public:
    /// @brief Initializes a newly constructed SgfcProperty object. The property
    /// has the specified type @a propertyType and name @a propertyName. The
    /// property has no values.
    SgfcProperty(
      SgfcPropertyType propertyType,
      const std::string& propertyName);

    /// @brief Initializes a newly constructed SgfcProperty object. The property
    /// has the specified type @a propertyType, name @a propertyName and
    /// property values @a propertyValues.
    SgfcProperty(
      SgfcPropertyType propertyType,
      const std::string& propertyName,
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);

    /// @brief Destroys and cleans up the SgfcProperty object.
    virtual ~SgfcProperty();

    virtual SgfcPropertyType GetPropertyType() const;
    virtual std::string GetPropertyName() const;

    virtual std::vector<std::shared_ptr<ISgfcPropertyValue>> GetPropertyValues() const;
    virtual void SetPropertyValues(
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);
    virtual std::shared_ptr<ISgfcPropertyValue> GetPropertyValue() const;

    virtual const ISgfcBoardSizeProperty* ToBoardSizeProperty() const;

  private:
    SgfcPropertyType propertyType;
    std::string propertyName;
    std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues;
  };
}
