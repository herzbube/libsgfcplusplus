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
#include "ISgfcMessage.h"
#include "SgfcExitCode.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcArgument;

  /// @brief The ISgfcCommandLine interface is used to operate the SGFC backend
  /// in command line mode. Use SgfcPlusPlusFactory to construct new
  /// ISgfcCommandLine objects.
  ///
  /// @ingroup public-api
  /// @ingroup sgfc-frontend
  ///
  /// The ISgfcCommandLine interface is designed to give clients control over
  /// when they want to execute load and save operations, and how they want the
  /// operations to behave. Clients specify SGFC command line arguments when
  /// they construct the ISgfcCommandLine object. The SGFC command line
  /// arguments cannot be changed after construction.
  ///
  /// A client typically uses the ISgfcCommandLine interface by following this
  /// sequence, which corresponds to invoking SGFC on the command line with an
  /// input file path and an output file path.
  /// - Use SgfcPlusPlusFactory to construct the object.
  /// - Verify that SGFC command line arguments are valid.
  /// - If SGFC command line arguments are valid: Load SGF content.
  /// - Access parse results.
  /// - If SGF content is valid: Save SGF content.
  ///
  /// A client may deviate from this sequence e.g. by repeatedly loading SGF
  /// content without saving (syntax checking), or by repeatedly saving the
  /// same SGF content to different locations.
  ///
  /// A client that deviates from the sequence must still follow a certain
  /// common-sense protocol in using the interface:
  /// - It may not load SGF content if the SGFC command line arguments are not
  ///   valid. Use IsCommandLineValid() to check this.
  /// - It may not save SGF content that was found to be invalid during loading,
  ///   or save SGF content without prior loading any content. Use
  ///   IsSgfContentValid() to check this.
  class SGFCPLUSPLUS_EXPORT ISgfcCommandLine
  {
  public:
    /// @brief Initializes a newly constructed ISgfcCommandLine object.
    ISgfcCommandLine();

    /// @brief Destroys and cleans up the ISgfcCommandLine object.
    virtual ~ISgfcCommandLine();

    /// @brief Returns the SGFC command line arguments that were used to
    /// construct the ISgfcCommandLine object.
    virtual std::vector<std::shared_ptr<ISgfcArgument>> GetArguments() const = 0;

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
    virtual bool IsCommandLineValid() const = 0;

    /// @brief Returns an ISgfcMessage object with message type
    /// #SgfcMessageType::FatalError that describes why the SGFC command
    /// line arguments that GetArguments() returns are not valid. This method
    /// may only be invoked if IsCommandLineValid() returns false.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// true.
    virtual std::shared_ptr<ISgfcMessage> GetInvalidCommandLineReason() const = 0;

    /// @brief Loads a single .sgf file from the specified path and puts it
    /// through the SGFC parser. This method may only be invoked if
    /// IsCommandLineValid() returns true.
    ///
    /// @return An SgfcExitCode value whose numeric value matches one of the
    /// exit codes of SGFC.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    virtual SgfcExitCode LoadSgfFile(const std::string& sgfFilePath) = 0;

    /// @brief Loads the specified SGF content and puts it through the SGFC
    /// parser. This method may only be invoked if IsCommandLineValid() returns
    /// true.
    ///
    /// @return An SgfcExitCode value whose numeric value matches one of the
    /// exit codes of SGFC.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    virtual SgfcExitCode LoadSgfContent(const std::string& sgfContent) = 0;

    /// @brief Returns true if the SGF content that was loaded and parsed by the
    /// most recent invocation of either LoadSgfFile() or LoadSgfContent() is
    /// valid. Returns false if the SGF content is not valid, or if none of the
    /// methods have been invoked yet.
    ///
    /// The SGF content is considered valid if LoadSgfFile() or LoadSgfContent()
    /// have been invoked at least once, and if their invocation did not
    /// generate a fatal error. A fatal error shows up in the collection of
    /// ISgfcMessage objects that GetParseResult() returns, as an ISgfcMessage
    /// object with message type #SgfcMessageType::FatalError.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    virtual bool IsSgfContentValid() const = 0;

    /// @brief Returns a collection of ISgfcMessage objects which together form
    /// the parse result from the most recent invocation of either LoadSgfFile()
    /// or LoadSgfContent().
    ///
    /// The collection is empty if none of the methods have been invoked yet, or
    /// if the most recent load operation did not generate any messages.
    ///
    /// If the collection is not empty, the messages appear in the order in
    /// which they were generated by SGFC.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    virtual std::vector<std::shared_ptr<ISgfcMessage>> GetParseResult() const = 0;

    /// @brief Saves the SGF content generated by SGFC after the most recent
    /// invocation of either LoadSgfFile() or LoadSgfContent() to the .sgf
    /// file at the specified path. This method may only be invoked if
    /// IsSgfContentValid() returns true.
    ///
    /// If a file already exists at the specified path it is overwritten.
    ///
    /// @return An SgfcExitCode value whose numeric value matches one of the
    /// exit codes of SGFC.
    ///
    /// @exception std::logic_error Is thrown if IsSgfContentValid() returns
    /// false.
    virtual SgfcExitCode SaveSgfFile(const std::string& sgfFilePath) = 0;
  
    /// @brief Saves the SGF content generated by SGFC after the most recent
    /// invocation of either LoadSgfFile() or LoadSgfContent() into the
    /// specified string object. This method may only be invoked if
    /// IsSgfContentValid() returns true.
    ///
    /// The previous content of @a sgfContent is overwritten.
    ///
    /// @return An SgfcExitCode value whose numeric value matches one of the
    /// exit codes of SGFC.
    ///
    /// @exception std::logic_error Is thrown if IsSgfContentValid() returns
    /// false.
    virtual SgfcExitCode SaveSgfContent(std::string& sgfContent) = 0;

    /// @brief Returns a collection of ISgfcMessage objects which together form
    /// the result from the most recent invocation of either SaveSgfFile()
    /// or SaveSgfContent().
    ///
    /// The collection is empty if none of the methods have been invoked yet, or
    /// if the most recent save operation did not generate any messages.
    ///
    /// If the collection is not empty, the messages appear in the order in
    /// which they were generated by SGFC.
    ///
    /// @exception std::logic_error Is thrown if IsCommandLineValid() returns
    /// false.
    virtual std::vector<std::shared_ptr<ISgfcMessage>> GetSaveResult() const = 0;
  };
}
