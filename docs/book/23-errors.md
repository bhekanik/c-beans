---
chapter: 23
session_id: M9-1
title: Errors as values
phase: D
estimated_time_minutes: 75
artifact: A `BeansError` enum + `Result_Task`-shaped returns replace ad-hoc `-1`/NULL conventions; errors propagate cleanly through the call stack
status: stub
related_milestone: docs/implementation/tasks/M09-errors.md
---

# Chapter 23 — Errors as values

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M9-1` · Phase D · ~75 min · [Underlying milestone](../implementation/tasks/M09-errors.md)

## What you'll learn

Error-as-value vs error-as-exception; why C doesn't have exceptions (cost of `setjmp`/`longjmp`); how Rust's `Result<T, E>` and `?` are this with sugar

## What you'll build

A `BeansError` enum + `Result_Task`-shaped returns replace ad-hoc `-1`/NULL conventions; errors propagate cleanly through the call stack

## Before you start

Run chapter 22's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/23-errors.md`](../teaching/notes/23-errors.md) gets filled during the live session.

## See also

- ← [Chapter 22 — CRUD via CLI](22-crud-cli.md)
- → [Chapter 24 — Hello, ncurses](24-hello-ncurses.md)
- [Underlying milestone](../implementation/tasks/M09-errors.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
