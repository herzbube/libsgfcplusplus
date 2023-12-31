include( ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES_LIST_FILE_NAME} )
if ( NOT DEFINED SOURCES )
  message ( FATAL_ERROR "List of source files not defined by ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES_LIST_FILE_NAME}" )
endif()

# Define a number of variables for working with the Catch2 library
set ( CATCH2_LIBRARY_BASE_NAME Catch2 )
set ( CATCH2_PACKAGE_NAME ${CATCH2_LIBRARY_BASE_NAME} )
set ( CATCH2_PACKAGE_FOUND_VARIABLE_NAME ${CATCH2_PACKAGE_NAME}_FOUND )
set ( CATCH2_LINK_LIBRARY_TARGET_NAME Catch2::Catch2WithMain )

# Attempt to find the Catch2 package, first as a system-wide package, then
# if that fails as a sub-directory in a custom location. The default is to look
# in the Catch2 Git submodule, but the user can override this.
find_package (
  ${CATCH2_PACKAGE_NAME}
  3
  QUIET)
if ( ${${CATCH2_PACKAGE_FOUND_VARIABLE_NAME}} )
  message ( STATUS "Found system-wide Catch2 CMake package." )
  message ( STATUS "${CATCH2_PACKAGE_FOUND_VARIABLE_NAME} = ${${CATCH2_PACKAGE_FOUND_VARIABLE_NAME}}" )
else()
  message ( STATUS "System-wide Catch2 CMake package not found." )

  if ( NOT DEFINED CATCH2_GITREPOSITORY_PREFIX )
    message ( STATUS "Using default git repository prefix to find Catch2 CMake package." )
    message ( STATUS "Define CATCH2_GITREPOSITORY_PREFIX to override this." )
    # A well known path: The Catch2 Git submodule.
    set ( CATCH2_GITREPOSITORY_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/Catch2" )
  else()
    message ( STATUS "Using user-provided git repository prefix to find Catch2 CMake package." )
  endif()

  # Here we expect to find the Catch2 source distribution, either as Catch2 git
  # repository clone or as a plain directory that is structurally identical to
  # the repository layout. In this form Catch2 supports easy integration via
  # add_subdirectory. The advantage over find_package() is that the user does
  # not need to build/install the Catch2 library separately - Catch2 is simply
  # built as part of the test project without the need of installation.
  message ( STATUS "Adding Catch2 CMake package as sub-directory from ${CATCH2_GITREPOSITORY_PREFIX}." )
  add_subdirectory (
    ${CATCH2_GITREPOSITORY_PREFIX}
  )
endif()

# See src/CMakeLists.txt for the explanation why we disable this compiler
# warning.
if ( ${MSVC} )
  set_source_files_properties(
    ${SOURCES}
    PROPERTIES
    COMPILE_OPTIONS "/wd4250"
  )
endif()

# Here we define the test executable target. Catch2 provides us with a
# sophisticated test driver, so main.cpp is mostly empty.
add_executable (
  ${TEST_EXECUTABLE_TARGET_NAME}
  ${SOURCES}
)

# The folder where the generated export header file is located must also be in
# our list of include directories. We don't need to specify that folder here,
# though, because we "inherit" it by linking against a libsgfc++ library target
# below. Reason: The target_link_libraries statement is also a dependency
# declaration that causes CMake to add all PUBLIC include directories of the
# dependency target to our own target.
# The same is true for the directory that contains the Catch2 header files:
# This directory is also added because we add Catch2 in the
# target_link_libraries statement below.
target_include_directories (
  ${TEST_EXECUTABLE_TARGET_NAME}
  # The tests treat libsgfc++ itself as a third-party library, so the next two
  # include directories are required to find the public interface headers and
  # the private implementation headers.
  PRIVATE ../include
  PRIVATE ../src
)

# Unit tests test library-internal classes. We need to link against a library
# that makes the symbols for these internal classes visible to us. This MUST
# be a static library because only a static library is guaranteed to have the
# necessary symbols visible on all platforms.
target_link_libraries (
  ${TEST_EXECUTABLE_TARGET_NAME}
  PRIVATE
  ${LINK_LIBRARY_TARGET_NAME}
  ${CATCH2_LINK_LIBRARY_TARGET_NAME}
)

# Define additional compile options.
# - EXPORT_HEADER_STATIC_DEFINE_MACRO_NAME macro: The test executable target
#   must define this macro to be able to link against the static library or
#   static library framework
# - COMPILE_OPTION_C_FUNCTIONS_MAY_THROW_EXCEPTIONS: Tell the compiler that
#   C functions may throw exceptions. See main CMake config file for details.
target_compile_options (
  ${TEST_EXECUTABLE_TARGET_NAME}
  PUBLIC
  -D${EXPORT_HEADER_STATIC_DEFINE_MACRO_NAME}
  ${COMPILE_OPTION_C_FUNCTIONS_MAY_THROW_EXCEPTIONS}
)

# We must define at least one test for "make test" to do anything.
# The test we define here can also be run with CMake's own ctest utility:
#   ctest all
# Since we only have one test at the moment, this would do the same:
#   ctest
# To list the tests:
#   ctest --show-only
add_test (
  NAME "all"
  COMMAND ${TEST_EXECUTABLE_TARGET_NAME}
)
