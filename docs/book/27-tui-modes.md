---
chapter: 27
session_id: M11-2
title: Modes — model/update/view
phase: E
estimated_time_minutes: 90
artifact: An `AppState`/`Msg`/`update(state, msg)` refactor lands; `NORMAL` / `INSERT` / `EDIT` modes work; the `view` function is pure
status: stub
related_milestone: docs/implementation/tasks/M11-tui-interactivity.md
---

# Chapter 27 — Modes — model/update/view

> **Status:** stub. Not yet taught live; will be filled in when the corresponding teaching session runs. Below is the planned scope; the predict-pauses, compiler conversations, and pain-anchor framing get added during the live session per the chapter template (see chapter 01 for the canonical shape).

> Session ID: `M11-2` · Phase E · ~90 min · [Underlying milestone](../implementation/tasks/M11-tui-interactivity.md)

## What you'll learn

The Elm Architecture in C; why this structure makes the TUI testable; how function pointers help; anchor to React's `useReducer`

## What you'll build

An `AppState`/`Msg`/`update(state, msg)` refactor lands; `NORMAL` / `INSERT` / `EDIT` modes work; the `view` function is pure

## Before you start

Run chapter 26's artifact to confirm the baseline. Exact verification commands land when this chapter is drafted.

## Outline (placeholder — filled during the live session)

1. *Surface the model* — a 🤔 Q: prompt anchored against the reader's prior-language model (see [`docs/teaching/c-anchor-table.md`](../teaching/c-anchor-table.md) for the JS/TS pain pairings).
2. *Concept slices* — broken down per the one-concept-per-session rule. Each slice has a 🔮 Predict pause before the code lands.
3. *Compiler / ASan conversation* — at least one deliberate-error walkthrough where the compiler or ASan points at the bug.
4. *Try it yourself* — one analogous task the reader writes alone (gradual release: I do → we do → you do).
5. *What you can run now* — the artifact, demonstrated.
6. *Teach-back* — 📣 questions to confirm the concept landed.
7. *Pain anchors covered* — table summarising what JS/TS pain each new construct addresses.

The companion teaching-notes file at [`docs/teaching/notes/27-tui-modes.md`](../teaching/notes/27-tui-modes.md) gets filled during the live session.

## See also

- ← [Chapter 26 — Navigation](26-tui-navigation.md)
- → [Chapter 28 — Add tasks via TUI](28-tui-add.md)
- [Underlying milestone](../implementation/tasks/M11-tui-interactivity.md)
- [Book README / TOC](README.md)
- [Pain anchor table](../teaching/c-anchor-table.md)
