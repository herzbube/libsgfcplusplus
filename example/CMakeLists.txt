include( ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES_LIST_FILE_NAME} )
if ( NOT DEFINED SOURCES )
  message ( FATAL_ERROR "List of source files not defined by ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES_LIST_FILE_NAME}" )
endif()

# Here we define the example executable target.
add_executable (
  ${EXAMPLE_EXECUTABLE_TARGET_NAME}
  ${SOURCES}
)

# The folder where the generated export header file is located must also be in
# our list of include directories. We don't need to specify that folder here,
# though, because we "inherit" it by linking against a libsgfc++ library target
# below. Reason: The target_link_libraries statement is also a dependency
# declaration that causes CMake to add all PUBLIC include directories of the
# dependency target to our own target.
target_include_directories (
  ${EXAMPLE_EXECUTABLE_TARGET_NAME}
  # The examples treat libsgfc++ itself as a third-party library, so the next
  # include directory is required to find the public interface headers.
  PRIVATE ../include
)

# Examples use only public symbols, so we don't care which library we link
# against.
target_link_libraries (
  ${EXAMPLE_EXECUTABLE_TARGET_NAME}
  ${LINK_LIBRARY_TARGET_NAME}
)

# On some platforms iconv is provided by a dedicated library that must be
# explicitly linked against.
if ( ${ICONV_NEEDS_LINKING} )
  target_link_libraries (
    ${EXAMPLE_EXECUTABLE_TARGET_NAME}
    ${ICONV_LIBRARY}
  )
endif()

# Define additional compile options.
# - EXPORT_HEADER_STATIC_DEFINE_MACRO_NAME macro: The example executable target
#   must define this macro to be able to link against the static library or
#   static library framework
# - COMPILE_OPTION_C_FUNCTIONS_MAY_THROW_EXCEPTIONS: Tell the compiler that
#   C functions may throw exceptions. See main CMake config file for details.
target_compile_options (
  ${EXAMPLE_EXECUTABLE_TARGET_NAME}
  PUBLIC
  -D${EXPORT_HEADER_STATIC_DEFINE_MACRO_NAME}
  ${COMPILE_OPTION_C_FUNCTIONS_MAY_THROW_EXCEPTIONS}
)
