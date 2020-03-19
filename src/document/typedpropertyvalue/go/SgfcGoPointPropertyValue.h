#pragma once

// Project includes
#include "../../../../include/ISgfcGoPointPropertyValue.h"
#include "../../../../include/SgfcBoardSize.h"
#include "../SgfcPointPropertyValue.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoPointPropertyValue class provides an implementation of
  /// the ISgfcGoPointPropertyValue interface. See the interface header file
  /// for documentation.
  class SgfcGoPointPropertyValue : public SgfcPointPropertyValue, public ISgfcGoPointPropertyValue
  {
  public:
    SgfcGoPointPropertyValue(const std::string& rawValue, SgfcBoardSize boardSize);
    virtual ~SgfcGoPointPropertyValue();

    virtual const ISgfcGoPointPropertyValue* ToGoPointValue() const;
    virtual std::shared_ptr<ISgfcGoPoint> GetGoPoint() const;

  private:
    std::shared_ptr<ISgfcGoPoint> goPoint;
  };
}
