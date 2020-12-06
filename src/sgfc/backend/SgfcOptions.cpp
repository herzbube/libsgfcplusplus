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

// Project includes
#include "SgfcOptions.h"

// SGFC includes
extern "C"
{
  #include "../../../sgfc/src/all.h"
  #include "../../../sgfc/src/protos.h"
}

// System includes
#include <cstdlib>  // for free()

namespace LibSgfcPlusPlus
{
  SgfcOptions::SgfcOptions()
    : options(NULL)
  {
    // Throws std::runtime_error if SGFC fails to allocate memory
    this->options = SGFCDefaultOptions();
  }

  SgfcOptions::~SgfcOptions()
  {
    free(this->options);
  }

  void SgfcOptions::CaptureOptions(const SGFCOptions* sourceOptions)
  {
    CopyOptions(sourceOptions, this->options);
  }

  void SgfcOptions::RestoreOptions(SGFCOptions* targetOptions) const
  {
    CopyOptions(this->options, targetOptions);
  }

  void SgfcOptions::CopyOptions(const SGFCOptions* sourceOptions, SGFCOptions* targetOptions) const
  {
    // We don't copy SGFCOptions::infile and SGFCOptions::outfile. These are
    // set up separately by other parts of libsgfc++.

    // We don't copy SGFCOptions::forced_encoding and
    // SGFCOptions::default_encoding. These are never used by libsgfc++.

    targetOptions->linebreaks = sourceOptions->linebreaks;
    targetOptions->find_start = sourceOptions->find_start;
    targetOptions->encoding = sourceOptions->encoding;
    targetOptions->help = sourceOptions->help;
    targetOptions->warnings = sourceOptions->warnings;
    targetOptions->keep_head = sourceOptions->keep_head;
    targetOptions->keep_unknown_props = sourceOptions->keep_unknown_props;
    targetOptions->keep_obsolete_props = sourceOptions->keep_obsolete_props;
    targetOptions->del_empty_nodes = sourceOptions->del_empty_nodes;
    targetOptions->del_move_markup = sourceOptions->del_move_markup;
    targetOptions->split_file = sourceOptions->split_file;
    targetOptions->write_critical = sourceOptions->write_critical;
    targetOptions->interactive = sourceOptions->interactive;
    targetOptions->soft_linebreaks = sourceOptions->soft_linebreaks;
    targetOptions->node_linebreaks = sourceOptions->node_linebreaks;
    targetOptions->expand_cpl = sourceOptions->expand_cpl;
    targetOptions->pass_tt = sourceOptions->pass_tt;
    targetOptions->fix_variation = sourceOptions->fix_variation;
    targetOptions->game_signature = sourceOptions->game_signature;
    targetOptions->strict_checking = sourceOptions->strict_checking;
    targetOptions->reorder_variations = sourceOptions->reorder_variations;
    targetOptions->add_sgfc_ap_property = sourceOptions->add_sgfc_ap_property;

    for (int indexOfError = 0; indexOfError < MAX_ERROR_NUM; indexOfError++)
      targetOptions->error_enabled[indexOfError] = sourceOptions->error_enabled[indexOfError];

    for (int indexOfProperty = 0; indexOfProperty < NUM_SGF_TOKENS; indexOfProperty++)
      targetOptions->delete_property[indexOfProperty] = sourceOptions->delete_property[indexOfProperty];
  }
}
