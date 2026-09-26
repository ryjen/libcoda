# Seamwork re-charter and migration

## Status

In progress.

This document tracks the transition from `libcoda` to Seamwork. The transition intentionally separates project purpose, code disposition, C++23 migration, and repository renaming so history is preserved and legacy code is not promoted accidentally.

## Target identity

**Seamwork — modern C++23 through interface and architecture refinement.**

The repository is becoming a design laboratory with practical consumers, studies, and selectively promoted components rather than an aggregate general-purpose utility toolkit.

## Migration principles

1. Preserve Git history and provenance.
2. Do not mechanically rename every `libcoda` component.
3. Review legacy code for educational or practical value before migration.
4. C++23 is required for new and materially refined Seamwork code.
5. Legacy C++17 code may remain temporarily while being classified or used as a baseline.
6. Prefer one coherent Seamwork repository unless a component demonstrates a real independent release/lifecycle need.
7. Keep compatibility shims only when they reduce migration risk; do not let compatibility define the new architecture.

## Proposed target layout

```text
seamwork/
├── docs/
│   ├── charter.md
│   ├── principles.md
│   ├── refinement-workflow.md
│   ├── design-notes/
│   ├── qart/
│   └── adr/
├── studies/
│   ├── interfaces/
│   ├── ownership/
│   ├── errors/
│   ├── polymorphism/
│   └── dependency-inversion/
├── components/
├── examples/
│   └── yahtzee/
├── benchmarks/
└── tests/
```

The layout is a target direction, not justification for empty directory scaffolding.

## Legacy disposition model

Each legacy area receives one disposition:

| Disposition | Meaning |
| --- | --- |
| KEEP | Useful practical consumer or component with a clear role in Seamwork. |
| REWORK | The problem remains useful but the implementation should become a C++23 refinement study. |
| ABSORB | Useful material should move into another study/component rather than remain independently branded. |
| ARCHIVE | Preserve as historical/reference material but do not present as recommended modern design. |
| REMOVE | No meaningful current purpose beyond accidental utility accumulation. |

## Final legacy disposition

The first disposition review is complete. These decisions determine what may receive further Seamwork modernization effort; they do **not** require immediate deletion of historical code.

| Legacy area | Final disposition | Rationale / preserved evidence | Follow-up |
| --- | --- | --- | --- |
| Yahtzee | **REWORK** (preserve lineage) | It is the strongest real historical consumer and a compact domain for interface studies. The old C++ application remains baseline evidence rather than a port target. | Continue focused C++23 studies; PR #23 established the randomness seam. |
| `libcoda-dice` | **ABSORB** | Generic dice and Yahtzee-specific behavior were already mixed. The useful randomness/domain problem belongs with the Yahtzee study, not an independent library. | Preserve history; migrate only behavior required by studies; retire the independent library when references are removed. |
| `libcoda-format` | **ARCHIVE** | C++23 `std::format` removes the main product justification. Its deterministic parser tests, fuzzing, sanitizer work, and bounded-input lessons remain valuable evidence. | Keep security/testing artifacts as reference; do not promote another formatter unless a study identifies a gap in standard/mature facilities. |
| `libcoda-db` | **ARCHIVE** | Adapter, transaction, URI, error, and backend-contract work is useful architectural source material, but Seamwork has no current consumer justifying a general DB abstraction. | Mine focused studies only when a real consumer needs them; preserve threat model and deterministic backend-test lessons. |
| `libcoda-net` | **ARCHIVE** | Transport/TLS/protocol boundaries are rich study material, but a broad networking library carries a large security and maintenance surface without a current Seamwork consumer. | Preserve threat model/test-boundary evidence; create future narrow studies from concrete consumers rather than maintain the library. |
| log | **ARCHIVE** | Historical variadic logging predates modern formatting/printing practice and has no current consumer justification. | Retain lineage only; use established logging facilities in examples unless logging itself becomes the study. |
| math / `bigint` | **ARCHIVE** | Arbitrary-precision arithmetic is a substantial specialist domain and not part of Seamwork's current interface-refinement thesis without a consumer. | Preserve implementation history; prefer a mature bigint implementation for future consumers. |
| string / argument / buffer helpers | **ARCHIVE** | The area combines tokenization, parsing, buffers, and generic string utilities. Much is better served by standard/mature facilities and no current consumer requires the old API. | Extract a focused parsing/interface study only if a real CLI example needs it. |
| terminal | **ARCHIVE** | VT100, cursor, color, output, and progress handling are infrastructure rather than a current design target. | Revisit as an adapter only for a practical CLI study; otherwise use a mature terminal library. |
| thread / `later` | **ARCHIVE** | The detached-thread helper has weak lifetime/cancellation semantics and predates `std::jthread`/stop-token-era design. It is useful as a negative baseline, not as a component. | Potential future structured-concurrency/lifetime study only when a consumer requires delayed work. |
| utility / collections | **REMOVE — completed in #26** | Generic collection helpers are precisely the utility-bucket model Seamwork is leaving behind and are largely superseded by ranges/standard algorithms. | Removed from the active tree; Git history preserves provenance. |
| json wrapper | **ARCHIVE** | C++23 has no standard JSON facility, but Seamwork has no reason to own a generic wrapper around json-c without a consumer. | Use a mature JSON library or narrow adapter in future examples; retain old code as history. |
| custom variant | **REMOVE — completed in #26** | The home-grown discriminated union is directly superseded by `std::variant` and has no remaining design role. | Removed from the active tree; retain only historical provenance. |
| shared `cmake` repo | **ABSORB selectively** | Build helpers are migration infrastructure, not a product. Useful helpers should live with the project or an organization-wide build standard. | Copy only still-needed helpers into the appropriate maintained location, then retire the independent dependency when unused. |

