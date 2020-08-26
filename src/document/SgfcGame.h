#pragma once

// Project includes
#include "../../include/ISgfcGame.h"

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

    virtual SgfcGameType GetGameType() const;
    virtual SgfcNumber GetGameTypeAsNumber() const;

    virtual bool HasBoardSize() const;
    virtual SgfcBoardSize GetBoardSize() const;

    virtual bool HasRootNode() const;
    virtual std::shared_ptr<ISgfcNode> GetRootNode() const;
    virtual void SetRootNode(std::shared_ptr<ISgfcNode> rootNode);

    virtual std::shared_ptr<ISgfcTreeBuilder> GetTreeBuilder() const;
    void SetTreeBuilder(std::shared_ptr<ISgfcTreeBuilder> treeBuilder);

  private:
    SgfcGameType gameType;
    std::shared_ptr<ISgfcNode> rootNode;
    std::shared_ptr<ISgfcTreeBuilder> treeBuilder;
  };
}
