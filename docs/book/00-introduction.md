# Chapter 00 — Introduction

> Read this first. ~10 minutes.

## What this book is, in one paragraph

A guided, multi-session walk through learning C while building a real terminal task manager called **c-beans**. Each chapter is one teaching session: one new concept, one runnable artifact at the end. Read it solo (like a textbook with predict-pauses) or open it in an LLM-aware coding agent and have it taught to you live (the agent runs the chapter as a script, calibrating to your specific predictions). By chapter 33 you'll have published v0.1 — a JSONL-backed CLI + TUI you can install. By chapter 43 c-beans is a daemon-backed multi-client task manager with a SQLite store and a TCP protocol. The C you write along the way is the curriculum; the binary is the artifact.

## What this book is not

- **Not a C reference.** [Modern C](https://gustedt.gitlabpages.inria.fr/modern-c/) by Jens Gustedt and the [C99 / C11 standards](https://www.iso.org/standard/57853.html) cover the language exhaustively. Read those alongside; the standard is hard going but the source of truth.
- **Not a "C in 21 days" tutorial.** Tutorials assume nothing about your prior knowledge and explain everything. This book assumes you've shipped real software in *something* — TypeScript, Python, Java, Go, Ruby — and uses that as your starting model. The chapters surface what you already know, then teach what's different.
- **Not a survey of every C feature.** No discussion of `_Alignas`, no deep dive on `_Generic`, no chapter on threads. The book is structured around what the project needs; rabbit holes get a footnote, not a chapter.
- **Not interactive in the chat-bot sense.** "LLM-as-teacher" mode is a coding agent following the chapter as a script, not a chat about C.

## How learning works here

Three pedagogical ideas, paid for in pain:

### 1. Surface your model before teaching

Every chapter opens with a **🤔 Q:** prompt asking you to predict or describe how something works *in a language you already know*. You answer in your head (solo) or out loud (live). Then the chapter calibrates.

This isn't a quiz. It's a diagnostic. Your prediction tells the chapter (or agent) where you actually are, so it can teach what's *new* and skip what's familiar. If you've already mostly-known something, the chapter extends your model. If you've half-known it, the chapter flags where the analogy breaks.

> **Why it matters:** the hardest learners to teach are the ones who *think* they understand but actually don't. Surfacing the model up-front pulls the misalignment into view before you build code on top of it.

### 2. Predict before run

Every code block has a **🔮 Predict** prompt before you run it: "what will this print?" or "what will the compiler say?" or "what will ASan diagnose?" Answer in your head, then expand the `<details>` block to calibrate.

Wrong predictions are the most teachable moments. They tell you exactly which part of your mental model is buggy. Right predictions move you forward fast.

If you skip the predicts, the chapter degrades into a flat tutorial. The pedagogy depends on you genuinely not knowing the answer when you guess.

### 3. The compiler — and the sanitizers — are the teachers

C's compiler will tell you a lot. Modern clang and gcc emit good diagnostics with `-Wall -Wextra -Wpedantic`. Many chapters deliberately have you write code-that-doesn't-quite-work, hit a warning or error, read it together, and then fix.

ASan and UBSan are the next layer down. They catch things the compiler can't see at compile time — out-of-bounds reads, use-after-free, signed integer overflow, the whole zoo of undefined behaviour. From chapter 04 onwards, ASan is a co-teacher. Many bugs the chapter walks you through are bugs you trigger on purpose to watch ASan call them out.

Pre-empting compiler errors and ASan diagnostics by writing "correct" code from the start would rob you of the conversation between you and the tools that actually builds your mental model. Don't fight the chapter when it tells you to compile something that you're sure won't work. Often the bug isn't where you expect. Often the diagnostic teaches more than the fix.

## The cumulative project: c-beans

This book is a long-arc project, not isolated examples. Each chapter's artifact is *cumulative*:

- **Chapters 01–03** (Phase 0, ceremony): you have a CMake workspace, a `beans` binary that takes args, sanitizers wired into debug builds, CI green.
- **Chapters 04–09** (Phase A, memory primitives): the building blocks. Owned strings, dynamic arrays, tagged unions. ASan is your friend by now.
- **Chapters 10–15** (Phase B, JSON parser): a hand-rolled JSON parser. From characters to tokens to a typed `Task` struct.
- **Chapters 16–19** (Phase C, persistence): the Store interface and a JSONL backend. `beans add` and `beans list` work; a crash mid-write doesn't corrupt the file.
- **Chapters 20–23** (Phase D, domain + tests): a real test harness, the Task model with ULID ids, full CRUD via the CLI, error handling that doesn't lie.
- **Chapters 24–30** (Phase E, TUI): an ncurses TUI with model/update/view, navigation, add/edit/complete/delete, filtering.
- **Chapters 31–33** (Phase F, ship): polish, XDG paths, error rendering, **v0.1.0 published**.
- **Chapters 34–37** (Phase G, SQLite): embed sqlite, prepared statements, transactions, migrate from JSONL. **v0.2.0**.
- **Chapters 38–43** (Phase H, daemon + TCP): BSD sockets, length-prefixed framing, multi-client poll loop, daemon-backed thin clients. **v0.3.0**.

By the time you finish chapter 33, c-beans is shipped. Real users can install it. You did that. By the time you finish chapter 43, c-beans is the same shape as lazydap — a daemon serving multiple clients over a typed protocol, with a TUI that's just one of those clients. The architectural patterns transfer cleanly to Rust if that's where you go next.

The frame to hold: **the goal isn't to ship c-beans. The goal is to fill in the C that's missing under everything else you've ever written.** The published binary is a side effect. (A delicious one.)

## Pace and slowness

This book is slow on purpose. Senior-engineer learners have strong intrinsic motivation but high opportunity cost. The failure mode is "concepts piling up toward a future arrival point that never quite arrives." So:

- **Each chapter caps at one new concept.** Two new concepts in one session loads cognitive capacity past what schema-building can handle.
- **Each chapter ends with a runnable artifact.** Stop after any chapter and there's a working thing. Skateboard → scooter → bike → motorbike → car (Henrik Kniberg's MVP framing).
- **Each chapter ends with a teach-back.** If you can't articulate the concept in your own words, the chapter didn't land. Re-read before moving on.

