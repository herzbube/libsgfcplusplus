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

// Forward declarations
struct SGFCOptions;

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcOptions class is used to capture a snapshot of the option
  /// values in an SGFCOptions struct, and to reconfigure an SGFCOptions struct
  /// with those captured values at a later time.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-arguments
  /// @ingroup sgfc-backend
  ///
  /// Some notes about the internal workings of SGFC:
  /// - An SGFCOptions struct is part of the SGFInfo struct that is passed as
  ///   a parameter to all major SGFC functions, including ParseArgs(). Thus
  ///   the option values are available everywhere in SGFC.
  /// - When SGFInfo is created/initialized with SetupSGFInfo() a custom
  ///   SGFCOptions object can be passed as a parameter. SetupSGFInfo() uses
  ///   this to populate the SGFInfo object. This is the mechanism how an
  ///   SGFCOptions with arbitrary values can be injected into SGFC.
  /// - When SetupSGFInfo() receives no custom SGFCOptions object, it invokes
  ///   the SGFC global function SGFCDefaultOptions() to construct a new
  ///   SGFCOptions object with default values. SGFCDefaultOptions() can also
  ///   be invoked outside of the context of SetupSGFInfo().
  /// - When ParseArgs() is invoked it parses the command line arguments that
  ///   are specified as a parameter and populates the SGFCOptions object
  ///   inside the SGFInfo object with values that result from these parsing
  ///   activities. The purpose of the SgfcOptions class is to capture the
  ///   values in such an SGFCOptions object.
  class SgfcOptions
  {
  public:
    /// @brief Initializes a newly constructed SgfcOptions object. The object
    /// holds default option values.
    ///
    /// @exception std::runtime_error Is thrown if SGFC fails to allocate
    /// memory.
    SgfcOptions();

    /// @brief Destroys and cleans up the SgfcOptions object.
    virtual ~SgfcOptions();

    /// @brief Captures a snapshot of the option values in @a sourceOptions.
    void CaptureOptions(const SGFCOptions* sourceOptions);

    /// @brief Reconfigures @a targetOptions with the option values that the
    /// SgfcOption object currently holds.
    ///
    /// If CaptureOptions() has never been invoked before, this applies default
    /// option values to @a targetOptions.
    void RestoreOptions(SGFCOptions* targetOptions) const;

  private:
    SGFCOptions* options;

    void CopyOptions(const SGFCOptions* sourceOptions, SGFCOptions* targetOptions) const;
  };
}
