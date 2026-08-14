# libcoda-db threat model

## Scope

`libcoda-db` parses connection URIs, models SQL values and queries, maps bind parameters, and adapts sessions/statements/results/transactions to SQLite, MySQL/MariaDB, and PostgreSQL.

Database URIs and application values may be sensitive or attacker-controlled. External databases are separate trust domains even when they are operated by the same application owner.

## Security invariants

1. Data values are bound separately from SQL structure wherever the backend supports binding.
2. Raw SQL fragments/identifiers are never described as protected by parameter binding.
3. Credentials are not exposed through routine string conversion, diagnostics, or logs.
4. URI/query parsing is deterministic and bounded for malformed inputs.
5. Backend-specific handles/OIDs/errors remain inside adapter boundaries unless deliberately part of a public contract.
6. Transactions/sessions/statements reject invalid lifecycle states rather than dereferencing invalid native state.
7. Unit/fuzz tests for query/value logic do not require a live external DB service.

## Trust boundaries

```text
configuration / DB URI
  -> URI parser + credential representation
  -> query/value/bind model
  -> backend adapter
  -> external SQLite file / MySQL / PostgreSQL service
```

A string crossing from application data into SQL structure is a separate trust decision from a string bound as a value.

## Current findings

### DB-SEC-001 — URI string conversion retains credentials

`uri_type::parse()` stores the complete original URI in `value`, while `operator std::string()` returns that value. If the input contains `user:password@host`, ordinary stringification reproduces the password.

Impact: credentials can leak through logs, exception messages, debug output, telemetry, or caller diagnostics.

Required direction:

- make redacted display/stringification the default;
- preserve secret-bearing raw input only when necessary and with explicit access semantics;
- redact password/userinfo and security-sensitive query parameters;
- add regression tests proving password material is absent from display/error representations.

### DB-SEC-002 — SQL injection boundary is not documented at API level

The codebase contains query generation and bind mapping, but callers need a clear contract identifying which APIs accept structural SQL versus bound data.

Required direction:

- document bind guarantees for statement/query APIs;
- identify any raw SQL fragment, table, column, order-by, or expression APIs that remain structural;
- unit/fuzz test generated SQL and bind mapping independently from live DB services;
- avoid concatenating untrusted values into structural SQL paths.

### DB-SEC-003 — PostgreSQL adapter consumes server/internal type headers

The current PostgreSQL binding maps OID constants through `catalog/pg_type.h`, requiring server development headers in addition to `libpq`.

Security/maintenance impact: this expands the build dependency surface and couples the client adapter to PostgreSQL server header layout/versioning.

Required direction:

- evaluate replacing server-header constants with a stable adapter-local mapping or supported client-facing API;
- if retained, keep the dependency private to the PostgreSQL adapter and explicitly provision/version it.

### DB-SEC-004 — credential/error redaction is not systematic

Backend errors can contain connection/configuration context. No project-wide DB redaction helper/contract currently guarantees sensitive URI material is removed.

Required direction:

- centralize redacted URI/display behavior;
- ensure exceptions and test diagnostics use redacted forms;
- test representative MySQL/PostgreSQL URI failures with credentials present.

## SQL structure versus values

Parameter binding protects **values**, not arbitrary SQL grammar.

Treat these as structural unless the API converts them through a trusted enumeration/model:

- table/column identifiers;
- sort direction;
- operators;
- raw WHERE/JOIN fragments;
- function names;
- LIMIT/OFFSET syntax on backends where not bound;
- schema/object names.

If user-controlled structural selection is required, map external strings to trusted internal identifiers rather than interpolating arbitrary input.

## Lifecycle and resource risks

Review session/statement/transaction/result ownership for:

- null/invalid native handles after failed construction;
- use after session/transaction completion;
- double finalization/rollback/commit;
- statement/result lifetime exceeding required backend owner lifetime;
- move/copy semantics for native-handle-owning objects;
- cleanup on backend exceptions.

SQLite should be the first deterministic contract backend because it avoids service/network uncertainty while exercising real adapter lifecycle behavior.

## URI parser inputs

Test/fuzz at least:

- missing scheme/host/path;
- user without password;
- password containing delimiters/escaped characters;
- IPv6 host forms;
- empty/malformed ports;
- very long user/host/query components;
- duplicate or unusual query keys;
- percent-encoding rules if/when supported;
- credential redaction regardless of parse success/failure.

## Service integration boundary

MySQL/PostgreSQL live service tests should be explicit integration jobs/fixtures and should use ephemeral credentials/databases. They should not be required for pure query/value/parser tests or fuzzing.

CI logs must not echo service credentials or full connection URIs containing secrets.

## Verification priorities

1. Make DB URI display/error output redacted by default and add tests.
2. Document and test SQL structure/bind boundaries.
3. Add deterministic SQLite lifecycle/contract tests.
4. Add SQL generation/bind/URI fuzz targets without external services.
5. Review PostgreSQL server-header dependency and native-handle ownership under #8.
