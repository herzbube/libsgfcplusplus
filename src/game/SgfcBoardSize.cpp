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
#include "../../include/SgfcBoardSize.h"

namespace LibSgfcPlusPlus
{
  bool SgfcBoardSize::IsSquare() const
  {
    return (this->Columns == this->Rows);
  }

  bool SgfcBoardSize::operator==(const SgfcBoardSize& other) const
  {
    if (this == &other)
      return true;
    else if (this->Columns != other.Columns)
      return false;
    else if (this->Rows != other.Rows)
      return false;
    else
      return true;
  }

  bool SgfcBoardSize::operator!=(const SgfcBoardSize& other) const
  {
    return ! (*this == other);
  }
}
