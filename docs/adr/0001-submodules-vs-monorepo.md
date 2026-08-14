# ADR 0001 — Retain component repositories and submodules during modernization

## Status

Accepted for the current modernization phase.

## Context

`libcoda` currently integrates independently versioned component repositories through Git submodules. The arrangement adds operational complexity, but it also represents real component/release boundaries: format, database, networking, and other libraries can evolve and validate independently before the aggregate repository advances its gitlink.

A monorepo could simplify atomic changes and shared tooling, but migrating source control structure before component contracts are stabilized would mix architectural refactoring with repository migration and make regressions harder to attribute.

## Decision question

Should libcoda preserve the current multi-repository/submodule topology during modernization, or migrate immediately to a monorepo/workspace?

## Alternatives

### A. Retain the current repositories and submodules

Component repositories remain independent. The aggregate repository pins exact component commits and validates them recursively.

Advantages:

- preserves existing release/history boundaries;
- keeps component modernization slices small and attributable;
- allows component CI/fuzzing to mature independently;
- makes aggregate gitlink advancement an explicit integration gate;
- avoids a large source-control migration while architecture is still changing.

Costs:

- cross-repository changes require ordered PRs/commits;
- stale gitlinks can hide component progress;
- tooling/CI conventions can drift;
- local checkout and contributor workflow are more complex.

### B. Immediate monorepo migration

Move component history/source into a single repository and replace submodule integration with normal subdirectories/workspaces.

Advantages:

- atomic cross-component changes;
- simpler checkout and code search;
- one CI/security/tooling policy surface;
- easier repository-wide refactors.

Costs:

- migration itself is high-churn and hard to separate from behavioral modernization;
- release/version boundaries must be redesigned at the same time;
- existing component repository consumers/history may be disrupted;
- broad commits can obscure which component introduced a regression.

### C. Package-only composition

Keep component repositories independent but remove submodules; consume released/installable component packages from the aggregate repository.

Advantages:

- stronger release boundaries;
- aggregate repository becomes a true consumer rather than a source checkout orchestrator;
- reduced nested Git complexity.

Costs:

- requires mature package/export/versioning contracts that do not yet exist consistently;
- slows coordinated development until component release automation is reliable;
- makes testing unpublished coordinated changes more complex.

## Recommendation

Choose **A: retain component repositories and Git submodules during the current modernization phase**.

This is a sequencing decision, not a claim that submodules are the ideal permanent topology.

The immediate architectural work is to make component contracts, CMake targets, tests, security boundaries, and packaging explicit. Once those boundaries are stable, the project can reassess whether submodules still provide value or merely impose coordination cost.

## Decision

For the current phase:

1. Component repositories remain independently maintained.
2. `libcoda` pins exact component SHAs as Git submodules.
3. Component changes should be validated in their own repository when practical.
4. Aggregate gitlink changes require recursive integration CI before merge.
5. Cross-repository modernization should be split into bounded component PRs followed by a small aggregate integration change.
6. No new third-party dependency should use Git submodules merely because project components do.
7. Monorepo migration is deferred until packaging/API/test boundaries are sufficiently stable to evaluate it on operational merits rather than as a modernization shortcut.

## Tradeoffs accepted

We accept additional coordination and gitlink maintenance in exchange for lower migration risk and clearer fault isolation during modernization.

The aggregate CI/build system must compensate for the topology by detecting:

- stale or invalid component SHAs;
- dependency-policy incompatibilities;
- component CMake/test option drift;
- integration failures caused by independently evolving component heads.

## Revisit criteria

Reopen this ADR when at least most of the following are true:

- component public targets/install/export behavior are stable;
- test/fuzz/static-analysis conventions are consistent;
- component release/version policy is documented;
- aggregate CI is reliable and cross-repository change frequency is measurable;
- the ongoing coordination cost of submodules is known rather than assumed.

At that point compare submodules, monorepo, and package-only composition using concrete metrics: change coupling, release cadence, CI time, contributor friction, and rollback/release independence.

## Consequences

Positive:

- modernization can proceed incrementally with explicit integration evidence;
- component CI and architecture can improve without waiting for repository migration;
- accidental cross-component coupling remains visible.

Negative:

- multi-repo coordination remains part of the SDLC;
- aggregate gitlinks must be deliberately maintained;
- architecture/tooling documentation must distinguish component and aggregate responsibilities.
