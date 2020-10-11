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

// C++ Standard Library includes
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcOptions class is used to capture a snapshot of the option
  /// values that SGFC sets up when it parses its command line arguments, and
  /// to reconfigure SGFC with those captured values at a later time.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-arguments
  /// @ingroup sgfc-backend
  ///
  /// Calling the RestoreOptions() method of a newly constructed SgfcOptions
  /// object (i.e. before its CaptureOptions() method is called for the first
  /// time) can be used to reconfigure SGFC with its default option values,
  /// as if the command line utility had just started up. This should be used
  /// every time just before SGFC is instructed to parse command line arguments.
  class SgfcOptions
  {
  public:
    /// @brief Initializes a newly constructed SgfcOptions object. The object
    /// holds default option values.
    SgfcOptions();

    /// @brief Destroys and cleans up the SgfcOptions object.
    virtual ~SgfcOptions();

    /// @brief Captures a snapshot of the option values that SGFC is currently
    /// configured with.
    void CaptureOptions();

    /// @brief Reconfigures SGFC with the option values that the SgfcOption
    /// object currently holds.
    void RestoreOptions() const;

  private:
    char option_warnings;
    char option_keep_head;
    char option_keep_unknown_props;
    char option_keep_obsolete_props;
    char option_del_empty_nodes;
    char option_del_move_markup;
    char option_split_file;
    char option_write_critical;
    char option_interactive;
    char option_linebreaks;
    char option_softlinebreaks;
    char option_nodelinebreaks;
    char option_expandcpl;
    char option_pass_tt;
    char option_fix_variation;
    char option_findstart;
    char option_game_signature;
    char option_strict_checking;
    char option_reorder_variations;
    std::vector<bool> error_enabled;
    std::vector<bool> delete_property;

    static int GetErrorCount();
    static int GetPropertyCount();
  };
}
