# SGFC notes

This document contains assorted notes about SGFC, how it operates, and the consequences this has for libsgfc++ and/or the library client.

These notes can be important to understand the implementation of libsgfc++.

## Escaping

On reading SimpleText/Text property values, SGFC removes escape characters that don't do anything (e.g. `\a`, or `\:` in a non-composed property value) but preserves escape characters that have a purpose: `\\`, `\]` and `\:`.

On writing SimpleText/Text property values, SGFC does not add escape characters because it expects that those escape characters that have a purpose are still there.

libsgfc++ removes escape characters from SimpleText/Text property values so that the library client does not have to deal with them.

Because SGFC does not add escape characters, libsgfc++ is responsible for adding escape characters back to SimpleText/Text property values to protect the special characters "\", "]" and ":".

Technical detail: libsgfc++ escapes the ":" character even if the property value is not composed, but SGFC then removes that useless escape character again during `SaveSGF()`.

For application-specific properties and Point/Move/Stone properties of game types != Go, libsgfc++ has no idea how the value type is structured. It therefore performs automatic escaping/unescaping only for the end-of-value character "]".

## Line breaks

SGFC detects any kind of line breaks when it reads/parses SGF content.

However, the kind of line break SGFC uses when writing SGF content is determined at compile time. By default SGFC uses a single LF character. This can be changed by redefining the pre-processor macro `EOLCHAR` to something else during compilation. The macro must resolve into a single character, such as a LF character (already the default) or a CR character (used on classic MacOS systems). If you undefine `EOLCHAR` then SGFC will write two characters, a LF followed by a CR, which is the standard on Windows/MS-DOS systems.

When reading SimpleText or Text property values, SGFC follows the SGF standard rules for soft and hard line breaks. 

- Text property values: SGFC preserves unescaped (= hard) line breaks. SGFC removes escaped (= soft) line breaks (including the escape character). libsgfc++ never gets to see escaped line breaks.
- SimpleText property values: SGFC converts unescaped line breaks into a single space character. SGFC removes escaped line breaks (including the escape character). libsgfc++ never gets to see escaped line breaks.

When writing SimpleText or Text property values, SGFC preserves unescaped line breaks and generates escaped line breaks as needed.

## Known bug when handling composed values with SimpleText

SGFC has a known bug when handling composed values where the second value is a SimpleText value. In such a scenario, SGFC has problems detecting unescaped and escaped line breaks. Note that if the SimpleText value is the first value of the composed value, then SGFC handles line breaks correctly.

Two properties are currently known to have a problem:

- Property "AP": SGFC detects neither unescaped nor escaped line breaks.
- Property "LB": SGFC detects escaped line breaks, but not unescaped line breaks.

## Known bugs when handling composed SZ values

SGFC has two known bugs when handling composed SZ values:

1. If GM = 1 and SZ = 3:4 then SGFC does not fix the problem. The output still contains SZ[3:4]. Expected: SGFC assumes board size 19, as it does in all other cases where the SZ property is missing or has a missing or invalid value.
1. If GM != 1 and SZ = 3:foo then SGFC does not recognize the non-numeric second value and does not fix the problem. The output still contains SZ[3:foo]. Expected: SGFC removes the property, as it does when a non-numeric single value is specified, or the first value of the composed value is non-numeric.

libsgfc++ does not handle these errors, it discards the entire SGF content.

## Pass moves for Go games

For Go [the SGF standard defines](https://www.red-bean.com/sgf/go.html#types) that black or white pass moves can have either value "" (an empty string) or "tt". The latter counts as pass move only for board sizes <= 19, for larger boards "tt" is a normal move. The SGF standard also mentions that "tt" is kept only for compatibility with FF3.

The observed behaviour is that SGFC can deal with "tt" both on reading and writing, and it always performs the conversion to an empty string in an attempt to produce FF4 content. Consequently:

- When `ISgfcDocumentReader` reads SGF content with "tt" property values, the resulting `ISgfcDocument` will contain pass moves with empty string property values.
- When an `ISgfcDocument` is programmatically set up with black or white move properties that have value "tt", and the document is then passed to `ISgfcDocumentWriter` for writing, the resulting SGF content will contain pass moves with empty string property values.

## Compressed point lists

SGFC automatically expands compressed point lists during parsing when the game type is Go (GM[1]). See `Check_Pos()`. It compresses them again during saving unless the `-e` option is specified. See `WriteNode()`.

It's impossible to preserve the original format in all cases, because SGFC normalizes the input during parsing, but it does not record any traces of what it did.

## Why document writing works like it does today

The original idea was that the `SgfcDocumentEncoder` class creates data structures using the structs that SGFC defines (e.g. `Node`, `Property`, `PropValue`). In theory it should have been as easy as invoking the appropriate SGFC helper functions, such as `NewNode()` or `NewProperty()`, to create the data structures. In practice this scheme turned out at first to be problematic, and then doomed.

The first minor problem is accessibility of the involved functions: `NewNode()` is declared `extern`, so it can be used by `SgfcDocumentEncoder` easily. `NewProperty()` and other functions, on the other hand, are declared `static` inside `load.c`, so it would have been necessary to further patch SGFC in order to be able to use those functions.

The next problem, which turned out to be the real bummer, is that each `Property` structure has a member named `buffer`, which is a pointer that SGFC expects to point deeply into the `SGFInfo` file buffer. Although `NewProperty()` sets `buffer` up for us, it expects the buffer start as a parameter, i.e. the start within the file buffer from where property parsing should begin. We can't provide `NewProperty()` with a pointer into an `std::string` buffer because that goes away when the `std::string` object is destroyed. This means we would have to create a copy of the `std::string` buffer on the heap. But then the next problem would be, who frees that memory when the SGFC operation is done? `FreeSGFInfo()` is not the one, because it assumes that the `Property` buffer is part of the file buffer, so it merely frees the file buffer. In addition to the memory management issue, there are doubts whether SGFC's parsing functions can handle an abrupt end of the file buffer - which would occur because our copy of the `std::string` buffer would naturally be bounded with a zero byte.

In the end the best (because simplest and safest) idea seemed to be to just let `SgfcDocumentEncoder` generate an SGF content stream that simulates an entire file buffer.

