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

* SGFC invokes `exit()` deep within a helper function to abort program execution whhen it finds a fatal error in the SGF data. This is a no-go for a software library. libsgfc++ patches the `exit()` call into oblivion and replaces it with a different mechanism to report fatal errors to its clients.
* SGFC prints warnings and errors that occur during parsing to `stdout`. libsgfc++ modifies SGFC so that it can make these warnings and errors available to its clients in a programmatical way.
* SGFC uses many global and `static` variables that are initialized only once, because a command line utility only needs to run once. libsgfc++ changes this so that its clients can run the library functions over and over without stopping the program.

## Why another library?

The Smart Game Format is a decades old, established file format. There are many Go applications out there that have to deal with SGF files. Surely someone else has already written a reusable C/C++ software library for reading and writing SGF files. Right?

Alas, the answer seems to be "No". 

When you look at the list of known Go-related software projects on [Sensei's Library](https://senseis.xmp.net/?SGFFile), especially the libraries section, you will notice that there are indeed quite a few libraries. The problem is that all except one are written in non-C/C++ languages.

The exception is GNU Go, which is written in C, and which contains [a library component](http://www.gnu.org/software/gnugo/gnugo_16.html) that can read and write SGF files. The first problem is that the component is not a standalone library. The second and much more severe problem is that GNU Go is published under the GNU GPL license. Integrating the GNU Go code into a library would force the library to also adopt the GNU GPL license, which would prevent the library from being used in certain scenarios. Notably it would not be possible to integrate the library into an iOS app that is published on the Apple App Store - which unfortunately is exactly the main motivation behind this library project. If you want to read the FSF's stance on this check out their posts from 2010 [here](https://www.fsf.org/news/2010-05-app-store-compliance) and [here](https://www.fsf.org/blogs/licensing/more-about-the-app-store-gpl-enforcement).

There is also [Fuego](http://fuego.sourceforge.net/), which similar to GNU Go contains an SGF reading/writing component, but is published under the LGPL license. Although Fuego solves the license problem, there is still the other issue that the SGF-handling component is not built and distributed as a standalone library, but rather as part of a whole command line program.

At this point it seems clear that a new library project is in order. The question remains whether SGFC or Fuego should be adapted/wrapped. Here are some considerations:

- Fuego's SGF component is bound to the purpose of enabling Fuego, so there is a certain danger of limitations that serve that purpose. SGFC on the other hand is a standalone program without any obligations to a higher goal, and is therefore probably more general-purpose in nature.
- SGFC has a clear focus on robustness in the face of incomplete or even erroneous SGF data. When it can't handle a certain piece of data it has a documented mechanism of reporting warnings and/or errors to the user. This is a very valuable function for a library and not something that Fuego's SGF component can offer.
- SGFC can read files in older SGF formats and write them as FF[4], so it provides a valuable conversion function. While there are some hints in the Fuego source code that Fuego's SGF component can do a bit more than read only FF[4], there is certainly not the same amount of dedication to read old formats as there is in SGFC.

The conclusion from this miniature evaluation is that SGFC clearly seems to be the better choice.

## Dependencies

This project only has two dependencies:

- The main dependency, of course, is [SGFC](https://www.red-bean.com/sgf/sgfc/).
- The only other dependency this project has is the unit test library [Catch2](https://github.com/catchorg/Catch2).

Both dependencies are integrated via Git submodule.

## How to build

The project requires CMake 3.10 or newer to build.

After cloning the repository you must first initialize its Git submodules:

    cd /path/to/project
    git submodule update --init --recursive

In the next step you apply some patches to SGFC:

    cd sgfc
    for PATCH_FILE in ../patch/*; do git apply "$PATCH_FILE"; done
    cd ..

Now you're ready to build. These commands should do it:

    mkdir build
    cd build
    # If you want a debug build then replace "Release" with "Debug"
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .

## How to test

After building you can run tests from the `build` folder with this command:

    ctest

Why does `ctest` report only a single test? This is because CMake sees the Catch2 test runner as a single test, when in fact the test runner is only the "facade" of the project's entire test suite. Execute the Catch2 test runner directly, with something like the following command, to see more detailed results. The command may vary on different platforms.

    ./test/libsgfcplusplus-test

## How to install

After the tests have run successfully you install the build products to a destination folder of your choice. CMake 3.15 and newer include a command line option `--install` which can be used like this:

    cmake --install . --prefix /path/to/destfolder

Older CMake versions don't have the `--install` command line option and you must use the generated build system to perform the installation. You also have to define the prefix folder when you generate the build system. Example for `make`:

    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/path/to/destfolder ..
    [...]
    make install

The following things will be installed:

- Subfolder `lib`: A shared library and a static library.
- Subfolder `include`: The library's public header files.
- Subfolder `Frameworks`: A shared library framework and a static library framework.

## Enabling/disabling build parts

The default build builds everything, but if you wish you can disable certain parts by setting the corresponding variables:

- Set `ENABLE_SHARED_LIBRARY` to `NO` to prevent the shared library from being built.
- Set `ENABLE_STATIC_LIBRARY` to `NO` to prevent the static library from being built.
- Set `ENABLE_SHARED_FRAMEWORK` to `NO` to prevent the shared library framework from being built.
- Set `ENABLE_STATIC_FRAMEWORK` to `NO` to prevent the static library framework from being built.
- Set `ENABLE_TESTS` to `NO` to prevent unit tests from being built.
- Set `ENABLE_EXAMPLES` to `NO` to prevent the examples from being built.

The following example builds everything except the static library framework and the examples:

    cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_STATIC_FRAMEWORK=NO -DENABLE_EXAMPLES=NO ..
    cmake --build .

You can also set the variable `ENABLE_DEFAULT` to `NO` as a quick way to change the default from "build everything" to "build nothing". After that you can enable only certain parts.

The following example only builds the shared library:

    cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_DEFAULT=NO -DENABLE_SHARED_LIBRARY=YES ..
    cmake --build .

## Xcode build

In the previous section you have seen how to generate a Makefile-based build system. Cmake can also generate an Xcode project, like this:

    cd build
    cmake -G Xcode ..
    
    # Launch Xcode with the generated project
    open libsgfc++.xcodeproj

The `ALL_BUILD` target in the Xcode project builds all targets, i.e. both the shared and the static libraries, the shared and static library frameworks, and the unit tests.

The `RUN_TESTS` target builds the unit test target and executes a custom post-build script that is supposed to run the test. The post-build script currently doesn't seem to work. It is therefore recommended building the unit test target (`libsgfc++-test`) and selecting "Product > Run" to execute the test runner. This always works, and Xcode is even nice enough to pop up an output pane that shows you the output of the command line test runner.

The `ZERO_CHECK` target checks whether your `CMakeLists.txt` files have changed and if necessary updates the Xcode project with the changes.

## Cross-compiling for iOS

Cross-compiling for iOS is mentioned and explained in the `cmake-toolchains` man page, which is also available [from the CMake website](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#cross-compiling-for-ios-tvos-or-watchos).

These commands create a Release configuration build of the static library and static library framework for iOS on a macOS machine where Xcode is installed:

    cmake .. -G Xcode \
      -DCMAKE_SYSTEM_NAME=iOS \
      "-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64" \
      -DCMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH=NO \
      -DCMAKE_IOS_INSTALL_COMBINED=YES \
      -DCMAKE_INSTALL_PREFIX=install

    cmake --build . --config Release --target install

Notes:

- We list two architectures: `x86_64` for the simulator build, and `arm64` for the device build. The result of both builds will be stored in the same library files, making them so-called "universal" binaries. Use `lipo -info /path/to/file` to check what's inside such a file.
- Setting the `ONLY_ACTIVE_ARCH` flag to `NO` is important so that Xcode really builds those architectures we just mentioned. If we didn't set this Xcode would only build the architecture in the `NATIVE_ARCH` Xcode build setting.
- Setting the CMake property `IOS_INSTALL_COMBINED` to `YES` causes the targets to be built  for both the device SDK and the simulator SDK. It's not known why exactly this is needed in addition to the previous settings.
- It's important that the build is made with the target `install` because only then will CMake generate the simulator build. Also if you don't use this target and perform installation in a separate step (with `cmake --install`), CMake will be unable to find the generated library files. The reason fo these quirks is not known.
- Because we do the build and the installation all in one step, we can't specify the installation prefix during that step (the `--prefix` option cannot be used with `cmake --build`). For this reason we set `INSTALL_PREFIX` during configuration.

## Codesigning when building for iOS

For iOS builds the project default is to **not** build the shared library, shared library framework, unit tests or the examples. The reason is that when built for the device these binaries all require codesigning, but since the project does not provide a codesigning identity the build would just fail.

The following example shows how you can force the shared library to be built with a codesigning identity of your own.

    cmake .. -G Xcode \
      [...]  # same options as shown in the cross-compiling section
      -DENABLE_SHARED_LIBRARY=YES \
      -DCMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY=<identity>

**Note:** You can find out your codesigning identy with this command: `xcrun security find-identity -v -p codesigning`. It's the long hex string at the start of the output.

## Deployment target and bundle identifier when building for iOS

Should you try to build unit tests or the examples for iOS (by setting `ENABLE_TESTS` or `ENEABLE_EXAMPLES` to `YES`) you will encounter two obstacles.

1. The unit test library (Catch2) header contains code that is available only since iOS 10.0. Because of this you have to set the deployment target to 10.0. This tells the compiler to generate binaries that at runtime require iOS 10.0 as the minimum iOS version. The deployment target is set with the CMake option `-DCMAKE_OSX_DEPLOYMENT_TARGET=10.0`.
1. The unit test runner and the examples are executables, so they need to be codesigned. Unlike a shared library, executables can only be codesigned if they have a bundle identifier. The project does not provide any bundle identifiers, so if you insist on building the unit tests and/or the examples that is something you have to provide. There is currently no example how to build bundles - a starting point would be the [CMake documentation for MACOSX_BUNDLE](https://cmake.org/cmake/help/latest/prop_tgt/MACOSX_BUNDLE.html).

## Sample code

The `example` folder contains sample code that demonstrates how to use the library in a client application. When you build the project a simple command line program is built that you can invoke in one of four modes to run the sample code.

```
Usage:
  ./libsgfcplusplus-example cmdline   input-file [output-file]
  ./libsgfcplusplus-example docread   input-file
  ./libsgfcplusplus-example docwrite  input-file output-file
  ./libsgfcplusplus-example buildtree output-file
```

The four modes quickly explained:

* Mode "cmdline" demonstrates the usage of `ISgfcCommandLine`.
* Mode "docread"  demonstrates the usage of `ISgfcDocumentReader`.
* Mode "docwrite"  demonstrates the usage of `ISgfcDocumentWriter`.
* Mode "buildtree"  demonstrates the usage of the various factories to programmatically build a game tree.

## License

libsgfc++ is released under the [Apache License](http://www.apache.org/licenses/LICENSE-2.0) (2.0).

SGFC is released under the terms of the [BSD License](https://opensource.org/licenses/BSD-3-Clause).

