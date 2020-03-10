// Project includes
#include "../../SgfcPrivateConstants.h"
#include "SgfcMessage.h"

namespace LibSgfcPlusPlus
{
  SgfcMessage::SgfcMessage()
    : messageID(SgfcPrivateConstants::DefaultMessageID)
    , messageType(SgfcPrivateConstants::DefaultMessageType)
    , lineNumber(SgfcPrivateConstants::DefaultLineNumber)
    , columnNumber(SgfcPrivateConstants::DefaultColumnNumber)
    , isCriticalMessage(SgfcPrivateConstants::DefaultIsCriticalMessage)
    , messageText(SgfcPrivateConstants::DefaultMessageText)
    , rawMessageText(SgfcPrivateConstants::DefaultRawMessageText)
  {
  }

  SgfcMessage::SgfcMessage(
    int messageID,
    SgfcMessageType messageType,
    int lineNumber,
    int columnNumber,
    bool isCriticalMessage,
    const std::string& messageText,
    const std::string& rawMessageText)
    : messageID(messageID)
    , messageType(messageType)
    , lineNumber(lineNumber)
    , columnNumber(columnNumber)
    , isCriticalMessage(isCriticalMessage)
    , messageText(messageText)
    , rawMessageText(rawMessageText)
  {
  }

  SgfcMessage::~SgfcMessage()
  {
  }

  int SgfcMessage::GetMessageID() const
  {
    return this->messageID;
  }

  SgfcMessageType SgfcMessage::GetMessageType() const
  {
    return this->messageType;
  }

  int SgfcMessage::GetLineNumber() const
  {
    return this->lineNumber;
  }

  int SgfcMessage::GetColumnNumber() const
  {
    return this->columnNumber;
  }

  bool SgfcMessage::IsCriticalMessage() const
  {
    return this->isCriticalMessage;
  }

  std::string SgfcMessage::GetMessageText() const
  {
    return this->messageText;
  }

  std::string SgfcMessage::GetRawMessageText() const
  {
    return this->rawMessageText;
  }

  std::shared_ptr<ISgfcMessage> SgfcMessage::CreateFatalErrorMessage(
    int messageID,
    const std::string& messageText)
  {
    std::shared_ptr<ISgfcMessage> sgfcMessage = std::shared_ptr<ISgfcMessage>(new SgfcMessage(
      messageID,
      SgfcMessageType::FatalError,
      SgfcPrivateConstants::DefaultLineNumber,
      SgfcPrivateConstants::DefaultColumnNumber,
      SgfcPrivateConstants::DefaultIsCriticalMessage,
      messageText,
      messageText));

    return sgfcMessage;
  }
}
