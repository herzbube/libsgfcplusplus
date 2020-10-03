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

  void SgfcArguments::AddArgument(SgfcArgumentType argumentType, SgfcPropertyType parameter)
  {
    ThrowIfMultiplicityViolated(argumentType, parameter, &ISgfcArgument::GetPropertyTypeParameter);

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
      case SgfcArgumentType::DisableMessageNumber:
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
            << static_cast<int>(parameter)
            << " is already present";
          throw std::invalid_argument(message.str());
        }
      }
    }
  }
}
