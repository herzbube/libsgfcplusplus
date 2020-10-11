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
#include "../../include/ISgfcDocument.h"
#include "../../include/ISgfcComposedPropertyValue.h"
#include "../../include/ISgfcSinglePropertyValue.h"
#include "../SgfcPrivateConstants.h"
#include "SgfcDocumentEncoder.h"

// C++ Standard Library includes
#include <sstream>

namespace LibSgfcPlusPlus
{
  SgfcDocumentEncoder::SgfcDocumentEncoder(std::shared_ptr<ISgfcDocument> document)
    : document(document)
  {
  }

  SgfcDocumentEncoder::~SgfcDocumentEncoder()
  {
  }

  std::string SgfcDocumentEncoder::Encode() const
  {
    std::stringstream sgfContentStream;

    int indentationLevel = 0;

    int indexOfGame = -1;
    for (auto game : document->GetGames())
    {
      indexOfGame++;

      auto rootNode = game->GetRootNode();
      if (rootNode == nullptr)
      {
        std::stringstream errorMessage;
        errorMessage << "Document encoding failed: Game at index position " << indexOfGame << " has no root node";
        throw std::logic_error(errorMessage.str());
      }

      EncodeGameTreeBeginOrEnd(SgfcPrivateConstants::GameTreeBeginToken, sgfContentStream, indentationLevel);
      indentationLevel++;

      EncodeNode(rootNode.get(), sgfContentStream, indentationLevel);

      RecursiveParseDepthFirst(rootNode, sgfContentStream, indentationLevel);

      indentationLevel--;
      EncodeGameTreeBeginOrEnd(SgfcPrivateConstants::GameTreeEndToken, sgfContentStream, indentationLevel);

      rootNode = rootNode->GetNextSibling();
    }

    return sgfContentStream.str();
  }

  void SgfcDocumentEncoder::RecursiveParseDepthFirst(
    std::shared_ptr<ISgfcNode> parentNode,
    std::stringstream& sgfContentStream,
    int indentationLevel) const
  {
    std::shared_ptr<ISgfcNode> firstChildNode = parentNode->GetFirstChild();
    if (firstChildNode == nullptr)
      return;

    // TODO: This kind of "lookahead" would not be necessary if we could simply
    // get the parent node's children and do a count on them. It would also
    // make special treatment of first child node unnecessary - we could
    // simply iterate over all children.
    bool hasSibling = (firstChildNode->GetNextSibling() != nullptr);

    if (hasSibling)
    {
      EncodeGameTreeBeginOrEnd(SgfcPrivateConstants::GameTreeBeginToken, sgfContentStream, indentationLevel);
      indentationLevel++;
    }

    EncodeNode(firstChildNode.get(), sgfContentStream, indentationLevel);

    RecursiveParseDepthFirst(firstChildNode, sgfContentStream, indentationLevel);

    if (hasSibling)
    {
      indentationLevel--;
      EncodeGameTreeBeginOrEnd(SgfcPrivateConstants::GameTreeEndToken, sgfContentStream, indentationLevel);
    }

    std::shared_ptr<ISgfcNode> nextSiblingNode = firstChildNode->GetNextSibling();
    while (nextSiblingNode != nullptr)
    {
      EncodeGameTreeBeginOrEnd(SgfcPrivateConstants::GameTreeBeginToken, sgfContentStream, indentationLevel);
      indentationLevel++;

      EncodeNode(nextSiblingNode.get(), sgfContentStream, indentationLevel);

      RecursiveParseDepthFirst(nextSiblingNode, sgfContentStream, indentationLevel);

      indentationLevel--;
      EncodeGameTreeBeginOrEnd(SgfcPrivateConstants::GameTreeEndToken, sgfContentStream, indentationLevel);

      nextSiblingNode = nextSiblingNode->GetNextSibling();
    }
  }

  void SgfcDocumentEncoder::EncodeNode(
    const ISgfcNode* node,
    std::stringstream& sgfContentStream,
    int indentationLevel) const
  {
    EncodeIndentation(indentationLevel, sgfContentStream);

    sgfContentStream << SgfcPrivateConstants::NodeBeginToken;

    for (auto property : node->GetProperties())
    {
      EncodeProperty(property.get(), sgfContentStream, indentationLevel);
    }

    sgfContentStream << std::endl;
  }

  void SgfcDocumentEncoder::EncodeProperty(
    const ISgfcProperty* property,
    std::stringstream& sgfContentStream,
    int indentationLevel) const
  {
    sgfContentStream << property->GetPropertyName();

    // TODO: Add a convenience method ISgfcProperty::HasValues/HasNoValues
    bool propertyHasNoValues = true;

    for (auto propertyValue : property->GetPropertyValues())
    {
      propertyHasNoValues = false;

      EncodePropertyValue(propertyValue.get(), sgfContentStream, indentationLevel);
    }

    if (propertyHasNoValues)
      sgfContentStream << SgfcPrivateConstants::PropertyValueBeginToken << SgfcPrivateConstants::PropertyValueEndToken;
  }

