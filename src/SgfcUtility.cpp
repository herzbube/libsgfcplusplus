// Project includes
#include "../include/SgfcConstants.h"
#include "SgfcUtility.h"

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  std::string SgfcUtility::MapPropertyTypeToPropertyName(SgfcPropertyType propertyType)
  {
    auto it = SgfcConstants::PropertyTypeToPropertyNameMap.find(propertyType);

    if (it == SgfcConstants::PropertyTypeToPropertyNameMap.cend())
    {
      std::stringstream message;
      message << "Property type argument has unsupported value: " << static_cast<int>(propertyType);
      throw std::invalid_argument(message.str());
    }

    std::string propertyName = it->second;
    return propertyName;
  }

  SgfcPropertyType SgfcUtility::MapPropertyNameToPropertyType(const std::string& propertyName)
  {
    auto it = SgfcConstants::PropertyNameToPropertyTypeMap.find(propertyName);

    if (it != SgfcConstants::PropertyNameToPropertyTypeMap.cend())
      return it->second;
    else
      return SgfcPropertyType::Unknown;
  }

  SgfcNumber SgfcUtility::MapGameTypeToNumberValue(SgfcGameType gameType)
  {
    auto it = SgfcConstants::GameTypeToGameTypeAsNumberMap.find(gameType);

    if (it == SgfcConstants::GameTypeToGameTypeAsNumberMap.cend())
    {
      std::stringstream message;
      message << "Game type argument has unsupported value: " << static_cast<int>(gameType);
      throw std::invalid_argument(message.str());
    }

    SgfcNumber gameTypeAsNumber = it->second;
    return gameTypeAsNumber;

  }

  SgfcGameType SgfcUtility::MapNumberValueToGameType(SgfcNumber gameTypeAsNumber)
  {
    auto it = SgfcConstants::GameTypeAsNumberToGameTypeMap.find(gameTypeAsNumber);

    if (it != SgfcConstants::GameTypeAsNumberToGameTypeMap.cend())
      return it->second;
    else
      return SgfcGameType::Unknown;
  }

  SgfcExitCode SgfcUtility::GetSgfcExitCodeFromMessageCollection(
    const std::vector<std::shared_ptr<ISgfcMessage>>& messageCollection)
  {
    bool warningMessageFound = false;
    bool errorMessageFound = false;
    bool fatalErrorMessageFound = false;

    for (const auto& message : messageCollection)
    {
      switch (message->GetMessageType())
      {
        case SgfcMessageType::Warning:
          warningMessageFound = true;
          break;
        case SgfcMessageType::Error:
          errorMessageFound = true;
          break;
        case SgfcMessageType::FatalError:
          fatalErrorMessageFound = true;
          break;
      }
    }

    if (fatalErrorMessageFound)
      return SgfcExitCode::FatalError;
    if (errorMessageFound)
      return SgfcExitCode::Error;
    else if (warningMessageFound)
      return SgfcExitCode::Warning;
    else
      return SgfcExitCode::Ok;
  }

  bool SgfcUtility::GetIsSgfDataValidFromMessageCollection(
    const std::vector<std::shared_ptr<ISgfcMessage>>& messageCollection)
  {
    for (const auto& message : messageCollection)
    {
      if (message->GetMessageType() == SgfcMessageType::FatalError)
        return false;
    }

    return true;
  }
}
