#pragma once

// Project includes
#include "../include/SgfcMessageType.h"

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcConstants class is a container class for constants.
  class SgfcConstants
  {
  public:
    static const std::string LibraryName;

    static const std::string EmptyString;
    static const std::string SpaceCharacter;
    static const char NewlineCharacter;
    static const std::string DoubleNormalString;
    static const std::string DoubleEmphasizedString;
    static const std::string ColorBlackString;
    static const std::string ColorWhiteString;

    static const std::string LineToken;
    static const std::string ColumnToken;
    static const std::string DashToken;
    static const std::string WarningToken;
    static const std::string ErrorUpperCaseToken;
    static const std::string FatalToken;
    static const std::string ErrorLowerCaseToken;
    static const std::string CriticalToken;

    static const std::string ShortOptionPrefix;
    static const std::string LongOptionPrefix;
    static const std::string ShortHelpOption;
    static const std::string LongHelpOption;
    static const std::string VersionOption;
    static const std::string InteractiveModeOption;
    static const std::string WriteFileEvenIfCriticalErrorOccurs;
    static const std::string PrintGameSignature;

    /// @brief This constant is used to indicate a message without a valid ID
    /// but whose origin is not defined. For instance, a default constructed
    /// ISgfcMessage object has this ID.
    static const int InvalidMessageID;
    /// @brief This constant is used when a message that is known to originate
    /// from SGFC is parsed, and its ID cannot be determined from the raw
    /// message text.
    static const int UnknownSgfcMessageID;
    /// @brief Indicates a fatal error due to an SGFC command line argument
    /// that is banned by libsgfc++.
    static const int BannedArgumentMessageID;
    /// @brief Indicates a fatal error that occurred during parsing of the
    /// SGFC command line argument.
    static const int ParseArgumentErrorMessageID;

    static const int DefaultMessageID;
    static const SgfcMessageType DefaultMessageType;
    static const int DefaultLineNumber;
    static const int DefaultColumnNumber;
    static const bool DefaultIsCriticalMessage;
    static const std::string DefaultMessageText;
    static const std::string DefaultRawMessageText;
  };
}