  void SgfcDocumentEncoder::EncodePropertyValue(
    const ISgfcPropertyValue* propertyValue,
    std::stringstream& sgfContentStream,
    int indentationLevel) const
  {
    sgfContentStream << SgfcPrivateConstants::PropertyValueBeginToken;

    if (propertyValue->IsComposedValue())
      EncodeComposedPropertyValue(propertyValue->ToComposedValue(), sgfContentStream, indentationLevel);
    else
      EncodeSinglePropertyValue(propertyValue->ToSingleValue(), sgfContentStream, indentationLevel);

    sgfContentStream << SgfcPrivateConstants::PropertyValueEndToken;
  }

  void SgfcDocumentEncoder::EncodeComposedPropertyValue(
    const ISgfcComposedPropertyValue* composedPropertyValue,
    std::stringstream& sgfContentStream,
    int indentationLevel) const
  {
    EncodeSinglePropertyValue(composedPropertyValue->GetValue1().get(), sgfContentStream, indentationLevel);

    sgfContentStream << SgfcPrivateConstants::ComposedValueSeparatorToken;

    EncodeSinglePropertyValue(composedPropertyValue->GetValue2().get(), sgfContentStream, indentationLevel);
  }

  void SgfcDocumentEncoder::EncodeSinglePropertyValue(
    const ISgfcSinglePropertyValue* singlePropertyValue,
    std::stringstream& sgfContentStream,
    int indentationLevel) const
  {
    switch (singlePropertyValue->GetValueType())
    {
      case SgfcPropertyValueType::SimpleText:
      case SgfcPropertyValueType::Text:
        // TODO: Handle newlines
        sgfContentStream << AddSimpleTextAndTextEscapeCharacters(singlePropertyValue->GetRawValue());
        break;

      // An application-specific value type might contain anything at all. We
      // can't perform the same escaping as for SimpleText/Text, though, because
      // we have no idea how the unknown value type is structured.
      case SgfcPropertyValueType::Unknown:  // fall-through intentional

      // For unknown game types the following value types can contain anything
      // at all, quite similar to SgfcPropertyValueType::Unknown.
      // TODO: Do not escape for SgfcGameType::Go
      case SgfcPropertyValueType::Point:
      case SgfcPropertyValueType::Move:
      case SgfcPropertyValueType::Stone:
        sgfContentStream << AddMandatoryEscapeCharacters(singlePropertyValue->GetRawValue());
        break;

      // All other value types have strict requirements and don't need
      // escaping
      default:
        sgfContentStream << singlePropertyValue->GetRawValue();
        break;
    }
  }

  void SgfcDocumentEncoder::EncodeGameTreeBeginOrEnd(
    const std::string& beginOrEndToken,
    std::stringstream& sgfContentStream,
    int indentationLevel) const
  {
    EncodeIndentation(indentationLevel, sgfContentStream);

    sgfContentStream << beginOrEndToken;

    sgfContentStream << std::endl;
  }

  void SgfcDocumentEncoder::EncodeIndentation(
    int indentationLevel,
    std::stringstream& sgfContentStream) const
  {
    while (indentationLevel > 0)
    {
      sgfContentStream << SgfcPrivateConstants::IndentationWhitespace;
      indentationLevel--;
    }
  }

  std::string SgfcDocumentEncoder::AddSimpleTextAndTextEscapeCharacters(const std::string& propertyValue) const
  {
    // Escape characters already present must be escaped first so that we don't
    // escape the escape characters from other escape sequences.
    std::string result = std::regex_replace(
      propertyValue,
      SgfcPrivateConstants::UnescapedEscapeCharacterRegex,
      SgfcPrivateConstants::EscapedEscapeCharacterToken);

    // There's no logic here to check whether this belongs to a composed
    // property value and needs escaping at all. It would make things overly
    // complicated, and the SGF standard does not forbid useless escape
    // character. Last but not least, as an implementation detail we know that
    // later on when SGFC processes the SGF content we generate here it will
    // remove any unnecessary escape characters.
    result = std::regex_replace(
      result,
      SgfcPrivateConstants::UnescapedComposedValueSeparatorTokenRegex,
      SgfcPrivateConstants::EscapedComposedValueSeparatorToken);

    return AddMandatoryEscapeCharacters(result);
  }

  std::string SgfcDocumentEncoder::AddMandatoryEscapeCharacters(const std::string& propertyValue) const
  {
    return std::regex_replace(
      propertyValue,
      SgfcPrivateConstants::UnescapedPropertyValueEndTokenRegex,
      SgfcPrivateConstants::EscapedPropertyValueEndToken);
  }
}
