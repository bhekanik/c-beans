# c-beans

A terminal task manager written in C, built from zero as a learn-by-LLM book. Each chapter teaches one C concept and ships one runnable artifact. By the end you'll have a daemon-backed task manager with a JSONL/SQLite store, an ncurses TUI, and a TCP protocol — and you'll have the C pain in your hands that makes Rust's compiler feel like a gift.

## Status

**Pre-alpha.** Chapter 01 is the start of the build; nothing else exists yet.

The project is in active teaching-mode development. The shape of every chapter is settled; the shape of the final binary is sketched in [`docs/blueprint/00-overview.md`](docs/blueprint/00-overview.md).

## Who this book is for

You've shipped real software in *something* — JavaScript, Python, Java, Go, Ruby, Swift, anything. You want to fill in the layer below: manual memory, pointer semantics, the kernel boundary, the actual machinery higher-level languages hide. You don't want to sit through "what is a variable" — you want to walk into the C pain and feel it.

You also want a real artifact at the end, not just notes. c-beans is a real terminal task manager. By the time you finish chapter 43, you can install it, use it, give it to a friend.

## How to read this book

Two ways:

### Solo (like a textbook)

Read the chapters in order. At every `🔮 **Predict:**` prompt, *actually predict* the answer in your head. Then click the `<details>` block and calibrate. The pedagogy depends on you doing this — passive reading degrades the chapters into a flat tutorial.

Start at [`docs/book/00-introduction.md`](docs/book/00-introduction.md).

### Live, with an LLM-aware coding agent (Claude Code, Cursor, etc.)

Open the repo in the agent. The agent reads [`AGENTS.md`](AGENTS.md), the chapter, and the companion teaching notes; then it runs the chapter live — asking the predict questions out loud, waiting for your answer, calibrating, running the actual code in your environment, reading the actual compiler/ASan output with you.

The agent's contract: **the chapter is the curriculum.** It does not freestyle, skip ahead, or invent new concepts. If something genuinely new comes up, it flags it and stays in the chapter's lane.

To start: open the repo in your agent and say *"start chapter 01"* (or whichever chapter you're at).

## Quick orientation

```
docs/
├── book/                 ← the chapter sequence — read in order
│   ├── 00-introduction.md
│   ├── 00b-what-is-c-beans.md
│   ├── 00c-why-im-learning-c.md     (optional backstory)
│   ├── 01-cmake-workspace.md         (the build starts here)
│   └── ...
├── teaching/             ← teaching-mode metadata (skip if reading solo)
│   ├── sessions.md       ← the session plan
│   ├── build-philosophy.md
│   └── c-anchor-table.md ← JS/TS → C pain anchor reference
├── implementation/       ← ship-mode milestones (also skip if reading solo)
└── blueprint/            ← what we're building, end state
```

The book chapters are the canonical curriculum. Everything else exists to support them.

## What c-beans will be at v1

- A `beans` binary. Run with no arguments → ncurses TUI. Run with a subcommand (`add`, `list`, `complete`, `delete`, `edit`) → CLI.
- A `beans-daemon` (Phase H) that owns the Store and serves both modes over a JSON-over-TCP protocol. Auto-spawned on first contact; you never start it manually.
- Storage: JSONL by default (chapters 16-18), SQLite as an alternate backend (chapters 33-36) with an in-place migration tool.
- Tests, sanitizers, CI, lint — production-shape from chapter 03 forward.

The chapter list lives at [`docs/book/README.md`](docs/book/README.md) (or [`docs/teaching/sessions.md`](docs/teaching/sessions.md) for the session plan with concept and artifact per row).

## Try chapter 01 right now

The full chapter is at [`docs/book/01-cmake-workspace.md`](docs/book/01-cmake-workspace.md). It assumes:

- `cmake --version` prints something >= 3.20
- `clang --version` or `gcc --version` prints something modern
- An empty directory you can work in (this repo, after `git checkout chapter-01`)

Then:

```bash
git clone <repo-url> c-beans
cd c-beans
git checkout chapter-01            # start state of chapter 01
# Open docs/book/01-cmake-workspace.md and follow along.
```

## Build (when there's something to build)

Once chapter 01 ships its artifact, the build commands will look like this:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DBEANS_SANITIZERS=ON
cmake --build build
ctest --test-dir build --output-on-failure   # after TDD-1
./build/bin/beans --help                     # after chapter 02
```

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for the full developer-machine setup.

## Why "c-beans"

C, plus task management, plus the colour of strong coffee. Naming was not the hard problem.

## License

MIT. See [`LICENSE`](LICENSE) (TODO: add).

## See also

- [`AGENTS.md`](AGENTS.md) — for AI agents working in this repo
- [`CONTRIBUTING.md`](CONTRIBUTING.md) — developer setup, chapter-tags convention
- [`ARCHITECTURE.md`](ARCHITECTURE.md) — the end-state architecture (sketched, not yet built)
- Sister project: [lazydap](https://github.com/planetaryescape/lazydap) — the same learning model, in Rust, building a debugger. The Rust solutions to the C problems c-beans surfaces.
