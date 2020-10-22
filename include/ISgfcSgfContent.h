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
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcSgfContent interface represents a distinct piece of SGF
  /// content that is generated by SGFC when it performs a save operation.
  /// ISgfcSgfContent objects are immutable.
  ///
  /// @ingroup public-api
  class SGFCPLUSPLUS_EXPORT ISgfcSgfContent
  {
  public:
    /// @brief Initializes a newly constructed ISgfcSgfContent object.
    ISgfcSgfContent();

    /// @brief Destroys and cleans up the ISgfcSgfContent object.
    virtual ~ISgfcSgfContent();

    /// @brief Returns the SGF content.
    virtual std::string GetSgfContent() const = 0;

    /// @brief Returns the file name that SGFC would have used to save the SGF
    /// content to the filesystem.
    virtual std::string GetFileName() const = 0;
  };
}
