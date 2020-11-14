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
#include "../../document/SgfcDocument.h"
#include "../../SgfcUtility.h"
#include "../argument/SgfcArguments.h"
#include "../backend/SgfcBackendController.h"
#include "SgfcDocumentReader.h"
#include "SgfcDocumentReadResult.h"

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

      std::shared_ptr<ISgfcDocument> document;
      if (sgfcExitCode != SgfcExitCode::FatalError)
        document = std::shared_ptr<ISgfcDocument>(new SgfcDocument(backendLoadResult->GetSgfDataWrapper()->GetSgfData()));
      else
        document = std::shared_ptr<ISgfcDocument>(new SgfcDocument());

      std::shared_ptr<ISgfcDocumentReadResult> result = std::shared_ptr<ISgfcDocumentReadResult>(new SgfcDocumentReadResult(
        backendLoadResult->GetParseResult(),
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
}
