# Teaching session breakdown

Per-milestone session cuts for teaching mode. The underlying milestones live in [`docs/implementation/tasks/`](../implementation/tasks/) — those stay clean and ship-mode-ready. This doc is the parallel teaching plan.

Cognitive load discipline: **one new concept per session.** Some milestones are 1 session; dense ones are several. Each session produces three artifacts: a teach-back captured in the Obsidian session note (private), a public **book chapter** at `docs/book/<NN>-<title>.md`, and a teacher's-eye **teaching-notes** file at `docs/teaching/notes/<NN>-<title>.md`. See `.skills/teaching/SKILL.md` rules 14 and 15.

c-beans is a **reproduce-mode** book: the learner builds the project from zero, chapter by chapter. Each chapter ends with a runnable artifact (unless explicitly named as ceremony — chapters 01 and 03 fall in that bucket).

Quick map from session ID → book chapter:

| Session | Chapter | Status |
|---|---|---|
| WS-1 | [`docs/book/01-cmake-workspace.md`](../book/01-cmake-workspace.md) | filled |
| WS-2 | [`docs/book/02-hello-beans.md`](../book/02-hello-beans.md) | stub |
| WS-3 | [`docs/book/03-conventions-as-code.md`](../book/03-conventions-as-code.md) | stub |
| M0-1 | [`docs/book/04-first-segfault.md`](../book/04-first-segfault.md) | stub |
| later | `docs/book/05-*` and onwards | stub — fill during the live session |

---

## Phase 0 — Workspace setup → 3 sessions

[`docs/implementation/00-workspace-setup.md`](../implementation/00-workspace-setup.md)

| Session | Concept | What we do |
|---|---|---|
| **WS-1** | CMake workspace structure | Root `CMakeLists.txt` with `project(c_beans)`, `add_subdirectory(src/core)`, first STATIC library `beans_core`. Concept focus: what `CMakeLists.txt` is, what `add_subdirectory` does, the difference between a module-as-library and a binary, why we structure projects this way. **Ceremony — name it.** |
| **WS-2** | First binary linking a library | Add `src/cli/CMakeLists.txt` with `beans` executable that links `beans_core` and prints "hello, beans". Touch `argc`/`argv`. Concept focus: linker dependencies, the `target_link_libraries` graph, the difference between a library target and an executable target. |
| **WS-3** | Conventions as code | `.clang-format`, `.clang-tidy`, sanitizer CMake module (`cmake/Sanitizers.cmake`), warning module (`cmake/CompilerWarnings.cmake`), `.github/workflows/ci.yml` walkthrough, `Makefile` thin wrapper. Concept focus: why each file exists, the gap between "compiles" and "compiles cleanly", the failure modes ASan/UBSan catch that the compiler doesn't. **Ceremony — name it.** |

Anchor: lazydap's `Cargo.toml` workspace + `rustfmt.toml`/`clippy.toml`/`rust-toolchain.toml` are the pattern. Each Rust convention file maps to a C analogue here. Read them side-by-side.

---

## Phase A — Memory primitives → 6 sessions

The cliff. Spend extra time here. C's hardest lessons live in this phase.

