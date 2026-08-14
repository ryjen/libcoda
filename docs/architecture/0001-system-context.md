# 0001 — System context

## Status

Accepted as modernization guidance.

## Purpose

`libcoda` is an aggregate C++17 toolkit and integration repository. It assembles a set of utility libraries, including database, networking, formatting, logging, math, string, terminal, threading, and general utility components.

The aggregate repository has two responsibilities:

1. provide a reproducible integration/build surface for the component libraries;
2. define project-wide architecture, dependency, testing, and security policy that component repositories can adopt incrementally.

It is not intended to become a framework that forces unrelated utility domains behind one abstraction hierarchy.

## Current topology

The codebase is a hybrid multi-repository system:

- `libcoda` owns the aggregate build, integration CI, in-tree utility components, and project-wide policy;
- `libcoda-format`, `libcoda-db`, `libcoda-net`, and other independently versioned components are consumed through Git submodules;
- the shared `cmake` repository provides legacy CMake helpers used by several components;
- some component CMake and test conventions remain independent and are being converged incrementally.

The submodule boundary is therefore both a source-control boundary and a release/integration boundary. A change to a component is not part of an aggregate release until the aggregate gitlink is advanced and the recursive integration build passes.

## Intended consumers

The primary consumers are:

- C++ applications that use one or more libcoda component libraries;
- the aggregate libcoda build used to validate compatibility across components;
- maintainers extending or modernizing individual components;
- CI/fuzz/security tooling that needs deterministic component boundaries.

## Architectural drivers

Modernization prioritizes:

1. **correctness and explicit contracts** — parsing, state, ownership, error, and lifecycle behavior should be testable and documented;
2. **dependency direction** — domain and parsing logic should not depend on concrete database, socket, TLS, or platform adapters;
3. **deterministic builds** — normal builds should not require network dependency downloads or external services;
4. **security** — untrusted format strings, URIs, network data, SQL inputs, and credentials cross explicit trust boundaries;
5. **testability** — pure logic should be testable without sockets or database services, with SQLite/fakes used for deterministic integration where appropriate;
6. **incremental compatibility** — modernization should avoid unnecessary public API or ABI breakage and should isolate deliberate compatibility changes.

## Maturity

The aggregate build and several components are in active modernization. The architecture in this document describes the intended dependency rules; it does not imply every existing component already conforms.

Known transitional areas include:

- legacy global compiler settings and CMake helper behavior;
- component-specific test setup;
- service-coupled DB/network tests;
- concrete adapter details leaking into higher-level code;
- public-header and package-layout inconsistencies;
- legacy dependencies retained for compatibility.

These should be treated as migration debt, not precedent for new code.

## Non-goals

The modernization effort does not require:

- converting every component into a single monolithic library;
- introducing interfaces where there is only one stable implementation and no testability benefit;
- hiding standard-library value types behind project-specific wrappers;
- replacing working algorithms solely to use newer language syntax;
- moving all repositories into a monorepo before component boundaries are understood;
- preserving accidental behavior caused by undefined, unsafe, or undocumented implementation details.

## Change rule

When a modernization change crosses a public API, component boundary, dependency direction, ownership/lifetime contract, or security boundary, the change should be justified by tests and, when durable, captured in architecture documentation or an ADR.
