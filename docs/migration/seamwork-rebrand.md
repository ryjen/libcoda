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

## Initial inventory

These are migration directions, not blanket endorsements of the old implementations.

| Legacy area | Initial direction | Reason |
| --- | --- | --- |
| Yahtzee | KEEP AS LINEAGE / REWORK | The current default branch is a later Go rewrite, but the `original` branch preserves the C++14 application that consumed the old library family. Use it as baseline evidence; rebuild only useful domain seams in C++23. |
| `libcoda-dice` | ABSORB / REWORK | Contains generic dice plus Yahtzee-specific code/tests. It is a strong source for the first randomness/domain study but does not currently justify an independent library lifecycle. |
| `libcoda-format` | REWORK / ARCHIVE | Existing parser/fuzz work is useful evidence; C++23 `std::format` substantially weakens the case for maintaining another standalone formatter. Preserve interesting parser/API studies rather than competing with the standard facility. |
| `libcoda-db` | REWORK / ARCHIVE | Its easy-syntax wrapper and adapter boundaries are useful architecture/error-handling material, but Seamwork should not own a general DB abstraction without a concrete study/consumer need. |
| `libcoda-net` | REWORK / ARCHIVE | Transport/TLS/protocol boundaries are useful study material, but a broad networking library has a large maintenance/security surface and needs stronger justification than historical reuse. |
| log/math/string/terminal/thread/utility | REVIEW | Generic utility categories are exactly the old project shape Seamwork is moving away from. Review for study material or consumers rather than migrating them as categories. |
| shared `cmake` repo | REVIEW / ABSORB selectively | Keep only project-owned helpers that support the new build/evidence model; avoid retaining a separate helper repository solely for historical reasons. |

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
- [ ] Establish and validate the root C++23 build baseline.
- [ ] Complete legacy component disposition review.
- [x] Reconcile the existing multi-repository ADR with the new target topology.
- [x] Rebuild a focused Yahtzee slice as the first practical reference application (#22).
- [x] Complete one end-to-end refinement study.
- [ ] Introduce the first intentional `seamwork::` public surface.
- [ ] Rename the GitHub repository after the active surface reflects the new identity.
