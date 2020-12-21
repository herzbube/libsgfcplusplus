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
#include "SgfcArgumentType.h"
#include "SgfcMessageID.h"
#include "SgfcPropertyType.h"

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

// C++ Standard Library includes
#include <memory>
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcArgument;

  /// @brief The ISgfcArguments interface represents a collection of arguments
  /// to be passed on to SGFC when it reads or writes SGF content.
  ///
  /// @ingroup public-api
  /// @ingroup sgfc-arguments
  class SGFCPLUSPLUS_EXPORT ISgfcArguments
  {
  public:
    /// @brief Initializes a newly constructed ISgfcArguments object.
    ISgfcArguments();

    /// @brief Destroys and cleans up the ISgfcArguments object.
    virtual ~ISgfcArguments();

    /// @brief Returns true if the ISgfcArguments object contains one or more
    /// arguments. Returns false if the ISgfcArguments object contains no
    /// arguments.
    virtual bool HasArguments() const = 0;

    /// @brief Returns a collection of arguments that make up the content of
    /// the ISgfcArguments object. The collection is ordered, beginning with the
    /// first argument that was added to the ISgfcArguments object. The
    /// collection is empty if the ISgfcArguments object contains no arguments.
    virtual std::vector<std::shared_ptr<ISgfcArgument>> GetArguments() const = 0;

    /// @brief Adds an argument to the end of the collection of arguments that
    /// make up the content of the ISgfcArguments object.
    ///
    /// @param argumentType The argument type.
    ///
    /// @exception std::invalid_argument is thrown if @a argumentType requires a
    /// parameter, or if the collection already contains an argument with the
    /// same type as @a argumentType.
    virtual void AddArgument(SgfcArgumentType argumentType) = 0;

    /// @brief Adds an argument to the end of the collection of arguments that
    /// make up the content of the ISgfcArguments object.
    ///
    /// @param argumentType The argument type.
    /// @param parameter The argument's integer type parameter.
    ///
    /// @exception std::invalid_argument is thrown if @a argumentType does not
    /// require an integer type parameter, or if @a argumentType does not
    /// support multiple specifications but the collection already contains an
    /// argument with the same type as @a argumentType, or if @a argumentType
    /// supports multiple specifications but the collection already contains an
    /// argument with an argument type / parameter combination that is equal to
    /// @a argumentType and @a parameter.
    virtual void AddArgument(SgfcArgumentType argumentType, int parameter) = 0;

    /// @brief Adds an argument to the end of the collection of arguments that
    /// make up the content of the ISgfcArguments object.
    ///
    /// @param argumentType The argument type.
    /// @param parameter The argument's string type parameter.
    ///
    /// @exception std::invalid_argument is thrown if @a argumentType does not
    /// require a string type parameter, or if @a argumentType does not
    /// support multiple specifications but the collection already contains an
    /// argument with the same type as @a argumentType, or if @a argumentType
    /// supports multiple specifications but the collection already contains an
    /// argument with an argument type / parameter combination that is equal to
    /// @a argumentType and @a parameter.
    virtual void AddArgument(SgfcArgumentType argumentType, const std::string& parameter) = 0;

    /// @brief Adds an argument to the end of the collection of arguments that
    /// make up the content of the ISgfcArguments object.
    ///
    /// @param argumentType The argument type.
    /// @param parameter The argument's SgfcPropertyType parameter.
    ///
    /// @exception std::invalid_argument is thrown if @a argumentType does not
    /// require an SgfcPropertyType parameter, or if @a argumentType does not
    /// support multiple specifications but the collection already contains an
    /// argument with the same type as @a argumentType, or if @a argumentType
    /// supports multiple specifications but the collection already contains an
    /// argument with an argument type / parameter combination that is equal to
    /// @a argumentType and @a parameter.
    virtual void AddArgument(SgfcArgumentType argumentType, SgfcPropertyType parameter) = 0;

    /// @brief Adds an argument to the end of the collection of arguments that
    /// make up the content of the ISgfcArguments object.
    ///
    /// @param argumentType The argument type.
    /// @param parameter The argument's SgfcMessageID parameter.
    ///
    /// @exception std::invalid_argument is thrown if @a argumentType does not
    /// require an SgfcMessageID parameter, or if @a argumentType does not
    /// support multiple specifications but the collection already contains an
    /// argument with the same type as @a argumentType, or if @a argumentType
    /// supports multiple specifications but the collection already contains an
    /// argument with an argument type / parameter combination that is equal to
    /// @a argumentType and @a parameter, or if @a parameter is a message ID
    /// not known to SGFC (libsgfc++ message IDs with an underlying negative
    /// numeric value, or #SgfcMessageID::UnknownSgfcMessageID).
    virtual void AddArgument(SgfcArgumentType argumentType, SgfcMessageID parameter) = 0;

    /// @brief Removes all arguments from the collection of arguments that make
    /// up the content of the ISgfcArguments object.
    virtual void ClearArguments() = 0;
  };
}
