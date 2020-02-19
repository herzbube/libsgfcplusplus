// Project includes
#include "SgfcCommandLine.h"
#include "SgfcConstants.h"
#include "SgfcMessage.h"
#include "SgfcMessageParser.h"
#include "SgfcMessageStream.h"

// SGFC includes
extern "C"
{
  #include "../sgfc/all.h"
  #include "../sgfc/protos.h"
}

// C++ Standard Library includes
#include <algorithm>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcCommandLine::SgfcCommandLine(const std::vector<std::string>& arguments)
    : arguments(arguments)
    , invalidCommandLineReason(nullptr)
    , sgfInfo(0)
  {
    // TODO: Add multi-threading protection.

    // Parse the supplied arguments, thus changing the SGFC option values
    ParseArguments(arguments);
  }

  SgfcCommandLine::~SgfcCommandLine()
  {
    if (this->sgfInfo)
      DeallocateSgfInfo();
  }

  std::vector<std::string> SgfcCommandLine::GetArguments() const
  {
    return this->arguments;
  }

  bool SgfcCommandLine::IsCommandLineValid() const
  {
    if (this->invalidCommandLineReason == nullptr)
      return true;
    else
      return false;
  }

  std::shared_ptr<ISgfcMessage> SgfcCommandLine::GetInvalidCommandLineReason() const
  {
    ThrowIfIsCommandLineValidReturnsTrue();

    return this->invalidCommandLineReason;
  }

  SgfcExitCode SgfcCommandLine::LoadSgfFile(const std::string& sgfFilePath)
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

    // Free any memory from a previous run, then start with a new struct
    ReallocateSgfInfo();

    // Prepare the SGFInfo struct for LoadSGF()
    this->sgfInfo->name = option_infile;

    try
    {
      // Both of the following functions set the global variable sgfc as a
      // side effect
      LoadSGF(this->sgfInfo);
      ParseSGF(this->sgfInfo);
    }
    catch (std::runtime_error& exception)
    {
      // Handle the exception. The SGFC message stream should now hold a
      // fatal error message that we get access to after FillParseResult().
    }

    // Reset global variable. This makes sure that our data in this->sgfInfo
    // remains untouched when other SGFC controllers perform SGFC operations.
    sgfc = nullptr;

    FillParseResult();

    SgfcExitCode sgfcExitCode = GetSgfcExitCodeFromMessageCollection(this->parseResult);
    return sgfcExitCode;
  }

  SgfcExitCode SgfcCommandLine::LoadSgfContent(const std::string& sgfContent)
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    throw std::runtime_error("not yet implemented");
  }

  bool SgfcCommandLine::IsSgfContentValid() const
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    for (const auto& message : this->parseResult)
    {
      if (message->GetMessageType() == SgfcMessageType::FatalError)
        return false;
    }

    return true;
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcCommandLine::GetParseResult() const
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    return this->parseResult;
  }

  SgfcExitCode SgfcCommandLine::SaveSgfFile(const std::string& sgfFilePath)
  {
    ThrowIfIsSgfContentValidReturnsFalse();

    // TODO: Add multi-threading protection.

    // Reset global variables, then re-apply the outcome of ParseArgs() so that
    // SGFC behaves the same on each invocation.
    ResetGlobalVariables();
    this->sgfcOptions.RestoreOptions();

    // It is safe to keep the pointer to the internal string buffer as long
    // as the string remains in scope and we don't change the string content.
    // It is safe to remove const'ness because we know that SaveSGF() won't
    // change the char buffer.
    option_outfile = const_cast<char*>(sgfFilePath.c_str());

    // Prepare the SGFInfo struct for LoadSGF()
    this->sgfInfo->name = option_outfile;

    try
    {
      // The following function sets the global variable sgfc as a side effect
      SaveSGF(this->sgfInfo);
    }
    catch (std::runtime_error& exception)
    {
      // Handle the exception. The SGFC message stream should now hold a
      // fatal error message that we get access to after FillParseResult().
    }

    // Reset global variable. This makes sure that our data in this->sgfInfo
    // remains untouched when other SGFC controllers perform SGFC operations.
    sgfc = nullptr;

    FillSaveResult();

    SgfcExitCode sgfcExitCode = GetSgfcExitCodeFromMessageCollection(this->saveResult);
    return sgfcExitCode;
  }

  SgfcExitCode SgfcCommandLine::SaveSgfContent(std::string& sgfContent)
  {
    ThrowIfIsSgfContentValidReturnsFalse();

    throw std::runtime_error("not yet implemented");
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcCommandLine::GetSaveResult() const
  {
    ThrowIfIsCommandLineValidReturnsFalse();

    return this->saveResult;
  }

  void SgfcCommandLine::ParseArguments(const std::vector<std::string>& arguments)
  {
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

  void SgfcCommandLine::SetInvalidCommandLineReasonIfArgumentsContainBannedArgument(const std::vector<std::string>& arguments)
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

  void SgfcCommandLine::SetInvalidCommandLineReasonIfSgfcFailsToParseArguments(const std::vector<std::string>& arguments)
  {
    std::vector<std::string> argvArguments = ConvertArgumentsToArgvStyle(arguments);

    int argc = static_cast<int>(argvArguments.size());
    const char* argv[argc];
    InitializeArgv(argv, argvArguments);

    InvokeSgfcParseArgs(argc, argv);
  }

  std::vector<std::string> SgfcCommandLine::ConvertArgumentsToArgvStyle(const std::vector<std::string>& arguments) const
  {
    std::vector<std::string> argvArguments =
    {
      // argv[0] in a main() function is the program name
      SgfcConstants::LibraryName,
    };

    argvArguments.insert(argvArguments.end(), arguments.begin(), arguments.end());

    return argvArguments;
  }

  void SgfcCommandLine::InitializeArgv(const char** argv, const std::vector<std::string>& argvArguments) const
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

  void SgfcCommandLine::InvokeSgfcParseArgs(int argc, const char** argv)
  {
    // Set SGFC options to their default values as if the command line utility
    // had just started up. This works because we know that at this point the
    // SgfcOptions object still has its default values that it set up during
    // construction.
    this->sgfcOptions.RestoreOptions();

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
        FillParseResult();
        SetInvalidCommandLineReasonFromParseResults();
        parseResult.clear();
      }
    }
  }

  void SgfcCommandLine::ResetGlobalVariables()
  {
    ResetGlobalVariablesInMain();
    ResetGlobalVariablesInSave();
    ResetGlobalVariablesInProperties();
    ResetGlobalVariablesInParse2();
    ResetGlobalVariablesInExecute();
    ResetGlobalVariablesInUtil();
  }

  void SgfcCommandLine::AllocateSgfInfo()
  {
    this->sgfInfo = new SGFInfo();

    // Immediately zero the struct so that FreeSGFInfo() inside
    // DeallocateSgfInfo() works. This is important if the destructor runs
    // immediately after the constructor, without SGF content
    memset(this->sgfInfo, 0, sizeof(struct SGFInfo));
  }

  void SgfcCommandLine::DeallocateSgfInfo()
  {
    FreeSGFInfo(this->sgfInfo);
    delete this->sgfInfo;
    this->sgfInfo = 0;
  }

  void SgfcCommandLine::ReallocateSgfInfo()
  {
    if (this->sgfInfo)
      DeallocateSgfInfo();

    AllocateSgfInfo();
  }

  void SgfcCommandLine::FillParseResult()
  {
    this->parseResult = GetMessageStreamResult();
  }

  void SgfcCommandLine::FillSaveResult()
  {
    this->saveResult = GetMessageStreamResult();
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcCommandLine::GetMessageStreamResult() const
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

  void SgfcCommandLine::SetInvalidCommandLineReasonFromParseResults()
  {
    for (const auto& message : this->parseResult)
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

  SgfcExitCode SgfcCommandLine::GetSgfcExitCodeFromMessageCollection(const std::vector<std::shared_ptr<ISgfcMessage>>& messageCollection)
  {
    bool warningMessageFound = false;
    bool errorMessageFound = false;
    bool fatalErrorMessageFound = false;

    for (const auto& message : messageCollection)
    {
      switch (message->GetMessageType())
      {
        case SgfcMessageType::Warning:
          warningMessageFound = true;
          break;
        case SgfcMessageType::Error:
          errorMessageFound = true;
          break;
        case SgfcMessageType::FatalError:
          fatalErrorMessageFound = true;
          break;
      }
    }

    if (fatalErrorMessageFound)
      return SgfcExitCode::FatalError;
    if (errorMessageFound)
      return SgfcExitCode::Error;
    else if (warningMessageFound)
      return SgfcExitCode::Warning;
    else
      return SgfcExitCode::Ok;
  }

  void SgfcCommandLine::ThrowIfIsCommandLineValidReturnsTrue() const
  {
    if (this->IsCommandLineValid())
      throw std::runtime_error("Interface protocol violation: IsCommandLineValid() returns true");
  }

  void SgfcCommandLine::ThrowIfIsCommandLineValidReturnsFalse() const
  {
    if (! this->IsCommandLineValid())
      throw std::runtime_error("Interface protocol violation: IsCommandLineValid() returns false");
  }

  void SgfcCommandLine::ThrowIfIsSgfContentValidReturnsFalse() const
  {
    if (! this->IsSgfContentValid())
      throw std::runtime_error("Interface protocol violation: IsSgfContentValid() returns false");
  }
}
