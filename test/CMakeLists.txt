include( ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES_LIST_FILE_NAME} )
if ( NOT DEFINED SOURCES )
  message ( FATAL_ERROR "List of source files not defined by ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES_LIST_FILE_NAME}" )
endif()

# TODO: Use target_include_directories instead of include_directories
include_directories (
  Catch2/single_include
  # The tests treat libsgfc++ itself as a third-party library, so the next two
  # include directories are required to find the public interface headers and
  # the private implementation headers.
  ../include
  ../src
)

# Here we define the test executable target. Catch2 provides us with a
# sophisticated test driver, so main.cpp is mostly empty.
add_executable (
  ${TEST_EXECUTABLE_TARGET_NAME}
  ${SOURCES}
)

# We link against the shared library. We could also link against the static
# library, but this would be a bit slower.
target_link_libraries (
  ${TEST_EXECUTABLE_TARGET_NAME}
  ${LINK_LIBRARY_TARGET_NAME}
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

# TODO: Find out how to build bundles on iOS. The following sets the bundle
# identifier, but this alone is not sufficient.
#set_target_properties(
#  ${TEST_EXECUTABLE_TARGET_NAME}
#  PROPERTIES
#  XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "ch.herzbube.libsgfcplusplus-test"
#)
