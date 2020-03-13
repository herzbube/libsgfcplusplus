#pragma once

// Project includes
#include "ISgfcCommandLine.h"
#include "ISgfcDocumentReader.h"
#include "ISgfcDocumentWriter.h"

// C++ Standard Library includes
#include <memory>
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcCommandLine;
  class ISgfcPropertyValueFactory;

  /// @brief The SgfcPlusPlusFactory class is a class that contains only static
  /// functions. The functions are used to construct various library objects.
  class SgfcPlusPlusFactory
  {
  public:
    /// @brief Returns a newly constructed ISgfcCommandLine object that passes
    /// the specified command line arguments to SGFC.
    ///
    /// @param arguments The command line arguments to pass to SGFC, exactly
    /// as you would specify them on the command line. Invoke the
    /// ISgfcCommandLine::IsCommandLineValid() method on the resulting object
    /// to find out whether the arguments are valid.
    ///
    /// @todo Specify arguments with types instead of with std::string.
    static std::shared_ptr<ISgfcCommandLine> CreateSgfcCommandLine(
      const std::vector<std::string>& arguments);

    /// @brief Returns a newly constructed ISgfcCommandLine object that passes
    /// no command line arguments to SGFC.
    static std::shared_ptr<ISgfcCommandLine> CreateSgfcCommandLine();

    /// @brief Returns a newly constructed ISgfcDocumentReader object.
    static std::shared_ptr<ISgfcDocumentReader> CreateDocumentReader();

    /// @brief Returns a newly constructed ISgfcDocumentWriter object.
    static std::shared_ptr<ISgfcDocumentWriter> CreateDocumentWriter();

    /// @brief Returns a newly constructed ISgfcDocument object. The
    /// ISgfcDocument is empty and contains no games.
    static std::shared_ptr<ISgfcDocument> CreateDocument();

    /// @brief Returns a newly constructed ISgfcDocument object. The
    /// ISgfcDocument content consists of the specified game @a game. The
    /// ISgfcDocument object takes ownership of @a game.
    static std::shared_ptr<ISgfcDocument> CreateDocument(std::shared_ptr<ISgfcGame> game);

    /// @brief Returns a newly constructed ISgfcGame object. The game type is
    /// SgfcGameType::Unknown. The game is not associated with any document.
    /// The game has no game tree.
    static std::shared_ptr<ISgfcGame> CreateGame();

    /// @brief Returns a newly constructed ISgfcGame object. The game tree's
    /// root node is @a rootNode. The game type depends on the content of the
    /// root node. The game is not associated with any document. The ISgfcGame
    /// object takes ownership of @a rootNode.
    static std::shared_ptr<ISgfcGame> CreateGame(std::shared_ptr<ISgfcNode> rootNode);

    /// @brief Returns a newly constructed ISgfcNode object that has no parent,
    /// child or sibling and is not associated with any game.
    static std::shared_ptr<ISgfcNode> CreateNode();

    /// @brief Returns a newly constructed ISgfcNode object that is a child node
    /// of @a parentNode. The node is appended as the last child to @a parent.
    static std::shared_ptr<ISgfcNode> CreateChildNode(std::shared_ptr<ISgfcNode> parentNode);

    /// @brief Returns a newly constructed ISgfcProperty object that has the
    /// specified property type @a propertyType. The property has no values.
    /// The property is not associated with any node.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyType is
    /// SgfcPropertyType::Unknown.
    static std::shared_ptr<ISgfcProperty> CreateProperty(SgfcPropertyType propertyType);

    /// @brief Returns a newly constructed ISgfcProperty object that has the
    /// specified property type @a propertyType and the specified property
    /// values @a propertyValues. The property is not associated with any node.
    /// The ISgfcProperty object takes ownership of the ISgfcPropertyValue
    /// objects in @a propertyValues.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyType is
    /// SgfcPropertyType::Unknown.
    static std::shared_ptr<ISgfcProperty> CreateProperty(
      SgfcPropertyType propertyType,
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);

    /// @brief Returns a newly constructed ISgfcProperty object that has the
    /// specified property name @a propertyName. The property type is inferred
    /// from the property name. The property has no values. The property is not
    /// associated with any node.
    ///
    /// Attempts to map @a propertyName to a value in the enumeration
    /// SgfcPropertyType. If the mapping succeeds the result of invoking this
    /// method is the same as invoking the overload that takes an
    /// SgfcPropertyType value. If the mapping fails then the resulting
    /// ISgfcProperty object has SgfcPropertyType::Unknown.
    static std::shared_ptr<ISgfcProperty> CreateProperty(const std::string& propertyName);

    /// @brief Returns a newly constructed ISgfcProperty object that has the
    /// specified property name @a propertyName and the specified property
    /// values @a propertyValues. The property type is inferred from the
    /// property name. The property is not associated with any node.
    /// The ISgfcProperty object takes ownership of the ISgfcPropertyValue
    /// objects in @a propertyValues.
    ///
    /// Attempts to map @a propertyName to a value in the enumeration
    /// SgfcPropertyType. If the mapping succeeds the result of invoking this
    /// method is the same as invoking the overload that takes an
    /// SgfcPropertyType value. If the mapping fails then the resulting
    /// ISgfcProperty object has SgfcPropertyType::Unknown.
    static std::shared_ptr<ISgfcProperty> CreateProperty(
      const std::string& propertyName,
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);

    /// @brief Returns a newly constructed ISgfcPropertyValueFactory object
    /// that can be used to create objects of every known sub-type of
    /// ISgfcPropertyValue.
    static std::shared_ptr<ISgfcPropertyValueFactory> CreatePropertyValueFactory();

  private:
    SgfcPlusPlusFactory();
    ~SgfcPlusPlusFactory();
  };
}
