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
#include "../../include/SgfcConstants.h"
#include "../../include/SgfcPlusPlusFactory.h"
#include "../game/SgfcGameInfo.h"
#include "../SgfcUtility.h"
#include "SgfcNode.h"

// C++ Standard Library includes
#include <algorithm>
#include <map>
#include <set>
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

  bool SgfcNode::IsRoot() const
  {
    return (this->parent.lock() == nullptr);
  }

  SgfcNodeTraits SgfcNode::GetTraits() const
  {
    SgfcNodeTraits traits = SgfcConstants::NodeTraitsNone;

    if (IsRoot())
      traits |= SgfcNodeTrait::Root;

    for (auto property : this->properties)
    {
      SgfcPropertyCategory propertyCategory = property->GetPropertyCategory();
      traits |= SgfcUtility::MapPropertyCategoryToNodeTraits(propertyCategory);

      if (property->HasTrait(SgfcPropertyTrait::Inheritable))
        traits |= SgfcNodeTrait::Inheritable;
    }

    return traits;
  }

  bool SgfcNode::HasTrait(SgfcNodeTrait trait) const
  {
    SgfcNodeTraits traits = GetTraits();
    return (traits & trait) != SgfcConstants::NodeTraitsNone;
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

    // shared_from_this returns a const object pointer because the method is
    // declared const. But we want to return a non-const object pointer because
    // the caller of the method should be free to do non-const things with the
    // object, since at that time program execution has left the "const context"
    // of the method. The only time it would not be safe to remove const'ness
    // is if another const-declared method ON THE SAME object invokes the method
    // and then does something non-const with the returned object, not realizing
    // that it is operating on itself.
    return std::const_pointer_cast<SgfcNode>(shared_from_this());
  }

  std::shared_ptr<ISgfcNode> SgfcNode::GetGameInfoNode() const
  {
    // See comment in GetRoot() about shared_from_this
    std::shared_ptr<ISgfcNode> node = std::const_pointer_cast<SgfcNode>(shared_from_this());

    while (node)
    {
      if (node->HasTrait(SgfcNodeTrait::GameInfo))
        return node;
      node = node->GetParent();
    }

    return nullptr;
  }

  std::vector<std::shared_ptr<ISgfcNode>> SgfcNode::GetMainVariationNodes() const
  {
    std::vector<std::shared_ptr<ISgfcNode>> mainVariationNodes;

    // See comment in GetRoot() about shared_from_this
    std::shared_ptr<ISgfcNode> node = std::const_pointer_cast<SgfcNode>(shared_from_this());

    while (node)
    {
      mainVariationNodes.push_back(node);
      node = node->GetFirstChild();
    }

    return mainVariationNodes;
  }

  std::shared_ptr<ISgfcGameInfo> SgfcNode::CreateGameInfo() const
  {
    auto rootNode = GetRoot();
    auto gameInfoNode = GetGameInfoNode();

    if (gameInfoNode == nullptr)
      return SgfcPlusPlusFactory::CreateGameInfo(rootNode);
    else
      return SgfcPlusPlusFactory::CreateGameInfo(rootNode, gameInfoNode);
  }

  void SgfcNode::WriteGameInfo(std::shared_ptr<ISgfcGameInfo> gameInfo) const
  {
    auto rootNode = GetRoot();
    auto gameInfoNode = GetGameInfoNode();
    if (gameInfoNode == nullptr)
      gameInfoNode = rootNode;

    auto gameInfoImplementation = std::dynamic_pointer_cast<SgfcGameInfo>(gameInfo);
    gameInfoImplementation->WriteToRootNode(rootNode);
    gameInfoImplementation->WriteToGameInfoNode(gameInfoNode);
  }

  bool SgfcNode::HasProperties() const
  {
    return ! this->properties.empty();
  }

  std::vector<std::shared_ptr<ISgfcProperty>> SgfcNode::GetProperties() const
  {
    return this->properties;
  }

  void SgfcNode::SetProperties(const std::vector<std::shared_ptr<ISgfcProperty>>& properties)
  {
    std::string validationFailedReason;
    bool arePropertiesValid = SgfcNode::ValidateProperties(properties, validationFailedReason);
    if (! arePropertiesValid)
      throw std::invalid_argument("SetProperties failed: " + validationFailedReason);

    this->properties = properties;
  }

  void SgfcNode::SetProperty(std::shared_ptr<ISgfcProperty> property)
  {
    if (property == nullptr)
      throw std::invalid_argument("AppendProperty failed: Property argument is null");

    auto propertyName = property->GetPropertyName();
    auto lambdaPropertyName = [&propertyName](auto lambdaProperty)->bool { return lambdaProperty->GetPropertyName() == propertyName; };

    // TODO: Use std::erase_if once C++20 becomes available
    auto result = std::find_if(
      std::begin(this->properties),
      std::end(this->properties),
      lambdaPropertyName);
    if (result != std::end(this->properties))
      this->properties.erase(result);

    auto propertyType = property->GetPropertyType();
    if (propertyType != SgfcPropertyType::Unknown)
    {
      auto lambdaPropertyType = [propertyType](auto lambdaProperty)->bool { return lambdaProperty->GetPropertyType() == propertyType; };
      // TODO: Use std::erase_if once C++20 becomes available
      auto result = std::find_if(
        std::begin(this->properties),
        std::end(this->properties),
        lambdaPropertyType);
      if (result != std::end(this->properties))
        this->properties.erase(result);
    }

    this->properties.push_back(property);
  }

  void SgfcNode::AppendProperty(std::shared_ptr<ISgfcProperty> property)
  {
    if (property == nullptr)
      throw std::invalid_argument("AppendProperty failed: Property argument is null");

    auto result = std::find(std::begin(this->properties), std::end(this->properties), property);
    if (result != std::end(this->properties))
      throw std::invalid_argument("AppendProperty failed: Property is already part of the node");

    std::vector<std::shared_ptr<ISgfcProperty>> propertiesCopy = this->properties;
    propertiesCopy.push_back(property);

    std::string validationFailedReason;
    bool arePropertiesValid = SgfcNode::ValidateProperties(propertiesCopy, validationFailedReason);
    if (! arePropertiesValid)
      throw std::invalid_argument("AppendProperty failed: " + validationFailedReason);

    this->properties = propertiesCopy;
  }

  void SgfcNode::RemoveProperty(std::shared_ptr<ISgfcProperty> property)
  {
    // This works because std::shared_ptr::operator==() compares pointer values
    auto result = std::find(std::begin(this->properties), std::end(this->properties), property);
    if (result == std::end(this->properties))
      throw std::invalid_argument("RemoveProperty failed: Property is not part of the node");

    this->properties.erase(result);
  }

  void SgfcNode::RemoveAllProperties()
  {
    this->properties.clear();
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

  std::shared_ptr<ISgfcProperty> SgfcNode::GetProperty(const std::string& propertyName) const
  {
    for (const auto& property : this->properties)
    {
      if (property->GetPropertyName() == propertyName)
        return property;
    }

    return nullptr;
  }

  bool SgfcNode::ValidateProperties(const std::vector<std::shared_ptr<ISgfcProperty>>& properties, std::string& validationFailedReason)
  {
    std::map<SgfcPropertyType, bool> propertyTypeMap;
    std::map<std::string, bool> propertyNameMap;

    for (const auto& property : properties)
    {
      if (property == nullptr)
      {
        validationFailedReason = "Properties collection contains nullptr element";
        return false;
      }

      auto propertyType = property->GetPropertyType();
      if (propertyType != SgfcPropertyType::Unknown && propertyTypeMap.find(propertyType) != propertyTypeMap.end())
      {
        std::stringstream message;
        message
          << "Properties collection contains element with duplicate property type "
          << static_cast<int>(propertyType);
        validationFailedReason = message.str();
        return false;
      }

      auto propertyName = property->GetPropertyName();
      if (propertyNameMap.find(propertyName) != propertyNameMap.end())
      {
        std::stringstream message;
        message
          << "Properties collection contains element with duplicate property name "
          << propertyName;
        validationFailedReason = message.str();
        return false;
      }

      propertyTypeMap[propertyType] = true;
      propertyNameMap[propertyName] = true;
    }

    return true;
  }

  std::vector<std::shared_ptr<ISgfcProperty>> SgfcNode::GetProperties(SgfcPropertyCategory propertyCategory) const
  {
    std::vector<std::shared_ptr<ISgfcProperty>> properties;

    for (auto property : this->properties)
    {
      if (property->GetPropertyCategory() == propertyCategory)
        properties.push_back(property);
    }

    return properties;
  }

  std::vector<std::shared_ptr<ISgfcProperty>> SgfcNode::GetInheritedProperties() const
  {
    std::vector<std::shared_ptr<ISgfcProperty>> properties;

    // This implementation is probably quite inefficient:
    // - Every time we invoke a property's HasTrait() method a lookup is made
    //   in the global property type to property traits map, which has many
    //   entries. If the same property exists in many nodes then the property
    //   is therefore looked up many times.
    // - Also this algorithm does not know when to stop, it will always follow
    //   the path up to the root node even if it has found all possible
    //   inheritable properties.
    //
    // It might be worth to rewrite the implementation to compile a list of
    // properties that have the inheritable trait. This list could then be
    // reduced when one of the properties is found, so the lookups become
    // shorter and shorter the more properties have been found, until eventually
    // the search can even stop if all properties have been found.

    std::set<std::string> propertyNamesSeen;

    const ISgfcNode* node = this;
    while (node)
    {
      for (auto property : node->GetProperties())
      {
        auto propertyName = property->GetPropertyName();
        if (propertyNamesSeen.find(propertyName) != propertyNamesSeen.end())
        {
          // Ignore property, we have already seen it in a previous node
          continue;
        }

        if (property->HasTrait(SgfcPropertyTrait::Inheritable))
        {
          properties.push_back(property);
          propertyNamesSeen.insert(propertyName);
        }
      }

      node = node->GetParent().get();
    }

    return properties;
  }
}
