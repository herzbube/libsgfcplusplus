#pragma once

// Project includes
#include "../../include/ISgfcNode.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcNode class provides an implementation of the
  /// ISgfcNode interface. See the interface header file for
  /// documentation.
  class SgfcNode : public ISgfcNode
  {
  public:
    SgfcNode();
    virtual ~SgfcNode();

    virtual std::shared_ptr<ISgfcNode> GetFirstChild() const;
    virtual void SetFirstChild(std::shared_ptr<ISgfcNode> firstChild);

    virtual std::shared_ptr<ISgfcNode> GetNextSibling() const;
    virtual void SetNextSibling(std::shared_ptr<ISgfcNode> nextSibling);
    
    virtual std::shared_ptr<ISgfcNode> GetParent() const;
    virtual void SetParent(std::shared_ptr<ISgfcNode> parent);

    virtual std::vector<std::shared_ptr<ISgfcProperty>> GetProperties() const;
    virtual void SetProperties(std::vector<std::shared_ptr<ISgfcProperty>> properties);

  private:
    std::shared_ptr<ISgfcNode> firstChild;
    std::shared_ptr<ISgfcNode> nextSibling;
    std::shared_ptr<ISgfcNode> parent;
    std::vector<std::shared_ptr<ISgfcProperty>> properties;
  };
}