### Decision rule going forward

**ARCHIVE** does not mean "modernize before archiving." It means stop investing in the component as a product while preserving enough source, documentation, tests, threat models, and Git history to support future studies.

**REMOVE** means remove the code from the active Seamwork build/tree once references are eliminated; history remains available in Git.

**ABSORB** means migrate only the useful behavior/evidence into a concrete study or maintained build surface before retiring the old boundary.

No legacy component should receive a broad C++23 conversion simply because it exists.

## Inventory evidence

The first pass found several useful constraints:

- `ryjen/yahtsee` is archived and its default branch is Go.
- The recoverable `original` branch is C++14 and depends directly on old logging, string, dice, network, HTTP, async, terminal/libcaca, archive, and UPnP surfaces.
- The original Yahtzee test tree is effectively empty, so existing behavior must be characterized rather than assumed.
- `libcoda-dice` already mixes generic dice behavior with a `yaht` subtree, reinforcing that the historical library boundary was not especially strong.
- `libcoda-format` has some of the strongest existing modernization evidence (deterministic tests, fuzzing, target-local coverage), which is worth preserving even if the formatter itself is not promoted.
- DB and network components have useful adapter/security/test boundaries, but their scope is much broader than needed for an initial Seamwork example.

The first concrete study is tracked in #22: rebuild the smallest useful Yahtzee dice/randomness seam in C++23 and compare dependency-inversion mechanisms against a real consumer.

## C++23 migration

The aggregate/root target is the first C++23 boundary. Component targets remain responsible for their own compile-feature declarations while they are reviewed.

When a legacy component becomes an active Seamwork study/component:

1. establish a C++23 compiler/toolchain baseline;
2. characterize current behavior with tests;
3. identify the design question being studied;
4. compare standard-library/mature-library alternatives;
5. refactor only the parts required by the study;
6. update namespaces/targets only when the new contract is ready.

Do not perform a syntax-only "C++23 conversion."

## Rename sequence

1. Land charter, principles, workflow, and migration plan.
2. Establish C++23 at the aggregate/new-code boundary.
3. Inventory legacy components and decide KEEP/REWORK/ABSORB/ARCHIVE/REMOVE.
4. Build the first reference study/consumer under the new structure.
5. Introduce `seamwork::`, `Seamwork::`, and `SEAMWORK_*` names for active new surfaces.
6. Provide temporary compatibility aliases where justified.
7. Rename the GitHub repository from `libcoda` to `seamwork`.
8. Update badges, package metadata, links, namespaces, include paths, and related repositories.
9. Archive or redirect legacy component repositories according to their disposition.

The repository rename is deliberately later than the charter so the name does not imply that all legacy code is already endorsed as Seamwork.

## First milestone: Seamwork 0.1

- [x] Define the Seamwork charter.
- [x] Define design principles.
- [x] Define the refinement workflow.
- [x] Record the migration/disposition model.
- [x] Establish and validate the root C++23 build baseline.
- [x] Complete legacy component disposition review (#24).
- [x] Reconcile the existing multi-repository ADR with the new target topology.
- [x] Rebuild a focused Yahtzee slice as the first practical reference application (#22).
- [x] Complete one end-to-end refinement study.
- [ ] Introduce the first intentional `seamwork::` public surface.
- [ ] Rename the GitHub repository after the active surface reflects the new identity.
