# libcoda-format threat model

## Scope

`libcoda-format` parses format strings, stores specifier/argument state, applies stream manipulators, renders values, supports reset/copy/move operations, and exposes a public C++ formatting API.

Format strings should be treated as potentially untrusted when they originate from configuration, protocol data, templates, logs, or external inputs.

## Security invariants

1. Malformed format strings fail deterministically with documented exceptions rather than memory errors or undefined behavior.
2. Numeric/index/width/precision parsing consumes complete tokens and rejects overflow or unsupported syntax.
3. Specifier/index state cannot address outside owned containers/buffers.
4. Copy/move/reset preserve valid iterator/state relationships.
5. Rendering does not interpret format data as printf-style variadic control strings.
6. Attacker-controlled inputs have bounded enough size/work characteristics for intended use; fuzz harnesses enforce explicit campaign bounds.
7. Public headers do not leak namespace state or unnecessary implementation dependencies into consumers.

## Trust boundary

```text
format string + typed arguments
  -> parser/specifier model
  -> argument binding/state
  -> renderer/stream manipulation
  -> resulting string/stream
```

The parser boundary should remain independently testable/fuzzable without filesystem, network, DB, clock, or random dependencies.

## Current posture

Recent modernization work has already improved several security properties:

- public-header `using namespace std` pollution was removed;
- canonical grammar and legacy compatibility syntax are documented;
- index/width/precision numeric fields are parsed strictly instead of accepting `std::stoi` prefixes;
- malformed/repeated separators, negative index/precision, and width overflow are regression-tested;
- AFL++ harnessing exercises parse/copy/move/bind/render/reset transitions with bounded input and argument counts;
- CI includes sanitizer and fuzz-smoke coverage in the component repository.

These controls reduce parser ambiguity but do not make fuzzing or sanitizer review complete.

## Primary abuse cases

### Parser memory/iterator corruption

Malformed braces, specifier ordering, reset operations, and copy/move state can stress iterator relationships.

Mitigations:

- unit tests for malformed/truncated/escaped inputs;
- ASAN/UBSAN execution of tests and fuzz corpus;
- fuzz copy/move/reset cycles, not only constructor parsing;
- avoid storing iterators across container mutations unless the lifecycle invariant is explicit.

### Integer/resource abuse

Indexes, width, precision, format-string length, and specifier count are attacker-influenced.

Mitigations:

- strict decimal token parsing and overflow rejection;
- document current width range where storage is intentionally narrow;
- bound fuzz input and repeated argument operations;
- review whether production parsing needs an explicit maximum input/specifier count or whether caller-level bounding is sufficient.

### Unexpected argument rendering side effects

User-defined argument types can execute arbitrary `operator<<` code. This is a normal C++ extensibility property, not a parser sandbox.

Security contract:

- libcoda-format guarantees its own parsing/state safety;
- it does not isolate or sandbox arbitrary caller-provided streaming operators;
- exceptions or side effects from user-defined `operator<<` remain caller/type behavior.

### Output/log injection

A memory-safe formatter can still render attacker-controlled newlines/control characters into logs or terminal output.

Mitigations belong at the output sink/context boundary:

- escape/sanitize control characters for structured logs or terminal contexts when required;
- do not claim the formatter itself provides HTML/shell/SQL/log escaping.

## Fuzzing contract

The deterministic format harness should:

- accept raw stdin bytes/strings;
- bound total input size;
- exercise constructor parsing, copy/move, argument binding, rendering, and reset;
- classify documented `std::invalid_argument` parse failures as expected;
- surface crashes, sanitizer failures, unexpected exceptions, hangs, and invariant violations;
- maintain a small grammar-focused seed corpus and dictionary;
- preserve crash reproducers as regression tests/corpus entries after triage.

Long-running fuzz campaigns should be separate from normal PR latency, while bounded smoke runs remain suitable for CI.

## Verification priorities

1. Continue ASAN/UBSAN + AFL++ smoke on every relevant component change.
2. Add regression tests for every parser/fuzz crash before fixing it.
3. Review iterator/state invariants around reset/copy/move under sanitizers.
4. Evaluate resource limits based on observed fuzz/performance behavior rather than arbitrary global caps.
5. Keep output-context escaping explicitly out of the formatter contract unless a dedicated encoding API is added.
