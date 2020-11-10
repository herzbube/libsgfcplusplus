## Project build system

This document contains instructions on how to build, install and execute all parts of the project: The software library itself, the unit tests, a sample program and the API documentation.

## How to build

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
- Subfolder `include/libsgfcplusplus`: The library's public header files.
- Subfolder `Frameworks`: A shared library framework and a static library framework.
- Subfolder `lib/libsgfcplusplus`: CMake package files.

A couple of notes:

- Public header files: Unless downstream projects specify the subfolder as an include directory to their compiler, they will have to use include statements that include the subfolder name. Example: `#include <libsgfcplusplus/SgfcPlusPlusFactory.h>`.
- The CMake package files are there so that a downstream project that also uses CMake to generate its build system can easily integrate libsgfc++ into its own build with the CMake command `find_package()`. See the section "CMake support for downstream projects" below for more details.

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

## CMake support for downstream projects

libsgfc++ exports its CMake targets (both from the build tree and from the install tree) as a CMake package. This allows downstream projects that also use CMake to generate their build system to easily integrate libsgfc++ into their own build. The CMake command for this is `find_package()`.

If libsgfc++ has been installed to a system-wide installation path (e.g. `/usr/local`) then it can be found without specifying a path. The search logic employed by `find_package()` is exceedingly complicated and is not documented here. If you want to know more look it up in the CMake documentation of the `find_package()` command.

An example:

    find_package (
      libsgfcplusplus
      0.1
      EXACT
    )

If libsgfc++ has been installed to some non-standard path, then the downstream project must provide a hint where to look for the CMake package files. The hint should be the installation prefix used to install libsgfc++, not the subfolder where the CMake package files actually reside. Again, `find_package()` employs clever search logic to probe for the files.

Another example:

    find_package (
      libsgfcplusplus
      0.1
      EXACT
      HINT /path/to/installation-prefix
    )

As can be seen in the examples, the package name to use is `libsgfcplusplus`. The exported targets all have the prefix `libsgfcplusplus::`. The exported targets are:

- `libsgfcplusplus::libsgfcplusplus_shared`
- `libsgfcplusplus::libsgfcplusplus_static`
- `libsgfcplusplus::libsgfcplusplus_shared_framework`
- `libsgfcplusplus::libsgfcplusplus_static_framework`

To use the exported targets after `find_package()` has successfully located the package, the downstream project typically specifies the exported target names in their `target_link_libraries()` commands. Example:

    target_link_libraries (
      downstream-target-name
      libsgfcplusplus::libsgfcplusplus_shared
    )

This not only adds the link instructions to the downstream target, it also adds the INTERFACE include directories of the linked libsgfc++ target to the include directories of the downstream target. This way the downstream project can write `#include` statements like this in their source code:

    #include <libsgfcplusplus/SgfcPlusPlusFactory.h>