Sessions that don't land aren't failures; they're data. The book says "go back" because going back is faster than fighting forward on a broken foundation.

## On the JS/TS analogy

You will see references to **JavaScript / TypeScript pains** throughout the book: `undefined is not a function`, `string` after a JSON parse, manually unsubscribing event listeners and forgetting. This is deliberate.

The pain anchor table at [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) catalogues every C concept against the closest pain you've already felt in JS. The framing **"You know how X is painful in JS? C has the same shape, but worse, because Y"** lands much deeper than **"In C you have to do Z."** Adults learn solutions to problems they've actually felt.

If you don't have a JS background, the table works as a translation table to whatever language you do come from. Most pains map across.

## On C as the foundation under everything else

Many of the things that make modern languages (Rust, Go, Swift, Java, Python, JS itself) feel a certain way exist *because of how C feels*. Garbage collection exists because manual `malloc`/`free` is a footgun. The borrow checker exists because use-after-free is a footgun. `Option<T>` exists because NULL is a footgun. Exhaustive `match` exists because `switch` is a footgun.

If you've felt those footguns, the modern-language solutions stop being trivia and start being a gift. That's the through-line. C is the gym. The gym hurts. The hurt is the point.

The sister book [lazydap](https://github.com/planetaryescape/lazydap) walks the Rust counterpart — same pedagogy, in Rust, building a debugger. The same person is reading both. The pains felt in c-beans are the anchors lazydap uses.

## On predict-before-run for senior engineers

Senior engineers can fake confidence. You've probably done it; everyone has. Predict-before-run is a forcing function for honesty: when you write down (or think out loud) "I think this will print X", you commit. When the code prints Y, you can't pretend you knew. The misalignment is now visible, in your own head.

That visibility is what makes the learning stick. Trust the process; it gets less awkward by chapter 04.

## On the LLM-as-teacher mode

If you're reading this in an agent harness (Claude Code, Cursor, etc.), the agent will:

- Read the chapter and its companion teaching-notes file before starting
- Ask the chapter's **🤔 Q:** and **🔮 Predict:** questions to *you* in real time, not just inline
- Wait for your answer
- Calibrate (using the chapter's `<details>` blocks as a menu of common responses)
- Run the actual code in your environment, not a stale screenshot
- Read the actual compiler / ASan output with you, not a cached one
- Close with the chapter's teach-back questions

The agent's contract: **the chapter is the curriculum.** It does not freestyle, skip ahead, or invent new concepts. If something genuinely new comes up, the agent flags it and stays in the chapter's lane.

If the chapter is wrong (a library version drifts, an OS quirk lands, your environment differs), the agent works around it AND files a follow-up to update the chapter. The book improves over time.

## Picking up where you left off

Each chapter's "Before you start" section lists *exact verification commands* you can run to confirm the previous chapter's artifact still works. Run them every time you re-open the book. If anything fails, go back to the chapter that introduced the broken thing.

If you're forking this repo to learn from someone else: chapter tags let you start anywhere. `git checkout chapter-NN` puts the codebase in exactly the state you should begin chapter NN from. See [`CONTRIBUTING.md`](../../CONTRIBUTING.md) for the convention.

## Where to go next

[**Chapter 00b: What is c-beans →**](00b-what-is-c-beans.md)

If you want the personal backstory before diving in: [**Chapter 00c: Why I'm learning C**](00c-why-im-learning-c.md) (optional).

If you'd like to skim the whole arc first: [**Table of contents**](README.md).

If you're an agent: [**AGENTS.md**](../../AGENTS.md) (teaching-mode contract).
