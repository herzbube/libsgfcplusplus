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

## Character encoding

### Introduction

The SGF standard specifies the `CA` property which allows an SGF-writing application to specify the character encoding in which a game tree's SimpleText and Text property values are stored.

This approach is somewhat antiquated as it not only allows SGF content to be partially encoded (SimpleText and Text property values are encoded, but not the rest of the content), it even allows different character encodings to be used within the same piece of SGF content! From a modern-day point of view this seems strange, and it definitely breaks the notion of an SGF file being "just a regular text file".

An additional complication to the partial encoding approach are the SGF standard's escaping rules. See the section "Escaping and multi-byte character encodings" below for details.

All things considered it is reasonable to assume that modern-day SGF-writing applications that support non-ASCII SGF content are not strictly conforming to the SGF standard, but are using the common-sense approach of encoding the **entire** SGF content with the same character encoding.

### Encoding modes

The library client can choose between 3 encoding modes when it reads SGF content with `ISgfcDocumentReader` or writes SGF content with `ISgfcDocumentWriter`. The selection is made by specifying `SgfcArgumentType::EncodingMode` when the read or write operation is performed. 

The documentation of `SgfcArgumentType::EncodingMode` has the details about each of the 3 modes. The following is just an excerpt to provide an overview:

- Mode 1 (the default mode): A single encoding is used to decode the **entire** SGF content. The encoding to use is detected by probing the SGF content. If a Unicode BOM marker is found then the encoding defined by that marker is used, but the first CA property in the decoded SGF content must match the encoding detected from the BOM. If no Unicode BOM marker is found then the SGF content is probed for CA properties, and the first CA property value found is used as the encoding. If no CA property is found the default encoding ISO-8859-1 is used. Note that only this mode allows the wide-character encodings UTF-16 and UTF-32 to be processed (via BOM detection).
- Mode 2 (specification conformant): A separate encoding is used to decode each game tree in the SGF content. The encoding is defined by the CA property value of that game tree. If a game tree has no CA property the default encoding ISO-8859-1 is used. Only SimpleText and Text property values are decoded! The SGF formatting skeleton as well as property values that are not SimpleText or Text are parsed using ASCII/ISO-8859-1.
- Mode 3: No decoding takes place.

Please make sure to read the documentation of `SgfcArgumentType::EncodingMode` to understand the details. You may also wish to consult the documentation in SGFC's README file.

### ASCII-compatible vs. ASCII-safe

Term definitions:

- ASCII-compatible: A character encoding that is ASCII-compatible encodes ASCII characters with their single byte values from the ASCII table. Example: A closing bracket `]` character is encoded as a single byte that has the hex value 0x5d.
- ASCII-safe : A character encoding that is ASCII-safe is also ASCII-compatible, but in addition it guarantees that the byte values of ASCII characters are not used to encode anything else but ASCII characters. Example: The hex byte value 0x5d does not appear anywhere in the encoded byte stream except when it encodes a closing bracket `]` character.

Encoding examples:

```
            ASCII        ASCII
Encoding    compatible   safe    ]           \              因               申
-------------------------------------------------------------------------------------------
UTF-16      No           No      0x00 0x5d   0x00 0x5c      0x56 0xe0        0x75 0x33
Big5        Yes          No      0x5d        0x5c           0xa6 0x5d        0xa5 0xd3
Shift_JIS   Yes          No      0x5d        0x5c           0x88 0xf6        0x90 0x5c
UTF-8       Yes          Yes     0x5d        0x5c           0xe5 0x9b 0xa0   0xe7 0x94 0xb3
```

Discussion:

- UTF-16 is not ASCII-compatible, because it uses two bytes to represent all characters.
- In the Big5 encoding the 0x5d byte value is used to encode both the closing bracket and the 因 character.
- In the Shift_JIS encoding the 0x5c byte value, which in ASCII represents the backslash character, is used to encode the 申 character.
- UTF-8 is ASCII-safe because the 0x5d and 0x5c values are not used for anything else except to encode the closing bracket and the backslash characters. Note: The table above does not demonstrate this, it is stated as a fact with the knowledge of how UTF-8 works. If in doubt consult the "Layout of UTF-8 byte sequences" table on the [UTF-8 Wikipedia page](https://en.wikipedia.org/wiki/UTF-8#Encoding).

### Escaping and multi-byte character encodings 

As demonstrated in the previous section, the Big5-encoded character `因` contains the 0x5d byte value that is also the ASCII value of a closing bracket character `]`. Now let's look at this simple piece of SGF content:

    (;FF[4]CA[Big5]C[因])

Taking a hex dump of this SGF content reveals the individual byte values:

    28 3b 46 46 5b 34 5d 43   41 5b 42 69 67 35 5d 43   5b a6 5d 5d 29
    (  ;  F  F  [  4  ]  C    A  [  B  i  g  5  ]  C    [  因    ]  )
                                                              ^  ^

Note the two byte values 0x5d towards the end. A strictly standard-conforming SGF-writing application would be required to escape the first 0x5d to prevent it from being interpreted as the closing bracket of the `C` property value.

Another example, this time with the `申` character which, as demonstrated in the previous section, when encoded with Shift_JIS contains the 0x5c byte value that is also the ASCII value of the backslash character `\`. The SGF content

    (;FF[4]CA[SJIS]C[申])

looks like this in the hex dump:

    28 3b 46 46 5b 34 5d 43   41 5b 53 4a 49 53 5d 43   5b 90 5c 5d 29
    (  ;  F  F  [  4  ]  C    A  [  S  J  I  S  ]  C    [  申    ]  )
                                                              ^  ^

Note the byte values 0x5c towards the end. A strictly standard-conforming SGF-writing application would be required to escape this 0x5c value to prevent it from being interpreted as escaping the closing bracket of the `C` property value.

**Conclusion:** These two examples show how impractical it is to program a strictly standard-conforming SGF-writing application. Such an application would have to operate on two levels: First on a character level to perform the encoding of the human-readable text, then on the underlying byte-stream level to perform the escaping required by the SGF standard.

Furthermore, after the escape-processing the resulting SGF content might not even be valid text anymore, because inserting the escape characters might have invalidated the encoding. The Big5 encoding example above is such a case.

### UTF-8 is recommended for programmatically creating ISgfcDocument object trees

A library client that programmatically creates `ISgfcDocument` object trees should use UTF-8 to encode SimpleText and Text property values. UTF-8 is a universal and ASCII-safe character encoding that causes the least amount of trouble along all routes.

Specifically, `ISgfcDocumentWriter` supports only ASCII-safe character encodings to write an `ISgfcDocument` object tree. The escape-processing discussed in the previous section is the root cause for the restriction. Read the `ISgfcDocumentWriter` class documentation for some technical details.
