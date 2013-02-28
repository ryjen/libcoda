libarg3
=======

a c++11 utility library

requirements
============

- a c++11 compiler (I use clang++ on OSX)

optional
========

- [http://igloo-testing.org](Igloo) Unit Testing
- [premake](http://industriousone.com/premake) for building
- [HeaderDoc](http://developer.apple.com/library/mac/#documentation/developertools/Conceptual/HeaderDoc/intro/intro.html) (Apple) for creating documentation
- [astyle](http://astyle.sourceforge.net) for formatting source code

compilation
===========

To install premake4 you can use [homebrew](http://mxcl.github.com/homebrew/) (brew install premake)

Just run 'premake4 --help' to get a list of build types

Typically I run 'premake4 gmake; make'

TODO
====

- ~~arg3::db::base_record should be able to determine its own schema given a table name~~
- more testing

licensing
=========

copyrighted under the Lesser GNU Public License
