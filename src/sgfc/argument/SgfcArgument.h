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
#include "../../../include/ISgfcArgument.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcArgument class provides an implementation of the
  /// ISgfcArgument interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-arguments
  class SgfcArgument : public ISgfcArgument
  {
  public:
    /// @brief Initializes a newly constructed SgfcArgument object with the
    /// type @a argumentType.
    ///
    /// @exception std::invalid_argument is thrown if @a argumentType requires
    /// a parameter.
    SgfcArgument(SgfcArgumentType argumentType);

    /// @brief Initializes a newly constructed SgfcArgument object with the
    /// type @a argumentType and the integer type parameter @a parameter.
    ///
    /// @exception std::invalid_argument is thrown if @a argumentType does not
    /// require an integer type parameter.
    SgfcArgument(SgfcArgumentType argumentType, int parameter);

    /// @brief Initializes a newly constructed SgfcArgument object with the
    /// type @a argumentType and the SgfcPropertyType parameter @a parameter.
    ///
    /// @exception std::invalid_argument is thrown if @a argumentType does not
    /// require an SgfcPropertyType parameter.
    SgfcArgument(SgfcArgumentType argumentType, SgfcPropertyType parameter);

    /// @brief Destroys and cleans up the SgfcArgument object.
    virtual ~SgfcArgument();

    virtual SgfcArgumentType GetArgumentType() const override;
    virtual bool HasIntegerTypeParameter() const override;
    virtual int GetIntegerTypeParameter() const override;
    virtual bool HasPropertyTypeParameter() const override;
    virtual SgfcPropertyType GetPropertyTypeParameter() const override;
    virtual std::string ToString() const override;

  private:
    SgfcArgumentType argumentType;
    bool hasIntegerTypeParameter;
    int integerTypeParameter;
    bool hasPropertyTypeParameter;
    SgfcPropertyType propertyTypeParameter;
  };
}
