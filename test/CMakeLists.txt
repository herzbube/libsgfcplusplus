include( ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES_LIST_FILE_NAME} )
if ( NOT DEFINED SOURCES )
  message ( FATAL_ERROR "List of source files not defined by ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES_LIST_FILE_NAME}" )
endif()

# Here we define the test executable target. Catch2 provides us with a
# sophisticated test driver, so main.cpp is mostly empty.
add_executable (
  ${TEST_EXECUTABLE_TARGET_NAME}
  ${SOURCES}
)

target_include_directories (
  ${TEST_EXECUTABLE_TARGET_NAME}
  PRIVATE Catch2/single_include
  # The tests treat libsgfc++ itself as a third-party library, so the next two
  # include directories are required to find the public interface headers and
  # the private implementation headers.
  PRIVATE ../include
  PRIVATE ../src
)

# Unit tests test library-internal classes. We need to link against a library
# that makes the symbols for these internal classes visible to us. This should
# be static library.
target_link_libraries (
  ${TEST_EXECUTABLE_TARGET_NAME}
  ${LINK_LIBRARY_TARGET_NAME}
)

# On some platforms iconv is provided by a dedicated library that must be
# explicitly linked against.
if ( ${ICONV_NEEDS_LINKING} )
  target_link_libraries (
    ${TEST_EXECUTABLE_TARGET_NAME}
    ${ICONV_LIBRARY}
  )
endif()

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
