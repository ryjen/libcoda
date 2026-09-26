# Seamwork

[![CI](https://github.com/ryjen/libcoda/actions/workflows/ci.yml/badge.svg?branch=development)](https://github.com/ryjen/libcoda/actions/workflows/ci.yml)
[![License](https://img.shields.io/:license-mit-blue.svg)](http://ryjen.mit-license.org)

**Modern C++23 through interface and architecture refinement.**

Seamwork is a practical laboratory for exploring how modern C++ can produce interfaces that are expressive, maintainable, difficult to misuse, and explicit about ownership, lifetime, cost, and failure.

The project began as `libcoda`, a C++ utility toolkit used to learn modern C++ and experiment with cleaner APIs. The re-charter keeps that interest in interface quality while dropping the goal of being a general-purpose utility library.

Reusable components may emerge from the work, but the primary artifacts are the design studies, practical consumers, tests, measurements, and documented trade-offs that justify them.

## Project direction

Seamwork focuses on:

- interface refinement;
- C++23 language and standard-library facilities used deliberately;
- clean architectural boundaries without ceremony;
- pragmatic SOLID principles;
- explicit ownership, lifetime, error, and resource semantics;
- realistic examples rather than syntax-only demonstrations;
- testing, static analysis, sanitizers, fuzzing, and benchmarks as design evidence;
- comparing alternatives instead of assuming one C++ idiom is universally best.

See:

- [Project charter](docs/charter.md)
- [Design principles](docs/principles.md)
- [Refinement workflow](docs/refinement-workflow.md)
- [Re-charter and migration plan](docs/migration/seamwork-rebrand.md)

## Architecture

The existing architecture work remains useful as migration guidance:

- [System context](docs/architecture/0001-system-context.md)
- [Layered architecture and SOLID guidance](docs/architecture/0002-layered-architecture.md)
- [Error handling policy](docs/architecture/0003-error-handling.md)
- [Dependency policy](docs/architecture/0004-dependency-policy.md)
- [ADR 0002: transition toward a single Seamwork repository](docs/adr/0002-seamwork-topology.md)

Legacy `libcoda` components are migration inputs, not automatically endorsed Seamwork components. Each will be reviewed as KEEP, REWORK, ABSORB, ARCHIVE, or REMOVE before becoming part of the long-term structure.

## C++23 baseline

C++23 is the baseline for new and materially refined Seamwork code.

The root aggregate target now requires C++23. Legacy submodule targets currently retain their own language requirements while they are classified and migrated; changing their standard without a design purpose would be a syntax-only modernization and is intentionally not the migration strategy.

The rule is:

> use the simplest mechanism that preserves the desired semantics, and use C++23 where it makes the interface or architecture meaningfully better.

## Practical consumers

The original command-line Yahtzee application is intended to become the first reference consumer. It provides useful seams around domain rules, randomness, input/output, formatting, persistence, and testing without requiring a large application.

A typical Seamwork study should move through:

```text
problem
  -> straightforward implementation
  -> identify friction / coupling / ambiguity
  -> compare alternatives
  -> refine with appropriate C++23 mechanisms
  -> test / analyze / benchmark
  -> validate with a real consumer
  -> optionally promote to a reusable component
```

Promotion is optional. Demonstrating why an abstraction should not exist is a valid result.

## Security

The existing security work remains part of the evidence base:

- [Project threat model and release-hardening checklist](docs/security/threat-model.md)
- [Legacy `libcoda-net` threat model](docs/security/libcoda-net.md)
- [Legacy `libcoda-db` threat model](docs/security/libcoda-db.md)
- [Legacy `libcoda-format` threat model](docs/security/libcoda-format.md)

Security is treated as part of interface design: trust boundaries, input validation, resource bounds, error behavior, and secret handling should be explicit in the contract.

## Building

Initialize the existing migration-era submodules:

```bash
git submodule update --recursive --init
```

Use the checked-in presets:

```bash
cmake --preset dev
cmake --build --preset dev
ctest --preset dev
```

For a release aggregate build:

```bash
cmake --preset release
cmake --build --preset release
```

See [`docs/build.md`](docs/build.md) for the current build boundary and transition notes.

## Toolchain

The active Seamwork boundary requires a C++23-capable compiler. The checked-in Nix development shell currently uses GCC 14.

Legacy components may still declare C++17 until they are actively migrated as studies/components. That is transitional state, not the target standard.

## Lineage

Seamwork preserves the Git history and lessons of `libcoda`.

The eventual repository rename will happen after the active code surface reflects the new purpose. This avoids turning a repository rename into an implicit claim that every legacy utility is already part of the new design.
