// Project includes
#include "../../include/ISgfcDocument.h"
#include "../../include/ISgfcComposedPropertyValue.h"
#include "../../include/ISgfcSinglePropertyValue.h"
#include "../SgfcConstants.h"
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

    // TODO: Take SgfcDocument::leadingContent into account.

    int indentationLevel = 0;

    for (auto game : document->GetGames())
    {
      auto rootNode = game->GetRootNode();

      EncodeGameTreeBeginOrEnd(SgfcConstants::GameTreeBeginToken, sgfContentStream, indentationLevel);
      indentationLevel++;

      EncodeNode(rootNode.get(), sgfContentStream, indentationLevel);

      RecursiveParseDepthFirst(rootNode, sgfContentStream, indentationLevel);

      indentationLevel--;
      EncodeGameTreeBeginOrEnd(SgfcConstants::GameTreeEndToken, sgfContentStream, indentationLevel);

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
      EncodeGameTreeBeginOrEnd(SgfcConstants::GameTreeBeginToken, sgfContentStream, indentationLevel);
      indentationLevel++;
    }

    EncodeNode(firstChildNode.get(), sgfContentStream, indentationLevel);

    RecursiveParseDepthFirst(firstChildNode, sgfContentStream, indentationLevel);

    if (hasSibling)
    {
      indentationLevel--;
      EncodeGameTreeBeginOrEnd(SgfcConstants::GameTreeEndToken, sgfContentStream, indentationLevel);
    }

    std::shared_ptr<ISgfcNode> nextSiblingNode = firstChildNode->GetNextSibling();
    while (nextSiblingNode != nullptr)
    {
      EncodeGameTreeBeginOrEnd(SgfcConstants::GameTreeBeginToken, sgfContentStream, indentationLevel);
      indentationLevel++;

      EncodeNode(nextSiblingNode.get(), sgfContentStream, indentationLevel);

      RecursiveParseDepthFirst(nextSiblingNode, sgfContentStream, indentationLevel);

      indentationLevel--;
      EncodeGameTreeBeginOrEnd(SgfcConstants::GameTreeEndToken, sgfContentStream, indentationLevel);

      nextSiblingNode = nextSiblingNode->GetNextSibling();
    }
  }

  void SgfcDocumentEncoder::EncodeNode(
    const ISgfcNode* node,
    std::stringstream& sgfContentStream,
    int indentationLevel) const
  {
    EncodeIndentation(indentationLevel, sgfContentStream);
    sgfContentStream << SgfcConstants::NodeBeginToken;

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
      sgfContentStream << SgfcConstants::PropertyValueBeginToken << SgfcConstants::PropertyValueEndToken;
  }

  void SgfcDocumentEncoder::EncodePropertyValue(
    const ISgfcPropertyValue* propertyValue,
    std::stringstream& sgfContentStream,
    int indentationLevel) const
  {
    sgfContentStream << SgfcConstants::PropertyValueBeginToken;

    if (propertyValue->IsComposedValue())
    {
      auto composedValue = propertyValue->ToComposedValue();
      // TODO: Escape [:], handle newlines etc.
      sgfContentStream << composedValue->GetValue1()->GetRawValue();
      sgfContentStream << SgfcConstants::ComposedValueSeparatorToken;
      // TODO: Escape [:], handle newlines etc.
      sgfContentStream << composedValue->GetValue2()->GetRawValue();
    }
    else
    {
      auto singleValue = propertyValue->ToSingleValue();
      // TODO: Escape [:], handle newlines etc.
      sgfContentStream << singleValue->GetRawValue();
    }

    sgfContentStream << SgfcConstants::PropertyValueEndToken;
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
      sgfContentStream << SgfcConstants::IndentationWhitespace;
      indentationLevel--;
    }
  }
}
