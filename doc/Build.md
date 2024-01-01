## Project build system

This document contains instructions on how to build, install and execute all parts of the project: The software library itself, the unit tests, a sample program and the API documentation.

## Prerequisites

The project requires CMake 3.10 or newer to build, and a reasonably modern version of Git to clone the project repository and fetch some Git submodules. Building the API documentation requires Doxygen.

Use your package manager of choice to install these components on your system. On macOS the recommended package manager is [Homebrew](https://brew.sh/), on Windows it's [Chocolatey](https://chocolatey.org/).

## How to build

After cloning the repository you must first initialize its Git submodules:

    cd /path/to/project
    git submodule update --init --recursive

Now you're ready to build. On platforms that support Makefile-based build systems these commands should do it:

    mkdir build
    cd build
    # If you want a debug build then replace "Release" with "Debug"
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .

Building with Xcode or Visual Studio is explained in sections further down.

## How to test

### Executing tests

After building you can run tests from the `build` folder with this command:

    ctest

Why does `ctest` report only a single test? This is because CMake sees the Catch2 test runner as a single test, when in fact the test runner is only the "facade" of the project's entire test suite. Execute the Catch2 test runner directly, with something like the following command, to see more detailed results. The command may vary on different platforms.

    ./test/libsgfcplusplus-test

The Catch2 test runner also has more capabilities than `ctest` to control which tests should be run. Invoke the test runner with the `-h` option to see all the options that are available. Example: All test scenarios are tagged, you can list those tags like this:

    ./test/libsgfcplusplus-test --list-tags

To run only tests marked with certain tags specify the tags in brackets. The following examples only runs tests that are related to text encodings and/or that excercise go-specific functionality:

    ./test/libsgfcplusplus-test "[encoding],[go]"   # or
    ./test/libsgfcplusplus-test "[encoding][go]"    # and

The `[filesystem]` tag marks all tests that interact with the filesystem. To exclude these:

    ./test/libsgfcplusplus-test "~[filesystem]"

For more details see the [Catch2 documentation](https://github.com/catchorg/Catch2/blob/devel/docs/command-line.md).


### Integrating Catch2 into the build

The libsgfc++ build system integrates Catch2 by way of the CMake commands `find_package()` or `add_subdirectory()`. It attempts to locate the package in two steps:

1. First the build system looks for a system-wide package in a series of likely installation paths. The search logic is exceedingly complicated and can be looked up in the CMake documentation of the `find_package()` command.
2. If there is no system-wide package the build system then looks for the package in a defined path where it expects to find a Catch2 source distribution. This can be either a Catch2 git repository clone or a a plain directory that is structurally identical to the repository layout. For this the build system uses the `add_subdirectory()` command.

If both lookup attempts fail, the build fails.

You can define the source distribution path where the build system should look for the package by defining the variable `CATCH2_SOURCEDISTRIBUTION_PREFIX`:

    cmake -DCMAKE_BUILD_TYPE=Release \
          -DCATCH2_SOURCEDISTRIBUTION_PREFIX=/path/to/folder \
          ..

If you don't define a source distribution path, the build system assumes `test/Catch2` as the default source distribution path. This path points to the Catch2 Git submodule which you have initialized at the very beginning.

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

## Enabling/disabling build products

The default build builds everything, but if you wish you can disable certain build products by setting the corresponding variables:

- Set `ENABLE_SHARED_LIBRARY` to `NO` to prevent the shared library from being built.
- Set `ENABLE_STATIC_LIBRARY` to `NO` to prevent the static library from being built.
- Set `ENABLE_SHARED_FRAMEWORK` to `NO` to prevent the shared library framework from being built.
- Set `ENABLE_STATIC_FRAMEWORK` to `NO` to prevent the static library framework from being built.
- Set `ENABLE_TESTS` to `NO` to prevent unit tests from being built.
- Set `ENABLE_EXAMPLES` to `NO` to prevent the examples from being built.

The following example builds everything except the static library framework and the examples:

    cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_STATIC_FRAMEWORK=NO -DENABLE_EXAMPLES=NO ..
    cmake --build .

You can also set the variable `ENABLE_DEFAULT` to `NO` as a quick way to change the default from "build everything" to "build nothing". After that you can enable only certain build products.

The following example only builds the shared library:

    cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_DEFAULT=NO -DENABLE_SHARED_LIBRARY=YES ..
    cmake --build .

## Xcode build

In the previous section you have seen how to generate a Makefile-based build system. CMake can also generate an Xcode project, like this:

    cd build
    cmake -G Xcode ..
    
    # Launch Xcode with the generated project
    open libsgfc++.xcodeproj

The `ALL_BUILD` target in the Xcode project builds all targets, i.e. both the shared and the static libraries, the shared and static library frameworks, and the unit tests.

The `RUN_TESTS` target builds the unit test target and executes a custom post-build script that is supposed to run the test. The post-build script currently doesn't seem to work. It is therefore recommended building the unit test target (`libsgfc++-test`) and selecting "Product > Run" to execute the test runner. This always works, and Xcode is even nice enough to pop up an output pane that shows you the output of the command line test runner.

The `ZERO_CHECK` target checks whether your `CMakeLists.txt` files have changed and if necessary updates the Xcode project with the changes.

## Building on Windows

### Visual Studio

CMake can generate a Visual Studio solution like this:

    cd build
    cmake -G "Visual Studio 16 2019" ..

If you use a different version of Visual Studio replace the `-G` parameter value. Invoking just `cmake -G` prints out available values.

When CMake has finished you can launch Visual Studio with the generated solution file `libsgfc++.sln`.

The above generates a true "out of source" build system that is so typical for CMake. An alternative approach is shown in the article [CMake projects in Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio) on Microsoft's official documentation site. This is a convenient GUI-only approach, but it generates stuff in two folders `.vs` and `out` in the project root.

### Cygwin

Some packages need to be installed before building can start:

* Either clang or gcc
* CMake
* make
* libiconv

Once all packages are installed the Cygwin build works just like it does on other UNIX-like systems. Just follow the steps in the first sections at the top of this document.

### MinGW/MSYS

No instructions available. This has not been tested yet.

## Cross-compiling for iOS

Cross-compiling for iOS (or for any of the other Apple device OS's) currently seems to be a bit of a moving target in CMake, due to some changes that have been going on in the Apple developer ecosystem in the last years. Driving factors are the introduction of Silicon Macs (i.e. macOS machines running on ARM processors) and the continued evolution of Xcode (e.g. introduction of a new / removal of the old build system).

The next two sections therefore present two ways how to cross-compile for iOS: An old way, which will eventually stop working in future CMake versions (and probably does not even work today on Silicon Macs), and a new way, which may need refinement in the future but should at least work on all machines given modern versions of CMake and Xcode are used.

Both solutions build on CMake's basic mechanics for cross-compiling for iOS, which are explained in the `cmake-toolchains` man page and are also available [from the CMake website](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html#cross-compiling-for-ios-tvos-or-watchos).

### The old way: `IOS_INSTALL_COMBINED`

Here is a set of commands that should work with CMake 3.28.1, on an Intel macOS machine where Xcode 15 is installed. This solution uses the property `IOS_INSTALL_COMBINED`, which  has been deprecated in CMake version 3.28, so the solution will eventually stop working once CMake removes the property completely. Also note that the solution most likely does not work on Silicon Macs - if you have one of these machines then jump ahead to the "new way" section below.

    cd /path/to/libsgfcplusplus
    mkdir build
    
    cd build
    cmake .. -G Xcode \
      -DCMAKE_SYSTEM_NAME=iOS \
      "-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64" \
      -DCMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH=NO \
      -DCMAKE_IOS_INSTALL_COMBINED=YES

    cmake --build . --config Release
    cmake --install . --prefix `pwd`/install

Notes:

- The commands create a Release configuration build. The configuration is not specified in the first command via `-DCMAKE_BUILD_TYPE=Release` because the Xcode generator produces a multi-configuration build system which is capable of building both Debug and Release configurations. The configuration therefore must be selected during the `--build` step.
- Because none of the `ENABLE_*` variables is set, the libsgfc++ project's CMake configuration internally decides to create only the static library and the static library framework. The reason is to avoid a codesigning error - see the section [Codesigning when building for iOS](#codesigning-when-building-for-ios) for more details.
- We list two architectures: `x86_64` for the simulator build, and `arm64` for the device build. The result of both builds will be stored in the same library files, making them so-called "universal" binaries. Use `lipo -info /path/to/file` to check what's inside such a file. Omitting `CMAKE_OSX_ARCHITECTURES` builds slices for all default architectures.
- Setting the `ONLY_ACTIVE_ARCH` flag to `NO` is important so that Xcode really builds those architectures we just mentioned. If we didn't set this Xcode would only build the architecture in the `NATIVE_ARCH` Xcode build setting.
- Setting the CMake property `IOS_INSTALL_COMBINED` to `YES` causes the targets to be built for both the device SDK and the simulator SDK. An `arm64` build made with the device SDK is slightly different than an `arm64` build made with the simulator SDK. CMake figures out on its own which SDK it must use to build each architecture. The property also indicates to CMake that it needs to build **all** architectures in `CMAKE_OSX_ARCHITECTURES`, not just the first, and to stitch together all resulting slices into a universal binary.
- When using a modern version of CMake together with the new Xcode build system (introduced in Xcode 10) it is important that the `--build` and the `--install` steps are done separately, because only then does CMake work correctly with that new Xcode build system.
  - With older versions of CMake it was mandatory to use the old Xcode build system (you had to specify `-T buildsystem 1` to the generate CMake command), **and** it was also mandatory to combine the build and install steps, i.e. to have only a `--build` step during which the option `--target install` is also specified.
  - Because modern Xcode versions no longer support the old build system the combined build/install step approach is no longer viable with modern CMake/Xcode versions.
- In the `--install` step, the `pwd` command is used because CMake requires the installation prefix to be an absolute path.

### The new way: XCFramework

The results of the "old way" solution are universal (aka "fat") binaries: These are binaries that can contain multiple architectures (aka "slices") as long as they are different. On Intel macOS machines this is fine because the simulator build (`x86_64` architecture) and the device build (`arm64` architecture) have different architectures, so it is no problem to store both slices in the same universal binary. On ARM macOS machines (aka Silicon Macs) this does not work, though, because on these machines the simulator build and the device build both use the `arm64` architecture.

Apple's solution for this is a new kind of framework called "XCFramework": This is an enhanced framework bundle (recognizable by the extension `.xcframework`) that can contain any number of binaries for different platforms. It seems that currently CMake does not have built-in support for creating XCFrameworks, instead one has to stitch together an XCFramework bundle manually from individual framework parts using `xcodebuild -create-xcframework`. 

Here is an example that was tested on an Intel Mac, but should also work on a Silicon Mac. Note that this solution no longer uses the deprecated property `IOS_INSTALL_COMBINED`

```
cd /path/to/libsgfcplusplus
mkdir -p build/simulator build/device

cd build/simulator
cmake ../.. -G Xcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphonesimulator
cmake --build . --config Release
cmake --install . --prefix `pwd`/install

cd ../device
cmake ../.. -G Xcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphoneos
cmake --build . --config Release
cmake --install . --prefix `pwd`/install

cd ..
xcodebuild -create-xcframework \
           -framework simulator/install/Frameworks/libsgfcplusplus_static.framework \
           -framework device/install/Frameworks/libsgfcplusplus_static.framework \
           -output libsgfcplusplus_static.xcframework
```

Notes:

- The solution creates two wholly separate builds for the simulator and device platforms, using the same set of generate/build/install commands that were also used in the "old way" solution.
- The `CMAKE_OSX_SYSROOT` variable selects the SDK to be used for building each platform. Specifying an SDK name without a version (e.g. `iphonesimulator` instead of `iphonesimulator17.2`) selects the latest SDK version. A list of available SDKs can be obtained by running `xcodebuild -showsdks`.
- We omit `CMAKE_OSX_ARCHITECTURES` and let Xcode build slices for all default architectures of the target platform. On Silicon Macs this should only build only an `arm64` slice for both platforms. On Intel Macs this builds only an `arm64` slice for the device platform, and both `arm64` and `x86_64` slices for the simulator platform. `-DCMAKE_OSX_ARCHITECTURES=x86_64` can be specified to avoid building two slices for the simulator.
- For simplicity's sake the example does not specify any of the `ENABLE_*` variables. This results in both the shared library and the shared library framework to be built, although we only need the framework for stitching the XCFramework. The overhead of building the unneeded shared library is negligible, though, because it consists of the same object files as the framework. To avoid building the shared library, the options `-DENABLE_DEFAULT=NO` and `-DENABLE_STATIC_FRAMEWORK=YES` can be added to the generate command.
- The CMake cross-compilation documentation mentions that with the Xcode generator it is possible to generate only one build system (i.e. have only one `-G` command) without specifying the SDK, and then selecting the SDK during the `--build` step with `-sdk <sdk-name>`. The same documentation also gives a warning that taking this shortcut might cause problems with commands such as `find_package()` or `find_library()`. To be on the safe side our example therefore does not use the shortcut.

### Xcode's old/new build system

If you see an Xcode build error "unable to attach DB" then you are likely affected by an incompatibility between the way how CMake handles `IOS_INSTALL_COMBINED` and the Xcode build system. Depending on the combination of versions of Xcode and CMake that you have, if you still want to use `IOS_INSTALL_COMBINED` you may therefore need to select the old or the new Xcode build system.

Some background information:

- Xcode 10 introduced a new build system, Xcode 13 deprecated the old build system and XCode 14 completely removed the old build system.
- Since CMake 3.19 you can specify `-T buildsystem=<value>` to a CMake generator command (a command using the `-G` option) to select the Xcode build system to be used later on in the `--build` step.
- Value "1" selects the old build system, value "12" selects the new build system. By default CMake selects the new build system.

## Codesigning when building for iOS

For iOS builds the project default is to **not** build the shared library, shared library framework, unit tests or the examples. The reason is that when built for the device these binaries all require codesigning, but since the project does not provide a codesigning identity the build would just fail.

The following example shows how you can force the shared library to be built with a codesigning identity of your own.

    cmake .. -G Xcode \
      [...]  # same options as shown in the cross-compiling section
      -DENABLE_SHARED_LIBRARY=YES \
      -DCMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY=<identity>

**Note:** You can find out your codesigning identy with this command: `xcrun security find-identity -v -p codesigning`. It's the long hex string at the start of the output.

## Deployment target and bundle identifier when building for iOS

When you build libsgfc++ for iOS you may encounter errors because some build products require a certain minimum iOS version. Known cases:

- libsgfc++ requires iOS 13 or newer because of its usage of `std::filesystem`
- The unit test library (Catch2) contains code that is available only since iOS 10.0.

If you have these errors you have to set the deployment target to 13.0. The deployment target is set with the CMake option `-DCMAKE_OSX_DEPLOYMENT_TARGET=13.0`.

## Bundle identifier when building for iOS

Should you try to build unit tests or the examples for iOS you will encounter an obstacle: The unit test runner and the examples are both executables, so they need to be codesigned, but unlike a shared library an executable can only be codesigned if it has a bundle identifier.

The project does not provide any bundle identifiers, so if you insist on building the unit tests and/or the examples for iOS that is something you have to provide. There is currently no example how to build bundles - a starting point would be the [CMake documentation for MACOSX_BUNDLE](https://cmake.org/cmake/help/latest/prop_tgt/MACOSX_BUNDLE.html).

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

This not only adds the link instructions (including to the `iconv` dependency) to the downstream target, it also adds the INTERFACE include directories of the linked libsgfc++ target to the include directories of the downstream target. This way the downstream project can write `#include` statements like this in their source code:

    #include <libsgfcplusplus/SgfcPlusPlusFactory.h>
