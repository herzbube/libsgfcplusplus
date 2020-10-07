#pragma once

// Project includes
#include "../../../include/ISgfcSgfContent.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcSgfContent class provides an implementation of the
  /// ISgfcSgfContent interface. See the interface header file for
  /// documentation.
  ///
  /// @ingroup internals
  /// @ingroup sgfc-backend
  class SgfcSgfContent : public ISgfcSgfContent
  {
  public:
    /// @brief Initializes a newly constructed SgfcSgfContent object. The object
    /// has no SGF content.
    SgfcSgfContent();

    /// @brief Initializes a newly constructed SgfcSgfContent object. The object
    /// has the SGF content @a sgfContent, SGFC would have used @a fileName to
    /// save the SGF content to the filesystem.
    SgfcSgfContent(
      const std::string& sgfContent,
      const std::string& fileName);

    /// @brief Destroys and cleans up the SgfcSgfContent object.
    virtual ~SgfcSgfContent();
  
    virtual std::string GetSgfContent() const;
    virtual std::string GetFileName() const;

  private:
    std::string sgfContent;
    std::string fileName;
  };
}
