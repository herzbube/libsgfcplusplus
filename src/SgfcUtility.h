#pragma once

// Project includes
#include "../include/ISgfcMessage.h"
#include "../include/SgfcExitCode.h"
#include "../include/SgfcPropertyType.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcUtility class is a container for static helper functions.
  class SgfcUtility
  {
  public:
    /// @brief Returns the property name, as defined by the SGF standard, that
    /// corresponds to @a propertyType. @a propertyType must not be
    /// SgfcPropertyType::Unknown.
    ///
    /// This is a convenience function that looks up @a propertyType in
    /// SgfcConstants::PropertyTypeToPropertyNameMap.
    ///
    /// @exception std::invalid_argument Is thrown if there is no mapping, i.e.
    /// if @a propertyType does not appear in
    /// SgfcConstants::PropertyTypeToPropertyNameMap. This should only occur if
    /// @a propertyType is SgfcPropertyType::Unknown, because obviously that
    /// property type has no corresponding property name. Otherwise this
    /// indicates a programming error in the library, i.e. an SgfcPropertyType
    /// value was not added to SgfcConstants::PropertyTypeToPropertyNameMap.
    static std::string MapPropertyTypeToPropertyName(SgfcPropertyType propertyType);

    /// @brief Returns the SgfcPropertyType value that corresponds to
    /// @a propertyName. Returns SgfcPropertyType::Unknown if @a propertyName
    /// cannot be mapped, which is the case if @a propertyName is not the name
    /// of a property as defined by the SGF standard.
    ///
    /// This is a convenience function that looks up @a propertyName in
    /// SgfcConstants::PropertyNameToPropertyTypeMap.
    static SgfcPropertyType MapPropertyNameToPropertyType(const std::string& propertyName);

    static SgfcExitCode GetSgfcExitCodeFromMessageCollection(
      const std::vector<std::shared_ptr<ISgfcMessage>>& messageCollection);
    static bool GetIsSgfDataValidFromMessageCollection(
      const std::vector<std::shared_ptr<ISgfcMessage>>& messageCollection);
  };
}
