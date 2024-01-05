# ChangeLog

## Version 2.0.1 (January 5 2024)

This release contains no changes to the libsgfc++ source code at all. The release is made only to fix the SGFC git submodule reference in branch `master`: The git submodule now correctly points to the `V2_0` tag in the SGFC repository.

Also in this release are fixes for a number of errors in the libsgfc++ Doxygen documentation.

## Version 2.0.0 (January 3 2024)

Note: The Git tag `2.0.0` in branch `master` points to the wrong commit in the SGFC git submodule.

### Features

- None

### Bugfixes

- Fixed numeric value of `SgfcMessageID::IllegalVariationStartCorrected` (#39). The enum value had the same numeric value as `SgfcMessageID::IllegalVariationStartIgnored`.
- Changed the value type for referencing line and column numbers in messages to `unsigned long`, to match the error reporting interface of SGFC (#40). The old type `int` was insufficient to hold all possible `unsigned long` values, also the there was a signed/unsigned mismatch. The change affects the `ISgfcMessage` getters `GetLineNumber()` and `GetColumnNumber()`, as well as the constants `SgfcConstants::InvalidLineNumber` and `SgfcConstants::InvalidColumnNumber`. The constants also changed their value (previously -1, now 0).

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
