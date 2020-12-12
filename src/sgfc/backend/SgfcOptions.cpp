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

    if (this->options->default_encoding != nullptr)
      this->defaultEncoding = std::string(this->options->default_encoding);
    if (this->options->forced_encoding != nullptr)
      this->forcedEncoding = std::string(this->options->forced_encoding);
  }

  SgfcOptions::~SgfcOptions()
  {
    free(this->options);
  }

  void SgfcOptions::CaptureOptions(const SGFCOptions* sourceOptions)
  {
    CopyOptions(sourceOptions, this->options);

    if (sourceOptions->default_encoding == nullptr)
    {
      // This should not happen in practice - SGFCDefaultOptions always sets
      // up a default encoding. It may happen in a unit test context.
      this->defaultEncoding.clear();
    }
    else
    {
      // The source is either a string literal set up in SGFCDefaultOptions,
      // or a pointer into an argv element buffer.
      this->defaultEncoding = std::string(sourceOptions->default_encoding);
    }

    if (sourceOptions->forced_encoding == nullptr)
    {
      // This can happen in reality if --encoding was not specified - in this
      // case th value set up by SGFCDefaultOptions is used, which is NULL.
      this->forcedEncoding.clear();
    }
    else
    {
      // The source is a pointer into an argv element buffer.
      this->forcedEncoding = std::string(sourceOptions->forced_encoding);
    }
  }

  void SgfcOptions::RestoreOptions(SGFCOptions* targetOptions) const
  {
    CopyOptions(this->options, targetOptions);

    // The pointers we assign here are valid only for a limited time. This is
    // documented in the public API.
    if (this->defaultEncoding.length() > 1)
      targetOptions->default_encoding = this->defaultEncoding.c_str();
    else
      targetOptions->default_encoding = nullptr;
    if (this->forcedEncoding.length() > 1)
      targetOptions->forced_encoding = this->forcedEncoding.c_str();
    else
      targetOptions->forced_encoding = nullptr;
  }

  void SgfcOptions::CopyOptions(const SGFCOptions* sourceOptions, SGFCOptions* targetOptions) const
  {
    // We don't copy SGFCOptions::infile and SGFCOptions::outfile. These are
    // set up separately by other parts of libsgfc++.

    // We don't copy SGFCOptions::forced_encoding and
    // SGFCOptions::default_encoding. These are handled by the caller.

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
