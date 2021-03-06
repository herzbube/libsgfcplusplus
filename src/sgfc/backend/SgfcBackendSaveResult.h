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
#include "../../../include/ISgfcMessage.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcBackendSaveResult class provides access to the result of
  /// a save operation performed by SgfcBackendController.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-backend
  class SgfcBackendSaveResult
  {
  public:
    /// @brief Initializes a newly constructed SgfcBackendSaveResult object
    /// with the specified results.
    SgfcBackendSaveResult(
      std::vector<std::shared_ptr<ISgfcMessage>> saveResult);

    /// @brief Destroys and cleans up the SgfcBackendSaveResult object.
    virtual ~SgfcBackendSaveResult();

    /// @brief Returns a collection of ISgfcMessage objects which together form
    /// the result of the save operation. The messages appear in the order in
    /// which they were generated by SGFC.
    std::vector<std::shared_ptr<ISgfcMessage>> GetSaveResult() const;

  private:
    std::vector<std::shared_ptr<ISgfcMessage>> saveResult;
  };
}
