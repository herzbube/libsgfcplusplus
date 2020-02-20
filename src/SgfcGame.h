#pragma once

// Project includes
#include "../include/ISgfcGame.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGame class provides an implementation of the
  /// ISgfcGame interface. See the interface header file for
  /// documentation.
  class SgfcGame : public ISgfcGame
  {
  public:
    SgfcGame();
    SgfcGame(std::shared_ptr<ISgfcNode> rootNode);
    virtual ~SgfcGame();

    virtual std::shared_ptr<ISgfcNode> GetRootNode() const;
    virtual void SetRootNode(std::shared_ptr<ISgfcNode> rootNode);

  private:
    std::shared_ptr<ISgfcNode> rootNode;
  };
}
