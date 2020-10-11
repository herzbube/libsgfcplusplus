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
#include "SgfcBackendDataWrapper.h"

// SGFC includes
extern "C"
{
  #include <stdio.h>  // required to define size_t and FILE which are used in all.h
  #include "../../../sgfc/all.h"
  #include "../../../sgfc/protos.h"
}

// C++ Standard Library includes
#include <cstring>  // GCC insists on this for memset and memcpy

namespace LibSgfcPlusPlus
{
  SgfcBackendDataWrapper::SgfcBackendDataWrapper()
    : sgfData(new SGFInfo())
    , dataState(SgfcBackendDataState::NotLoaded)
  {
    // Immediately zero the struct so that FreeSGFInfo() inside the destructor
    // works. This is important in case the destructor runs immediately after
    // the constructor, without SGF content being generated.
    memset(this->sgfData, 0, sizeof(struct SGFInfo));
  }

  SgfcBackendDataWrapper::SgfcBackendDataWrapper(const std::string& sgfContent)
    : SgfcBackendDataWrapper()
  {
    InitializeFileBuffer(sgfContent);
    this->dataState = SgfcBackendDataState::PartiallyLoaded;
  }

  SgfcBackendDataWrapper::~SgfcBackendDataWrapper()
  {
    FreeSGFInfo(this->sgfData);
    delete this->sgfData;
    this->sgfData = 0;
  }

  SGFInfo* SgfcBackendDataWrapper::GetSgfData() const
  {
    return this->sgfData;
  }

  SgfcBackendDataState SgfcBackendDataWrapper::GetDataState() const
  {
    return this->dataState;
  }

  void SgfcBackendDataWrapper::SetDataState(SgfcBackendDataState dataState)
  {
    this->dataState = dataState;
  }

  /// @brief Sets up the SGFInfo object with a newly allocated buffer which
  /// duplicates the content of @a sgfContent.
  ///
  /// This method simulates that part of LoadSGF() which loads the entire
  /// .sgf file into memory and configures the SGFInfo structure with the
  /// resulting buffer.
  ///
  /// The state of the SGFInfo object when this method returns is incomplete.
  /// Someone needs to invoke LoadSGFFromFileBuffer() to bring the SGFInfo
  /// object into the state it normally has after LoadSGF(). The next step then
  /// usually is invoking ParseSGF().
  void SgfcBackendDataWrapper::InitializeFileBuffer(const std::string& sgfContent) const
  {
    size_t sgfContentSize = sgfContent.size();
    SaveMalloc(char *, sgfData->buffer, sgfContentSize, "source file buffer");

    memcpy(sgfData->buffer, sgfContent.c_str(), sgfContentSize);

    // Some implementations of malloc return nullptr when a zero-size buffer is
    // requested. In that case doing pointer arithmetic would be fatal, so
    // we avoid that.
    if (sgfContentSize > 0)
      sgfData->b_end = sgfData->buffer + sgfContentSize;
    else
      sgfData->b_end = sgfData->buffer;

    sgfData->current = sgfData->buffer;

    // sgfData->start will be set by LoadSGFFromFileBuffer
  }
}
