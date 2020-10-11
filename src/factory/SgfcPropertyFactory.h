// -----------------------------------------------------------------------------
// Copyright 2020 Patrick Näf (herzbube@herzbube.ch)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -----------------------------------------------------------------------------

#pragma once

// Project includes
#include "../../include/ISgfcPropertyFactory.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyFactory class provides an implementation of
  /// the ISgfcPropertyFactory interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup factory
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
