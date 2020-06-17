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

  const std::string SgfcPrivateConstants::LineToken = "Line:";
  const std::string SgfcPrivateConstants::ColumnToken = "Col:";
  const std::string SgfcPrivateConstants::DashToken = "-";
  const std::string SgfcPrivateConstants::WarningToken = "Warning";
  const std::string SgfcPrivateConstants::ErrorUpperCaseToken = "Error";
  const std::string SgfcPrivateConstants::FatalToken = "Fatal";
  const std::string SgfcPrivateConstants::ErrorLowerCaseToken = "error";
  const std::string SgfcPrivateConstants::CriticalToken = "(critical):";

  const std::string SgfcPrivateConstants::ShortOptionPrefix = "-";
  const std::string SgfcPrivateConstants::LongOptionPrefix = "--";
  const std::string SgfcPrivateConstants::ShortHelpOption = "-h";
  const std::string SgfcPrivateConstants::LongHelpOption = "--help";
  const std::string SgfcPrivateConstants::VersionOption = "--version";
  const std::string SgfcPrivateConstants::InteractiveModeOption = "-i";
  const std::string SgfcPrivateConstants::WriteFileEvenIfCriticalErrorOccurs = "-c";
  const std::string SgfcPrivateConstants::PrintGameSignature = "-g";

  const SgfcMessageType SgfcPrivateConstants::DefaultMessageType = SgfcMessageType::FatalError;
  const bool SgfcPrivateConstants::DefaultIsCriticalMessage = false;
  const std::string SgfcPrivateConstants::DefaultMessageText = SgfcPrivateConstants::EmptyString;
  const std::string SgfcPrivateConstants::DefaultRawMessageText = SgfcPrivateConstants::EmptyString;
}
