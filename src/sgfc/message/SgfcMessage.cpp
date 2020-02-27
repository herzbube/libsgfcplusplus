// Project includes
#include "../../SgfcConstants.h"
#include "SgfcMessage.h"

namespace LibSgfcPlusPlus
{
  SgfcMessage::SgfcMessage()
    : messageID(SgfcConstants::DefaultMessageID)
    , messageType(SgfcConstants::DefaultMessageType)
    , lineNumber(SgfcConstants::DefaultLineNumber)
    , columnNumber(SgfcConstants::DefaultColumnNumber)
    , isCriticalMessage(SgfcConstants::DefaultIsCriticalMessage)
    , messageText(SgfcConstants::DefaultMessageText)
    , rawMessageText(SgfcConstants::DefaultRawMessageText)
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
      SgfcConstants::DefaultLineNumber,
      SgfcConstants::DefaultColumnNumber,
      SgfcConstants::DefaultIsCriticalMessage,
      messageText,
      messageText));

    return sgfcMessage;
  }
}
