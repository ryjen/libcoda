[dice-engine](http://c0der78.github.com/dice-engine)
===========

A c++11 library for working with dice.  Engines for different dice games (Yahtzee, Liar's Dice, Backgammon)

See the [documentation](http://c0der78.github.com/dice-engine/docs)

requirements
============

- c++11 for compiling

optional
========

- [http://igloo-testing.org](Igloo) Unit Testing
- requires [rake](http://rake.rubyforge.org) (ruby) for building
- [HeaderDoc](http://developer.apple.com/library/mac/#documentation/developertools/Conceptual/HeaderDoc/intro/intro.html) (Apple) for creating documentation
- [astyle](http://astyle.sourceforge.net) for formatting source code

compilation
===========

Just run 'rake' to compile and run unit tests

other options:

- *rake debug*: makes a debug build
- *rake release*: makes a release build
- *rake test*: runs the unit tests
- *rake docs*: builds documents
- *rake format*: formats source code
- *rake clean*: cleans build files
- *rake install*: installs library to system
