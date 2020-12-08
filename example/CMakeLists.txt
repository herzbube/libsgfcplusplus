include( ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES_LIST_FILE_NAME} )
if ( NOT DEFINED SOURCES )
  message ( FATAL_ERROR "List of source files not defined by ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES_LIST_FILE_NAME}" )
endif()

# Here we define the example executable target.
add_executable (
  ${EXAMPLE_EXECUTABLE_TARGET_NAME}
  ${SOURCES}
)

target_include_directories (
  ${EXAMPLE_EXECUTABLE_TARGET_NAME}
  # The examples treat libsgfc++ itself as a third-party library, so the next
  # include directory is required to find the public interface headers.
  PRIVATE ../include
)

# We link against the shared library. We could also link against the static
# library, but this would be a bit slower.
target_link_libraries (
  ${EXAMPLE_EXECUTABLE_TARGET_NAME}
  ${LINK_LIBRARY_TARGET_NAME}
)

# On some platforms iconv is provided by a dedicated library that must be
# explicitly linked against.
if ( ${LINK_ICONV} )
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