| Session | Concept | What we do |
|---|---|---|
| **M0-1** | First segfault — UB and ASan as co-teacher | Write a program that returns a pointer to a stack local. Compile, run, watch it crash (or worse, *not* crash). Re-build with `-fsanitize=address`, watch ASan diagnose it. Concept focus: undefined behaviour as a category, why "it ran fine" is not evidence of correctness, ASan as a teaching companion. **Pain anchor: dangling pointers — the canonical C bug.** |
| **M1-1** | The Owned String — `struct String { char *data; size_t len; size_t cap; }` | Build `String` with `string_init`, `string_free`, `string_append_cstr`, `string_debug`. Concept focus: ownership of heap memory, the three-field invariant (data + len + cap), why `len` and `cap` are separate, the discipline of "every allocation has exactly one owner". **Pain anchor: `char*` ambiguity — has no length, hopes for `\0`, no UTF-8 guarantee.** |
| **M1-2** | String views — `struct StringView { const char *data; size_t len; }` | Add `StringView` for borrowed access. Build `string_view_from_cstr`, `string_view_from_owned`. Establish the rule: functions that don't take ownership take a view; functions that do take ownership take a `String *`. Concept focus: the owned/borrowed distinction at the type level, `const`-correctness as a contract, why this matters more in C than in JS. **Pain anchor: "did I just hand someone a pointer they think they own?" — the source of double-free in real codebases.** |
| **M2-1** | Dynamic array — `struct Vec_int` (no generics yet) | Build `Vec_int` with `init`/`push`/`free`/`debug`. Concept focus: the realloc-on-full pattern, why we double on grow (amortised O(1)), what happens to existing pointers when realloc moves memory. **Pain anchor: every C codebase eventually grows its own dynamic array, badly. We're going to grow ours well, once.** |
| **M2-2** | Generic Vec via macros | Convert `Vec_int` to a `DEFINE_VEC(T)` macro that generates `Vec_T` for any type. Use it for `Vec_String`, `Vec_Task` (forward-declared). Concept focus: textual substitution as the only generic mechanism C has, the trade-offs (no type-checked generics, but no runtime cost either), the discipline of `_Generic` for type-dispatched calls. **Pain anchor: Rust's `Vec<T>` is a single type because the compiler monomorphises at compile time. C macros are how we bolt that on manually.** |
| **M3-1** | Tagged unions for events | Define `enum TaskEventTag` and `struct TaskEvent { TaskEventTag tag; union { TaskAdd add; TaskComplete done; TaskDelete del; } payload; }`. Write an exhaustive `switch` over the tag. Concept focus: sum types in C (`enum` + `union` + manual discipline), the "free must check the tag" rule, why `default:` is a footgun (silently swallows new variants). **Pain anchor: `switch` fall-through, missing cases for new variants, double-free when freeing the wrong union member.** |

End of Phase A. Stop point worth flagging — celebrate before Phase B. The memory primitives that everything else builds on are now real.

---

## Phase B — Hand-rolled JSON parser → 6 sessions

Build the JSON parser from zero. Every line of `cJSON` you'd otherwise depend on, you'll write yourself. The point is the parser as a teaching surface — JSON is small enough to build correctly in 6 sessions and large enough to teach state machines, error propagation, and recursive descent.

| Session | Concept | What we do |
|---|---|---|
| **M4-1** | File I/O — `fopen`, `fread`, `getline` | Read a file line-by-line. Handle EOF correctly. Concept focus: `FILE *` is opaque, the difference between line-buffered and unbuffered reads, why `fgets` is awkward and `getline` is preferred (POSIX 2008+), what happens when the file doesn't end with `\n`. **Pain anchor: NUL termination — the difference between "read N bytes" and "read until null".** |
| **M5-1** | The tokenizer — characters → tokens | State-machine tokenizer that emits `Token { TokenKind kind, StringView text, size_t line, size_t col }`. Recognise: `{`, `}`, `[`, `]`, `:`, `,`, strings, numbers, `true`, `false`, `null`. Concept focus: state machines as the right tool for character-driven parsing, why we tokenize before parsing (separation of concerns), how positions get tracked for error messages. |
| **M5-2** | String tokens — escape sequences and UTF-8 | Decode `\n`, `\t`, `\"`, `\\`, `\/`, `\b`, `\f`, `\r`, `\uXXXX`. Validate UTF-8. Concept focus: the tokenizer doesn't allocate; the parser does. Escape decoding happens at parse time, not tokenize time. The `\uXXXX` surrogate-pair dance. **Pain anchor: "I just used `strncpy`" → silent UTF-8 corruption.** |
| **M5-3** | Number tokens — `strtol` / `strtod` with `errno` | Parse integers and floats correctly. Detect overflow. Concept focus: why `atoi` is a footgun (no error reporting, undefined on overflow), the `endptr` + `errno` dance for safe parsing, the JSON number grammar's edge cases (no leading zero, optional fraction, optional exponent). **Pain anchor: `int x = atoi(s)` silently returns 0 on garbage. `strtol` reports the error.** |
| **M6-1** | Recursive descent parser — objects + arrays | Parse the token stream into a `JsonValue` DOM (tagged union). Concept focus: recursive descent as the standard parser shape, why "parse object" and "parse array" call each other recursively, how errors propagate through return values (no exceptions in C — return a `Result`-shaped enum). |
| **M6-2** | From DOM to typed Task struct | Write `task_from_json(JsonValue *)` that produces a `Task`. Validate required fields. Reject unknown fields (or warn). Concept focus: the parsing/validation distinction, why we don't shape-check during tokenize/parse (one job per layer), how to surface errors that point at line/column. |

