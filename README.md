librj
=====

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/f39c12a30e1141eaa8ae9aca5f4fe8c9)](https://www.codacy.com/app/ryjen/libarg3?utm_source=github.com&utm_medium=referral&utm_content=ryjen/libryjen&utm_campaign=badger)
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
cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON -DENABLE_MEMCHECK=ON ..
make
make test
```

options supported are:

		-DENABLE_COVERAGE=ON   :   enable code coverage using lcov
		-DENABLE_MEMCHECK=ON    :   enable valgrind memory checking on tests

Requirements
============

*compiler*
You need a c++11 compiler.  

*libraries*
- [https://github.com/json-c/json-c](libjson-c)
- [http://curl.haxx.se/libcurl/](libcurl)
- [http://www.sqlite.org](sqlite3)
- [http://www.mysql.com](mysql)
