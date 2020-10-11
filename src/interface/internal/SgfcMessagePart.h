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

namespace LibSgfcPlusPlus
{
  /// @brief Enumerates the individual parts of an SGFC message.
  ///
  /// @ingroup internals
  ///
  /// The message format according to the SGFC documentation file is this:
  ///
  /// "[Line:x Col:x - ] Message type and number [(critical)]: message text"
  ///
  /// Examples:
  ///
  /// Line:2 Col:56 - Error 8 (critical): illegal char(s) found: "fsgdf"
  /// Line:35 Col:1 - Warning 35: unknown property <XX> found
  /// Fatal error 2: unknown command line option 'x'
  /// Error 60: file contains more than one game tree
  /// Line:1 Col:5 - Fatal error 46: unknown file format (only able to handle files up to FF[4])
  enum class SgfcMessagePart
  {
    LineNumberOrMessageTypeToken,
    ColumnNumber,
    ErrorLowerCaseToken,
    Dash,
    MessageType,
    MessageID,
    CriticalIndicator,
    MessageText,
  };
}
