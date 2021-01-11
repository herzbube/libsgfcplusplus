[![Build Status](https://github.com/herzbube/libsgfcplusplus/workflows/build/badge.svg)](https://github.com/herzbube/libsgfcplusplus/actions?query=workflow%3Abuild)
[![Github Releases](https://img.shields.io/github/release/herzbube/libsgfcplusplus.svg)](https://github.com/herzbube/libsgfcplusplus/releases)
[![Github Releases](https://img.shields.io/github/license/herzbube/libsgfcplusplus.svg)](https://github.com/herzbube/libsgfcplusplus/blob/master/LICENSE)

## What is it?

libsgfc++ is a C++ wrapper library around [SGFC](https://www.red-bean.com/sgf/sgfc/). As such, libsgfc++ offers the same functionality as SGFC:

- Read and write SGF (Smart Game Format) files.
- Check the file content for correctness.
- Correct any errors.
- Convert FF[1] - FF[3] files to the FF[4] format.
- Convert files with a character encoding that is not UTF-8 to the UTF-8 character encoding.

libsgfc++ is not restricted to files, it also reads and writes SGF data from/to `std::string` without filesystem interaction.

SGFC is written in pure C. libsgfc++ adds an object-oriented API layer written in C++ on top of that.

libsgfc++ is cross-platform. It builds on the three major desktop operating systems (macOS, Linux, Windows) as well as on iOS. Other platforms may work as well but have not been tested.

## What it's not

The limitations of SGFC also apply to libsgfc++. Quoting from the [SGFC website](https://www.red-bean.com/sgf/sgfc/):

> SGFC is intended to be a tool for SGF experts, coders and maintainers of large SGF archives. You ought to have quite some knowledge of SGF to use SGFC efficiently.
> 
> SGFC was written primarily for Go/WeiQi/Baduk (GM[1]) files. It can't handle other games yet, i.e. it doesn't check any game-specific properties and values of other games than Go. It may even save erronous game-specific properties of other games! Use SGFC for other games with care. 

## Project status

libsgfc++ has reached something that could be tentatively called a "beta phase". It has taken its first baby steps in an iOS project (via an Objective-C wrapper library [SgfcKit](https://github.com/herzbube/SgfcKit)), where it will now have to prove both stability and ease of use over the coming weeks and months. Although the API should be fairly stable, if using the library turns out to be too cumbersome there can still be drastic changes.

Feel free to play around with libsgfc++, but at the moment, unless you are adventurous, I still advise against using it in earnest. Feedback how to improve the library or its build process is very welcome.

## Dependencies

At runtime libsgfc++ depends on the C/C++ runtime library, the C++ standard library and possibly (depending on the platform) an iconv library.

At build time libsgfc++ has the following dependencies:

1. The main dependency, of course, is [SGFC](https://www.red-bean.com/sgf/sgfc/). A transitive dependency inherited from SGFC is [iconv](https://en.wikipedia.org/wiki/Iconv) (more on that see below).
2. The second dependency is the unit test library [Catch2](https://github.com/catchorg/Catch2).
3. The third dependency is the build management tool [CMake](https://cmake.org/cmake/help/latest/).
4. A last dependency is [Doxygen](https://www.doxygen.org/), used to optionally generate the project's API documentation.

SGFC and Catch2 are integrated via Git submodule.

iconv is integrated differently depending on the platform:

* On Apple platforms (macOS, iOS, etc.) and the Windows-based platforms Cygwin and MinGW/MSYS, iconv is expected to be present as a separate library, both at build time and at runtime. This typically is GNU `libiconv`.
* On Win32 the [win-iconv project](https://github.com/win-iconv/win-iconv) provides the iconv implementation. win-iconv is integrated via Git submodule at build time. The win-iconv sources are statically linked into libsgfc++, so there is no dependency at runtime.
* On all other platforms iconv is expected to be present natively without a separate library. For instance on Linux the iconv implementation is provided by `glibc`.

## Project build system

The project build system is [documented here](doc/Build.md).

## More documentation

- [API documentation](https://herzbube.github.io/libsgfcplusplus/api-docs/index.html) (the public API is in the "Public API" module)
- [Why another library?](doc/WhyAnotherLibrary.md)
- [SGF notes](doc/SgfNotes.md): SGF features and how libsgfc++ exposes them to the library client.
- [Library design and working principles](doc/Principles.md)
- [Assorted SGFC notes](doc/SgfcNotes.md)
- [Other project notes](doc/ProjectNotes.md)
- [Coding guidelines](doc/CodingGuidelines.md)

## Acknowledgment

Thanks to Arno Hollosi, for writing SGFC in the first place, and for responding to an initial alpha version of libsgfc++ with a virtual whirlwind of changes to SGFC to make it much more library-friendly.

## License

libsgfc++ is released under the [Apache License](http://www.apache.org/licenses/LICENSE-2.0) (2.0). Here's the [link to the license file](LICENSE).

SGFC is released under the terms of the [BSD License](https://opensource.org/licenses/BSD-3-Clause).

- [Link to local license file](sgfc/COPYING). This works only if you have a local clone of the SGFC git submodule.
- [Link to remote license file](https://bitbucket.org/arnoh/sgfc/src/master/COPYING). This link points to the `master` branch version of the license file.

Catch2 is released under the [Boost Software License](https://www.boost.org/LICENSE_1_0.txt) (1.0).

- [Link to local license file](test/Catch2/LICENSE.txt). This works only if you have a local clone of the SGFC git submodule.
- [Link to remote license file](https://github.com/catchorg/Catch2/blob/master/LICENSE.txt). This link points to the `master` branch version of the license file.
