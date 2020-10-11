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
#include "../../../include/ISgfcArguments.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcArguments class provides an implementation of the
  /// ISgfcArguments interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-arguments
  class SgfcArguments : public ISgfcArguments
  {
  public:
    /// @brief Initializes a newly constructed SgfcArguments object that
    /// contains no arguments.
    SgfcArguments();

    /// @brief Destroys and cleans up the SgfcArguments object.
    virtual ~SgfcArguments();

    virtual bool HasArguments() const;
    virtual std::vector<std::shared_ptr<ISgfcArgument>> GetArguments() const;

    virtual void AddArgument(SgfcArgumentType argumentType);
    virtual void AddArgument(SgfcArgumentType argumentType, int parameter);
    virtual void AddArgument(SgfcArgumentType argumentType, SgfcPropertyType parameter);

    virtual void ClearArguments();

  private:
    std::vector<std::shared_ptr<ISgfcArgument>> arguments;

    bool ArgumentTypeCanBeAddedMultipleTimes(SgfcArgumentType argumentType) const;
    void ThrowIfMultiplicityViolated(SgfcArgumentType argumentType);
    template <typename T, typename FType>
    void ThrowIfMultiplicityViolated(SgfcArgumentType argumentType, T parameter, FType ParameterValueGetter);
  };
}
