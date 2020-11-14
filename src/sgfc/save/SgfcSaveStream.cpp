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
#include "SgfcSaveStream.h"
#include "SgfcSgfContent.h"

// SGFC includes
extern "C"
{
  #include "../../../sgfc/src/all.h"
  #include "../../../sgfc/src/protos.h"
}

namespace LibSgfcPlusPlus
{
  // ----------------------------------------------------------------------
  // Hook/callback function prototype used to interact with SGFC.
  // ----------------------------------------------------------------------

  int openHook(struct SaveFileHandler* sfh, const char* path, const char* mode);
  int closeHook(struct SaveFileHandler* sfh, U_LONG error);

  // ----------------------------------------------------------------------
  // Static variables used by the hook function to store the captured data.
  // ----------------------------------------------------------------------

  static std::vector<std::string> saveStreamFilePaths;
  static std::vector<std::string> saveStreamContents;

  // ----------------------------------------------------------------------
  // Other static variables
  // ----------------------------------------------------------------------

  static bool capturingIsInProgress = false;
  static int (*originalOpenHook)(struct SaveFileHandler *, const char *, const char *) = NULL;
  static int (*originalCloseHook)(struct SaveFileHandler *, U_LONG) = NULL;

  // ----------------------------------------------------------------------
  // The SgfcSaveStream class.
  // ----------------------------------------------------------------------

  SgfcSaveStream::SgfcSaveStream(SGFInfo* sgfInfo)
    : sgfInfo(sgfInfo)
  {
    if (sgfInfo == NULL)
      throw std::invalid_argument("SgfcSaveStream constructor failed: SGFInfo argument is null");

    if (capturingIsInProgress)
      throw std::logic_error("Another SgfcSaveStream object is already capturing the SGFC save stream");

    capturingIsInProgress = true;

    originalOpenHook = this->sgfInfo->sfh->open;
    originalCloseHook = this->sgfInfo->sfh->close;
    this->sgfInfo->sfh->open = openHook;
    this->sgfInfo->sfh->close = closeHook;

    saveStreamFilePaths.clear();
    saveStreamContents.clear();
  }

  SgfcSaveStream::~SgfcSaveStream()
  {
    this->sgfInfo->sfh->open = originalOpenHook;
    this->sgfInfo->sfh->close = originalCloseHook;

    saveStreamFilePaths.clear();
    saveStreamContents.clear();

    capturingIsInProgress = false;
  }

  std::vector<std::shared_ptr<SgfcSgfContent>> SgfcSaveStream::GetSgfContents() const
  {
    std::vector<std::shared_ptr<SgfcSgfContent>> sgfContents;

    auto itSaveStreamContents = saveStreamContents.cbegin();
    auto itSaveStreamFilePaths = saveStreamFilePaths.cbegin();

    // We know that the two vectors contain the same number of elements, in
    // matching order.
    while (itSaveStreamContents != saveStreamContents.cend() &&
           itSaveStreamFilePaths != saveStreamFilePaths.cend())
    {
      const std::string& saveStreamContent = *itSaveStreamContents;
      const std::string& saveStreamFilePath = *itSaveStreamFilePaths;

      std::shared_ptr<SgfcSgfContent> sgfContent = std::shared_ptr<SgfcSgfContent>(new SgfcSgfContent(
        saveStreamContent,
        saveStreamFilePath));

      // Preserve order in which SGFC generated SGF content
      sgfContents.push_back(sgfContent);

      ++itSaveStreamContents;
      ++itSaveStreamFilePaths;
    }

    return sgfContents;
  }

  int openHook(struct SaveFileHandler* sfh, const char* path, const char* mode)
  {
    saveStreamFilePaths.push_back(path);

    // Forward the call to the original open hook. It will take care of
    // initializing and allocating memory.
    return originalOpenHook(sfh, path, mode);
  }

  int closeHook(struct SaveFileHandler* sfh, U_LONG error)
  {
    if (error == E_NO_ERROR)
    {
      size_t contentLength = sfh->fh.memh.pos - sfh->fh.memh.buffer;
      std::string sgfContent = std::string(sfh->fh.memh.buffer, contentLength);
      saveStreamContents.push_back(sgfContent);
    }

    // Forward the call to the original close hook. It will take care of
    // cleaning up and freeing memory.
    return originalCloseHook(sfh, error);
  }
}
