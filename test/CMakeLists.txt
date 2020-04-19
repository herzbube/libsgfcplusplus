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
  main.cpp
  SgfcMessageParserTest.cpp
  SgfcMessageTest.cpp
)

# We link against the shared library. We could also link against the static
# library, but this would be a bit slower.
target_link_libraries (
  ${TEST_EXECUTABLE_TARGET_NAME}
  ${LINK_LIBRARY_TARGET_NAME}
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
