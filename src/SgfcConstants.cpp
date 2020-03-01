// Project includes
#include "SgfcConstants.h"

namespace LibSgfcPlusPlus
{
  const std::string SgfcConstants::LibraryName = "libsgfc++";

  const std::string SgfcConstants::EmptyString = "";
  const std::string SgfcConstants::SpaceCharacter = " ";
  const char SgfcConstants::NewlineCharacter = '\n';
  const std::string SgfcConstants::DoubleNormalString = "1";
  const std::string SgfcConstants::DoubleEmphasizedString = "2";
  const std::string SgfcConstants::ColorBlackString = "B";
  const std::string SgfcConstants::ColorWhiteString = "W";

  const std::string SgfcConstants::LineToken = "Line:";
  const std::string SgfcConstants::ColumnToken = "Col:";
  const std::string SgfcConstants::DashToken = "-";
  const std::string SgfcConstants::WarningToken = "Warning";
  const std::string SgfcConstants::ErrorUpperCaseToken = "Error";
  const std::string SgfcConstants::FatalToken = "Fatal";
  const std::string SgfcConstants::ErrorLowerCaseToken = "error";
  const std::string SgfcConstants::CriticalToken = "(critical):";

  const std::string SgfcConstants::ShortOptionPrefix = "-";
  const std::string SgfcConstants::LongOptionPrefix = "--";
  const std::string SgfcConstants::ShortHelpOption = "-h";
  const std::string SgfcConstants::LongHelpOption = "--help";
  const std::string SgfcConstants::VersionOption = "--version";
  const std::string SgfcConstants::InteractiveModeOption = "-i";
  const std::string SgfcConstants::WriteFileEvenIfCriticalErrorOccurs = "-c";
  const std::string SgfcConstants::PrintGameSignature = "-g";

  const int SgfcConstants::InvalidMessageID = -1;
  const int SgfcConstants::UnknownSgfcMessageID = -2;
  const int SgfcConstants::BannedArgumentMessageID = -3;
  const int SgfcConstants::ParseArgumentErrorMessageID = -4;

  const int SgfcConstants::DefaultMessageID = SgfcConstants::InvalidMessageID;
  const SgfcMessageType SgfcConstants::DefaultMessageType = SgfcMessageType::Warning;
  const int SgfcConstants::DefaultLineNumber = -1;
  const int SgfcConstants::DefaultColumnNumber = -1;
  const bool SgfcConstants::DefaultIsCriticalMessage = -1;
  const std::string SgfcConstants::DefaultMessageText = SgfcConstants::EmptyString;
  const std::string SgfcConstants::DefaultRawMessageText = SgfcConstants::EmptyString;

  const SgfcGameType SgfcConstants::DefaultGameType = SgfcGameType::Go;
}
