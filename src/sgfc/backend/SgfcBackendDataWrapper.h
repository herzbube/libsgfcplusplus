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

// Project includes
#include "SgfcBackendDataState.h"

// C++ Standard Library includes
#include <string>

// Forward declarations
struct SGFInfo;

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcBackendDataWrapper class is a wrapper around the SGFInfo
  /// data structure that is defined by the SGFC backend. SgfcBackendDataWrapper
  /// is responsible for managing the memory of an SGFInfo object.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-backend
  ///
  /// When SgfcBackendDataWrapper is constructed it immediately allocates
  /// the memory for a basic empty SGFInfo object that does not contain any
  /// data yet.
  ///
  /// While SgfcBackendDataWrapper lives, clients can access the SGFInfo object
  /// for the following purposes:
  /// - Only once: Pass the SGFInfo object to the SGFC backend for a load
  ///   operation. The SGFC backend will populate the SGFInfo object with
  ///   further data structures that contain the SGF data it loaded.
  ///   SgfcBackendDataWrapper becomes responsible for deallocating these
  ///   further data structures.
  /// - Any amount of times: Parse the SGFInfo object after it was populated
  ///   by an SGFC backend load operation.
  /// - Only once: Populate the empty SGFInfo object with data structures that
  ///   contain the SGF data to be passed to SGFC for writing.
  ///   SgfcBackendDataWrapper becomes responsible for deallocating the data
  ///   structures.
  /// - Only once: Pass the SGFInfo object to the SGFC backend for a save
  ///   operation. The SGFC backend will modify some of the data in the SGFInfo
  ///   object, so parsing the object before and after a save operation will
  ///   yield different results.
  ///
  /// When SgfcBackendDataWrapper is destroyed, it deallocates all memory
  /// that is currently occupied by the SGFInfo object. It doesn't matter
  /// whether an SGFC backend load and/or save operation have been performed
  /// since construction.
  class SgfcBackendDataWrapper
  {
  public:
    /// @brief Initializes a newly constructed SgfcBackendDataWrapper object
    /// that wraps an empty SGFInfo data structure. SGFC save operations that
    /// use the SGFInfo object will write data to a memory buffer. The data
    /// state is SgfcBackendDataState::NotLoaded.
    SgfcBackendDataWrapper();

    /// @brief Initializes a newly constructed SgfcBackendDataWrapper object
    /// that wraps an SGFInfo data structure that contains a file buffer with
    /// a duplicate of the content of @a sgfContent. SGFC save operations that
    /// use the SGFInfo object will write data to a memory buffer. The data
    /// state is SgfcBackendDataState::PartiallyLoaded.
    SgfcBackendDataWrapper(const std::string& sgfContent);

    /// @brief Destroys and cleans up the SgfcBackendDataWrapper object.
    virtual ~SgfcBackendDataWrapper();

    /// @brief Returns a pointer to the SGFInfo data object that the
    /// SgfcBackendDataWrapper encapsulates.
    SGFInfo* GetSgfData() const;

  private:
    SGFInfo* sgfData;
    SgfcBackendDataState dataState;

    void InitializeFileBuffer(const std::string& sgfContent) const;

    friend class SgfcBackendController;
    SgfcBackendDataState GetDataState() const;
    void SetDataState(SgfcBackendDataState dataState);
  };
}
