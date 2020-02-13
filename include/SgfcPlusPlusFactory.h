#pragma once

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
    /// @brief Returns a newly constructed ISgfcCommandLine object.
    ///
    /// @param arguments The command line arguments to pass to SGFC, exactly
    /// as you would specify them on the command line. Some arguments are not
    /// allowed because they do not make sense when using SGFC in a library
    /// context, or in the particular context of SgfcCommandLine. The following
    /// arguments are not allowed: "-h", "--help", "-i", "infile", "outfile".
    ///
    /// @todo Specify other arguments that are not allowed.
    /// @todo Specify arguments with types instead of with std::string.
    ///
    /// @exception std::invalid_argument Is thrown if any of the arguments
    /// specified in @a arguments is not allowed by SgfcCommandLine, or if
    /// SGFC has a problem evaluating any of the arguments (e.g. unknown
    /// argument).
    static std::shared_ptr<ISgfcCommandLine> CreateSgfcCommandLine(
      const std::vector<std::string>& arguments);

    /// @brief Returns a newly constructred ISgfcCommandLine object that passes
    /// no command line arguments to SGFC.
    static std::shared_ptr<ISgfcCommandLine> CreateSgfcCommandLine();

  private:
    SgfcPlusPlusFactory();
    ~SgfcPlusPlusFactory();
  };
}
