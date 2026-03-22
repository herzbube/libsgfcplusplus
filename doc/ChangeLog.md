# ChangeLog

## Version 3.0.0 (March 22 2026)

### Features

- The `SgfcNumber` type now has the underlying fixed width integer type `int64_t`, guaranteeing a 64-bit value range on all platforms (#50). In previous versions of the library, the underlying type was `long`, which was ambiguous and caused the value range of `SgfcNumber` to be platform-dependent. The change is known to affect the Windows platform, when using the MSVC compiler, which treats `long` as a 32-bit value type. Apple platforms (macOS, iOS etc.) should not be affected unless they are very old, because on these platforms `long` has been a 64-bit value type for a long time (pun not intended). On Linux the system architecture decides the size of `long`. **Important:** Behind the scenes, SGFC still uses `long` to process SGF property values with the SGF type `Number`, so in practice the value range of such property values is still platform-dependent. This can be considered a "known bug", and issue #52 exists to track its status.
- In a similar vein, several other data types in the public interface of the library have been changed to use fixed width integer types instead of ambiguous sized data types (#51).
  - `ISgfcMessage`: Line and column numbers now use `uint64_t` instead of `long`.
  - `ISgfcGoPoint`: x- and y-position now use `uint64_t` instead of `unsigned int`.
  - `SgfcNodeTraits` and `SgfcPropertyTraits`: These typedefs now use the underlying type `uint64_t` instead of `unsigned long long`.
- Library clients can now set a custom value for the SGF property AP (#45). To do so, a library client must use `SgfcArgumentType::DoNotAddSgfcApProperty` when writing SGF content, in addition to adding the AP property to the document tree. If the library client does not use the argument, then SGFC will write its own AP property with value "SGFC:<sgfc-version>". See [SgfcNotes.md](SgfcNotes.md#the-ap-property) for details.

### Bugfixes

- Fixed a bug in SGFC that, when saving SGF files with 5'000 characters or more, would write one or more random byte values into the file. (#46). When generating SGF content, SGFC uses an internal buffer that starts with a size of 5'000 bytes and then doubles in size whenever the buffer end is reached (5'000, 10'000, 20'000, 40'000, etc.). When the buffer was doubled, the bug caused the byte at position `buffer size - 1` to be skipped, thus introducing a random value at byte positions 4'999, 9'999, 19'999, 39'999, etc.
- Fixed bugs when converting SGF property values of type "Real" and "Number" to string (#47). Depending on the numeric value, it was possible that "Real" values would be converted using the scientific notation or with a maximum precision of 6 decimal digits, while "Number" values would be converted with thousands separators. After the fix, scientific notation and thousands separators will no longer be used, and "Real" values will have a precision of up to 16 decimal digits. See [SgfNotes.md](SgfNotes.md#precision-of-properties-with-sgf-type-real) for details.
- `SgfcGoPlayerRank::FromPropertyValue` no longer throws `std::logic_error` if the rank number exceeds the `SgfcNumber` value range (#49). The function instead returns an `SgfcGoPlayerRank` value whose `IsValid` property has value `false`.

### Regressions

- None

### Technical changes

- Updated SGFC from v2.0 to v2.2.
- Updated unit test library Catch2 from v3.5.0 to v3.12.0.
- Update library win-iconv to latest commit.
- Updated project from the C++17 language standard to C++20.
- Fix Doxygen documentation errors

### GitHub issue list

A list of all issues closed for this release is available [on GitHub](https://github.com/herzbube/libsgfcplusplus/milestone/6?closed=1)

## Version 2.0.1 (January 5 2024)

This release contains no changes to the libsgfc++ source code at all. The release is made only to fix the SGFC git submodule reference in branch `master`: The git submodule now correctly points to the `V2_0` tag in the SGFC repository.

Also in this release are fixes for a number of errors in the libsgfc++ Doxygen documentation.

## Version 2.0.0 (January 3 2024)

Note: The Git tag `2.0.0` in branch `master` points to the wrong commit in the SGFC git submodule.

### Features

- None

### Bugfixes

- Fixed numeric value of `SgfcMessageID::IllegalVariationStartCorrected` (#39). The enum value had the same numeric value as `SgfcMessageID::IllegalVariationStartIgnored`.
- Changed the value type for referencing line and column numbers in messages to `unsigned long`, to match the error reporting interface of SGFC (#40). The old type `int` was insufficient to hold all possible `unsigned long` values, also there was a signed/unsigned mismatch. The change affects the `ISgfcMessage` getters `GetLineNumber()` and `GetColumnNumber()`, as well as the constants `SgfcConstants::InvalidLineNumber` and `SgfcConstants::InvalidColumnNumber`. The constants also changed their value (previously -1, now 0).

### Regressions

- None

### Technical changes

- Replaced internal custom code to determine the path to a temporary folder with `std::filesystem::temp_directory_path()` (#18).
- Updated unit test library Catch2 from v2.13.4 to v3.5.0.
- Updated the [Cross-compiling for iOS](Build.md#cross-compiling-for-ios) documentation for modern CMake/Xcode versions.
- Updated the GitHub build pipelines.

### GitHub issue list

A list of all issues closed for this release is available [on GitHub](https://github.com/herzbube/libsgfcplusplus/milestone/4?closed=1)

## Version 1.0 (February 23 2021)

Initial 1.0 release that includes SGFC v2.0.

Note: The Git tag `1.0` in branch `master` points to the wrong commit in the SGFC git submodule.

## Version 0.2 (beta) (January 12 2021)

Release of version 0.2 (beta).

## Version 0.1 (alpha) (October 11 2020)

Release of version 0.1 (alpha).

## September 20 2020

Unit tests largely completed.

## May 23 2020

Unit tests (work in progress), CMake build system, Travis CI, cross-platform build.

## April 09 2020

SGFC patching complete.

## February 5 2020

Created project
