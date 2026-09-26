# 0001 — System context

## Status

Accepted as Seamwork transition guidance.

## Purpose

Seamwork is a practical C++23 interface and architecture refinement laboratory.

It exists to study how C++ interfaces and system boundaries can become easier to use, harder to misuse, and easier to reason about while keeping ownership, lifetime, allocation, blocking, failure, concurrency, and other important consequences visible.

The repository currently contains the historical `libcoda` aggregate and utility components. Those are migration inputs and practical source material, not the long-term product definition.

## Responsibilities

The primary repository should converge on four responsibilities:

1. host practical C++23 design studies and preserve their reasoning;
2. host realistic example applications that exercise the studied seams;
3. promote only justified abstractions into reusable components;
4. provide common build, testing, security, analysis, and benchmarking infrastructure.

It is not intended to become a framework or a replacement for the standard library and mature C++ ecosystems.

## Current transition topology

The current codebase is still a hybrid multi-repository system:

- the historical `libcoda` root owns aggregate build/integration policy and in-tree utilities;
- `libcoda-format`, `libcoda-db`, `libcoda-net`, dice, and other components are consumed through Git submodules;
- the shared `cmake` repository provides migration-era helpers;
- architecture, testing, fuzzing, and security modernization already exists across several components.

ADR 0002 changes the target topology: Seamwork will move toward one primary repository while legacy components are classified and either absorbed, reworked, archived, or removed.

Submodules therefore remain a temporary migration mechanism rather than a permanent architectural principle.

## Intended consumers

The primary consumers are now:

- maintainers/readers studying practical modern C++ design alternatives;
- example applications validating interface ergonomics and architecture;
- reusable components that survive the project's promotion criteria;
- CI/fuzz/security/benchmark tooling producing evidence about design claims.

A generic external consumer base is not assumed merely because legacy code was once packaged as a library.

## Architectural drivers

Seamwork prioritizes:

1. **interface clarity** — call sites should communicate intent and constrain misuse;
2. **visible semantics** — ownership, lifetime, cost, I/O, concurrency, and failure should remain understandable;
3. **C++23 as a design tool** — concepts, ranges, `std::expected`, views, formatting, constexpr facilities, and other modern features are used when they improve the contract;
4. **dependency direction** — policy and pure behavior should not acquire concrete infrastructure dependencies without reason;
5. **pragmatic architecture** — SOLID and Clean Architecture guide coupling but do not mandate layers or interfaces;
6. **practical evidence** — real consumers, tests, fuzzing, analysis, and measurements support design decisions;
7. **security** — trust boundaries and unsafe assumptions are part of interface design;
8. **refinement over reinvention** — mature existing libraries are preferred when they already provide the right contract.

## Maturity

The repository is in a re-charter/migration phase.

Useful modernization has already established target-local CMake behavior, deterministic test layers, security models, fuzzing, and analysis patterns. That work is retained.

Known transitional areas include:

- legacy C++17 component contracts;
- multi-repository/submodule topology;
- `coda` namespace/target/option names;
- generic utility components without a current Seamwork study;
- service-coupled database/network surfaces;
- legacy shared CMake helpers and testing infrastructure.

These are migration debt, not precedent for new Seamwork code.

## Non-goals

Seamwork does not require:

- preserving every historical utility as a library;
- hiding standard-library value types behind project wrappers;
- using a C++23 feature when a simpler mechanism is clearer;
- introducing an interface merely to satisfy dependency inversion terminology;
- creating a reusable component from every study;
- preserving accidental legacy API/ABI behavior when it prevents useful refinement.

## Change rule

A meaningful refinement should identify the problem, compare relevant alternatives, and capture evidence appropriate to the claim.

When a change crosses a public API, dependency direction, ownership/lifetime contract, security boundary, or significant performance characteristic, document the trade-off through a study, QART note, or ADR as appropriate.

See the [charter](../charter.md), [principles](../principles.md), and [refinement workflow](../refinement-workflow.md).
