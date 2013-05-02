libarg3
=======

a c++11 utility library.  Its my toolkit for anything c++11.

requirements
============

*compiler*
You need a c++11 compiler.  I use [http://clang.llvm.org](clang++) on OSX. You need to pass '-std=c++11' and '-stdlib=libc++' options.

*libraries*
- [https://github.com/json-c/json-c](libjson)
- [http://curl.haxx.se/libcurl/](libcurl)
- [http://www.sqlite.org](sqlite3)

all of the above libraries are available on OSX with the fabulous [http://mxcl.github.io/homebrew/](Homebrew)

optional
========

- [http://igloo-testing.org](Igloo) Unit Testing (header only library)
- [premake](http://industriousone.com/premake) for building (available on hombrew)
- [HeaderDoc](http://developer.apple.com/library/mac/#documentation/developertools/Conceptual/HeaderDoc/intro/intro.html) (Apple) for creating documentation
- [astyle](http://astyle.sourceforge.net) for formatting source code

compilation
===========

Just run 'premake4 --help' to get a list of build options

Typically I run 'premake4 --shared gmake; make'

If you want to install the library use 'premake4 install /usr/local'.  I plan on making a homebrew formula when more mature.

licensing
=========

under the Lesser GNU Public License
