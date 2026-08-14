# Building libcoda

## Prerequisites

- CMake 3.21 or newer
- A C++17 compiler
- Git submodules initialized recursively
- Component dependencies required by the enabled libcoda modules

Initialize submodules after cloning:

```bash
git submodule update --init --recursive
```

## Preset-based builds

The checked-in presets keep common development and release configurations reproducible without embedding machine-specific paths.

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

Current project-level options are:

| Option | Default | Purpose |
| --- | --- | --- |
| `CODA_BUILD_TESTS` | `ON` | Configure the root tests and migrated component test trees. |
| `CODA_ENABLE_COVERAGE` | `OFF` | Enable the existing coverage integration. |
| `CODA_ENABLE_MEMCHECK` | `OFF` | Enable the existing Valgrind memcheck integration. |
| `CODA_ENABLE_PROFILING` | `OFF` | Enable the existing Valgrind profiling integration. |

`ENABLE_COVERAGE`, `ENABLE_MEMCHECK`, and `ENABLE_PROFILING` remain accepted as compatibility aliases while downstream CMake is migrated. New scripts should use the `CODA_*` names.

## Modernization boundary

The aggregate no longer sets a project-wide C++ standard. Each compiled library target in the current aggregate graph declares its own `target_compile_features(... cxx_std_17)` requirement, including the migrated format, dice, DB, and network submodules. This keeps language requirements attached to the targets that need them and prevents ambient compiler state from masking incomplete component configuration.

The root `LIBRARY_VERSION` definition is target-local to `coda` rather than injected through `CMAKE_CXX_FLAGS`.

`CODA_BUILD_TESTS` now governs the aggregate root tests and the migrated `format`, `dice`, `db`, and `net` component test trees through the shared cache option. Issue #5 tracks completing the remaining test-system convergence, including legacy Bandit setup and build-time test dependency behavior.

Some analysis paths still use legacy shared CMake helpers that mutate global compiler flags, particularly coverage instrumentation. Those are intentionally separate from the language-requirement migration and remain tracked under issues #2 and #5.

The release CI gate recursively initializes submodules and proves the full aggregate compile graph with shared tests disabled. Test-layer CI, sanitizers, coverage, and service-backed integration tests remain separate follow-up work under issue #5.
