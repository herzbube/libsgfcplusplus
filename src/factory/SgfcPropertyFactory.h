#pragma once

// Project includes
#include "../../include/ISgfcPropertyFactory.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyFactory class provides an implementation of
  /// the ISgfcPropertyFactory interface. See the interface header file for
  /// documentation.
  class SgfcPropertyFactory : public ISgfcPropertyFactory
  {
  public:
    SgfcPropertyFactory();
    virtual ~SgfcPropertyFactory();

    /// @name ISgfcProperty - Create with property type
    //@{
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(
      SgfcPropertyType propertyType);
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(
      SgfcPropertyType propertyType,
      std::shared_ptr<ISgfcPropertyValue> propertyValue);
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(
      SgfcPropertyType propertyType,
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);
    //@}

    /// @name ISgfcProperty - Create with property name
    //@{
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(
      const std::string& propertyName);
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(
      const std::string& propertyName,
      std::shared_ptr<ISgfcPropertyValue> propertyValue);
    virtual std::shared_ptr<ISgfcProperty> CreateProperty(
      const std::string& propertyName,
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);
    //@}

    /// @name Concrete property types - ISgfcBoardSizeProperty
    //@{
    virtual std::shared_ptr<ISgfcBoardSizeProperty> CreateBoardSizeProperty();
    virtual std::shared_ptr<ISgfcBoardSizeProperty> CreateBoardSizeProperty(
      std::shared_ptr<ISgfcNumberPropertyValue> propertyValue);
    virtual std::shared_ptr<ISgfcBoardSizeProperty> CreateBoardSizeProperty(
      std::shared_ptr<ISgfcComposedPropertyValue> propertyValue);
    //@}

    /// @name Concrete property types - ISgfcGameTypeProperty
    //@{
    virtual std::shared_ptr<ISgfcGameTypeProperty> CreateGameTypeProperty();
    virtual std::shared_ptr<ISgfcGameTypeProperty> CreateGameTypeProperty(
      std::shared_ptr<ISgfcNumberPropertyValue> propertyValue);
    //@}

  private:
    std::shared_ptr<ISgfcProperty> CreateProperty(
      SgfcPropertyType propertyType,
      const std::string& propertyName,
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);
  };
}
