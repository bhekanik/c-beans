# c-beans — overview

The full project vision. Read this when you've lost the thread.

## What c-beans is

A terminal task manager written in C, structured to teach the C concepts a senior engineer with no formal CS background would otherwise plateau without. Each concept gets one chapter, one runnable artifact, one slow-and-sticky landing.

By the time c-beans ships v0.3, the codebase contains: hand-rolled JSON parser, owned strings + dynamic arrays + tagged unions, a Store interface implemented over both JSONL and SQLite, an ncurses TUI built on a model/update/view pattern, and a TCP daemon serving multiple thin clients with pub/sub events. The TUI and CLI both work; both reach the daemon over the same protocol; both can be replaced.

## Why c-beans exists

Two reasons, both load-bearing:

1. **CS foundations practice.** The learner is a senior engineer who came up through web dev — strong tacit knowledge, weak classical fundamentals. C is the forcing function for filling those in. Manual memory, pointer semantics, the kernel boundary — internalised by writing them, not by reading about them.

2. **Setting up Rust to land.** The learner is also building [lazydap](https://github.com/planetaryescape/lazydap) (a Rust DAP debugger) in parallel. Rust's hardest features (ownership, lifetimes, `Result`, `?`, exhaustive `match`) exist *to fix specific pains in C*. c-beans surfaces the pains; lazydap teaches the Rust solutions. The two books are siblings.

The point isn't to ship c-beans fast. The point is the practice.

## End-state architecture

See [`/ARCHITECTURE.md`](../../ARCHITECTURE.md). The short version:

- **Modules**: `core`, `string_`, `vec`, `json`, `store`, `task`, `tui`, `cli`, `daemon`. Each its own static library; cross-module access via public headers in `include/beans/`.
- **Storage**: Store interface (function-pointer vtable) with JSONL and SQLite backends. The CLI/TUI never talk to backends directly.
- **Surfaces**: CLI (canonical), TUI (ncurses), daemon (TCP, JSON-RPC-shaped). Every TUI action has a CLI equivalent. Once the daemon ships, both become network clients.

## Phases

| Phase | What lands | Shipping flag |
|---|---|---|
| 0 — Workspace | Build system, conventions, CI | (no shippable artifact) |
| A — Memory primitives | Owned String, Vec, tagged unions | (still no shippable) |
| B — JSON parser | Hand-rolled tokenizer + parser + DOM | (parses but doesn't store) |
| C — JSONL persistence | Store interface + JSONL backend | (CLI add/list works) |
| D — Domain + tests | ULID, errors, test harness, CRUD CLI | (CLI shippable, no TUI) |
| E — TUI | ncurses TUI on JSONL | (full feature parity) |
| F — Polish | XDG paths, error rendering, README, **ship v0.1** | **v0.1.0** |
| G — SQLite | Embedded sqlite, prepared statements, transactions, **swap default backend** | **v0.2.0** |
| H — Daemon + TCP | BSD sockets, length-prefixed framing, multi-client poll, **daemon-backed thin clients** | **v0.3.0** |

The session plan with chapter-level breakdowns lives at [`docs/teaching/sessions.md`](../teaching/sessions.md).

## Principles

1. **Hand-roll what's pedagogical.** No `cJSON`, no `getopt_long` for CLI parsing, no third-party `String` lib. The build IS the teaching.
2. **Sanitizers are first-class teaching material.** ASan + UBSan are co-teachers, not optional QA.
3. **The Store is the load-bearing abstraction.** Established in Phase C so Phase G's SQLite swap is trivial.
4. **The CLI is the canonical surface.** TUI is a client; agents (eventual) are clients. Same protocol once the daemon ships.
5. **One concept per chapter.** Hard cap. The pedagogy depends on this.
6. **Every chapter ships an artifact you can run** (or names itself as ceremony — see [`docs/teaching/build-philosophy.md`](../teaching/build-philosophy.md)).

## See also

- [`/ARCHITECTURE.md`](../../ARCHITECTURE.md) — the end-state architecture in more detail
- [`/AGENTS.md`](../../AGENTS.md) — pedagogy, learner profile, agent startup checklist
- [`docs/teaching/sessions.md`](../teaching/sessions.md) — session-by-session plan
- [`docs/book/README.md`](../book/README.md) — chapter table of contents
