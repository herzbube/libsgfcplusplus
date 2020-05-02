// Project includes
#include "../../include/SgfcPlusPlusFactory.h"
#include "../document/SgfcDocument.h"
#include "../document/SgfcGame.h"
#include "../document/SgfcNode.h"
#include "../document/SgfcTreeBuilder.h"
#include "../sgfc/frontend/SgfcCommandLine.h"
#include "../sgfc/frontend/SgfcDocumentReader.h"
#include "../sgfc/frontend/SgfcDocumentWriter.h"
#include "SgfcPropertyFactory.h"
#include "SgfcPropertyValueFactory.h"

// C++ Standard Library includes
#include <stdexcept>

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
    if (game == nullptr)
      throw std::invalid_argument("SgfcPlusPlusFactory::CreateDocument failed: Game is nullptr");

    std::shared_ptr<ISgfcDocument> document = CreateDocument();
    document->AppendGame(game);
    return document;
  }

  std::shared_ptr<ISgfcGame> SgfcPlusPlusFactory::CreateGame()
  {
    std::shared_ptr<SgfcGame> game = std::shared_ptr<SgfcGame>(new SgfcGame());

    std::shared_ptr<ISgfcTreeBuilder> treeBuilder =
      std::shared_ptr<ISgfcTreeBuilder>(new SgfcTreeBuilder(game));
    game->SetTreeBuilder(treeBuilder);

    return game;
  }

  std::shared_ptr<ISgfcGame> SgfcPlusPlusFactory::CreateGame(std::shared_ptr<ISgfcNode> rootNode)
  {
    if (rootNode == nullptr)
      throw std::invalid_argument("SgfcPlusPlusFactory::CreateGame failed: Root node is nullptr");

    auto game = CreateGame();

    game->SetRootNode(rootNode);

    return game;
  }

  std::shared_ptr<ISgfcNode> SgfcPlusPlusFactory::CreateNode()
  {
    std::shared_ptr<ISgfcNode> node = std::shared_ptr<ISgfcNode>(new SgfcNode());
    return node;
  }

  std::shared_ptr<ISgfcPropertyFactory> SgfcPlusPlusFactory::CreatePropertyFactory()
  {
    std::shared_ptr<ISgfcPropertyFactory> factory = std::shared_ptr<ISgfcPropertyFactory>(
      new SgfcPropertyFactory());
    return factory;
  }

  std::shared_ptr<ISgfcPropertyValueFactory> SgfcPlusPlusFactory::CreatePropertyValueFactory()
  {
    std::shared_ptr<ISgfcPropertyValueFactory> factory = std::shared_ptr<ISgfcPropertyValueFactory>(
      new SgfcPropertyValueFactory());
    return factory;
  }
}
