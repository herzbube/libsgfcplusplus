// Project includes
#include "../include/SgfcConstants.h"
#include "SgfcPrivateConstants.h"
#include "SgfcUtility.h"

// C++ Standard Library includes
#include <random>
#include <sstream>
#include <stdexcept>

// System includes
#ifdef _MSC_VER
  #include <fileapi.h>  // for GetTempPath()
//  #include <io.h>
#else
  #include <cstdlib>    // for std::getenv()
#endif

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

  std::string SgfcUtility::GetTempFolderPath()
  {
    std::string tempFolderPath;

#ifdef _MSC_VER
    size_t bufferLength = MAX_PATH + 1
    char* buffer = new char[bufferLength];

    // The Win32 API works with TCHAR, but since everything else in libsgfc++
    // does not work with wchar or wstring we don't bother here and just use
    // char and string.

    DWORD getTempPathResult = GetTempPath(bufferLength, buffer);
    if (getTempPathResult == 0 || getTempPathResult > bufferLength)
    {
      delete[] buffer;
      throw std::runtime_error("Win32 API function GetTempPath() failed");
    }

    std::string tempFolderPath = buffer;
    delete[] buffer;

#else

    // Environment variable names taken from
    // https://en.cppreference.com/w/cpp/filesystem/temp_directory_path
    static std::vector<std::string> environmentVariableNames = { "TMPDIR", "TMP", "TEMP", "TEMPDIR" };

    tempFolderPath = "/tmp";

    for ( const auto& environmentVariableName : environmentVariableNames )
    {
      const char* environmentVariableValue = std::getenv(environmentVariableName.c_str());
      if (environmentVariableValue != nullptr)
      {
        tempFolderPath = environmentVariableValue;
        break;
      }
    }

#endif

    // On all platforms we have no guarantee that the folder actually exists.
    // This works purely by convention. Because we intend to replace all this
    // cruft with std::filesystem::temp_directory_path() anyway sooner or later,
    // this implementation is good enoughh.

    return tempFolderPath;
  }

  std::string SgfcUtility::JoinPathComponents(const std::string& component1, const std::string& component2)
  {
    std::string joinedPath = component1;
    if (SgfcUtility::StringEndsWith(component1, SgfcPrivateConstants::DirectorySeparator))
    {
      size_t position = joinedPath.rfind(SgfcPrivateConstants::DirectorySeparator);
      joinedPath.erase(position, SgfcPrivateConstants::DirectorySeparator.length());
    }

    if (SgfcUtility::StringStartsWith(component2, SgfcPrivateConstants::DirectorySeparator))
      joinedPath += component2;
    else
      joinedPath += SgfcPrivateConstants::DirectorySeparator + component2;

    return joinedPath;
  }

  bool SgfcUtility::StringStartsWith(const std::string& string, const std::string& prefix)
  {
    if (prefix.size() > string.size())
      return false;

    int beginComparePosition = 0;
    return (string.compare(beginComparePosition, prefix.size(), prefix) == 0);
  }

  bool SgfcUtility::StringEndsWith(const std::string& string, const std::string& suffix)
  {
    if (suffix.size() > string.size())
      return false;

    int beginComparePosition = string.size() - suffix.size();
    return (string.compare(beginComparePosition, suffix.size(), suffix) == 0);
  }

  std::string SgfcUtility::CreateUuid()
  {
    // The following implementation is more or less a straight copy of this
    // StackOverflow answer, with some minor changes:
    // https://stackoverflow.com/a/58467162/1054378.

    static std::random_device dev;
    static std::mt19937 rng(dev());
    static const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };
    static std::uniform_int_distribution<int> dist(0, 15);
    static const char* digits = "0123456789abcdef";

    std::string uuid;

    for (int i = 0; i < 16; i++)
    {
        if (dash[i])
          uuid += "-";
        uuid += digits[dist(rng)];
        uuid += digits[dist(rng)];
    }

    return uuid;
  }
}
