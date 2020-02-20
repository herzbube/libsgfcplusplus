// Project includes
#include "SgfcNode.h"

namespace LibSgfcPlusPlus
{
  SgfcNode::SgfcNode()
  {
  }

  SgfcNode::~SgfcNode()
  {
  }

  std::shared_ptr<ISgfcNode> SgfcNode::GetFirstChild() const
  {
    return this->firstChild;
  }

  void SgfcNode::SetFirstChild(std::shared_ptr<ISgfcNode> firstChild)
  {
    this->firstChild = firstChild;
  }

  std::shared_ptr<ISgfcNode> SgfcNode::GetNextSibling() const
  {
    return this->nextSibling;
  }

  void SgfcNode::SetNextSibling(std::shared_ptr<ISgfcNode> nextSibling)
  {
    this->nextSibling = nextSibling;
  }

  std::shared_ptr<ISgfcNode> SgfcNode::GetParent() const
  {
    return this->parent;
  }

  void SgfcNode::SetParent(std::shared_ptr<ISgfcNode> parent)
  {
    this->parent = parent;
  }

  std::vector<std::shared_ptr<ISgfcProperty>> SgfcNode::GetProperties() const
  {
    return this->properties;
  }

  void SgfcNode::SetProperties(std::vector<std::shared_ptr<ISgfcProperty>> properties)
  {
    this->properties = properties;
  }
}
