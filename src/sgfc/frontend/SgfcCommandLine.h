#pragma once

// Project includes
#include "../../../include/ISgfcCommandLine.h"
#include "../backend/SgfcBackendController.h"

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
    std::shared_ptr<SgfcBackendController> backendController;
    std::shared_ptr<SgfcBackendLoadResult> backendLoadResult;
    std::shared_ptr<SgfcBackendSaveResult> backendSaveResult;

    void ThrowIfIsCommandLineValidReturnsFalse() const;
    void ThrowIfIsSgfContentValidReturnsFalse() const;

    bool DeleteTempFileOrCreateAndSetBackendSaveResultWithErrorMessage(
      const std::string& tempFilePath);

    SgfcExitCode CreateAndSetBackendLoadResultWithErrorMessage(
      int messageID,
      const std::string& messageText);
    SgfcExitCode CreateAndSetBackendSaveResultWithErrorMessage(
      int messageID,
      const std::string& messageText);
  };
}
