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
    SgfcMessage();
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

    /// @brief Returns a newly constructed ISgfcMessage object with message type
    /// SgfcMessageType::FatalError that has the specified message ID and
    /// message text.
    static std::shared_ptr<ISgfcMessage> CreateFatalErrorMessage(
      int messageID,
      const std::string& messageText);

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
