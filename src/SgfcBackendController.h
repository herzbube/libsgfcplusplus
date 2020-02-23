#pragma once

// Project includes
#include "../include/ISgfcMessage.h"
#include "SgfcBackendDataWrapper.h"
#include "SgfcBackendLoadResult.h"
#include "SgfcBackendSaveResult.h"
#include "SgfcOptions.h"

// C++ Standard Library includes
#include <memory>
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcBackendController class encapsuslates the SGFC backend and
  /// is responsible for coordinating access to it.
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
  /// After construction SgfcBackendController is responsible for managing the
  /// global state of the SGFC backend before and after each operation:
  /// - Reset global variables.
  /// - Re-apply command line arguments.
  /// - Obtain a copy of the results of the operation and make them available
  ///   to the owner of the SgfcBackendController instance.
  ///
  /// In addition SgfcBackendController is responsible for serializing
  /// operations that are started concurrently. Unfortunately it is impossible
  /// to run SGFC operations in parallel because SGFC makes heavy use of global
  /// variables and a global output channel for sending its messages.
  class SgfcBackendController
  {
  public:
    /// @brief Initializes a newly constructed SgfcBackendController object
    /// that passes no command line arguments to SGFC.
    SgfcBackendController();

    /// @brief Initializes a newly constructed SgfcBackendController object.
    /// All SGFC backend operations performed by the SgfcBackendController
    /// object behave according to the specified command line arguments
    /// @a arguments.
    SgfcBackendController(const std::vector<std::string>& arguments);

    /// @brief Destroys and cleans up the SgfcBackendController object.
    virtual ~SgfcBackendController();

    std::vector<std::string> GetArguments() const;
    bool IsCommandLineValid() const;
    std::shared_ptr<ISgfcMessage> GetInvalidCommandLineReason() const;

    std::shared_ptr<SgfcBackendLoadResult> LoadSgfFile(
      const std::string& sgfFilePath);
    std::shared_ptr<SgfcBackendSaveResult> SaveSgfFile(
      const std::string& sgfFilePath,
      std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper);

  private:
    std::vector<std::string> arguments;
    std::shared_ptr<ISgfcMessage> invalidCommandLineReason;
    SgfcOptions sgfcOptions;

    void ParseArguments(const std::vector<std::string>& arguments);
    void SetInvalidCommandLineReasonIfArgumentsContainBannedArgument(const std::vector<std::string>& arguments);
    void SetInvalidCommandLineReasonIfSgfcFailsToParseArguments(const std::vector<std::string>& arguments);
    std::vector<std::string> ConvertArgumentsToArgvStyle(const std::vector<std::string>& arguments) const;
    void InitializeArgv(const char** argv, const std::vector<std::string>& argvArguments) const;
    void InvokeSgfcParseArgs(int argc, const char** argv);

    void ResetGlobalVariables();

    std::vector<std::shared_ptr<ISgfcMessage>> GetMessageStreamResult() const;

    void SetInvalidCommandLineReasonFromParseArgsResults(
      const std::vector<std::shared_ptr<ISgfcMessage>>& parseArgsResult);

    void ThrowIfIsCommandLineValidReturnsTrue() const;
    void ThrowIfIsCommandLineValidReturnsFalse() const;
  };
}
