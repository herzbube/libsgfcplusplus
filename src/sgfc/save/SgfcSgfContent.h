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
    SgfcSgfContent();
    SgfcSgfContent(
      const std::string& sgfContent,
      const std::string& fFileName);
    virtual ~SgfcSgfContent();
  
    virtual std::string GetSgfContent() const;
    virtual std::string GetFileName() const;

  private:
    std::string sgfContent;
    std::string fileName;
  };
}
