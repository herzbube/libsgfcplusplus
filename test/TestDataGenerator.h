#pragma once

// Library includes
#include <SgfcBoardSize.h>
#include <SgfcColor.h>
#include <SgfcDouble.h>
#include <SgfcGameType.h>
#include <SgfcTypedefs.h>
#include <game/go/SgfcGoPoint.h>

// C++ Standard Library includes
#include <string>
#include <tuple>
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

    static std::vector<std::pair<std::string, std::string>> GetSimpleTextStrings();

    static std::vector<std::pair<std::string, std::string>> GetTextStrings();

    static std::vector<std::tuple<std::string, SgfcBoardSize, int, int, int, int, bool, bool, bool, std::string, std::string, std::string>> GetGoPointStrings();
    static std::vector<SgfcBoardSize> GetInvalidGoBoardSizes();
    static std::vector<std::pair<std::string, SgfcBoardSize>> GetInvalidGoPointStrings();

    static std::vector<std::tuple<std::string, SgfcGameType, SgfcBoardSize>> GetValidSZSquareStrings();
    static std::vector<std::tuple<std::string, SgfcGameType>> GetInvalidSZSquareStrings();
    static std::vector<std::tuple<std::string, std::string, SgfcGameType, SgfcBoardSize>> GetValidSZRectangularStrings();
    static std::vector<std::tuple<std::string, std::string, SgfcGameType>> GetInvalidSZRectangularStrings();

    static std::vector<std::tuple<SgfcBoardSize, SgfcGameType, SgfcBoardSize>> GetValidBoardSizes();
    static std::vector<std::tuple<SgfcBoardSize, SgfcGameType>> GetInvalidBoardSizes();

  private:
    TestDataGenerator();
    virtual ~TestDataGenerator();

    static SgfcNumber ConvertStringToNumberOrThrow(const std::string& string);
  };
}
