<!-- SPDX-License-Identifier: CC0-1.0 -->
<!-- SPDX-FileCopyrightText: 2020 Lynn Kirby -->

# Lynn's TestU01 fork

[![License: GPL-3.0-or-later](https://img.shields.io/badge/license-GPL--3.0--or--later-blue?style=flat-square)](./COPYING.txt)
[![GitHub Workflow Status](https://img.shields.io/github/workflow/status/LynnKirby/TestU01/CI%20Build/master?style=flat-square)](https://github.com/LynnKirby/TestU01/actions)
[![REUSE compliant](https://img.shields.io/badge/REUSE-compliant-green?style=flat-square)](https://reuse.software/spec/)

**Warning: work in progress and undergoing rapid change.**

Fork of the [TestU01][] library created by Pierre L'Ecuyer and Richard Simard.
TestU01 provides a set of tools for the empirical statistical testing of uniform
random number generators.

[TestU01]: http://simul.iro.umontreal.ca/testu01/tu01.html

## Building

### Dependencies

- [**CMake 3.16+**](https://cmake.org). It's likely the project will build on
  earlier versions but that hasn't been tested.
- [**Ninja**](https://ninja-build.org/) *(optional)*. Recommended build
  generator for CMake. The instructions below assume you are using it.
- **C99 compiler**. Currently tested with:
    - Clang 9 (including `clang-cl`)
    - GCC 7
    - Visual C++ 2019 Version 16.4
- [**cmocka**](https://cmocka.org/) 1.1.5 *(optional)*. Used for testing. Will
  be downloaded and built automatically if `TESTU01_BUILD_THIRDPARTY` is `ON`.

### CMake options

- `TESTU01_ENABLE_WARNINGS`. Show or suppress build warnings.
  (Default: `ON` when this is the root CMake project)
- `TESTU01_ENABLE_TESTS`. Enable building and running tests.
  (Default: `ON` when this is the root CMake project)
- `TESTU01_BUILD_THIRDPARTY`. Download and build dependencies if they cannot be
  found locally. (Default: `ON`)

### Building the CMake project

```
git clone https://github.com/LynnKirby/TestU01
cd TestU01
mkdir build
cd build
cmake -GNinja ..
ninja
```

<!-- TODO: Building as CMake subproject -->
<!-- TODO: Installing TestU01 then using find_package(...) -->

## Elsewhere

###### Links of interest

- [TestU01 website][TestU01]
- [Pierre L'Ecuyer's homepage](http://www.iro.umontreal.ca/~lecuyer/)

###### Publications

- P. L'Ecuyer and R. Simard, *TestU01: A C Library for Empirical Testing of
  Random Number Generators*, ACM Transactions on Mathematical Software,
  Vol. 33, 4, article 22, 2007.
  [doi:10.1145/1268776.1268777](https://sci-hub.tw/10.1145/1268776.1268777)

## License

This project is provided under the GNU General Public License v3.0 or later,
with additional terms. See [`GPL-3.0-or-later.txt`][] and
[`LicenseRef-testu01.txt`][] under the [`LICENSES`][] directory for details.

Individual files may have their own licences. Refer to file comment headers and
the DEP-5 file in [`.reuse/dep5`][].

[`GPL-3.0-or-later.txt`]: ./LICENSES/GPL-3.0-or-later.txt
[`LicenseRef-testu01.txt`]: ./LICENSES/LicenseRef-testu01.txt
[`LICENSES`]: ./LICENSES
[`.reuse/dep5`]: ./.reuse/dep5
