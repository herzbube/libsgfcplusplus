#pragma once

// C++ Standard Library includes
#include <memory>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcComposedPropertyValue;
  class ISgfcDocument;
  class ISgfcNode;
  class ISgfcProperty;
  class ISgfcPropertyValue;
  class ISgfcSinglePropertyValue;

  /// @brief The SgfcDocumentEncoder class encodes the content of an
  /// ISgfcDocument object into an in-memory string buffer that contains the
  /// SGF content stream as if it were read from an .sgf file, and that can be
  /// passed to SGFC for further processing (corrections and/or writing to an
  /// .sgf file in the filesystem).
  ///
  /// @ingroup internals
  /// @ingroup parsing
  ///
  /// Implementation note: SgfcDocumentEncoder formats the SGF content that it
  /// generates with indentation and line breaks to make the content human
  /// readable. It is expected that SGFC removes that whitespace when it parses
  /// the SGF content.
  class SgfcDocumentEncoder
  {
  public:
    /// @brief Initializes a newly constructed SgfcDocumentEncoder object. The
    /// object encodes the content of the specified @a document.
    SgfcDocumentEncoder(std::shared_ptr<ISgfcDocument> document);
    
    /// @brief Destroys and cleans up the SgfcDocumentEncoder object.
    virtual ~SgfcDocumentEncoder();

    /// @brief Returns a string that contains the SGF data generated by encoding
    /// the content of the document with which the SgfcDocumentEncoder was
    /// constructed.
    ///
    /// The resulting string can be used to construct an SgfcBackendDataWrapper
    /// object that can then be passed to SgfcBackendController for further
    /// processing by SGFC.
    ///
    /// This method can be invoked any amount of times. It will return a newly
    /// allocated string object on each invocation.
    ///
    /// @exception std::logic_error is thrown if the document with which the
    /// SgfcDocumentEncoder was constructed cannot be encoded into a string due
    /// to some fundamental error in the object tree. Currently the only known
    /// case is if the document contains one or more games that have no root
    /// node.
    std::string Encode() const;

  private:
    std::shared_ptr<ISgfcDocument> document;

    void RecursiveParseDepthFirst(
      std::shared_ptr<ISgfcNode> parentNode,
      std::stringstream& sgfContentStream,
      int indentationLevel) const;

    void EncodeNode(
      const ISgfcNode* node,
      std::stringstream& sgfContentStream,
      int indentationLevel) const;

    void EncodeProperty(
      const ISgfcProperty* property,
      std::stringstream& sgfContentStream,
      int indentationLevel) const;

    void EncodePropertyValue(
      const ISgfcPropertyValue* propertyValue,
      std::stringstream& sgfContentStream,
      int indentationLevel) const;

    void EncodeComposedPropertyValue(
      const ISgfcComposedPropertyValue* composedPropertyValue,
      std::stringstream& sgfContentStream,
      int indentationLevel) const;

    void EncodeSinglePropertyValue(
      const ISgfcSinglePropertyValue* singlePropertyValue,
      std::stringstream& sgfContentStream,
      int indentationLevel) const;

    void EncodeGameTreeBeginOrEnd(
      const std::string& beginOrEndToken,
      std::stringstream& sgfContentStream,
      int indentationLevel) const;

    void EncodeIndentation(
      int indentationLevel,
      std::stringstream& sgfContentStream) const;

    std::string AddSimpleTextAndTextEscapeCharacters(
      const std::string& propertyValue) const;
    std::string AddMandatoryEscapeCharacters(
      const std::string& propertyValue) const;
  };
}
