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
    , hasStringTypeParameter(false)
    , hasPropertyTypeParameter(false)
    , propertyTypeParameter(SgfcPropertyType::Unknown)
    , hasMessageIDParameter(false)
    , messageIDParameter(SgfcMessageID::UnknownSgfcMessageID)
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
    , hasStringTypeParameter(false)
    , hasPropertyTypeParameter(false)
    , propertyTypeParameter(SgfcPropertyType::Unknown)
    , hasMessageIDParameter(false)
    , messageIDParameter(SgfcMessageID::UnknownSgfcMessageID)
  {
    switch (argumentType)
    {
      case SgfcArgumentType::BeginningOfSgfData:
      case SgfcArgumentType::HardLineBreakMode:
      case SgfcArgumentType::EncodingMode:
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

  SgfcArgument::SgfcArgument(SgfcArgumentType argumentType, std::string parameter)
    : argumentType(argumentType)
    , hasIntegerTypeParameter(false)
    , integerTypeParameter(-1)
    , hasStringTypeParameter(true)
    , stringTypeParameter(parameter)
    , hasPropertyTypeParameter(false)
    , propertyTypeParameter(SgfcPropertyType::Unknown)
    , hasMessageIDParameter(false)
    , messageIDParameter(SgfcMessageID::UnknownSgfcMessageID)
  {
    switch (argumentType)
    {
      case SgfcArgumentType::DefaultEncoding:
      case SgfcArgumentType::ForcedEncoding:
        break;
      default:
        std::stringstream message;
        message
          << "SgfcArgument constructor failed: Specified argument type "
          << static_cast<int>(argumentType)
          << " does not require a string type parameter, but a string type parameter was specified";
        throw std::invalid_argument(message.str());
    }
  }

  SgfcArgument::SgfcArgument(SgfcArgumentType argumentType, SgfcPropertyType parameter)
    : argumentType(argumentType)
    , hasIntegerTypeParameter(false)
    , integerTypeParameter(-1)
    , hasStringTypeParameter(false)
    , hasPropertyTypeParameter(true)
    , propertyTypeParameter(parameter)
    , hasMessageIDParameter(false)
    , messageIDParameter(SgfcMessageID::UnknownSgfcMessageID)
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

  SgfcArgument::SgfcArgument(SgfcArgumentType argumentType, SgfcMessageID parameter)
    : argumentType(argumentType)
    , hasIntegerTypeParameter(false)
    , integerTypeParameter(-1)
    , hasStringTypeParameter(false)
    , hasPropertyTypeParameter(false)
    , propertyTypeParameter(SgfcPropertyType::Unknown)
    , hasMessageIDParameter(true)
    , messageIDParameter(parameter)
  {
    switch (argumentType)
    {
      case SgfcArgumentType::DisableMessageID:
        break;
      default:
        std::stringstream message;
        message
          << "SgfcArgument constructor failed: Specified argument type "
          << static_cast<int>(argumentType)
          << " does not require an SgfcMessageID parameter, but an SgfcMessageID parameter was specified";
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

  bool SgfcArgument::HasStringTypeParameter() const
  {
    return this->hasStringTypeParameter;
  }

  std::string SgfcArgument::GetStringTypeParameter() const
  {
    return this->stringTypeParameter;
  }

  bool SgfcArgument::HasPropertyTypeParameter() const
  {
    return this->hasPropertyTypeParameter;
  }

  SgfcPropertyType SgfcArgument::GetPropertyTypeParameter() const
  {
    return this->propertyTypeParameter;
  }

  bool SgfcArgument::HasMessageIDParameter() const
  {
    return this->hasMessageIDParameter;
  }

  SgfcMessageID SgfcArgument::GetMessageIDParameter() const
  {
    return this->messageIDParameter;
  }

  std::string SgfcArgument::ToString() const
  {
    std::stringstream argumentAsString;
    // Make sure that decimal point is always a period (".") character and that
    // there are no thousands separators
    argumentAsString.imbue(std::locale::classic());

    argumentAsString << SgfcUtility::MapArgumentTypeToCmdlineOption(this->argumentType);

    if (HasIntegerTypeParameter())
      argumentAsString << this->integerTypeParameter;
    else if (HasStringTypeParameter())
      argumentAsString << "=" << this->stringTypeParameter;
    else if (HasPropertyTypeParameter())
      argumentAsString << SgfcUtility::MapPropertyTypeToPropertyName(this->propertyTypeParameter);
    else if (HasMessageIDParameter())
      argumentAsString << static_cast<int>(this->messageIDParameter);

    return argumentAsString.str();
  }
}
