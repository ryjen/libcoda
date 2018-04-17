libcoda
=====

[![Build Status](http://img.shields.io/travis/ryjen/libcoda.svg)](https://travis-ci.org/ryjen/libcoda)
[![Coverage Status](https://coveralls.io/repos/ryjen/libcoda/badge.svg?branch=master&service=github)](https://coveralls.io/github/ryjen/libcoda?branch=master)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://ryjen.mit-license.org)

a c++17 utility library.  Its my toolkit for anything c++17.

Submodules
==========

After cloning run two commands to initialize submodules:

```bash
git submodule update --recursive --init
```

Building
========

This project now builds with [prep](https://github.com/ryjen/prep).

```bash
prep            # install dependencies only
prep build      # build project
prep install    # install project to kitchen
```

You can use [cmake](https://cmake.org) to generate for the build system of your choice.

```bash
mkdir debug; cd debug
cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON -DENABLE_MEMCHECK=ON ..
make
make test
```

options supported are:

		-DENABLE_COVERAGE=ON   :   enable code coverage using lcov
		-DENABLE_MEMCHECK=ON   :   enable valgrind memory checking on tests

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
