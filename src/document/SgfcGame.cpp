// Project includes
#include "SgfcGame.h"

namespace LibSgfcPlusPlus
{
  SgfcGame::SgfcGame(SgfcGameType gameType, std::shared_ptr<ISgfcNode> rootNode)
    : gameType(gameType)
    , rootNode(rootNode)
  {
  }

  SgfcGame::~SgfcGame()
  {
  }

  SgfcGameType SgfcGame::GetGameType() const
  {
    return this->gameType;
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
