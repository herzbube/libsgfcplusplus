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

// Project includes
#include "SgfcPrivateConstants.h"

namespace LibSgfcPlusPlus
{
  const std::string SgfcPrivateConstants::EmptyString = "";
  const std::string SgfcPrivateConstants::SpaceCharacter = " ";
  const char SgfcPrivateConstants::NewlineCharacter = '\n';
  const char SgfcPrivateConstants::CarriageReturnCharacter = '\r';
  const std::string SgfcPrivateConstants::IndentationWhitespace = "  ";
  // We use the same preprocessor logic here that is also used in WriteChar()
  // in save.c.
#if EOLCHAR
  const std::string SgfcPrivateConstants::EndOfLineStringUsedBySgfc = EOLCHAR;
#else
  const std::string SgfcPrivateConstants::EndOfLineStringUsedBySgfc = "\r\n";
#endif

#ifdef _MSC_VER
  const std::string SgfcPrivateConstants::DirectorySeparator = "\\";
#else
  const std::string SgfcPrivateConstants::DirectorySeparator = "/";
#endif
  const std::string SgfcPrivateConstants::TempFilePrefix = "libsgfc++";
  const std::string SgfcPrivateConstants::TempFileSuffix = "tmp";

  const std::string SgfcPrivateConstants::GameTreeBeginToken = "(";
  const std::string SgfcPrivateConstants::GameTreeEndToken = ")";
  const std::string SgfcPrivateConstants::NodeBeginToken = ";";
  const std::string SgfcPrivateConstants::PropertyValueBeginToken = "[";
  const std::string SgfcPrivateConstants::PropertyValueEndToken = "]";
  const std::string SgfcPrivateConstants::ComposedValueSeparatorToken = ":";
  const std::string SgfcPrivateConstants::EscapeCharacterToken = "\\";
  const std::string SgfcPrivateConstants::EscapedPropertyValueEndToken =
    SgfcPrivateConstants::EscapeCharacterToken +
    SgfcPrivateConstants::PropertyValueEndToken;
  const std::string SgfcPrivateConstants::EscapedComposedValueSeparatorToken =
    SgfcPrivateConstants::EscapeCharacterToken +
    SgfcPrivateConstants::ComposedValueSeparatorToken;
  const std::string SgfcPrivateConstants::EscapedEscapeCharacterToken =
    SgfcPrivateConstants::EscapeCharacterToken +
    SgfcPrivateConstants::EscapeCharacterToken;

