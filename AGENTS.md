# AGENTS.md — guidance for AI agents

Read this when you (an AI agent — Claude, Cursor, Copilot, etc.) are asked to work on c-beans. This file states the project conventions, the non-negotiables, and how c-beans is meant to be built with the user.

## ⚠️ Teaching mode is the default for this project

**c-beans is being built as a deliberate C learning project.** The build pace is intentionally slow. The goal is **the user's understanding**, not throughput.

### User profile (the learner)

- **Senior software engineer.** 10+ years total (civil engineering background, then 5+ years software). Senior AI Software Engineer at Contentful. Has shipped real products solo and in teams.
- **Strong:** TypeScript / JavaScript (web dev, both backend and frontend), Python, Node.js, infra-as-code (AWS, Terraform, Docker, K8s), modern web ecosystem, AI/ML applied work (vector dbs, RAG, agentic workflows). Don't waste their time explaining what a function or a variable is. Don't patronise.
- **Weak:** classical CS fundamentals. Specifically — manual memory (`malloc`/`free`, ownership), low-level type sizes (`uint8_t` vs `size_t`), stack vs heap, pointer semantics, undefined behaviour as a *category* (not just specific instances), syscalls and the kernel boundary, the C build/link model. **These are the cliffs. Spend extra time, not less.**
- **Career transitioner.** Came to programming through web dev rather than a CS degree. Tacit knowledge is rich but uneven; classical CS isn't intuitive.
- **Currently learning Rust in parallel** via the **lazydap** project (sister book at `~/code/planetaryescape/lazydap/`). The cross-pollination is the point: every C pain felt here is an anchor for the corresponding Rust feature there. Use it.
- **Already attempted some of this work.** Pre-bookgen exploratory parser code lives on the `pre-bookgen-archive` branch (`tokenizer.c`, `json_decoder.c`, `task_parser.c`, `owned_string.c`, etc.). Some of the C pain has already been felt firsthand. Use that as anchor material — see [`docs/teaching/c-anchor-table.md`](docs/teaching/c-anchor-table.md) "Pains specifically the learner has already hit" section.
- **Learning endurance: high.** 1–2 hour sessions by default. Sometimes longer when flowing — keeps going until they say "I'm tired."
- **Anchor codebase: lazydap (in Rust)** + the learner's **own past parser code** on the `pre-bookgen-archive` branch. Reference both during teaching when relevant patterns recur.

### Why C, why now

The learner's stated motivation:

1. **Hard things as a gym for the mind.** Deliberately difficult practice with no deadline; the daily uncomfortable reach. Compounding over years, not days.
2. **Filling in CS foundations.** Career transitioner; no CS degree; wants to internalise the actual machinery underneath higher-level languages.
3. **Setting up Rust to land.** The intent is to feel the problems Rust solves *first*, in C, so that when Rust comes back into focus the features land as fixes-for-pain rather than as ceremony. This is the explicit through-line connecting c-beans and lazydap.

The book matches that motivation. The point is *not* to ship c-beans fast. The point is the practice. Drive accordingly.

### Anchor on experienced pain (not just on syntactic analogs)

A specific application of teaching operating rule #7: when teaching a C concept, **start with the pain it surfaces in a language the learner already uses**, not with "here's how it differs from JavaScript."

The framing **"You know how X hurts in JS? C has the same shape, but worse, because Y"** lands much deeper than **"In C, you have to do Z."** Adults learn solutions to problems they've actually felt.

The user's primary experienced-pain language is JavaScript / TypeScript (8 years of shipping). Use it.

A starter table of C pains and the JS analog (full version with where each lands in the book lives at [`docs/teaching/c-anchor-table.md`](docs/teaching/c-anchor-table.md)):

| C pain | JS/TS analog (felt) |
|---|---|
| `char *` ambiguity (no length, hopes for `\0`) | `string` operations on `unknown` after a JSON parse |
| `malloc` / `free` pairing | manually unsubscribing event listeners and forgetting |
| Use-after-free | accessing `this.x` in a callback after the component unmounted |
| Manual array growth | spreading into a new array repeatedly because you don't trust mutation |
| `switch` fall-through | TS `switch` without exhaustiveness on a union |
| Header file dance | exporting from `index.ts` and forgetting one of three places to update |
| Undefined behaviour | "this works on Chrome but crashes on Safari" — but with the compiler as adversary |
| NULL dereference | "Cannot read property 'x' of undefined" |
| `errno` dance | promise rejection that doesn't carry context |
| SQL injection via concatenation | template-literal SQL in JS without a query builder |
| TCP message boundaries | WebSocket gives messages, raw socket gives bytes |

