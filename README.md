libarg3
=======

a c++11 utility library.  Its my toolkit for anything c++11.

Submodules
==========

After cloning run two commands to initialize submodules:

git submodule init
git submodule update

Building
========

Requires [autotools](http://en.wikipedia.org/wiki/GNU_build_system).

```bash
./configure --prefix=/usr/local

make
```

Coding Style
============

- class/struct/method names are all lower case with underscores separating words
- non public members are camel case with and underscore at end of the name
- macros, enums and constants are all upper case with underscores seperating words
- braces on a new line

Requirements
============

*compiler*
You need a c++11 compiler.  I use [http://clang.llvm.org](clang++) on OSX. You need to pass '-std=c++11' and '-stdlib=libc++' options.

*libraries*
- [https://github.com/json-c/json-c](libjson-c)
- [http://curl.haxx.se/libcurl/](libcurl)
- [http://www.sqlite.org](sqlite3)
- [http://www.mysql.com](mysql)

all of the above libraries are available on OSX with [http://mxcl.github.io/homebrew/](Homebrew)
