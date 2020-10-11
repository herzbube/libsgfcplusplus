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
#include "../../../include/ISgfcCommandLine.h"
#include "../backend/SgfcBackendController.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcCommandLine class provides an implementation of the
  /// ISgfcCommandLine interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-frontend
  class SgfcCommandLine : public ISgfcCommandLine
  {
  public:
    /// @brief Initializes a newly constructed SgfcCommandLine object.
    ///
    /// See SgfcPlusPlusFactory::CreateSgfcCommandLine() for a documentation
    /// of the contract that this constructor must fulfill (e.g. exceptions).
    SgfcCommandLine(const std::vector<std::shared_ptr<ISgfcArgument>>& arguments);

    /// @brief Destroys and cleans up the SgfcCommandLine object.
    virtual ~SgfcCommandLine();

    virtual std::vector<std::shared_ptr<ISgfcArgument>> GetArguments() const;
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
  };
}
