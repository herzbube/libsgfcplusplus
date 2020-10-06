#pragma once

// Project includes
#include "SgfcArgumentType.h"
#include "SgfcPropertyType.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcArgument interface represents a single argument to be
  /// passed on to SGFC when it reads or writes SGF content. Depending on the
  /// argument type, the argument also has either an integer type or an
  /// SgfcPropertyType parameter.
  ///
  /// @ingroup public-api
  /// @ingroup sgfc-arguments
  class SGFCPLUSPLUS_EXPORT ISgfcArgument
  {
  public:
    /// @brief Initializes a newly constructed ISgfcArgument object.
    ISgfcArgument();

    /// @brief Destroys and cleans up the ISgfcArgument object.
    virtual ~ISgfcArgument();

    /// @brief Returns the argument type.
    virtual SgfcArgumentType GetArgumentType() const = 0;

    /// @brief Returns true if the argument has an integer type parameter.
    virtual bool HasIntegerTypeParameter() const = 0;

    /// @brief Returns the argument's integer type parameter value. The return
    /// value is undefined if HasIntegerTypeParameter() returns false.
    virtual int GetIntegerTypeParameter() const = 0;

    /// @brief Returns true if the argument has an SgfcPropertyType parameter.
    virtual bool HasPropertyTypeParameter() const = 0;

    /// @brief Returns the argument's SgfcPropertyType parameter value. The
    /// return value is undefined if HasPropertyTypeParameter() returns false.
    virtual SgfcPropertyType GetPropertyTypeParameter() const = 0;

    /// @brief Returns the argument as a string, exactly as it would be
    /// specified on the SGFC command line. Examples: -n, -b1, -yMA.
    virtual std::string ToString() const = 0;
  };
}
