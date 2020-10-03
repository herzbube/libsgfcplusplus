#pragma once

// Project includes
#include "../../../include/ISgfcArgument.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcArgument class provides an implementation of the
  /// ISgfcArgument interface. See the interface header file for
  /// documentation.
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

    virtual SgfcArgumentType GetArgumentType() const;
    virtual bool HasIntegerTypeParameter() const;
    virtual int GetIntegerTypeParameter() const;
    virtual bool HasPropertyTypeParameter() const;
    virtual SgfcPropertyType GetPropertyTypeParameter() const;
    virtual std::string ToString() const;

  private:
    SgfcArgumentType argumentType;
    bool hasIntegerTypeParameter;
    int integerTypeParameter;
    bool hasPropertyTypeParameter;
    SgfcPropertyType propertyTypeParameter;
  };
}
