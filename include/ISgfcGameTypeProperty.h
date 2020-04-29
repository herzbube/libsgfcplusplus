#pragma once

// Project includes
#include "ISgfcProperty.h"
#include "SgfcGameType.h"
#include "SgfcTypedefs.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcGameTypeProperty interface is a specialization of
  /// ISgfcProperty for SgfcPropertyType::GM. It simplifies access to the
  /// property value and provides the value in the form of an SgfcGameType
  /// value.
  class SGFCPLUSPLUS_EXPORT ISgfcGameTypeProperty : virtual public ISgfcProperty
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGameTypeProperty object.
    ISgfcGameTypeProperty();

    /// @brief Destroys and cleans up the ISgfcGameTypeProperty object.
    virtual ~ISgfcGameTypeProperty();

    /// @brief Returns the property value interpreted as an SgfcGameType value.
    ///
    /// @retval SgfcGameType If the property has a value defined in the
    ///         SGF standard, returns the SgfcGameType value that corresponds
    ///         to the property value. The value is guaranteed not to be
    ///         SgfcGameType::Unknown.
    /// @retval SgfcConstants::DefaultGameType If the property has no value.
    ///         The value is guaranteed not to be SgfcGameType::Unknown.
    /// @retval SgfcGameType::Unknown If the property has a value that is not
    ///         defined in the SGF standard.
    virtual SgfcGameType GetGameType() const = 0;

    /// @brief Returns the property value interpreted as an SgfcNumber value.
    /// This is useful if GetGameType() returns SgfcGameType::Unknown.
    ///
    /// @retval SgfcNumber The Number value of the property. If the property
    ///         has no value, returns the Number value that corresponds to
    ///         SgfcConstants::DefaultGameType.
    virtual SgfcNumber GetGameTypeAsNumber() const = 0;
  };
}
