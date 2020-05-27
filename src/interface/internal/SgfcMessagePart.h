#pragma once

namespace LibSgfcPlusPlus
{
  /// @brief Enumerates the individual parts of an SGFC message.
  /// 
  /// The message format according to the SGFC documentation file is this:
  ///
  /// "[Line:x Col:x - ] Message type and number [(critical)]: message text"
  ///
  /// Examples:
  ///
  /// Line:2 Col:56 - Error 8 (critical): illegal char(s) found: "fsgdf"
  /// Line:35 Col:1 - Warning 35: unknown property <XX> found
  /// Fatal error 2: unknown command line option 'x'
  /// Error 60: file contains more than one game tree
  enum class SgfcMessagePart
  {
    LineNumberOrMessageTypeToken,
    ColumnNumber,
    ErrorLowerCaseToken,
    Dash,
    MessageType,
    MessageID,
    CriticalIndicator,
    MessageText,
  };
}
