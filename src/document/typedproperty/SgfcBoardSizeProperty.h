#pragma once

// Project includes
#include "../../../include/ISgfcBoardSizeProperty.h"
#include "../SgfcProperty.h"

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcComposedPropertyValue;
  class ISgfcNumberPropertyValue;
  class ISgfcSinglePropertyValue;

  /// @brief The SgfcBoardSizeProperty class provides an implementation of
  /// the ISgfcBoardSizeProperty interface. See the interface header file
  /// for documentation.
  ///
  /// @ingroup internals
  /// @ingroup property
  class SgfcBoardSizeProperty : public SgfcProperty, public ISgfcBoardSizeProperty
  {
  public:
    /// @brief Initializes a newly constructed SgfcBoardSizeProperty object. The
    /// property has no value.
    SgfcBoardSizeProperty();

    /// @brief Initializes a newly constructed SgfcBoardSizeProperty object. The
    /// property has the specified property value @a propertyValue.
    ///
    /// This constructor constructs an ISgfcBoardSizeProperty object that
    /// describes a square board.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyValue is
    /// null or if the @a propertyValue object's method HasTypedValue() returns
    /// false.
    SgfcBoardSizeProperty(
      std::shared_ptr<ISgfcNumberPropertyValue> propertyValue);

    /// @brief Initializes a newly constructed SgfcBoardSizeProperty object. The
    /// property has the specified property value @a propertyValue.
    ///
    /// This overload constructs an ISgfcBoardSizeProperty object that
    /// describes a rectangular board.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyValue is
    /// null or if the @a propertyValue object is not composed of two
    /// ISgfcNumberPropertyValue objects, or if any of the
    /// ISgfcNumberPropertyValue object's method HasTypedValue() returns false.
    SgfcBoardSizeProperty(
      std::shared_ptr<ISgfcComposedPropertyValue> propertyValue);

    /// @brief Destroys and cleans up the SgfcBoardSizeProperty object.
    virtual ~SgfcBoardSizeProperty();

    virtual const ISgfcBoardSizeProperty* ToBoardSizeProperty() const;

    virtual SgfcBoardSize GetBoardSize(SgfcGameType gameType) const;

  private:
    SgfcBoardSize GetBoardSizeFromSingleValue(const ISgfcSinglePropertyValue* singleValue) const;
    SgfcBoardSize GetBoardSizeFromComposedValue(const ISgfcComposedPropertyValue* composedValue) const;
  };
}
