// Project includes
#include "SgfcOptions.h"

// SGFC includes
extern "C"
{
  #include <stdio.h>  // required to define size_t and FILE which are used in all.h
  #include "../../../sgfc/all.h"
  #include "../../../sgfc/protos.h"
}

namespace LibSgfcPlusPlus
{
  SgfcOptions::SgfcOptions()
    // Values copied from main.c
    : option_warnings(TRUE)
    , option_keep_head(FALSE)
    , option_keep_unknown_props(TRUE)
    , option_keep_obsolete_props(TRUE)
    , option_del_empty_nodes(FALSE)
    , option_del_move_markup(FALSE)
    , option_split_file(FALSE)
    , option_write_critical(FALSE)
    , option_interactive(FALSE)
    , option_linebreaks(1)
    , option_softlinebreaks(TRUE)
    , option_nodelinebreaks(FALSE)
    , option_expandcpl(FALSE)
    , option_pass_tt(FALSE)
    , option_fix_variation(FALSE)
    , option_findstart(1)
    , option_game_signature(FALSE)
    , option_strict_checking(FALSE)
    , option_reorder_variations(FALSE)
    // Corresponds to memset(error_enabled, TRUE, sizeof(error_enabled));
    , error_enabled(SgfcOptions::GetErrorCount(), TRUE)
    // Corresponds to setup of sgf_token in properties.c - no property has the
    // DELETE_PROP flag
    , delete_property(SgfcOptions::GetPropertyCount(), FALSE)
  {
  }

  SgfcOptions::~SgfcOptions()
  {
  }

  void SgfcOptions::CaptureOptions()
  {
    this->option_warnings = ::option_warnings;
    this->option_keep_head = ::option_keep_head;
    this->option_keep_unknown_props = ::option_keep_unknown_props;
    this->option_keep_obsolete_props = ::option_keep_obsolete_props;
    this->option_del_empty_nodes = ::option_del_empty_nodes;
    this->option_del_move_markup = ::option_del_move_markup;
    this->option_split_file = ::option_split_file;
    this->option_write_critical = ::option_write_critical;
    this->option_interactive = ::option_interactive;
    this->option_linebreaks = ::option_linebreaks;
    this->option_softlinebreaks = ::option_softlinebreaks;
    this->option_nodelinebreaks = ::option_nodelinebreaks;
    this->option_expandcpl = ::option_expandcpl;
    this->option_pass_tt = ::option_pass_tt;
    this->option_fix_variation = ::option_fix_variation;
    this->option_findstart = ::option_findstart;
    this->option_game_signature = ::option_game_signature;
    this->option_strict_checking = ::option_strict_checking;
    this->option_reorder_variations = ::option_reorder_variations;

    int errorCount = SgfcOptions::GetErrorCount();
    for (int indexOfError = 0; indexOfError < errorCount; indexOfError++)
      this->error_enabled[indexOfError] = (::error_enabled[indexOfError] == TRUE);

    int propertyCount = SgfcOptions::GetPropertyCount();
    for (int indexOfProperty = 0; indexOfProperty < propertyCount; indexOfProperty++)
      this->delete_property[indexOfProperty] = ((::sgf_token[indexOfProperty].flags & DELETE_PROP) == DELETE_PROP);
  }

  void SgfcOptions::RestoreOptions() const
  {
    ::option_warnings = this->option_warnings;
    ::option_keep_head = this->option_keep_head;
    ::option_keep_unknown_props = this->option_keep_unknown_props;
    ::option_keep_obsolete_props = this->option_keep_obsolete_props;
    ::option_del_empty_nodes = this->option_del_empty_nodes;
    ::option_del_move_markup = this->option_del_move_markup;
    ::option_split_file = this->option_split_file;
    ::option_write_critical = this->option_write_critical;
    ::option_interactive = this->option_interactive;
    ::option_linebreaks = this->option_linebreaks;
    ::option_softlinebreaks = this->option_softlinebreaks;
    ::option_nodelinebreaks = this->option_nodelinebreaks;
    ::option_expandcpl = this->option_expandcpl;
    ::option_pass_tt = this->option_pass_tt;
    ::option_fix_variation = this->option_fix_variation;
    ::option_findstart = this->option_findstart;
    ::option_game_signature = this->option_game_signature;
    ::option_strict_checking = this->option_strict_checking;
    ::option_reorder_variations = this->option_reorder_variations;

    int errorCount = SgfcOptions::GetErrorCount();
    for (int indexOfError = 0; indexOfError < errorCount; indexOfError++)
      ::error_enabled[indexOfError] = this->error_enabled[indexOfError] ? TRUE : FALSE;

    int propertyCount = SgfcOptions::GetPropertyCount();
    for (int indexOfProperty = 0; indexOfProperty < propertyCount; indexOfProperty++)
    {
      if (this->delete_property[indexOfProperty])
        ::sgf_token[indexOfProperty].flags |= DELETE_PROP;
      else
        ::sgf_token[indexOfProperty].flags &= ~DELETE_PROP;
    }
  }

  int SgfcOptions::GetErrorCount()
  {
    return MAX_ERROR_NUM;
  }

  int SgfcOptions::GetPropertyCount()
  {
    static int propertyCount = -1;

    if (propertyCount == -1)
    {
      // The last array element is not a real property, it's a delimiter element
      // used to stop iterations. The identifying mark is that member
      // SGFToken.id is NULL instead of a string. See properties.c.
      int indexOfProperty = 0;
      while (sgf_token[indexOfProperty].id != nullptr)
        indexOfProperty++;

      // We don't count the delimiter element at the end, so there's no need
      // for the usual +1 to get from index to count.
      propertyCount = indexOfProperty;
    }

    return propertyCount;
  }
}
