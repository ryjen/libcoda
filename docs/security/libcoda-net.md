# libcoda-net threat model

## Scope

`libcoda-net` handles hostnames, URIs, socket lifecycle, network reads/writes, optional TLS, HTTP/curl integration, telnet/protocol behavior, and sync/async orchestration. Network peers and host/URI inputs must be treated as untrusted.

## Security invariants

1. A secure client connection authenticates the intended peer, not merely negotiates encryption.
2. Socket/TLS native handles have unambiguous ownership; resource-owning types are not shallow-copyable.
3. Buffer sizes and native API integer conversions are validated before narrowing.
4. Public address/URI APIs return value-oriented data without shared mutable buffers.
5. Malformed network/protocol input produces bounded errors rather than undefined behavior.
6. Closing/shutdown is deterministic and does not double-release a resource.
7. DNS/URI parsing does not silently change the trust decision about the requested host.

## Trust boundaries

```text
caller hostname / URI
  -> URI + DNS resolution
  -> socket transport
  -> TLS context / peer verification
  -> remote peer bytes
  -> protocol parser / client behavior
```

The hostname used for DNS resolution must remain available to TLS verification. Resolving an address is not equivalent to authenticating the host.

## Current findings

### NET-SEC-001 — TLS peer verification is not explicit

Current OpenSSL code creates a client context and calls `SSL_connect`, but does not visibly configure trusted certificate verification or expected-hostname verification.

Impact: an active attacker may be able to impersonate a TLS endpoint even though the connection is encrypted.

Required direction:

- use supported client TLS APIs;
- configure certificate-chain verification;
- bind verification to the requested hostname/IP;
- make verification failure observable;
- test trusted, untrusted, expired, and hostname-mismatch cases where feasible.

### NET-SEC-002 — `openssl_layer` is shallow-copyable

`openssl_layer` owns `SSL*` and `SSL_CTX*` but currently declares copy construction/assignment, while the implementation copies those pointers.

Impact: copies can release the same native resources more than once or retain dangling handles.

Required direction:

- delete copy construction/assignment unless a real deep/share ownership model is implemented;
- keep move construction/assignment explicit and no-throw where possible;
- ensure move assignment releases any resource already owned by the destination before taking ownership.

### NET-SEC-003 — raw-pointer exception ownership

Socket extraction contains `throw new socket_exception(...)`.

Impact: callers catching normal exceptions do not catch the pointer; ownership/leak/error behavior becomes inconsistent.

Required direction: throw the exception object by value and add a regression test.

### NET-SEC-004 — address string API uses shared/static storage

IPv4 uses `inet_ntoa` storage and IPv6 uses a function-static buffer.

Impact: returned pointers are not value-safe or reliably thread-safe and can be overwritten by later calls.

Required direction: return `std::string` (or another owning value type) and use `inet_ntop` into local storage.

### NET-SEC-005 — transport/TLS size and error translation

`secure_layer` exposes `size_t` lengths but OpenSSL read/write APIs have version-dependent integer-size contracts and error reporting through `SSL_get_error`.

Required direction:

- validate/narrow lengths safely;
- translate TLS errors consistently;
- distinguish orderly shutdown, retryable WANT_READ/WANT_WRITE, and fatal failures where non-blocking behavior requires it.

## Socket lifecycle review areas

- move assignment should close/release the destination's existing socket/TLS state before taking ownership;
- `listen()` should not attach a client TLS handshake to a listening socket; server TLS should occur on accepted connections with an explicit server context;
- failed `setsockopt` paths must close temporary sockets before continuing;
- accepted socket validity should use the platform `INVALID` contract rather than assuming descriptors `<= 0` are invalid;
- `AI_PASSIVE` should be reviewed on outbound client resolution;
- thread-safety expectations for shared socket/secure-layer instances must be documented.

## Protocol and parser boundaries

URI/HTTP/telnet parsers should be separable from live socket I/O. Fuzz targets should prefer pure byte/string parsing or fake transports before live network fuzzing.

Test/fuzz inputs should include:

- empty/truncated fields;
- oversized lengths/counts;
- invalid UTF-8/opaque bytes where accepted as raw protocol data;
- duplicate/conflicting URI components;
- unusual IPv4/IPv6 literals;
- protocol negotiation/state transitions in unexpected order.

## TLS configuration policy target

The secure default should eventually be:

- modern client method negotiated by OpenSSL;
- certificate verification enabled;
- trusted system roots or explicitly supplied trust store;
- hostname verification using the original caller hostname;
- SNI set when appropriate;
- insecure/no-verify mode only if explicitly requested and clearly named/documented.

No compatibility mode should silently weaken verification.

## Verification priorities

1. Fix copy ownership + raw-pointer exception with unit/sanitizer coverage.
2. Make IP/address return values owning and thread-safe.
3. Introduce an explicit TLS client verification contract and tests.
4. Separate transport/TLS/protocol parsing boundaries under #9.
5. Add URI/protocol/fake-transport fuzz targets under #6/#9.
