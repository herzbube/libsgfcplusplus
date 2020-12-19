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

// Project includes
#include "TestDataGenerator.h"
#include <parsing/SgfcValueConverter.h>
#include <SgfcConstants.h>

// C++ Standard Library includes
#include <stdexcept>

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
      SgfcConstants::NoneValueString,
      " \t\r\n",
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
      SgfcConstants::NoneValueString,
      " \t\r\n",
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
      SgfcConstants::NoneValueString,
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
      SgfcConstants::NoneValueString,
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

  std::vector<std::tuple<std::string, SgfcSimpleText, SgfcSimpleText, SgfcSimpleText>> TestDataGenerator::GetSimpleTextStrings()
  {
    // Element 0 = The raw value that is the input for SgfcPropertyDecoder
    //             tests
    // Element 1 = The parsed SgfcSimpleText value if the raw value is used
    //             as input for a standalone single property value
    // Element 2 = The parsed SgfcSimpleText value if the raw value is used
    //             as input for the first value of a composed property value
    // Element 3 = The parsed SgfcSimpleText value if the raw value is used
    //             as input for the second value of a composed property value
    std::vector<std::tuple<std::string, SgfcSimpleText, SgfcSimpleText, SgfcSimpleText>> testData =
    {
      std::make_tuple(SgfcConstants::NoneValueString, SgfcConstants::NoneValueString, SgfcConstants::NoneValueString, SgfcConstants::NoneValueString),
      std::make_tuple("foo", "foo", "foo", "foo"),
      std::make_tuple("foo bar", "foo bar", "foo bar", "foo bar"),
      std::make_tuple("foo  bar", "foo  bar", "foo  bar", "foo  bar"),
      // Whitespace characters other than space must be converted to space.
      // However, the library relies on SGFC doing this conversion, so for the
      // unit tests we make sure that the library does NOT convert.
      std::make_tuple("foo\t\vbar", "foo\t\vbar", "foo\t\vbar", "foo\t\vbar"),
      // Each of the line endings mentioned in the SGF standard must be
      // converted to a single space (even if the line ending consists of two
      // characters).
      std::make_tuple("foo\nbar", "foo bar", "foo bar", "foo bar"),
      std::make_tuple("foo\rbar", "foo bar", "foo bar", "foo bar"),
      std::make_tuple("foo\r\nbar", "foo bar", "foo bar", "foo bar"),
      std::make_tuple("foo\n\rbar", "foo bar", "foo bar", "foo bar"),
      // Escaped line breaks are removed entirely
      std::make_tuple("foo\\\nbar", "foobar", "foobar", "foobar"),
      std::make_tuple("foo\\\rbar", "foobar", "foobar", "foobar"),
      std::make_tuple("foo\\\r\nbar", "foobar", "foobar", "foobar"),
      std::make_tuple("foo\\\n\rbar", "foobar", "foobar", "foobar"),
      // The escape character is removed if it escapes one of the special
      // characters mentioned in the SGF standard ("]", "\")
      std::make_tuple("foo\\]bar", "foo]bar", "foo]bar", "foo]bar"),
      std::make_tuple("foo\\\\bar", "foo\\bar", "foo\\bar", "foo\\bar"),
      // The escape character is not removed if it does not escape one of the
      // special characters mentioned in the SGF standard. The reason is that
      // the library expects that SGFC removes those unnecessary escape
      // characters and it therefore does not perform escape character handling
      // itself.
      std::make_tuple("foo\\bar", "foo\\bar", "foo\\bar", "foo\\bar"),
      std::make_tuple("foo\\[bar", "foo\\[bar", "foo\\[bar", "foo\\[bar"),
      // The escape character is removed only if the value is used as input for
      // the first or second value of a composed value (for the second value
      // this is a quirk of SGFC which does not remove the unnecessary escape
      // character as it should, so libsgfc++ has to do it). The escape
      // character is not removed for a standalone property value because there
      // it is expected that SGFC does the removal.
      std::make_tuple("foo\\:bar", "foo\\:bar", "foo:bar", "foo:bar"),
      // We also test whether multiple consecutive escape characters work. There
      // is no order of precedence, an escape character simply always must act
      // upon the character that follows it. E.g. "\\:" escapes the escape
      // character, not the ":" character.
      std::make_tuple("foo\\\\:bar", "foo\\:bar", "foo\\:bar", "foo\\:bar"),
      std::make_tuple("foo\\\\\\:bar", "foo\\\\:bar", "foo\\:bar", "foo\\:bar"),
      std::make_tuple("foo\\\\\\\\:bar", "foo\\\\:bar", "foo\\\\:bar", "foo\\\\:bar")
    };

    return testData;
  }

  std::vector<std::tuple<std::string, SgfcText, SgfcText, SgfcText>> TestDataGenerator::GetTextStrings()
  {
    // Element 0 = The raw value that is the input for SgfcPropertyDecoder
    //             tests
    // Element 1 = The parsed SgfcSimpleText value if the raw value is used
    //             as input for a standalone single property value
    // Element 2 = The parsed SgfcSimpleText value if the raw value is used
    //             as input for the first value of a composed property value
    // Element 3 = The parsed SgfcSimpleText value if the raw value is used
    //             as input for the second value of a composed property value
    std::vector<std::tuple<std::string, SgfcText, SgfcText, SgfcText>> testData =
    {
      std::make_tuple(SgfcConstants::NoneValueString, SgfcConstants::NoneValueString, SgfcConstants::NoneValueString, SgfcConstants::NoneValueString),
      std::make_tuple("foo", "foo", "foo", "foo"),
      std::make_tuple("foo bar", "foo bar", "foo bar", "foo bar"),
      std::make_tuple("foo  bar", "foo  bar", "foo  bar", "foo  bar"),
      // Whitespace characters other than line breaks must be converted to
      // space. However, the library relies on SGFC doing this conversion, so
      // for the unit tests we make sure that the library does NOT convert.
      std::make_tuple("foo\t\vbar", "foo\t\vbar", "foo\t\vbar", "foo\t\vbar"),
      // Un-escaped line breaks (the SGF standard calls them "hard line breaks")
      // must be preserved.
      std::make_tuple("foo\nbar", "foo\nbar", "foo\nbar", "foo\nbar"),
      std::make_tuple("foo\rbar", "foo\rbar", "foo\rbar", "foo\rbar"),
      std::make_tuple("foo\r\nbar", "foo\r\nbar", "foo\r\nbar", "foo\r\nbar"),
      std::make_tuple("foo\n\rbar", "foo\n\rbar", "foo\n\rbar", "foo\n\rbar"),
      // Escaped line breaks (the SGF standard calls them "soft line breaks")
      // are removed entirely
      std::make_tuple("foo\\\nbar", "foobar", "foobar", "foobar"),
      std::make_tuple("foo\\\rbar", "foobar", "foobar", "foobar"),
      std::make_tuple("foo\\\r\nbar", "foobar", "foobar", "foobar"),
      std::make_tuple("foo\\\n\rbar", "foobar", "foobar", "foobar"),
      // The escape character is removed if it escapes one of the special
      // characters mentioned in the SGF standard ("]", "\" and ":")
      std::make_tuple("foo\\]bar", "foo]bar", "foo]bar", "foo]bar"),
      std::make_tuple("foo\\\\bar", "foo\\bar", "foo\\bar", "foo\\bar"),
      // The escape character is not removed if it does not escape one of the
      // special characters mentioned in the SGF standard. The reason is that
      // the library expects that SGFC removes those unnecessary escape
      // characters and it therefore does not perform escape character handling
      // itself.
      std::make_tuple("foo\\bar", "foo\\bar", "foo\\bar", "foo\\bar"),
      std::make_tuple("foo\\[bar", "foo\\[bar", "foo\\[bar", "foo\\[bar"),
      // The escape character is removed only if the value is used as input for
      // the first or second value of a composed value (for the second value
      // this is a quirk of SGFC which does not remove the unnecessary escape
      // character as it should, so libsgfc++ has to do it). The escape
      // character is not removed for a standalone property value because there
      // it is expected that SGFC does the removal.
      std::make_tuple("foo\\:bar", "foo\\:bar", "foo:bar", "foo:bar"),
      // We also test whether multiple consecutive escape characters work. There
      // is no order of precedence, an escape character simply always must act
      // upon the character that follows it. E.g. "\\:" escapes the escape
      // character, not the ":" character.
      std::make_tuple("foo\\\\:bar", "foo\\:bar", "foo\\:bar", "foo\\:bar"),
      std::make_tuple("foo\\\\\\:bar", "foo\\\\:bar", "foo\\:bar", "foo\\:bar"),
      std::make_tuple("foo\\\\\\\\:bar", "foo\\\\:bar", "foo\\\\:bar", "foo\\\\:bar")
    };

    return testData;
  }

  std::vector<std::tuple<SgfcPoint, SgfcBoardSize, int, int, int, int, bool, bool, bool, std::string, std::string, std::string, std::string, SgfcMove, SgfcPoint, SgfcStone>> TestDataGenerator::GetGoPointStrings()
  {
    // Element 0 = The SgfcPoint value that is the input to the GoPoint
    //             constructor. Can be a value in any of the 3 notations
    //             Sgf, Figure, Hybrid. Cannot be used as input for
    //             SgfcPropertyDecoder tests: SgfcPropertyDecoder requires
    //             a raw value in Sgf Notation as input, and an SgfcPoint
    //             value in Sgf Notation is its output.
    // Element 1 = The board size required to interpret the SgfcPoint value or
    //             the raw value.
    // Elements 2-3 = x/y position when SgfcCoordinateSystem::UpperLeftOrigin
    // Elements 4-5 = x/y position when SgfcCoordinateSystem::LowerLeftOrigin
    // Elements 6-8 = HasPosition value for the 3 notations Sgf, Figure, Hybrid
    // Elements 9-11 = Position value for the 3 notations Sgf, Figure, Hybrid
    // Element 12 = The raw string value that is the input to
    //              SgfcPropertyDecoder when it generates a Move, Point or Stone
    //              property value object
    // Elements 13-15 = The SgfcMove, SgfcPoint and SgfcStone values that are
    //                  the output of SgfcPropertyDecoder when it generates a
    //                  Move, Point or Stone property value object
    std::vector<std::tuple<SgfcPoint, SgfcBoardSize, int, int, int, int, bool, bool, bool, std::string, std::string, std::string, std::string, SgfcMove, SgfcPoint, SgfcStone>> testData =
    {
      // SgfcGoPointNotation::Sgf
      // Coordinate system origin is upper-left corner
      std::make_tuple("as", SgfcConstants::BoardSizeDefaultGo, 1, 19, 1, 1, true, true, true, "as", "1-19", "A1", "as", "as", "as", "as"),
      std::make_tuple("sa", SgfcConstants::BoardSizeDefaultGo, 19, 1, 19, 19, true, true, true, "sa", "19-1", "T19", "sa", "sa", "sa", "sa"),
      // Uppercase letters start at 26
      std::make_tuple("Az", SgfcConstants::BoardSizeMaximumGo, 27, 26, 27, 27, true, true, false, "Az", "27-26", "", "Az", "Az", "Az", "Az"),
      std::make_tuple("zA", SgfcConstants::BoardSizeMaximumGo, 26, 27, 26, 26, true, true, false, "zA", "26-27", "", "zA", "zA", "zA", "zA"),
      // Minimum/Maximum board size
      std::make_tuple("aa", SgfcConstants::BoardSizeMinimum, 1, 1, 1, 1, true, true, true, "aa", "1-1", "A1", "aa", "aa", "aa", "aa"),
      std::make_tuple("ZZ", SgfcConstants::BoardSizeMaximumGo, 52, 52, 52, 1, true, true, false, "ZZ", "52-52", "", "ZZ", "ZZ", "ZZ", "ZZ"),
      // Non-square board
      std::make_tuple("bc", SgfcBoardSize { 7, 3 }, 2, 3, 2, 1, true, true, true, "bc", "2-3", "B1", "bc", "bc", "bc", "bc"),

      // SgfcGoPointNotation::Figure
      // Coordinate system origin is upper-left corner
      std::make_tuple("1-19", SgfcConstants::BoardSizeDefaultGo, 1, 19, 1, 1, true, true, true, "as", "1-19", "A1", "as", "as", "as", "as"),
      std::make_tuple("19-1", SgfcConstants::BoardSizeDefaultGo, 19, 1, 19, 19, true, true, true, "sa", "19-1", "T19", "sa", "sa", "sa", "sa"),
      // Minimum/Maximum board size
      std::make_tuple("1-1", SgfcConstants::BoardSizeMinimum, 1, 1, 1, 1, true, true, true, "aa", "1-1", "A1", "aa", "aa", "aa", "aa"),
      std::make_tuple("52-52", SgfcConstants::BoardSizeMaximumGo, 52, 52, 52, 1, true, true, false, "ZZ", "52-52", "", "ZZ", "ZZ", "ZZ", "ZZ"),
      // Non-square board
      std::make_tuple("2-3", SgfcBoardSize { 7, 3 }, 2, 3, 2, 1, true, true, true, "bc", "2-3", "B1", "bc", "bc", "bc", "bc"),

      // SgfcGoPointNotation::Hybrid
      // Coordinate system origin is lower-left corner
      std::make_tuple("A1", SgfcConstants::BoardSizeDefaultGo, 1, 19, 1, 1, true, true, true, "as", "1-19", "A1", "as", "as", "as", "as"),
      std::make_tuple("T19", SgfcConstants::BoardSizeDefaultGo, 19, 1, 19, 19, true, true, true, "sa", "19-1", "T19", "sa", "sa", "sa", "sa"),
      // Letter "I" is not used
      std::make_tuple("H5", SgfcConstants::BoardSizeDefaultGo, 8, 15, 8, 5, true, true, true, "ho", "8-15", "H5", "ho", "ho", "ho", "ho"),
      std::make_tuple("J5", SgfcConstants::BoardSizeDefaultGo, 9, 15, 9, 5, true, true, true, "io", "9-15", "J5", "io", "io", "io", "io"),
      // Minimum/Maximum board size
      std::make_tuple("A1", SgfcConstants::BoardSizeMinimum, 1, 1, 1, 1, true, true, true, "aa", "1-1", "A1", "aa", "aa", "aa", "aa"),
      std::make_tuple("Z25", SgfcBoardSize { 25, 25 }, 25, 1, 25, 25, true, true, true, "ya", "25-1", "Z25", "ya", "ya", "ya", "ya"),
      // Non-square board
      std::make_tuple("B1", SgfcBoardSize { 7, 3 }, 2, 3, 2, 1, true, true, true, "bc", "2-3", "B1", "bc", "bc", "bc", "bc"),

      // As long as a location can be expressed in Hybrid notation it will be
      // done, even if the board is larger than the coordinate space that
      // hybrid notation can cover
      std::make_tuple("yB", SgfcConstants::BoardSizeMaximumGo, 25, 28, 25, 25, true, true, true, "yB", "25-28", "Z25", "yB", "yB", "yB", "yB"),
      std::make_tuple("25-28", SgfcConstants::BoardSizeMaximumGo, 25, 28, 25, 25, true, true, true, "yB", "25-28", "Z25", "yB", "yB", "yB", "yB"),
      std::make_tuple("Z25", SgfcConstants::BoardSizeMaximumGo, 25, 28, 25, 25, true, true, true, "yB", "25-28", "Z25", "yB", "yB", "yB", "yB"),
      std::make_tuple("yA", SgfcConstants::BoardSizeMaximumGo, 25, 27, 25, 26, true, true, false, "yA", "25-27", "", "yA", "yA", "yA", "yA"),
      std::make_tuple("25-27", SgfcConstants::BoardSizeMaximumGo, 25, 27, 25, 26, true, true, false, "yA", "25-27", "", "yA", "yA", "yA", "yA"),
      std::make_tuple("zB", SgfcConstants::BoardSizeMaximumGo, 26, 28, 26, 25, true, true, false, "zB", "26-28", "", "zB", "zB", "zB", "zB"),
      std::make_tuple("26-28", SgfcConstants::BoardSizeMaximumGo, 26, 28, 26, 25, true, true, false, "zB", "26-28", "", "zB", "zB", "zB", "zB")
    };

    return testData;
  }

  std::vector<SgfcBoardSize> TestDataGenerator::GetInvalidGoBoardSizes()
  {
    std::vector<SgfcBoardSize> testData =
    {
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
      std::pair<std::string, SgfcBoardSize> { SgfcConstants::NoneValueString, SgfcConstants::BoardSizeDefaultGo },
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

  std::vector<std::tuple<std::string, SgfcGameType, SgfcBoardSize>> TestDataGenerator::GetValidSZSquareStrings()
  {
    std::vector<std::tuple<std::string, SgfcGameType, SgfcBoardSize>> testData =
    {
      // For Go any board size is valid as long as it falls between the minimum
      // and the maximum
      std::make_tuple("1", SgfcGameType::Go, SgfcConstants::BoardSizeMinimum),
      std::make_tuple("19", SgfcGameType::Go, SgfcConstants::BoardSizeDefaultGo),
      std::make_tuple("20", SgfcGameType::Go, SgfcBoardSize {20, 20}),
      std::make_tuple("52", SgfcGameType::Go, SgfcConstants::BoardSizeMaximumGo),
      // For non-Go game types any board size is valid as long as it is above
      // the minimum
      std::make_tuple("1", SgfcGameType::Chess, SgfcBoardSize {1, 1}),
      std::make_tuple("8", SgfcGameType::Chess, SgfcBoardSize {8, 8}),
      std::make_tuple("9", SgfcGameType::Chess, SgfcBoardSize {9, 9}),
      std::make_tuple("1000", SgfcGameType::Chess, SgfcBoardSize {1000, 1000}),
      std::make_tuple("1", SgfcGameType::PhilosophersFootball, SgfcBoardSize {1, 1}),
      std::make_tuple("8", SgfcGameType::PhilosophersFootball, SgfcBoardSize {8, 8}),
      std::make_tuple("9", SgfcGameType::PhilosophersFootball, SgfcBoardSize {9, 9}),
      std::make_tuple("1000", SgfcGameType::PhilosophersFootball, SgfcBoardSize {1000, 1000})
    };

    return testData;
  }

  std::vector<std::tuple<std::string, SgfcGameType>> TestDataGenerator::GetInvalidSZSquareStrings()
  {
    std::vector<std::tuple<std::string, SgfcGameType>> testData =
    {
      // For Go any board size that is below the minimum is invalid ...
      std::make_tuple("-42", SgfcGameType::Go),
      std::make_tuple("-1", SgfcGameType::Go),
      std::make_tuple("0", SgfcGameType::Go),
      // ... as well as any board size that is above the maximum
      std::make_tuple("53", SgfcGameType::Go),
      std::make_tuple("1000", SgfcGameType::Go),
      // For non-Go game types the board size is invalid only if it is below
      // the minimum. There is no maximum.
      std::make_tuple("-42", SgfcGameType::Chess),
      std::make_tuple("-1", SgfcGameType::Chess),
      std::make_tuple("0", SgfcGameType::Chess),
      std::make_tuple("-42", SgfcGameType::Kropki),
      std::make_tuple("-1", SgfcGameType::Kropki),
      std::make_tuple("0", SgfcGameType::Kropki)
    };

    return testData;
  }

  std::vector<std::tuple<std::string, std::string, SgfcGameType, SgfcBoardSize>> TestDataGenerator::GetValidSZRectangularStrings()
  {
    std::vector<std::tuple<std::string, std::string, SgfcGameType, SgfcBoardSize>> testData =
    {
      // For Go any board size is valid as long as row and colum fall between
      // the minimum and the maximum
      std::make_tuple("1", "2", SgfcGameType::Go, SgfcBoardSize {1, 2}),
      std::make_tuple("1", "19", SgfcGameType::Go, SgfcBoardSize {1, 19}),
      std::make_tuple("1", "20", SgfcGameType::Go, SgfcBoardSize {1, 20}),
      std::make_tuple("1", "52", SgfcGameType::Go, SgfcBoardSize {1, 52}),
      std::make_tuple("2", "1", SgfcGameType::Go, SgfcBoardSize {2, 1}),
      std::make_tuple("19", "1", SgfcGameType::Go, SgfcBoardSize {19, 1}),
      std::make_tuple("20", "1", SgfcGameType::Go, SgfcBoardSize {20, 1}),
      std::make_tuple("52", "1", SgfcGameType::Go, SgfcBoardSize {52, 1}),
      // As long as its values are within the limits, a rectangular board size
      // is valid even if the two values are the same
      std::make_tuple("1", "1", SgfcGameType::Go, SgfcBoardSize {1, 1}),
      std::make_tuple("19", "19", SgfcGameType::Go, SgfcBoardSize {19, 19}),
      std::make_tuple("20", "20", SgfcGameType::Go, SgfcBoardSize {20, 20}),
      std::make_tuple("52", "52", SgfcGameType::Go, SgfcBoardSize {52, 52}),
      // For non-Go game types any board size is valid as long as neither row
      // nor column fall below the minimum
      std::make_tuple("1", "1", SgfcGameType::Chess, SgfcBoardSize {1, 1}),
      std::make_tuple("1", "2", SgfcGameType::Chess, SgfcBoardSize {1, 2}),
      std::make_tuple("1", "8", SgfcGameType::Chess, SgfcBoardSize {1, 8}),
      std::make_tuple("8", "8", SgfcGameType::Chess, SgfcBoardSize {8, 8}),
      std::make_tuple("9", "1000", SgfcGameType::Chess, SgfcBoardSize {9, 1000}),
      std::make_tuple("9", "1000", SgfcGameType::Chess, SgfcBoardSize {9, 1000}),
      std::make_tuple("1", "1", SgfcGameType::Zertz, SgfcBoardSize {1, 1}),
      std::make_tuple("1", "2", SgfcGameType::Zertz, SgfcBoardSize {1, 2}),
      std::make_tuple("1", "8", SgfcGameType::Zertz, SgfcBoardSize {1, 8}),
      std::make_tuple("8", "8", SgfcGameType::Zertz, SgfcBoardSize {8, 8}),
      std::make_tuple("9", "1000", SgfcGameType::Zertz, SgfcBoardSize {9, 1000}),
      std::make_tuple("9", "1000", SgfcGameType::Zertz, SgfcBoardSize {9, 1000})
    };

    return testData;
  }

  std::vector<std::tuple<std::string, std::string, SgfcGameType>> TestDataGenerator::GetInvalidSZRectangularStrings()
  {
    std::vector<std::tuple<std::string, std::string, SgfcGameType>> testData =
    {
      // A rectangular board size is invalid for Go if either the row or column
      // are below the minimum ...
      std::make_tuple("-42", "19", SgfcGameType::Go),
      std::make_tuple("-1", "19", SgfcGameType::Go),
      std::make_tuple("0", "19", SgfcGameType::Go),
      std::make_tuple("19", "-42", SgfcGameType::Go),
      std::make_tuple("19", "-1", SgfcGameType::Go),
      std::make_tuple("19", "0", SgfcGameType::Go),
      // ... or above the maximum
      std::make_tuple("1000", "19", SgfcGameType::Go),
      std::make_tuple("100", "19", SgfcGameType::Go),
      std::make_tuple("53", "19", SgfcGameType::Go),
      std::make_tuple("19", "1000", SgfcGameType::Go),
      std::make_tuple("19", "100", SgfcGameType::Go),
      std::make_tuple("19", "53", SgfcGameType::Go),
      // For non-Go game types the board size is invalid only if either the
      // row or column are below the minimum
      std::make_tuple("-42", "19", SgfcGameType::Chess),
      std::make_tuple("-1", "19", SgfcGameType::Chess),
      std::make_tuple("0", "19", SgfcGameType::Chess),
      std::make_tuple("19", "-42", SgfcGameType::Chess),
      std::make_tuple("19", "-1", SgfcGameType::Chess),
      std::make_tuple("19", "0", SgfcGameType::Chess)
    };

    return testData;
  }

  std::vector<std::tuple<SgfcBoardSize, SgfcGameType, SgfcBoardSize>> TestDataGenerator::GetValidBoardSizes()
  {
    std::vector<std::tuple<SgfcBoardSize, SgfcGameType, SgfcBoardSize>> testData;

    auto testDataToConvertSquare = GetValidSZSquareStrings();
    for (auto testDataElementToConvertSquare : testDataToConvertSquare)
    {
      SgfcNumber boardSizeColumnAndRow = TestDataGenerator::ConvertStringToNumberOrThrow(
        std::get<0>(testDataElementToConvertSquare));

      testData.push_back(std::make_tuple(
        SgfcBoardSize {boardSizeColumnAndRow, boardSizeColumnAndRow},
        std::get<1>(testDataElementToConvertSquare),
        std::get<2>(testDataElementToConvertSquare)));
    }

    auto testDataToConvertRectangular = GetValidSZRectangularStrings();
    for (auto testDataElementToConvertRectangular : testDataToConvertRectangular)
    {
      SgfcNumber boardSizeColumn = TestDataGenerator::ConvertStringToNumberOrThrow(
        std::get<0>(testDataElementToConvertRectangular));
      SgfcNumber boardSizeRow = TestDataGenerator::ConvertStringToNumberOrThrow(
        std::get<1>(testDataElementToConvertRectangular));

      testData.push_back(std::make_tuple(
        SgfcBoardSize {boardSizeColumn, boardSizeRow},
        std::get<2>(testDataElementToConvertRectangular),
        std::get<3>(testDataElementToConvertRectangular)));
    }

    return testData;
  }

  std::vector<std::tuple<SgfcBoardSize, SgfcGameType>> TestDataGenerator::GetInvalidBoardSizes()
  {
    std::vector<std::tuple<SgfcBoardSize, SgfcGameType>> testData;

    auto testDataToConvertSquare = GetInvalidSZSquareStrings();
    for (auto testDataElementToConvertSquare : testDataToConvertSquare)
    {
      SgfcNumber boardSizeColumnAndRow = TestDataGenerator::ConvertStringToNumberOrThrow(
        std::get<0>(testDataElementToConvertSquare));

      testData.push_back(std::make_tuple(
        SgfcBoardSize {boardSizeColumnAndRow, boardSizeColumnAndRow},
        std::get<1>(testDataElementToConvertSquare)));
    }

    auto testDataToConvertRectangular = GetInvalidSZRectangularStrings();
    for (auto testDataElementToConvertRectangular : testDataToConvertRectangular)
    {
      SgfcNumber boardSizeColumn = TestDataGenerator::ConvertStringToNumberOrThrow(
        std::get<0>(testDataElementToConvertRectangular));
      SgfcNumber boardSizeRow = TestDataGenerator::ConvertStringToNumberOrThrow(
        std::get<1>(testDataElementToConvertRectangular));

      if (std::get<2>(testDataElementToConvertRectangular) == SgfcGameType::Go && boardSizeColumn == boardSizeRow)
      {
        // The test data that we convert contains a special case where a board
        // size consisting of two string values is invalid for SgfcGameType::Go
        // even if the two values are the same. This makes sense for raw SGF
        // content, where the SGF standard mandates that SgfcGameType::Go can
        // only have a non-composed board size. But here we convert the data
        // into an SgfcBoardSize value - after the conversion has taken place
        // the distinction between single and composed values is no longer
        // possible because SgfcBoardSize always has two values. Because a
        // receiver of the test data we return from this function cannot handle
        // the distinction, we filter out that particular element.
        continue;
      }

      testData.push_back(std::make_tuple(
        SgfcBoardSize {boardSizeColumn, boardSizeRow},
        std::get<2>(testDataElementToConvertRectangular)));
    }

    return testData;
  }

  SgfcNumber TestDataGenerator::ConvertStringToNumberOrThrow(const std::string& string)
  {
    SgfcValueConverter valueConverter;
    std::string typeConversionErrorMessage;

    SgfcNumber number;
    bool conversionResult = valueConverter.TryConvertStringToNumberValue(
      string, number, typeConversionErrorMessage);

    if (conversionResult)
      return number;
    else
      throw new std::logic_error("Failed to convert test data");
  }

  std::vector<std::tuple<SgfcArgumentType, std::string>> TestDataGenerator::GetArgumentTypesWithoutParameters()
  {
    std::vector<std::tuple<SgfcArgumentType, std::string>> testData =
    {
      std::make_tuple(SgfcArgumentType::DisableWarningMessages, "-w"),
      std::make_tuple(SgfcArgumentType::LineBreakAtEndOfNode, "-L"),
      std::make_tuple(SgfcArgumentType::NoSoftLineBreaksInTextValues, "-t"),
      std::make_tuple(SgfcArgumentType::DeleteMarkupOnCurrentMove, "-m"),
      std::make_tuple(SgfcArgumentType::DeleteEmptyNodes, "-n"),
      std::make_tuple(SgfcArgumentType::DeleteObsoleteProperties, "-o"),
      std::make_tuple(SgfcArgumentType::DeleteUnknownProperties, "-u"),
      std::make_tuple(SgfcArgumentType::UseOldPassMoveNotation, "-p"),
      std::make_tuple(SgfcArgumentType::EnableRestrictiveChecking, "-r"),
      std::make_tuple(SgfcArgumentType::CorrectVariationLevelAndRootMoves, "-v"),
      std::make_tuple(SgfcArgumentType::ReverseVariationOrdering, "-z"),
      std::make_tuple(SgfcArgumentType::ExpandCompressedPointLists, "-e")
    };

    return testData;
  }

  std::vector<SgfcArgumentType> TestDataGenerator::GetArgumentTypesWithIntegerTypeParameter()
  {
    std::vector<SgfcArgumentType> testData =
    {
      SgfcArgumentType::BeginningOfSgfData,
      SgfcArgumentType::HardLineBreakMode,
      SgfcArgumentType::EncodingMode,
    };

    return testData;
  }

  std::vector<SgfcArgumentType> TestDataGenerator::GetArgumentTypesWithStringTypeParameter()
  {
    std::vector<SgfcArgumentType> testData =
    {
      SgfcArgumentType::DefaultEncoding,
      SgfcArgumentType::ForcedEncoding,
    };

    return testData;
  }

  std::vector<SgfcArgumentType> TestDataGenerator::GetArgumentTypesWithPropertyTypeParameter()
  {
    std::vector<SgfcArgumentType> testData =
    {
      SgfcArgumentType::DeletePropertyType
    };

    return testData;
  }

  std::vector<SgfcArgumentType> TestDataGenerator::GetArgumentTypesWithMessageIDParameter()
  {
    std::vector<SgfcArgumentType> testData =
    {
      SgfcArgumentType::DisableMessageID
    };

    return testData;
  }

  std::vector<SgfcArgumentType> TestDataGenerator::GetArgumentTypesWithParameter()
  {
    std::vector<SgfcArgumentType> testData;

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithIntegerTypeParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithStringTypeParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithPropertyTypeParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithMessageIDParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    return testData;
  }

  std::vector<SgfcArgumentType> TestDataGenerator::GetArgumentTypesWithoutIntegerTypeParameter()
  {
    std::vector<SgfcArgumentType> testData;

    for (auto testDataArgumentTypeWithoutParameters : GetArgumentTypesWithoutParameters())
      testData.push_back(std::get<0>(testDataArgumentTypeWithoutParameters));

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithStringTypeParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithPropertyTypeParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithMessageIDParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    return testData;
  }

  std::vector<SgfcArgumentType> TestDataGenerator::GetArgumentTypesWithoutStringTypeParameter()
  {
    std::vector<SgfcArgumentType> testData;

    for (auto testDataArgumentTypeWithoutParameters : GetArgumentTypesWithoutParameters())
      testData.push_back(std::get<0>(testDataArgumentTypeWithoutParameters));

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithIntegerTypeParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithPropertyTypeParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithMessageIDParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    return testData;
  }

  std::vector<SgfcArgumentType> TestDataGenerator::GetArgumentTypesWithoutPropertyTypeParameter()
  {
    std::vector<SgfcArgumentType> testData;

    for (auto testDataArgumentTypeWithoutParameters : GetArgumentTypesWithoutParameters())
      testData.push_back(std::get<0>(testDataArgumentTypeWithoutParameters));

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithIntegerTypeParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithStringTypeParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithMessageIDParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    return testData;
  }

  std::vector<SgfcArgumentType> TestDataGenerator::GetArgumentTypesWithoutMessageIDParameter()
  {
    std::vector<SgfcArgumentType> testData;

    for (auto testDataArgumentTypeWithoutParameters : GetArgumentTypesWithoutParameters())
      testData.push_back(std::get<0>(testDataArgumentTypeWithoutParameters));

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithIntegerTypeParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithStringTypeParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    for (auto argumentTypeWithIntegerTypeParameter : GetArgumentTypesWithPropertyTypeParameter())
      testData.push_back(argumentTypeWithIntegerTypeParameter);

    return testData;
  }

  std::vector<std::tuple<SgfcArgumentType, int, std::string>> TestDataGenerator::GetArgumentTypesWithValidIntegerTypeParameter()
  {
    std::vector<std::tuple<SgfcArgumentType, int, std::string>> testData =
    {
      std::make_tuple(SgfcArgumentType::BeginningOfSgfData, 1, "-b1"),
      std::make_tuple(SgfcArgumentType::BeginningOfSgfData, 2, "-b2"),
      std::make_tuple(SgfcArgumentType::BeginningOfSgfData, 3, "-b3"),
      std::make_tuple(SgfcArgumentType::HardLineBreakMode, 1, "-l1"),
      std::make_tuple(SgfcArgumentType::HardLineBreakMode, 2, "-l2"),
      std::make_tuple(SgfcArgumentType::HardLineBreakMode, 3, "-l3"),
      std::make_tuple(SgfcArgumentType::HardLineBreakMode, 4, "-l4")
    };

    return testData;
  }

  std::vector<std::tuple<SgfcArgumentType, int>> TestDataGenerator::GetArgumentTypesWithInvalidIntegerTypeParameter()
  {
    std::vector<std::tuple<SgfcArgumentType, int>> testData =
    {
      // Arguments that require an integer type parameter, but use a value that
      // is out of bounds
      std::make_tuple(SgfcArgumentType::BeginningOfSgfData, -1),
      std::make_tuple(SgfcArgumentType::BeginningOfSgfData, 0),
      std::make_tuple(SgfcArgumentType::BeginningOfSgfData, 4),
      std::make_tuple(SgfcArgumentType::HardLineBreakMode, -1),
      std::make_tuple(SgfcArgumentType::HardLineBreakMode, 0),
      std::make_tuple(SgfcArgumentType::HardLineBreakMode, 5),
      // Arguments that do not require an integer type parameter
      std::make_tuple(SgfcArgumentType::DeleteEmptyNodes, 1),
      std::make_tuple(SgfcArgumentType::DefaultEncoding, 1),
      std::make_tuple(SgfcArgumentType::DeletePropertyType, 1),
      std::make_tuple(SgfcArgumentType::DisableMessageID, 1),
    };

    return testData;
  }

  std::vector<std::tuple<SgfcArgumentType, std::string, std::string>> TestDataGenerator::GetArgumentTypesWithValidStringTypeParameter()
  {
    std::vector<std::tuple<SgfcArgumentType, std::string, std::string>> testData =
    {
      std::make_tuple(SgfcArgumentType::DefaultEncoding, "UTF-8", "--default-encoding=UTF-8")
    };

    return testData;
  }

  std::vector<std::tuple<SgfcArgumentType, std::string>> TestDataGenerator::GetArgumentTypesWithInvalidStringTypeParameter()
  {
    std::vector<std::tuple<SgfcArgumentType, std::string>> testData =
    {
      // Arguments that require a string type parameter, but use a value that
      // is not allowed
      std::make_tuple(SgfcArgumentType::DefaultEncoding, "foo"),
      std::make_tuple(SgfcArgumentType::ForcedEncoding, "foo"),
      // Arguments that do not require an SgfcPropertyType parameter
      std::make_tuple(SgfcArgumentType::DeleteEmptyNodes, "UTF-8"),
      std::make_tuple(SgfcArgumentType::BeginningOfSgfData, "UTF-8"),
      std::make_tuple(SgfcArgumentType::DeletePropertyType, "UTF-8"),
      std::make_tuple(SgfcArgumentType::DisableMessageID, "UTF-8")
    };

    return testData;
  }

  std::vector<std::tuple<SgfcArgumentType, SgfcPropertyType, std::string>> TestDataGenerator::GetArgumentTypesWithValidPropertyTypeParameter()
  {
    std::vector<std::tuple<SgfcArgumentType, SgfcPropertyType, std::string>> testData =
    {
      std::make_tuple(SgfcArgumentType::DeletePropertyType, SgfcPropertyType::GM, "-yGM")
    };

    return testData;
  }

  std::vector<std::tuple<SgfcArgumentType, SgfcPropertyType>> TestDataGenerator::GetArgumentTypesWithInvalidPropertyTypeParameter()
  {
    std::vector<std::tuple<SgfcArgumentType, SgfcPropertyType>> testData =
    {
      // Arguments that require an SgfcPropertyType parameter, but use a
      // statically cast numeric value
      std::make_tuple(SgfcArgumentType::DeletePropertyType, static_cast<SgfcPropertyType>(-1)),
      std::make_tuple(SgfcArgumentType::DeletePropertyType, static_cast<SgfcPropertyType>(1000)),
      // Arguments that do not require an SgfcPropertyType parameter
      std::make_tuple(SgfcArgumentType::DeleteEmptyNodes, SgfcPropertyType::BO),
      std::make_tuple(SgfcArgumentType::BeginningOfSgfData, SgfcPropertyType::BO),
      std::make_tuple(SgfcArgumentType::DefaultEncoding, SgfcPropertyType::BO),
      std::make_tuple(SgfcArgumentType::DisableMessageID, SgfcPropertyType::BO)
    };

    return testData;
  }

  std::vector<std::tuple<SgfcArgumentType, SgfcMessageID, std::string>> TestDataGenerator::GetArgumentTypesWithValidMessageIDParameter()
  {
    std::vector<std::tuple<SgfcArgumentType, SgfcMessageID, std::string>> testData =
    {
      std::make_tuple(SgfcArgumentType::DisableMessageID, SgfcMessageID::UnknownPropertyDeleted, "-d35"),
      // Disabling a fatal error message does not lead to invalid arguments, it
      // simply has no effect
      std::make_tuple(SgfcArgumentType::DisableMessageID, SgfcMessageID::UnknownCommandLineOption, "-d2")
    };

    return testData;
  }

  std::vector<std::tuple<SgfcArgumentType, SgfcMessageID>> TestDataGenerator::GetArgumentTypesWithInvalidMessageIDParameter()
  {
    std::vector<std::tuple<SgfcArgumentType, SgfcMessageID>> testData =
    {
      // Arguments that require an SgfcMessageID parameter, but use an
      // enumerator value whose underlying numeric value is not known to SGFC
      // (libsgfc++ message IDs with an underlying negative numeric value, or
      // #SgfcMessageID::UnknownSgfcMessageID).
      std::make_tuple(SgfcArgumentType::DisableMessageID, SgfcMessageID::ParseArgumentError),
      std::make_tuple(SgfcArgumentType::DisableMessageID, SgfcMessageID::UnknownSgfcMessageID),
      // Arguments that require an SgfcMessageID parameter, but use a statically
      // cast numeric value that is not known to SGFC
      // - Negative numeric values are all treated as invalid
      // - Numeric value 0 (zero) is specially tested for because the public
      //   API documentation includes 0 (zero) in the range of message IDs
      //   that can be generated by SGFC, although in fact SGFC does not know
      //   an error code 0.
      // - Numeric value 1000 is not an error code known to SGFC
      std::make_tuple(SgfcArgumentType::DisableMessageID, static_cast<SgfcMessageID>(-42)),
      std::make_tuple(SgfcArgumentType::DisableMessageID, static_cast<SgfcMessageID>(0)),
      std::make_tuple(SgfcArgumentType::DisableMessageID, static_cast<SgfcMessageID>(1000)),
      // Although SgfcMessageID has no enumerator with an underlying numeric
      // value 0 (zero), a library client might think
      // The public API documentation says that underlying numeric value >= 0
      // are from SGFC.
      std::make_tuple(SgfcArgumentType::DisableMessageID, static_cast<SgfcMessageID>(0)),
      // Arguments that do not require an SgfcMessageID parameter
      std::make_tuple(SgfcArgumentType::DeleteEmptyNodes, SgfcMessageID::UnknownPropertyDeleted),
      std::make_tuple(SgfcArgumentType::BeginningOfSgfData, SgfcMessageID::UnknownPropertyDeleted)
    };

    return testData;
  }

  std::vector<std::tuple<std::string, std::vector<SgfcDate>, bool>> TestDataGenerator::GetValidPropertyValuesDT()
  {
    // Element 0 = The SgfcPropertyValue::DT property value
    // Element 1 = The collection with the decomposed SgfcDate objects
    // Element 2 = Indicator whether elements 1 and 0 can be reused as
    //             input/output for testing the inverse function that composes
    //             an SgfcPropertyValue::DT property value.
    std::vector<std::tuple<std::string, std::vector<SgfcDate>, bool>> testData =
    {
      // Full date
      std::make_tuple("2020-12-31", std::vector<SgfcDate> { {2020, 12, 31} }, true),
      // Partial dates
      std::make_tuple("2020-12", std::vector<SgfcDate> { {2020, 12, 0} }, true),
      std::make_tuple("2020", std::vector<SgfcDate> { {2020, 0, 0} }, true),
      // It's legal to NOT use shortcuts, even if they are possible
      std::make_tuple("2020-12-30,2020-12-31", std::vector<SgfcDate> { {2020, 12, 30}, {2020, 12, 31} }, false),

      // MM-DD shortcut after full date is ok
      std::make_tuple("2020-01-01,04-15", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 4, 15} }, true),
      // Single double-digit shortcut after full date means DD
      std::make_tuple("2020-01-01,04", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 1, 4} }, true),

      // MM-DD shortcut after YYYY-MM partial date is ok
      std::make_tuple("2020-01,04-15", std::vector<SgfcDate> { {2020, 1, 0}, {2020, 4, 15} }, true),
      // Single double-digit shortcut after YYYY-MM partial date means MM
      std::make_tuple("2020-01,04", std::vector<SgfcDate> { {2020, 1, 0}, {2020, 4, 0} }, true),

      // MM-DD shortcut after MM-DD shortcut is ok
      std::make_tuple("2020-01-01,04-15,10-22", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 4, 15}, {2020, 10, 22} }, true),
      // Single double-digit shortcut after MM-DD shortcut means DD
      std::make_tuple("2020-01-01,04-15,22", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 4, 15}, {2020, 4, 22} }, true),

      // MM-DD shortcut after MM shortcut is ok
      std::make_tuple("2020-01,04,10-22", std::vector<SgfcDate> { {2020, 1, 0}, {2020, 4, 0}, {2020, 10, 22} }, true),
      // Single double-digit shortcut after MM shortcut means MM
      std::make_tuple("2020-01,04,10", std::vector<SgfcDate> { {2020, 1, 0}, {2020, 4, 0}, {2020, 10, 0} }, true),

      // MM-DD shortcut after DD shortcut is ok
      std::make_tuple("2020-01-01,04,10-22", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 1, 4}, {2020, 10, 22} }, true),
      // Single double-digit shortcut after DD shortcut means DD
      std::make_tuple("2020-01-01,04,10", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 1, 4}, {2020, 1, 10} }, true),

      // Repeating full dates
      std::make_tuple("2020-01-01,2020-04-15", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 4, 15} }, false),
      // Repeating partial dates
      std::make_tuple("2020-01,2020-04", std::vector<SgfcDate> { {2020, 1, 0}, {2020, 4, 0} }, false),
      std::make_tuple("2020,2021", std::vector<SgfcDate> { {2020, 0, 0}, {2021, 0, 0} }, true),

      // Repeating MM-DD shortcuts
      std::make_tuple("2020-01-01,04-15,10-22", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 4, 15}, {2020, 10, 22} }, true),
      // Repeating MM shortcuts
      std::make_tuple("2020-01,04,10", std::vector<SgfcDate> { {2020, 1, 0}, {2020, 4, 0}, {2020, 10, 0} }, true),
      // Repeating DD shortcuts
      std::make_tuple("2020-01-01,02,22", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 1, 2}, {2020, 1, 22} }, true),

      // Go back to YYYY-MM-DD after YYYY-MM
      std::make_tuple("2020-04,2020-10-22", std::vector<SgfcDate> { {2020, 4, 0}, {2020, 10, 22} }, false),
      // Go back to YYYY-MM-DD after YYYY
      std::make_tuple("2020,2020-10-22", std::vector<SgfcDate> { {2020, 0, 0}, {2020, 10, 22} }, true),
      // Go back to YYYY-MM after YYYY
      std::make_tuple("2020,2020-10", std::vector<SgfcDate> { {2020, 0, 0}, {2020, 10, 0} }, true),

      // Go back to YYYY-MM-DD after MM-DD
      std::make_tuple("2020-01-01,04-15,2021-10-22", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 4, 15}, {2021, 10, 22} }, true),
      // Go back to YYYY-MM after MM-DD
      std::make_tuple("2020-01-01,04-15,2021-10", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 4, 15}, {2021, 10, 0} }, true),
      // Go back to YYYY after MM-DD
      std::make_tuple("2020-01-01,04-15,2021", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 4, 15}, {2021, 0, 0} }, true),

      // Go back to YYYY-MM-DD after MM
      std::make_tuple("2020-01,04,2021-10-22", std::vector<SgfcDate> { {2020, 1, 0}, {2020, 4, 0}, {2021, 10, 22} }, true),
      // Go back to YYYY-MM after MM
      std::make_tuple("2020-01,04,2021-10", std::vector<SgfcDate> { {2020, 1, 0}, {2020, 4, 0}, {2021, 10, 0} }, true),
      // Go back to YYYY after MM
      std::make_tuple("2020-01,04,2021", std::vector<SgfcDate> { {2020, 1, 0}, {2020, 4, 0}, {2021, 0, 0} }, true),
      // Go back to MM-DD after MM
      std::make_tuple("2020-01,04,10-22", std::vector<SgfcDate> { {2020, 1, 0}, {2020, 4, 0}, {2020, 10, 22} }, true),

      // Go back to YYYY-MM-DD after DD
      std::make_tuple("2020-01-01,04-15,22,2021-10-22", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 4, 15}, {2020, 4, 22}, {2021, 10, 22} }, true),
      // Go back to YYYY-MM after DD
      std::make_tuple("2020-01-01,04-15,22,2021-10", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 4, 15}, {2020, 4, 22}, {2021, 10, 0} }, true),
      // Go back to YYYY after DD
      std::make_tuple("2020-01-01,04-15,22,2021", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 4, 15}, {2020, 4, 22}, {2021, 0, 0} }, true),
      // Go back to MM-DD after DD
      std::make_tuple("2020-01-01,04-15,22,10-22", std::vector<SgfcDate> { {2020, 1, 1}, {2020, 4, 15}, {2020, 4, 22}, {2020, 10, 22} }, true),

      // Month days
      std::make_tuple("2019-01-31", std::vector<SgfcDate> { {2019, 1, 31} }, true),
      std::make_tuple("2019-02-28", std::vector<SgfcDate> { {2019, 2, 28} }, true),
      std::make_tuple("2019-03-31", std::vector<SgfcDate> { {2019, 3, 31} }, true),
      std::make_tuple("2019-04-30", std::vector<SgfcDate> { {2019, 4, 30} }, true),
      std::make_tuple("2019-05-31", std::vector<SgfcDate> { {2019, 5, 31} }, true),
      std::make_tuple("2019-06-30", std::vector<SgfcDate> { {2019, 6, 30} }, true),
      std::make_tuple("2019-07-31", std::vector<SgfcDate> { {2019, 7, 31} }, true),
      std::make_tuple("2019-08-31", std::vector<SgfcDate> { {2019, 8, 31} }, true),
      std::make_tuple("2019-09-30", std::vector<SgfcDate> { {2019, 9, 30} }, true),
      std::make_tuple("2019-10-31", std::vector<SgfcDate> { {2019, 10, 31} }, true),
      std::make_tuple("2019-11-30", std::vector<SgfcDate> { {2019, 11, 30} }, true),
      std::make_tuple("2019-12-31", std::vector<SgfcDate> { {2019, 12, 31} }, true),

      // Leap days
      std::make_tuple("2020-02-29", std::vector<SgfcDate> { {2020, 2, 29} }, true),
      std::make_tuple("1600-02-29", std::vector<SgfcDate> { {1600, 2, 29} }, true),
    };

    return testData;
  }

  std::vector<std::string> TestDataGenerator::GetInvalidPropertyValuesDT()
  {
    std::vector<std::string> testData =
    {
      // Illegal format
      "",
      ",",
      "foo",
      "2020/12/31",
      "2020.12.31",
      "31-12-2020",
      // Leading zeros are not allowed
      "02020/12/31",
      "2020/012/31",
      "2020/12/031",
      // Correct format but non-numeric parts
      "yyyy-mm-dd",
      "2020-12-dd",
      "2020-mm-31",
      "yyyy-12-31",
      // Leading/trailing whitespace
      " 2020-12-31",
      "2020-12-31 ",
      // Wrong list format
      ",2020-12-31",
      "2020-12-31,",
      // Illegal shortcuts
      "2020, 12-31",
      "2020, 12",
      // Shortcuts without a preceding date
      "12-31",
      "12",
      // Invalid month
      "2020-13-01",
      // Invalid month days
      "2019-01-32",
      "2019-02-29",
      "2019-03-32",
      "2019-04-31",
      "2019-05-32",
      "2019-06-31",
      "2019-07-32",
      "2019-08-32",
      "2019-09-31",
      "2019-10-32",
      "2019-11-31",
      "2019-12-32",
      // Invalid leap day
      "2100-02-29",
      // Missing month or missing all date parts
      "2020-00-01",
      "0000-00-00",
      // Missing year in the first date
      "0000-01-01",
      "0000-01-00",
      "0000-00-01",
    };

    return testData;
  }

  std::vector<std::tuple<std::vector<SgfcDate>, std::string>> TestDataGenerator::GetValidSgfcDates()
  {
    std::vector<std::tuple<std::vector<SgfcDate>, std::string>> testData
    {
      // Full date
      std::make_tuple(std::vector<SgfcDate> { {2020, 12, 31} }, "2020-12-31"),
      // Partial dates
      std::make_tuple(std::vector<SgfcDate> { {2020, 12, 00} }, "2020-12"),
      std::make_tuple(std::vector<SgfcDate> { {2020, 00, 00} }, "2020"),

      // Let the algorithm generate shortcuts. Add only a few simple cases here,
      // the bulk of the shortcut-generation tests is made when the test data
      // from GetValidPropertyValuesDT() is added below.
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {2020, 1, 2}, {2020, 1, 3} }, "2020-01-01,02,03"),
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 0}, {2020, 4, 0}, {2020, 10, 0} }, "2020-01,04,10"),

      // MM-DD shortcut after full date is ok
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 4, 15} }, "2020-01-01,04-15"),
      // Single double-digit shortcut after full date means DD
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 0, 4} }, "2020-01-01,04"),

      // MM-DD shortcut after YYYY-MM partial date is ok
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 0}, {0, 4, 15} }, "2020-01,04-15"),
      // Single double-digit shortcut after YYYY-MM partial date means MM
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 0}, {0, 4, 0} }, "2020-01,04"),

      // MM-DD shortcut after MM-DD shortcut is ok
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 4, 15}, {0, 10, 22} }, "2020-01-01,04-15,10-22"),
      // Single double-digit shortcut after MM-DD shortcut means DD
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 4, 15}, {0, 0, 22} }, "2020-01-01,04-15,22"),

      // MM-DD shortcut after MM shortcut is ok
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 0}, {0, 4, 0}, {0, 10, 22} }, "2020-01,04,10-22"),
      // Single double-digit shortcut after MM shortcut means MM
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 0}, {0, 4, 0}, {0, 10, 0} }, "2020-01,04,10"),

      // MM-DD shortcut after DD shortcut is ok
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 0, 4}, {0, 10, 22} }, "2020-01-01,04,10-22"),
      // Single double-digit shortcut after DD shortcut means DD
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 0, 4}, {0, 0, 10} }, "2020-01-01,04,10"),

      // Repeating MM-DD shortcuts
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 4, 15}, {0, 10, 22} }, "2020-01-01,04-15,10-22"),
      // Repeating MM shortcuts
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 0}, {0, 4, 0}, {0, 10, 0} }, "2020-01,04,10"),
      // Repeating DD shortcuts
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 0, 2}, {0, 0, 22} }, "2020-01-01,02,22"),

      // Go back to YYYY-MM-DD after YYYY-MM
      std::make_tuple(std::vector<SgfcDate> { {2020, 4, 0}, {2020, 10, 22} }, "2020-04,10-22"),
      // Go back to YYYY-MM-DD after YYYY
      std::make_tuple(std::vector<SgfcDate> { {2020, 0, 0}, {2020, 10, 22} }, "2020,2020-10-22"),
      // Go back to YYYY-MM after YYYY
      std::make_tuple(std::vector<SgfcDate> { {2020, 0, 0}, {2020, 10, 0} }, "2020,2020-10"),

      // Go back to YYYY-MM-DD after MM-DD
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 4, 15}, {2021, 10, 22} }, "2020-01-01,04-15,2021-10-22"),
      // Go back to YYYY-MM after MM-DD
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 4, 15}, {2021, 10, 0} }, "2020-01-01,04-15,2021-10"),
      // Go back to YYYY after MM-DD
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 4, 15}, {2021, 0, 0} }, "2020-01-01,04-15,2021"),

      // Go back to YYYY-MM-DD after MM
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 0}, {0, 4, 0}, {2021, 10, 22} }, "2020-01,04,2021-10-22"),
      // Go back to YYYY-MM after MM
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 0}, {0, 4, 0}, {2021, 10, 0} }, "2020-01,04,2021-10"),
      // Go back to YYYY after MM
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 0}, {0, 4, 0}, {2021, 0, 0} }, "2020-01,04,2021"),
      // Go back to MM-DD after MM
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 0}, {0, 4, 0}, {0, 10, 22} }, "2020-01,04,10-22"),

      // Go back to YYYY-MM-DD after DD
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 4, 15}, {0, 0, 22}, {2021, 10, 22} }, "2020-01-01,04-15,22,2021-10-22"),
      // Go back to YYYY-MM after DD
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 4, 15}, {0, 0, 22}, {2021, 10, 0} }, "2020-01-01,04-15,22,2021-10"),
      // Go back to YYYY after DD
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 4, 15}, {0, 0, 22}, {2021, 0, 0} }, "2020-01-01,04-15,22,2021"),
      // Go back to MM-DD after DD
      std::make_tuple(std::vector<SgfcDate> { {2020, 1, 1}, {0, 4, 15}, {0, 0, 22}, {0, 10, 22} }, "2020-01-01,04-15,22,10-22"),
    };

    // Test whether decomposed SgfcDate values can be composed again.
    // Also test single dates with specific date parts, such as month days and
    // leap days.
    for (auto testDataValidPropertyValuesDT : GetValidPropertyValuesDT())
    {
      if (std::get<2>(testDataValidPropertyValuesDT))
        testData.push_back(std::make_tuple(std::get<1>(testDataValidPropertyValuesDT), std::get<0>(testDataValidPropertyValuesDT)));
    }

    return testData;
  }

  std::vector<std::vector<SgfcDate>> TestDataGenerator::GetInvalidSgfcDates()
  {
    std::vector<std::vector<SgfcDate>> testData =
    {
      // Invalid month
      { {2020, 13, 1} },
      // Invalid month days
      { {2019, 1, 32} },
      { {2019, 2, 29} },
      { {2019, 3, 32} },
      { {2019, 4, 31} },
      { {2019, 5, 32} },
      { {2019, 6, 31} },
      { {2019, 7, 32} },
      { {2019, 8, 32} },
      { {2019, 9, 31} },
      { {2019, 10, 32} },
      { {2019, 11, 31} },
      { {2019, 11, 32} },
      // Invalid leap day
      { {2100, 02, 29} },
      // Missing month or missing all date parts
      { {2020, 0, 1} },
      { {0, 0, 0} },
      // Missing year in the first date
      { {0, 1, 1} },
      { {0, 1, 0} },
      { {0, 0, 1} },
      // Collection contains some valid and some invalid dates
      { {2020, 1, 1}, {2020, 2, 1}, {2020, 0, 1} },
      // Two consecutive dates that are the same
      { {2020, 1, 1}, {2020, 1, 1} },
      { {2020, 1, 0}, {2020, 1, 0} },
      { {2020, 0, 0}, {2020, 0, 0} },
      // Invalid MM-DD shortcut
      { {2020, 0, 0}, {0, 10, 22} },
      // Invalid MM shortcut
      { {2020, 1, 1}, {0, 10, 0} },
      { {2020, 0, 0}, {0, 10, 0} },
      { {0, 1, 1}, {0, 10, 0} },
      { {0, 0, 1}, {0, 10, 0} },
      // Invalid DD shortcut
      { {2020, 1, 0}, {0, 0, 22} },
      { {2020, 0, 0}, {0, 0, 22} },
      { {0, 1, 0}, {0, 0, 22} },
    };

    return testData;
  }
}
