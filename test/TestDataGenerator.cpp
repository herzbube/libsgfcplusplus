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
      "3",
      // SGFC is nice and trims whitespace it encounters when it parses the
      // SGF content, so in practice our library never gets to see leading or
      // trailing whitespace. The library therefore treats such whitespace as
      // invalid, in accordance with the SGF standard.
      " 1", " 2"
      "1 ", "2 "
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
      // SGFC is nice and trims whitespace it encounters when it parses the
      // SGF content, so in practice our library never gets to see leading or
      // trailing whitespace. The library therefore treats such whitespace as
      // invalid, in accordance with the SGF standard.
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

  std::vector<std::pair<std::string, std::string>> TestDataGenerator::GetSimpleTextStrings()
  {
    std::vector<std::pair<std::string, std::string>> testData =
    {
      std::pair<std::string, std::string> { "", "" },
      std::pair<std::string, std::string> { "foo", "foo" },
      std::pair<std::string, std::string> { "foo bar", "foo bar" },
      std::pair<std::string, std::string> { "foo  bar", "foo  bar" },
      // Whitespace characters other than space must be converted to space.
      // However, the library relies on SGFC doing this conversion, so for the
      // unit tests we make sure that the library does NOT convert.
      std::pair<std::string, std::string> { "foo\t\vbar", "foo\t\vbar" },
      // Each of the line endings mentioned in the SGF standard must be
      // converted to a single space (even if the line ending consists of two
      // characters).
      std::pair<std::string, std::string> { "foo\nbar", "foo bar" },
      std::pair<std::string, std::string> { "foo\rbar", "foo bar" },
      std::pair<std::string, std::string> { "foo\r\nbar", "foo bar" },
      std::pair<std::string, std::string> { "foo\n\rbar", "foo bar" },
      // Escaped line breaks are removed entirely
      std::pair<std::string, std::string> { "foo\\\nbar", "foobar" },
      std::pair<std::string, std::string> { "foo\\\rbar", "foobar" },
      std::pair<std::string, std::string> { "foo\\\r\nbar", "foobar" },
      std::pair<std::string, std::string> { "foo\\\n\rbar", "foobar" },
      // The escape character is removed if it escapes one of the special
      // characters mentioned in the SGF standard ("]", "\" and ":")
      std::pair<std::string, std::string> { "foo\\]bar", "foo]bar" },
      std::pair<std::string, std::string> { "foo\\\\bar", "foo\\bar" },
      std::pair<std::string, std::string> { "foo\\:bar", "foo:bar" },
      // The escape character is not removed if it does not escape one of the
      // special characters mentioned in the SGF standard. The reason is that
      // the library expects that SGFC removes those unnecessary escape
      // characters and it therefore does not perform escape character handling
      // itself.
      std::pair<std::string, std::string> { "foo\\bar", "foo\\bar" },
      std::pair<std::string, std::string> { "foo\\[bar", "foo\\[bar" },
      // We also test whether multiple consecutive escape characters work. There
      // is no order of precedence, an escape character simply always must act
      // upon the character that follows it. E.g. "\\:" escapes the escape
      // character, not the ":" character.
      std::pair<std::string, std::string> { "foo\\\\:bar", "foo\\:bar" },
      std::pair<std::string, std::string> { "foo\\\\\\:bar", "foo\\:bar" },
      std::pair<std::string, std::string> { "foo\\\\\\\\:bar", "foo\\\\:bar" }
    };

    return testData;
  }

  std::vector<std::pair<std::string, std::string>> TestDataGenerator::GetTextStrings()
  {
    std::vector<std::pair<std::string, std::string>> testData =
    {
      std::pair<std::string, std::string> { "", "" },
      std::pair<std::string, std::string> { "foo", "foo" },
      std::pair<std::string, std::string> { "foo bar", "foo bar" },
      std::pair<std::string, std::string> { "foo  bar", "foo  bar" },
      // Whitespace characters other than line breaks must be converted to
      // space. However, the library relies on SGFC doing this conversion, so
      // for the unit tests we make sure that the library does NOT convert.
      std::pair<std::string, std::string> { "foo\t\vbar", "foo\t\vbar" },
      // Un-escaped line breaks (the SGF standard calls them "hard line breaks")
      // must be preserved.
      std::pair<std::string, std::string> { "foo\nbar", "foo\nbar" },
      std::pair<std::string, std::string> { "foo\rbar", "foo\rbar" },
      std::pair<std::string, std::string> { "foo\r\nbar", "foo\r\nbar" },
      std::pair<std::string, std::string> { "foo\n\rbar", "foo\n\rbar" },
      // Escaped line breaks (the SGF standard calls them "soft line breaks")
      // are removed entirely
      std::pair<std::string, std::string> { "foo\\\nbar", "foobar" },
      std::pair<std::string, std::string> { "foo\\\rbar", "foobar" },
      std::pair<std::string, std::string> { "foo\\\r\nbar", "foobar" },
      std::pair<std::string, std::string> { "foo\\\n\rbar", "foobar" },
      // The escape character is removed if it escapes one of the special
      // characters mentioned in the SGF standard ("]", "\" and ":")
      std::pair<std::string, std::string> { "foo\\]bar", "foo]bar" },
      std::pair<std::string, std::string> { "foo\\\\bar", "foo\\bar" },
      std::pair<std::string, std::string> { "foo\\:bar", "foo:bar" },
      // The escape character is not removed if it does not escape one of the
      // special characters mentioned in the SGF standard. The reason is that
      // the library expects that SGFC removes those unnecessary escape
      // characters and it therefore does not perform escape character handling
      // itself.
      std::pair<std::string, std::string> { "foo\\bar", "foo\\bar" },
      std::pair<std::string, std::string> { "foo\\[bar", "foo\\[bar" },
      // We also test whether multiple consecutive escape characters work. There
      // is no order of precedence, an escape character simply always must act
      // upon the character that follows it. E.g. "\\:" escapes the escape
      // character, not the ":" character.
      std::pair<std::string, std::string> { "foo\\\\:bar", "foo\\:bar" },
      std::pair<std::string, std::string> { "foo\\\\\\:bar", "foo\\:bar" },
      std::pair<std::string, std::string> { "foo\\\\\\\\:bar", "foo\\\\:bar" }
    };

    return testData;
  }

  std::vector<std::tuple<std::string, SgfcBoardSize, int, int, int, int, bool, bool, bool, std::string, std::string, std::string>> TestDataGenerator::GetGoPointStrings()
  {
    std::vector<std::tuple<std::string, SgfcBoardSize, int, int, int, int, bool, bool, bool, std::string, std::string, std::string>> testData =
    {
      // SgfcGoPointNotation::Sgf
      // Coordinate system origin is upper-left corner
      std::make_tuple("as", SgfcConstants::BoardSizeDefaultGo, 1, 19, 1, 1, true, true, true, "as", "1-19", "A1"),
      std::make_tuple("sa", SgfcConstants::BoardSizeDefaultGo, 19, 1, 19, 19, true, true, true, "sa", "19-1", "T19"),
      // Uppercase letters start at 26
      std::make_tuple("Az", SgfcConstants::BoardSizeMaximumGo, 27, 26, 27, 27, true, true, false, "Az", "27-26", ""),
      std::make_tuple("zA", SgfcConstants::BoardSizeMaximumGo, 26, 27, 26, 26, true, true, false, "zA", "26-27", ""),
      // Minimum/Maximum board size
      std::make_tuple("aa", SgfcConstants::BoardSizeMinimum, 1, 1, 1, 1, true, true, true, "aa", "1-1", "A1"),
      std::make_tuple("ZZ", SgfcConstants::BoardSizeMaximumGo, 52, 52, 52, 1, true, true, false, "ZZ", "52-52", ""),

      // SgfcGoPointNotation::Figure
      // Coordinate system origin is upper-left corner
      std::make_tuple("1-19", SgfcConstants::BoardSizeDefaultGo, 1, 19, 1, 1, true, true, true, "as", "1-19", "A1"),
      std::make_tuple("19-1", SgfcConstants::BoardSizeDefaultGo, 19, 1, 19, 19, true, true, true, "sa", "19-1", "T19"),
      // Minimum/Maximum board size
      std::make_tuple("1-1", SgfcConstants::BoardSizeMinimum, 1, 1, 1, 1, true, true, true, "aa", "1-1", "A1"),
      std::make_tuple("52-52", SgfcConstants::BoardSizeMaximumGo, 52, 52, 52, 1, true, true, false, "ZZ", "52-52", ""),

      // SgfcGoPointNotation::Hybrid
      // Coordinate system origin is lower-left corner
      std::make_tuple("A1", SgfcConstants::BoardSizeDefaultGo, 1, 19, 1, 1, true, true, true, "as", "1-19", "A1"),
      std::make_tuple("T19", SgfcConstants::BoardSizeDefaultGo, 19, 1, 19, 19, true, true, true, "sa", "19-1", "T19"),
      // Letter "I" is not used
      std::make_tuple("H5", SgfcConstants::BoardSizeDefaultGo, 8, 15, 8, 5, true, true, true, "ho", "8-15", "H5"),
      std::make_tuple("J5", SgfcConstants::BoardSizeDefaultGo, 9, 15, 9, 5, true, true, true, "io", "9-15", "J5"),
      // Minimum/Maximum board size
      std::make_tuple("A1", SgfcConstants::BoardSizeMinimum, 1, 1, 1, 1, true, true, true, "aa", "1-1", "A1"),
      std::make_tuple("Z25", SgfcBoardSize { 25, 25 }, 25, 1, 25, 25, true, true, true, "ya", "25-1", "Z25"),

      // As long as a location can be expressed in Hybrid notation it will be
      // done, even if the board is larger than the coordinate space that
      // hybrid notation can cover
      std::make_tuple("yB", SgfcConstants::BoardSizeMaximumGo, 25, 28, 25, 25, true, true, true, "yB", "25-28", "Z25"),
      std::make_tuple("25-28", SgfcConstants::BoardSizeMaximumGo, 25, 28, 25, 25, true, true, true, "yB", "25-28", "Z25"),
      std::make_tuple("Z25", SgfcConstants::BoardSizeMaximumGo, 25, 28, 25, 25, true, true, true, "yB", "25-28", "Z25"),
      std::make_tuple("yA", SgfcConstants::BoardSizeMaximumGo, 25, 27, 25, 26, true, true, false, "yA", "25-27", ""),
      std::make_tuple("25-27", SgfcConstants::BoardSizeMaximumGo, 25, 27, 25, 26, true, true, false, "yA", "25-27", ""),
      std::make_tuple("zB", SgfcConstants::BoardSizeMaximumGo, 26, 28, 26, 25, true, true, false, "zB", "26-28", ""),
      std::make_tuple("26-28", SgfcConstants::BoardSizeMaximumGo, 26, 28, 26, 25, true, true, false, "zB", "26-28", "")
    };

    return testData;
  }

  std::vector<SgfcBoardSize> TestDataGenerator::GetInvalidGoBoardSizes()
  {
    std::vector<SgfcBoardSize> testData =
    {
      // Not square
      SgfcBoardSize { 19, 18 },
      SgfcBoardSize { 18, 19 },
      // Below minimum
      SgfcBoardSize { SgfcConstants::BoardSizeMinimum.Columns - 1, SgfcConstants::BoardSizeMinimum.Rows - 1 },
      // Above maximum
      SgfcBoardSize { SgfcConstants::BoardSizeMaximumGo.Columns + 1, SgfcConstants::BoardSizeMaximumGo.Rows + 1 }
    };

    return testData;
  }

  std::vector<std::pair<std::string, SgfcBoardSize>> TestDataGenerator::GetInvalidGoPointStrings()
  {
    std::vector<std::pair<std::string, SgfcBoardSize>> testData =
    {
      // Invalid because the string is not a valid notation
      std::pair<std::string, SgfcBoardSize> { "", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "foo", SgfcConstants::BoardSizeDefaultGo },
      // Valid SgfcGoPointNotation::Sgf but exceeds the board size
      std::pair<std::string, SgfcBoardSize> { "az", SgfcBoardSize { 25, 25 } },
      std::pair<std::string, SgfcBoardSize> { "za", SgfcBoardSize { 25, 25 } },
      std::pair<std::string, SgfcBoardSize> { "at", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "ta", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "ab", SgfcConstants::BoardSizeMinimum },
      std::pair<std::string, SgfcBoardSize> { "ba", SgfcConstants::BoardSizeMinimum },
      // Invalid SgfcGoPointNotation::Sgf - compounds must be letters
      std::pair<std::string, SgfcBoardSize> { "a$", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "$a", SgfcConstants::BoardSizeDefaultGo },
      // Valid SgfcGoPointNotation::Figure but exceeds the board size
      std::pair<std::string, SgfcBoardSize> { "1-53", SgfcConstants::BoardSizeMaximumGo },
      std::pair<std::string, SgfcBoardSize> { "53-1", SgfcConstants::BoardSizeMaximumGo },
      std::pair<std::string, SgfcBoardSize> { "1-20", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "20-1", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "1-2", SgfcConstants::BoardSizeMinimum },
      std::pair<std::string, SgfcBoardSize> { "2-1", SgfcConstants::BoardSizeMinimum },
      std::pair<std::string, SgfcBoardSize> { "1-0", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "0-1", SgfcConstants::BoardSizeDefaultGo },
      // Invalid SgfcGoPointNotation::Figure - compounds must be numeric
      std::pair<std::string, SgfcBoardSize> { "a-1", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "1-a", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "1a-1", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "1-1a", SgfcConstants::BoardSizeDefaultGo },
      // Looks like SgfcGoPointNotation::Figure, but signed numbers are not recognized
      std::pair<std::string, SgfcBoardSize> { "-1-1", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "1--1", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "+1-1", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "1-+1", SgfcConstants::BoardSizeDefaultGo },
      // Invalid SgfcGoPointNotation::Hybrid
      std::pair<std::string, SgfcBoardSize> { "a1", SgfcConstants::BoardSizeDefaultGo },  // lowercase letters are not allowed
      std::pair<std::string, SgfcBoardSize> { "A0", SgfcConstants::BoardSizeDefaultGo },  // minimum y-axis position is 1
      std::pair<std::string, SgfcBoardSize> { "I1", SgfcConstants::BoardSizeDefaultGo },  // letter "I" is unused
      std::pair<std::string, SgfcBoardSize> { "A26", SgfcConstants::BoardSizeMaximumGo }, // notation cannot address board sizes > 25x25
      // Looks like SgfcGoPointNotation::Hybrid, but signed numbers are not recognized
      std::pair<std::string, SgfcBoardSize> { "A-1", SgfcConstants::BoardSizeDefaultGo },
      std::pair<std::string, SgfcBoardSize> { "A+1", SgfcConstants::BoardSizeDefaultGo }
    };

    return testData;
  }
}
