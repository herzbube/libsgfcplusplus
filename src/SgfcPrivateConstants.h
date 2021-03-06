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
#include "../include/SgfcArgumentType.h"
#include "../include/SgfcMessageType.h"
#include "../include/SgfcNodeTraits.h"
#include "../include/SgfcPropertyCategory.h"

// C++ Standard Library includes
#include <map>
#include <regex>
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPrivateConstants class is a container class for
  /// library-internal constants.
  ///
  /// @ingroup internals
  /// @ingroup library-support
  class SgfcPrivateConstants
  {
  public:
    SgfcPrivateConstants() = delete;
    ~SgfcPrivateConstants() = delete;

    /// @name General string constants
    //@{
    /// @brief The empty string.
    static const std::string EmptyString;
    /// @brief A string consisting of a single space character.
    static const std::string SpaceCharacter;
    /// @brief A string consisting of a single newline character ("\n").
    static const char NewlineCharacter;
    /// @brief A string consisting of a single newline character ("\r").
    static const char CarriageReturnCharacter;
    /// @brief A string consisting of a number of space characters thaht is used
    /// generate indentation in formatted output.
    static const std::string IndentationWhitespace;
    /// @brief The line ending used by SGFC. Currently this is used by SGFC only
    /// when it writes SGF content. Currently SGFC does not use this when it
    /// writes messages with PrintError() - in that case it always uses
    /// SgfcPrivateConstants::NewlineCharacter.
    static const std::string EndOfLineStringUsedBySgfc;
    //@}

    /// @name Filesystem related constants
    //@{
    /// @brief This constant contains a platform-specific string that is used
    /// as the directory separator in filesystem paths.
    static const std::string DirectorySeparator;
    /// @brief The prefix used in names of temporary files created by the
    /// library.
    static const std::string TempFilePrefix;
    /// @brief The suffix used in names of temporary files created by the
    /// library.
    static const std::string TempFileSuffix;
    //@}

    /// @name String constants defined by the SGF standard to structure the file format
    //@{
    /// @brief The token that marks the beginning of a game tree.
    static const std::string GameTreeBeginToken;
    /// @brief The token that marks the end of a game tree.
    static const std::string GameTreeEndToken;
    /// @brief The token that marks the beginning of a node in a game tree.
    static const std::string NodeBeginToken;
    /// @brief The token that marks the beginning of a property value.
    static const std::string PropertyValueBeginToken;
    /// @brief The token that marks the end of a property value.
    static const std::string PropertyValueEndToken;
    /// @brief The token that separates the first from the second value in a
    /// composed value.
    static const std::string ComposedValueSeparatorToken;
    /// @brief The escape character.
    static const std::string EscapeCharacterToken;
    /// @brief A composition of EscapeCharacterToken and PropertyValueEndToken.
    static const std::string EscapedPropertyValueEndToken;
    /// @brief A composition of EscapeCharacterToken and
    /// ComposedValueSeparatorToken.
    static const std::string EscapedComposedValueSeparatorToken;
    /// @brief A composition of EscapeCharacterToken and EscapeCharacterToken.
    static const std::string EscapedEscapeCharacterToken;
    //@}

    /// @name Regular expression constants
    //@{
    /// @brief A regex pattern that matches the line endings on all platforms.
    static const std::string LineEndingsPattern;
    /// @brief A regex with a pattern that matches EscapedPropertyValueEndToken.
    static const std::regex EscapedPropertyValueEndTokenRegex;
    /// @brief A regex with a pattern that matches
    /// EscapedComposedValueSeparatorToken.
    static const std::regex EscapedComposedValueSeparatorTokenRegex;
    /// @brief A regex with a pattern that matches EscapedEscapeCharacterToken.
    static const std::regex EscapedEscapeCharacterRegex;
    /// @brief A regex with a pattern that matches any of the line endings in
    /// LineEndingsPattern when it is escaped with EscapeCharacterToken.
    static const std::regex EscapedLineEndingsRegex;
    /// @brief A regex with a pattern that matches PropertyValueEndToken.
    static const std::regex UnescapedPropertyValueEndTokenRegex;
    /// @brief A regex with a pattern that matches ComposedValueSeparatorToken.
    static const std::regex UnescapedComposedValueSeparatorTokenRegex;
    /// @brief A regex with a pattern that matches EscapeCharacterToken.
    static const std::regex UnescapedEscapeCharacterRegex;
    /// @brief A regex with a pattern that matches LineEndingsPattern.
    static const std::regex UnescapedLineEndingsRegex;
    /// @brief A regex with a pattern that matches 0-n LineEndingsPattern at
    /// the end of the string.
    static const std::regex ZeroOrMoreLineEndingsAtEndOfStringRegex;
    /// @brief A regex with a pattern that matches the parts of an
    /// SgfcPropertyType::RE property value.
    static const std::regex GameResultRegex;
    /// @brief A regex with a pattern that matches the parts of an
    /// SgfcPropertyType::RO property value.
    static const std::regex RoundInformationRegex;
    /// @brief A regex with a pattern that matches the parts of an
    /// SgfcPropertyType::BR or SgfcPropertyType::WR property value.
    static const std::regex GoPlayerRankRegex;
    //@}

    /// @name Constants for strings that can appear in messages generated by SGFC
    //@{
    /// @brief The token that precedes the line number.
    static const std::string LineToken;
    /// @brief The token that precedes the column number.
    static const std::string ColumnToken;
    /// @brief The dash character ("-").
    static const std::string DashToken;
    /// @brief The token that marks a message to be of typw
    /// #SgfcMessageType::Warning.
    static const std::string WarningToken;
    /// @brief The token that marks a message to be of typw
    /// #SgfcMessageType::Error (beginning with an uppercase letter).
    static const std::string ErrorUpperCaseToken;
    /// @brief The token that marks a message to be of typw
    /// #SgfcMessageType::FatalError.
    static const std::string FatalToken;
    /// @brief The token that marks a message to be of typw
    /// #SgfcMessageType::Error (beginning with a lowercase letter).
    static const std::string ErrorLowerCaseToken;
    /// @brief The token that marks a message to be a critical message.
    static const std::string CriticalToken;
    //@}

    /// @name SGFC command line argument constants
    //@{
    /// @brief Maps values from the enumeration SgfcArgumentType to command line
    /// options as defined by the SGFC documentation.
    static const std::map<SgfcArgumentType, std::string> ArgumentTypeToCmdlineOptionMap;

    /// @brief Parameter value for #SgfcArgumentType::EncodingMode. Specifies
    /// that a single encoding is used to decode all game trees in the entire
    /// SGF content.
    ///
    /// The numeric value of this constant is 1.
    static const int EncodingModeSingleEncoding;
    /// @brief Parameter value for #SgfcArgumentType::EncodingMode. Specifies
    /// that each game tree in the SGF content is decoded separately with the
    /// encoding specified in the game tree's CA property.
    ///
    /// The numeric value of this constant is 2.
    static const int EncodingModeMultipleEncodings;
    /// @brief Parameter value for #SgfcArgumentType::EncodingMode. Specifies
    /// that no decoding is to be done and that the SGF content is to be read
    /// as-is.
    ///
    /// The numeric value of this constant is 3.
    static const int EncodingModeNoDecoding;
    //@}

    /// @name Constants for parsing messages generated by SGFC
    //@{
    /// @brief The default message type to be used when the message type for
    /// some reason cannot be determined by parsing.
    static const SgfcMessageType DefaultMessageType;
    /// @brief The default message criticality to be used when the criticality
    /// for some reason cannot be determined by parsing.
    static const bool DefaultIsCriticalMessage;
    /// @brief The default message text to be used when the text for some reason
    /// cannot be determined by parsing.
    static const std::string DefaultMessageText;
    /// @brief The default raw message text to be used when the raw text for
    /// some reason cannot be determined by parsing.
    static const std::string DefaultRawMessageText;
    //@}

    /// @name Mappings between libsgfc++ values and SGF standard values, and vice versa
    //@{
    /// @brief Maps values from the enumeration SgfcPropertyCategory to values
    /// from the enumeration SgfcNodeTrait.
    ///
    /// If a node contains one or more properties classified as a specific
    /// SgfcPropertyCategory then the node has the SgfcNodeTrait that is mapped
    /// to that SgfcPropertyCategory. For some SgfcPropertyCategory values there
    /// is no mapping. Because this use of the map is not overly intuitive it is
    /// not part of the public constants.
    static const std::map<SgfcPropertyCategory, SgfcNodeTrait> PropertyCategoryToNodeTraitMap;
    //@}

    /// @name Other private constants
    //@{
    /// @brief Name of the UTF-8 text encoding. This is used both as CA
    /// property value and to form SGFC command line arguments.
    static const std::string TextEncodingNameUTF8;
    //@}
  };
}
