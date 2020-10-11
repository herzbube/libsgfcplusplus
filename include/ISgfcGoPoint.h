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
#include "SgfcCoordinateSystem.h"
#include "SgfcGoPointNotation.h"

// Project includes (generated)
#include <SgfcPlusPlusExport.h>

// C++ Standard Library includes
#include <string>

namespace LibSgfcPlusPlus
{
  /// @brief The ISgfcGoPoint interface represents a point on a Go board.
  ///
  /// @ingroup public-api
  /// @ingroup go
  ///
  /// A point on a Go board is an intersection of two lines. A point's location
  /// is identified by a position in a two-dimensional coordinate system. The
  /// horizontal axis is the x-axis, sometimes also called column. The vertical
  /// axis is the y-axis, sometimes also called row.
  ///
  /// ISgfcGoPoint has getter methods that make the point location available
  /// as numeric values in several coordinate systems (enumerated in
  /// SgfcCoordinateSystem). There are two getter methods: One for the x-axis
  /// position and one for the y-axis position. Both provide 1-based values.
  ///
  /// In addition ISgfcGoPoint has getter methods that make the point location
  /// available as string values in several notations (enumerated in
  /// SgfcGoPointNotation). There are three getter methods:
  /// - One getter method that provides the location as a single string value.
  /// - And two getter methods that provide the x-axis and y-axis compounds of
  ///   the location, respectively, as two separate string values.
  class SGFCPLUSPLUS_EXPORT ISgfcGoPoint
  {
  public:
    /// @brief Initializes a newly constructed ISgfcGoPoint object.
    ISgfcGoPoint();

    /// @brief Destroys and cleans up the ISgfcGoPoint object.
    virtual ~ISgfcGoPoint();

    /// @brief Returns the 1-based numeric x-axis position of the point in the
    /// desired coordinate system @a coordinateSystem.
    virtual unsigned int GetXPosition(SgfcCoordinateSystem coordinateSystem) const = 0;

    /// @brief Returns the 1-based numeric y-axis position of the point in the
    /// desired coordinate system @a coordinateSystem.
    virtual unsigned int GetYPosition(SgfcCoordinateSystem coordinateSystem) const = 0;

    /// @brief Returns true if GetPosition(), GetXPosition() and GetYPosition()
    /// return a non-empty string for the desired notation @a goPointNotation.
    /// Returns false if these methods return an empty string.
    ///
    /// The methods may return an empty string if the desired notation cannot
    /// represent the point location. See the documentation of each
    /// SgfcGoPointNotation enum value for a definition of the notation and its
    /// limitations. Notably, the "A1" hybrid notation cannot represent
    /// point locations with an x- or y-axis position greater than 25.
    virtual bool HasPosition(SgfcGoPointNotation goPointNotation) const = 0;

    /// @brief Returns the position of the point as a single string value in
    /// the desired notation @a goPointNotation. Returns an empty string if
    /// HasPosition() returns false for @a goPointNotation.
    virtual std::string GetPosition(SgfcGoPointNotation goPointNotation) const = 0;

    /// @brief Returns the x-axis compound of the point's position in the
    /// desired notation @a goPointNotation. Returns an empty string if
    /// HasPosition() returns false for @a goPointNotation.
    virtual std::string GetXPosition(SgfcGoPointNotation goPointNotation) const = 0;

    /// @brief Returns the y-axis compound of the point's position in the
    /// desired notation @a goPointNotation. Returns an empty string if
    /// HasPosition() returns false for @a goPointNotation.
    virtual std::string GetYPosition(SgfcGoPointNotation goPointNotation) const = 0;
  };
}
