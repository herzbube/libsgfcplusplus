#pragma once

// Project includes
#include "../../include/ISgfcProperty.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcProperty class provides an implementation of the
  /// ISgfcProperty interface. See the interface header file for
  /// documentation.
  class SgfcProperty : public ISgfcProperty
  {
  public:
    SgfcProperty();
    SgfcProperty(
      SgfcPropertyType propertyType,
      const std::string& propertyName,
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);
    virtual ~SgfcProperty();

    virtual SgfcPropertyType GetPropertyType() const;

    virtual std::string GetPropertyName() const;

    virtual std::vector<std::shared_ptr<ISgfcPropertyValue>> GetPropertyValues() const;

  private:
    SgfcPropertyType propertyType;
    std::string propertyName;
    std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues;
  };
}
