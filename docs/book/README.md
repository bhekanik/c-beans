# c-beans — the book

A multi-session walk through learning C while building a real terminal task manager. Each chapter is one teaching session: one new concept, one runnable artifact at the end. Read it solo or open it in an LLM-aware coding agent.

## How to read this

1. Start with [`00-introduction.md`](00-introduction.md) — how learning works in this book. ~10 min.
2. Read [`00b-what-is-c-beans.md`](00b-what-is-c-beans.md) — the technical context. ~5 min.
3. Optional: [`00c-why-im-learning-c.md`](00c-why-im-learning-c.md) — personal backstory. ~5 min. Skip if you just want to learn C.
4. Then [chapter 01](01-cmake-workspace.md) and forward, one chapter per session.

## The chapter list

### Phase 0 — Workspace setup (ceremony)

| # | Chapter | Concept | Artifact | Status |
|---|---|---|---|---|
| 01 | [CMake workspace](01-cmake-workspace.md) | Workspace structure | `libbeans_core.a` builds clean | filled |
| 02 | [Hello, beans](02-hello-beans.md) | First binary linking a library | `./build/bin/beans` prints "hello, beans" | stub |
| 03 | [Conventions as code](03-conventions-as-code.md) | Formatter, sanitizers, CI | `BEANS_SANITIZERS=ON` build runs | stub |

### Phase A — Memory primitives

| # | Chapter | Concept | Artifact | Status |
|---|---|---|---|---|
| 04 | [First segfault on purpose](04-first-segfault.md) | UB and ASan as co-teacher | ASan diagnoses a use-after-free | stub |
| 05 | [Owned String](05-owned-string.md) | The three-field String invariant | String round-trips through alloc + append + free | stub |
| 06 | [String views](06-string-view.md) | Owned vs borrowed | Function takes view, builder takes ownership | stub |
| 07 | [Vec_int](07-vec-int.md) | Dynamic array, realloc, doubling | Vec_int with 100 pushes prints | stub |
| 08 | [Generic Vec via macros](08-generic-vec-macros.md) | Macros as the only generics C has | `Vec_String`, `Vec_Task` from one macro | stub |
| 09 | [Tagged unions](09-tagged-unions.md) | Sum types in C | `TaskEvent` with exhaustive switch | stub |

### Phase B — Hand-rolled JSON parser

| # | Chapter | Concept | Artifact | Status |
|---|---|---|---|---|
| 10 | [File I/O](10-file-io.md) | `fopen` / `getline` / EOF | Reads a file line by line | stub |
| 11 | [The tokenizer](11-tokenizer.md) | State machine, characters → tokens | Tokenizes `{"a": 1}` | stub |
| 12 | [String tokens — escapes](12-string-tokens.md) | Escape decoding, UTF-8 | `"hello\nworld"` decoded correctly | stub |
| 13 | [Number tokens](13-number-tokens.md) | `strtol` / `strtod` with `errno` | Parses numbers, detects overflow | stub |
| 14 | [Recursive descent](14-recursive-descent.md) | Recursive parser | Parses arbitrary JSON to DOM | stub |
| 15 | [DOM to typed Task](15-dom-to-task.md) | Validation as a separate layer | `Task` populated from JSON line | stub |

### Phase C — JSONL persistence

| # | Chapter | Concept | Artifact | Status |
|---|---|---|---|---|
| 16 | [The Store interface](16-store-interface.md) | Vtables in C | Empty `Store` + `StoreVTable` | stub |
| 17 | [JSONL write](17-jsonl-write.md) | `O_APPEND` atomicity | `beans add` persists a task | stub |
| 18 | [JSONL read](18-jsonl-read.md) | Startup load | `beans list` reads from file | stub |
| 19 | [Atomic file writes](19-atomic-writes.md) | tmp + fsync + rename | Crash-safe rewrite | stub |

### Phase D — Domain + tests

