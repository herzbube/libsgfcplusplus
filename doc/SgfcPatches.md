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

## Patches 001-014

These patches were removed because a newer version of SGFC made them obsolete.
