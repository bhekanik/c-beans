---
chapter: "0b"
title: What is c-beans
status: complete
estimated_time_minutes: 6
---

# Chapter 00b — What is c-beans

> Required reading. ~6 minutes. The technical context everyone needs before chapter 01.

## What you'll know by the end

- What c-beans is at v0.1 vs v0.3, and why the staged shape matters
- The layer cake under c-beans: from your keystroke to the bytes on disk to the kernel
- Where the chapters that "feel like ceremony" sit on that cake — and why they're not actually ceremony

## What c-beans is

A terminal task manager. CRUD over a list of `Task`s. Each task has an id (ULID), a title, a status (active or completed), and timestamps. Tasks live in a file. You manipulate them via the CLI or the TUI — both are the same `beans` binary, dispatched by argv:

```bash
$ beans                  # no args → opens the ncurses TUI
$ beans add "feed the cat"
✓ added: 01HXV2... feed the cat

$ beans list
01HXV2... [ ] feed the cat
01HXM4... [x] take out trash
```

The "no args = TUI" convention is what `lazygit`, `htop`, `vim`, and most modern TUIs follow. Subcommand on the command line → script-like one-shot CLI behaviour. No subcommand → interactive UI.

That's it as a *product*. The interesting part is what's underneath.

## The c-beans layer cake

This is the sketch you'll come back to throughout the book.

```
┌──────────────────────────────────────────────────────┐
│  YOU (or your shell, your TUI, your script)          │
└────────────────────┬─────────────────────────────────┘
                     │ keystrokes / argv
                     ▼
┌──────────────────────────────────────────────────────┐
│  Frontend: beans CLI · beans TUI · (later) clients   │   ← Phase 0, E, H
└────────────────────┬─────────────────────────────────┘
                     │ direct call (early) → JSON-over-TCP (late)
                     ▼
┌──────────────────────────────────────────────────────┐
│  Domain: Task model, CRUD orchestration              │   ← Phase D
└────────────────────┬─────────────────────────────────┘
                     │ Store vtable
                     ▼
┌──────────────────────────────────────────────────────┐
│  Storage: JSONL backend OR SQLite backend            │   ← Phase C, G
└────────────────────┬─────────────────────────────────┘
                     │ libc syscalls
                     ▼
┌──────────────────────────────────────────────────────┐
│  Kernel: file descriptors, fsync, atomic rename      │   ← syscall boundary
└────────────────────┬─────────────────────────────────┘
                     │
                     ▼
┌──────────────────────────────────────────────────────┐
│  Disk: bytes that survive a power cut                │
└──────────────────────────────────────────────────────┘
```

Layer by layer, briefly:

