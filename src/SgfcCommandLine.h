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
  
    virtual SgfcExitCode LoadSgfFile(const std::string& sgfFilePath);
    virtual SgfcExitCode LoadSgfContent(const std::string& sgfContent);
  
    virtual std::vector<std::shared_ptr<ISgfcMessage>> GetParseResult() const;
  
    virtual void SaveSgfFile(const std::string& fileName) const;
    virtual void SaveSgfContent(std::string& sgfContent) const;

  private:
    SgfcOptions sgfcOptions;
    SGFInfo* sgfInfo;
    std::vector<std::shared_ptr<ISgfcMessage>> parseResult;

    void ParseArguments(const std::vector<std::string>& arguments);
    void ThrowIfArgumentsContainBannedArgument(const std::vector<std::string>& arguments) const;
    std::vector<std::string> ConvertArgumentsToArgvStyle(const std::vector<std::string>& arguments) const;
    void InitializeArgv(const char** argv, const std::vector<std::string>& argvArguments) const;
    void InvokeSgfcParseArgsOrThrow(int argc, const char** argv);

    void AllocateSgfInfo();
    void DeallocateSgfInfo();
    void ReallocateSgfInfo();

    void FillParseResult();

    SgfcExitCode GetSgfcExitCodeFromGlobalVariables();
  };
}