| # | Chapter | Concept | Artifact | Status |
|---|---|---|---|---|
| 20 | [TDD-1: testing as a discipline](20-testing-discipline.md) | Test harness + Implementation Swap Test | `ctest` runs all chapters' smoke tests | stub |
| 21 | [Task model + ULID](21-task-model.md) | ULID generation, time_t | Task with sortable id | stub |
| 22 | [CRUD CLI](22-crud-cli.md) | Command dispatch through Store | `beans add/list/complete/delete` works; no-args prints help (TUI swaps in at chapter 24) | stub |
| 23 | [Errors as values](23-errors.md) | `BeansError` enum, Result pattern | Errors propagate cleanly | stub |

### Phase E — TUI

| # | Chapter | Concept | Artifact | Status |
|---|---|---|---|---|
| 24 | [Hello, ncurses](24-hello-ncurses.md) | initscr/refresh/getch/endwin | `beans` (no args) launches the TUI, prints + waits for keypress | stub |
| 25 | [Render task list](25-render-task-list.md) | ncurses windows, mvprintw | Task list shows | stub |
| 26 | [Navigation](26-tui-navigation.md) | j/k, A_REVERSE highlight | Cursor moves through list | stub |
| 27 | [Modes — model/update/view](27-tui-modes.md) | TEA in C | Normal/Insert/Edit modes | stub |
| 28 | [Add via TUI](28-tui-add.md) | One-line text editor | Press `a`, type, task added | stub |
| 29 | [Filter](29-tui-filter.md) | `/` filter, derived state | Filter applies to view | stub |
| 30 | [Wire CRUD](30-tui-crud.md) | Full CRUD round-trip | Toggle + delete in TUI | stub |

### Phase F — Polish + ship v0.1

| # | Chapter | Concept | Artifact | Status |
|---|---|---|---|---|
| 31 | [XDG paths](31-xdg-paths.md) | XDG Base Directory spec | Tasks live in `~/.local/share/beans/` | stub |
| 32 | [Error rendering in TUI](32-tui-error-bar.md) | Status bar, time-based clear | Errors show + auto-clear | stub |
| 33 | [Ship v0.1](33-ship-v01.md) | LICENSE, CHANGELOG, demo | `v0.1.0` tag pushed | stub |

### Phase G — SQLite migration

| # | Chapter | Concept | Artifact | Status |
|---|---|---|---|---|
| 34 | [Embedding sqlite](34-embed-sqlite.md) | `FetchContent`, `sqlite3_open` | DB file with `tasks` table | stub |
| 35 | [Prepared statements](35-prepared-statements.md) | bind/step/finalize, no SQLi | Insert via bound params | stub |
| 36 | [Transactions, WAL](36-transactions-wal.md) | ACID, crash safety | Bulk insert atomic | stub |
| 37 | [Migrate JSONL → SQLite](37-jsonl-sqlite-migrate.md) | Store interface payoff | TUI runs on SQLite | stub |

### Phase H — Daemon + TCP

| # | Chapter | Concept | Artifact | Status |
|---|---|---|---|---|
| 38 | [Hello, sockets](38-hello-sockets.md) | BSD sockets API | Server prints what client sends | stub |
| 39 | [Length-prefixed framing](39-tcp-framing.md) | Message boundaries on TCP | Framed messages flow | stub |
| 40 | [Protocol design](40-protocol-design.md) | JSON-over-TCP envelope | Typed request/response | stub |
| 41 | [Multi-client poll](41-multi-client-poll.md) | `poll(2)`, no threads | Two clients connected | stub |
| 42 | [Daemon extraction](42-daemon-extraction.md) | Auto-spawn, probe-fork-wait | CLI as thin client | stub |
| 43 | [TUI as thin client](43-tui-thin-client.md) | Pub/sub events | TUI updates from CLI in another shell | stub |

## See also

- [`/AGENTS.md`](../../AGENTS.md) — pedagogy, learner profile, agent startup
- [`/docs/teaching/sessions.md`](../teaching/sessions.md) — session plan with concept + artifact per row
- [`/docs/blueprint/00-overview.md`](../blueprint/00-overview.md) — full project vision
- Sister book: [lazydap](https://github.com/planetaryescape/lazydap) — Rust solutions to the C pains taught here
