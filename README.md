[![Build Status](https://travis-ci.com/herzbube/libsgfcplusplus.svg?branch=master)](https://travis-ci.com/herzbube/libsgfcplusplus)
[![Github Releases](https://img.shields.io/github/release/herzbube/libsgfcplusplus.svg)](https://github.com/herzbube/libsgfcplusplus/releases)
[![Github Releases](https://img.shields.io/github/license/herzbube/libsgfcplusplus.svg)](https://github.com/herzbube/libsgfcplusplus/blob/master/LICENSE)

## Project status

This software library project has grown out of its inception phase, but is still clearly pre-alpha. Please don't use it in other software projects yet, the API is far from stable.

I have created a number of issues and a few milestones that are supposed to outline the next steps (alpha, beta, 1.0), but there is no due date for any of them.

## What is it?

libsgfc++ is a C++ wrapper library around [SGFC](https://www.red-bean.com/sgf/sgfc/). As such, libsgfc++ offers the same functionality as SGFC:

- Read and write SGF (Smart Game Format) files.
- Check the file content for correctness.
- Correct any errors.
- Convert FF[1] - FF[3] files to the FF[4] format.

SGFC is written in pure C. libsgfc++ adds a thin object-oriented API layer written in C++ on top of that.

## What it's not

The limitations of SGFC also apply to libsgfc++. Quoting from the [SGFC website](https://www.red-bean.com/sgf/sgfc/):

> SGFC is intended to be a tool for SGF experts, coders and maintainers of large SGF archives. You ought to have quite some knowledge of SGF to use SGFC efficiently.
> 
> SGFC was written primarily for Go/WeiQi/Baduk (GM[1]) files. It can't handle other games yet, i.e. it doesn't check any game-specific properties and values of other games than Go. It may even save erronous game-specific properties of other games! Use SGFC for other games with care. 

## Command line tool vs. software library

SGFC is very good as a command line tool, but it is not a software library. Although other programs can execute SGFC to process SGF files, they cannot make use of SGFC's functions to programmatically gain access to the actual SGF data.
 
Enter libsgfc++.

libsgfc++ applies a number of patches to the original SGFC source code to make it more suitable in a software library context. SGFC is quite unusable as a library without these modifications, because many of its routines are designed for command line usage. The main points are:

* SGFC invokes `exit()` deep within a helper function to abort program execution when it finds a fatal error in the SGF data. This is a no-go for a software library. libsgfc++ patches the `exit()` call into oblivion and replaces it with a different mechanism to report fatal errors to its clients.
* SGFC prints warnings and errors that occur during parsing to `stdout`. libsgfc++ modifies SGFC so that it can make these warnings and errors available to its clients in a programmatical way.
* SGFC uses many global and `static` variables that are initialized only once, because a command line utility only needs to run once. libsgfc++ changes this so that its clients can run the library functions over and over without stopping the program.

Detailed information about each patch can be found in [SgfcPatches.md](doc/SgfcPatches.md).

## Dependencies

At runtime this project has no dependencies except for the C/C++ runtime library and the C++ standard library.

At build time this project has the following dependencies:

1. The main dependency, of course, is [SGFC](https://www.red-bean.com/sgf/sgfc/).
2. The second dependency is the unit test library [Catch2](https://github.com/catchorg/Catch2).
3. The third dependency is the build management tool [CMake](https://cmake.org/cmake/help/latest/).
4. A last dependency is [Doxygen](https://www.doxygen.org/), used to optionally generate the project's API documentation.

Dependencies 1 and 2 are integrated via Git submodule.

## Project build system

The project build system is [documented here](doc/Build.md).

## More documentation

- [Why another library?](doc/WhyAnotherLibrary.md)
- [Library design and working principles](doc/Principles.md)
- [Assorted SGFC notes](doc/SgfcNotes.md)
- [Coding guidelines](doc/CodingGuidelines.md)

## License

libsgfc++ is released under the [Apache License](http://www.apache.org/licenses/LICENSE-2.0) (2.0).

SGFC is released under the terms of the [BSD License](https://opensource.org/licenses/BSD-3-Clause).

