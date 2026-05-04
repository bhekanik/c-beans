# Architecture

The end-state architecture of c-beans. Most of this is **not yet built** — chapters land it incrementally. This file is the target.

## The core tenet

**Every action a TUI user can do, a CLI invocation can do, and a programmatic client can do.** Both wired or neither. The CLI is the canonical surface; the TUI is a client of the same Store; agents/scripts are clients of the same protocol once the daemon ships.

## Module layout

```
src/
├── core/           ← types, errors, result. No I/O. (chapter 01+)
├── string_/        ← Owned String + StringView (chapter 05-06)
├── vec/            ← Dynamic array (chapter 07-08)
├── json/           ← Tokenizer, parser, DOM, serialiser (chapter 11-15)
├── store/          ← Store interface + JSONL backend + SQLite backend (chapter 16-19, 33-36)
├── task/           ← Task model, ULID, CRUD orchestration (chapter 20-21)
├── tui/            ← ncurses TUI (chapter 23-29)
├── cli/            ← CLI parsing + dispatch (chapter 02, 21+)
└── daemon/         ← TCP daemon, request router, event broker (chapter 38-43)

include/beans/      ← Public headers (one per module)
examples/           ← One small program per chapter that motivates an example
tests/              ← Test files (assert-harness early, Unity later)
cmake/              ← Helper modules (Sanitizers.cmake, CompilerWarnings.cmake)
```

Each `src/<module>/` is its own static library (`beans_core`, `beans_string`, ...). Cross-module access goes through public headers in `include/beans/`. The linker enforces boundaries; convention does not.

## The Store interface (chapter 16)

```c
typedef struct Store Store;

typedef struct {
    BeansError (*add)(void *self, const Task *t);
    BeansError (*list)(void *self, Vec_Task *out);
    BeansError (*complete)(void *self, const char *id);
    BeansError (*delete)(void *self, const char *id);
    void       (*free)(void *self);
} StoreVTable;

struct Store {
    void *self;
    const StoreVTable *vtable;
};
```

Backends:

- **JSONL** (chapter 16-19): file at `~/.local/share/beans/tasks.jsonl`. Append-only writes; full rewrite via tmp+rename for `complete`/`delete`.
- **SQLite** (chapter 33-36): file at `~/.local/share/beans/tasks.db`. Prepared statements; WAL journal mode; transactions for batch ops.

The CLI and TUI never call backends directly. They hold a `Store *` and call through the vtable. The `BEANS_STORE` env var or config key picks the backend.

## CLI surface (chapter 02, 21)

```bash
beans                     # no args → launches the TUI (chapter 24+)
beans add "feed the cat"
beans list
beans list --status active
beans complete <id-prefix>
beans delete <id-prefix>
beans edit <id-prefix>
```

`beans` invoked with no arguments launches the TUI. Any subcommand argument routes to the CLI. Until chapter 24 ships, no-args prints help text; chapter 24 wires the TUI in as the no-args branch.

Output formats: human table by default (TTY), `--json` for scripting. Stable schema once chapter 23 lands.

## TUI architecture (chapter 26-27)

Model / Update / View pattern, in C:

```c
typedef struct {
    Vec_Task tasks;
    size_t   selected;
    Mode     mode;            // NORMAL, INSERT, EDIT, FILTER
    String   filter_text;
    String   status_msg;
    time_t   status_clear_at;
} AppState;

typedef enum { MSG_KEY, MSG_TICK, MSG_DAEMON_EVENT } MsgKind;
typedef struct { MsgKind kind; /* payload union */ } Msg;

AppState update(AppState s, Msg m, Cmd *out_cmd);
void     view(const AppState *s);
```

Single-threaded event loop reads keypresses + ticks + daemon events, dispatches via `update`, calls `view` on each frame. Side effects produced via `Cmd` (e.g., `Cmd::SendIpc(Request::Add)`).

Anchor: lazydap's TUI uses the same shape (in Rust). When chapter 26 lands, point at the parallel.

## Daemon architecture (chapter 41-43)

```
┌──────────────────────────────┐         ┌─────────────────────────────┐
│  beans <subcommand>          │         │  beans (no args)            │
│  (CLI client)                │         │  (TUI client)               │
└──────────────┬───────────────┘         └─────────────┬───────────────┘
               │ JSON-over-TCP framed                  │
               ▼                                       ▼
            ┌─────────────────────────────────────────────────┐
            │  beans-daemon                                   │
            │  (single binary; CLI/TUI both invoke `beans`,   │
            │   the daemon is auto-spawned on first contact)  │
            │  ┌───────────────────────────────────────────┐  │
            │  │ poll() loop over listener + clients       │  │
            │  ├───────────────────────────────────────────┤  │
            │  │ Request router → Store ops → Response     │  │
            │  ├───────────────────────────────────────────┤  │
            │  │ Event broker → Subscribed clients         │  │
            │  └───────────────────────────────────────────┘  │
            │                                                 │
            │  Owns: Store (JSONL or SQLite)                  │
            └─────────────────────────────────────────────────┘
```

Single-threaded. `poll(2)` over the listening socket and all connected client sockets. No data races on the Store because there's no other thread.

Auto-spawn: CLI/TUI probe the socket on startup; if nothing's listening, fork+exec the daemon and wait for the socket to appear. Same pattern as lazydap.

## What c-beans is NOT

- Not a project management system. No tags, no projects, no recurrence (until Phase I, optional).
- Not a sync service. Local single-user. (Sync sketched for Phase I.)
- Not a TUI library or a parser library or a network library. It uses these things; it doesn't try to be them.
- Not a tutorial. The book is the tutorial; the project is the artifact.

## See also

- [`docs/blueprint/00-overview.md`](docs/blueprint/00-overview.md) — full project vision
- [`docs/teaching/sessions.md`](docs/teaching/sessions.md) — chapter arc that produces this architecture
- [`AGENTS.md`](AGENTS.md) — non-negotiables, especially the no-third-party-libraries rule
