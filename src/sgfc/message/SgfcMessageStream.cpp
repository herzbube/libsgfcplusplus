// -----------------------------------------------------------------------------
// Copyright 2024 Patrick Näf (herzbube@herzbube.ch)
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
#include "../../../include/SgfcConstants.h"
#include "../../SgfcPrivateConstants.h"
#include "SgfcMessage.h"
#include "SgfcMessageStream.h"

// C++ Standard Library includes
#include <cstring>  // for strerror() / strerror_s()
#include <regex>
#include <sstream>

// SGFC includes
extern "C"
{
  #include "../../../sgfc/src/all.h"
  #include "../../../sgfc/src/protos.h"
}

namespace LibSgfcPlusPlus
{
  // ----------------------------------------------------------------------
  // Hook/callback function prototype used to interact with SGFC.
  // ----------------------------------------------------------------------

  void PrintErrorOutputHook(struct SGFCError* sgfcError);

  // ----------------------------------------------------------------------
  // Static variables used by the hook function to store the captured messages.
  // ----------------------------------------------------------------------

  static std::vector<std::shared_ptr<ISgfcMessage>> messages;
  static bool capturingIsInProgress = false;

  // ----------------------------------------------------------------------
  // The SgfcMessageStream class.
  // ----------------------------------------------------------------------

  SgfcMessageStream::SgfcMessageStream()
  {
    if (capturingIsInProgress)
      throw std::logic_error("Another SgfcMessageStream object is already capturing the SGFC message stream");

    print_error_output_hook = PrintErrorOutputHook;
    messages.clear();
    capturingIsInProgress = true;
  }

  SgfcMessageStream::~SgfcMessageStream()
  {
    print_error_output_hook = NULL;
    messages.clear();
    capturingIsInProgress = false;
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcMessageStream::GetMessagees() const
  {
    return messages;
  }

  // The implementation of this function is inspired by the implementation of
  // the SGFC-internal PrintErrorOutputHook() function. If in doubt check there
  // to see how SGFC interprets the SGFCError data.
  void PrintErrorOutputHook(struct SGFCError* sgfcError)
  {
    // We use this stringstream to accumulate an error message that looks
    // exactly as if it had been printed by SGFC on the command-line. Check the
    // SGFC-internal PrintErrorOutputHook() function to see the relevant message
    // fragments.
    std::stringstream formattedMessageTextStream;
    // Make sure that decimal point is always a period (".") character and that
    // there are no thousands separators
    formattedMessageTextStream.imbue(std::locale::classic());

    unsigned long lineNumber = sgfcError->row;
    unsigned long columnNumber = sgfcError->col;
    if (lineNumber > 0 && columnNumber > 0)
    {
      formattedMessageTextStream
        << "Line:" << lineNumber
        << " Col:" << columnNumber
        << " - ";
    }
    else
    {
      lineNumber = SgfcConstants::InvalidLineNumber;
      columnNumber = SgfcConstants::InvalidColumnNumber;
    }

    SgfcMessageID messageID;
    // Casting to int should be safe after applying the bitwise-and operator.
    // The SGFC code internally does the same.
    int messageIDAsInt = static_cast<int>(sgfcError->error & M_ERROR_NUM);
    // It's hard to imagine how this should ever become true, but we want to
    // be 100% sure that negative numbers are reserved for the library.
    if (messageIDAsInt < 0)
      messageID = SgfcMessageID::UnknownSgfcMessageID;
    else
      messageID = static_cast<SgfcMessageID>(messageIDAsInt);
    
    SgfcMessageType messageType;
    switch (sgfcError->error & M_ERROR_TYPE)
    {
      case E_ERROR:
        messageType = SgfcMessageType::Error;
        formattedMessageTextStream << "Error " << messageIDAsInt;
        break;
      case E_WARNING:
        messageType = SgfcMessageType::Warning;
        formattedMessageTextStream << "Warning " << messageIDAsInt;
        break;
      case E_FATAL_ERROR:
      // Fall-through intentional. This should not occur unless a new version
      // of SGFC introduces a new message type, in which case we have a problem
      // that should not go unnoticed. Fatal errors will prevent at least the
      // reading of documents with SgfcDocumentReader.
      default:
        messageType = SgfcMessageType::FatalError;
        formattedMessageTextStream << "Fatal error " << messageIDAsInt;
        break;
    }

    bool isCriticalMessage = sgfcError->error & E_CRITICAL;
    if (isCriticalMessage)
      formattedMessageTextStream << " (critical): ";
    else
      formattedMessageTextStream << ": ";

    std::string messageText = sgfcError->message;
    // The message contains a line ending which we have to remove
    messageText = std::regex_replace(
      messageText,
      SgfcPrivateConstants::ZeroOrMoreLineEndingsAtEndOfStringRegex,
      SgfcPrivateConstants::EmptyString);
    formattedMessageTextStream << messageText;

    // errno is initialized with 0 when the program starts. Standard library
    // functions never store 0 (zero) in errno, so that value is good enough
    // for us to indicate "no error".
    int libraryErrorNumber = SgfcConstants::LibraryErrorNumberNoError;
    if (sgfcError->error & E_ERRNO)
    {
      // Standard library functions indicate errors by writing positive
      // integers to errno. We accept everything except 0 (which is our
      // indication for "no error").
      if (sgfcError->lib_errno != SgfcConstants::LibraryErrorNumberNoError)
      {
        libraryErrorNumber = sgfcError->lib_errno;

#ifdef _MSC_VER
        char fileErrorLocalizedDescription[200];
        errno_t strerrorResult = strerror_s(
          fileErrorLocalizedDescription,
          sizeof(fileErrorLocalizedDescription),
          libraryErrorNumber);
        if (strerrorResult == 0)
          formattedMessageTextStream << fileErrorLocalizedDescription;
        else
          formattedMessageTextStream << "error code:" << libraryErrorNumber;
#else
        char* fileErrorLocalizedDescription = strerror(libraryErrorNumber);
        if (fileErrorLocalizedDescription)
          formattedMessageTextStream << fileErrorLocalizedDescription;
        else
          formattedMessageTextStream << "error code:" << libraryErrorNumber;
#endif
      }
    }

    std::shared_ptr<ISgfcMessage> sgfcMessage = std::shared_ptr<ISgfcMessage>(new SgfcMessage(
      messageID,
      messageType,
      lineNumber,
      columnNumber,
      isCriticalMessage,
      libraryErrorNumber,
      messageText,
      formattedMessageTextStream.str()));

    messages.push_back(sgfcMessage);
  }
}
