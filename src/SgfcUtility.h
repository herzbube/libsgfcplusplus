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
#include "../include/ISgfcMessage.h"
#include "../include/SgfcBoardSize.h"
#include "../include/SgfcExitCode.h"
#include "../include/SgfcGameType.h"
#include "../include/SgfcArgumentType.h"
#include "../include/SgfcNodeTraits.h"
#include "../include/SgfcPropertyCategory.h"
#include "../include/SgfcPropertyTraits.h"
#include "../include/SgfcPropertyType.h"
#include "../include/SgfcTypedefs.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcUtility class is a container for static helper functions.
  ///
  /// @ingroup internals
  /// @ingroup library-support
  class SgfcUtility
  {
  public:
    SgfcUtility() = delete;
    ~SgfcUtility() = delete;

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

    /// @brief Returns the property category, as defined by the SGF standard,
    /// that corresponds to @a propertyType.
    ///
    /// This is a convenience function that looks up @a propertyType in
    /// SgfcConstants::PropertyTypeToPropertyCategoryMap.
    ///
    /// @exception std::invalid_argument Is thrown if there is no mapping, i.e.
    /// if @a propertyType does not appear in
    /// SgfcConstants::PropertyTypeToPropertyCategoryMap. If this occurs it
    /// indicates a programming error in the library, i.e. an SgfcPropertyType
    /// value was not added to SgfcConstants::PropertyTypeToPropertyCategoryMap.
    static SgfcPropertyCategory MapPropertyTypeToPropertyCategory(SgfcPropertyType propertyType);

    /// @brief Returns the property traits, as defined by the SGF standard,
    /// that the property with property type @a propertyType has.
    ///
    /// This is a convenience function that looks up @a propertyType in
    /// SgfcConstants::PropertyTypeToPropertyTraitsMap.
    ///
    /// @exception std::invalid_argument Is thrown if there is no mapping, i.e.
    /// if @a propertyType does not appear in
    /// SgfcConstants::PropertyTypeToPropertyTraitsMap. If this occurs it
    /// indicates a programming error in the library, i.e. an SgfcPropertyType
    /// value was not added to SgfcConstants::PropertyTypeToPropertyTraitsMap.
    static SgfcPropertyTraits MapPropertyTypeToPropertyTraits(SgfcPropertyType propertyType);

    /// @brief Returns the node trait, as defined by the SGF standard, that
    /// corresponds to @a propertyCategory. Returns
    /// SgfcConstants::NodeTraitsNone if @a propertyCategory cannot be mapped.
    ///
    /// This is a convenience function that looks up @a propertyCategory in
    /// SgfcPrivateConstants::PropertyCategoryToNodeTraitMap.
    static SgfcNodeTraits MapPropertyCategoryToNodeTraits(SgfcPropertyCategory propertyCategory);

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

    /// @brief Returns the default board size for @a gameType, as specified by
    /// the SGF standard. Returns SgfcConstants::BoardSizeNone if the SGF
    /// standard does not specify a default board size for @a gameType.
    static SgfcBoardSize GetDefaultBoardSize(SgfcGameType gameType);

    /// @brief Returns true if @a boardSize is a valid board size for
    /// @a gameType. Returns false if @a boardSize is not a valid board size
    /// for @a gameType.
    ///
    /// A board size is invalid if it violates the constraints defined by the
    /// SGF standard. See the documentation of SgfcConstants::BoardSizeInvalid
    /// for details.
    static bool IsBoardSizeValid(SgfcBoardSize boardSize, SgfcGameType gameType);

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

    /// @brief Returns the command line option, as defined by the SGFC
    /// documentation, that corresponds to @a argumentType.
    ///
    /// This is a convenience function that looks up @a argumentType in
    /// SgfcPrivateConstants::ArgumentTypeToCmdlineOptionMap.
    ///
    /// @exception std::invalid_argument Is thrown if there is no mapping, i.e.
    /// if @a argumentType does not appear in
    /// SgfcPrivateConstants::ArgumentTypeToCmdlineOptionMap. In practice this
    /// should never occur. If it occurs it indicates a programming error in the
    /// library, i.e. an SgfcArgumentType value was not added to
    /// SgfcPrivateConstants::ArgumentTypeToCmdlineOptionMap.
    static std::string MapArgumentTypeToCmdlineOption(SgfcArgumentType argumentType);

    /// @brief Returns the full path to a folder that is suitable for temporary
    /// files. The path is guaranteed to exist and to be a directory.
    ///
    /// This is a replacement for std::filesystem::temp_directory_path().
    /// This function was defined in C++17, but is not available on all
    /// platforms (notably on macOS it is available only from macOS 10.15), so
    /// we have to roll our own platform-independent function.
    static std::string GetTempFolderPath();

    /// @brief Returns the unique base name of a file that is extremely
    /// unlikely to already exist in the temporary folder returned by
    /// GetTempPath(). This method never returns the same value twice.
    ///
    /// The file name is composed of the following parts:
    /// - A prefix that indicates that the file origin is this library
    /// - The ID of the system process that hosts the library
    /// - A randomly generated UUID
    /// - A file extension suffix that indicates that the file is a temporary
    ///   file
    static std::string GetUniqueTempFileName();

    /// @brief Returns the unique absolute path name of a file that is extremely
    /// unlikely to already exist in the temporary folder returned by
    /// GetTempPath(). This method never returns the same value twice.
    ///
    /// This is a convenience function that invokes JoinPathComponents() using
    /// the return values of GetTempFolderPath() and GetUniqueTempFileName().
    static std::string GetUniqueTempFilePath();

    /// @brief Joins two filesystem path components together using the
    /// platform-specific directory separator.
    static std::string JoinPathComponents(const std::string& component1, const std::string& component2);

    /// @brief Returns true if @a string begins with @a prefix. Returns false
    /// if @a string does not begin with @a prefix. Comparison is case
    /// sensitive.
    static bool StringStartsWith(const std::string& string, const std::string& prefix);

    /// @brief Returns true if @a string ends with @a suffix. Returns false
    /// if @a string does not end with @a suffix. Comparison is case
    /// sensitive.
    static bool StringEndsWith(const std::string& string, const std::string& suffix);

    /// @brief Splits @a string into substrings using the single character
    /// @a delimiter as the delimiter.
    static std::vector<std::string> SplitString(const std::string& string, char delimiter);

    /// @brief Splits @a string into substrings using the string @a delimiter
    /// as the delimiter.
    static std::vector<std::string> SplitString(const std::string& string, const std::string& delimiter);

    /// @brief Returns a newly generated random UUID.
    static std::string CreateUuid();

    /// @brief Makes sure that the file located at @a path in the filesystem
    /// exists and has zero length. If the file does not exist it is created.
    /// If the file already exists it is truncated to zero length.
    ///
    /// @exception std::runtime_error Is thrown if the file cannot be opened
    /// for writing for any reason.
    static void CreateOrTruncateFile(const std::string& path);

    /// @brief Deletes the file located at @a path in the filesystem if it
    /// exists. Does nothing if the file does not exist.
    ///
    /// @retval true if the file exists and was deleted.
    /// @retval false if the file does not exist.
    ///
    /// @exception std::runtime_error Is thrown if the file exists but cannot
    /// be deleted for any reason.
    static bool DeleteFileIfExists(const std::string& path);

    /// @brief Appends @a string to the the file located at @a path in the
    /// filesystem. If the file does not exist it is created.
    ///
    /// @exception std::runtime_error Is thrown if the file cannot be opened
    /// for writing for any reason.
    static void AppendTextToFile(const std::string& path, const std::string& string);

    /// @brief Reads the entire content of the file located at @a path in the
    /// filesystem into memory and returns the content as a string.
    ///
    /// @exception std::runtime_error Is thrown if the file cannot be opened
    /// for reading for any reason.
    static std::string ReadFileContent(const std::string& path);
  };
}
