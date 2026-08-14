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

Development build with tests:

```bash
cmake --preset dev
cmake --build --preset dev
ctest --preset dev
```

Release build without test-only dependency setup:

```bash
cmake --preset release
cmake --build --preset release
```

## Build options

Current project-level options are:

| Option | Default | Purpose |
| --- | --- | --- |
| `CODA_BUILD_TESTS` | `ON` | Configure and build the test tree. |
| `CODA_ENABLE_COVERAGE` | `OFF` | Enable the existing coverage integration. |
| `CODA_ENABLE_MEMCHECK` | `OFF` | Enable the existing Valgrind memcheck integration. |
| `CODA_ENABLE_PROFILING` | `OFF` | Enable the existing Valgrind profiling integration. |

`ENABLE_COVERAGE`, `ENABLE_MEMCHECK`, and `ENABLE_PROFILING` remain accepted as compatibility aliases while downstream CMake is migrated. New scripts should use the `CODA_*` names.

## Modernization boundary

The root build is being modernized incrementally. This first slice deliberately keeps the project-wide C++17 setting because several component libraries are Git submodules and still inherit language configuration from the aggregate build. As those component targets migrate, they should declare their own `target_compile_features(... cxx_std_17)` and target-local compile definitions/options.

The root `LIBRARY_VERSION` definition is now target-local to `coda` rather than injected through `CMAKE_CXX_FLAGS`.

Tests still initialize Bandit through the legacy test CMake and may fetch it when `CODA_BUILD_TESTS=ON`. The testing modernization issue tracks removing that configure/build ordering and network dependency behavior.
