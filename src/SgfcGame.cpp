// Project includes
#include "SgfcGame.h"

namespace LibSgfcPlusPlus
{
  SgfcGame::SgfcGame()
  {
  }

  SgfcGame::SgfcGame(std::shared_ptr<ISgfcNode> rootNode)
    : rootNode(rootNode)
  {
  }

  SgfcGame::~SgfcGame()
  {
  }

  std::shared_ptr<ISgfcNode> SgfcGame::GetRootNode() const
  {
    return this->rootNode;
  }

  void SgfcGame::SetRootNode(std::shared_ptr<ISgfcNode> rootNode)
  {
    this->rootNode = rootNode;
  }
}
