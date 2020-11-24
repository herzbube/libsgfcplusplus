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
    /// @e nullptr.
    SgfcBoardSizeProperty(
      std::shared_ptr<ISgfcNumberPropertyValue> propertyValue);

    /// @brief Initializes a newly constructed SgfcBoardSizeProperty object. The
    /// property has the specified property value @a propertyValue.
    ///
    /// This overload constructs an ISgfcBoardSizeProperty object that
    /// describes a rectangular board.
    ///
    /// @exception std::invalid_argument Is thrown if @a propertyValue is
    /// @e nullptr, or if the @a propertyValue object is not composed of two
    /// ISgfcNumberPropertyValue objects.
    SgfcBoardSizeProperty(
      std::shared_ptr<ISgfcComposedPropertyValue> propertyValue);

    /// @brief Destroys and cleans up the SgfcBoardSizeProperty object.
    virtual ~SgfcBoardSizeProperty();

    virtual const ISgfcBoardSizeProperty* ToBoardSizeProperty() const override;

    virtual SgfcBoardSize GetBoardSize(SgfcGameType gameType) const override;
  };
}
