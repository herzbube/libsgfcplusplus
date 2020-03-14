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
    void SetFirstChild(std::shared_ptr<ISgfcNode> node);
    virtual std::shared_ptr<ISgfcNode> GetLastChild() const;
    virtual std::vector<std::shared_ptr<ISgfcNode>> GetChildren() const;
    virtual bool HasChildren() const;

    virtual std::shared_ptr<ISgfcNode> GetNextSibling() const;
    void SetNextSibling(std::shared_ptr<ISgfcNode> node);
    virtual bool HasNextSibling() const;
    virtual std::shared_ptr<ISgfcNode> GetPreviousSibling() const;
    virtual bool HasPreviousSibling() const;

    virtual std::shared_ptr<ISgfcNode> GetParent() const;
    void SetParent(std::shared_ptr<ISgfcNode> node);
    virtual bool HasParent() const;
    virtual bool IsDescendantOf(std::shared_ptr<ISgfcNode> node) const;
    virtual bool IsAncestorOf(std::shared_ptr<ISgfcNode> node) const;
    virtual std::shared_ptr<ISgfcNode> GetRoot() const;
    virtual bool IsRoot() const;

    virtual std::vector<std::shared_ptr<ISgfcProperty>> GetProperties() const;
    virtual void SetProperties(std::vector<std::shared_ptr<ISgfcProperty>> properties);
    virtual std::shared_ptr<ISgfcProperty> GetProperty(SgfcPropertyType propertyType) const;

  private:
    std::shared_ptr<ISgfcNode> firstChild;
    std::shared_ptr<ISgfcNode> nextSibling;
    std::weak_ptr<ISgfcNode> parent;  // must be weak_ptr to break reference cycle
    std::vector<std::shared_ptr<ISgfcProperty>> properties;
  };
}