---

## Phase C — JSONL persistence → 4 sessions

The first storage layer. JSONL because it's a parser exercise (we just built one) and append-friendly (one line = one entry). SQLite later.

| Session | Concept | What we do |
|---|---|---|
| **M7-1** | The Store interface — function pointers as vtable | Define `struct Store { void *self; StoreVTable *vtable; }` with a `StoreVTable` of function pointers (`add`, `list`, `complete`, `delete`). Concept focus: how C does polymorphism, why the explicit vtable is the right shape (vs hiding it via `void *` casts), the cost (one indirection per call) vs the benefit (multiple backends without recompiling consumers). **Pain anchor: "I want an interface" — and Rust gives you `trait`. C gives you this struct, and you build it yourself.** |
| **M7-2** | JSONL Store — write a task | First implementation of the Store interface. `jsonl_store_add()` opens the file in `O_APPEND`, serialises the task to JSON (using a tiny serialiser we write), writes one line. Concept focus: file flags (`O_APPEND` is atomic for small writes on POSIX), serialisation as the inverse of parsing, why JSONL's append-only shape simplifies the write path. |
| **M7-3** | JSONL Store — read all tasks at startup | `jsonl_store_load()` reads the file, runs each line through the parser, collects into `Vec_Task`. Concept focus: what to do with a malformed line (skip + warn? abort? quarantine?), why startup-load is OK at small scale and a problem at large scale (foreshadows the SQLite migration), how this interacts with the Store interface. |
| **M7-4** | Atomic file writes — `write tmp, fsync, rename` | The append-only write isn't enough for the "rewrite all tasks" path (used by `complete` / `delete`). Build the safe-rewrite pattern: write to `tasks.jsonl.tmp`, `fsync`, `rename` over the original. Concept focus: what `fsync` actually does, why `rename` on POSIX is atomic, the failure modes you survive (crash mid-write) and the ones you don't (hardware failure between rename and the next read). **Pain anchor: data loss on crash — a real production failure mode in many "simple" persistence layers.** |

End of Phase C. The store is a pluggable interface with one working JSONL backend. The TUI in Phase E will treat it as opaque, which is what makes the SQLite swap in Phase H trivial.

---

## Phase D — Domain logic + testing graduation → 4 sessions

| Session | Concept | What we do |
|---|---|---|
| **TDD-1** | The dedicated meta-session — testing as a discipline | Up to this point smoke tests have been teacher-written and treated as deferred-load (rule 8 of the teaching skill). This session walks the existing tests for chapters 04-19 together. Build the tiny test harness (`#define TEST(name)` + `#define ASSERT(...)` + a `main` that runs them). Concept focus: tests as a design tool *and* a verification tool, the Implementation Swap Test, behaviour-vs-implementation testing. After this session, M8 onward is test-driven by default. |
| **M8-1** | The Task model — id (ULID), title, status, timestamps | Implement `Task { char id[27]; String title; TaskStatus status; time_t created_at; time_t completed_at; }`. Build ULID generation (timestamp + randomness, Crockford base32). Concept focus: why ULID over UUID v4 (sortable, time-readable), `time_t` and friends, the `<random>`-equivalent in C (`getrandom` on Linux, `arc4random` on macOS — wrap it). |
| **M8-2** | CRUD via CLI — `beans add` / `list` / `complete` / `delete` | Wire each subcommand through the Store interface via a manual `argv[1]` switch. With no args, print help text (chapter 24 will swap that branch to "launch TUI"). Concept focus: command dispatch, how the CLI is just a thin caller of Store ops, the no-args-means-TUI discipline that ships in chapter 24. |
| **M9-1** | Errors — `enum BeansError`, `Result`-shaped returns, error rendering | Replace ad-hoc error returns with `enum BeansError` and a tagged-union-ish `Result_Task` pattern. Concept focus: error-as-value vs error-as-exception, why C doesn't have exceptions (the cost of `setjmp`/`longjmp`), how Rust's `Result<T, E>` and `?` operator are this pattern with sugar. **Pain anchor: the `errno` dance — return -1, check `errno`, hope nothing else clobbered it. Result types fix this.** |

