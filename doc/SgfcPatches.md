# SGFC Patches

libsgfc++ applies a number of patches to the original SGFC source code. This document lists all of the patches, outlines **what** changes that are made in each patch and provides an explanation **why** the changes are made.

**Note:** The patches are incremental. The patch files have a numeric prefix that makes it easy to apply them in the correct order.

## How to apply the patches

The patches were created with `git diff`. To apply them use `git apply`. The following shell script snippet applies the patches in the correct order:

```
cd sgfc
for PATCH_FILE in ../patch/*; do
  git apply "$PATCH_FILE"
done
```

## Patches 001-011

These patches were removed because a newer version of SGFC made them obsolete.

## 012-fix-sgfc-version-in-ap-property.patch

SGFC version 2.1 writes version 2.0 into the AP property when it saves an SGF file.

This patch fixes the hardcoded string in `save.c` to use the correct version.

The issue has been reported [upstream here](https://bitbucket.org/arnoh/sgfc/issues/10).

## 013-fix-sgfc-version-in-test-files.patch

This patch fixes the test files that incorrectly expect "AP[SGFC:2.0]" to expect "AP[SGFC:2.1]" instead.

This patch is not necessary for building libsgfc++. It exists to allow executing the SGFC unit tests.
