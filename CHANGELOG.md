<!-- SPDX-License-Identifier: CC0-1.0 -->
<!-- SPDX-FileCopyrightText: 2020 Lynn Kirby -->

# Changelog

## Unreleased

### Features
- Implemented cross-platform CMake build system.
- Support `gdef_GetHostName()` on Windows.

### Improvements
- Increased use of C99 constructs like new math functions and sized integers.

### Bug fixes
- Memory leak in `ucrypto_DeleteAES()`.
- `sspacings` was zero-ing out its result data structure incorrectly.
- Numerous instances of undefined behavior: lack of variable initialization,
  expressions that both evaluate and assign the same variable.

### BREAKING CHANGES

Note: these breaking changes are relative to TestU01 1.2.3.

- Package now requires a C99 compiler.
- Many function signatures and external variable types have changed because of
  the move to use standard C99 types.
