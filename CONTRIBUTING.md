# Contributing to c-beans

How to set up a working dev environment for this repo. For project conventions (commit style, testing rules, teaching mode) see [`AGENTS.md`](AGENTS.md). For architecture see [`ARCHITECTURE.md`](ARCHITECTURE.md).

## Prerequisites

- **C compiler** — `clang` 14+ or `gcc` 11+ . Apple clang on a modern macOS is fine.
- **CMake** — 3.20+ (4.x is fine).
- **Make** or **Ninja** — your build tool. The chapter examples use `cmake --build build` so the underlying generator doesn't matter.
- **clang-format** — for chapter 03 onwards. `brew install clang-format` on macOS, `apt install clang-format` on Linux.
- **clang-tidy** *(optional)* — `brew install llvm` on macOS (then add `/opt/homebrew/opt/llvm/bin` to PATH). `apt install clang-tidy` on Linux. Used for static analysis from chapter 03; not strictly required to build.
- **ncurses headers** — installed by default on macOS. `apt install libncurses-dev` on Ubuntu. Required from chapter 23 (Phase E) onwards.
- **macOS or Linux** — Windows is not currently a target. WSL works.

Earlier chapters (01-12) only need a C compiler and CMake. Add the rest as you reach the chapters that need them.

## Build, test, lint

```bash
# Configure (once per build flavour)
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DBEANS_SANITIZERS=ON

# Build
cmake --build build --parallel

# Test (after TDD-1, chapter 19)
ctest --test-dir build --output-on-failure

# Format check
find src include tests -type f \( -name '*.c' -o -name '*.h' \) -print0 \
  | xargs -0 clang-format --dry-run --Werror

# Format apply
find src include tests -type f \( -name '*.c' -o -name '*.h' \) -print0 \
  | xargs -0 clang-format -i

# Static analysis (optional, requires clang-tidy installed)
cmake --build build --target clang-tidy
```

CI runs build + test + format check on Ubuntu and macOS for every push. Run them locally before pushing.

## Sanitizer notes

The `BEANS_SANITIZERS=ON` CMake option (introduced in chapter 03) wires `-fsanitize=address,undefined -fno-omit-frame-pointer` into debug builds.

- **macOS**: ASan + UBSan work out of the box. Leak detection requires `MallocStackLogging=1 MallocStackLoggingNoCompact=1` in the environment for symbolicated leak reports.
- **Linux**: full ASan + UBSan + LSan available. The CI workflow runs them.
- **Don't ship a release build with sanitizers on**. They add ~2x runtime cost and a memory-shadow that's typically 3x. Release builds use `-DCMAKE_BUILD_TYPE=Release -DBEANS_SANITIZERS=OFF`.

## Chapter tags and releases

This repo is a **learn-by-LLM book** (see [`docs/book/`](docs/book/)). Every chapter has a git tag named `chapter-NN` that points at the state of `main` you should checkout to **begin** that chapter. Each tag has a corresponding GitHub Release.

### How the convention works

- **Naming**: `chapter-NN` is the *start state* of chapter NN. To start chapter 04, run `git checkout chapter-04`. The end of chapter NN is the start of chapter NN+1, so to see the state *after* a chapter ships, checkout the next chapter's tag (or `main` for the latest taught chapter).
- **What it points at**: the commit on `main` that represents "everything taught up to and including chapter NN-1, ready to start chapter NN."
- **When to create**: at the end of a session that completes chapter NN-1, tag the resulting commit as `chapter-NN`. Don't tag the commit being authored — tag the state it produces, which is the starting point for the *next* chapter.
- **Releases auto-create**: pushing a `chapter-*` tag fires [`.github/workflows/release.yml`](.github/workflows/release.yml), which generates release notes from the chapter file's frontmatter and creates the GitHub Release.

### Best-current semantics (tags move forward)

When a retroactive fix lands on `main` that affects an earlier chapter (e.g., a chapter file gets rewritten because of version drift in a tool), **move the affected chapter tags forward**:

```bash
git tag -fa chapter-04 <new-commit>
git push --force-with-lease origin chapter-04
```

The release workflow handles updates idempotently — if the release already exists, its notes are refreshed; if not, it's created.

This means `chapter-NN` tags always point at the *best-current* version of that chapter's start state, not the historical "as-shipped" version. The chapter narrative still tells the story of any pedagogically valuable bugs we hit live; the code at the tagged checkout point reflects the corrected state so future learners don't re-encounter accidents that don't teach anything.

### Why this exists

A book is built linearly across many sessions, but learners don't always want to read it linearly. Chapter tags let someone arrive cold at chapter 09, checkout the corresponding tag, and have the codebase in exactly the right shape to follow the chapter. Same affordance for the LLM-as-teacher mode: an agent picking up a session can verify it's at the right starting state by `git checkout chapter-NN`.

## Commit style

Conventional-style messages, no Claude / co-author attribution:

```
type: description

optional body, in plain prose, focused on the why
```

`type` is one of: `feat`, `fix`, `refactor`, `docs`, `chore`, `test`, `book`, `chapter`. The `book` and `chapter` types are c-beans-specific:

- `book:` — additions/edits to chapter prose, teaching notes, the session plan, the anchor table
- `chapter:` — code that lands as a chapter's artifact (the example file the learner is about to write, or the smoke test)

## Where to look next

- [`AGENTS.md`](AGENTS.md) — non-negotiables, teaching mode protocol, learner profile
- [`ARCHITECTURE.md`](ARCHITECTURE.md) — module layout, Store interface, daemon protocol (sketched)
- [`docs/blueprint/00-overview.md`](docs/blueprint/00-overview.md) — full project vision
- [`docs/book/README.md`](docs/book/README.md) — the book's table of contents
- [`docs/teaching/sessions.md`](docs/teaching/sessions.md) — session-by-session plan