End of Phase D. The CLI is feature-complete. Tests cover all of it. Time for the TUI.

---

## Phase E — ncurses TUI → 7 sessions

This is the longest phase. The TUI builds incrementally; each session adds one capability and ships an artifact you can run.

| Session | Concept | What we do |
|---|---|---|
| **M10-1** | Hello, ncurses — `initscr`, `printw`, `refresh`, `getch`, `endwin` | The minimum viable TUI: initialise, print "hello, beans", wait for a keypress, restore terminal. Wire the no-args branch of `main` (currently prints help, from chapter 22) to launch this TUI; subcommands continue to dispatch as before. Concept focus: what initscr actually does (raw mode, alternate screen, no echo), the absolute necessity of `endwin`, why `refresh()` exists, and the no-args-means-TUI dispatch convention. |
| **M10-2** | Render the task list — windows, `mvprintw` | Open the JSONL store, render the task list line by line. No interaction yet. Concept focus: ncurses windows as bounded drawing regions, the `mv*` family (move-then-do), why ncurses' coordinate system is `(y, x)` not `(x, y)`. |
| **M11-1** | Navigation — `j`/`k`, highlight current row | Track a `selected` index. Re-render with current row highlighted (`A_REVERSE`). Concept focus: the model + view split (state vs draw), input mapping, the `getch()` event loop. |
| **M11-2** | Modes — model/update/view loop in C | Refactor into `AppState`, `Msg`, `update(state, msg)`. Pure view function. Modes: `NORMAL`, `INSERT`, `EDIT`. Concept focus: the Elm Architecture in C, why this structure makes the TUI testable, how function pointers help here. **Anchor: The Elm Architecture (TEA) — the same pattern lazydap's TUI uses.** |
| **M11-3** | Adding tasks via TUI input | Press `a` → enter `INSERT` mode → type → press `Enter` → task added to store + list re-renders. Concept focus: line-buffer input, how to render a one-line text editor with primitives, the round-trip from TUI → Store → TUI. |
| **M12-1** | Filtering — `/` opens filter, applies to list | Add a `filter_text` to `AppState`, filter the rendered task list. Concept focus: derived state (filter applied at view time, not stored), how the model/update/view pattern handles transient UI state. |
| **M12-2** | Wire complete/delete to store + redraw | `<Space>` toggles complete, `d` deletes (with confirmation prompt). Concept focus: the full CRUD round-trip via the TUI, error rendering in the status bar (foreshadow Phase F). |

End of Phase E. **lazydap-equivalent v0.1 lands here** — full TUI on JSONL backend.

---

## Phase F — Polish + ship v0.1 → 3 sessions

| Session | Concept | What we do |
|---|---|---|
| **M13-1** | XDG config paths — `~/.config/beans/` + first-run setup | Replace hardcoded `tasks.jsonl` with the XDG Base Directory spec resolution. Create the directory on first run. Concept focus: `getenv("XDG_CONFIG_HOME")` with fallback, why hardcoded paths are a portability trap, how `mkdir -p` semantics work via `mkdir(2)` + `EEXIST`. |
| **M13-2** | Error rendering in TUI — status bar | Render errors from the store/parser/etc in a dedicated status bar at the bottom. Auto-clear after N seconds. Concept focus: how errors flow through the model/update loop, the time-based clear (the second tick source feeding `update`), graceful degradation. |
| **M13-3** | Final demo + README polish + ship v0.1 | LICENSE, CHANGELOG, README polish, real install instructions, GIF demo. Tag `v0.1.0`. Concept focus: the difference between "a project that builds" and "a project someone else can install", the documentation that matters for adoption. **Public release.** |

