// Project includes
#include "SgfcGoMovePropertyValue.h"
#include "../../../game/go/SgfcGoMove.h"
#include "../../../game/go/SgfcGoPoint.h"
#include "../../../game/go/SgfcGoStone.h"

namespace LibSgfcPlusPlus
{
  SgfcGoMovePropertyValue::SgfcGoMovePropertyValue(const std::string& rawValue, SgfcBoardSize boardSize, SgfcColor color)
    : SgfcMovePropertyValue(rawValue)
    , goMove(new SgfcGoMove(std::shared_ptr<ISgfcGoStone>(new SgfcGoStone(color, std::shared_ptr<ISgfcGoPoint>(new SgfcGoPoint(rawValue, boardSize))))))
  {
  }

  SgfcGoMovePropertyValue::SgfcGoMovePropertyValue(SgfcColor color)
    : SgfcMovePropertyValue("")
    , goMove(new SgfcGoMove(color))
  {
  }

  SgfcGoMovePropertyValue::~SgfcGoMovePropertyValue()
  {
  }

  const ISgfcGoMovePropertyValue* SgfcGoMovePropertyValue::ToGoMoveValue() const
  {
    return this;
  }

  std::shared_ptr<ISgfcGoMove> SgfcGoMovePropertyValue::GetGoMove() const
  {
    return this->goMove;
  }
}
