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
> SGFC was written primarily for Go/WeiQi/Baduk (GM[1]) files. It can't handle other games yet, i.e. it doesn't check any game-specific properties and values of other games than Go. It may even save errornous game-specific properties of other games! Use SGFC for other games with care. 

## Command line tool vs. software library

SGFC is very good as a command line tool, but it is not a software library. Although other programs can execute SGFC to process SGF files, they cannot make use of SGFC's functions to programmatically gain access to the actual SGF data.
 
Enter libsgfc++.

libsgfc++ applies a number of patches to the original SGFC source code to make it more suitable in a software library context. SGFC is quite unusable as a library without these modifications, because many of its routines are designed for command line usage. The main points are:

* SGFC uses `exit()` deep within a helper function to abort program execution if a fatal error is found. This is a no-go for a software library. libsgfc++ patches the `exit()` call into oblivion and replaces it with a different mechanism to report fatal errors to its clients.
* SGFC prints warnings and errors that occur during parsing to `stdout`. libsgfc++ modifies SGFC so that it can make these warnings and errors available to its clients.
* SGFC uses many global and `static` variables that are initialized only once, because a command line utility only needs to run once. libsgfc++ changes this so that its clients can run the library functions over and over without stopping the program.

## Why another library?

The Smart Game Format is a decades old, established file format. There are many Go applications out there that have to deal with SGF files. Surely someone else has already written a reusable C/C++ software library for reading and writing SGF files. Right?

Alas, the answer seems to be "No". 

When we look at the list of known software projects on [Sensei's Library](https://senseis.xmp.net/?SGFFile), especially the libraries section, we notice that there are indeed quite a few libraries. The problem is that all except one are written in non-C/C++ languages.

The exception is GNU Go, which is written in C, and which contains [a library component](http://www.gnu.org/software/gnugo/gnugo_16.html) that can read and write SGF files. The first problem is that the component is not a standalone library. The second and much more severe problem is that GNU Go is published under the GNU GPL license. I need the library to have a more relaxed license so that it can be integrated into an iOS app that is published on the Apple App Store.

There is also [Fuego](http://fuego.sourceforge.net/), which similar to GNU Go contains an SGF reading/writing component, but is published under the LGPL license. Although the license problem is solved, there is still the other issue that the SGF-handling component is not distributed as a standalone library, but rather as part of a whole command line program.

At this point I decided that a new library project was required. I still had the choice between adapting/wrapping SGF and Fuego. I went for SGFC because it is more robust and can handle files in older SGF formats.

## How to build and test

The project requires CMake 3.10 or newer to build.

After cloning the repository you must first initialize its Git submodules:

    cd /path/to/project
    git submodule update --init --recursive

Now you're ready to build. These commands should do it:

    mkdir build
    cd build
    # If you want a debug build then replace "Release" with "Debug"
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .

After building you can run tests from the `build` folder with this command:

    ctest

## License

libsgfc++ is released under the [Apache License](http://www.apache.org/licenses/LICENSE-2.0) (2.0).

SGFC is released under the terms of the [BSD License](https://opensource.org/licenses/BSD-3-Clause).

