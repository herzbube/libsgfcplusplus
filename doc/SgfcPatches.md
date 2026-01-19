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

## Patches 001-010

These patches were removed because a newer version of SGFC made them obsolete.

## 011-save.c-fix-off-by-one-position-calculation.patch

This patch fixes a bug in the function `SaveBufferIO_putc` in `save.c`.

The function allocates additional memory when it finds that its current buffer is running out. When it sets the write position in the new buffer it miscalculates the position by one byte, causing one uninitialized byte with a random value in the middle of the buffer.

Original code:

    sfh->fh.memh.pos = new_buffer + sfh->fh.memh.buffer_size;

Patched code:

    sfh->fh.memh.pos = new_buffer + sfh->fh.memh.buffer_size - 1;

**Note:** The bug has been [reported upstream](https://bitbucket.org/arnoh/sgfc/issues/9). Once a fix has been integrated upstream this patch can be removed.
