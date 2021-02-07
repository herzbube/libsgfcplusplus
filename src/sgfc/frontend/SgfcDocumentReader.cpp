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
#include "../../../include/ISgfcGame.h"
#include "../../../include/ISgfcNode.h"
#include "../../../include/ISgfcProperty.h"
#include "../../../include/ISgfcPropertyFactory.h"
#include "../../../include/ISgfcPropertyValueFactory.h"
#include "../../../include/ISgfcSimpleTextPropertyValue.h"
#include "../../../include/SgfcPlusPlusFactory.h"
#include "../../document/SgfcDocument.h"
#include "../../SgfcPrivateConstants.h"
#include "../../SgfcUtility.h"
#include "../argument/SgfcArgument.h"
#include "../argument/SgfcArguments.h"
#include "../backend/SgfcBackendController.h"
#include "../message/SgfcMessage.h"
#include "SgfcDocumentReader.h"
#include "SgfcDocumentReadResult.h"

// C++ Standard Library includes
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcDocumentReader::SgfcDocumentReader()
    : arguments(new SgfcArguments())
  {
  }

  SgfcDocumentReader::~SgfcDocumentReader()
  {
  }

  std::shared_ptr<ISgfcArguments> SgfcDocumentReader::GetArguments() const
  {
    return this->arguments;
  }

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::ReadSgfFile(const std::string& sgfFilePath) const
  {
    std::string sgfContent;
    return ReadSgfContentFromFilesystemOrInMemoryBuffer(sgfFilePath, sgfContent, SgfcDataLocation::Filesystem);
  }

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::ReadSgfContent(const std::string& sgfContent) const
  {
    std::string sgfFilePath;
    return ReadSgfContentFromFilesystemOrInMemoryBuffer(sgfFilePath, sgfContent, SgfcDataLocation::InMemoryBuffer);
  }

  std::shared_ptr<ISgfcDocumentReadResult> SgfcDocumentReader::ReadSgfContentFromFilesystemOrInMemoryBuffer(
    const std::string& sgfFilePath,
    const std::string& sgfContent,
    SgfcDataLocation dataLocation) const
  {
    SgfcBackendController backendController(this->arguments->GetArguments());
    if (backendController.IsCommandLineValid())
    {
      std::shared_ptr<SgfcBackendLoadResult> backendLoadResult;
      if (dataLocation == SgfcDataLocation::Filesystem)
        backendLoadResult = backendController.LoadSgfFile(sgfFilePath);
      else
        backendLoadResult = backendController.LoadSgfContent(sgfContent);

      SgfcExitCode sgfcExitCode = SgfcUtility::GetSgfcExitCodeFromMessageCollection(
        backendLoadResult->GetParseResult());

      auto parseResult = backendLoadResult->GetParseResult();

      std::shared_ptr<ISgfcDocument> document;
      if (sgfcExitCode == SgfcExitCode::FatalError)
      {
        document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());
      }
      else
      {
        try
        {
          document = std::shared_ptr<ISgfcDocument>(new SgfcDocument(backendLoadResult->GetSgfDataWrapper()->GetSgfData()));
        }
        catch (std::invalid_argument& exception)
        {
          document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());
          parseResult.push_back(std::shared_ptr<ISgfcMessage>(new SgfcMessage(
            SgfcMessageID::ParseSgfContentError,
            exception.what())));
        }
        catch (std::domain_error& exception)
        {
          document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());
          parseResult.push_back(std::shared_ptr<ISgfcMessage>(new SgfcMessage(
            SgfcMessageID::SGFCInterfacingError,
            exception.what())));
        }
      }

      PostProcessDocument(document);

      std::shared_ptr<ISgfcDocumentReadResult> result = std::shared_ptr<ISgfcDocumentReadResult>(new SgfcDocumentReadResult(
        parseResult,
        document));
      return result;
    }
    else
    {
      std::shared_ptr<ISgfcDocumentReadResult> result = std::shared_ptr<ISgfcDocumentReadResult>(new SgfcDocumentReadResult(
        backendController.GetInvalidCommandLineReason()));
      return result;
    }
  }

  void SgfcDocumentReader::PostProcessDocument(std::shared_ptr<ISgfcDocument> document) const
  {
    for (auto argument : this->arguments->GetArguments())
    {
      if (argument->GetArgumentType() == SgfcArgumentType::EncodingMode &&
          argument->GetIntegerTypeParameter() == SgfcPrivateConstants::EncodingModeNoDecoding)
      {
        return;
      }
    }

    auto propertyValueFactory = SgfcPlusPlusFactory::CreatePropertyValueFactory();
    auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();

    for (auto game : document->GetGames())
    {
      if (! game->HasRootNode())
        continue;

      auto rootNode = game->GetRootNode();

      // Create a new property/property value object for each game tree
      auto caPropertyValue = propertyValueFactory->CreateSimpleTextPropertyValue(SgfcPrivateConstants::TextEncodingNameUTF8);
      auto caProperty = propertyFactory->CreateProperty(SgfcPropertyType::CA, caPropertyValue);

      // This overwrites a CA property that is already there and adds the
      // property if it does not exist
      rootNode->SetProperty(caProperty);
    }
  }
}
