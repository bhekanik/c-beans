---
chapter: 3
session_id: WS-3
title: Conventions as code
phase: 0
estimated_time_minutes: 75
artifact: `BEANS_SANITIZERS=ON` debug build runs cleanly; clang-format check passes; CI is green
status: stub
related_milestone: docs/implementation/00-workspace-setup.md
---

# Chapter 03 — Conventions as code

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `WS-3` · Phase 0 · ~75 min · [Underlying milestone](../implementation/00-workspace-setup.md)

## What you'll learn

`.clang-format` + `.clang-tidy` + sanitizer CMake module + warning module + GitHub Actions CI walkthrough; ceremony chapter

## What you'll build

`BEANS_SANITIZERS=ON` debug build runs cleanly; clang-format check passes; CI is green

## Before you start

Run chapter 02's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/03-conventions-as-code.md`](../teaching/notes/03-conventions-as-code.md) gets filled during the live session.

## See also

- ← [Chapter 02 — Hello, beans](02-hello-beans.md)
- → [Chapter 04 — First segfault on purpose](04-first-segfault.md)
- [Underlying milestone](../implementation/00-workspace-setup.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
