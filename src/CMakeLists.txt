# Because we don't list files explicitly, if a file is added or removed we need
# to run
#  touch CMakeLists.txt
# in the project root folder to trigger re-generation of the build system.
# TODO Don't do globbing. The argument that convinces me is that someone
# downstream might get into trouble if for some reason they don't have a clean
# source tree.
# TODO Maybe we should also add header files and other stuff? Test what happens
# if we generate an Xcode or VisualStudio project. At least the header files
# should be part of the projects.
file ( GLOB_RECURSE SOURCES *.cpp )
file ( GLOB_RECURSE SOURCES_SGFC ../sgfc/*.c )
file ( GLOB_RECURSE HEADERS ../include/*.h )

# SGFC is written in C, but because libsgfc++ patches the SGFC source code the
# files listed here now contain C++ snippets and therefore must be built with
# the C++ compiler. Here we explicitly configure CMake to override the default
# compiler behaviour, which is to derive the language (C) from the file
# extension (.c).
set_source_files_properties (
  ../sgfc/save.c
  ../sgfc/util.c
  PROPERTIES LANGUAGE CXX
)

# This is an "object library" target: It compiles the sources but doesn't
# aggregate them into an actual shared or static library yet. The purpose of
# this is to avoid compiling the sources twice, once for the shared library and
# once for the static library.
add_library (
  ${OBJECT_LIBRARY_TARGET_NAME}
  OBJECT
  ${SOURCES_SGFC}
  ${SOURCES}
)

# Shared libraries need PIC. Static libraries don't need PIC, so the static
# library built from the object library will be a bit less performant than it
# could be. That's the price we pay for compiling only once. If we wanted an
# ultra-fast static library we would have to compile twice.
set_property (
  TARGET ${OBJECT_LIBRARY_TARGET_NAME}
  PROPERTY POSITION_INDEPENDENT_CODE 1
)

# Here we finally build the shared and static libraries. We build them
# from the same set of object files.
add_library (
  ${SHARED_LIBRARY_TARGET_NAME}
  SHARED
  $<TARGET_OBJECTS:${OBJECT_LIBRARY_TARGET_NAME}>
)
add_library (
  ${STATIC_LIBRARY_TARGET_NAME}
  STATIC
  $<TARGET_OBJECTS:${OBJECT_LIBRARY_TARGET_NAME}>
)