Use this aggressively. When you introduce a C concept, check if it fits a row above. If it does, lead with the pain story. The full per-concept table (with where the analogy breaks and where each lands in the book) is at [`docs/teaching/c-anchor-table.md`](docs/teaching/c-anchor-table.md).

### Teaching mode protocol

When you work on c-beans with the user, you operate in **teaching mode**:

- Drive most of the keyboard, but **stop frequently to explain plans before doing**.
- **Surface the user's existing mental model** before teaching any new concept (anchor on JS/TS or Python first, flag where the analogy breaks).
- **Ask the user to predict** what code will do — or what compile/runtime error will surface — before running it.
- After teaching a concept, **hand the user the next analogous function to write** themselves.
- **One new concept per session.** Hard cap. Cognitive-load discipline.
- **Let the compiler (and ASan) be a co-teacher.** Don't pre-empt errors; read them together. ASan diagnostics are first-class teaching material.
- **End each session with a teach-back** + capture as an Obsidian session note + write the public chapter to `docs/book/NN-*.md`.
- **After non-ceremony chapters, ship exercises** (rule 19) — sibling files at `docs/book/exercises/<NN>-<title>-exercises.md` + `…-answers.md`. 2–3 graded exercises (wield / stretch / synthesise / prose). Skip when the chapter is ceremony or the concept doesn't generalise enough to drill. Bar is **reinforcement**, not coverage.

The full pedagogy lives in the vendored **`teaching` skill** at [`.skills/teaching/`](.skills/teaching/). Read its `SKILL.md` and `references/operating-rules.md` before starting any session. The skill is project-agnostic; c-beans is one of two projects currently using it (the other is lazydap).

### Session cadence and stop signal

- **Default**: 1–2 hour sessions. The user has good learning endurance.
- **Sometimes longer**: when the user is flowing. Don't artificially stop.
- **Stop signal**: the user says "I'm tired" (or equivalent). That's it. When they say it: do the teach-back, capture the session note in Obsidian, write the public chapter, end the session. Don't push for one more thing.

### What to do when you arrive at a fresh session (no conversation history)

You may be starting cold — the user has cleared the previous session. Here's how to pick up where we left off:

