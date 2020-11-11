[![Build Status](https://travis-ci.com/herzbube/libsgfcplusplus.svg?branch=master)](https://travis-ci.com/herzbube/libsgfcplusplus)
[![Github Releases](https://img.shields.io/github/release/herzbube/libsgfcplusplus.svg)](https://github.com/herzbube/libsgfcplusplus/releases)
[![Github Releases](https://img.shields.io/github/license/herzbube/libsgfcplusplus.svg)](https://github.com/herzbube/libsgfcplusplus/blob/master/LICENSE)

## Project status

This software library project has grown out of its inception phase, but is still in a pre-release stage. Please don't use it in other software projects yet, the API is far from stable.

I have created a number of issues and a few milestones that are supposed to outline the next steps (alpha, beta, 1.0), but there is no due date for any of them.

## What is it?

libsgfc++ is a C++ wrapper library around [SGFC](https://www.red-bean.com/sgf/sgfc/). As such, libsgfc++ offers the same functionality as SGFC:

- Read and write SGF (Smart Game Format) files.
- Check the file content for correctness.
- Correct any errors.
- Convert FF[1] - FF[3] files to the FF[4] format.

libsgfc++ is not restricted to files, it also reads and writes SGF data from/to `std::string` without filesystem interaction.

SGFC is written in pure C. libsgfc++ adds an object-oriented API layer written in C++ on top of that.

libsgfc++ is cross-platform. It builds on the three major desktop operating systems (macOS, Linux, Windows) as well as on iOS. Other platforms may work as well but have not been tested.

## What it's not

The limitations of SGFC also apply to libsgfc++. Quoting from the [SGFC website](https://www.red-bean.com/sgf/sgfc/):

> SGFC is intended to be a tool for SGF experts, coders and maintainers of large SGF archives. You ought to have quite some knowledge of SGF to use SGFC efficiently.
> 
> SGFC was written primarily for Go/WeiQi/Baduk (GM[1]) files. It can't handle other games yet, i.e. it doesn't check any game-specific properties and values of other games than Go. It may even save erronous game-specific properties of other games! Use SGFC for other games with care. 

## Dependencies

At runtime libsgfc++ has no dependencies except for the C/C++ runtime library and the C++ standard library.

At build time libsgfc++ has the following dependencies:

1. The main dependency, of course, is [SGFC](https://www.red-bean.com/sgf/sgfc/).
2. The second dependency is the unit test library [Catch2](https://github.com/catchorg/Catch2).
3. The third dependency is the build management tool [CMake](https://cmake.org/cmake/help/latest/).
4. A last dependency is [Doxygen](https://www.doxygen.org/), used to optionally generate the project's API documentation.

Dependencies 1 and 2 are integrated via Git submodule.

## Project build system

The project build system is [documented here](doc/Build.md).

## More documentation

- [API documentation](https://herzbube.github.io/libsgfcplusplus/api-docs/index.html) (the public API is in the "Public API" module)
- [Why another library?](doc/WhyAnotherLibrary.md)
- [Library design and working principles](doc/Principles.md)
- [Assorted SGFC notes](doc/SgfcNotes.md)
- [Other project notes](doc/ProjectNotes.md)
- [Coding guidelines](doc/CodingGuidelines.md)

## License

libsgfc++ is released under the [Apache License](http://www.apache.org/licenses/LICENSE-2.0) (2.0). Here's the [link to the license file](LICENSE).

SGFC is released under the terms of the [BSD License](https://opensource.org/licenses/BSD-3-Clause).

- [Link to local license file](sgfc/COPYING). This works only if you have a local clone of the SGFC git submodule.
- [Link to remote license file](https://bitbucket.org/arnoh/sgfc/src/master/COPYING). This link points to the `master` branch version of the license file.

Catch2 is released under the [Boost Software License](https://www.boost.org/LICENSE_1_0.txt) (1.0).

- [Link to local license file](test/Catch2/LICENSE.txt). This works only if you have a local clone of the SGFC git submodule.
- [Link to remote license file](https://github.com/catchorg/Catch2/blob/master/LICENSE.txt). This link points to the `master` branch version of the license file.
