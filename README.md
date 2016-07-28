librj
=====

[![Build Status](http://img.shields.io/travis/ryjen/librj.svg)](https://travis-ci.org/ryjen/librj)
[![Coverage Status](https://coveralls.io/repos/ryjen/librj/badge.svg?branch=master&service=github)](https://coveralls.io/github/ryjen/librj?branch=master)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://ryjen.mit-license.org)

a c++11 utility library.  Its my toolkit for anything c++11.

Submodules
==========

After cloning run two commands to initialize submodules:

```bash
git submodule init
git submodule update
```

Building
========

You can use [cmake](https://cmake.org) to generate for the build system of your choice.

```bash
mkdir debug; cd debug
cmake -DCMAKE_BUILD_TYPE=Debug -DCODE_COVERAGE=ON -DMEMORY_CHECK=ON ..
make
make test
```

options supported are:

		-DCODE_COVERAGE=ON   :   enable code coverage using lcov
		-DMEMORY_CHECK=ON    :   enable valgrind memory checking on tests

Requirements
============

*compiler*
You need a c++11 compiler.  

*libraries*
- [https://github.com/json-c/json-c](libjson-c)
- [http://curl.haxx.se/libcurl/](libcurl)
- [http://www.sqlite.org](sqlite3)
- [http://www.mysql.com](mysql)
