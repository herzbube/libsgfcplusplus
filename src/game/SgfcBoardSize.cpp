#pragma once

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
