// Project includes
#include "SgfcCommandLine.h"
#include "SgfcConstants.h"
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
    : sgfInfo(0)
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

  SgfcExitCode SgfcCommandLine::LoadSgfFile(const std::string& sgfFilePath)
  {
    // TODO: Add multi-threading protection.

    // Re-apply the outcome of ParseArgs() so that SGFC behaves the same
    // on each invocation.
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

    bool fatalErrorOccurred = false;
    try
    {
      // Both of the following functions set the global variable sgfc as a
      // side effect
      LoadSGF(this->sgfInfo);
      ParseSGF(this->sgfInfo);
    }
    catch (std::runtime_error& exception)
    {
      fatalErrorOccurred = true;
    }

    // Reset global variable. This makes sure that our data in this->sgfInfo
    // remains untouched when other SGFC controllers perform SGFC operations.
    sgfc = nullptr;

    FillParseResult();

    if (fatalErrorOccurred)
    {
      return SgfcExitCode::FatalError;
    }
    else
    {
      SgfcExitCode sgfcExitCode = GetSgfcExitCodeFromGlobalVariables();
      return sgfcExitCode;
    }
  }

  SgfcExitCode SgfcCommandLine::LoadSgfContent(const std::string& sgfContent)
  {
    throw std::runtime_error("not yet implemented");
  }

  std::vector<std::shared_ptr<ISgfcMessage>> SgfcCommandLine::GetParseResult() const
  {
    return this->parseResult;
  }

  void SgfcCommandLine::SaveSgfFile(const std::string& fileName) const
  {
    // TODO Check if this is called without prior parsing of SGF content
    throw std::runtime_error("not yet implemented");
  }

  void SgfcCommandLine::SaveSgfContent(std::string& sgfContent) const
  {
    throw std::runtime_error("not yet implemented");
  }

  void SgfcCommandLine::ParseArguments(const std::vector<std::string>& arguments)
  {
    ThrowIfArgumentsContainBannedArgument(arguments);

    std::vector<std::string> argvArguments = ConvertArgumentsToArgvStyle(arguments);

    int argc = static_cast<int>(argvArguments.size());
    const char* argv[argc];
    InitializeArgv(argv, argvArguments);

    InvokeSgfcParseArgsOrThrow(argc, argv);
  }

  void SgfcCommandLine::ThrowIfArgumentsContainBannedArgument(const std::vector<std::string>& arguments) const
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
    };

    for (const auto& argument : arguments)
    {
      if (std::find(bannedArguments.begin(), bannedArguments.end(), argument) != bannedArguments.end())
      {
        std::string message = "Argument not allowed by " + SgfcConstants::LibraryName + ": " + argument;
        throw std::invalid_argument(message);
      }
    }
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

  void SgfcCommandLine::InvokeSgfcParseArgsOrThrow(int argc, const char** argv)
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
        throw std::invalid_argument(exception.what());
      }
    }

    // Capture the changed SGFC option values so that we can re-apply them
    // later on
    this->sgfcOptions.CaptureOptions();
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
    this->parseResult.clear();

    SgfcMessageStream messageStream;
    std::vector<std::string> messageStreamLines = messageStream.GetMessageStreamLines();

    for (const auto& messageStreamLine : messageStreamLines)
    {
      std::shared_ptr<ISgfcMessage> message = SgfcMessageParser::CreateSgfcMessage(messageStreamLine);
      this->parseResult.push_back(message);
    }
  }

  SgfcExitCode SgfcCommandLine::GetSgfcExitCodeFromGlobalVariables()
  {
    if (error_count > 0)
      return SgfcExitCode::Error;
    else if (warning_count > 0)
      return SgfcExitCode::Warning;
    else
      return SgfcExitCode::Ok;
  }
}
