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
#include "../../include/ISgfcMovePropertyValue.h"
#include "../../include/ISgfcPointPropertyValue.h"
#include "../../include/ISgfcStonePropertyValue.h"
#include "../../include/ISgfcSinglePropertyValue.h"
#include "../../include/ISgfcSimpleTextPropertyValue.h"
#include "../../include/ISgfcTextPropertyValue.h"
#include "../SgfcPrivateConstants.h"
#include "SgfcDocumentEncoder.h"

// C++ Standard Library includes
#include <sstream>
#include <stack>

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
    // Make sure that decimal point is always a period (".") character and that
    // there are no thousands separators
    sgfContentStream.imbue(std::locale::classic());

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

      ParseDepthFirst(rootNode, sgfContentStream, indentationLevel);

      indentationLevel--;
      EncodeGameTreeBeginOrEnd(SgfcPrivateConstants::GameTreeEndToken, sgfContentStream, indentationLevel);

      rootNode = rootNode->GetNextSibling();
    }

    return sgfContentStream.str();
  }

  void SgfcDocumentEncoder::ParseDepthFirst(
    std::shared_ptr<ISgfcNode> rootNode,
    std::stringstream& sgfContentStream,
    int indentationLevel) const
  {
    // Implementation note: We can't use
    // SgfcNodeIterator::IterateOverNodesDepthFirst() because of the indentation
    // feature. SgfcNodeIterator::IterateOverNodesDepthFirst() visits a node
    // only once, but this method needs to visit a node twice: Once when it
    // encounters the node for the first time, and once when it pops the node
    // from the stack. If the indentation feature is no longer needed then
    // this method can use SgfcNodeIterator::IterateOverNodesDepthFirst().

    std::stack<std::shared_ptr<ISgfcNode>> stack;

    std::shared_ptr<ISgfcNode> currentNode = rootNode;

    while (true)
    {
      while (currentNode)
      {
        if (currentNode->HasNextSibling() || currentNode->HasPreviousSibling())
        {
          EncodeGameTreeBeginOrEnd(SgfcPrivateConstants::GameTreeBeginToken, sgfContentStream, indentationLevel);
          indentationLevel++;
        }

        EncodeNode(currentNode.get(), sgfContentStream, indentationLevel);

        stack.push(currentNode);

        currentNode = currentNode->GetFirstChild();
      }

      if (! stack.empty())
      {
        currentNode = stack.top();
        stack.pop();

        if (currentNode->HasNextSibling() || currentNode->HasPreviousSibling())
        {
          indentationLevel--;
          EncodeGameTreeBeginOrEnd(SgfcPrivateConstants::GameTreeEndToken, sgfContentStream, indentationLevel);
        }

        currentNode = currentNode->GetNextSibling();
      }
      else
      {
        // We're done
        break;
      }
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
      EncodeSinglePropertyValue(propertyValue->ToSingleValue(), SgfcSinglePropertyValueContext::Standalone, sgfContentStream, indentationLevel);

    sgfContentStream << SgfcPrivateConstants::PropertyValueEndToken;
  }

  void SgfcDocumentEncoder::EncodeComposedPropertyValue(
    const ISgfcComposedPropertyValue* composedPropertyValue,
    std::stringstream& sgfContentStream,
    int indentationLevel) const
  {
    EncodeSinglePropertyValue(
      composedPropertyValue->GetValue1().get(),
      SgfcSinglePropertyValueContext::FirstValueOfComposedValue,
      sgfContentStream,
      indentationLevel);

    sgfContentStream << SgfcPrivateConstants::ComposedValueSeparatorToken;

    EncodeSinglePropertyValue(
      composedPropertyValue->GetValue2().get(),
      SgfcSinglePropertyValueContext::SecondValueOfComposedValue,
      sgfContentStream,
      indentationLevel);
  }

  void SgfcDocumentEncoder::EncodeSinglePropertyValue(
    const ISgfcSinglePropertyValue* singlePropertyValue,
    SgfcSinglePropertyValueContext singlePropertyValueContext,
    std::stringstream& sgfContentStream,
    int indentationLevel) const
  {
    auto propertyValueType = singlePropertyValue->GetValueType();
    switch (propertyValueType)
    {
      // libsgfc++ gives the library client the guarantee that SimpleText and
      // Text values don't need to contain escape characters, so we now have to
      // add escaping. If possible we don't use the raw value, although it
      // should not matter:
      // - If the property value object was created programmatically then the
      //   raw value and the value passed by the library client to the factory
      //   are the same.
      // - If the property value object was created internally by ligsgfc++
      //   during reading of SGF content, then the raw value is what SGFC passed
      //   on to libsgfc++ after performing error corrections. Since SGFC V2.0
      //   this should not contain escape characters.
      case SgfcPropertyValueType::SimpleText:
      case SgfcPropertyValueType::Text:
      {
        std::string valueToEncode;

        if (! singlePropertyValue->HasTypedValue())
          valueToEncode = singlePropertyValue->GetRawValue();
        else if (propertyValueType == SgfcPropertyValueType::SimpleText)
          valueToEncode = singlePropertyValue->ToSimpleTextValue()->GetSimpleTextValue();
        else
          valueToEncode = singlePropertyValue->ToTextValue()->GetTextValue();

        // Newlines should not exist in a SimpleText value, but if it does
        // SGFC will treat it as a space character when we pass it
        // sgfContentStream for reading.

        sgfContentStream << AddSimpleTextAndTextEscapeCharacters(valueToEncode, singlePropertyValueContext);
        break;
      }

      // An application-specific value type might contain anything at all. We
      // can't perform the same escaping as for SimpleText/Text, though, because
      // we have no idea how the unknown value type is structured.
      case SgfcPropertyValueType::Unknown:
      {
        sgfContentStream << AddMandatoryEscapeCharacters(singlePropertyValue->GetRawValue(), singlePropertyValueContext);
        break;
      }

      // For game types that are not Go the following value types can contain
      // anything at all, quite similar to SgfcPropertyValueType::Unknown.
      // - If the property value object was created programmatically then the
      //   raw value was created by libsgfc++ and cannot contain any errors
      //   because the factory strictly allow only good values. The raw value
      //   is therefore good to pass to SGFC for writing.
      // - If the property value object was created internally by ligsgfc++
      //   during reading of SGF content, then the raw value is what SGFC passed
      //   on to libsgfc++ after performing error corrections. That should also
      //   be good enough to pass to SGFC for writing. Any errors in the
      //   original SGF content that SGFC passed on to libsgfc++ can now be
      //   passed back to SGFC, as that is what would have happened had the SGF
      //   content been read+written by SGFC on the command line.
      // - If the property value object is for game type Go, then the raw value
      //   contains the SGF notation of the move/point/stone, regardless of
      //   whether the property value object was created programmatically by
      //   the library client or internally by libsgfc++ during reading of SGF
      //   content. The SGF notation does not need escaping.
      // - If the property value object is not for game type Go, then the raw
      //   value and the move/point/stone value are the same, regardless of
      //   whether the property value object was created programmatically by
      //   the library client or internally by libsgfc++ during reading of SGF
      //   content. This value could contain anything, so we have to do
      //   escaping, but since we don't know the structure of the value we can
      //   only do basic escaping.
      case SgfcPropertyValueType::Point:
      case SgfcPropertyValueType::Move:
      case SgfcPropertyValueType::Stone:
      {
        std::string valueToEncode = singlePropertyValue->GetRawValue();
        bool valueToEncodeNeedsEscaping = true;

        if (singlePropertyValue->HasTypedValue())
        {
          if (propertyValueType == SgfcPropertyValueType::Point)
          {
            auto pointPropertyValue = singlePropertyValue->ToPointValue();
            if (pointPropertyValue->ToGoPointValue() != nullptr)
              valueToEncodeNeedsEscaping = false;
          }
          else if (propertyValueType == SgfcPropertyValueType::Move)
          {
            auto movePropertyValue = singlePropertyValue->ToMoveValue();
            if (movePropertyValue->ToGoMoveValue() != nullptr)
              valueToEncodeNeedsEscaping = false;
          }
          else
          {
            auto stonePropertyValue = singlePropertyValue->ToStoneValue();
            if (stonePropertyValue->ToGoStoneValue() != nullptr)
              valueToEncodeNeedsEscaping = false;
          }
        }

        if (valueToEncodeNeedsEscaping)
          sgfContentStream << AddMandatoryEscapeCharacters(valueToEncode, singlePropertyValueContext);
        else
          sgfContentStream << valueToEncode;

        break;
      }

      // All other value types have strict requirements and don't need
      // escaping.
      // - If the property value object was created programmatically then the
      //   raw value was created by libsgfc++ and cannot contain any errors
      //   because the factory strictly allows only good values. The raw value
      //   is therefore good to pass to SGFC for writing.
      // - If the property value object was created internally by ligsgfc++
      //   during reading of SGF content, then the raw value is what SGFC passed
      //   on to libsgfc++ after performing error corrections. That should also
      //   be good enough to pass to SGFC for writing. Any errors in the
      //   original SGF content that SGFC passed on to libsgfc++ can now be
      //   passed back to SGFC, as that is what would have happened had the SGF
      //   content been read+written by SGFC on the command line.
      default:
      {
        sgfContentStream << singlePropertyValue->GetRawValue();
        break;
      }
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

  std::string SgfcDocumentEncoder::AddSimpleTextAndTextEscapeCharacters(
    const std::string& propertyValue,
    SgfcSinglePropertyValueContext singlePropertyValueContext) const
  {
    // Escape characters already present must be escaped first so that we don't
    // escape the escape characters from other escape sequences.
    std::string result = std::regex_replace(
      propertyValue,
      SgfcPrivateConstants::UnescapedEscapeCharacterRegex,
      SgfcPrivateConstants::EscapedEscapeCharacterToken);

    return AddMandatoryEscapeCharacters(result, singlePropertyValueContext);
  }

  std::string SgfcDocumentEncoder::AddMandatoryEscapeCharacters(
    const std::string& propertyValue,
    SgfcSinglePropertyValueContext singlePropertyValueContext) const
  {
    std::string result = std::regex_replace(
      propertyValue,
      SgfcPrivateConstants::UnescapedPropertyValueEndTokenRegex,
      SgfcPrivateConstants::EscapedPropertyValueEndToken);

    switch (singlePropertyValueContext)
    {
      case SgfcSinglePropertyValueContext::FirstValueOfComposedValue:
      {
        return std::regex_replace(
          result,
          SgfcPrivateConstants::UnescapedComposedValueSeparatorTokenRegex,
          SgfcPrivateConstants::EscapedComposedValueSeparatorToken);
      }
      case SgfcSinglePropertyValueContext::SecondValueOfComposedValue:
      case SgfcSinglePropertyValueContext::Standalone:
      default:
      {
        return result;
      }
    }
  }
}
