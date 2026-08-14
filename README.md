libcoda
=====

[![Build Status](http://img.shields.io/travis/ryjen/libcoda.svg)](https://travis-ci.org/ryjen/libcoda)
[![Coverage Status](https://coveralls.io/repos/ryjen/libcoda/badge.svg?branch=master&service=github)](https://coveralls.io/github/ryjen/libcoda?branch=master)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://ryjen.mit-license.org)

a c++17 utility library.  Its my toolkit for anything c++17.

Submodules
==========

After cloning, initialize the Git submodules:

```bash
git submodule update --recursive --init
```

Building
========

The preferred CMake workflow uses the checked-in presets:

```bash
cmake --preset dev
cmake --build --preset dev
ctest --preset dev
```

For a release aggregate build with the root test target disabled:

```bash
cmake --preset release
cmake --build --preset release
```

The legacy `prep` workflow remains available where configured:

```bash
prep            # install dependencies only
prep build      # build project
prep install    # install project to kitchen
```

See [`docs/build.md`](docs/build.md) for build options, compatibility aliases, and the current CMake modernization boundary.

Requirements
============

*compiler*

You need a c++17 compiler.

*libraries*
- [libjson-c](https://github.com/json-c/json-c)
- [libcurl](http://curl.haxx.se/libcurl/)
- [sqlite3](http://www.sqlite.org)
- [mysql](http://www.mysql.com)
- postgres