- **Frontend.** What a user (or a script) talks to. Translates intent into Store ops. The CLI is the canonical surface; the TUI is just another client of the same Store. Once Phase H lands, both become network clients of the daemon.
- **Domain.** The Task model, the CRUD orchestration, error handling. Knows nothing about how tasks get persisted. Knows nothing about ncurses or TCP. Pure logic.
- **Store.** The persistence interface. Function-pointer vtable in C (chapter 16). Implementations: JSONL backend (chapter 17-19), SQLite backend (chapter 34-37). The frontend sees a `Store *` and calls through it; switching backends is a config flag.
- **libc.** The C standard library wrapping syscalls. `fopen`, `read`, `write`, `fsync`, `rename`. The boundary between what your program can do and what it asks the kernel to do.
- **Kernel.** Tracks the file descriptor, mediates the actual disk write, decides when bytes are durable, enforces atomicity for `rename`. You don't write kernel code in this book — you learn what the kernel guarantees so you can write code that depends on those guarantees correctly.
- **Disk.** Survives power cuts (when you've called `fsync`). Doesn't survive without it. The discipline of crash safety is built on this distinction.

## Why staged shipping (v0.1 → v0.2 → v0.3)?

The staged architecture is deliberate.

**v0.1 — JSONL only.** You hand-roll the JSON parser (Phase B), then build a JSONL store on top of it (Phase C). The pedagogy here is dense: every line of `cJSON` you'd otherwise depend on, you write yourself. State machines for the tokenizer, recursive descent for the parser, escape sequences, UTF-8, atomic file writes. Six chapters of parsing + four chapters of persistence.

**v0.2 — SQLite swap.** Phase G replaces JSONL with sqlite. Same Store interface, different backend. The point is that the rest of c-beans doesn't change at all. The Store interface from Phase C was the load-bearing abstraction; here it pays off. You also get to do the database stuff: prepared statements (vs string concat), transactions (vs atomic rename), WAL mode (vs `fsync`).

**v0.3 — daemon + thin clients.** Phase H extracts the daemon. The CLI and TUI become network clients of `beans-daemon` over a JSON-over-TCP protocol. Same architectural pattern as lazydap, postgres, redis, sqlite-server, kubelet — every program that grew from "single binary" to "multi-client server" walked this path. You learn BSD sockets, length-prefixed framing, multi-client `poll` loops, the auto-spawn-daemon dance.

The reason for the stages: each architectural change is itself a teaching surface. Skipping straight to a daemon would mean starting with sockets before you've done file I/O. Starting with SQLite would mean depending on a parser before you've built one. The staging is the curriculum.

## What c-beans is NOT

- Not a project management system. No projects, no tags, no recurrence (until optional Phase I, if you ever want them).
- Not a sync service. Local single-user.
- Not a TUI library or a parser library or a network library. It uses these things; it doesn't try to be them.
- Not a tutorial. The book is the tutorial; the project is the artifact.

## Where the "ceremony" chapters sit

Chapter 01 (CMake workspace) and chapter 03 (conventions as code) are *ceremony* chapters — they don't ship user-visible features. The build philosophy ([`docs/teaching/build-philosophy.md`](../teaching/build-philosophy.md)) names them as such. But they sit at the very bottom of the layer cake — the `cmake --build build` that produces every binary, the formatter that keeps the code readable, the sanitizers that make every later "first segfault" lesson catchable. Not glamorous. Not optional.

Chapter 02 (hello-beans) is where the first user-visible artifact lands: `./build/bin/beans` runs and prints something. The chapter list calls out which chapters are ceremony and which ship features, so you know what to expect at chapter close.

## What to take from this chapter

The required thing is the **layer cake**. Keep it in your head. When chapter 17 has you opening a file with `O_APPEND` and writing a JSON line, you'll think: "right, the CLI (frontend) is calling the Store (interface), which is calling the JSONL backend (implementation), which is calling `write(2)` (libc), which is asking the kernel (syscall) to put bytes on disk." That mental picture is what makes the design choices comprehensible.

Optional but useful: the staged-shipping framing. When chapter 34 (sqlite swap) lands, you'll already know *why* the Store interface exists — chapter 16 set it up exactly so this swap is trivial.

If you'd like the personal backstory behind the project (why I'm learning C, why this project, what it's setting up for), [Chapter 00c](00c-why-im-learning-c.md) has it. If you don't care, skip straight to [Chapter 01](01-cmake-workspace.md). The book works either way.

## See also

- [`/ARCHITECTURE.md`](../../ARCHITECTURE.md) — the end-state architecture in code-shape
- [`/docs/blueprint/00-overview.md`](../blueprint/00-overview.md) — the staged build plan
- [`/docs/teaching/sessions.md`](../teaching/sessions.md) — chapter-by-chapter what-and-why
- [`/docs/teaching/build-philosophy.md`](../teaching/build-philosophy.md) — what "artifact at chapter close" means

Next up: [Chapter 00c — Why I'm learning C](00c-why-im-learning-c.md) (optional backstory) or [Chapter 01 — CMake workspace](01-cmake-workspace.md) (where the book starts building).