  // The four line ending types mentioned in the SGF standard in the description
  // of the Text value type: LF, CR, CRLF and the non-standard LFCR.
  // Important: The multi-character line endings must appear first so that
  // they are recognized as one unit. If they appear at the end then the regex
  // engine matches e.g. "\r\n" as two separate line endings.
  const std::string SgfcPrivateConstants::LineEndingsPattern = "(\\r\\n|\\n\\r|\\n|\\r)";
  const std::regex SgfcPrivateConstants::EscapedPropertyValueEndTokenRegex(
    SgfcPrivateConstants::EscapeCharacterToken +   // Make the following escape character a literal for the regex
    SgfcPrivateConstants::EscapeCharacterToken +   // The literal as it appears in the SGF content
    SgfcPrivateConstants::EscapeCharacterToken +   // Make the following token a literal for the regex
    SgfcPrivateConstants::PropertyValueEndToken);  // The literal as it appears in the SGF content
  const std::regex SgfcPrivateConstants::EscapedComposedValueSeparatorTokenRegex(
    SgfcPrivateConstants::EscapeCharacterToken +   // Make the following escape character a literal for the regex
    SgfcPrivateConstants::EscapeCharacterToken +   // The literal as it appears in the SGF content
    SgfcPrivateConstants::ComposedValueSeparatorToken);
  const std::regex SgfcPrivateConstants::EscapedEscapeCharacterRegex(
    SgfcPrivateConstants::EscapeCharacterToken +   // Make the following escape character a literal for the regex
    SgfcPrivateConstants::EscapeCharacterToken +   // The literal as it appears in the SGF content
    SgfcPrivateConstants::EscapeCharacterToken +   // Make the following escape character a literal for the regex
    SgfcPrivateConstants::EscapeCharacterToken);   // The literal as it appears in the SGF content
  const std::regex SgfcPrivateConstants::EscapedLineEndingsRegex(
    SgfcPrivateConstants::EscapeCharacterToken +   // Make the following escape character a literal for the regex
    SgfcPrivateConstants::EscapeCharacterToken +   // The literal as it appears in the SGF content
    SgfcPrivateConstants::LineEndingsPattern);
  const std::regex SgfcPrivateConstants::UnescapedPropertyValueEndTokenRegex(
    SgfcPrivateConstants::EscapeCharacterToken +   // Make the following token a literal for the regex
    SgfcPrivateConstants::PropertyValueEndToken);  // The literal as it appears in the SGF content
  const std::regex SgfcPrivateConstants::UnescapedComposedValueSeparatorTokenRegex(
    SgfcPrivateConstants::ComposedValueSeparatorToken);
  const std::regex SgfcPrivateConstants::UnescapedEscapeCharacterRegex(
    SgfcPrivateConstants::EscapeCharacterToken +   // Make the following escape character a literal for the regex
    SgfcPrivateConstants::EscapeCharacterToken);  // The literal as it appears in the SGF content
  const std::regex SgfcPrivateConstants::UnescapedLineEndingsRegex(
    SgfcPrivateConstants::LineEndingsPattern);
  const std::regex SgfcPrivateConstants::ZeroOrMoreLineEndingsAtEndOfStringRegex(
    SgfcPrivateConstants::LineEndingsPattern + "*$");


  const std::string SgfcPrivateConstants::LineToken = "Line:";
  const std::string SgfcPrivateConstants::ColumnToken = "Col:";
  const std::string SgfcPrivateConstants::DashToken = "-";
  const std::string SgfcPrivateConstants::WarningToken = "Warning";
  const std::string SgfcPrivateConstants::ErrorUpperCaseToken = "Error";
  const std::string SgfcPrivateConstants::FatalToken = "Fatal";
  const std::string SgfcPrivateConstants::ErrorLowerCaseToken = "error";
  const std::string SgfcPrivateConstants::CriticalToken = "(critical):";

  const std::map<SgfcArgumentType, std::string> SgfcPrivateConstants::ArgumentTypeToCmdlineOptionMap =
  {
    { SgfcArgumentType::BeginningOfSgfData, "-b" },
    { SgfcArgumentType::DisableMessageNumber, "-d" },
    { SgfcArgumentType::DisableWarningMessages, "-w" },
    { SgfcArgumentType::HardLineBreakMode, "-l" },
    { SgfcArgumentType::LineBreakAtEndOfNode, "-L" },
    { SgfcArgumentType::NoSoftLineBreaksInTextValues, "-t" },
    { SgfcArgumentType::DeleteMarkupOnCurrentMove, "-m" },
    { SgfcArgumentType::DeleteEmptyNodes, "-n" },
    { SgfcArgumentType::DeleteObsoleteProperties, "-o" },
    { SgfcArgumentType::DeleteUnknownProperties, "-u" },
    { SgfcArgumentType::DeletePropertyType, "-y" },
    { SgfcArgumentType::UseOldPassMoveNotation, "-p" },
    { SgfcArgumentType::EnableRestrictiveChecking, "-r" },
    { SgfcArgumentType::CorrectVariationLevelAndRootMoves, "-v" },
    { SgfcArgumentType::ReverseVariationOrdering, "-z" },
    { SgfcArgumentType::ExpandCompressedPointLists, "-e" },
  };

  const SgfcMessageType SgfcPrivateConstants::DefaultMessageType = SgfcMessageType::FatalError;
  const bool SgfcPrivateConstants::DefaultIsCriticalMessage = false;
  const std::string SgfcPrivateConstants::DefaultMessageText = SgfcPrivateConstants::EmptyString;
  const std::string SgfcPrivateConstants::DefaultRawMessageText = SgfcPrivateConstants::EmptyString;
}
