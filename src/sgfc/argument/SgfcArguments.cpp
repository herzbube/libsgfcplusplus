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
#include "SgfcArgument.h"
#include "SgfcArguments.h"

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcArguments::SgfcArguments()
  {
  }

  SgfcArguments::~SgfcArguments()
  {
  }

  bool SgfcArguments::HasArguments() const
  {
    return (this->arguments.size() > 0);
  }

  std::vector<std::shared_ptr<ISgfcArgument>> SgfcArguments::GetArguments() const
  {
    return this->arguments;
  }

  void SgfcArguments::AddArgument(SgfcArgumentType argumentType)
  {
    ThrowIfMultiplicityViolated(argumentType);

    auto argument = std::shared_ptr<ISgfcArgument>(new SgfcArgument(argumentType));
    this->arguments.push_back(argument);
  }

  void SgfcArguments::AddArgument(SgfcArgumentType argumentType, int parameter)
  {
    ThrowIfMultiplicityViolated(argumentType, parameter, &ISgfcArgument::GetIntegerTypeParameter);

    auto argument = std::shared_ptr<ISgfcArgument>(new SgfcArgument(argumentType, parameter));
    this->arguments.push_back(argument);
  }

  void SgfcArguments::AddArgument(SgfcArgumentType argumentType, const std::string& parameter)
  {
    ThrowIfMultiplicityViolated(argumentType, parameter, &ISgfcArgument::GetStringTypeParameter);

    auto argument = std::shared_ptr<ISgfcArgument>(new SgfcArgument(argumentType, parameter));
    this->arguments.push_back(argument);
  }

  void SgfcArguments::AddArgument(SgfcArgumentType argumentType, SgfcPropertyType parameter)
  {
    ThrowIfMultiplicityViolated(argumentType, parameter, &ISgfcArgument::GetPropertyTypeParameter);

    auto argument = std::shared_ptr<ISgfcArgument>(new SgfcArgument(argumentType, parameter));
    this->arguments.push_back(argument);
  }

  void SgfcArguments::AddArgument(SgfcArgumentType argumentType, SgfcMessageID parameter)
  {
    ThrowIfMultiplicityViolated(argumentType, parameter, &ISgfcArgument::GetMessageIDParameter);

    auto argument = std::shared_ptr<ISgfcArgument>(new SgfcArgument(argumentType, parameter));
    this->arguments.push_back(argument);
  }

  void SgfcArguments::ClearArguments()
  {
    this->arguments.clear();
  }

  bool SgfcArguments::ArgumentTypeCanBeAddedMultipleTimes(SgfcArgumentType argumentType) const
  {
    switch (argumentType)
    {
      case SgfcArgumentType::DisableMessageID:
      case SgfcArgumentType::DeletePropertyType:
        return true;
      default:
        return false;
    }
  }

  void SgfcArguments::ThrowIfMultiplicityViolated(SgfcArgumentType argumentType)
  {
    if (ArgumentTypeCanBeAddedMultipleTimes(argumentType))
      return;

    for (auto argument : this->arguments)
    {
      if (argument->GetArgumentType() == argumentType)
      {
        std::stringstream message;
        message
          << "AddArgument failed: Argument of type "
          << static_cast<int>(argumentType)
          << " is already present";
        throw std::invalid_argument(message.str());
      }
    }
  }

  std::ostream& operator<< (std::ostream& out, SgfcPropertyType value)
  {
    out << static_cast<int>(value);
    return out;
  }

  std::ostream& operator<< (std::ostream& out, SgfcMessageID value)
  {
    out << static_cast<int>(value);
    return out;
  }

  template <typename T, typename FType>
  void SgfcArguments::ThrowIfMultiplicityViolated(
    SgfcArgumentType argumentType,
    T parameter,
    FType ParameterValueGetter)
  {
    bool argumentTypeCanBeAddedMultipleTimes = ArgumentTypeCanBeAddedMultipleTimes(argumentType);

    for (auto argument : this->arguments)
    {
      if (argument->GetArgumentType() == argumentType)
      {
        if (! argumentTypeCanBeAddedMultipleTimes)
        {
          std::stringstream message;
          message
            << "AddArgument failed: Argument of type "
            << static_cast<int>(argumentType)
            << " is already present";
          throw std::invalid_argument(message.str());
        }
        else if ((argument.get()->*ParameterValueGetter)() == parameter)
        {
          std::stringstream message;
          message
            << "AddArgument failed: Argument of type "
            << static_cast<int>(argumentType)
            << " with parameter value "
            << parameter
            << " is already present";
          throw std::invalid_argument(message.str());
        }
      }
    }
  }
}
