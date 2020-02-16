// Project includes
#include "SgfcMessage.h"
#include "SgfcConstants.h"

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
}
