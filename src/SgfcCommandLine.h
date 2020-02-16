#pragma once

// Project includes
#include "../include/ISgfcCommandLine.h"
#include "SgfcOptions.h"

// Forward declarations
struct SGFInfo;

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcCommandLine class provides an implementation of the
  /// ISgfcCommandLine interface. See the interface header file for
  /// documentation.
  class SgfcCommandLine : public ISgfcCommandLine
  {
  public:
    /// @brief Initializes a newly constructed SgfcCommandLine object.
    ///
    /// See SgfcPlusPlusFactory::CreateSgfcCommandLine() for a documentation
    /// of the contract that this constructor must fulfill (e.g. exceptions).
    SgfcCommandLine(const std::vector<std::string>& arguments);

    /// @brief Destroys and cleans up the SgfcCommandLine object.
    virtual ~SgfcCommandLine();

    virtual std::vector<std::string> GetArguments() const;
    virtual bool IsCommandLineValid() const;
    virtual std::shared_ptr<ISgfcMessage> GetInvalidCommandLineReason() const;

    virtual SgfcExitCode LoadSgfFile(const std::string& sgfFilePath);
    virtual SgfcExitCode LoadSgfContent(const std::string& sgfContent);

    virtual bool IsSgfContentValid() const;
    virtual std::vector<std::shared_ptr<ISgfcMessage>> GetParseResult() const;

    virtual SgfcExitCode SaveSgfFile(const std::string& sgfFilePath);
    virtual SgfcExitCode SaveSgfContent(std::string& sgfContent);

    virtual std::vector<std::shared_ptr<ISgfcMessage>> GetSaveResult() const;

  private:
    std::vector<std::string> arguments;
    std::shared_ptr<ISgfcMessage> invalidCommandLineReason;
    SgfcOptions sgfcOptions;
    SGFInfo* sgfInfo;
    std::vector<std::shared_ptr<ISgfcMessage>> parseResult;
    std::vector<std::shared_ptr<ISgfcMessage>> saveResult;

    void ParseArguments(const std::vector<std::string>& arguments);
    void SetInvalidCommandLineReasonIfArgumentsContainBannedArgument(const std::vector<std::string>& arguments);
    void SetInvalidCommandLineReasonIfSgfcFailsToParseArguments(const std::vector<std::string>& arguments);
    std::vector<std::string> ConvertArgumentsToArgvStyle(const std::vector<std::string>& arguments) const;
    void InitializeArgv(const char** argv, const std::vector<std::string>& argvArguments) const;
    void InvokeSgfcParseArgs(int argc, const char** argv);

    void AllocateSgfInfo();
    void DeallocateSgfInfo();
    void ReallocateSgfInfo();

    void FillParseResult();
    void FillSaveResult();
    std::vector<std::shared_ptr<ISgfcMessage>> GetMessageStreamResult() const;

    void SetInvalidCommandLineReasonFromParseResults();
    SgfcExitCode GetSgfcExitCodeFromMessageCollection(const std::vector<std::shared_ptr<ISgfcMessage>>& messageCollection);

    void ThrowIfIsCommandLineValidReturnsTrue() const;
    void ThrowIfIsCommandLineValidReturnsFalse() const;
    void ThrowIfIsSgfContentValidReturnsFalse() const;
  };
}
