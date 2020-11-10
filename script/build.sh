#!/bin/bash

SCRIPT_NAME="$(basename "$0")"
SCRIPT_FOLDER="$(dirname "$0")"
case "$SCRIPT_FOLDER" in
  /*) BASE_FOLDER="$SCRIPT_FOLDER/.." ;;
  *) BASE_FOLDER="$(pwd)/$SCRIPT_FOLDER/.." ;;
esac
SGFC_FOLDER="$BASE_FOLDER/sgfc"
BUILD_FOLDER="$BASE_FOLDER/build"

echo ""
echo "------------------------------------------------------------"
echo "Running CMake to create build system"
echo "------------------------------------------------------------"
if test ! -d "$BUILD_FOLDER"; then
  echo "Creating build folder ..."
  mkdir "$BUILD_FOLDER"
  if test $? -ne 0; then
    echo "Failed to create build folder $BUILD_FOLDER"
    exit 1
  fi
  echo "Build folder created successfully."
fi
cd "$BUILD_FOLDER"

echo "Creating build system ..."
cmake -DCMAKE_BUILD_TYPE=Release ..
if test $? -ne 0; then
  echo "Failed to create build system"
  exit 1
fi
echo "Build system created successfully."
cd "$BASE_FOLDER"

echo ""
echo "------------------------------------------------------------"
echo "Running CMake to build the project"
echo "------------------------------------------------------------"
cd "$BUILD_FOLDER"
cmake --build .
if test $? -ne 0; then
  echo "Failed to build the project"
  exit 1
fi
echo "Project build successful."
cd "$BASE_FOLDER"

echo ""
echo "------------------------------------------------------------"
echo "Executing unit tests"
echo "------------------------------------------------------------"
cd "$BUILD_FOLDER"
./test/libsgfcplusplus-test
if test $? -ne 0; then
  echo "Some unit tests failed"
  exit 1
fi
echo "Unit tests ran successfully."
cd "$BASE_FOLDER"

echo ""
echo ------------------------------------------------------------
echo "You are now ready to install the build results with something like"
echo "  cmake --install . --prefix install"
echo "You may also want to have a look at the sample code in the \"example\" folder."
echo ------------------------------------------------------------
