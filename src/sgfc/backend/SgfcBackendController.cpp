// Project includes
#include "../../SgfcConstants.h"
#include "../message/SgfcMessage.h"
#include "../message/SgfcMessageParser.h"
#include "../message/SgfcMessageStream.h"
#include "SgfcBackendController.h"

// SGFC includes
extern "C"
{
  #include "../../../sgfc/all.h"
  #include "../../../sgfc/protos.h"
}

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcBackendController::SgfcBackendController()
    : invalidCommandLineReason(nullptr)
  {
    // TODO: Add multi-threading protection.

    ParseArguments(this->arguments);
  }

  SgfcBackendController::SgfcBackendController(const std::vector<std::string>& arguments)
    : arguments(arguments)
    , invalidCommandLineReason(nullptr)
  {
    // TODO: Add multi-threading protection.

    ParseArguments(arguments);
  }

  SgfcBackendController::~SgfcBackendController()
  {
  }

  std::vector<std::string> SgfcBackendController::GetArguments() const
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
    ThrowIfIsCommandLineValidReturnsFalse();

    // TODO: Add multi-threading protection.

    // Reset global variables, then re-apply the outcome of ParseArgs() so that
    // SGFC behaves the same on each invocation.
    ResetGlobalVariables();
    this->sgfcOptions.RestoreOptions();

    // It is safe to keep the pointer to the internal string buffer as long
    // as the string remains in scope and we don't change the string content.
    // It is safe to remove const'ness because we know that LoadSGF() and
    // ParseSGF() won't change the char buffer.
    option_infile = const_cast<char*>(sgfFilePath.c_str());

    std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper =
      std::shared_ptr<SgfcBackendDataWrapper>(new SgfcBackendDataWrapper());

    // Prepare the SGFInfo struct for LoadSGF()
    sgfDataWrapper->GetSgfData()->name = option_infile;

    try
    {
      // Both of the following functions set the global variable sgfc as a
      // side effect
      LoadSGF(sgfDataWrapper->GetSgfData());
      ParseSGF(sgfDataWrapper->GetSgfData());
    }
    catch (std::runtime_error& exception)
    {
      // Handle the exception. The SGFC message stream should now hold a
      // fatal error message that we get access to after FillParseResult().
    }

    std::vector<std::shared_ptr<ISgfcMessage>> parseSgfResult = GetMessageStreamResult();

    sgfDataWrapper->SetDataState(SgfcBackendDataState::FullyLoaded);

    std::shared_ptr<SgfcBackendLoadResult> backendLoadResult =
      std::shared_ptr<SgfcBackendLoadResult>(new SgfcBackendLoadResult(parseSgfResult, sgfDataWrapper));
    return backendLoadResult;
  }

  std::shared_ptr<SgfcBackendSaveResult> SgfcBackendController::SaveSgfFile(
    const std::string& sgfFilePath,
    std::shared_ptr<SgfcBackendDataWrapper> sgfDataWrapper)
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    // TODO: Add multi-threading protection.

    // Reset global variables, then re-apply the outcome of ParseArgs() so that
    // SGFC behaves the same on each invocation.
    ResetGlobalVariables();
    this->sgfcOptions.RestoreOptions();

    bool parseSgfWasSuccessful = true;

    if (sgfDataWrapper->GetDataState() == SgfcBackendDataState::PartiallyLoaded)
    {
      try
      {
        // Both of the following functions set the global variable sgfc as a
        // side effect
        LoadSGFFromFileBuffer(sgfDataWrapper->GetSgfData());
        ParseSGF(sgfDataWrapper->GetSgfData());
      }
      catch (std::runtime_error& exception)
      {
        // Handle the exception. The SGFC message stream should now hold a
        // fatal error message that we get access to after
        // GetMessageStreamResult().
        parseSgfWasSuccessful = false;
      }

      sgfDataWrapper->SetDataState(SgfcBackendDataState::FullyLoaded);
    }

    // Don't attempt to save if parsing was not successful
    // TODO: Currently we only skip saving if a fatal error occurred. Shouldn't
    // we skip saving also for critical errors?
    if (parseSgfWasSuccessful)
    {
      // It is safe to keep the pointer to the internal string buffer as long
      // as the string remains in scope and we don't change the string content.
      // It is safe to remove const'ness because we know that SaveSGF() won't
      // change the char buffer.
      option_outfile = const_cast<char*>(sgfFilePath.c_str());

      // Prepare the SGFInfo struct for SaveSGF()
      sgfDataWrapper->GetSgfData()->name = option_outfile;

      try
      {
        // The following function sets the global variable sgfc as a side effect
        SaveSGF(sgfDataWrapper->GetSgfData());
      }
      catch (std::runtime_error& exception)
      {
        // Handle the exception. The SGFC message stream should now hold a
        // fatal error message that we get access to after
        // GetMessageStreamResult().
      }
    }

    std::vector<std::shared_ptr<ISgfcMessage>> saveSgfResult = GetMessageStreamResult();

    std::shared_ptr<SgfcBackendSaveResult> backendSaveResult =
      std::shared_ptr<SgfcBackendSaveResult>(new SgfcBackendSaveResult(saveSgfResult));
    return backendSaveResult;
  }

  void SgfcBackendController::ParseArguments(const std::vector<std::string>& arguments)
  {
    ResetGlobalVariables();

    SetInvalidCommandLineReasonIfArgumentsContainBannedArgument(arguments);
    if (! this->IsCommandLineValid())
      return;

    SetInvalidCommandLineReasonIfSgfcFailsToParseArguments(arguments);
    if (! this->IsCommandLineValid())
      return;

    // Capture the changed SGFC option values so that we can re-apply them
    // later on when we perform a load or save operation. There's no need for
    // doing that if the command line arguments are not valid, because in that
    // case a client is not allowed to perform load or save operations.
    this->sgfcOptions.CaptureOptions();
  }

  void SgfcBackendController::SetInvalidCommandLineReasonIfArgumentsContainBannedArgument(const std::vector<std::string>& arguments)
  {
    std::vector<std::string> bannedArguments =
    {
      // We don't want these arguments because they would cause ParseArgs() to
      // output something on stdout
      SgfcConstants::ShortHelpOption,
      SgfcConstants::LongHelpOption,
      SgfcConstants::VersionOption,
      // Interactive use in a library doesn't make sense
      SgfcConstants::InteractiveModeOption,
      // The library client decides whether it wants to write the SGF content
      SgfcConstants::WriteFileEvenIfCriticalErrorOccurs,
      // SGFC needs to be patched so that it does not print game signatures to
      // stdout but instead lets libsgfc++ capture the output.
      SgfcConstants::PrintGameSignature,
    };

    for (const auto& argument : arguments)
    {
      if (argument.substr(0, SgfcConstants::ShortOptionPrefix.length()) != SgfcConstants::ShortOptionPrefix)
      {
        std::string message = "Not an option, argument not allowed by " + SgfcConstants::LibraryName + ": " + argument;

        this->invalidCommandLineReason = SgfcMessage::CreateFatalErrorMessage(
          SgfcConstants::BannedArgumentMessageID,
          message);
      }

      if (std::find(bannedArguments.begin(), bannedArguments.end(), argument) != bannedArguments.end())
      {
        std::string message = "Argument not allowed by " + SgfcConstants::LibraryName + ": " + argument;

        this->invalidCommandLineReason = SgfcMessage::CreateFatalErrorMessage(
          SgfcConstants::BannedArgumentMessageID,
          message);
      }
    }
  }

  void SgfcBackendController::SetInvalidCommandLineReasonIfSgfcFailsToParseArguments(const std::vector<std::string>& arguments)
  {
    std::vector<std::string> argvArguments = ConvertArgumentsToArgvStyle(arguments);

    int argc = static_cast<int>(argvArguments.size());
    const char* argv[argc];
    InitializeArgv(argv, argvArguments);

    InvokeSgfcParseArgs(argc, argv);
  }

  std::vector<std::string> SgfcBackendController::ConvertArgumentsToArgvStyle(const std::vector<std::string>& arguments) const
  {
    std::vector<std::string> argvArguments =
    {
      // argv[0] in a main() function is the program name
      SgfcConstants::LibraryName,
    };

    argvArguments.insert(argvArguments.end(), arguments.begin(), arguments.end());

    return argvArguments;
  }

  void SgfcBackendController::InitializeArgv(const char** argv, const std::vector<std::string>& argvArguments) const
  {
    for (int indexOfArgument = 0; indexOfArgument < argvArguments.size(); indexOfArgument++)
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
    if (argc == 1)
    {
      // Don't call ParseArgs() if there are no arguments, because that causes
      // ParseArgs() to print a usage line to stdout.
    }
    else
    {
      try
      {
        // It is safe to remove const'ness because we know that ParseArgs()
        // won't change any of the char buffers.
        ParseArgs(argc, const_cast<char**>(argv));

        // In theory ParseArgs() can return TRUE or FALSE. Practically we
        // removed all possibilities for it to return FALSE, so we don't have
        // to check the return value. ParseArgs() returns FALSE in two cases:
        // - If no argument is specified. We excluded this with the initial
        //   argc == 1 check.
        // - If an argument is specified that requires SGFC to exit without
        //   error. These are -h, --help and --version. These are all in the
        //   list of banned arguments.
      }
      catch (std::runtime_error& exception)
      {
        std::vector<std::shared_ptr<ISgfcMessage>> parseArgsResult = GetMessageStreamResult();
        SetInvalidCommandLineReasonFromParseArgsResults(parseArgsResult);
      }
    }
  }

  void SgfcBackendController::ResetGlobalVariables()
  {
    ResetGlobalVariablesInMain();
    ResetGlobalVariablesInSave();
    ResetGlobalVariablesInProperties();
    ResetGlobalVariablesInParse2();
    ResetGlobalVariablesInExecute();
    ResetGlobalVariablesInUtil();
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcBackendController::GetMessageStreamResult() const
  {
    std::vector<std::shared_ptr<ISgfcMessage>> result;

    SgfcMessageStream messageStream;
    std::vector<std::string> messageStreamLines = messageStream.GetMessageStreamLines();

    for (const auto& messageStreamLine : messageStreamLines)
    {
      std::shared_ptr<ISgfcMessage> message = SgfcMessageParser::CreateSgfcMessage(messageStreamLine);
      result.push_back(message);
    }

    return result;
  }

  void SgfcBackendController::SetInvalidCommandLineReasonFromParseArgsResults(
    const std::vector<std::shared_ptr<ISgfcMessage>>& parseArgsResult)
  {
    for (const auto& message : parseArgsResult)
    {
      if (message->GetMessageType() == SgfcMessageType::FatalError)
      {
        this->invalidCommandLineReason = message;
        return;
      }
    }

    // This should not happen. If it does there was an error parsing the
    // message text.
    this->invalidCommandLineReason = SgfcMessage::CreateFatalErrorMessage(
      SgfcConstants::ParseArgumentErrorMessageID,
      "SGFC failed to parse the specified arguments");
  }

  void SgfcBackendController::ThrowIfIsCommandLineValidReturnsTrue() const
  {
    if (this->IsCommandLineValid())
      throw std::runtime_error("Interface protocol violation: IsCommandLineValid() returns true");
  }

  void SgfcBackendController::ThrowIfIsCommandLineValidReturnsFalse() const
  {
    if (! this->IsCommandLineValid())
      throw std::runtime_error("Interface protocol violation: IsCommandLineValid() returns false");
  }
}
