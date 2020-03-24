#pragma once

// Project includes
#include "../include/ISgfcMessage.h"
#include "../include/SgfcExitCode.h"
#include "../include/SgfcGameType.h"
#include "../include/SgfcPropertyType.h"
#include "../include/SgfcTypedefs.h"

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

    /// @brief Returns the SgfcNumber value that corresponds to the SgfcGameType
    /// value @a gameType. @a gameType must not be SgfcGameType::Unknown.
    ///
    /// This is a convenience function that looks up @a gameType in
    /// SgfcConstants::GameTypeToGameTypeAsNumberMap.
    ///
    /// @exception std::invalid_argument Is thrown if there is no mapping, i.e.
    /// if @a gameType does not appear in
    /// SgfcConstants::GameTypeToGameTypeAsNumberMap. This should only occur if
    /// @a gameType is SgfcGameType::Unknown, because obviously that game type
    /// has no corresponding Number value. Otherwise this indicates a
    /// programming error in the library, i.e. an SgfcGameType value was not
    /// added to SgfcConstants::GameTypeToGameTypeAsNumberMap.
    static SgfcNumber MapGameTypeToNumberValue(SgfcGameType gameType);

    /// @brief Returns the SgfcGameType value that corresponds to the Number
    /// value @a gameTypeAsNumber. Returns SgfcGameType::Unknown if the Number
    /// value cannot be mapped, which is the case if the Number value does not
    /// correspond to one of the known values defined by the SGF standard.
    ///
    /// This is a convenience function that looks up @a gameTypeAsNumber in
    /// SgfcConstants::GameTypeAsNumberToGameTypeMap.
    static SgfcGameType MapNumberValueToGameType(SgfcNumber gameTypeAsNumber);

    /// @brief Returns an SgfcExitCode value that represents the messages
    /// in @a messageCollection. See the documentation of the individual
    /// enumeration values for details.
    static SgfcExitCode GetSgfcExitCodeFromMessageCollection(
      const std::vector<std::shared_ptr<ISgfcMessage>>& messageCollection);

    /// @brief Returns whether @a messageCollection, which is the result of an
    /// SGFC read or write operation, indicate that the piece of SGF data that
    /// was read or written is valid.
    ///
    /// @retval true if the data that was read or written is valid.
    /// @retval false if the data that was read or written is invalid.
    static bool GetIsSgfDataValidFromMessageCollection(
      const std::vector<std::shared_ptr<ISgfcMessage>>& messageCollection);
  };
}
