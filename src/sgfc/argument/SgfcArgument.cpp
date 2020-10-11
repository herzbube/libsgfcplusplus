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
#include "../../SgfcUtility.h"
#include "SgfcArgument.h"

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcArgument::SgfcArgument(SgfcArgumentType argumentType)
    : argumentType(argumentType)
    , hasIntegerTypeParameter(false)
    , integerTypeParameter(-1)
    , hasPropertyTypeParameter(false)
    , propertyTypeParameter(SgfcPropertyType::Unknown)
  {
    switch (argumentType)
    {
      case SgfcArgumentType::DisableWarningMessages:
      case SgfcArgumentType::LineBreakAtEndOfNode:
      case SgfcArgumentType::NoSoftLineBreaksInTextValues:
      case SgfcArgumentType::DeleteMarkupOnCurrentMove:
      case SgfcArgumentType::DeleteEmptyNodes:
      case SgfcArgumentType::DeleteObsoleteProperties:
      case SgfcArgumentType::DeleteUnknownProperties:
      case SgfcArgumentType::UseOldPassMoveNotation:
      case SgfcArgumentType::EnableRestrictiveChecking:
      case SgfcArgumentType::CorrectVariationLevelAndRootMoves:
      case SgfcArgumentType::ReverseVariationOrdering:
      case SgfcArgumentType::ExpandCompressedPointLists:
        break;
      default:
        std::stringstream message;
        message
          << "SgfcArgument constructor failed: Specified argument type "
          << static_cast<int>(argumentType)
          << " requires a parameter, but no parameter was specified";
        throw std::invalid_argument(message.str());
    }
  }

  SgfcArgument::SgfcArgument(SgfcArgumentType argumentType, int parameter)
    : argumentType(argumentType)
    , hasIntegerTypeParameter(true)
    , integerTypeParameter(parameter)
    , hasPropertyTypeParameter(false)
    , propertyTypeParameter(SgfcPropertyType::Unknown)
  {
    switch (argumentType)
    {
      case SgfcArgumentType::BeginningOfSgfData:
      case SgfcArgumentType::DisableMessageNumber:
      case SgfcArgumentType::HardLineBreakMode:
        break;
      default:
        std::stringstream message;
        message
          << "SgfcArgument constructor failed: Specified argument type "
          << static_cast<int>(argumentType)
          << " does not require an integer type parameter, but an integer type parameter was specified";
        throw std::invalid_argument(message.str());
    }
  }

  SgfcArgument::SgfcArgument(SgfcArgumentType argumentType, SgfcPropertyType parameter)
    : argumentType(argumentType)
    , hasIntegerTypeParameter(false)
    , integerTypeParameter(-1)
    , hasPropertyTypeParameter(true)
    , propertyTypeParameter(parameter)
  {
    switch (argumentType)
    {
      case SgfcArgumentType::DeletePropertyType:
        break;
      default:
        std::stringstream message;
        message
          << "SgfcArgument constructor failed: Specified argument type "
          << static_cast<int>(argumentType)
          << " does not require an SgfcPropertyType parameter, but an SgfcPropertyType parameter was specified";
        throw std::invalid_argument(message.str());
    }
  }

  SgfcArgument::~SgfcArgument()
  {
  }

  SgfcArgumentType SgfcArgument::GetArgumentType() const
  {
    return this->argumentType;
  }

  bool SgfcArgument::HasIntegerTypeParameter() const
  {
    return this->hasIntegerTypeParameter;
  }

  int SgfcArgument::GetIntegerTypeParameter() const
  {
    return this->integerTypeParameter;
  }

  bool SgfcArgument::HasPropertyTypeParameter() const
  {
    return this->hasPropertyTypeParameter;
  }

  SgfcPropertyType SgfcArgument::GetPropertyTypeParameter() const
  {
    return this->propertyTypeParameter;
  }

  std::string SgfcArgument::ToString() const
  {
    std::stringstream argumentAsString;
    argumentAsString << SgfcUtility::MapArgumentTypeToCmdlineOption(this->argumentType);

    if (HasIntegerTypeParameter())
      argumentAsString << this->integerTypeParameter;
    else if (HasPropertyTypeParameter())
      argumentAsString << SgfcUtility::MapPropertyTypeToPropertyName(this->propertyTypeParameter);

    return argumentAsString.str();
  }
}
