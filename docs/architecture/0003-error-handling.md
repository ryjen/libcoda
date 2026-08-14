# 0003 — Error handling policy

## Status

Accepted as modernization guidance.

## Principles

Errors are part of a component contract. A caller should be able to distinguish malformed external input, invalid API/state usage, and infrastructure failure without depending on undefined behavior or backend-specific implementation details.

## Required rules

1. Throw exception objects by value; never `throw new ...` or otherwise transfer exception ownership through raw pointers.
2. Do not use null dereference, assertion failure, process termination, or undefined behavior as normal invalid-input handling.
3. Preserve useful causal information when translating backend errors, but do not expose secrets merely to make an error descriptive.
4. Prefer a small, documented exception surface over creating a unique exception class for every branch.
5. Destructors and cleanup paths must not throw during ordinary resource release.
6. A moved-from or closed object may have restricted operations, but those restrictions must be deterministic and documented rather than relying on stale internal pointers/handles.

## Error categories

### Parse / validation errors

Examples:

- malformed format specifier;
- invalid URI;
- unsupported or malformed protocol field;
- invalid SQL/query-builder input that can be detected before execution.

These are recoverable caller/input errors. Components should reject them deterministically at the pure parsing/model boundary when possible.

Use `std::invalid_argument` while the existing public API relies on standard exceptions, or a component-specific parse/validation exception when the component already has a stable hierarchy. Do not expose `std::stoi`/third-party parser exceptions accidentally as the public contract.

### Invalid state / programmer errors

Examples:

- binding more arguments than a format has specifiers;
- executing through a session/statement that has no valid underlying resource;
- committing an already completed transaction;
- using a transport after ownership has been transferred or closure is final.

If the invalid state is possible through a public runtime sequence, detect it and return/throw a documented failure rather than asserting. Assertions remain appropriate for internal invariants that cannot be caused by supported public input or lifecycle calls.

### Infrastructure / adapter failures

Examples:

- database connection/query failure;
- DNS/socket/TLS failure;
- filesystem/platform failure;
- third-party library failure.

Adapters should translate implementation-specific errors at the adapter boundary when callers do not need the raw type. Preserve backend diagnostic text/code where useful, but attach it to a stable component-level error model.

A DB/network abstraction should not require callers to include MySQL/PostgreSQL/OpenSSL/platform headers merely to catch normal operational failures.

## Exception hierarchy direction

Do not introduce a project-wide inheritance tree preemptively. Prefer component-scoped hierarchies where they add observable value.

A reasonable target is:

```text
std::exception
  -> coda::<component>::exception
       -> parse/validation error       (only if standard invalid_argument is insufficient)
       -> state/lifecycle error
       -> adapter/operation error
```

Backend-specific detail should normally be data carried by an adapter/operation error, not another public inheritance level.

## Recoverable versus fatal

Library code should treat most input, lifecycle, and infrastructure failures as recoverable by the embedding application.

Fatal process behavior is appropriate only when:

- continuing would violate memory/process safety and no safe error path exists; or
- the embedding application explicitly chooses to terminate after receiving a library error.

A reusable library should not call `exit`, `abort`, or terminate the process for an ordinary parse, DB, network, or configuration failure.

## Ownership and cleanup

Resource-owning types should make ownership obvious through RAII and move/copy policy.

- Prefer value members, smart pointers, or narrowly owned native handles over ambiguous raw owning pointers.
- Closing/releasing a resource should be idempotent where practical.
- Partial construction or adapter failure must not leak sockets, DB handles, buffers, or TLS state.
- Exception paths should provide at least the basic exception guarantee; stronger guarantees should be used for value/model operations where practical.

## Security and diagnostics

Error text and logs must not expose:

- DB URI passwords or credentials;
- TLS/private-key material;
- authentication headers/tokens;
- unbounded attacker-controlled payloads.

When an input is useful for diagnosis, log a bounded/redacted representation or metadata rather than the raw secret-bearing value.

## Testing expectations

For each public error contract that is modernized, add tests for:

- the successful path;
- malformed input;
- invalid lifecycle/state transitions;
- adapter failure translation where practical;
- cleanup after failure;
- redaction when errors/logging can contain credentials or sensitive input.

Fuzz harnesses should classify documented parse/validation exceptions as expected outcomes and allow crashes, sanitizer failures, invariant violations, or unexpected exception types to surface as findings.
