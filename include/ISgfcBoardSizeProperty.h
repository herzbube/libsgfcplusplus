#pragma once

// Project includes
#include "ISgfcProperty.h"
#include "SgfcBoardSize.h"
#include "SgfcGameType.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcBoardSizeProperty interface is a specialization of
  /// ISgfcProperty for SgfcPropertyType::SZ. It simplifies access to the
  /// property value and provides the value in the form of an SgfcBoardSize
  /// object.
  class SGFCPLUSPLUS_EXPORT ISgfcBoardSizeProperty : virtual public ISgfcProperty
  {
  public:
    /// @brief Initializes a newly constructed ISgfcBoardSizeProperty object.
    ISgfcBoardSizeProperty();

    /// @brief Destroys and cleans up the ISgfcBoardSizeProperty object.
    virtual ~ISgfcBoardSizeProperty();

    /// @brief Returns the property value interpreted as an SgfcBoardSize value.
    ///
    /// @retval SgfcBoardSize If the property has a valid value. The value is
    ///         guaranteed not to be SgfcConstants::BoardSizeNone nor
    ///         SgfcConstants::BoardSizeInvalid.
    /// @retval SgfcConstants::BoardSizeDefaultGo If the property has no value,
    ///         and @a gameType is SgfcGameType::Go.
    /// @retval SgfcConstants::BoardSizeDefaultChess If the property has no
    ///         value, and @a gameType is SgfcGameType::Chess.
    /// @retval SgfcConstants::BoardSizeNone If the property has no value, but
    ///         @a gameType is neither SgfcGameType::Go nor SgfcGameType::Chess.
    /// @retval SgfcConstants::BoardSizeInvalid If the property has an invalid
    ///         value. A board size is invalid if it violates the constraints
    ///         defined by the SGF standard. See the documentation of
    ///         SgfcConstants::BoardSizeInvalid for details.
    virtual SgfcBoardSize GetBoardSize(SgfcGameType gameType) const = 0;
  };
}
