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

#pragma once

// Project includes
#include "../../../include/ISgfcArgument.h"
#include "../../../include/ISgfcMessage.h"
#include "SgfcBackendDataWrapper.h"
#include "SgfcBackendLoadResult.h"
#include "SgfcBackendSaveResult.h"
#include "SgfcDataLocation.h"
#include "SgfcOptions.h"

// C++ Standard Library includes
#include <memory>
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class SgfcSgfContent;

  /// @brief The SgfcBackendController class encapsuslates the SGFC backend and
  /// is responsible for coordinating access to it.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-backend
  ///
  /// SgfcBackendController provides its service to other library-internal
  /// classes. The external user of libsgfc++ never comes into direct contact
  /// with SgfcBackendController.
  ///
  /// When SgfcBackendController is instantiated a set of SGFC command line
  /// arguments must be specified that determine how all further SGFC backend
  /// operations behave. The SGFC command line arguments cannot be changed after
  /// construction. SgfcBackendController validates the arguments and forbids
  /// all operations if they are not valid.
  ///
  /// After construction SgfcBackendController is responsible for translating
  /// load or save operations invoked by the owner of the SgfcBackendController
  /// instance into the correct SGFC API calls. This includes:
  /// - Setting up the data structures required by SGFC for its operation
  /// - Applying the command line arguments that were passed to
  ///   SgfcBackendController on construction
  /// - Capturing the stream of messages generated by SGFC
  /// - Making the results of the operation available to the owner of the
  ///   SgfcBackendController instance.
  ///
  /// In addition SgfcBackendController is responsible for serializing
  /// operations that are started concurrently. Unfortunately it is impossible
  /// to run SGFC operations in parallel because SGFC uses a global output
  /// channel for sending its messages.
  ///
  /// @note If the SGFC message output channel becomes non-global in the future
  /// some libsgfc++ things will also have to be changed before concurrent
  /// operations can be allowed to run non-serialized. A known class is
  /// SgfcSaveStream which uses internal static functions to capture the SGFC
  /// save stream.
  ///
  /// SGFC has a central memory allocation function (actually a preprocessor
  /// macro). When this function fails to allocate memory it invokes an
  /// out-of-memory hook/callback to handle the error. The SGFC-internal default
  /// hook/callback simply calls exit() and terminates the operating system
  /// process. When the first instance of SgfcBackendController is created,
  /// that instance installs its own hook/callback which throws
  /// std::runtime_error instead of calling exit(). This is done in the remote
  /// hope that an out-of-memory situation might possibly be salvaged without
  /// terminating the OS process. The SGFC memory allocation function is
  /// already invoked when SgfcBackendController is constructed (in the
  /// SgfcOption constructor), so when memory allocation fails at that moment
  /// one of two things can happen:
  /// - If this is the first instance of SgfcBackendController then the
  ///   replacement hook/callback has not been installed yet and exit() will
  ///   be called by SGFC's hook/callback.
  /// - If this is the second or a later instance of SgfcBackendController then
  ///   the replacement hook/callback has been installed and std::runtime_error
  ///   will be called by the replacement hook/callback.
  class SgfcBackendController
  {
  public:
    /// @brief Initializes a newly constructed SgfcBackendController object
    /// that passes no command line arguments to SGFC.
    ///
    /// @exception std::runtime_error Is thrown if a memory allocation error
    /// occurs. If this is the first SgfcBackendController instance that is
    /// created then no exception will be thrown, instead the operating system
    /// process will be terminate with a call to exit(). See the
    /// SgfcBackendController class documentation for details.
    SgfcBackendController();

    /// @brief Initializes a newly constructed SgfcBackendController object.
    /// All SGFC backend operations performed by the SgfcBackendController
    /// object behave according to the specified command line arguments
    /// @a arguments.
    ///
    /// @exception std::runtime_error Is thrown if a memory allocation error
    /// occurs. If this is the first SgfcBackendController instance that is
    /// created then no exception will be thrown, instead the operating system
    /// process will be terminate with a call to exit(). See the
    /// SgfcBackendController class documentation for details.
    SgfcBackendController(const std::vector<std::shared_ptr<ISgfcArgument>>& arguments);

    /// @brief Destroys and cleans up the SgfcBackendController object.
    virtual ~SgfcBackendController();

    /// @brief Returns the SGFC command line arguments that were used to
    /// construct the SgfcBackendController object. The collection is empty if
    /// the SgfcBackendController object was constructed with the default
    /// constructor.
    std::vector<std::shared_ptr<ISgfcArgument>> GetArguments() const;

    /// @brief Returns true if the SGFC command line arguments that
    /// GetArguments() returns are valid. Returns false if they are not valid.
    ///
    /// One known case where the command line arguments can be invalid is if
    /// an illegal parameter is specified for one of the arguments that require
    /// a parameter. Example: SgfcArgumentType::BeginningOfSgfData requires an
    /// integer parameter. The argument is invalid if an integer value is
    /// specified that is not within the accepted range.
    ///
    /// There may be other cases. Invoke GetInvalidCommandLineReason() to learn
    /// the actual reason why the command line arguments are not valid.
    bool IsCommandLineValid() const;

    /// @brief Returns an ISgfcMessage object with message type
    /// #SgfcMessageType::FatalError that describes why the SGFC command
    /// line arguments that GetArguments() returns are not valid. This method
    /// may only be invoked if IsCommandLineValid() returns false.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// true.
    std::shared_ptr<ISgfcMessage> GetInvalidCommandLineReason() const;

    /// @brief Loads a single .sgf file from the specified path and puts it
    /// through the SGFC parser. This method may only be invoked if
    /// IsCommandLineValid() returns true.
    ///
    /// @return An SgfcBackendLoadResult object that holds the result of the
    /// load operation. Notably if the operation was successful the result
    /// object contains the SGF content that was loaded.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    std::shared_ptr<SgfcBackendLoadResult> LoadSgfFile(
      const std::string& sgfFilePath);

    /// @brief Loads the specified SGF content and puts it through the SGFC
    /// parser. This method may only be invoked if IsCommandLineValid() returns
    /// true.
    ///
    /// @return An SgfcBackendLoadResult object that holds the result of the
    /// load operation. Notably if the operation was successful the result
    /// object contains the SGF content that was loaded.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    std::shared_ptr<SgfcBackendLoadResult> LoadSgfContent(
      const std::string& sgfContent);

    /// @brief Saves the SGF content that is encapsulated by @a sgfDataWrapper
    /// to the .sgf file at the specified path @a sgfFilePath. This method may
    /// only be invoked if IsCommandLineValid() returns true.
    ///
    /// If a file already exists at the specified path it is overwritten.
    ///
    /// Before SgfcBackendController can invoke the SGFC save function, it
    /// needs to pass the SGF content through SGFC's load/parse functions.
    /// The messages in the result object therefore are a combination of a full
    /// cycle of SGFC load/parse/save operations.
    ///
    /// @return An SgfcBackendSaveResult object that holds the result of the
    /// save operation.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    std::shared_ptr<SgfcBackendSaveResult> SaveSgfFile(
      const std::string& sgfFilePath,
      std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper);

    /// @brief Saves the SGF content that is encapsulated by @a sgfDataWrapper
    /// into the specified string object. This method may only be invoked if
    /// IsCommandLineValid() returns true.
    ///
    /// The previous content of @a sgfContent is overwritten.
    ///
    /// Before SgfcBackendController can invoke the SGFC save function, it
    /// needs to pass the SGF content through SGFC's load/parse functions.
    /// The messages in the result object therefore are a combination of a full
    /// cycle of SGFC load/parse/save operations.
    ///
    /// @return An SgfcBackendSaveResult object that holds the result of the
    /// save operation.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    std::shared_ptr<SgfcBackendSaveResult> SaveSgfContent(
      std::string& sgfContent,
      std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper);

  private:
    std::vector<std::shared_ptr<ISgfcArgument>> arguments;
    std::shared_ptr<ISgfcMessage> invalidCommandLineReason;
    SgfcOptions sgfcOptions;

    void InstallOutOfMemoryErrorHookIfNotYetInstalled();

    void ParseArguments(const std::vector<std::shared_ptr<ISgfcArgument>>& arguments);
    std::vector<std::string> ConvertArgumentsToArgvStyle(const std::vector<std::shared_ptr<ISgfcArgument>>& arguments) const;
    void InitializeArgv(const char** argv, const std::vector<std::string>& argvArguments) const;
    void InvokeSgfcParseArgs(int argc, const char** argv);

    std::shared_ptr<SgfcBackendLoadResult> LoadSgfContentFromFilesystemOrInMemoryBuffer(
      const std::string& sgfFilePath,
      const std::string& sgfContent,
      SgfcDataLocation dataLocation);
    std::shared_ptr<SgfcBackendSaveResult> SaveSgfContentToFilesystemOrInMemoryBuffer(
      const std::string& sgfFilePath,
      std::string& sgfContent,
      std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper,
      SgfcDataLocation dataLocation);

    bool SaveSgfContentToFilesystem(std::shared_ptr<SgfcSgfContent> sgfContent) const;

    void SetInvalidCommandLineReasonFromParseArgsMessages(
      const std::vector<std::shared_ptr<ISgfcMessage>>& parseArgsMessages);
    void SetInvalidCommandLineReasonBecauseMemoryAllocationFailed();

    void ThrowIfIsCommandLineValidReturnsTrue() const;
    void ThrowIfIsCommandLineValidReturnsFalse() const;
  };
}
