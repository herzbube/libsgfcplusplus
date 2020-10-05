#!/bin/bash

SCRIPT_NAME="$(basename "$0")"
SCRIPT_FOLDER="$(dirname "$0")"
case "$SCRIPT_FOLDER" in
  /*) BASE_FOLDER="$SCRIPT_FOLDER/.." ;;
  *) BASE_FOLDER="$(pwd)/$SCRIPT_FOLDER/.." ;;
esac
SGFC_FOLDER="$BASE_FOLDER/sgfc"
PATCH_FOLDER="$BASE_FOLDER/patch"
BUILD_FOLDER="$BASE_FOLDER/build"
PATCHH_MARKER_FILENAME="libsgfc++.patches.were.applied"

echo "------------------------------------------------------------"
echo "Patching SGFC"
echo "------------------------------------------------------------"
cd "$SGFC_FOLDER"
if test -f "$PATCHH_MARKER_FILENAME"; then
  echo "Patches were already applied"
else
  for PATCH_FILE in $PATCH_FOLDER/*; do
    git apply "$PATCH_FILE"
    if test $? -ne 0; then
      echo "Applying patch file $(basename $PATCH_FILE) failed."
      exit 1
    fi
    touch "$PATCHH_MARKER_FILENAME"
  done
  echo "Patching successful."
fi
cd "$BASE_FOLDER"

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
