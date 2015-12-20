libarg3
=======

[![Build Status](http://img.shields.io/travis/deadcoda/libarg3.svg)](https://travis-ci.org/deadcoda/libarg3)
[![Coverage Status](https://coveralls.io/repos/deadcoda/libarg3/badge.svg?branch=master&service=github)](https://coveralls.io/github/deadcoda/libarg3?branch=master)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://deadcoda.mit-license.org)
[![Codacy Badge](https://api.codacy.com/project/badge/grade/f39c12a30e1141eaa8ae9aca5f4fe8c9)](https://www.codacy.com/app/c0der78/libarg3)

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

for homebrew you can add the install prefix:

```bash
mkdir release; cd release
cmake $(brew diy --version=0.5.0) -DCMAKE_BUILD_TYPE=Release ..
make
make install
brew link libarg3
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
