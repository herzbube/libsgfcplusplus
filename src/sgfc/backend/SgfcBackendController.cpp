// -----------------------------------------------------------------------------
// Copyright 2020 Patrick Näf (herzbube@herzbube.ch)
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
#include "../message/SgfcMessage.h"
#include "../message/SgfcMessageStream.h"
#include "../save/SgfcSaveStream.h"
#include "../save/SgfcSgfContent.h"
#include "SgfcBackendController.h"

// SGFC includes
extern "C"
{
  #include "../../../sgfc/src/all.h"
  #include "../../../sgfc/src/protos.h"
}

// C++ Standard Library includes
#include <algorithm>
#include <fstream>
#include <mutex>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  static std::mutex sgfcMutex;

  // ----------------------------------------------------------------------
  // Hook/callback function prototype used to interact with SGFC.
  // ----------------------------------------------------------------------

  static void OutOfMemoryErrorHook(const char* detail)
  {
    // SgfcBackendController handles this exception in a few places
    throw std::runtime_error("SGFC failed to allocate memory");
  }

  // ----------------------------------------------------------------------
  // The SgfcBackendController class.
  // ----------------------------------------------------------------------

  SgfcBackendController::SgfcBackendController()
    : invalidCommandLineReason(nullptr)
  {
    std::lock_guard sgfcGuard(sgfcMutex);

    InstallOutOfMemoryErrorHookIfNotYetInstalled();
    ParseArguments(this->arguments);
  }

  SgfcBackendController::SgfcBackendController(const std::vector<std::shared_ptr<ISgfcArgument>>& arguments)
    : arguments(arguments)
    , invalidCommandLineReason(nullptr)
  {
    std::lock_guard sgfcGuard(sgfcMutex);

    InstallOutOfMemoryErrorHookIfNotYetInstalled();
    ParseArguments(this->arguments);
  }

  SgfcBackendController::~SgfcBackendController()
  {
  }

  std::vector<std::shared_ptr<ISgfcArgument>> SgfcBackendController::GetArguments() const
  {
    return this->arguments;
  }

  bool SgfcBackendController::IsCommandLineValid() const
  {
    if (this->invalidCommandLineReason == nullptr)
      return true;
    else
      return false;
  }

  std::shared_ptr<ISgfcMessage> SgfcBackendController::GetInvalidCommandLineReason() const
  {
    ThrowIfIsCommandLineValidReturnsTrue();

    return this->invalidCommandLineReason;
  }

  std::shared_ptr<SgfcBackendLoadResult> SgfcBackendController::LoadSgfFile(const std::string& sgfFilePath)
  {
    std::string sgfContent;
    return LoadSgfContentFromFilesystemOrInMemoryBuffer(sgfFilePath, sgfContent, SgfcDataLocation::Filesystem);
  }

  std::shared_ptr<SgfcBackendLoadResult> SgfcBackendController::LoadSgfContent(const std::string& sgfContent)
  {
    std::string sgfFilePath;
    return LoadSgfContentFromFilesystemOrInMemoryBuffer(sgfFilePath, sgfContent, SgfcDataLocation::InMemoryBuffer);
  }

  std::shared_ptr<SgfcBackendSaveResult> SgfcBackendController::SaveSgfFile(
    const std::string& sgfFilePath,
    std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper)
  {
    std::string sgfContent;
    return SaveSgfContentToFilesystemOrInMemoryBuffer(sgfFilePath, sgfContent, sgfDataWrapper, SgfcDataLocation::Filesystem);
  }

  std::shared_ptr<SgfcBackendSaveResult> SgfcBackendController::SaveSgfContent(
    std::string& sgfContent,
    std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper)
  {
    std::string sgfFilePath;
    return SaveSgfContentToFilesystemOrInMemoryBuffer(sgfFilePath, sgfContent, sgfDataWrapper, SgfcDataLocation::InMemoryBuffer);
  }

  void SgfcBackendController::InstallOutOfMemoryErrorHookIfNotYetInstalled()
  {
    if (oom_panic_hook != OutOfMemoryErrorHook)
      oom_panic_hook = OutOfMemoryErrorHook;
  }

  void SgfcBackendController::ParseArguments(const std::vector<std::shared_ptr<ISgfcArgument>>& arguments)
  {
    std::vector<std::string> argvArguments = ConvertArgumentsToArgvStyle(arguments);

    int argc = static_cast<int>(argvArguments.size());
    const char** argv = new const char*[argc];

    try
    {
      InitializeArgv(argv, argvArguments);

      InvokeSgfcParseArgs(argc, argv);
    }
    catch (...)
    {
      delete[] argv;
      throw;
    }

    delete[] argv;
  }

  std::vector<std::string> SgfcBackendController::ConvertArgumentsToArgvStyle(const std::vector<std::shared_ptr<ISgfcArgument>>& arguments) const
  {
    std::vector<std::string> argvArguments =
    {
      // argv[0] in a main() function is the program name
      SgfcConstants::LibraryName,
    };

    for (auto argument : arguments)
    {
      argvArguments.push_back(argument->ToString());
    }

    return argvArguments;
  }

  void SgfcBackendController::InitializeArgv(const char** argv, const std::vector<std::string>& argvArguments) const
  {
    for (unsigned int indexOfArgument = 0; indexOfArgument < argvArguments.size(); indexOfArgument++)
    {
      const char* arg = argvArguments[indexOfArgument].c_str();

      // It is safe to keep the pointer to the internal string buffer as long
      // as we don't change the string content and as long as the vector of
      // strings does not change and remains in scope.
      argv[indexOfArgument] = arg;
    }
  }

  void SgfcBackendController::InvokeSgfcParseArgs(int argc, const char** argv)
  {
    SgfcMessageStream messageStream;

    SGFInfo* sgfc = NULL;

    try
    {
      sgfc = SetupSGFInfo(NULL);
      bool parseArgsResult = ParseArgs(sgfc, argc, argv);

      if (parseArgsResult)
      {
        // Capture the changed SGFC option values so that we can re-apply them
        // later on when we perform a load or save operation. There's no need
        // for doing that if the command line arguments are not valid, because
        // in that case a client is not allowed to perform load or save
        // operations.
        this->sgfcOptions.CaptureOptions(sgfc->options);
      }
      else
      {
        std::vector<std::shared_ptr<ISgfcMessage>> parseArgsMessages = messageStream.GetMessagees();
        SetInvalidCommandLineReasonFromParseArgsMessages(parseArgsMessages);
      }
    }
    catch (std::runtime_error&)
    {
      // SetupSGFInfo() and ParseArgs() both throw std::runtime_error if SGFC
      // fails to allocate memory. We handle the exception and hope that
      // freeing some memory will magically save the OS process from crashing.

      SetInvalidCommandLineReasonBecauseMemoryAllocationFailed();
    }

    if (sgfc)
      FreeSGFInfo(sgfc);
  }

  std::shared_ptr<SgfcBackendLoadResult> SgfcBackendController::LoadSgfContentFromFilesystemOrInMemoryBuffer(
    const std::string& sgfFilePath,
    const std::string& sgfContent,
    SgfcDataLocation dataLocation)
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    std::lock_guard sgfcGuard(sgfcMutex);

    try
    {
      std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper;
      if (dataLocation == SgfcDataLocation::Filesystem)
      {
        sgfDataWrapper =
          std::shared_ptr<SgfcBackendDataWrapper>(new SgfcBackendDataWrapper());
      }
      else
      {
        sgfDataWrapper =
          std::shared_ptr<SgfcBackendDataWrapper>(new SgfcBackendDataWrapper(sgfContent));
      }

      this->sgfcOptions.RestoreOptions(sgfDataWrapper->GetSgfData()->options);

      SgfcMessageStream messageStream;

      // The LoadSGF functions return false if a fatal error occurred
      bool loadSgfWasSuccessful;
      if (dataLocation == SgfcDataLocation::Filesystem)
        loadSgfWasSuccessful = LoadSGF(sgfDataWrapper->GetSgfData(), sgfFilePath.c_str());
      else
        loadSgfWasSuccessful = LoadSGFFromFileBuffer(sgfDataWrapper->GetSgfData());

      if (loadSgfWasSuccessful)
      {
        // ParseSGF never has fatal errors, so it does not return a status
        ParseSGF(sgfDataWrapper->GetSgfData());
        sgfDataWrapper->SetDataState(SgfcBackendDataState::FullyLoaded);
      }

      std::vector<std::shared_ptr<ISgfcMessage>> loadOperationMessages = messageStream.GetMessagees();

      std::shared_ptr<SgfcBackendLoadResult> backendLoadResult =
        std::shared_ptr<SgfcBackendLoadResult>(new SgfcBackendLoadResult(loadOperationMessages, sgfDataWrapper));
      return backendLoadResult;
    }
    catch (std::runtime_error&)
    {
      // The SgfcBackendDataWrapper constructor, LoadSGF(),
      // LoadSGFFromFileBuffer() and ParseArgs() all throw std::runtime_error
      // if SGFC fails to allocate memory. We handle the exception and hope that
      // freeing some memory will magically save the OS process from crashing.

      std::vector<std::shared_ptr<ISgfcMessage>> loadOperationMessages;
      loadOperationMessages.push_back(std::shared_ptr<ISgfcMessage>(new SgfcMessage(
        SgfcMessageID::OutOfMemoryError,
        "Memory allocation failed during load operation")));

      std::shared_ptr<SgfcBackendLoadResult> backendLoadResult =
        std::shared_ptr<SgfcBackendLoadResult>(new SgfcBackendLoadResult(loadOperationMessages, nullptr));
      return backendLoadResult;
    }
  }

  std::shared_ptr<SgfcBackendSaveResult> SgfcBackendController::SaveSgfContentToFilesystemOrInMemoryBuffer(
    const std::string& sgfFilePath,
    std::string& sgfContent,
    std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper,
    SgfcDataLocation dataLocation)
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    std::lock_guard sgfcGuard(sgfcMutex);

    this->sgfcOptions.RestoreOptions(sgfDataWrapper->GetSgfData()->options);

    SgfcMessageStream messageStream;

    try
    {
      bool loadDataWasSuccessful = true;
      if (sgfDataWrapper->GetDataState() == SgfcBackendDataState::PartiallyLoaded)
      {
        // LoadSGFFromFileBuffer returns false if a fatal error occurred
        loadDataWasSuccessful = LoadSGFFromFileBuffer(sgfDataWrapper->GetSgfData());
        if (loadDataWasSuccessful)
        {
          // ParseSGF never has fatal errors, so it does not return a status
          ParseSGF(sgfDataWrapper->GetSgfData());
          sgfDataWrapper->SetDataState(SgfcBackendDataState::FullyLoaded);
        }
      }

      std::vector<std::shared_ptr<SgfcSgfContent>> savedSgfContents;

      // Don't attempt to save if loading was not successful
      // TODO: Currently we only skip saving if a fatal error occurred. Shouldn't
      // we skip saving also for critical errors?
      if (loadDataWasSuccessful)
      {
        SgfcSaveStream saveStream;

        // SaveSGF() expects to receive a file name, so we have to give it one
        // even for SgfcDataLocation::InMemoryBuffer where we dont actually
        // interact with the filesystem. SaveSGF() can handle an empty file
        // name.
        // SaveSGF returns false if a fatal error occurred (which is exposed
        // to clients via ISgfcMessage) or in case the save handler factory
        // method in SgfcSaveStream returns nothing, i.e. an interfacing issue.
        bool saveDataWasSuccessful = SaveSGF(sgfDataWrapper->GetSgfData(), &SgfcSaveStream::CreateSaveFileHandler, sgfFilePath.c_str());
        if (saveDataWasSuccessful)
          savedSgfContents = saveStream.GetSgfContents();
      }

      // Here we get all messages, even messages from LoadSGFFromFileBuffer
      // and ParseSGF
      std::vector<std::shared_ptr<ISgfcMessage>> saveOperationMessages = messageStream.GetMessagees();

      // Initialize the out variable
      if (dataLocation == SgfcDataLocation::InMemoryBuffer)
        sgfContent = std::string();

      for (auto sgfContentLoop : savedSgfContents)
      {
        if (dataLocation == SgfcDataLocation::Filesystem)
        {
          bool success = SaveSgfContentToFilesystem(sgfContentLoop);
          if (! success)
          {
            std::string messageString = "Writing SGF file failed: " + sgfContentLoop->GetFilePath();

            auto message = std::shared_ptr<ISgfcMessage>(new SgfcMessage(
              SgfcMessageID::SaveSgfContentToFilesystemError,
              messageString));

            saveOperationMessages.push_back(message);
          }
        }
        else
        {
          sgfContent += sgfContentLoop->GetSgfContent();
        }
      }

      std::shared_ptr<SgfcBackendSaveResult> backendSaveResult =
        std::shared_ptr<SgfcBackendSaveResult>(new SgfcBackendSaveResult(saveOperationMessages));
      return backendSaveResult;
    }
    catch (std::runtime_error&)
    {
      // LoadSGFFromFileBuffer(), ParseArgs() and SaveSGF() all throw
      // std::runtime_error if SGFC fails to allocate memory. We handle the
      // exception and hope that freeing some memory will magically save the
      // OS process from crashing.

      std::vector<std::shared_ptr<ISgfcMessage>> saveOperationMessages;
      saveOperationMessages.push_back(std::shared_ptr<ISgfcMessage>(new SgfcMessage(
        SgfcMessageID::OutOfMemoryError,
        "Memory allocation failed during load operation")));

      std::shared_ptr<SgfcBackendSaveResult> backendSaveResult =
        std::shared_ptr<SgfcBackendSaveResult>(new SgfcBackendSaveResult(saveOperationMessages));
      return backendSaveResult;
    }
  }

  bool SgfcBackendController::SaveSgfContentToFilesystem(std::shared_ptr<SgfcSgfContent> sgfContent) const
  {
    std::string fileName = sgfContent->GetFilePath();

    std::ofstream out(fileName);
    if (out.fail())
      return false;  // SGFC generates fatal error FE_DEST_FILE_OPEN for this

    out << sgfContent->GetSgfContent();
    out.close();

    // Because of buffering we don't check immediately after outputting the
    // SGF content. Closing the stream flushes it, so afterwards the fail bit
    // is guaranteed to be set if an error occurred.
    if (out.fail())
      return false;  // SGFC generates fatal error FE_DEST_FILE_WRITE for this

    return true;
  }

  void SgfcBackendController::SetInvalidCommandLineReasonFromParseArgsMessages(
    const std::vector<std::shared_ptr<ISgfcMessage>>& parseArgsMessages)
  {
    for (const auto& message : parseArgsMessages)
    {
      if (message->GetMessageType() == SgfcMessageType::FatalError)
      {
        this->invalidCommandLineReason = message;
        return;
      }
    }

    // This should not happen. If it does then ParseArgs() returned false but
    // there was no fatal error in the message stream.
    this->invalidCommandLineReason = std::shared_ptr<ISgfcMessage>(new SgfcMessage(
      SgfcMessageID::ParseArgumentError,
      "SGFC failed to parse the specified arguments"));
  }

  void SgfcBackendController::SetInvalidCommandLineReasonBecauseMemoryAllocationFailed()
  {
    this->invalidCommandLineReason = std::shared_ptr<ISgfcMessage>(new SgfcMessage(
      SgfcMessageID::OutOfMemoryError,
      "Memory allocation failed during argument parsing"));
  }

  void SgfcBackendController::ThrowIfIsCommandLineValidReturnsTrue() const
  {
    if (this->IsCommandLineValid())
      throw std::logic_error("Interface protocol violation: IsCommandLineValid() returns true");
  }

  void SgfcBackendController::ThrowIfIsCommandLineValidReturnsFalse() const
  {
    if (! this->IsCommandLineValid())
      throw std::logic_error("Interface protocol violation: IsCommandLineValid() returns false");
  }
}
