// Project includes
#include "../../include/SgfcConstants.h"
#include "../../include/SgfcPlusPlusFactory.h"
#include "../document/typedproperty/SgfcGameTypeProperty.h"
#include "../document/SgfcDocument.h"
#include "../document/SgfcGame.h"
#include "../document/SgfcNode.h"
#include "../document/SgfcProperty.h"
#include "../document/SgfcTreeBuilder.h"
#include "../sgfc/frontend/SgfcCommandLine.h"
#include "../sgfc/frontend/SgfcDocumentReader.h"
#include "../sgfc/frontend/SgfcDocumentWriter.h"
#include "../SgfcUtility.h"
#include "SgfcPropertyValueFactory.h"

namespace LibSgfcPlusPlus
{
  std::shared_ptr<LibSgfcPlusPlus::ISgfcCommandLine> SgfcPlusPlusFactory::CreateSgfcCommandLine(
    const std::vector<std::string>& arguments)
  {
    std::shared_ptr<ISgfcCommandLine> commandLine = std::shared_ptr<SgfcCommandLine>(new SgfcCommandLine(arguments));
    return commandLine;
  }

  std::shared_ptr<ISgfcCommandLine> SgfcPlusPlusFactory::CreateSgfcCommandLine()
  {
    std::vector<std::string> emptyArgumentList;
    return SgfcPlusPlusFactory::CreateSgfcCommandLine(emptyArgumentList);
  }

  std::shared_ptr<ISgfcDocumentReader> SgfcPlusPlusFactory::CreateDocumentReader()
  {
    std::shared_ptr<ISgfcDocumentReader> reader = std::shared_ptr<ISgfcDocumentReader>(new SgfcDocumentReader());
    return reader;
  }

  std::shared_ptr<ISgfcDocumentWriter> SgfcPlusPlusFactory::CreateDocumentWriter()
  {
    std::shared_ptr<ISgfcDocumentWriter> writer = std::shared_ptr<ISgfcDocumentWriter>(new SgfcDocumentWriter());
    return writer;
  }

  std::shared_ptr<ISgfcDocument> SgfcPlusPlusFactory::CreateDocument()
  {
    std::shared_ptr<ISgfcDocument> document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());
    return document;
  }

  std::shared_ptr<ISgfcDocument> SgfcPlusPlusFactory::CreateDocument(std::shared_ptr<ISgfcGame> game)
  {
    std::shared_ptr<ISgfcDocument> document = CreateDocument();
    document->AppendGame(game);
    return document;
  }

  std::shared_ptr<ISgfcGame> SgfcPlusPlusFactory::CreateGame()
  {
    return CreateGame(nullptr);
  }

  std::shared_ptr<ISgfcGame> SgfcPlusPlusFactory::CreateGame(std::shared_ptr<ISgfcNode> rootNode)
  {
    std::shared_ptr<SgfcGame> game = std::shared_ptr<SgfcGame>(new SgfcGame(rootNode));

    std::shared_ptr<ISgfcTreeBuilder> treeBuilder =
      std::shared_ptr<ISgfcTreeBuilder>(new SgfcTreeBuilder(game));
    game->SetTreeBuilder(treeBuilder);

    return game;
  }

  std::shared_ptr<ISgfcNode> SgfcPlusPlusFactory::CreateNode()
  {
    std::shared_ptr<ISgfcNode> node = std::shared_ptr<ISgfcNode>(new SgfcNode());
    return node;
  }

  std::shared_ptr<ISgfcNode> SgfcPlusPlusFactory::CreateChildNode(std::shared_ptr<ISgfcNode> parentNode)
  {
    std::shared_ptr<ISgfcNode> node = std::shared_ptr<ISgfcNode>(new SgfcNode());
    return node;
  }

  std::shared_ptr<ISgfcProperty> SgfcPlusPlusFactory::CreateProperty(SgfcPropertyType propertyType)
  {
    std::shared_ptr<ISgfcProperty> property = CreateProperty(
      propertyType,
      std::vector<std::shared_ptr<ISgfcPropertyValue>> {} );

    return property;
  }

  std::shared_ptr<ISgfcProperty> SgfcPlusPlusFactory::CreateProperty(
    SgfcPropertyType propertyType,
    std::shared_ptr<ISgfcPropertyValue> propertyValue)
  {
    std::shared_ptr<ISgfcProperty> property = CreateProperty(
      propertyType,
      std::vector<std::shared_ptr<ISgfcPropertyValue>> { propertyValue } );

    return property;
  }

  std::shared_ptr<ISgfcProperty> SgfcPlusPlusFactory::CreateProperty(
    SgfcPropertyType propertyType,
    const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
  {
    std::string propertyName = SgfcUtility::MapPropertyTypeToPropertyName(propertyType);

    std::shared_ptr<ISgfcProperty> property = CreateProperty(
      propertyType,
      propertyName,
      propertyValues);

    return property;
  }

  std::shared_ptr<ISgfcProperty> SgfcPlusPlusFactory::CreateProperty(const std::string& propertyName)
  {
    std::shared_ptr<ISgfcProperty> property = CreateProperty(
      propertyName,
      std::vector<std::shared_ptr<ISgfcPropertyValue>> {} );

    return property;
  }

  std::shared_ptr<ISgfcProperty> SgfcPlusPlusFactory::CreateProperty(
    const std::string& propertyName,
    std::shared_ptr<ISgfcPropertyValue> propertyValue)
  {
    std::shared_ptr<ISgfcProperty> property = CreateProperty(
      propertyName,
      std::vector<std::shared_ptr<ISgfcPropertyValue>> { propertyValue } );

    return property;
  }

  std::shared_ptr<ISgfcProperty> SgfcPlusPlusFactory::CreateProperty(
    const std::string& propertyName,
    const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
  {
    SgfcPropertyType propertyType = SgfcUtility::MapPropertyNameToPropertyType(propertyName);

    std::shared_ptr<ISgfcProperty> property = CreateProperty(
      propertyType,
      propertyName,
      propertyValues);

    return property;
  }

  std::shared_ptr<ISgfcGameTypeProperty> SgfcPlusPlusFactory::CreateGameTypeProperty()
  {
    std::shared_ptr<ISgfcGameTypeProperty> property =
      std::shared_ptr<ISgfcGameTypeProperty>(new SgfcGameTypeProperty());

    return property;
  }

  std::shared_ptr<ISgfcGameTypeProperty> SgfcPlusPlusFactory::CreateGameTypeProperty(
    std::shared_ptr<ISgfcNumberPropertyValue> propertyValue)
  {
    std::shared_ptr<ISgfcGameTypeProperty> property =
      std::shared_ptr<ISgfcGameTypeProperty>(new SgfcGameTypeProperty(propertyValue));

    return property;
  }

  std::shared_ptr<ISgfcProperty> SgfcPlusPlusFactory::CreateProperty(
    SgfcPropertyType propertyType,
    const std::string& propertyName,
    const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues)
  {
    std::shared_ptr<ISgfcProperty> property = std::shared_ptr<ISgfcProperty>(new SgfcProperty(
      propertyType,
      propertyName));

    property->SetPropertyValues(propertyValues);

    return property;
  }

  std::shared_ptr<ISgfcPropertyValueFactory> SgfcPlusPlusFactory::CreatePropertyValueFactory()
  {
    std::shared_ptr<ISgfcPropertyValueFactory> factory = std::shared_ptr<ISgfcPropertyValueFactory>(
      new SgfcPropertyValueFactory());
    return factory;
  }
}
