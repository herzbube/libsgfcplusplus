# SGF notes

This document contains assorted notes about how libsgfc++ presents certain aspects of the SGF standard to the library client.

## Object model

EBNF terms and their corresponding libsgfc++ types:

- Structural
  - Collection → `ISgfcDocument`
  - GameTree → `ISgfcGame`, but `ISgfcGame` objects cannot be nested. Instead an `ISgfcGame` has a full tree of nodes starting with a root node.
  - Sequence → No corresponding libsgfc++ type
  - Node → `ISgfcNode`
  - Property → `ISgfcProperty`
  - PropIdent → The "PropertyName" property of `ISgfcProperty`
- Property values, basic
  - PropValue → `ISgfcPropertyValue`
  - ValueType → `ISgfcSinglePropertyValue`
  - Compose → `ISgfcComposedPropertyValue`
- Property values, concrete types
  - Number → `ISgfcNumberPropertyValue`
  - Real → `ISgfcRealPropertyValue`
  - Double → `ISgfcDoublePropertyValue`
  - Color → `ISgfcColorPropertyValue`
  - SimpleText → `ISgfcSimpleTextPropertyValue`
  - Text → `ISgfcTextPropertyValue`
  - Point → `ISgfcPointPropertyValue`
  - Move → `ISgfcMovePropertyValue`
  - Stone → `ISgfcStonePropertyValue`
  - None → See section [Properties with no value](#properties-with-no-value)

## SGF format

The following has already been stated in the main README and elsewhere, but to reiterate:

- SGF data read by libsgfc++ can be in any of the FF1 - FF4 formats.
- SGF data written by libsgfc++ is always in the FF4 format.
- When `ISgfcDocumentReader` reads SGF data, the object tree under the resulting `ISgfcDocument` is already in FF4 format.

## Properties with no value

The EBNF in the SGF standard says that a property must have at least one value. This can be a value that has the value type "None", which the SGF standard defines to be an empty string. The meaning for SGF content in its raw string form is clear: Something like `XY[]` is possible.

In the libsgfc++ object model, however, a "None" value is not an empty string. Instead it is translated to an empty collection of property values. In other words, if a property has no values the method `ISgfcProperty::GetPropertyValues()` returns a collection with zero elements.

## Property value validation

libsgfc++ makes no attempt to check the validity of property values assigned to a property with, for instance, `ISgfcProperty::SetPropertyValues()`.

A last-ditch attempt at validation is made only when the SGF data is written to a destination, but this is unlikely to catch all mistakes. In any case, it might pay to examine the exit code and messages that are returned as the result of a write operation.

It is ultimately the responsibility of the library client to take care that the values are valid. The consequence of faulty values is that the library client might be unable to read in the game tree again after it has been written out.

## Escaping

#### Summary

Wherever possible libsgfc++ performs escaping and unescaping on behalf of the library client, so that the library client can work naturally with unescaped values at all times.

libsgfc++ does escaping and unescaping for properties of type Text, SimpleText, Move, Point and Stone, but not for properties of the primitive types Number, Real, Color and Double.

**Note:** If the library client performs its own escaping where it is not necessary, the resulting SGF content will be "double-escaped".

#### SimpleText and Text property values

Library clients never need to deal with escaping and unescaping in SimpleText and Text property values.

When the library client programmatically creates an `ISgfcSimpleTextPropertyValue` or an `ISgfcTextPropertyValue` object it can simply provide the natural string value without escape characters. Later libsgfc++ will add the necessary escape characters at the time it generates the SGF content.

When it reads in SGF content libsgfc++ removes all escape characters from SimpleText and Text property values so that the library client is presented with property values that do not contain any escape characters.

**Note:** When it reads in SGF content libsgfc++ preserves escape characters in the raw property value (`ISgfcSinglePropertyValue::GetRawValue()`). When the library client programmatically creates a property value object libsgfc++ does not add escape characters to the raw value.

#### Move/Point/Stone property values

Move/Point/Stone property values for Go (GM[1]) are simple two-letter strings that do not need escaping.

Move/Point/Stone property values for other game types are different: Because libsgfc++ does not know the format of these values (libsgfc++ only has game-specific knowlege about Go) it cannot make any assumptions regarding escaping except for the most basic rules that are required for the integrity of the SGF format. The library client therefore does not have to deal with the following:

- Escaping/unescaping a closing bracket character ("]").
- Escaping/unescaping a colon character (":") when the value is the first value of a composed value.

All other cases of escaping/unescaping are the responsibility of the library client.

#### Test cases

Run the test file `escaping.sgf` through the example program to see what your library client will get from libsgfc++ in various scenarios.

    ./build/example/libsgfcplusplus-example docread test/test-files/escaping.sgf

## Line breaks

TODO

## Go support

#### Go-specific C++ types

The SGF standard does not specify how to interpret Move, Point and Stone property values. However, the library treats Go as a first class citizen, in a similar way that SGFC does, and provides the following Go-specific C++ types:

- `ISgfcGoPoint` and `ISgfcGoPointPropertyValue`
- `ISgfcGoStone` and `ISgfcGoStonePropertyValue`
- `ISgfcGoMove` and `ISgfcGoMovePropertyValue`

In order for this support to be possible, the library needs to analyze the game type and board size properties (GM and SZ). For this purpose the library makes the following special property C++ types available:

- `ISgfcGameTypeProperty`
- `ISgfcBoardSizeProperty`

#### Pass moves for Go games

For Go [the SGF standard defines](https://www.red-bean.com/sgf/go.html#types) that black or white pass moves can have either value "" (an empty string) or "tt". The latter counts as pass move only for board sizes <= 19, for larger boards "tt" is a normal move. The SGF standard also mentions that "tt" is kept only for compatibility with FF3.

libsgfc++ always exposes pass moves as an empty string to the library client. This is unambigous and conforms to FF4. This means that when `ISgfcDocumentReader` reads SGF content with "tt" property values, the resulting `ISgfcDocument` will contain pass moves with empty string property values.

When the library client programmatically sets up an `ISgfcDocument` with pass moves that have value "tt", and the document is then passed to `ISgfcDocumentWriter` for writing, the resulting SGF content will contain pass moves with empty string property values.

#### Compressed point lists

libsgfc++ automatically expands compressed point lists when it reads SGF content and the game type is Go (GM[1]). So when `ISgfcDocumentReader` reads SGF content the resulting object tree will contain one `ISgfcPointPropertyValue` object for each individual point on the Go board, whereas the original SGF content might have contained only a single property value.

When it writes SGF content and the game type is Go (GM[1]) libsgfc++ behaves in one of the following ways:

- By default libsgfc++ automatically compresses expanded point lists, and leaves already compressed point lists alone so they remain compressed.
- When the library client specifies the argument `SgfcArgumentType::ExpandCompressedPointLists`, libsgfc++ automatially expands compressed point lists, and leaves already expanded point lists alone so they remain expanded.

When libsgfc++ expands a compressed point list it normalizes the resulting expanded point list. When libsgfc++ compresses an expanded point list it does so in the most efficient way. This means that in roundtrip processing, when SGF content is first read and then written, it is impossible to preserve the original format in all cases.

#### The "KI" and "KM" properties

According to the SGFC readme document the "KI" property is a private property of the "Smart Game Board" application (SGB). The property name means "integer komi".

libsgfc++ converts "KI" to the Go-specific "KM" property, dividing the original "KI" numeric value by 2 to obtain the new "KM" value. libsgfc++ performs this conversion in all cases, even if the game tree's game type is not Go.

When libsgfc++ reads SGF content it treats the "KM" property as having a Real value when the game tree's game type is Go. For all other game types it treats the "KM" property being a custom property with an unknown property value type.

## Inheritable properties

TODO

## Text encoding

TODO
