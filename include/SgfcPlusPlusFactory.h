#pragma once

// Project includes
#include "ISgfcCommandLine.h"
#include "ISgfcDocumentReader.h"

// C++ Standard Library includes
#include <memory>
#include <string>
#include <vector>

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class ISgfcCommandLine;

  /// @brief The SgfcPlusPlusFactory class is a class that contains only static
  /// functions. The functions are used to construct various library objects.
  class SgfcPlusPlusFactory
  {
  public:
    /// @brief Returns a newly constructed ISgfcCommandLine object that passes
    /// the specified command line arguments to SGFC.
    ///
    /// @param arguments The command line arguments to pass to SGFC, exactly
    /// as you would specify them on the command line. Invoke the
    /// ISgfcCommandLine::IsCommandLineValid() method on the resulting object
    /// to find out whether the arguments are valid.
    ///
    /// @todo Specify arguments with types instead of with std::string.
    static std::shared_ptr<ISgfcCommandLine> CreateSgfcCommandLine(
      const std::vector<std::string>& arguments);

    /// @brief Returns a newly constructed ISgfcCommandLine object that passes
    /// no command line arguments to SGFC.
    static std::shared_ptr<ISgfcCommandLine> CreateSgfcCommandLine();

    /// @brief Returns a newly constructed ISgfcDocumentReader object.
    static std::shared_ptr<ISgfcDocumentReader> CreateDocumentReader();

  private:
    SgfcPlusPlusFactory();
    ~SgfcPlusPlusFactory();
  };
}
