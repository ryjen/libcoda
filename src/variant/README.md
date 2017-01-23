variant
=======
[![Build Status](http://img.shields.io/travis/ryjen/variant/master.svg)](https://travis-ci.org/ryjen/variant)
[![Coverage Status](https://img.shields.io/coveralls/ryjen/variant/master.svg)](https://coveralls.io/github/ryjen/variant?branch=master)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://ryjen.mit-license.org)

A c++11 utility class for storing arbitrary variables with automatic type conversion.  Usefull for things like database or configuration values.

----

After cloning run the following command to initialize submodules:

```bash
git submodule update --init --recursive
```

Building
--------

you can use [cmake](https://cmake.org) to generate for the build system of your choice.

```bash
mkdir debug; cd debug;
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
make test
```

options supported are:

	-DCODE_COVERAGE=ON   :   enable code coverage using lcov
	-DMEMORY_CHECK=ON    :   enable valgrind memory checking on tests

examples
--------

```c++
variant v = "1234.1234"; // assign a string

assert(v == 1234); // yep can convert to int

assert(v == 1234.1234); // yep can convert to double

assert(v == true); // yep can convert to bool

v = 1234.1234; // assign a double

assert(v == 1234ULL); // yep can convert to an unsigned long long

assert(v == "1234.1234"); // yep its a string

v = "abscdef"; // assign a non number string

v.to_int(0); // will return 0 on error

v.to_double(); // will throw a conversion exception without a default parameter

```