Major stop point. Celebrate. Then Phase G.

---

## Phase G — SQLite migration → 4 sessions

The user explicitly wants database experience in C. JSONL ships first (Phase C-F) so the parser teaching lands, then we get to do the real database stuff.

| Session | Concept | What we do |
|---|---|---|
| **M14-1** | Embedding sqlite3 — CMake `FetchContent`, opening a db, first query | Add sqlite as a CMake dependency (FetchContent + amalgamation). Open a database file. Run a hardcoded `CREATE TABLE` and a `SELECT 1`. Concept focus: sqlite as an embedded library (not a server), the amalgamation distribution model, the `sqlite3_open`/`sqlite3_close` lifecycle. **Pain anchor: every other DB in JS-land is a server. SQLite isn't. The mental model is different.** |
| **M14-2** | Prepared statements + parameter binding | `sqlite3_prepare_v2`, `sqlite3_bind_text`, `sqlite3_step`, `sqlite3_finalize`. Implement `sqlite_store_add()`. Concept focus: why prepared statements (SQL injection prevention + perf via parsed-query caching), the bind/step/finalize lifecycle, the `SQLITE_ROW` vs `SQLITE_DONE` return values. **Pain anchor: SQL injection — the same shape as buffer overruns; manual concatenation gets you owned.** |
| **M14-3** | Transactions + crash safety (WAL mode) | Wrap multi-step writes in `BEGIN`/`COMMIT`. Switch to WAL journal mode. Concept focus: ACID, what each letter actually buys you, why WAL is the default for embedded sqlite, the crash-safety guarantees vs the JSONL atomic-rename approach. |
| **M14-4** | Implement Store interface against SQLite + migrate JSONL → SQLite + swap default backend | Write `sqlite_store.c` implementing the same Store vtable as `jsonl_store.c`. Build `beans migrate` that reads JSONL → writes SQLite. Switch default config to SQLite. Concept focus: the payoff of Phase C's Store interface — the TUI/CLI don't change at all. **The Store interface from M7-1 is the load-bearing abstraction here.** |

End of Phase G. **Multi-backend store.** JSONL still works (for export/import); SQLite is the default. Ship v0.2.

---

## Phase H — Daemon + TCP, TUI becomes a thin client → 6 sessions

Up to here, the TUI talks to the Store directly (in-process). This phase introduces a `beans-daemon` that owns the Store, and the TUI/CLI become network clients. The point is to learn TCP in C and to set up the architecture lazydap uses (daemon + multiple clients over IPC).

