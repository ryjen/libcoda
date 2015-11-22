libarg3
=======

[![Build Status](https://travis-ci.org/c0der78/libarg3.svg?branch=master)](https://travis-ci.org/c0der78/libarg3)

a c++11 utility library.  Its my toolkit for anything c++11.

[View Testing Code Coverage](http://htmlpreview.github.com/?https://github.com/c0der78/libarg3/blob/master/coverage/index.html)

Submodules
==========

After cloning run two commands to initialize submodules:

```bash
git submodule init
git submodule update
```

Building
========

I use [autotools](http://en.wikipedia.org/wiki/GNU_build_system).

```bash
./configure --prefix=/usr/local
make
```

for homebrew you build like this:

```bash
./configure $(brew diy --version=0.5.0 libarg3)
make install
brew link libarg3
```

instead.

Requirements
============

*compiler*
You need a c++11 compiler.  

*libraries*
- [https://github.com/json-c/json-c](libjson-c)
- [http://curl.haxx.se/libcurl/](libcurl)
- [http://www.sqlite.org](sqlite3)
- [http://www.mysql.com](mysql)

