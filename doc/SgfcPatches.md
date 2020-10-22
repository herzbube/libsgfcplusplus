# SGFC Patches

libsgfc++ applies a number of patches to the original SGFC source code to make it more suitable in a software library context. SGFC is quite unusable as a library without these modifications, because many of its routines are designed for command line usage.

This document lists all patches, outlines **what** changes that are made in each patch and provides an explanation **why** the changes are made.

**Note:** The patches are incremental. The patch files have a numeric prefix that makes it easy to apply them in the correct order.

## How to apply the patches

The patches were created with `git diff`. To apply them use `git apply`. The following shell script snippet applies the patches in the correct order:

```
cd sgfc
for PATCH_FILE in ../patch/*; do
  git apply "$PATCH_FILE"
done
```

## 001-util.c-extern-c.patch

This patch adds the following `extern "C"` declaration to `util.c`:

```
extern "C"
{
#include "all.h"
#include "protos.h"
}
```

The reason for this is so that `util.c` can be be compiled as C++ code (e.g. `clang -x c++`), but the rest of the SGFC source code can remain being compiled as C code. As a reminder, an `extern "C"` declaration forces the function names it surrounds to have C linkage (i.e. the compiler does not mangle the names) although the code is compiled by a C++ compiler. Also cf. [this StackOverflow answer](https://stackoverflow.com/a/1041880/1054378).

Compiling `util.c` as C++ code is necessary first and foremost because the call to `exit()` needs to be replaced with a statement that throws an exception - and exceptions are a C++ feature. This replacement occurs in the next patch.

Allowing C++ constructs also makes life much easier for later patches.
## 002-util.c-throw.patch

This patch replaces the call to `exit()` in `util.c` within the function `PrintError()` with a statement that throws an exception. The new code looks like this:

```
if((type & M_ERROR_TYPE) == E_FATAL_ERROR)      /* fatal one? */
{
       throw std::runtime_error("PrintError() called with fatal error");
}
```

The reason for this change is that a software library must never invoke `exit()` to abort program execution - this is the prerogative of the program that makes use of the library.

Throwing a C++ exception is the best replacement for invoking `exit()` because it stops code execution and allows the exception to propagate up the call stack until it can be caught by the calling code in libsgfc++. 

Adding a return value to `PrintError()` to achieve the same effect is a doomed effort, because it not only requires a change to every `PrintError()` call site to handle the return value, but also to every function that somehow ends up indirectly calling `PrintError()`.

**Important:** Throwing a C++ exception from a C function (functions declared with `extern "C"`) is not something that just works naturally. Compilers on the different platforms usually have an option that tells them that C functions are allowed to throw C++ exceptions. This causes the compiler to generate code that allows catching those exceptions. For example the MSVC compiler option is `/EHs`. Details can be found in the project's main `CMakeLists.txt`.

## 003-util.c-messagestream.patch

This patch changes the `PrintError()` function so that it pours the output it generates into an `std::stringstream` instead of printing it to standard output. The patch also changes all other places in the SGFC source code that use `fprintf()` to write directly to standard output to instead call a new global function `WriteFormattedStringToLibSgfcPlusPlusMessageStream()`. As its name says, that function redirects the input it receives to the same `std::stringstream` that is also filled by `PrintError()`.

The patch then adds global functions that can be called from libsgfc++ to acquire the content of the stream after an SGFC operation, and to reset the stream to prepare SGFC for another operation.

In summary, the changes in this patch enable libsgfc++ to make the SGFC output available to the library client in a structured way so that the client can programmatically evaluate the output e.g. for error handling purposes. libsgfc++ parses the stream content after acquiring it and generates `ISgfcMessage` objects from the parsed content. libsgfc++ also examines the message types of the `ISgfcMessage` objects to emulate the exit code that SGFC would terminate with when invoked on the command line (cf. `SgfcExitCode` enumeration).

**Note:** A solution that sends individual messages back to libsgfc++ for parsing has been considered, but found to be more difficult to implement because then it would be necessary to decide when a message ends and the next one begins. This is non-trivial, because SGFC has been designed so that one call to `PrintError()` can generate only a partial message, i.e. a full message might need several `PrintError()` calls. Sometimes `PrintError()` even calls itself recursively.

## 004-main.c-parseargs.patchThis patch changes the `ParseArgs()` function so that it is no longer a static function local to `main.c`, but instead becomes a global function that is callable from libsgfc++. This includes adding the function prototype to `protos.h` to make it visible to libsgfc++.

The goal is that the library client can programmatically pass arguments to SGFC just as a user would do when invoking SGFC on the command line.

A small but important change that is also included in this patch is that `ParseArgs()` no longer treats a missing input file argument as a fatal error. This change is necessary so that libsgfc++ can invoke `SaveSGF()` without a prior call to `LoadSGF()`.

## 005-resetglobalvariables.patchThis patch adds a number of global functions, each of which is responsible for resetting a few global and `static` variables that are local to the file in which the reset function is located. For instance, `ResetGlobalVariablesInSave()` is responsible for resetting variables within `save.c`.

It is vital that libsgfc++ is capable of resetting SGFC's global state so that the library can invoke SGFC operations many times.
## 006-nomainfunction.patchThis patch removes SGFC's `main()` function. In a library context the definition of a `main()` function is reserved for the library client.

Actually the patch makes use of an SGFC feature that already envisions someone else providing a `main()` function: The patch simply defines the preprocessor macro `VERSION_NO_MAIN`. This causes the `main()` function in `main.c` to not be compiled.
## 007-removedestinationfilenamelengthlimit.patchThe original SGFC code has a limit how long destination file names (including file system path) can be. The maximum is 480 characters. The limit exists merely because a character buffer is hardcoded to a size of 500.

This patch removes that limit.

Because the patch also adds C++ features (try/catch) to the code in `save.c` that file now needs to be compiled as C++ code. To achieve that the patch adds the same `extern "C"` declaration to `save.c` that is added to `util.c` by `001-util.c-extern-c.patch`.

The patch adds a different limit instead: When option `-s` is used for splitting games, there is now a maximum number of games that can be split. The limit is a compile time constant. the default limit is 999999 games, but it can be changed by defining the preprocessor macro `MAXIMUM_NUMBER_OF_GAMES`. The value must fit into an `int` type.

Before the patch there was a theoretical limit of 999999999999999 (15 digits) games that could be split before the sprintf() string formatting would exceed the string buffer limit and cause a buffer overrun. In practice this limit was unreachable because the counter variable of type int would overflow to a negative number before reaching that number.

## 008-split-loadsgf.patchThe function `LoadSGF()` originally consists of two distinct parts:

1. Load a file's content into a character buffer and configure the `SGFInfo` structure with that buffer.
2. Process the character buffer in preparation for invoking `ParseSGF()`; this can be seen as stage 1 of the parsing process.

This patch splits off the second part into a new function `LoadSGFFromFileBuffer()` and makes that function available for calling to libsgfc++. This eliminates the constraint that SGFC can only process SGF data loaded from a file and instead allows libsgfc++ to inject arbitrary content into the SGFC parsing process.## 009-save.c-savestream.patchThis patch follows a similar concept as `003-util.c-messagestream.patch`: It modifies all functions that are invoked directly or indirectly from `SaveSGF()` to send their output to an `std::stringstream` instead of writing it to a `FILE` handle.

The patch also modifies `SaveSGF()` so that when the function has finished writing to a file it invokes a function `CaptureSaveStreamContent()` newly introduced by the patch, to capture a snapshot of the stream. This also associates the snapshot with the file name that SGFC would have used.

The patch finally adds global functions that can be called from libsgfc++ after it receives back control from `SaveSGF()` to get hold of the captured SGF content and the associated file names. libsgfc++ can then process the SGF content as requested by the library client.

The changes in this patch are important so that libsgfc++ does not have to go through the file system to acquire SGF content saved by SGFC

## 010-const-declarations.patch

This patch adds the `const` keyword to some function parameter declarations. The purpose of the change is to avoid a number of these compiler warnings:

> ISO C++11 does not allow conversion from string literal to 'char *'

Without the modification the warnings occur because `New_PropValue()` is invoked several times with a string literal argument. Once `New_PropValue()` has been changed to accept a `const char*` parameter, the change must be propagated to functions called directly or indirectly from `New_PropValue()`.