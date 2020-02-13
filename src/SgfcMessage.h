#pragma once

// Project includes
#include "../include/ISgfcMessage.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcMessage class provides an implementation of the
  /// ISgfcMessage interface. See the interface header file for
  /// documentation.
  class SgfcMessage : public ISgfcMessage
  {
  public:
    SgfcMessage(
      int messageID,
      SgfcMessageType messageType,
      int lineNumber,
      int columnNumber,
      bool isCriticalMessage,
      const std::string& messageText,
      const std::string& rawMessageText);
    virtual ~SgfcMessage();
  
    virtual int GetMessageID() const;

    virtual SgfcMessageType GetMessageType() const;

    virtual int GetLineNumber() const;
    virtual int GetColumnNumber() const;

    virtual bool IsCriticalMessage() const;

    virtual std::string GetMessageText() const;
    virtual std::string GetRawMessageText() const;

  private:
    int messageID;
    SgfcMessageType messageType;
    int lineNumber;
    int columnNumber;
    bool isCriticalMessage;
    std::string messageText;
    std::string rawMessageText;
  };
}
