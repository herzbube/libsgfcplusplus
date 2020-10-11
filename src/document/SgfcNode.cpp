// -----------------------------------------------------------------------------
// Copyright 2020 Patrick Näf (herzbube@herzbube.ch)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -----------------------------------------------------------------------------

// Project includes
#include "SgfcNode.h"

// C++ Standard Library includes
#include <map>
#include <sstream>

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

  void SgfcNode::SetFirstChild(std::shared_ptr<ISgfcNode> node)
  {
    this->firstChild = node;
  }

  std::shared_ptr<ISgfcNode> SgfcNode::GetLastChild() const
  {
    auto child = this->firstChild;

    while (child)
    {
      if (child->HasNextSibling())
        child = child->GetNextSibling();
      else
        return child;
    }

    return nullptr;
  }

  std::vector<std::shared_ptr<ISgfcNode>> SgfcNode::GetChildren() const
  {
    std::vector<std::shared_ptr<ISgfcNode>> children;

    auto child = this->firstChild;

    while (child)
    {
      children.push_back(child);
      child = child->GetNextSibling();
    }

    return children;
  }

  bool SgfcNode::HasChildren() const
  {
    return (this->firstChild != nullptr);
  }

  std::shared_ptr<ISgfcNode> SgfcNode::GetNextSibling() const
  {
    return this->nextSibling;
  }

  void SgfcNode::SetNextSibling(std::shared_ptr<ISgfcNode> node)
  {
    this->nextSibling = node;
  }

  bool SgfcNode::HasNextSibling() const
  {
    return (this->nextSibling != nullptr);
  }

  std::shared_ptr<ISgfcNode> SgfcNode::GetPreviousSibling() const
  {
    auto parentLocked = this->parent.lock();
    if (parentLocked == nullptr)
      return nullptr;

    auto child = parentLocked->GetFirstChild();
    if (child.get() == this)
      return nullptr;

    while (child)
    {
      auto nextSibling = child->GetNextSibling();
      if (nextSibling.get() == this)
        return child;
      else
        child = nextSibling;
    }

    return nullptr;
  }

  bool SgfcNode::HasPreviousSibling() const
  {
    // An implementation that is more efficient is not possible
    return (this->GetPreviousSibling() != nullptr);
  }

  std::shared_ptr<ISgfcNode> SgfcNode::GetParent() const
  {
    return this->parent.lock();
  }

  void SgfcNode::SetParent(std::shared_ptr<ISgfcNode> node)
  {
    this->parent = node;
  }

  bool SgfcNode::HasParent() const
  {
    return (this->parent.lock() != nullptr);
  }

  bool SgfcNode::IsDescendantOf(std::shared_ptr<ISgfcNode> node) const
  {
    if (node == nullptr)
      throw std::invalid_argument("IsDescendantOf failed: Node argument is null");

    auto parent = this->GetParent();

    while (parent)
    {
      if (parent == node)
        return true;
      else
        parent = parent->GetParent();
    }

    return false;
  }

  bool SgfcNode::IsAncestorOf(std::shared_ptr<ISgfcNode> node) const
  {
    if (node == nullptr)
      throw std::invalid_argument("IsAncestorOf failed: Node argument is null");

    auto parent = node->GetParent();

    while (parent)
    {
      if (parent.get() == this)
        return true;
      else
        parent = parent->GetParent();
    }

    return false;
  }

  std::shared_ptr<ISgfcNode> SgfcNode::GetRoot() const
  {
    auto parent = this->parent.lock();
    while (parent)
    {
      if (parent->HasParent())
        parent = parent->GetParent();
      else
        return parent;
    }

    // Actually we would like to return this object because the node is already
    // the root node. Unfortunately we can't, because returning a new
    // std::shared_ptr that contains this object would create a second source of
    // ownership for this object - the first source was when the library's main
    // factory created this object and handed it out wrapped in a
    // std::shared_ptr.
    return nullptr;
  }

  bool SgfcNode::IsRoot() const
  {
    return (this->parent.lock() == nullptr);
  }

  std::vector<std::shared_ptr<ISgfcProperty>> SgfcNode::GetProperties() const
  {
    return this->properties;
  }

  void SgfcNode::SetProperties(const std::vector<std::shared_ptr<ISgfcProperty>>& properties)
  {
    std::map<SgfcPropertyType, bool> propertyTypeMap;
    std::map<std::string, bool> propertyNameMap;

    for (const auto& property : properties)
    {
      if (property == nullptr)
        throw std::invalid_argument("SetProperties failed: Properties collection contains nullptr element");

      auto propertyType = property->GetPropertyType();
      if (propertyType != SgfcPropertyType::Unknown && propertyTypeMap.find(propertyType) != propertyTypeMap.end())
      {
        std::stringstream message;
        message
          << "SetProperties failed: Properties collection contains element with duplicate property type "
          << static_cast<int>(propertyType);
        throw std::invalid_argument(message.str());
      }

      auto propertyName = property->GetPropertyName();
      if (propertyNameMap.find(propertyName) != propertyNameMap.end())
      {
        std::stringstream message;
        message
          << "SetProperties failed: Properties collection contains element with duplicate property name "
          << propertyName;
        throw std::invalid_argument(message.str());
      }

      propertyTypeMap[propertyType] = true;
      propertyNameMap[propertyName] = true;
    }

    this->properties = properties;
  }

  std::shared_ptr<ISgfcProperty> SgfcNode::GetProperty(SgfcPropertyType propertyType) const
  {
    for (const auto& property : this->properties)
    {
      if (property->GetPropertyType() == propertyType)
        return property;
    }

    return nullptr;
  }
}
