// Project includes
#include "TestDataGenerator.h"
#include <SgfcConstants.h>

namespace LibSgfcPlusPlus
{
  std::vector<std::pair<std::string, SgfcNumber>> TestDataGenerator::GetValidNumberStrings()
  {
    std::vector<std::pair<std::string, SgfcNumber>> testData =
    {
      std::pair<std::string, SgfcNumber> { "-042", -42 },
      std::pair<std::string, SgfcNumber> { "-42", -42 },
      std::pair<std::string, SgfcNumber> { "-1", -1 },
      std::pair<std::string, SgfcNumber> { "-0", 0 },
      std::pair<std::string, SgfcNumber> { "0", 0 },
      std::pair<std::string, SgfcNumber> { "+0", 0 },
      std::pair<std::string, SgfcNumber> { "1", 1 },
      std::pair<std::string, SgfcNumber> { "+1", 1 },
      std::pair<std::string, SgfcNumber> { "42", 42 },
      std::pair<std::string, SgfcNumber> { "042", 42 },
      // Whitespace is ignored
      std::pair<std::string, SgfcNumber> { " \t\r\n123 \t\r\n", 123 },
      // Floating point numbers are parsed up to the decimal point, with no rounding
      std::pair<std::string, SgfcNumber> { "2.718", 2 },
      std::pair<std::string, SgfcNumber> { "3.141", 3 },
      // Any other non-digit characters after the last digit are also ignored
      std::pair<std::string, SgfcNumber> { "4abc2", 4 }
    };

    return testData;
  }

  std::vector<std::string> TestDataGenerator::GetInvalidNumberStrings()
  {
    std::vector<std::string> testData =
    {
      "", " \t\r\n",
      ".",
      "abc", "$",
      // Overflow
      "-12345678901234567890", "12345678901234567890"
    };

    return testData;
  }

  std::vector<std::pair<SgfcNumber, std::string>> TestDataGenerator::GetNumberValues()
  {
    std::vector<std::pair<SgfcNumber, std::string>> testData =
    {
      std::pair<SgfcNumber, std::string> { -42, "-42" },
      std::pair<SgfcNumber, std::string> { -1, "-1" },
      std::pair<SgfcNumber, std::string> { 0, "0" },
      std::pair<SgfcNumber, std::string> { 1, "1" },
      std::pair<SgfcNumber, std::string> { 42, "42" }
    };

    return testData;
  }

  std::vector<std::pair<std::string, SgfcReal>> TestDataGenerator::GetValidRealStrings()
  {
    std::vector<std::pair<std::string, SgfcReal>> testData =
    {
      // Integers
      std::pair<std::string, SgfcReal> { "-12345678901234567890", -12345678901234567890.0 },
      std::pair<std::string, SgfcReal> { "-042", -42.0 },
      std::pair<std::string, SgfcReal> { "-42", -42.0 },
      std::pair<std::string, SgfcReal> { "-1", -1.0 },
      std::pair<std::string, SgfcReal> { "-0", 0.0 },
      std::pair<std::string, SgfcReal> { "0", 0.0 },
      std::pair<std::string, SgfcReal> { "+0", 0.0 },
      std::pair<std::string, SgfcReal> { "1", 1.0 },
      std::pair<std::string, SgfcReal> { "+1", 1.0 },
      std::pair<std::string, SgfcReal> { "42", 42.0 },
      std::pair<std::string, SgfcReal> { "042", 42.0 },
      std::pair<std::string, SgfcReal> { "12345678901234567890", 12345678901234567890.0 },
      // Floating point numbers
      std::pair<std::string, SgfcReal> { "2.718", 2.718 },
      std::pair<std::string, SgfcReal> { "2.", 2.0 },
      std::pair<std::string, SgfcReal> { "0.2", 0.2 },
      std::pair<std::string, SgfcReal> { ".2", 0.2 },
      std::pair<std::string, SgfcReal> { "-0.2", -0.2 },
      std::pair<std::string, SgfcReal> { "-.2", -0.2 },
      std::pair<std::string, SgfcReal> { "0.", 0.0 },
      std::pair<std::string, SgfcReal> { ".0", 0.0 },
      std::pair<std::string, SgfcReal> { "1.23456e3", 1234.56 },
      std::pair<std::string, SgfcReal> { "1.23456e03", 1234.56 },
      std::pair<std::string, SgfcReal> { "1.23456e+3", 1234.56 },
      std::pair<std::string, SgfcReal> { "1.23456e-3", 0.00123456 },
      // Whitespace is ignored
      std::pair<std::string, SgfcReal> { " \t\r\n123.456 \t\r\n", 123.456 },
      // Any other non-digit characters after the last digit are also ignored
      std::pair<std::string, SgfcReal> { "1.23456a3", 1.23456 }
    };

    return testData;
  }

