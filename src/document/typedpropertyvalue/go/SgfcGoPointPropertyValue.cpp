// Project includes
#include "SgfcGoPointPropertyValue.h"
#include "../../../game/go/SgfcGoPoint.h"

namespace LibSgfcPlusPlus
{
  SgfcGoPointPropertyValue::SgfcGoPointPropertyValue(const std::string& rawValue, SgfcBoardSize boardSize)
    : SgfcPointPropertyValue(rawValue)
    , goPoint(new SgfcGoPoint(rawValue, boardSize))
  {
  }

  SgfcGoPointPropertyValue::SgfcGoPointPropertyValue(const std::string& rawValue)
    : SgfcPointPropertyValue(rawValue)
    , goPoint(nullptr)
  {
  }

  SgfcGoPointPropertyValue::~SgfcGoPointPropertyValue()
  {
  }

  const ISgfcGoPointPropertyValue* SgfcGoPointPropertyValue::ToGoPointValue() const
  {
    return this;
  }

  std::shared_ptr<ISgfcGoPoint> SgfcGoPointPropertyValue::GetGoPoint() const
  {
    return this->goPoint;
  }
}
