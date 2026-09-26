# Building Seamwork

## Default boundary

The default build is now **Seamwork**, not the historical libcoda aggregate.

C++23 studies/components/examples are the active surface. Archived libcoda code remains available through an explicit compatibility build while migration and provenance work finishes.

The default path does **not** require the legacy DB/network/tooling dependency graph or recursive submodules.

## Prerequisites

The recommended environment is the checked-in Nix flake:

```bash
nix develop
```

The default shell contains the C++23 build toolchain used by CI:

- CMake;
- Ninja;
- GCC 14;
- Clang.

Without Nix, use CMake 3.21+ and a C++23-capable compiler.

## Seamwork builds

Development:

```bash
cmake --preset dev
cmake --build --preset dev
ctest --preset dev
```

Release:

```bash
cmake --preset release
cmake --build --preset release
ctest --preset release
```

Both default presets set:

```text
SEAMWORK_BUILD_STUDIES=ON
SEAMWORK_BUILD_TESTS=ON
SEAMWORK_BUILD_LEGACY=OFF
```

## Build options

| Option | Default | Purpose |
| --- | --- | --- |
| `SEAMWORK_BUILD_STUDIES` | `ON` | Build active C++23 design studies. |
| `SEAMWORK_BUILD_TESTS` | `ON` | Register active Seamwork tests with CTest. |
| `SEAMWORK_BUILD_LEGACY` | `OFF` | Build archived libcoda aggregate/components for compatibility or historical validation. |

Legacy `CODA_*` and `ENABLE_*` analysis/test options remain available only for the explicit compatibility path.

## Legacy compatibility build

The legacy graph is preserved as transition evidence, not as the default product.

Initialize its historical submodules:

```bash
git submodule update --init --recursive
```

Enter the larger compatibility shell:

```bash
nix develop .#legacy
```

Then configure/build explicitly:

```bash
cmake --preset legacy-dev
cmake --build --preset legacy-dev
ctest --preset legacy-dev
```

A release-style compatibility build is available as `legacy-release`.

## CI

Required CI uses the flake and builds/tests the active Seamwork surface with both GCC and Clang.

The archived libcoda compatibility graph is a separate manually invoked job. This keeps normal CI fast and prevents legacy DB/network dependencies from defining Seamwork's runner image.

## Language-standard ownership

Each active target owns its language requirement with `target_compile_features`; Seamwork code uses C++23.

Archived legacy targets retain their historical target-local language requirements only while the compatibility graph exists. They should not receive syntax-only modernization.

## Direction

The build should continue converging toward:

- active C++23 studies/components/examples;
- flake-driven CI and development environments;
- minimal default dependencies;
- target-local compiler and dependency contracts;
- deterministic tests without external services by default;
- legacy code removed or archived once its evidence/provenance value is preserved.

See [the migration plan](migration/seamwork-rebrand.md) for sequencing.