| Session | Concept | What we do |
|---|---|---|
| **M15-1** | Hello, sockets — `socket`, `bind`, `listen`, `accept`, `recv`, `send` | Server that prints whatever arrives. Client that connects and sends a string. Concept focus: the BSD sockets API as it actually is (not as it's romanticised), the `sockaddr_in` cast dance, why `SO_REUSEADDR` exists, the fork-on-accept anti-pattern (we won't use it — we'll use poll later). **Pain anchor: every "hello, sockets" tutorial in C either skips the cast dance or pretends it's normal. It isn't. We'll name it.** |
| **M15-2** | Length-prefixed framing on TCP | TCP is a byte stream, not a message stream. Same problem JSON had with `Content-Length`-framed input. Build `read_framed`/`write_framed` with a 4-byte big-endian length prefix. Concept focus: why TCP doesn't preserve message boundaries, the partial-read problem (`recv` may return less than asked), `htonl`/`ntohl` for network byte order. |
| **M15-3** | Designing the protocol — JSON-over-TCP envelope | Use the JSON parser from Phase B. Define `Request { id, kind, payload }` and `Response { id, result, error }`. Same shape as DAP, same shape as JSON-RPC. Concept focus: why you correlate requests by id, the request/response/event distinction (foreshadow), schema versioning. |
| **M15-4** | Multi-client server with `poll` | One server, multiple clients, no blocking on a single client's slow read. `poll(2)` over the listening socket + each client socket. Concept focus: blocking vs non-blocking I/O, `O_NONBLOCK`, why `select` is deprecated (FD set size), why `poll` is the pragmatic choice (vs `epoll`/`kqueue` which are platform-specific). **Pain anchor: "I'll just use a thread per client" — and now you have data races on the Store. The single-threaded poll loop avoids this entirely.** |
| **M15-5** | Daemon extraction — `beans-daemon` owns the Store, CLI becomes a thin client | New `src/daemon/` module. The CLI's `add`/`list`/`complete`/`delete` now connect to the daemon and send Request envelopes. Auto-spawn the daemon if not running (probe socket → fork+exec → wait for socket). Concept focus: process lifecycle, the auto-spawn/probe pattern (lazydap uses it for codelldb), why the daemon vs a single binary trade-off. |
| **M15-6** | TUI as thin client + event subscription | The TUI connects, sends `Subscribe { kinds: [TaskAdded, TaskCompleted, TaskDeleted] }`, and re-renders on incoming events. Open two terminals; mutate from the CLI in one, watch the TUI redraw in the other. Concept focus: pub/sub over a duplex socket, how the TUI's update loop folds incoming events alongside keypresses, the moment the architecture makes sense. **The big payoff session.** |

End of Phase H. **Daemon-backed, multi-client, networked architecture.** Ship v0.3.

The architectural progression — single binary → Store interface → SQLite swap → daemon + thin clients — is the same arc lazydap walks (in Rust). After Phase H the C work transfers cleanly: same patterns in Rust syntax.

---

## Optional Phase I — beyond v0.3 (sessions added on demand)

Possible future sessions, plotted but not committed:

- **FTS5 search** — full-text search across task titles/descriptions.
- **Triggers + audit log** — `created_at` / `updated_at` via triggers, audit table.
- **Schema migrations** — versioned migrations table, `beans migrate up`.
- **Tags / labels** — many-to-many table, FK constraints, joined queries.
- **Recurring tasks** — cron-shaped specs in a `recurrence` column.
- **TLS on the daemon socket** — `mbedtls` or `openssl` integration.
- **Unix domain socket** as an alternative to TCP for local-only.
- **A second TUI** in a different language (e.g., Rust ratatui) talking to the same daemon — proves the protocol is real.
- **Agent skill** that lets a coding agent drive the daemon (lazydap pattern).

Add as the user chooses. The protocol from Phase H means none of these touch the existing CLI or TUI.

---

## Counts

| Phase | Sessions | Cumulative |
|---|---|---|
| Phase 0 — Workspace | 3 | 3 |
| Phase A — Memory primitives | 6 | 9 |
| Phase B — JSON parser | 6 | 15 |
| Phase C — JSONL persistence | 4 | 19 |
| Phase D — Domain + tests | 4 | 23 |
| Phase E — TUI | 7 | 30 |
| Phase F — Polish + ship v0.1 | 3 | 33 |
| Phase G — SQLite migration | 4 | 37 |
| Phase H — Daemon + TCP | 6 | 43 |
| **Total to v0.3** | **43** | **43** |

At ~1.5 hours per session average, that's ~65 hours of teaching time. Two evenings a week for eight months.

---

## When to deviate from this plan

- **A session feels light** — extend it. Combine with the next one if there's energy and the concepts are related.
- **A session feels heavy** — split it. Add a row to the table. The plan is meant to evolve.
- **A new concept comes up that wasn't planned** — capture it. Make it its own session if substantive; fold into an existing session if minor.
- **Reality diverges from the plan** — update the plan. Don't quietly skip ahead.

The plan exists so the cognitive-load discipline is real and the ladder of artifacts is visible from day one. It's not a contract. The chapters are.

---

## See also

- [`README.md`](README.md) — what this directory is
- [`/AGENTS.md`](../../AGENTS.md) — teaching mode setup for this project
- [`docs/implementation/`](../implementation/) — the underlying milestone tasks (ship-mode-ready)
- [`/docs/blueprint/00-overview.md`](../blueprint/00-overview.md) — the full project vision (recenter when lost)
- Obsidian: `C-Beans Teaching Sessions.md` — where actual sessions get logged
- Obsidian: `Teaching Senior Engineers.md` — the pedagogy synthesis
