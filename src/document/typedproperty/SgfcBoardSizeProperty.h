#pragma once

// Project includes
#include "../../../include/ISgfcBoardSizeProperty.h"
#include "../SgfcProperty.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcBoardSizeProperty class provides an implementation of
  /// the ISgfcBoardSizeProperty interface. See the interface header file
  /// for documentation.
  class SgfcBoardSizeProperty : public SgfcProperty, public ISgfcBoardSizeProperty
  {
  public:
    /// @brief Initializes a newly constructed SgfcBoardSizeProperty object. The
    /// property has no values.
    SgfcBoardSizeProperty();

    /// @brief Initializes a newly constructed SgfcBoardSizeProperty object. The
    /// property has the specified property values @a propertyValues.
    SgfcBoardSizeProperty(
      const std::vector<std::shared_ptr<ISgfcPropertyValue>>& propertyValues);

    /// @brief Destroys and cleans up the SgfcBoardSizeProperty object.
    virtual ~SgfcBoardSizeProperty();

    virtual const ISgfcBoardSizeProperty* ToBoardSizeProperty() const;

    virtual SgfcBoardSize GetBoardSize(SgfcGameType gameType) const;
  };
}
