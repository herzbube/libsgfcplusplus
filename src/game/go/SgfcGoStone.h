#pragma once

// Project includes
#include "../../../include/ISgfcGoStone.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcGoStone class provides an implementation of the
  /// ISgfcGoStone interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup go
  class SgfcGoStone : public ISgfcGoStone
  {
  public:
    /// @brief Initializes a newly constructed SgfcGoStone object. @a color and
    /// @a location indicate the color and location of the stone.
    ///
    /// @exception std::invalid_argument Is thrown if @a location is nullptr.
    SgfcGoStone(SgfcColor color, std::shared_ptr<ISgfcGoPoint> location);

    /// @brief Initializes a newly constructed SgfcGoStone object. @a color
    /// indicates the color of the stone. The location of the stone on the Go
    /// board is not known, or the stone is not located on the board at all.
    SgfcGoStone(SgfcColor color);

    /// @brief Destroys and cleans up the SgfcGoStone object.
    virtual ~SgfcGoStone();

    virtual SgfcColor GetColor() const;
    virtual bool HasLocation() const;
    virtual std::shared_ptr<ISgfcGoPoint> GetLocation() const;

  private:
    SgfcColor color;
    std::shared_ptr<ISgfcGoPoint> location;
  };
}
