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

#pragma once

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcArguments;
  class ISgfcCommandLine;
  class ISgfcDocument;
  class ISgfcDocumentReader;
  class ISgfcDocumentWriter;
  class ISgfcGame;
  class ISgfcNode;
  class ISgfcPropertyFactory;
  class ISgfcPropertyValueFactory;

  /// @brief The SgfcPlusPlusFactory class is a class that contains only static
  /// functions. The functions are used to construct various library objects.
  ///
  /// @ingroup public-api
  /// @ingroup factory
  class SGFCPLUSPLUS_EXPORT SgfcPlusPlusFactory
  {
  public:
    SgfcPlusPlusFactory() = delete;
    ~SgfcPlusPlusFactory() = delete;

    /// @brief Returns a newly constructed ISgfcArguments object that initially
    /// contains no arguments. Use the ISgfcArguments object's add methods to
    /// populate it with arguments.
    static std::shared_ptr<ISgfcArguments> CreateSgfcArguments();

    /// @brief Returns a newly constructed ISgfcCommandLine object that passes
    /// the specified command line arguments to SGFC.
    ///
    /// @param arguments The command line arguments to pass to SGFC. Invoke the
    /// ISgfcCommandLine::IsCommandLineValid() method on the resulting object
    /// to find out whether the arguments are valid.
    ///
    /// @note The content of @a arguments is copied, so if you change the
    /// content it will not affect the ISgfcCommandLine object returned from
    /// this method.
    static std::shared_ptr<ISgfcCommandLine> CreateSgfcCommandLine(
      std::shared_ptr<ISgfcArguments> arguments);

    /// @brief Returns a newly constructed ISgfcCommandLine object that passes
    /// no command line arguments to SGFC.
    static std::shared_ptr<ISgfcCommandLine> CreateSgfcCommandLine();

    /// @brief Returns a newly constructed ISgfcDocumentReader object.
    static std::shared_ptr<ISgfcDocumentReader> CreateDocumentReader();

    /// @brief Returns a newly constructed ISgfcDocumentWriter object.
    static std::shared_ptr<ISgfcDocumentWriter> CreateDocumentWriter();

    /// @brief Returns a newly constructed ISgfcDocument object. The
    /// ISgfcDocument content consists of a single ISgfcGame object with an
    /// empty root node.
    static std::shared_ptr<ISgfcDocument> CreateDocument();

    /// @brief Returns a newly constructed ISgfcDocument object. The
    /// ISgfcDocument content consists of the specified game @a game. The
    /// ISgfcDocument object takes ownership of @a game.
    ///
    /// @exception std::invalid_argument Is thrown if @a game is
    /// @e nullptr.
    static std::shared_ptr<ISgfcDocument> CreateDocument(std::shared_ptr<ISgfcGame> game);

    /// @brief Returns a newly constructed ISgfcGame object. The game type is
    /// SgfcConstants::DefaultGameType. The game is not associated with any
    /// document. The game has a game tree that consists of an empty root node.
    static std::shared_ptr<ISgfcGame> CreateGame();

    /// @brief Returns a newly constructed ISgfcGame object. The game tree's
    /// root node is @a rootNode. The game type depends on the content of the
    /// root node. The game is not associated with any document. The ISgfcGame
    /// object takes ownership of @a rootNode.
    ///
    /// @exception std::invalid_argument Is thrown if @a rootNode is
    /// @e nullptr.
    static std::shared_ptr<ISgfcGame> CreateGame(std::shared_ptr<ISgfcNode> rootNode);

    /// @brief Returns a newly constructed ISgfcNode object that has no parent,
    /// child or sibling and is not associated with any game.
    static std::shared_ptr<ISgfcNode> CreateNode();

    /// @brief Returns a newly constructed ISgfcPropertyFactory object
    /// that can be used to create ISgfcProperty objects, and objects of every
    /// known sub-type of ISgfcProperty.
    static std::shared_ptr<ISgfcPropertyFactory> CreatePropertyFactory();

    /// @brief Returns a newly constructed ISgfcPropertyValueFactory object
    /// that can be used to create ISgfcPropertyValue objects, and objects of
    /// every known sub-type of ISgfcPropertyValue.
    static std::shared_ptr<ISgfcPropertyValueFactory> CreatePropertyValueFactory();
  };
}
