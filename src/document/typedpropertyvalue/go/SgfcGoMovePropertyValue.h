#pragma once

// Project includes
#include "../../../../include/ISgfcGoMovePropertyValue.h"
#include "../../../../include/SgfcBoardSize.h"
#include "../../../../include/SgfcColor.h"
#include "../SgfcMovePropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoMovePropertyValue class provides an implementation of
  /// the ISgfcGoMovePropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcGoMovePropertyValue : public SgfcMovePropertyValue, public ISgfcGoMovePropertyValue
  {
  public:
    SgfcGoMovePropertyValue(const std::string& rawValue, SgfcBoardSize boardSize, SgfcColor color);
    virtual ~SgfcGoMovePropertyValue();

    virtual const ISgfcGoMovePropertyValue* ToGoMoveValue() const;
    virtual std::shared_ptr<ISgfcGoMove> GetGoMove() const;

  private:
    std::shared_ptr<ISgfcGoMove> goMove;
  };
}
