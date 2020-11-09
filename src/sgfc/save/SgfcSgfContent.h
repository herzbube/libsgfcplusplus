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
#include "../../../include/ISgfcSgfContent.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcSgfContent class provides an implementation of the
  /// ISgfcSgfContent interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-backend
  class SgfcSgfContent : public ISgfcSgfContent
  {
  public:
    /// @brief Initializes a newly constructed SgfcSgfContent object. The object
    /// has no SGF content.
    SgfcSgfContent();

    /// @brief Initializes a newly constructed SgfcSgfContent object. The object
    /// has the SGF content @a sgfContent, SGFC would have used @a filePath to
    /// save the SGF content to the filesystem.
    SgfcSgfContent(
      const std::string& sgfContent,
      const std::string& filePath);

    /// @brief Destroys and cleans up the SgfcSgfContent object.
    virtual ~SgfcSgfContent();
  
    virtual std::string GetSgfContent() const;
    virtual std::string GetFilePath() const;

  private:
    std::string sgfContent;
    std::string filePath;
  };
}
