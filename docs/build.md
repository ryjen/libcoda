# Building Seamwork

## Current transition boundary

The repository is being re-chartered from `libcoda` into Seamwork.

C++23 is the baseline for new and materially refined Seamwork code. The aggregate/root `coda` target is the first active C++23 boundary.

Legacy submodule targets retain their own target-local language requirements while they are inventoried and migrated. This is intentional: Seamwork does not perform syntax-only C++23 conversions merely to raise a version number.

## Prerequisites

- CMake 3.21 or newer
- A C++23-capable compiler for the aggregate/new Seamwork boundary
- Git submodules initialized recursively during the transition
- Component dependencies required by the enabled legacy modules

The checked-in Nix development shell currently provides GCC 14.

Initialize submodules after cloning:

```bash
git submodule update --init --recursive
```

## Preset-based builds

Development aggregate build with shared tests enabled:

```bash
cmake --preset dev
cmake --build --preset dev
ctest --preset dev
```

Release aggregate build with shared tests disabled where supported:

```bash
cmake --preset release
cmake --build --preset release
```

## Build options

Current migration-era project-level options are:

| Option | Default | Purpose |
| --- | --- | --- |
| `CODA_BUILD_TESTS` | `ON` | Configure root tests and migrated component test trees. |
| `CODA_ENABLE_COVERAGE` | `OFF` | Enable the existing coverage integration. |
| `CODA_ENABLE_MEMCHECK` | `OFF` | Enable the existing Valgrind memcheck integration. |
| `CODA_ENABLE_PROFILING` | `OFF` | Enable the existing Valgrind profiling integration. |

The `CODA_*` names are retained temporarily to avoid mixing the project re-charter with a broad compatibility break. Active new surfaces will introduce `SEAMWORK_*` naming deliberately; compatibility aliases can then be evaluated per surface.

`ENABLE_COVERAGE`, `ENABLE_MEMCHECK`, and `ENABLE_PROFILING` remain legacy aliases.

## Language-standard ownership

The project deliberately avoids a directory-global `CMAKE_CXX_STANDARD`.

Each compiled target owns its language requirement through `target_compile_features`.

The aggregate/root target now owns:

```cmake
target_compile_features(coda PUBLIC cxx_std_23)
```

and disables compiler-specific language extensions for that target.

Legacy component targets may still own `cxx_std_17`. When a component is promoted into an active Seamwork study or component, its language contract should be migrated to C++23 as part of the actual design work.

This preserves the useful target-local CMake modernization already completed while making the new project baseline explicit.

## Modernization boundary

The root `LIBRARY_VERSION` definition remains target-local rather than injected through global flags.

`CODA_BUILD_TESTS` governs the current aggregate and migrated component test trees. Existing issue #5 tracks remaining test-system convergence, including legacy Bandit setup and build-time test dependency behavior.

Some analysis paths still use legacy shared CMake helpers, particularly coverage instrumentation. Those remain migration debt; they should not be copied into new Seamwork targets.

The existing aggregate CI remains a compatibility/integration gate while component disposition is reviewed.

## Intended direction

As legacy components are classified and absorbed, the build should converge toward:

- one primary Seamwork repository;
- C++23 target-local requirements;
- small project-owned CMake helpers;
- flake-driven CI/dev environments;
- explicit study/example/component targets;
- no ambient compiler or dependency state;
- deterministic tests without external services by default.

See [the migration plan](migration/seamwork-rebrand.md) for sequencing.
