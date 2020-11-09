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
  #include "../../../sgfc/src/all.h"
  #include "../../../sgfc/src/protos.h"
}

// C++ Standard Library includes
#include <cstring>  // for memset() and memcpy()

namespace LibSgfcPlusPlus
{
  SgfcBackendDataWrapper::SgfcBackendDataWrapper()
    : sgfData(NULL)
    , dataState(SgfcBackendDataState::NotLoaded)
  {
    // SetupSGFInfo() and SetupSaveBufferIO() both throw std::runtime_error if
    // they fail to allocate memory.
    //
    // We set the SGFInfo object up so that any save operations will save the
    // SGF data to a memory buffer. Although it's possible to pass a close
    // hook/callback to SetupSaveBufferIO(), we specify NULL here because we
    // don't know the hook/callback that will be used eventually. Someone else
    // will have to reconfigure the SGFInfo object accordingly.
    this->sgfData = SetupSGFInfo(NULL, SetupSaveBufferIO(NULL));
  }

  SgfcBackendDataWrapper::SgfcBackendDataWrapper(const std::string& sgfContent)
    : SgfcBackendDataWrapper()
  {
    InitializeFileBuffer(sgfContent);
    this->dataState = SgfcBackendDataState::PartiallyLoaded;
  }

  SgfcBackendDataWrapper::~SgfcBackendDataWrapper()
  {
    if (this->sgfData)
    {
      FreeSGFInfo(this->sgfData);
      this->sgfData = 0;
    }
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
    this->sgfData->buffer = (char *) malloc((size_t) sgfContentSize);

    memcpy(this->sgfData->buffer, sgfContent.c_str(), sgfContentSize);

    // Some implementations of malloc return nullptr when a zero-size buffer is
    // requested. In that case doing pointer arithmetic would be fatal, so
    // we avoid that.
    if (sgfContentSize > 0)
      sgfData->b_end = sgfData->buffer + sgfContentSize;
    else
      sgfData->b_end = sgfData->buffer;

    // sgfData->current and sgfData->start will both be set by
    // LoadSGFFromFileBuffer
  }
}