  std::vector<std::string> TestDataGenerator::GetInvalidRealStrings()
  {
    std::vector<std::string> testData =
    {
      "", " \t\r\n",
      ".",
      "abc", "$",
      // Overflow: 310 digits
      "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
    };

    return testData;
  }

  std::vector<std::pair<SgfcReal, std::string>> TestDataGenerator::GetRealValues()
  {
    std::vector<std::pair<SgfcReal, std::string>> testData =
    {
      std::pair<SgfcReal, std::string> { -42.0, "-42" },
      std::pair<SgfcReal, std::string> { -1.0, "-1" },
      std::pair<SgfcReal, std::string> { 0.0, "0" },
      std::pair<SgfcReal, std::string> { 1.0, "1" },
      std::pair<SgfcReal, std::string> { 42.0, "42" },
      std::pair<SgfcReal, std::string> { 1.234, "1.234" },
      std::pair<SgfcReal, std::string> { -1.234, "-1.234" }
    };

    return testData;
  }

  std::vector<std::pair<std::string, SgfcDouble>> TestDataGenerator::GetValidDoubleStrings()
  {
    std::vector<std::pair<std::string, SgfcDouble>> testData =
    {
      std::pair<std::string, SgfcDouble> { SgfcConstants::DoubleNormalString, SgfcDouble::Normal },
      std::pair<std::string, SgfcDouble> { SgfcConstants::DoubleEmphasizedString, SgfcDouble::Emphasized }
    };

    return testData;
  }

  std::vector<std::string> TestDataGenerator::GetInvalidDoubleStrings()
  {
    std::vector<std::string> testData =
    {
      "",
      " \t\r\n",
      "-1",
      "1.0",
      "3"
    };

    return testData;
  }

  std::vector<std::pair<SgfcDouble, std::string>> TestDataGenerator::GetDoubleValues()
  {
    std::vector<std::pair<SgfcDouble, std::string>> testData =
    {
      std::pair<SgfcDouble, std::string> { SgfcDouble::Normal, SgfcConstants::DoubleNormalString },
      std::pair<SgfcDouble, std::string> { SgfcDouble::Emphasized, SgfcConstants::DoubleEmphasizedString }
};

    return testData;
  }

  std::vector<std::pair<std::string, SgfcColor>> TestDataGenerator::GetValidColorStrings()
  {
    std::vector<std::pair<std::string, SgfcColor>> testData =
    {
      std::pair<std::string, SgfcColor> { SgfcConstants::ColorBlackString, SgfcColor::Black },
      std::pair<std::string, SgfcColor> { SgfcConstants::ColorWhiteString, SgfcColor::White }
    };

    return testData;
  }

  std::vector<std::string> TestDataGenerator::GetInvalidColorStrings()
  {
    std::vector<std::string> testData =
    {
      "",
      " \t\r\n",
      "b", "w",
      " B", " W",
      "B ", "W "
    };

    return testData;
  }

  std::vector<std::pair<SgfcColor, std::string>> TestDataGenerator::GetColorValues()
  {
    std::vector<std::pair<SgfcColor, std::string>> testData =
    {
      std::pair<SgfcColor, std::string> { SgfcColor::Black, SgfcConstants::ColorBlackString },
      std::pair<SgfcColor, std::string> { SgfcColor::White, SgfcConstants::ColorWhiteString }
    };

    return testData;
  }
}

