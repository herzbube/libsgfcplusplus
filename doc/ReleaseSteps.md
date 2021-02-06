# Release steps

This document lists the steps needed to make a project release.

## Before the release

Things that need to be done before the actual release can take place:

- Create a release branch. All remaining work will be done in this branch. Command: `git checkout -b release-0.1.0 develop`
- Run Xcode's analyze tool and fix all problems that are reported (except those reported for SGFC source code).
- Run a CI build and fix all errors (hopefully none) and warnings that are reported on all platforms.
- Make sure that the issues in the bugtracker are up to date
- If SGFC has been updated
  - Make sure that the version number in `SgfcConstants::SgfcVersion` is up to date.
  - Make sure that the license information in `README.md` and in the `NOTICE` file is up to date.
  - Make sure to read the relevant release notes.
- Make sure that no debugging stuff has been forgotten in the code (e.g. search for "xxx")
- Update `ChangeLog.md`
  - The main source for this are the issues on the bug tracker.
  - The git commit log may also have useful information.
- Make sure that the version number is up to date in the following places:
  - `SgfcConstants::LibraryVersion`
  - `CMakeLists.txt` (the main file in the project root)
- Make sure that the copyright year is up to date in the following files (e.g.
  2020-2021 instead of 2020):
  - `NOTICE`
  - All source files that were touched since the last release. For instance, to list all files that were touched since the release 0.1 and were not updated to the current year 2021: `git diff --name-only 0.1 | egrep "^(example|include|src|test)" | sort | uniq | xargs grep "// Copyright" 2>/dev/null | grep -v 2021 | cut -d":" -f1`
- Remove the build directory to make sure that subsequent test and distribution builds are clean: `rm -rf build`
- Commit final changes (check with `git status` that nothing was forgotten).

## Create artifacts

### Create an archive

GitHub can generate a .zip file on demand from any commit in the repository history. It therefore does not make sense to upload a tar ball and waste space.

### Generate and publish API documentation

Step-by-step instructions to generate and publish the API documentation.

```
cd build

# Cleanup from a previous build
rm -rf doc/html

# Regenerate docs from scratch
cmake --build . --target libsgfcplusplus-doc
git checkout gh-pages

# Remove documentation from previous release
rm -rf ../api-docs

# Add documentation from new release
cp -Rp doc/html ../api-docs

git add ../api-docs
git commit -m "add API docs for version 0.1"
```

## Make the release

- Merge all changes in the release branch into `develop`
  - `git checkout develop`
  - `git merge release-0.1.0`
- Merge all changes in the release branch into `master`
  - `git checkout master`
  - `git merge develop`
- Tag and sign the release
  - `git tag -s -m "tagging release x.y" x.y <commit hash>`
- Update the GitHub repository
  - `git push`
  - `git push --tags`
- Remove the release branch, both locally and, if it was pushed, on GitHub
- Close tickets that are not yet closed in the issue tracker, then close the milestone
- Create a new release on GitHub that references the git tag. Copy ChangeLog content into the release description.