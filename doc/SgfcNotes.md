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

The first minor problem is accessibility of the involved functions: `NewNode()` is declared `extern`, so it can be used by `SgfcDocumentEncoder` easily. `NewProperty()` and other functions, on the other hand, are declared `static` inside `load.c`, so it would have been necessary to patch SGFC in order to be able to use those functions.

The next problem, which turned out to be the real bummer, is that each `Property` structure has a member named `buffer`, which is a pointer that SGFC expects to point deeply into the `SGFInfo` file buffer. Although `NewProperty()` sets `buffer` up for us, it expects the buffer start as a parameter, i.e. the start within the file buffer from where property parsing should begin. We can't provide `NewProperty()` with a pointer into an `std::string` buffer because that goes away when the `std::string` object is destroyed. This means we would have to create a copy of the `std::string` buffer on the heap. But then the next problem would be, who frees that memory when the SGFC operation is done? `FreeSGFInfo()` is not the one, because it assumes that the `Property` buffer is part of the file buffer, so it merely frees the file buffer. In addition to the memory management issue, there are doubts whether SGFC's parsing functions can handle an abrupt end of the file buffer - which would occur because our copy of the `std::string` buffer would naturally be bounded with a zero byte.

In the end the best (because simplest and safest) idea seemed to be to just let `SgfcDocumentEncoder` generate an SGF content stream that simulates an entire file buffer.

## SGFC code reuse in a software library

This section can be seen as a very high-level approach to an inofficial SGFC API (there is no official API). You may find this interesting if you're new to SGFC and want to learn how you can reuse its code in a software project of your own.

### The `main()` function

At the highest level the SGFC codebase can be divided into two parts:

- The `main()` function
- Everything else

A software library must not contain a `main()` function, so the first thing that needs to be done to enable reusing the "everything else" part is to remove the `main()` function part. This can be achieved in one of two ways:

- Don't include the file `main.c` in the build
- Include the file `main.c` in the build but define the preprocessor macro `VERSION_NO_MAIN` when `main.c` is compiled.

libsgfc++ uses the second approach because it allows `main.c` to be included in IDE projects that are generated by CMake.

### Global functions

The SGFC codebase offers a number of high-level global functions that are of interest to a library. The functions can be placed into four broad categories:

- Managing data structures
  - The function `SetupSGFInfo()` creates an `SGFInfo` data structure and initializes it with useful default values. An `SGFInfo` data structure must be passed as a parameter to all global functions that perform some sort of data processing. The `SGFInfo` data structure can be parameterized in a number of ways, but this is beyond the scope of this document.
  - The function `FreeSGFInfo()` frees all memory that is currently occupied by an `SGFInfo` structure.
- Working with arguments.
  - The function `ParseArgs()` processes command line arguments in the usual `argc` / `argv` format known from the `main()` function and stores the result in an `SGFCOptions` data structure.
- Loading SGF data.
  - The function `LoadSGF()` loads the SGF data from the filesystem into intermediate in-memory data structures.
  - The function `LoadSGFFromFileBuffer()` loads the SGF data from an in-memory buffer into intermediate in-memory data structures.
  - The function `ParseSGF()` processes the intermediate data structures generated by either one of the two load functions and generates the final data structures. These are what a software library such as libsgfc++ wants to work with.
- Saving SGF data.
  - The function `SaveSGF()` processes the final data structures generated by `ParseSGF()` into SGF data and saves that data, either to the filesystem or to an in-memory buffer.

### Hooks/callbacks

SGFC offers a software library to tap into parts of its data processing by way of hooks/callbacks that can be installed/provided in strategic places.

- Diagnostic output. These are the messages that are printed by SGFC to standard output when it is run as command line tool. Messages are generated as a **transient by-product** of the processing done by most of the global functions mentioned in the previous section. In other words, the message data is **not** available to the caller in the data structures generated/returned by the global functions! To get hold of the message data a software library can install a hook/callback function by setting the global variable `print_error_output_hook`. The hook/callback function will then receive the message data in structured form for further processing. See the `SgfcMessageStream` class for an example how libsgfc++ implements the hook/callback.
- Redirecting SGF data on save. The default for `SaveSGF()` is to write the SGF data to the filesystem. A library can redirect the output to be written to somewhere else so that the library can perform further processing. SGFC provides three hook/callback opportunities to tap into the save procedure: `open` and `close` for when an SGF file would normally be opened/created and closed, and `putc` for when character data is actually output to the save stream. See the `SgfcSaveStream` class for an example how libsgfc++ implements redirection to an in-memory buffer.
- Preventing a call to `exit()`. SGFC has an internal central memory-allocation function (actually a preprocessor macro). When that function fails to allocate memory it invokes a "panic" function to report the out-of-memory problem. When SGFC is run as command line tool the default "panic" function prints a message to standard output and then invokes `exit()`.   A software library can install its own versin of a "panic" function by setting the global variable `oom_panic_hook`. See the `SgfcBackendController` class for an example how libsgfc++ attempts to handle memory allocation failures.
