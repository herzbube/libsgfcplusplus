## Project build system

This document contains instructions on how to build, install and execute all parts of the project: The software library itself, the unit tests, a sample program and the API documentation.

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

## How to generate and install the API documentation

The library's source code is documented with [Doxygen](https://www.doxygen.org/) formatted inline comments. To generate the documentation you have to have Doxygen installed.

Generating and installing the API documentation is optional, and therefore is not part of the regular software build. These are the commands that need be invoked separately:

    cd build
    cmake --build   . --target    libsgfcplusplus-doc
    cmake --install . --component libsgfcplusplus-doc --prefix /path/to/destfolder

Notes:

- The generated documentation will be installed in the specified prefix location, in a subfolder `share/doc`. By default this consists of a set of HTML files.
- You can generate and install the documentation without having to build the software first.
- If you want to change the way how the documentation is generated you have to edit `doc/CMakeLists.txt`. In that file you can set variables whose names directly correspond to tags in the Doxygen configuration file. For instance, if you want to have additional LaTeX output you can set `DOXYGEN_GENERATE_LATEX` to `YES`, this will set the corresponding Doxygen tag `GENERATE_LATEX` to `YES`.
- If you modified `doc/CMakeLists.txt` so that Doxygen generates more output formats you also have to edit `doc/SourcesList.cmake` to make sure that the additional output formats are installed. Set the `OUTPUT_DIRECTORIES` variable accordingly.
- By default Doxygen generates documentation for both the public API part and the internal implementation part of the library. If you only want the public API part you can edit `doc/SourcesList.cmake` and change the `SOURCES` variable so that it does not include the `src` subfolder. If you leave the configuration as it is, then you can still focus on just the public API docs by navigating to the "Public API" module in the generated documentation.

## Sample code

The `example` folder contains sample code that demonstrates how to use the library in a client application. When you build the project a simple command line program is also built that you can invoke in one of four modes to run the sample code.

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
