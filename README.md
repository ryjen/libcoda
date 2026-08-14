libcoda
=====

[![CI](https://github.com/ryjen/libcoda/actions/workflows/ci.yml/badge.svg?branch=development)](https://github.com/ryjen/libcoda/actions/workflows/ci.yml)
[![Coverage Status](https://coveralls.io/repos/ryjen/libcoda/badge.svg?branch=master&service=github)](https://coveralls.io/github/ryjen/libcoda?branch=master)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://ryjen.mit-license.org)

a c++17 utility library.  Its my toolkit for anything c++17.

Architecture
============

Modernization follows explicit layered-dependency, error-handling, and dependency-management rules:

- [System context](docs/architecture/0001-system-context.md)
- [Layered architecture and SOLID guidance](docs/architecture/0002-layered-architecture.md)
- [Error handling policy](docs/architecture/0003-error-handling.md)
- [Dependency policy](docs/architecture/0004-dependency-policy.md)
- [ADR 0001: retain component repositories and submodules during modernization](docs/adr/0001-submodules-vs-monorepo.md)

The architecture documents describe target constraints for modernization; they do not imply every legacy component already conforms.

Security
========

Security modernization is driven by explicit trust boundaries and component threat models:

- [Project threat model and release-hardening checklist](docs/security/threat-model.md)
- [`libcoda-net` threat model](docs/security/libcoda-net.md)
- [`libcoda-db` threat model](docs/security/libcoda-db.md)
- [`libcoda-format` threat model](docs/security/libcoda-format.md)

The threat models record current findings as remediation inputs; documenting a legacy behavior does not make it an accepted security default.

Submodules
==========

After cloning, initialize the Git submodules:

```bash
git submodule update --recursive --init
```

Building
========

The preferred CMake workflow uses the checked-in presets:

```bash
cmake --preset dev
cmake --build --preset dev
ctest --preset dev
```

For a release aggregate build with shared tests disabled where supported:

```bash
cmake --preset release
cmake --build --preset release
```

The legacy `prep` workflow remains available where configured:

```bash
prep            # install dependencies only
prep build      # build project
prep install    # install project to kitchen
```

See [`docs/build.md`](docs/build.md) for build options, compatibility aliases, and the current CMake modernization boundary.

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
