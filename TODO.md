# TODO

The lightweight index. Real per-milestone content lives in `docs/implementation/tasks/`.

## Current teaching session

**Next session: `WS-1` — CMake workspace structure. [Read the plan](docs/teaching/sessions.md#phase-0--workspace-setup--3-sessions). [Read the chapter](docs/book/01-cmake-workspace.md).**

Before starting: greet the user, confirm we're in teaching mode, follow the AGENTS.md "fresh session" checklist (steps 1-10).

## Phases

- [ ] **Phase 0** — Workspace setup (chapters 01-03)
  - [ ] WS-1 — CMake workspace
  - [ ] WS-2 — First binary
  - [ ] WS-3 — Conventions as code
- [ ] **Phase A** — Memory primitives (chapters 04-09)
  - [ ] M0-1 — First segfault, ASan
  - [ ] M1-1 — Owned String
  - [ ] M1-2 — String views
  - [ ] M2-1 — Vec_int
  - [ ] M2-2 — Generic Vec via macros
  - [ ] M3-1 — Tagged unions
- [ ] **Phase B** — JSON parser (chapters 10-15)
  - [ ] M4-1 — File I/O
  - [ ] M5-1 — Tokenizer
  - [ ] M5-2 — String escapes
  - [ ] M5-3 — Number parsing
  - [ ] M6-1 — Recursive descent
  - [ ] M6-2 — DOM → Task
- [ ] **Phase C** — JSONL persistence (chapters 16-19)
  - [ ] M7-1 — Store interface
  - [ ] M7-2 — JSONL write
  - [ ] M7-3 — JSONL read
  - [ ] M7-4 — Atomic writes
- [ ] **Phase D** — Domain + tests (chapters 19-22 — TDD-1 numbering shifts; see sessions.md)
  - [ ] TDD-1 — Test harness meta-session
  - [ ] M8-1 — Task model + ULID
  - [ ] M8-2 — CRUD CLI
  - [ ] M9-1 — Errors as values
- [ ] **Phase E** — TUI (chapters 23-29)
  - [ ] M10-1 — Hello, ncurses
  - [ ] M10-2 — Render task list
  - [ ] M11-1 — Navigation
  - [ ] M11-2 — Modes
  - [ ] M11-3 — Add via TUI
  - [ ] M12-1 — Filter
  - [ ] M12-2 — Wire CRUD
- [ ] **Phase F** — Polish + ship v0.1 (chapters 30-32)
  - [ ] M13-1 — XDG paths
  - [ ] M13-2 — Error rendering
  - [ ] M13-3 — Ship v0.1
- [ ] **Phase G** — SQLite migration (chapters 33-36)
  - [ ] M14-1 — Embed sqlite
  - [ ] M14-2 — Prepared statements
  - [ ] M14-3 — Transactions, WAL
  - [ ] M14-4 — Migration + swap
- [ ] **Phase H** — Daemon + TCP (chapters 37-42)
  - [ ] M15-1 — Sockets
  - [ ] M15-2 — Length-prefixed framing
  - [ ] M15-3 — Protocol design
  - [ ] M15-4 — Multi-client poll
  - [ ] M15-5 — Daemon extraction
  - [ ] M15-6 — TUI as thin client

## See also

- [`docs/teaching/sessions.md`](docs/teaching/sessions.md) — full session plan (concept + artifact per row)
- [`docs/book/README.md`](docs/book/README.md) — chapter table of contents
- [`docs/implementation/`](docs/implementation/) — per-milestone task files (ship-mode-ready)
