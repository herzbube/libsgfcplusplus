// Project includes
#include "../include/SgfcConstants.h"
#include "SgfcPrivateConstants.h"
#include "SgfcUtility.h"

// C++ Standard Library includes
#include <cstdio>       // for remove()
#include <fstream>      // for std::ofstream and std::ifstream
#include <random>
#include <sstream>
#include <stdexcept>

// System includes
#ifdef _MSC_VER
  #include <Windows.h>  // for GetTempPath()
  #include <io.h>       // for _access_s()
#else
  #include <cstdlib>    // for std::getenv()
  #include <unistd.h>   // for access()
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
    DWORD bufferLength = MAX_PATH + 1;
    char* buffer = new char[bufferLength];

    // The Win32 API works with TCHAR, but since everything else in libsgfc++
    // does not work with wchar or wstring we don't bother here and just use
    // char and string.

    DWORD getTempPathResult = GetTempPath(bufferLength, buffer);
    if (getTempPathResult == 0 || getTempPathResult > bufferLength)
    {
      delete[] buffer;
      throw std::runtime_error("Win32 API function GetTempPath() failed");
    }

    tempFolderPath = buffer;
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
    // this implementation is good enough.

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

    size_t beginComparePosition = string.size() - suffix.size();
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

  void SgfcUtility::CreateOrTruncateFile(const std::string& path)
  {
    std::ofstream out(path, std::ios::out | std::ios::trunc);

    if (! out.is_open())
    {
      std::stringstream message;
      message << "Failed to open file for writing: " << path;
      throw std::runtime_error(message.str());
    }
  }

  bool SgfcUtility::DeleteFileIfExists(const std::string& path)
  {
#ifdef _MSC_VER
    errno_t accessResult = _access_s(path.c_str(), 0);
    if (accessResult != 0)
    {
      if (accessResult == ENOENT)
        return false;

      std::stringstream message;
      message << "Failed to determine whether file exists: " << path;
      throw std::runtime_error(message.str());
    }
#else
    int accessResult = access(path.c_str(), F_OK);
    if (accessResult == -1)
      return false;
#endif

    // On all platforms there is a gap between the check for the file's
    // existence above and its deletion below: Someone could delete the file
    // after we checked for its existence but before we were able to delete it
    // ourselves. In this case we throw an exception. Because we intend to
    // replace all this cruft with std::filesystem::remove() anyway sooner or
    // later, this implementation is good enough.

    bool removeResult = remove(path.c_str());
    if (removeResult != 0)
    {
      std::stringstream message;
      message << "Failed to delete file: " << path;
      throw std::runtime_error(message.str());
    }

    return true;
  }

  void SgfcUtility::AppendTextToFile(const std::string& path, const std::string& string)
  {
    std::ofstream out(path, std::ios::out | std::ios::app);

    if (! out.is_open())
    {
      std::stringstream message;
      message << "Failed to open file for writing: " << path;
      throw std::runtime_error(message.str());
    }

    out << string;
  }

  std::string SgfcUtility::ReadFileContent(const std::string& path)
  {
    std::ifstream in(path);

    if (! in.is_open())
    {
      std::stringstream message;
      message << "Failed to open file for reading: " << path;
      throw std::runtime_error(message.str());
    }

    std::stringstream content;
    content << in.rdbuf();

    return content.str();
  }
}
