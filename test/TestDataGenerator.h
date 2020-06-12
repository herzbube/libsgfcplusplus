#pragma once

// Library includes
#include <SgfcColor.h>
#include <SgfcDouble.h>
#include <SgfcTypedefs.h>

// C++ Standard Library includes
#include <string>
#include <utility>
#include <vector>

namespace LibSgfcPlusPlus
{
  /// @brief The TestDataGenerator class is a container for static methods that
  /// return test data to be used during unit testing.
  class TestDataGenerator
  {
  public:
    static std::vector<std::pair<std::string, SgfcNumber>> GetValidNumberStrings();
    static std::vector<std::string> GetInvalidNumberStrings();
    static std::vector<std::pair<SgfcNumber, std::string>> GetNumberValues();

    static std::vector<std::pair<std::string, SgfcReal>> GetValidRealStrings();
    static std::vector<std::string> GetInvalidRealStrings();
    static std::vector<std::pair<SgfcReal, std::string>> GetRealValues();

    static std::vector<std::pair<std::string, SgfcDouble>> GetValidDoubleStrings();
    static std::vector<std::string> GetInvalidDoubleStrings();
    static std::vector<std::pair<SgfcDouble, std::string>> GetDoubleValues();

    static std::vector<std::pair<std::string, SgfcColor>> GetValidColorStrings();
    static std::vector<std::string> GetInvalidColorStrings();
    static std::vector<std::pair<SgfcColor, std::string>> GetColorValues();

  private:
    TestDataGenerator();
    virtual ~TestDataGenerator();
  };
}
