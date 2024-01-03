// -----------------------------------------------------------------------------
// Copyright 2024 Patrick Näf (herzbube@herzbube.ch)
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

// Project includes
#include "../include/SgfcConstants.h"
#include "SgfcPrivateConstants.h"
#include "SgfcUtility.h"

// C++ Standard Library includes
#include <cstdio>       // for remove()
#include <filesystem>   // for std::filesystem::temp_directory_path()
#include <fstream>      // for std::ofstream and std::ifstream
#include <random>
#include <sstream>
#include <stdexcept>

// System includes
#ifdef _MSC_VER
  #include <io.h>       // for _access_s()
  #include <process.h>  // for _getpid()
#else
  #include <unistd.h>   // for access() and getpid()
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

  SgfcPropertyCategory SgfcUtility::MapPropertyTypeToPropertyCategory(SgfcPropertyType propertyType)
  {
    auto it = SgfcConstants::PropertyTypeToPropertyCategoryMap.find(propertyType);

    if (it == SgfcConstants::PropertyTypeToPropertyCategoryMap.cend())
    {
      std::stringstream message;
      message << "Property type cannot be mapped to property category, argument has unsupported value: " << static_cast<int>(propertyType);
      throw std::invalid_argument(message.str());
    }

    return it->second;
  }

  SgfcPropertyTraits SgfcUtility::MapPropertyTypeToPropertyTraits(SgfcPropertyType propertyType)
  {
    auto it = SgfcConstants::PropertyTypeToPropertyTraitsMap.find(propertyType);

    if (it == SgfcConstants::PropertyTypeToPropertyTraitsMap.cend())
    {
      std::stringstream message;
      message << "Property type cannot be mapped to property traits, argument has unsupported value: " << static_cast<int>(propertyType);
      throw std::invalid_argument(message.str());
    }

    return it->second;
  }

  SgfcNodeTraits SgfcUtility::MapPropertyCategoryToNodeTraits(SgfcPropertyCategory propertyCategory)
  {
    SgfcNodeTraits nodeTraits = SgfcConstants::NodeTraitsNone;

    auto it = SgfcPrivateConstants::PropertyCategoryToNodeTraitMap.find(propertyCategory);
    if (it != SgfcPrivateConstants::PropertyCategoryToNodeTraitMap.cend())
      nodeTraits |= it->second;

    return nodeTraits;
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

  std::string SgfcUtility::MapArgumentTypeToCmdlineOption(SgfcArgumentType argumentType)
  {
    auto it = SgfcPrivateConstants::ArgumentTypeToCmdlineOptionMap.find(argumentType);

    if (it == SgfcPrivateConstants::ArgumentTypeToCmdlineOptionMap.cend())
    {
      std::stringstream message;
      message << "Argument type argument has unsupported value: " << static_cast<int>(argumentType);
      throw std::invalid_argument(message.str());
    }

    std::string cmdlineOption = it->second;
    return cmdlineOption;
  }

  std::string SgfcUtility::GetTempFolderPath()
  {
    std::filesystem::path tempFolderPath = std::filesystem::temp_directory_path();
    return tempFolderPath.u8string();
  }

  std::string SgfcUtility::GetUniqueTempFileName()
  {
    std::stringstream uniqueTempFileName;

    // Example: libsgfc++_838c5afe-369e-4422-a1e7-3a008b57710c.12345.tmp
    uniqueTempFileName
      << SgfcPrivateConstants::TempFilePrefix
      << "_"
      << SgfcUtility::CreateUuid()
      << "."
#ifdef _MSC_VER
      // Returns an int value
      << _getpid()
#else
      // Returns a pid_t value. We don't care what this resolves to (int,
      // long, long long?), we simply pass the value to the stream and let it
      // handle the conversion to string.
      << getpid()
#endif
      << "."
      << SgfcPrivateConstants::TempFileSuffix;

    return uniqueTempFileName.str();
  }

  std::string SgfcUtility::GetUniqueTempFilePath()
  {
    return SgfcUtility::JoinPathComponents(
      SgfcUtility::GetTempFolderPath(),
      SgfcUtility::GetUniqueTempFileName());
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

  std::vector<std::string> SgfcUtility::SplitString(const std::string& string, char delimiter)
  {
    return SplitString(string, std::string(1, delimiter));
  }

  std::vector<std::string> SgfcUtility::SplitString(const std::string& string, const std::string& delimiter)
  {
    std::vector<std::string> substrings;

    const size_t length = string.length();
    size_t startPosition = 0;
    size_t delimiterPosition = 0;

    do
    {
      if (startPosition >= length)
      {
        substrings.push_back("");
        delimiterPosition = std::string::npos;
      }
      else
      {
        delimiterPosition = string.find(delimiter, startPosition);

        if (delimiterPosition == std::string::npos)
        {
          substrings.push_back(string.substr(startPosition));
        }
        else
        {
          substrings.push_back(string.substr(startPosition, delimiterPosition - startPosition));
          startPosition = delimiterPosition + 1;
        }
      }
    }
    while (delimiterPosition != std::string::npos);

    return substrings;
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
