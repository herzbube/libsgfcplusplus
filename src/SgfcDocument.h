#pragma once

// Project includes
#include "../include/ISgfcDocument.h"

// C++ Standard Library includes
#include <string>

// Forward declarations
struct SGFInfo;
struct Node;
struct Property;

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

    virtual std::vector<std::shared_ptr<ISgfcGame>> GetGames() const;
  
  private:
    std::string rawContent;
    std::string leadingContent;
    /// @todo Can we fill this?
    std::string trailingContent;
    std::vector<std::shared_ptr<ISgfcGame>> games;

    void RecursiveParseDepthFirst(std::shared_ptr<ISgfcNode> parentNode, Node* sgfParentNode);
    void ParseProperties(std::shared_ptr<ISgfcNode> node, Node* sgfNode);
    SgfcPropertyType GetSgfcPropertyTypeFromSgfProperty(Property* sgfProperty);
  };
}