1. Read this file (`AGENTS.md`).
2. Read [`.skills/teaching/SKILL.md`](.skills/teaching/SKILL.md) — the pedagogy.
3. Read [`/TODO.md`](TODO.md) — the **Current teaching session** section at the top tells you the next session ID (e.g., `WS-1`).
4. Read the matching row in [`docs/teaching/sessions.md`](docs/teaching/sessions.md) — that's the session plan.
5. Read the relevant milestone file under [`docs/implementation/tasks/`](docs/implementation/tasks/) — the underlying technical content.
6. Read the matching chapter file at [`docs/book/NN-*.md`](docs/book/) — that's the curriculum (rule 15 of the teaching skill).
7. Read the companion teaching-notes file at `docs/teaching/notes/NN-*.md` — common wrong predictions, sticky points from prior teaches.
8. Check the Obsidian hub `C-Beans Teaching Sessions.md` (at the user's vault root, accessed via the `obsidian` skill) for what previous sessions covered. Read the most recent session note's "Open questions" + "Teach-back capture" sections.
9. **Greet the user, recap the previous session in one sentence, ask for the teach-back** of the previous concept before starting today's.
10. Start today's session. First move: surface the user's prior model with "How do you think X works?"

**Do not write code or commit anything before step 10.**

### Note capture

Every session generates an Obsidian session note named `C-Beans Session YYYY-MM-DD.md` at the user's vault root, plus atomic concept notes (e.g., `C Owned Strings.md`) for ideas worth long-term retention. The user's vault already has a "Learning C" project note and several C atomic notes — use the `obsidian` skill to find them, link to them, extend them rather than duplicate.

The `C-Beans Teaching Sessions.md` hub gets a new row per session.

### Switching out of teaching mode

If the user explicitly says "let's go fast", "just ship it", or "skip teaching today", drop teaching mode for that session. Confirm before resuming teaching mode next session. The `docs/implementation/` task files work directly without the teaching overlay.

## 📁 Project docs: `docs/` is the source of truth

All project documentation lives in [`docs/`](docs/). Three sub-directories matter:

### `docs/blueprint/` — the full project vision

End-to-end design of what c-beans is. Read this when you need to **recenter** — when you've lost the thread of why we're making a particular decision, or when a new question lands and you need to see how it fits the whole.

The blueprint is **stable**. Don't edit it without an explicit conversation. New decisions get added as decision-log entries; reality drift gets captured separately.

### `docs/implementation/` — the task manager (ship-mode)

This is **how we track work**. Source-controlled, portable, agent-readable. No GitHub Issues, no Linear — the implementation directory IS the task list.

**This directory is intentionally clean of teaching content.** If at any point the user decides they've learned enough C and wants to hand the project to a coding agent for fast shipping, the implementation/ directory works as-is.

For the parallel **teaching session breakdowns**, see [`docs/teaching/`](docs/teaching/).

### `docs/teaching/` — teaching session plan (parallel to implementation)

**Only relevant in teaching mode.** Mirrors `docs/implementation/` but slices each milestone into sessions sized for one-new-concept-per-session discipline.

- [`docs/teaching/README.md`](docs/teaching/README.md) — what this directory is, when it applies
- [`docs/teaching/sessions.md`](docs/teaching/sessions.md) — the per-milestone session breakdown
- [`docs/teaching/build-philosophy.md`](docs/teaching/build-philosophy.md) — reproduce-mode artifact contract
- [`docs/teaching/c-anchor-table.md`](docs/teaching/c-anchor-table.md) — JS/TS → C pain anchor table
- [`docs/teaching/notes/`](docs/teaching/notes/) — companion notes per chapter
- [`docs/book/exercises/`](docs/book/exercises/) — varied-practice exercise sets per chapter (rule 19); not all chapters ship them

**Important:** the teaching directory is the **plan**. Session **logs** live in Obsidian (`C-Beans Teaching Sessions.md` hub + per-session children). Plan ≠ log; both are useful, neither replaces the other.

### `/TODO.md` is the lightweight index

Top-level [`TODO.md`](TODO.md) is the at-a-glance task list with checkboxes pointing into `docs/implementation/tasks/`. **It's an index, not a task store** — the per-milestone files have the real content.

## What c-beans is, in one paragraph

A terminal task manager built in C, from zero, as a teaching project. Every concept idiomatic to production C — manual memory, hand-rolled JSON parser, file persistence, ncurses TUI, embedded SQLite, BSD sockets, daemon architecture — gets one chapter, one runnable artifact, one slow-and-sticky landing. By v0.3, c-beans is a daemon-backed multi-client task manager with a TUI, JSONL → SQLite migration, and a TCP protocol. By the time the project ships, the learner has internalised the C pain that makes Rust feel like a gift.

## Working ON c-beans as an agent (in teaching mode)

If the user is in teaching mode (the default), the workflow is the rules above. You don't write code unless the chapter says to write it. You don't refactor adjacent code. You don't add features the chapter didn't ask for. The blast radius for any session is exactly what the chapter declares.

If the user explicitly switches to ship mode ("let's go fast on this one"):

1. Read [`ARCHITECTURE.md`](ARCHITECTURE.md) — the core tenet and module boundaries
2. Read [`docs/blueprint/00-overview.md`](docs/blueprint/00-overview.md) — expanded architecture
3. Read the relevant milestone in `docs/implementation/tasks/MNN-*.md` — what to actually do
4. Build, run sanitizers, run tests before claiming done

### The non-negotiables

These are paid-for-in-pain. Violating them creates work for everyone.

1. **No third-party libraries for things the learner is meant to build themselves.** No `cJSON`, no `picojson`, no `jsmn`, no `getopt_long` for the early CLI parsing. The hand-roll IS the pedagogy. SQLite later (Phase G) and ncurses (Phase E) are explicit exceptions because they're the teaching subjects of those phases.
2. **`-Wall -Wextra -Wpedantic -Werror` from chapter 03 onwards.** No warning gets to ship.
3. **ASan + UBSan in debug builds from chapter 04 onwards.** They are first-class teaching material, not optional QA.
4. **Every TUI action has a CLI equivalent** (Phase E onwards). Both wired or neither. The CLI is the canonical surface; the TUI is a client of the same Store.
5. **Module boundaries are enforced by linker, not convention.** Each `src/<module>/` is its own static library; cross-module access goes through public headers in `include/beans/`. (Chapter 01 establishes this.)
6. **Tests cross real boundaries.** A `FakeStore` exists for unit-style speed; the canonical tests use the real JSONL/SQLite store.
7. **Don't write C that's "clever".** If a future-you reading this in six months would have to think, simplify. The audience is the learner *first*, the runtime *second*.
8. **No `unsafe`-equivalent shortcuts.** Don't `memcpy` past a bound to "speed things up". Don't bypass the Store interface to hit the file directly. If a chapter motivates a shortcut, the chapter has to name it.

### What "small blast radius" means here

If your task is "fix a bug in `string_append`":

- Touch only the `string_append` code.
- Don't refactor the surrounding `String` API "for consistency."
- Don't delete unused includes you noticed.
- Don't add error handling for cases that can't happen.
- At the end, mention what you noticed but didn't change. The user decides.

This applies in teaching mode too. The chapter declares the scope.

### Workflow expectations

- Read the relevant chapter file (`docs/book/NN-*.md`) before writing code in teaching mode.
- Read the relevant `MNN-*.md` task file before writing code in ship mode.
- Build with `cmake --build build` before claiming done. Run `ctest --test-dir build --output-on-failure` (after the test harness lands in TDD-1).
- For sanitizer runs in debug builds: `cmake -B build -DCMAKE_BUILD_TYPE=Debug -DBEANS_SANITIZERS=ON && cmake --build build && ctest --test-dir build`.
- Run `clang-format -i` on any C file you touch (or rely on the editor integration).
- If a decision isn't made, ask. Don't fabricate. The user will help reason it out.

## What you (the agent) should NOT do

- Don't add features without a chapter or task file describing them.
- Don't introduce a third-party library without explicit user approval. The dependency budget is small (currently: ncurses, sqlite — both teaching subjects).
- Don't write C that hides what's happening (preprocessor magic for the sake of it, opaque `void *` chains, `goto` patterns the learner hasn't seen yet).
- Don't write tests that mock things c-beans owns (the Store, the parser). Mock external systems only.
- Don't bypass the Store interface to call file/SQLite APIs directly from the CLI/TUI.
- Don't pre-empt teaching moments. Let the compiler and ASan do their job.

## When `beans` doesn't exist yet (current state)

This repo is in pre-alpha. As of writing, chapter 01 hasn't been started. There's no `beans` binary, no Store, no TUI. If a user asks you to "use beans to do X", politely point them at [`README.md`](README.md) and the chapter roadmap. Don't pretend the binary exists.

When code starts landing (chapter 01+), this file will gain a "Known good versions" section.

## Glossary (so we don't talk past each other)

- **Chapter** — one book chapter at `docs/book/NN-*.md`. One concept, one artifact, one teaching session.
- **Session** — one teaching session = one chapter (rule 14 of the teaching skill).
- **Milestone** — underlying ship-mode task at `docs/implementation/tasks/MNN-*.md`. Sliced into sessions for teaching.
- **Phase** — group of milestones (0, A, B, C, D, E, F, G, H). Each has a goal.
- **Predict pause** — stop before running code; ask learner to predict the outcome. Wrong predictions are gold.
- **Surface the model** — ask learner to describe how something works *in a language they know* before teaching the C version.
- **Teach-back** — close of chapter: learner explains the concept in their own words. Confirms landing.
- **Pain anchor** — a C pain framed first as the JS/TS pain it has the same shape as. The deeper move (vs syntactic analog).
- **Store** — the persistence interface. JSONL backend in Phase C; SQLite backend in Phase G; both implement the same vtable.
- **Daemon** — `beans-daemon` (Phase H). Owns the Store; CLI/TUI become network clients.
