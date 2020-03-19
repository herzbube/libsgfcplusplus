#pragma once

// Project includes
#include "../../include/ISgfcDocument.h"

// C++ Standard Library includes
#include <string>

// Forward declarations
class ISgfcGoPoint;
struct SGFInfo;
struct Node;

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcDocument class provides an implementation of the
  /// ISgfcDocument interface. See the interface header file for
  /// documentation.
  class SgfcDocument : public ISgfcDocument
  {
  public:
    SgfcDocument();
    SgfcDocument(SGFInfo* sgfInfo);
    virtual ~SgfcDocument();

    virtual bool IsEmpty() const;

    virtual std::vector<std::shared_ptr<ISgfcGame>> GetGames() const;
    virtual void SetGames(const std::vector<std::shared_ptr<ISgfcGame>>& games);
    virtual void AppendGame(std::shared_ptr<ISgfcGame> game);
    virtual void RemoveGame(std::shared_ptr<ISgfcGame> game);
    virtual void RemoveAllGames();

    virtual void DebugPrintToConsole() const;

  private:
    std::string rawContent;
    std::string leadingContent;
    /// @todo Can we fill this?
    std::string trailingContent;
    std::vector<std::shared_ptr<ISgfcGame>> games;

    void RecursiveParseDepthFirst(
      std::shared_ptr<ISgfcNode> parentNode,
      Node* sgfParentNode,
      SgfcGameType gameType,
      SgfcBoardSize boardSize,
      std::shared_ptr<ISgfcTreeBuilder> treeBuilder);
    void ParseProperties(
      std::shared_ptr<ISgfcNode> node,
      Node* sgfNode,
      SgfcGameType gameType,
      SgfcBoardSize boardSize);

    void DebugPrintNodeToConsole(std::shared_ptr<ISgfcNode> node, int nodeNumber) const;
    void DebugPrintGoPropertyValueToConsole(const ISgfcSinglePropertyValue* propertyValue) const;
    void DebugPrintGoPointValueToConsole(const ISgfcGoPoint* goPoint) const;
  };
}
